/*
 * rionet - Ethernet driver over RapidIO messaging services
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#include <linux/kernel.h>
#include <linux/dma-mapping.h>
#include <linux/delay.h>
#include <linux/rio.h>
#include <linux/rio_drv.h>
#include <linux/slab.h>
#include <linux/rio_ids.h>

#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/cdev.h>
#include <linux/fs.h>

#include <linux/semaphore.h>

#include <asm/io.h>
#include <asm/fsldma.h>
#include <linux/dmaengine.h>
#include <linux/device.h>
#include "riodt.h"
#include "fslrio_priv.h"
#include "../lte_system.h"
#include "sriofsm.h"
#include "queue.h"

#undef DEBUG

#define DRV_NAME        "riodt"
#define DRV_VERSION     "0.0"
#define DRV_AUTHOR      "unknow"
#define DRV_DESC        "Data Transfor Over RapidIO"
#define TITLE         "RidDt"

#define MODIFY_LAW  /* 修改分配给SRIO的地址空间大小，如果仅做测试使用不需要更改 */    
//#undef  MODIFY_LAW

MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION(DRV_DESC);
MODULE_LICENSE("GPL");

#define AMC719_HOST_DEVICE_ID   (0)

#define RIODT_DOORBELL_MIN	0x0
#define RIODT_DOORBELL_MAX	0xffff

#define RIODT_MAILBOX		0

#define RIODT_RX_RING_SIZE    128	
#define RIODT_TX_RING_SIZE    128

static LIST_HEAD(riodt_peers);
struct riodt_peer {
	struct list_head node;	
	struct rio_dev *rdev;
	struct resource *res;
};


/*
 * This is a fast lookup table for translating TX
 * Ethernet packets into a destination RIO device. It
 * could be made into a hash table to save memory depending
 * on system trade-offs.
 */
#define is_riodt_capable(pef, src_ops, dst_ops)		\	((pef & RIO_PEF_INB_MBOX) &&		\
	(pef & RIO_PEF_INB_DOORBELL) &&	\	(src_ops & RIO_SRC_OPS_DOORBELL) &&	\
	(dst_ops & RIO_DST_OPS_DOORBELL))
#define dev_riodt_capable(dev) \
	is_riodt_capable(dev->pef, dev->src_ops, dev->dst_ops)

#define RIODT_TX_RING_SIZE 128
#define RIODT_RX_RING_SIZE 128
#define RIODT_DBELL_RING_SIZE 128
#define RIODT_DMA_RING_SIZE 128
#define RIODT_TX_LOCKED -1
#define RIODT_TX_BUSY   -2
#define RIODT_TX_INVALID -3
#define RIODT_TX_OK      0
#define DMA_TIMEOUT 3000 //dma单位ms
#define RIODT_WIN_START_ADDR 0x1000000

#ifdef MODIFY_LAW
#define RIODT_DIRECT_WIN_SIZE  0x400000
#define RIODT_NREAD_WIN_SIZE  0x100000000ull
#define RIODT_NWRITE_WIN_SIZE 0x100000000ull
#define SRIO_PORT0_MEM_SIZE      0x400000000ull
#define SRIO_PORT0_MEM_BASEADDR  0x800000000ull
#else
#define RIODT_DIRECT_WIN_SIZE  0x1000000
#define RIODT_NREAD_WIN_SIZE  0x1000000
#define RIODT_NWRITE_WIN_SIZE 0x1000000
#endif

#define RIODT_MAX_MSG_SIZE    (256 - 16)// MSG 
#define RIODT_NREAD_IRQ 28
#define RIODT_NWRITE_IRQ 29
#define DMA_CHAIN 0
#define DMA_DIRECT 1
#define RIODT_OUT_ATMU_MAX	4 
#define CCSR_LAW_BASEADDR   (0xffe000C00ULL) 
#define DELAY_LOG_COUNT	200  
#define RIODT_DBELL_COUNT 256

#define DEST_ID 0x80
#define LOCAL_ADDR 0xfc100000
#define AMC719_RESVMEM_BASEADDR      (0xfc100000)
#define AMC719_RESVMEM_LENGTH      (1024*1024*4) 
#define RIODT_DBELL_COUNT 256

struct rio_inatmu_regs {
	u32 riwtar;
	u32 pad;
	u32 riwbar;
	u32 pad1;
	u32 riwar;
	u32 pad2[3];
};
struct riodt_dbell_info {
	u16 sid;
	u16 tid;
	u16 info;
	u16 pad;
};

struct riodt_dma_info {
	u32 result;       
	void *arg;
};

struct riodt_dma_status {
	struct fsl_dma_ld_hw *dma_desc;
	u32 destid;
	u32 result;
	void *arg; 
};

struct riomsg {
	wait_queue_head_t rx_wait;/* receive wait queue */
	struct sk_buff *rx_list[RIODT_TX_RING_SIZE];/*buffer list */
	unsigned int rx_rp;/*buffer list read pointer*/
	unsigned int rx_wp;/*buffer list read pointer*/
	unsigned int rx_drop;/*buffer list drop count*/
	struct mutex lock;/* mutex lock */
};

struct msghead {
	u16 msg_select;
	u16 msg_size;
};

struct riodbell {
	wait_queue_head_t dbell_wait;/*receive wait queue*/
	struct riodt_dbell_info dbell_list[RIODT_DBELL_RING_SIZE];/*doorbell list */
	unsigned int dbell_rp;/*dbell list read pointer*/
	unsigned int dbell_wp;/*dbell list write pointer*/
	unsigned int dbell_drop;/*dbell list drop count*/
	struct mutex lock;/* mutex lock */
};

struct riodma {
	wait_queue_head_t dma_wait;/*wait queue */
	struct riodt_dma_info dma_list[RIODT_DMA_RING_SIZE];/* dmalink list */
	unsigned int dma_rp;/*dma list read pointer*/
	unsigned int dma_wp;
	unsigned int dma_drop;
	struct mutex lock;
	struct mutex dma_lock;
	spinlock_t dev_lock;
	int irq;
	int mode;

	void __iomem *rio_virt;
	dma_addr_t rio_phys;
	dma_addr_t mm_phys;
	void *mm_virt;
	struct rio_atmu_regs __iomem *out_atmu_regs;
	u64 size;

	struct fsldma_chan_regs *dma_regs;
	struct fsl_dma_ld_hw *dma_desc;
	dma_addr_t phy_desc;
	struct riodt_dma_status dma_status[RIODT_DMA_RING_SIZE];
	unsigned int hw_wp;
	unsigned int hw_rp;
	unsigned int hw_ack;
	unsigned int hw_drop;
};

struct riodt {
	struct rio_mport *mport;
	struct sk_buff *rx_skb[RIODT_TX_RING_SIZE];/*hw buffer queue*/
	struct riomsg msg_dev[2];/*msg unit 0*/
	struct riodma dma_dev[3];/* nread/nwrite DMA */
	struct riodbell dbell_dev; /* DOORBELL */
	int rx_slot;    /*hw buffer rx index */
	int tx_cnt;/*tx buffer count*/
	int ack_slot;/*hw buffer tx index*/
	spinlock_t lock;/* msg dev spinlock */
	spinlock_t tx_lock;/* msg tx spinlock */
	/* inbound atmu */
	struct rio_inatmu_regs __iomem *in_atmu_regs;
	struct rio_atmu_regs __iomem *out_atmu_regs[RIODT_OUT_ATMU_MAX];
	struct cdev cdev;
};


typedef struct srio_route_stat_info
{
	unsigned int NewFlag;
	unsigned short int AMC1_;
	unsigned short int AMC2_;
	unsigned short int DSP1_;
	unsigned short int DSP2_;
	unsigned short int FPGA1_;
	unsigned short int FPGA2_;
}SRIO_ROUTE_INFO;

/** riodt major, minor **/
static int major = 0;
static int minor = 0;

void *mapaddr = NULL;//内存映射地址
static int db_cnt = 0; //用于计数doorbell
int dbcheck_cnt = 0; //用于计数tasklet处理过的doorbell
char* buffer = NULL;
u32 data_size = 0x2CEC0;

static struct class *rio_class = NULL;

//hrtimer para
static struct hrtimer timer1;
ktime_t kt1;
static struct hrtimer timer2;
ktime_t kt2;

unsigned long timer_counter = 0;
struct rio_dma_para timer1_para = {0,0x54,0xfc100500,0x83096500,0x4000,0,1000000,0x0,0};
struct new_check_para timer2_para;
unsigned int sendcount = 0;
unsigned int totalcount = 0;
unsigned int offset = 0x4000;
//unsigned long long AddrStart = 0xfc215000;
void* VirAddr=NULL;
u32 dest_addr = 0x83096500;//type1:0x83096500  type3:0x830aa500

/*
unsigned long long AddrStart[QUEUE_MAX_NUM] = { 0xfc100500+0*QUEUE_OFFSET*0x4000,
											    0xfc100500+1*QUEUE_OFFSET*0x4000,
											    0xfc100500+2*QUEUE_OFFSET*0x4000,
												0xfc100500+3*QUEUE_OFFSET*0x4000,
												0xfc100500+4*QUEUE_OFFSET*0x4000,
												0xfc100500+5*QUEUE_OFFSET*0x4000,
												0xfc100500+6*QUEUE_OFFSET*0x4000,
												0xfc100500+7*QUEUE_OFFSET*0x4000,
												0xfc100500+8*QUEUE_OFFSET*0x4000,
												0xfc100500+9*QUEUE_OFFSET*0x4000,
											  };
*/

unsigned long long AddrStart[QUEUE_MAX_NUM] = { 0,
												0,
											    0xfc100500+0*QUEUE_OFFSET*0x4000,
											    0,
												0,
												0,
												0,
												0xfc100500+1*QUEUE_OFFSET*0x4000,
												0,
												0,
											  };								
											  
unsigned long long VirAddrStart[QUEUE_MAX_NUM];											  
											  
//delay_log
int delay_log_buf[DELAY_LOG_COUNT];
unsigned int log_wp[DELAY_LOG_COUNT];
unsigned int log_ack[DELAY_LOG_COUNT];
int delay_log_p = 0;
int prev_time = 0;

//test para
unsigned int data_size;
unsigned int buffnum = 0;
unsigned int subframenum = 0;
unsigned int sysframenum = 0;
unsigned int count[1000];

volatile ElemType NextData;

LinkQueue UnionQueue[QUEUE_MAX_NUM];
	
struct riodt g_riodt;
struct file g_fil;
struct riodt *dev;
struct srio_enum_cnt_info *seci = NULL;
struct srio_enum_stat_info sesi = {{0},{0},{0}};

struct rio_dma_para memread_para;
struct rio_dma_para memwrite_para;
static struct tasklet_struct dbell_tasklet;
unsigned int dbcheck[RIODT_DBELL_COUNT][3]; //用于记录doorbell check后的结果
unsigned int databyte_head = 0;
unsigned int databyte_tail = 0;
unsigned int dbcheck_p = 0;
static int i=0;
spinlock_t hrtimer2_lock = SPIN_LOCK_UNLOCKED;
void *checkaddr = NULL;
void *sourcepusch = NULL;

extern struct list_head rio_mports;

/**************function declaration**************/
static enum hrtimer_restart hrtimer_handler2(struct hrtimer *timer);
static int rio_hrtimer1_start(struct riodt *dev, unsigned int destid);
static int rio_hrtimer1_init(struct riodt *dev, unsigned int destid);
static void rio_hrtimer1_stop(void);
static int rio_hrtimer2_start(struct riodt *dev, unsigned int destid);
static void rio_hrtimer2_stop(void);
extern int rio_enum_init(struct rio_mport *port,unsigned long arg);
extern void rio_put_enum_info(unsigned long user_addr);
extern void rio_put_enum_error_info(unsigned long user_addr);

static void print_dbcheck(void);
static void send_dsp_route_info(struct riodt *timer_dev);
static void send_ueul_type1(struct riodt *timer_dev, u16 timer_destid, u64 timer_data, unsigned int timer_len, u64 timer_addr, void *timer_arg);
static void send_ueul_type3(struct riodt *timer_dev, u16 timer_destid, u64 timer_data, unsigned int timer_len, u64 timer_addr, void *timer_arg);
static void enbul_type2_send(struct riodt *timer_dev, u16 timer_destid, u64 timer_data, unsigned int timer_len, u64 timer_addr, void *timer_arg);

extern int rio_enum_init(struct rio_mport *port,unsigned long arg);
extern void rio_put_enum_info(unsigned long user_addr);
extern void rio_put_enum_error_info(unsigned long user_addr);
void rio_hrtimer1_stop_wrapper(void);
void send_dsp_route_info_wrapper(void);
unsigned int GetFrameNo(void);
unsigned int GetsubFrameNo(void);
void send_dbell(u16 sub);
	
/**************************************************************************************************
**函数名：gettb
**描述：获取寄存器的值
**输入：
**输出：
**返回值：tc
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static inline unsigned long gettb(void)
{	unsigned long tc;	__asm__ volatile("mftb %0" : "=r" (tc));
	return tc;
}

unsigned int GetFrameNo(void)
{
	
	return sysframenum;
}

unsigned int GetsubFrameNo(void)
{
	
	return subframenum;
}


/**************************************************************************************************
**函数名：riodt_outatmu_set
**描述：配置outbound atmu寄存器的值
**输入：struct rio_atmu_regs *atmu_regs, u64 addr, unsigned int len, u16 destid
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_outatmu_set(struct rio_atmu_regs *atmu_regs, u64 addr, unsigned int len, u16 destid)
{
	out_be32(&atmu_regs->rowtar, (destid << 22 | (u32)(addr >> 12)));
#ifdef DEBUG
	printk(KERN_INFO"%s:out bound atmu set wind addr 0x%llx, size 0x%x, N = 0x%x\n", DRV_NAME, addr, len, __ilog2_u64(len)-1);
#endif
	return 0;
}


void rio_hrtimer1_stop_wrapper(void)
{
	rio_hrtimer1_stop();
}

void send_dsp_route_info_wrapper(void)
{
	send_dsp_route_info(&g_riodt);
}
/**************************************************************************************************
**函数名：riodt_dma_tx_sync
**描述：DMA同步发送函数
**输入：struct riodma *dma, u16 destid, dma_addr_t dst, dma_addr_t src, unsigned int len
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_dma_tx_sync(struct riodma *dma, u16 destid, dma_addr_t dst, dma_addr_t src, unsigned int len)
{
	unsigned int timeout = 0;
	struct fsldma_chan_regs *dma_regs = dma->dma_regs;

	/* Check if the DMA channel is busy */
	if (dma_regs->sr & FSL_DMA_SR_CB)	{
		dma_regs->sr = 0xffffffff;
		dma_regs->mr = 0;
		printk(KERN_INFO "%s:dma busy exit\n", DRV_NAME);			
		return -EBUSY;
	}
	dma_regs->mr |= ((FSL_DMA_MR_BWC_DIRECT << FSL_DMA_MR_BWC_SHIFT) & FSL_DMA_MR_BWC_MASK) | \
					FSL_DMA_MR_CTM | FSL_DMA_MR_SRW;

	dma_regs->sar = (u32)(src & 0xffffffff);
	dma_regs->satr = FSL_DMA_SATR_SREADTYPE_SNOOP_READ | (u32)((src >> 32) & 0x3ff);
	dma_regs->bcr = len;
	dma_regs->datr = FSL_DMA_DATR_DWRITETYPE_SNOOP_WRITE | (u32)((dst >> 32) & 0x3ff);

	/* FPGA0 PORT0/PORT1 DSP0/1 no response */
	if (0x02 != (destid & 0x0F))
		dma_regs->datr |= FSL_DMA_DATR_NLWR;

	/* Write dest addr reg, then the transfer start */	
	dma_regs->dar = (u32)(dst & 0xffffffff);
	__asm__ __volatile__("sync");

	timeout = DMA_SET_CB_TIMEOUT;
	/* Wait for the transfer finish */
	while (dma_regs->sr & FSL_DMA_SR_CB)	{
		__asm__ __volatile__("nop");
		if ((timeout--) == 0)
		{
			/* Clear start bit to Stop the DMA transfer */
			dma_regs->mr = 0;
			printk(KERN_INFO "%s:dma busy wait timeout\n", DRV_NAME);			
			return -EBUSY; 
		}
	}
	if ((dma_regs->sr & FSL_DMA_SR_TE) || (dma_regs->sr & FSL_DMA_SR_PE))
	{
		/* Clear status regsiter */
		dma_regs->sr = 0xffffffffU;
		dma_regs->mr = 0;
		printk(KERN_INFO "%s:dma error\n", DRV_NAME);			
		return -EIO;	}

	return 0;
}

/**************************************************************************************************
**函数名：dma_is_idle
**描述：判断DMA是否空闲
**输入：struct riodma *dma
**输出：
**返回值：!(sr & FSL_DMA_SR_CB)) || (sr & FSL_DMA_SR_CH)
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int dma_is_idle(struct riodma *dma)
{
	u32 sr = dma->dma_regs->sr;
	return (!(sr & FSL_DMA_SR_CB)) || (sr & FSL_DMA_SR_CH);
}

/**************************************************************************************************
**函数名：dma_halt
**描述：DMA挂起
**输入：struct riodma *dma
**输出：
**返回值：
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static void dma_halt(struct riodma *dma)
{
	u32 mode;
	int i;

	mode = dma->dma_regs->mr;
	mode |= FSL_DMA_MR_CA;	dma->dma_regs->mr = mode;

	mode &= ~(FSL_DMA_MR_CS | FSL_DMA_MR_EMS_EN | FSL_DMA_MR_CA);
	dma->dma_regs->mr = mode;

	for (i=0; i < 100; i++) 
	{
		if (dma_is_idle(dma))
			return;
		udelay(1);
	}

	if (!dma_is_idle(dma))       		
		printk(KERN_DEBUG "DMA halt timeout\n");
}

/**************************************************************************************************
**函数名：riodt_dma_xfer_queue
**描述：DMA的发送队列
**输入：struct riodma *dma
**输出：
**返回值：ret
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_dma_xfer_queue(struct riodma *dma)
{
	int ret = 0;
	unsigned long flags;	
	struct fsl_dma_ld_hw *desc = NULL;
	struct riodt_dma_status *status;

	spin_lock_irqsave(&dma->dev_lock, flags);

	if (dma->hw_rp == dma->hw_wp) 
	{
		/*判断队列中是否有数据*/
#ifdef DEBUG        	printk(KERN_DEBUG "No pending desc\n");
#endif
		goto out;    
	}

	/* dma controller is not idle, still busy */	
	if (!dma_is_idle(dma)) 
	{
#ifdef DEBUG
   	printk(KERN_DEBUG "DMA controler still busy\n");
#endif
        goto out;	}

	/* make sure the dma channel is released */
	dma_halt(dma);

	status = &(dma->dma_status[dma->hw_rp++ % RIODT_DMA_RING_SIZE]);
	desc = status->dma_desc;
#ifdef MODIFY_LAW	/* setup out bound atmu */
	riodt_outatmu_set(dma->out_atmu_regs, 0, 0, status->destid);
#endif
#ifdef DEBUG
	printk(KERN_DEBUG "%s:start xfer %d desc\n", DRV_NAME, dma->hw_rp - 1);
#endif
	/* setup dma channel reg */
	dma->dma_regs->eclndar = 0;
	dma->dma_regs->clndar = virt_to_phys((void *)desc) | FSL_DMA_CLNDAR_EOSIE;
	
	out:
		spin_unlock_irqrestore(&dma->dev_lock, flags);
		return ret;
}

/**************************************************************************************************
**函数名：riodt_dma_tx_submit
**描述：通过hw_wp和hw_ack判断发送队列是否溢出或空闲
**输入：struct riodma *dma, u16 destid, u64 dst, u64 src, u32 len, void *arg
**输出：
**返回值：ret
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_dma_tx_submit(struct riodma *dma, u16 destid, u64 dst, u64 src, u32 len, void *arg)
{
	int ret;
	struct fsl_dma_ld_hw *desc = NULL;
	struct riodt_dma_status *status = NULL;

	if (0 == len || len > RIODT_NREAD_WIN_SIZE)
	{
		/*输入的发送长度出错*/
		printk(KERN_ERR "%s:dma data length error, len = %d\n", DRV_NAME, len);
		return -EINVAL;	}

	/* if queue is full, return */	if ((dma->hw_wp - dma->hw_ack) >= RIODT_DMA_RING_SIZE)
	{
		dma->hw_drop++;
		printk(KERN_INFO "%s: dma desc queue is full!\n", DRV_NAME);
		return -EBUSY;
	}

	/* init status */
	status = &dma->dma_status[dma->hw_wp % RIODT_DMA_RING_SIZE];
	status->arg = arg;
	status->destid = destid;
	status->result = DMA_ERR;

	/* init dma desc */
	desc = status->dma_desc;
	desc->src_attr = (u32)(src>>32) | FSL_DMA_SATR_SREADTYPE_SNOOP_READ;
	desc->src_addr = src;
	desc->dst_attr = (u32)(dst>>32) | FSL_DMA_DATR_DWRITETYPE_SNOOP_WRITE;
	desc->dst_addr = dst;
	desc->next_ln_ex_addr = 0;
	desc->next_ln_addr |= FSL_DMA_NLNDAR_NDEOSIE | FSL_DMA_NLNDAR_EOLND;
	desc->count = len;
	if (0x02 != (destid & 0x0F))
		desc->dst_attr |= FSL_DMA_DATR_NLWR;

#ifdef DEBUG
	printk(KERN_DEBUG "%s:submit %d dma_desc\n", DRV_NAME, dma->hw_wp - 1);
#endif
	dma->hw_wp++;
	ret = riodt_dma_xfer_queue(dma);

	return ret;
}

/**************************************************************************************************
**函数名：riodt_update_completed
**描述：
**输入：struct riodma *dma, int result
**输出：
**返回值：ret
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static void riodt_update_completed(struct riodma *dma, int result)
{
	int i;
	int slot;
	unsigned long flags;
	unsigned long ld_addr = 0;
	struct riodt_dma_status *status = NULL;

	spin_lock_irqsave(&dma->dev_lock, flags);
	ld_addr = dma->dma_regs->clndar & 0xFFFFFFF0;

	if (!ld_addr)
	{
		spin_unlock_irqrestore(&dma->dev_lock, flags);
		return;
	}

	i = (ld_addr - virt_to_phys(dma->dma_desc))/sizeof(struct fsl_dma_ld_hw);
	if (i >= RIODT_DMA_RING_SIZE)
	{
		spin_unlock_irqrestore(&dma->dev_lock, flags);
		printk("%s:irq: Offset Error\n", DRV_NAME);
		return;
	}
	/* dma busy */
	if (!dma_is_idle(dma))
	{		i -= 1;
		if (i < 0)
			i += RIODT_DMA_RING_SIZE;
	}

	slot = (i + 1) % RIODT_DMA_RING_SIZE;
	while ((dma->hw_ack % RIODT_DMA_RING_SIZE) != slot && (dma->hw_ack < dma->hw_rp))
	{
		status = &(dma->dma_status[dma->hw_ack % RIODT_DMA_RING_SIZE]);
		if ((dma->hw_ack % RIODT_DMA_RING_SIZE) == i && result < 0)
			status->result = DMA_ERR;
		else
			status->result = DMA_OK;

		dma->hw_ack++;

		/* if queue is full, return */
		if ((dma->dma_wp - dma->dma_rp) >= RIODT_DMA_RING_SIZE)
		{
			dma->dma_drop++;
			continue;
		}

		dma->dma_list[dma->dma_wp % RIODT_DMA_RING_SIZE].result = status->result;
		dma->dma_list[dma->dma_wp % RIODT_DMA_RING_SIZE].arg = status->arg;
		dma->dma_wp++;

	}

	spin_unlock_irqrestore(&dma->dev_lock, flags);

	wake_up_interruptible(&dma->dma_wait);
}

/**************************************************************************************************
**函数名：riodt_rx_clean
**描述：对发送寄存器的状态进行操作
**输入：
**输出：
**返回值：update
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_rx_clean(struct riodt *dev, int howmany)
{
	int i;
	void *data;
	int update = 0;
	int weight = 0;
	struct riomsg *msg_dev;

	i = dev->rx_slot;

	do
	{
		if (!dev->rx_skb[i])
			continue;

		if (!(data = rio_get_inb_message(dev->mport, RIODT_MAILBOX)))
			break;

		dev->rx_skb[i]->data = data;
#if 0
        struct msghead *msg_head;
        msg_head = (struct msghead *)data;
        /* nread or nwrite msg */
        if (msg_head->msg_size > RIODT_MAX_MSG_SIZE)
        {
            msg_dev = &dev->msg_dev[1];
#ifdef DEBUG
            printk(KERN_DEBUG "%s: mailbox 1 ", DRV_NAME);
#endif
		skb_put(dev->rx_skb[i], 28);
		update |= 0x2;
		}		else    /* msg */
		{
			msg_dev = &dev->msg_dev[0];
		#ifdef DEBUG			printk(KERN_DEBUG "%s: mailbox 0 ", DRV_NAME);
		#endif
			skb_put(dev->rx_skb[i], msg_head->msg_size + 16);
			update |= 0x1;		}
		#else			/* 閮芥斁鍒癿ailbox0 */
			msg_dev = &dev->msg_dev[0];
			skb_put(dev->rx_skb[i], 256);
			update |= 0x1;
		#endif

		if ((msg_dev->rx_wp - msg_dev->rx_rp) >= RIODT_TX_RING_SIZE)
		{               
			skb_trim(dev->rx_skb[i], 0);            
			rio_add_inb_buffer(dev->mport, RIODT_MAILBOX, dev->rx_skb[i]->data);
			msg_dev->rx_drop++;
			printk(KERN_INFO "%s:message list full\n", DRV_NAME);			continue;
		}

		msg_dev->rx_list[msg_dev->rx_wp++ % RIODT_TX_RING_SIZE] = dev->rx_skb[i];
		/* add new message to list */
		update |= 0x4;
		/* alloc new message, add to msg unit */
		dev->rx_skb[i] = dev_alloc_skb(RIO_MAX_MSG_SIZE);
		if (!dev->rx_skb[i])
		{
			printk(KERN_ERR "%s:alloc message error\n", DRV_NAME);
			break;
		}

		rio_add_inb_buffer(dev->mport, RIODT_MAILBOX, dev->rx_skb[i]->data);

		#ifdef DEBUG
			printk(KERN_DEBUG "enqueue msg rp %d, wp %d\n", msg_dev->rx_rp, msg_dev->rx_wp);
		#endif
	} while ((i = (i + 1) % RIODT_TX_RING_SIZE) != dev->rx_slot && ++weight < howmany);
	dev->rx_slot = i;
	return update;
}

/**************************************************************************************************
**函数名：riodt_channel_irq
**描述：判断DMA的中断状态
**输入：int irq, void *data
**输出：
**返回值：IRQ_HANDLED
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static irqreturn_t riodt_channel_irq(int irq, void *data)
{
	struct riodma *dma = (struct riodma *)data;
	int update = 0;
	int xfer_q = 0;
	u32 stat;

	stat = dma->dma_regs->sr;
	dma->dma_regs->sr = stat;    

#ifdef DEBUG
	printk(KERN_DEBUG "%s:irq: irq = %d: stat = 0x%x\n", DRV_NAME, irq, stat);
#endif

	stat &= ~(FSL_DMA_SR_CB | FSL_DMA_SR_CH);//判断是否有中断到来
	if (!stat)
	{
		return IRQ_NONE;
	}

	if (stat & FSL_DMA_SR_TE)
	{
#ifdef DEBUG
		printk(KERN_DEBUG "%s:irq: Transfer Error\n", DRV_NAME);
#endif
		stat &= ~FSL_DMA_SR_TE;
		update = -1;
	}

	if (stat & FSL_DMA_SR_PE)
	{    
#ifdef DEBUG
		printk(KERN_DEBUG "%s:irq: Programming Error\n", DRV_NAME);
#endif
		/* update dma result, and continue the next transfer */
		stat &= ~FSL_DMA_SR_PE;
		xfer_q = 1;
		update = -1;
	}

	if (stat & FSL_DMA_SR_EOSI) 
	{
#ifdef DEBUG
		printk(KERN_DEBUG "%s:irq: End-of-segments INT\n", DRV_NAME);		
		printk(KERN_DEBUG "%s:irq: clndar 0x%x, nlndar 0x%x\n", DRV_NAME,dma->dma_regs->clndar, dma->dma_regs->nlndar0);
#endif
		stat &= ~FSL_DMA_SR_EOSI;
		update = 1;
		xfer_q = 1;
	}

	if (stat & FSL_DMA_SR_EOLNI)
	{
#ifdef DEBUG		
	printk(KERN_DEBUG "%s:irq: End-of-link INT\n", DRV_NAME);
#endif
		stat &= ~FSL_DMA_SR_EOLNI;
	}
	if (stat & FSL_DMA_SR_EOCDI)
	{
#ifdef DEBUG
		printk(KERN_DEBUG "%s:irq: End-of-Chain link INT\n", DRV_NAME);
#endif 
		stat &= ~FSL_DMA_SR_EOCDI;
	}
#ifndef MODIFY_LAW		/*配置atmu1 maintenance寄存器*/
	out_be32(&dma->out_atmu_regs->rowar,0x80077017); 
#endif
	if (update)		
		riodt_update_completed(dma, update);

	if (xfer_q)
		riodt_dma_xfer_queue(dma);

#ifdef DEBUG
	if (stat)
	{
		printk(KERN_DEBUG "%s:irq:unhandled sr 0x%02x\n", DRV_NAME, stat);
	}
#endif

	return IRQ_HANDLED;
}

static void dbell_tasklet_handler(unsigned int arg)
{
	//fsm_printf("[SRIO]IOCCMD_SRIOtoADP_RECV\n");
	//fsm_do_ioctrl(STRM_TO_MAC, 0xEF, NULL, 0);    //20141111 0x11 need to be modified
	//fsm_schedule_self(0, _TEST_SRIO_IRQ);
	//__fsm_tm_ev_add(0,3,0xEF,NULL,0,0,NULL);
}

/******************************************************************************************************************************
**函数名：riodt_dbell_event
**描述：门铃中断处理函数
**输入：struct rio_mport *mport, void *dev_id, u16 sid, u16 tid, u16 info
**输出：
**返回值：
**创建者：demo
**创建日期：2014/01/01
********************************************************************************************************************************/
static void riodt_dbell_event(struct rio_mport *mport, void *dev_id, u16 sid, u16 tid, u16 info)
{
	struct riodt *dev = dev_id;
	struct riodbell *dbell_dev = &dev->dbell_dev;
	printk("Doorbell is coming...\n");
	count[i++]=sendcount;
	sendcount=0;
	if(db_cnt > 0)
	{
		subframenum = 5;
		sysframenum = (db_cnt*10000 - 1)%1024;
	}

	if(db_cnt == 0)
	{
		udelay(5);
		hrtimer_start(&timer1, kt1, HRTIMER_MODE_REL);
	}
	else
	{
		udelay(5);
		hrtimer_cancel(&timer1);
		udelay(5);
		hrtimer_start(&timer1, kt1, HRTIMER_MODE_REL);
	}
	db_cnt ++;
	
	//tasklet_init(&dbell_tasklet, dbell_tasklet_handler, 0);
	//tasklet_schedule(&dbell_tasklet);

	wake_up_interruptible(&dbell_dev->dbell_wait);  
}


/**************************************************************************************************
**函数名：riodt_inb_msg_event
**描述：inbound消息中断处理函数
**输入：
**输出：
**返回值：
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static void riodt_inb_msg_event(struct rio_mport *mport, void *dev_id, int mbox, int slot)
{
	int wakeup = 0;
	struct riodt *dev = dev_id;
	#ifdef DEBUG
		printk(KERN_DEBUG "%s: inbound message event, mbox %d slot %d\n",DRV_NAME, mbox, slot);
	#endif

	spin_lock(&dev->lock);

	wakeup = riodt_rx_clean(dev, 1);
	spin_unlock(&dev->lock);
	if ((wakeup & 0x5) == 0x5)
	{
		wake_up_interruptible(&dev->msg_dev[0].rx_wait);
	}

	if ((wakeup & 0x6) == 0x6)
	{
		wake_up_interruptible(&dev->msg_dev[1].rx_wait);
	}

}

/**************************************************************************************************
**函数名：riodt_outb_msg_event
**描述：outbound消息中断处理函数
**输入：
**输出：
**返回值：
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static void riodt_outb_msg_event(struct rio_mport *mport, void *dev_id, int mbox, int slot)
{
	struct riodt *dev = dev_id;

	spin_lock(&dev->lock);

	#ifdef DEBUG
		printk(KERN_DEBUG "%s: outbound message event, mbox %d slot %d\n",DRV_NAME, mbox, slot);
	#endif

	while (dev->tx_cnt && (dev->ack_slot != slot)) 
	{
		++dev->ack_slot;
		dev->ack_slot &= (RIODT_RX_RING_SIZE - 1);
		dev->tx_cnt--;
	}

	spin_unlock(&dev->lock);
}


/**************************************************************************************************
**函数名：riodt_dma
**描述：DMA发送函数
**输入：struct riodma *dma, u16 destid, u64 data, unsigned int len, u64 addr, int dir
**输出：
**返回值：ret
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_dma(struct riodma *dma, u16 destid, u64 data, unsigned int len, u64 addr, int dir)
{
	int ret = 0;
	u64 dst = 0;
	u64 src = 0;

#ifdef DEBUG
	printk(KERN_DEBUG "%s:riodt_dma: data %llx, addr %llx, len 0x%x\n", DRV_NAME, data, addr, len);
#endif

	if (dma->mode != DMA_DIRECT)
	{
		printk("%s:dma 0x%x is not initlization in DIRECT mode\n", DRV_NAME, (u32)dma);
		return -EINVAL;
	}

	if (len > dma->size)
		len = dma->size;

	mutex_lock(&dma->lock); 
	riodt_outatmu_set(dma->out_atmu_regs, addr, len, destid);

	/* write data to addr */
	if (dir == DMA_TO_DEVICE)
	{
		/* copy data from user to dma->mm */
		ret = copy_from_user(dma->mm_virt, (void *)((u32)data), len);
		if (ret)
		{
			ret = -EFAULT;
			goto out;
		}

		src = dma->mm_phys;
		dst = dma->rio_phys + (addr & (dma->size - 1));
	}
	else if (dir == DMA_FROM_DEVICE)	
		{
		src = dma->rio_phys + (addr & (dma->size - 1));
		dst = dma->mm_phys;
	}
	else
	{		
		printk(KERN_INFO "%s:riodt_dma: direction error\n", DRV_NAME);
	}

#ifdef DEBUG
	printk(KERN_DEBUG "%s:riodt_dma: dma 0x%x, dst 0x%llx, src 0x%llx, len 0x%x\n",DRV_NAME, (u32)dma, dst, src, len);
#endif

	ret = riodt_dma_tx_sync(dma, destid, dst, src, len);
	if (ret != 0)
	{
		ret = -EIO;
		goto out;
	}

	if (dir == DMA_FROM_DEVICE)
	{
		ret = copy_to_user((void *)((u32)data), dma->mm_virt, len);
		if (ret)
		{
			ret = -EFAULT;
			goto out;
		}
	}
	out:
		mutex_unlock(&dma->lock); 

	return ret; 
}

/**************************************************************************************************
**函数名：riodt_ndma
**描述：DMA发送函数
**输入：
**输出：
**返回值：ret
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_ndma(struct riodma *dma, u16 destid, u64 data, unsigned int len, u64 addr, int dir)
{
	int ret = 0;
	unsigned int size;
	#ifdef DEBUG 
	unsigned int e = 0;
	unsigned int s = gettb();
	#endif

	if (!len)
		return -EINVAL;

	while (((addr & (dma->size - 1)) + len) > dma->size)
	{
		size = dma->size - (addr & (dma->size - 1));
		ret = riodt_dma(dma, destid, data, size, addr, dir);		if (ret)
			return ret;
		data += size;
		addr += size;
		len -= size;
	}

	ret = riodt_dma(dma, destid, data, len, addr, dir);

	#ifdef DEBUG 
		e = gettb();
		printk(KERN_DEBUG "dma: e - s = 0x%x - 0x%x = 0x%x\n\n",e, s, e - s);
	#endif	
	return ret;
}

/**************************************************************************************************
**函数名：riodt_async
**描述：异步发送函数
**输入：
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_async(struct riodma *dma, u32 *result, u32 *arg, struct file *filp)
{
	mutex_lock(&dma->dma_lock);

	while(dma->dma_wp == dma->dma_rp)
	{
		mutex_unlock(&dma->dma_lock);
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
		if (wait_event_interruptible(dma->dma_wait, dma->dma_wp != dma->dma_rp))
			return -ERESTARTSYS;

		mutex_lock(&dma->dma_lock);
	}	*result = dma->dma_list[dma->dma_rp % RIODT_DMA_RING_SIZE].result;
	*arg = (u32)(dma->dma_list[dma->dma_rp % RIODT_DMA_RING_SIZE].arg);
	dma->dma_rp++;
	#ifdef DEBUG
		printk(KERN_DEBUG "%s:riodt_async result = %d, arg = %d\n", DRV_NAME, *result, *arg);
	#endif

	mutex_unlock(&dma->dma_lock);

	return 0;
}

/**************************************************************************************************
**函数名：riodt_map_write
**描述：nwrite 函数底层实现
**输入：struct riodma *nwrite, u16 destid, u64 data, unsigned int len, u64 addr, void *arg
**输出：
**返回值：ret
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_map_write(struct riodma *nwrite, u16 destid, u64 addr, unsigned int len, u64 data, void *arg)
{
	int ret = 0;
	//printk("riodt_map_write...\n");
	#if 0
		if (!len || (addr + len) > nwrite->size)
			return -EINVAL;
	#else
	if ( !len || ((addr&(nwrite->size-1)) + len) > nwrite->size )
		return -EINVAL;
	#endif

	if (nwrite->mode != DMA_CHAIN)
	{
		printk(KERN_ERR "%s:dma 0x%x is not initlization in chain mode\n", DRV_NAME, (u32)nwrite);
		return -EINVAL;	
	}

	mutex_lock(&nwrite->lock);
#ifndef MODIFY_LAW
	out_be32(&nwrite->out_atmu_regs->rowar,0x80044017); 
	out_be32(&nwrite->out_atmu_regs->rowtar, (destid << 22 | (u32)(addr >> 12)));
#endif
	addr = addr & (RIODT_NWRITE_WIN_SIZE - 1);
	addr += nwrite->rio_phys;

	ret = riodt_dma_tx_submit(nwrite, destid, addr, data, len, arg);

	mutex_unlock(&nwrite->lock);

	return ret; 
}

/**************************************************************************************************
**函数名：riodt_map_read
**描述：nread 函数
**输入：
**输出：
**返回值：ret
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_map_read(struct riodma *nread, u16 destid, u64 data, unsigned int len, u64 addr, void *arg)
{
	int ret = 0;
	#if 0
		if (!len || (addr + len) > nread->size)
			return -EINVAL;
	#else
	if ( !len || ((addr&(nread->size-1)) + len) > nread->size )		return -EINVAL;
	#endif
	if (nread->mode != DMA_CHAIN)
	{
		printk(KERN_ERR "%s:dma 0x%x is not initlization in chain mode\n", DRV_NAME, (u32)nread);
		return -EINVAL;
	}
	mutex_lock(&nread->lock);
	#ifndef MODIFY_LAW
		out_be32(&nread->out_atmu_regs->rowar,0x80044017); 
		out_be32(&nread->out_atmu_regs->rowtar, (destid << 22 | (u32)(addr >> 12)));
	#endif	addr = addr & (RIODT_NREAD_WIN_SIZE - 1);	addr += nread->rio_phys;
	ret = riodt_dma_tx_submit(nread, destid, data, addr, len, arg);
	mutex_unlock(&nread->lock);

	return ret; 
}

/**************************************************************************************************
**函数名：riodt_send_dbell
**描述：门铃发送函数
**输入：struct riodt *dev, u16 destid, u16 data
**输出：
**返回值：ret
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_send_dbell(struct riodt *dev, u16 destid, u16 data)
{
	int ret;
	ret = rio_mport_send_doorbell(dev->mport, destid, data);
	return ret;
}

void send_dbell(u16 sub)
{
	riodt_send_dbell(&g_riodt, 0x20, (sysframenum*10+sub));
}

/**************************************************************************************************
**函数名：riodt_recv_dbell
**描述：门铃接收函数
**输入：struct riodt *dev, u32 *sid, u32 *tid, u32 *data, struct file *filp
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_recv_dbell(struct riodt *dev, u32 *sid, u32 *tid, u32 *data)//, struct file *filp)
{
	struct riodbell *dbell_dev = &dev->dbell_dev;
	mutex_lock(&dbell_dev->lock);

	while (dbell_dev->dbell_wp == dbell_dev->dbell_rp)
	{
		mutex_unlock(&dbell_dev->lock);
#ifdef DEBUG
	printk(KERN_DEBUG "\"%s\" riodt_rx_dbell: going to sleep\n", current->comm);
#endif
		if (wait_event_interruptible(dbell_dev->dbell_wait, dbell_dev->dbell_wp != dbell_dev->dbell_rp))
			return -ERESTARTSYS;

		mutex_lock(&dbell_dev->lock);
	}
	*sid = dbell_dev->dbell_list[dbell_dev->dbell_rp % RIODT_DBELL_RING_SIZE].sid;
	*tid = dbell_dev->dbell_list[dbell_dev->dbell_rp % RIODT_DBELL_RING_SIZE].tid;
	*data = dbell_dev->dbell_list[dbell_dev->dbell_rp % RIODT_DBELL_RING_SIZE].info;

	dbell_dev->dbell_rp++;

	mutex_unlock(&dbell_dev->lock);

	return 0;
}

/**************************************************************************************************
**函数名：riodt_atmu_config
**描述：atmu寄存器配置
**输入：struct riodt *dev, int n, u32 rowtar, u32 rowtear, u32 rowbar, u32 rowar, u32 rows1r, u32 rows2r, u32 rows3r
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_atmu_config(struct riodt *dev, int n, u32 rowtar, u32 rowtear, u32 rowbar, u32 rowar, u32 rows1r, u32 rows2r, u32 rows3r)
{	
	struct rio_atmu_regs *regs = NULL;

	if (n >= RIODT_OUT_ATMU_MAX)
	{
		printk(KERN_ERR "%s:riodt_atmu_config:invalid index %d\n", DRV_NAME, n);
		return -EINVAL;
	}

	regs = dev->out_atmu_regs[n];
#ifdef DEBUG
	printk(KERN_DEBUG "%s:riodt_atmu_config:regs 0x%x rowtar 0x%x, rowtear 0x%x, rowbar 0x%x, rowar 0x%x\n", DRV_NAME, (u32)regs, rowtar, rowtear, rowbar, rowar);
#endif
	regs->rowtar = rowtar;
	regs->rowtear = rowtear;
	regs->rowbar = rowbar;
	regs->rowar = rowar;
	if (rowar & 0x00C00000)
	{		
		regs->rows1r = rows1r;
		regs->rows2r = rows2r;
		regs->rows3r = rows3r;
	}
	return 0;	
}

/**************************************************************************************************
**函数名：riodt_dma_channel_init
**描述：DMA信道初始化
**输入：struct riodma *dma
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_dma_channel_init(struct riodma *dma)
{
	int rc;
	int irq = -1;

	init_waitqueue_head(&dma->dma_wait);
	dma->hw_rp = 0;
	dma->hw_wp = 0;
	dma->hw_ack = 0;
	dma->hw_drop = 0;

	mutex_init(&dma->lock);
	mutex_init(&dma->dma_lock);
	spin_lock_init(&dma->dev_lock);
	memset((void *)(&dma->dma_list), 0, sizeof(struct riodt_dma_info) * RIODT_DMA_RING_SIZE); 
	memset((void *)(&dma->dma_status), 0, sizeof(struct riodt_dma_status) * RIODT_DMA_RING_SIZE); 

	/* nread dma channel regs init */    
	dma->dma_regs->mr = 0;
	dma->dma_regs->satr = 0;
	dma->dma_regs->datr = 0;

	dma->dma_regs->sr = 0xFFFFFFFFU;

	if (dma->mode == DMA_CHAIN)		
		dma->dma_regs->mr |= ((FSL_DMA_MR_BWC_CHAIN << FSL_DMA_MR_BWC_SHIFT) & FSL_DMA_MR_BWC_MASK) | \
								FSL_DMA_MR_EIE | FSL_DMA_MR_EOSIE | FSL_DMA_MR_CDSM;	else if (dma->mode == DMA_DIRECT)
		dma->dma_regs->mr |= ((FSL_DMA_MR_BWC_DIRECT << FSL_DMA_MR_BWC_SHIFT) & FSL_DMA_MR_BWC_MASK) | \
								FSL_DMA_MR_CTM | FSL_DMA_MR_SRW;
	dma->dma_regs->satr |= FSL_DMA_SATR_SREADTYPE_SNOOP_READ;
	dma->dma_regs->datr |= FSL_DMA_DATR_DWRITETYPE_SNOOP_WRITE;

	if (dma->irq && dma->mode == DMA_CHAIN)
	{		
		irq = dma->irq;
		dma->irq = irq_create_mapping(0, irq);
		if (dma->irq < 0)
		{			
			printk(KERN_ERR "%s:irq_create_mapping %d error\n", DRV_NAME, irq);
			return -EINVAL;
		}

		rc = request_irq(dma->irq, riodt_channel_irq, 0/*IRQF_SHARED*IRQF_DISABLED*/, "fsldma-chan", dma);
		if (rc)
		{
			printk(KERN_ERR "%s:request_irq %d error\n", DRV_NAME, irq);
			return -EBUSY;
		}
	}

	if (dma->dma_desc != NULL && dma->mode == DMA_CHAIN)
	{	
		int i;
		for (i = 0; i < RIODT_DMA_RING_SIZE; i++)
		{			
			dma->dma_status[i].dma_desc = dma->dma_desc + i;
			dma->dma_desc[i].next_ln_ex_addr = 0;			
			if ( i == (RIODT_DMA_RING_SIZE - 1))
			{
				dma->dma_desc[i].next_ln_addr = virt_to_phys((void *)dma->dma_desc) | FSL_DMA_NLNDAR_EOLND;
			}
			else
			{
				dma->dma_desc[i].next_ln_addr = virt_to_phys((void *)(dma->dma_desc + i + 1)) | FSL_DMA_NLNDAR_EOLND;
			}
		}
	}

#ifdef DEBUG	
	printk(KERN_DEBUG "%s:dma %x dma desc base 0x%x, size %d, regs base 0x%x, irq %d\n", DRV_NAME,(u32)dma,(u32)dma->dma_desc,RIODT_DMA_RING_SIZE,(u32)dma->dma_regs,irq);
#endif        
	return 0;
}

/**************************************************************************************************
**函数名：riodt_dma_init
**描述：DMA初始化
**输入：struct riodt *dev
**输出：
**返回值：rc
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_dma_init(struct riodt *dev)
{
	int rc = 0;
	struct rio_priv *priv = dev->mport->priv;

	struct riodma *nread = &(dev->dma_dev[0]);
	struct riodma *nwrite = &(dev->dma_dev[1]);
	struct riodma *direct = &(dev->dma_dev[2]);

	void *dma_base_addr = ioremap(FSL_DMA_BASE_ADDR, PAGE_SIZE);

	if (!dma_base_addr)
	{
		printk(KERN_ERR "%s:unable to map dma regs\n", DRV_NAME);
		return -ENOMEM;
	}

	nread->dma_desc = (struct fsl_dma_ld_hw *)dma_alloc_coherent(priv->dev, sizeof(struct fsl_dma_ld_hw) * (RIODT_DMA_RING_SIZE * 2 + 1),&nread->phy_desc,GFP_KERNEL);	if (!nread->dma_desc)
	{
		printk(KERN_ERR "%s:unable to allocate dma descriptor\n", DRV_NAME);
		rc = -ENOMEM;
		goto err;
	}

#ifdef DEBUG
	printk(KERN_DEBUG "nread->dma_desc 0x%x, nread->phy_desc 0x%llx\n", (u32)(nread->dma_desc), nread->phy_desc);
#endif
	nread->dma_desc = (struct fsl_dma_ld_hw *)round_up(((u32)(nread->dma_desc)), sizeof(struct fsl_dma_ld_hw));
	nread->phy_desc = round_up(nread->phy_desc, sizeof(struct fsl_dma_ld_hw));

	memset((void *)(nread->dma_desc), 0, sizeof(struct fsl_dma_ld_hw) * RIODT_DMA_RING_SIZE * 2);
	nread->irq = RIODT_NREAD_IRQ;
	nread->dma_regs = (struct fsldma_chan_regs *)((u32)dma_base_addr + 0x100);

	nwrite->dma_desc = (struct fsl_dma_ld_hw *)nread->dma_desc + RIODT_DMA_RING_SIZE;
	nwrite->irq = RIODT_NWRITE_IRQ;
	nwrite->dma_regs = (struct fsldma_chan_regs *)((u32)dma_base_addr + 0x100 + FSL_DMA_CHAN_LEN);

	direct->dma_desc = NULL;
	direct->irq = 0;
	direct->dma_regs = (struct fsldma_chan_regs *)((u32)dma_base_addr + 0x100 + FSL_DMA_CHAN_LEN * 2);

	rc = riodt_dma_channel_init(nread);
	if (rc < 0)
	{
		printk(KERN_ERR "%s:riodt_dma_init:nread dma channel initialize fail\n", DRV_NAME);
		goto err1;	
	}	
	rc = riodt_dma_channel_init(nwrite);	
	if (rc < 0)
	{
		printk(KERN_ERR "%s:riodt_dma_init:nread dma channel initialize fail\n", DRV_NAME);
		goto err1;
	}	
	rc = riodt_dma_channel_init(direct);	
	if (rc < 0)
	{
		printk(KERN_ERR "%s:riodt_dma_init:nread dma channel initialize fail\n", DRV_NAME);
		goto err1;	
	}	

	return rc;

	err1:
		dma_free_coherent(priv->dev, sizeof(struct fsl_dma_ld_hw) * (RIODT_DMA_RING_SIZE * 2 + 1),nread->dma_desc, nread->phy_desc);
	err:
		iounmap(dma_base_addr);
	return rc;
}

/**************************************************************************************************
**函数名：riodt_atmu_setup
**描述：ATMU寄存器设置
**输入：struct riodma *dma, struct device *dev
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_atmu_setup(struct riodma *dma, struct device *dev)
{
	if (dma->size != 0 && DMA_DIRECT == dma->mode)
	{
		dma->mm_virt = (void *)__get_free_pages(GFP_KERNEL,__ilog2_u64(dma->size / PAGE_SIZE));

		if (!dma->mm_virt)
		{
			printk(KERN_ERR "%s:dma 0x%x unable allocate nread dma buffer\n", DRV_NAME, (u32)dma);
			return -ENOMEM;		
		}

		dma->mm_phys = dma_map_single(dev, dma->mm_virt, (u32)RIODT_NREAD_WIN_SIZE, DMA_BIDIRECTIONAL);
	}
	if (dma->out_atmu_regs)
	{
		out_be32(&dma->out_atmu_regs->rowbar, (dma->rio_phys >> 12)); 
		out_be32(&dma->out_atmu_regs->rowar, 0x80044000 | (__ilog2_u64(dma->size) -1)); /*4M*/
	}

	return 0;
}

/**************************************************************************************************
**函数名：riodt_atmu_release
**描述：释放ATMU寄存器设置
**输入：struct riodma *dma, struct device *dev
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_atmu_release(struct riodma *dma, struct device *dev)
{
	if (!dma->mm_phys)
		dma_unmap_single(dev, dma->mm_phys, dma->size, DMA_BIDIRECTIONAL);

	if (!dma->mm_virt)
		free_pages((unsigned long)dma->mm_virt, __ilog2_u64(dma->size / PAGE_SIZE));
	return 0;
}


/**************************************************************************************************
**函数名：riodt_rx_msg
**描述：消息接收函数
**输入：
**输出：
**返回值：
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_rx_msg(struct riodt *dev, int mbox, void *data, unsigned int len, struct file *filp)
{
	struct sk_buff *skb = NULL;
	struct riomsg *msg_dev = NULL;

	if (mbox > 1 || mbox < 0)
	{		return -EINVAL;
	}

	msg_dev = &dev->msg_dev[mbox];

	mutex_lock(&msg_dev->lock);
	while ( msg_dev->rx_wp == msg_dev->rx_rp)
	{
		mutex_unlock(&msg_dev->lock);
	#if 0
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
	#else
		return -EAGAIN;
	#endif
	#ifdef DEBUG
		printk(KERN_DEBUG "\"%s\" riodt_rx_msg: going to sleep\n", current->comm);
	#endif
		if (wait_event_interruptible(msg_dev->rx_wait, msg_dev->rx_wp != msg_dev->rx_rp))
			return -ERESTARTSYS;
	#ifdef DEBUG
		printk(KERN_DEBUG "\"%s\" riodt_rx_msg: going to wakeup\n", current->comm);
	#endif
		mutex_lock(&msg_dev->lock);
	}

	skb = msg_dev->rx_list[msg_dev->rx_rp % RIODT_TX_RING_SIZE];

	if (len > skb->len)
		len = skb->len;

	#if 0
		if (copy_to_user(data, skb->data, len))
	{
		mutex_unlock(&msg_dev->lock);
		return -EFAULT;
	}
	#else	memcpy(data,skb->data,256);
	#endif
	msg_dev->rx_rp++;

	#ifdef DEBUG
		printk(KERN_DEBUG "%s: mailbox %d dequeue msg rp %d, wp %d, len %d\n", DRV_NAME, mbox, msg_dev->rx_rp, msg_dev->rx_wp, len);	
	#endif
	kfree_skb(skb);
	mutex_unlock(&msg_dev->lock);

	#if 1
		return len;
	#else
		return 0;
	#endif
}

/**************************************************************************************************
**函数名：riodt_queue_tx_msg
**描述：消息发送队列
**输入：
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_queue_tx_msg(struct riodt *dev, struct rio_dev *rdev, int mbox, void *data, unsigned int len)
{
	rio_add_outb_message(dev->mport, rdev, mbox, data, len);
	#ifdef DEBUG
		printk(KERN_DEBUG "%s: queued data %8.8x len %8.8x mbox %d\n", DRV_NAME,(u32) data, len, mbox);
	#endif

	return 0;
}

/**************************************************************************************************
**函数名：riodt_rx_fill
**描述：将发送的数据放入发送队列中
**输入：
**输出：
**返回值：
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static void riodt_rx_fill(struct riodt *dev, int end)
{
	int i;

	i = dev->rx_slot;
	do 
	{
		dev->rx_skb[i] = dev_alloc_skb(RIO_MAX_MSG_SIZE);

		if (!dev->rx_skb[i])
			break;

		rio_add_inb_buffer(dev->mport, RIODT_MAILBOX, dev->rx_skb[i]->data);
	} while ((i = (i + 1) % RIODT_TX_RING_SIZE) != end);

	dev->rx_slot = i;
}

/**************************************************************************************************
**函数名：riodt_atmu_init
**描述：初始化ATMU寄存器设置
**输入：struct riodt *dev
**输出：
**返回值：rc
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_atmu_init(struct riodt *dev)
{
	int rc = 0;
	int i;        
	struct rio_priv *priv = dev->mport->priv;
	struct riodma *nread = &(dev->dma_dev[0]);
	struct riodma *nwrite = &(dev->dma_dev[1]);
	struct riodma *direct = &(dev->dma_dev[2]);
	/* init nread outbound atmu */
	memset ((void *)&(dev->dma_dev[0]), 0, sizeof(struct riodma) * 3);
#ifdef MODIFY_LAW
	direct->rio_phys = dev->mport->iores.start + RIODT_WIN_START_ADDR;
	direct->size = RIODT_DIRECT_WIN_SIZE;
	direct->out_atmu_regs = priv->atmu_regs + 2;
	direct->mode = DMA_DIRECT;

	rc = riodt_atmu_setup(direct, priv->dev);
	if (rc < 0)
	{
		printk(KERN_ERR "%s: riodt setup direct atmu fail, rc=%d\n", DRV_NAME, rc);
		return rc;
	}
	nread->rio_phys = dev->mport->iores.start + RIODT_NREAD_WIN_SIZE; //direct->rio_phys + RIODT_DIRECT_WIN_SIZE;
	nread->size = RIODT_NREAD_WIN_SIZE;
	nread->out_atmu_regs = priv->atmu_regs + 3;
	nread->mode = DMA_CHAIN;
	rc = riodt_atmu_setup(nread, priv->dev);
	if (rc < 0)
	{		
		printk(KERN_ERR "%s: riodt setup nread atmu fail, rc=%d\n", DRV_NAME, rc);
		return rc;
	}

	nwrite->rio_phys = nread->rio_phys + RIODT_NREAD_WIN_SIZE;	nwrite->size = RIODT_NWRITE_WIN_SIZE;
	nwrite->out_atmu_regs = priv->atmu_regs + 4;
	nwrite->mode = DMA_CHAIN;

	rc = riodt_atmu_setup(nwrite, priv->dev);
	if (rc < 0)
	{
		printk(KERN_ERR "%s: riodt setup nwrite atmu fail, rc=%d\n", DRV_NAME, rc);
		return rc;
	}
#else
	direct->rio_phys = dev->mport->iores.start;
	direct->size = RIODT_DIRECT_WIN_SIZE;
	direct->out_atmu_regs = priv->atmu_regs + 1;
	direct->mode = DMA_DIRECT;
	nwrite->rio_phys = dev->mport->iores.start;
	nwrite->size = RIODT_NWRITE_WIN_SIZE;
	nwrite->out_atmu_regs = priv->atmu_regs + 1;
	nwrite->mode = DMA_CHAIN;
#endif
	/* init inbound atmu */
	dev->in_atmu_regs = (struct rio_inatmu_regs *)((u32)(priv->atmu_regs) + 0x160);

	/* map 4G DDR memory */
	out_be32(&dev->in_atmu_regs->riwtar, 0);
	out_be32(&dev->in_atmu_regs->riwbar, 0);
	out_be32(&dev->in_atmu_regs->riwar, 0x80f5501f);

	/* init outbound atmu */
	for (i=0;i<RIODT_OUT_ATMU_MAX;i++)
	{
		dev->out_atmu_regs[i] = priv->atmu_regs + 5 + i;
	}

#ifdef DEBUG
	printk(KERN_INFO "%s:nread atmu 0x%p, nwrite atmu 0x%p, direct atmu 0x%p, inbound atmu 0x%p\n",DRV_NAME, dev->dma_dev[0].out_atmu_regs,dev->dma_dev[1].out_atmu_regs,				dev->dma_dev[2].out_atmu_regs,dev->in_atmu_regs);
#endif

	return rc;
}

extern int memread(unsigned long readaddr,unsigned int length)
{
	unsigned int i;
//	printk("%s\n",__func__);
//	printk("%#x,length = %d\n",readaddr,length);
	for(i = 1;i <= length;i ++)
	{
		printk("%02x ",*((unsigned char *)(readaddr-AMC719_RESVMEM_BASEADDR+mapaddr + i - 1)));
		if ( i%16 == 0 )
		{
			printk("\n");
		}
	}
	printk("\n");
	return 0;
}

int memwrite(unsigned long writeaddr,unsigned int data,unsigned int length)
{
	printk("%s\n",__func__);
	memset((void *)(writeaddr-AMC719_RESVMEM_BASEADDR+mapaddr),(unsigned char)data,length);
	return 0;
}

/**************************************************************************************************
**函数名：riodt_msg_init
**描述：消息设备初始化
**输入：
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_msg_init(struct riodt *dev)
{
	int i = 0;
	struct riomsg *msg_dev = NULL;

	for (i = 0; i < 2; i++)
	{
		msg_dev = &(dev->msg_dev[i]);

		memset ((void *)&msg_dev->rx_list[0], 0, sizeof(struct sk_buff *) *RIODT_TX_RING_SIZE);

		mutex_init(&msg_dev->lock);

		init_waitqueue_head(&msg_dev->rx_wait);

		msg_dev->rx_rp = 0;
		msg_dev->rx_wp = 0;
		msg_dev->rx_drop = 0;	}
	return 0;
}

/**************************************************************************************************
**函数名：riodt_dbell_init
**描述：门铃设备初始化
**输入：struct riodt *dev
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
static int riodt_dbell_init(struct riodt *dev)
{
	struct riodbell *dbell_dev = &(dev->dbell_dev);
	memset((void *)(dbell_dev->dbell_list), 0, sizeof(struct riodt_dbell_info) * RIODT_DBELL_RING_SIZE);

	mutex_init(&dbell_dev->lock);
	init_waitqueue_head(&dbell_dev->dbell_wait);
	dbell_dev->dbell_wp = 0;
	dbell_dev->dbell_rp = 0;
	dbell_dev->dbell_drop = 0;

	return 0;
}

/**************************************************************************************************
**函数名：riodt_mmap
**描述：内存映射函数
**输入：struct file *filp,struct vm_area_struct *vma
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
int riodt_mmap()
{
	int i;
	mapaddr = ioremap(AMC719_RESVMEM_BASEADDR,AMC719_RESVMEM_LENGTH);
	
	for(i=0;i<QUEUE_MAX_NUM; i++)
	{
		if(i==2)
			VirAddrStart[i] = mapaddr+0x500 + 0*QUEUE_OFFSET*0x4000;
		else if(i==7)
			VirAddrStart[i] = mapaddr+0x500 + 1*QUEUE_OFFSET*0x4000;
		else
			VirAddrStart[i] = mapaddr;
	}
	VirAddrStart[2] = mapaddr+0x500 + 0*QUEUE_OFFSET*0x4000;
	VirAddrStart[7] = mapaddr+0x500 + 1*QUEUE_OFFSET*0x4000;					
	printk("RioDt test memory range %#x~%#x(phy addr)\n",AMC719_RESVMEM_BASEADDR,AMC719_RESVMEM_BASEADDR+AMC719_RESVMEM_LENGTH);
	return 0;
}

static struct file_operations riodt_fops = {
	.owner = THIS_MODULE,
};
/**************************************************************************************************
**函数名：riodt_setup_cdev
**描述：设备初始化函数
**输入：
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
extern int riodt_setup_cdev(void)
{
	int rc = 0;
	dev_t devno;
	u16 device_id;
	struct rio_priv *priv;
	struct rio_mport *mport = NULL;

	volatile u32 *preg;
	u32 i;

	memset(&g_riodt,0,sizeof(g_riodt));
	list_for_each_entry(mport, &rio_mports, node)
	{
		if (mport->host_deviceid == AMC719_HOST_DEVICE_ID )
		g_riodt.mport = mport;
	}

	if ( NULL == g_riodt.mport )
	{
		printk("RioDt:can't find serial rapidIO port,Module Init Fail!!!\n");
		return -ENODEV;	
	}
    
	device_id = mport->host_deviceid;
	
	
	if (major)
	{
		devno = MKDEV(major, minor);
		rc = register_chrdev_region(devno, 1, DRV_NAME);
	}
	else
	{		rc = alloc_chrdev_region(&devno, minor, 1, DRV_NAME);
		major = MAJOR(devno);	}

	if(rc < 0)
	{
		printk(KERN_ERR "riodt: can't get major %d\n", major);
		goto out;
	}
	
	cdev_init(&g_riodt.cdev, &riodt_fops);	g_riodt.cdev.owner = THIS_MODULE;	g_riodt.cdev.ops = &riodt_fops;
	rc = cdev_add(&g_riodt.cdev, devno, 1);
	if (rc)
	{
		printk(KERN_ERR "riodt: cdev_add error, ret = %d\n", rc);
		goto out;
	}
	spin_lock_init(&g_riodt.lock);
	spin_lock_init(&g_riodt.tx_lock);

	rio_class = class_create(THIS_MODULE, "riodt");
	if (IS_ERR(rio_class))
	{
		rc = PTR_ERR(rio_class);
		printk(KERN_ERR "riodt: class_create error, ret = %d\n", rc);
		goto out;
	}

	device_create(rio_class, NULL, devno, NULL, "riodt"); 
	
#ifdef MODIFY_LAW
		/* set LAWs,SRIO port0 use LAW[5] */
	preg = ioremap(CCSR_LAW_BASEADDR,0x400);
	preg[4*5] = (SRIO_PORT0_MEM_BASEADDR >> 32) & 0xf;	preg[4*5+1] = (u32)(SRIO_PORT0_MEM_BASEADDR & (u64)0xffffffff);
	preg[4*5+2] = (0x1<<31) | (0x8<<20) | 0x21;
	for ( i = 20 ; i < 23 ; i++ )
	{
		printk("law[%d][%d] %#x\n",i/4,i%4,preg[i]);	
	}
#endif
	printk(KERN_INFO "%s: %s %s Version %s, Id %04x\n","RapidIO",DRV_NAME,DRV_DESC,DRV_VERSION,device_id);

	priv = &(g_riodt.mport->priv);//dev->mport->priv;

	printk(KERN_INFO "%s:open\n", DRV_NAME);

	rc = riodt_msg_init(&g_riodt);
	if (rc < 0)
	{
		goto out;
	}
	
	rc = riodt_dbell_init(&g_riodt);
	if (rc < 0)
	{
		goto out;
	}
	
	rc = rio_request_inb_dbell(g_riodt.mport, &g_riodt, RIODT_DOORBELL_MIN, RIODT_DOORBELL_MAX, riodt_dbell_event);
	if (rc < 0)
	{
		printk("request inb_dbell fail,ret %#x\n",rc);
		goto out;	
	}
	
	rc = riodt_atmu_init(&g_riodt);
	if (rc < 0)
	{		
		goto out;
	}

	rc = riodt_dma_init(&g_riodt);
	if (rc < 0)
	{
		goto out;	
	}
	
	//路由信息
	printk("In setupdev\n");	
	seci = kmalloc(sizeof(struct srio_enum_cnt_info),GFP_KERNEL);
	if(seci == NULL)
		printk("allocate seci failed!\n");
	memset(seci,0,sizeof(struct srio_enum_cnt_info)); 
	rio_enum_init(g_riodt.mport,seci);
	memset(&sesi,0,sizeof(struct srio_enum_stat_info));
	if ( NULL != seci )
	{
		printk("In if\n");
		rio_put_enum_info(seci);
		rio_show_enum_info(seci,&sesi);
	}
	
	for(i=0; i<QUEUE_MAX_NUM ;i++)
	{
		InitQueue(&UnionQueue[i]);
	}
	
	//进行内存映射
	printk("In mmap\n");
	riodt_mmap();
	
	printk("hrtimer1 init\n");
	rio_hrtimer1_init(NULL, 0x54);
	/*
	buffer = kmalloc(data_size, GFP_ATOMIC);
	if (buffer == NULL)
	{
		return -ENOMEM;
	}
	memset(buffer, 0, data_size);
	*/
	sourcepusch = kmalloc(5120,GFP_KERNEL);
	//memcpy(sourcepusch,vxx_tb_buffer,sizeof(vxx_tb_buffer));
	memset(sourcepusch,0xef,2000);

	out:
		return rc;
}

/**************************************************************************************************
**函数名：riodt_exit
**描述：设备退出函数
**输入：
**输出：
**返回值：0
**创建者：demo
**创建日期：2014/01/01
***************************************************************************************************/
extern void riodt_exit(void)
{
	dev_t devno;
	int i;
	
	struct riodma *nread = &(g_riodt.dma_dev[0]);
	struct riodma *nwrite = &(g_riodt.dma_dev[1]);
	struct rio_priv *priv = g_riodt.mport->priv;
	printk(KERN_INFO "%s: close\n", DRV_NAME);
	free_irq(nread->irq,nread);
	free_irq(nwrite->irq,nwrite);

	riodt_atmu_release(&(g_riodt.dma_dev[0]), priv->dev);
	riodt_atmu_release(&(g_riodt.dma_dev[1]), priv->dev);
	riodt_atmu_release(&(g_riodt.dma_dev[2]), priv->dev);

	rio_release_inb_dbell(g_riodt.mport, RIODT_DOORBELL_MIN,RIODT_DOORBELL_MAX);
	rio_release_inb_mbox(g_riodt.mport, RIODT_MAILBOX);
	rio_release_outb_mbox(g_riodt.mport, RIODT_MAILBOX);
		for (i = 0; i < RIODT_TX_RING_SIZE; i++)
		kfree_skb(g_riodt.rx_skb[i]);
	
	for (i = 0; i < 2; i++)
	{		while(g_riodt.msg_dev[i].rx_wp != g_riodt.msg_dev[i].rx_rp)
		{			kfree_skb(g_riodt.msg_dev[i].rx_list[g_riodt.msg_dev[i].rx_rp % RIODT_TX_RING_SIZE]);
			g_riodt.msg_dev[i].rx_rp++;
		}
	}
	
	for(i=0; i<QUEUE_MAX_NUM ;i++)
	{
		DestroyQueue(&UnionQueue[i]);
	}
	
	rio_hrtimer1_stop();
	
	return; 
}

void rio_show_enum_info(struct srio_enum_cnt_info *seci,struct srio_enum_stat_info *sesi)
{
	int j = 0,slot = 0,tmp = 0;
	unsigned long i = 0,next_destid = 0;
	if ( NULL == seci || NULL == sesi )
		return;
	printk("\n----------------------"TITLE" begin show enum info----------------------\n");
	printk("\n"TITLE" enum found [%u] end points,[%u] switchs,[%u] empty switchs,cost [%u]ms\n",seci->ep_cnts,seci->switch_cnts,seci->emp_sw_cnts,seci->time_cnt_ms); 
	for ( i=0 ; i<VT861_SLOT_NUM ; i++ )
	{
		if ( 1 == seci->err_pass_slot[i] )
			printk(TITLE" enum error pass slot %u\n",i);
	}
	next_destid = seci->ep_cnts + seci->emp_sw_cnts;
	printk("\n----------------------------\n");
	printk("|      SRIO ROUTE CFG      |\n");
	printk("----------------------------\n");
	printk("|  slot  | destid |  port  |\n");
	printk("----------------------------\n");
	for ( j = 0; j< VT861_SLOT_NUM; j++ )
	{
		for ( i = 0; i < next_destid && i < VT861_LTEA_SRIO_DEV_NUM; i++ )
		{
			if ( seci->srt[j][i].destid == 0 && seci->srt[j][i].port == 0 )
				continue;
			printk("   %-6u  0x%-5x   %-7u\n",j,seci->srt[j][i].destid,seci->srt[j][i].port);	  
		}
	}
	printk("------------end-------------\n");
	printk("\n------------------------------------------------------------------------------\n");
	printk("|                       "TITLE" [%2d] active devices:                   |\n",seci->ep_cnts);
	printk("------------------------------------------------------------------------------\n");
	printk("| AMC |slot|CfgNum|FoundNum| ID |flag| ID |flag| ID |flag| ID |flag| ID |flag|\n");
	printk("------------------------------------------------------------------------------\n");
	for ( i=0 ; i < next_destid && i < VT861_LTEA_SRIO_DEV_NUM; i++ )
	{
		/* get slot num */
		tmp = (seci->destid_table[i] & 0xf0) >> 4;
		if ( (0 == i || tmp != slot) && (tmp != 0xf) )
		{
			slot = tmp;	
			if ( i != 0 )
			{
				printk("\n");
			}
			printk("%4u%6u%6u%7u   ",(slot+1),slot,sesi->slot_cfg_dev_num[slot],sesi->slot_found_dev_cnt[slot]);
		}
		else if ( 0xf == tmp )
		{
			/* tmp = 0xf,empty switch */
			tmp = seci->destid_table[i] & 0xf;
			if ( tmp != slot || 0 == i )
			{
				slot = tmp;	
				if ( i != 0 )
				{
					printk("\n");
				}
				printk("%4u%6u%6u%7u   ",(slot+1),slot,sesi->slot_cfg_dev_num[slot],sesi->slot_found_dev_cnt[slot]);
			}
		}
		printk("  0x%-2x%4u",seci->destid_table[i],seci->err_pass_port[i]);
	}
	printk("\n------------------------------------------------------------------------------\n");
	printk("| Specification:flag=1,link Error;flag=0,link Ok.                            |");
	printk("\n---------------------------------end------------------------------------------\n");
	printk("\n------------------------"TITLE" end show enum info----------------------\n");
	return;
}

extern void send_data(u32 dest_addr, u32 data_len, u32 data_addr)
{
	riodt_map_write(&(g_riodt.dma_dev[1]), 0x00, dest_addr, data_len, data_addr, (void *)0);
}

//extern int recieve_data(u32 checkaddr,u16* pkt_count);
extern int recieve_data(u32 checkaddr,u16* pkt_count)
{
	//struct sk_buff *skb;
	void* readaddr = mapaddr + (checkaddr - 0xfc100000);
	if ((*(u32*)readaddr == 1)&&((*(u16*)(readaddr+cache_size-2))!=0))
	{	
		*((u32 *)readaddr) = 0;
		*pkt_count=(*(u16*)(readaddr+cache_size-2));
		*((u16 *)(readaddr+cache_size-2))=0;
		return 1;	
	}
	else
		return 0;
		
}
extern void* rtn_mmap(){
	return mapaddr;
}

/*
int fsm_get_curtime(void)
{
	ktime_t	ktime;
	struct timeval cur_time;
	u32 ctm;
	ktime = ktime_get();
	cur_time = ktime_to_timeval(ktime);
	ctm = cur_time.tv_sec * 1000000 + cur_time.tv_usec;

	return ctm;
}
*/
/**************************************************************************************************
**函数名：do_delay_log
**描述：记录每次发送数据所用时间
**输入：
**输出：
**返回值：
**创建者：智前烨
**创建日期：2014/07/01
***************************************************************************************************/
void do_delay_log(unsigned int delay)
{
	if(delay_log_p < DELAY_LOG_COUNT)
	{
//		int current_time = fsm_get_curtime();
//		int delay = current_time - prev_time;
		delay_log_buf[delay_log_p] = delay;
		log_wp[delay_log_p] = g_riodt.dma_dev[1].hw_wp;
		log_ack[delay_log_p] = g_riodt.dma_dev[1].hw_ack;
		delay_log_p++;
//		prev_time = current_time;
	}
}

/**************************************************************************************************
**函数名：display_delay_log
**描述：显示每次定时器中数据发送的时间长度，发送ACK与确认发送ACK
**输入：
**输出：printk("log %d: %d wp-%u ack-%u", i, delay_log_buf[i],log_wp[i],log_ack[i])
**返回值：
**创建者：智前烨
**创建日期：2014/07/01
***************************************************************************************************/
void display_delay_log(void)
{
	int i;
	for(i = 0; i < DELAY_LOG_COUNT; i++)
	{
		if(i%5 == 0)
			printk("\n");
		printk("log %d: %d wp-%u ack-%u", i, delay_log_buf[i],log_wp[i],log_ack[i]);
	}
	printk("\n");
}

//type1:0x83096500  type3:0x830aa500
static enum hrtimer_restart hrtimer_handler0(struct hrtimer *timer) 
{
	unsigned int prevtime,currenttime,usetime;
	u32 dest_addr = 0x83096500;
	unsigned int offset = 0x4000;
	static unsigned int downlinkcount = 0;
	//printk("hrtimer_handler0...\n");
	hrtimer_forward(timer, timer->base->get_time(), kt1);
	
	prevtime = fsm_get_curtime();
	
	if(subframenum == 2 || subframenum == 7)
	{
		ElemType CurPos;
		spin_lock(&UnionQueue[subframenum].my_lock);
		if(Pop(&UnionQueue[subframenum], &CurPos))
		{
			
			dest_addr = dest_addr + offset * buffnum;
			buffnum++;
			if(dest_addr >= timer1_para.dest + offset * 5)
			{
				dest_addr = timer1_para.dest; 
				buffnum = 1;
			}
			//printk("Current Pop Pos is %d\n",CurPos);
			//printk("Poped QueueSize is %d\n",UnionQueue.QueueSize);
			//printk("Current NextData is %d\n",UnionQueue.NextData);
			//printk("dest_addr = %#llx\n",	dest_addr);
			//printk("Sending type1...\n");
			riodt_map_write(&(g_riodt.dma_dev[1]), 0x54, dest_addr,16384, (AddrStart[subframenum]+CurPos*0x4000), (void *)0);
			//printk("Sending type3...\n");
			send_ueul_type3(&g_riodt,0x54,0x830aa500,256,0xfc100000,(void *)timer1_para.arg);
		}
		spin_unlock(&UnionQueue[subframenum].my_lock);
		sendcount++;
	}
	else 
	{
		downlinkcount++;
	}
	
	subframenum++;
	currenttime = fsm_get_curtime();
	usetime = currenttime - prevtime;
	do_delay_log(usetime);  

	if(subframenum == 10)
	{
		subframenum = 0;
		sysframenum ++;
		if(sysframenum == 1024)
			sysframenum = 0;
	}
	return HRTIMER_RESTART;
}

static enum hrtimer_restart hrtimer_handler2(struct hrtimer *timer) 
{
	unsigned int prevtime,currenttime,usetime;
	u64 dest_addr = timer1_para.dest;
	unsigned int offset = 0x4000;
	static unsigned int downlinkcount = 0;
	printk("hrtimer_handler2...\n");
	hrtimer_forward(timer, timer->base->get_time(), kt1);

	prevtime = fsm_get_curtime();

	if(subframenum == 2 || subframenum == 7)
	{
//		printk("It is a commen subframe\n");
		dest_addr = dest_addr + offset * buffnum;
		buffnum ++;
		if(dest_addr >= timer1_para.dest + offset * 5)
		{
			dest_addr = timer1_para.dest;
			buffnum = 1;
		}
		//printk("dest_addr = %#llx\n",	dest_addr);
		send_ueul_type1(&g_riodt,timer1_para.destid,dest_addr,timer1_para.len,timer1_para.local,(void *)timer1_para.arg);
		udelay(100);
		send_ueul_type3(&g_riodt,timer1_para.destid,0x8308c480,256,0xfc200000,(void *)timer1_para.arg);
		sendcount ++;
		totalcount++;
	}
	else 
	{
		downlinkcount ++;
//		printk("It is a special subframe downlinkcount = %u\n",downlinkcount);
	}

	subframenum ++;	
//	printk("subframenum = %u\n",subframenum);
	currenttime = fsm_get_curtime();
	usetime = currenttime - prevtime;
	do_delay_log(usetime);  //记录发送所用时间
	if(subframenum == 10)
	{
		subframenum = 0;
		sysframenum ++;
		if(sysframenum == 1024)
			sysframenum = 0;
	}
	if(sendcount == timer1_para.sendtimes)
	{
		
		printk("dest_addr = %#llx\nsubframenum = %u\nsysframenum = %u\ndownlinkcount = %u\nsendcount = %u\n",dest_addr,subframenum,sysframenum,downlinkcount,sendcount);
		printk("total count = %u\n", totalcount);
		sendcount = 0;
		return HRTIMER_NORESTART;
	}
	else
		return HRTIMER_RESTART;
}

static enum hrtimer_restart hrtimer_handler1(struct hrtimer *timer) 
{
	u32 dest_addr = timer1_para.dest;
	unsigned int offset = 0x4000;
	static unsigned int downlinkcount = 0;
	printk("hrtimer_handler1...\n");
	hrtimer_forward(timer, timer->base->get_time(), kt1);

	if(subframenum == 2 && subframenum == 7)
	{
//		printk("It is a commen subframe\n");
		dest_addr = dest_addr + offset * buffnum;
		buffnum ++;
		if(dest_addr >= timer1_para.dest + offset * 5)
		{
			dest_addr = timer1_para.dest;
			buffnum = 1;
		}
		enbul_type2_send(&g_riodt,timer1_para.destid,dest_addr,timer1_para.len,timer1_para.local,(void *)timer1_para.arg);
/*		printk("timer1_para.dest = %#llx,timer1_para.local = %#llx\n",timer1_para.dest, timer1_para.local);
		printk("dest_addr = %#x\n",dest_addr);*/
		sendcount ++;
	}
	else 
	{
		downlinkcount ++;
	}

	subframenum ++;	
	if(subframenum == 10)
	{
		subframenum = 0;
		sysframenum ++;
		if(sysframenum == 1024)
			sysframenum = 0;
	}

	return HRTIMER_RESTART;
}

/**************************************************************************************************
**函数名：rio_hrtimer_start
**描述：定时器启动函数。对定时器实现初始化，启动定时器。可以改变定时器的周期（默认值为0.5ms）。
**输入：struct riodt *dev, unsigned int destid
**输出：printk("\n-------- timer send start ---------\n");
**返回值：0
**创建者：智前烨
**创建日期：2014/07/01
**-------------------------------------------------------------------------------------------------
**修改：张晓雨
**修改日期：2014/09/03
***************************************************************************************************/
static int rio_hrtimer1_start(struct riodt *dev, unsigned int destid)  //配置定时器
{
	kt1 = ktime_set(timer1_para.seconds, timer1_para.nseconds); /*  sec,  nsec */
	hrtimer_init(&timer1, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hrtimer_start(&timer1, kt1, HRTIMER_MODE_REL);
	if(timer1_para.sendtimes == 0)
		timer1.function = hrtimer_handler0;
	else if(timer1_para.sendtimes == 0xff)
		timer1.function = hrtimer_handler1;
	else
		timer1.function = hrtimer_handler2;
	printk("timer1_para.s = %u,timer1_para.ns = %u\n",timer1_para.seconds,timer1_para.nseconds);
	printk("\n-------- timer send start ---------\n");
	return 0;
}

static int rio_hrtimer1_init(struct riodt *dev, unsigned int destid)
{
	timer1_para.port = 0;
	timer1_para.destid = 0x54;
	timer1_para.local = 0xfc100500;
	timer1_para.dest = 0x83096500;
	timer1_para.len = 0x4000;
	timer1_para.seconds = 0;
	timer1_para.nseconds = 1000000;
	timer1_para.sendtimes =0x0;
	timer1_para.arg = 0;
	kt1 = ktime_set(timer1_para.seconds, timer1_para.nseconds); /*  sec,  nsec */
	hrtimer_init(&timer1, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	//hrtimer_start(&timer1, kt1, HRTIMER_MODE_REL);
	//dest_addr = dest_addr + buffnum;
	db_cnt=0;
	buffnum = 0;
	subframenum = 5;
	sysframenum = 0;
	if(timer1_para.sendtimes == 0)
		timer1.function = hrtimer_handler0;
	else if(timer1_para.sendtimes == 0xff)
		timer1.function = hrtimer_handler1;
	else
		timer1.function = hrtimer_handler2;
	printk("timer1_para.s = %u,timer1_para.ns = %u\n",timer1_para.seconds,timer1_para.nseconds);
	printk("\n-------- timer send init ---------\n");
	return 0;
}
/**************************************************************************************************
**函数名：rio_hrtimer_stop
**描述：定时器停止函数
**输入：
**输出：printk("\n-------- timer send stop-------\n");
**返回值：0
**创建者：智前烨
**创建日期：2014/07/01
***************************************************************************************************/
static void rio_hrtimer1_stop(void)  //停止定时器
{
	hrtimer_cancel(&timer1);
	printk("send complished sendcount = %u\n",sendcount);
	sendcount = 0;
	printk("subframenum = %u\nsysframenum = %u\n",subframenum,sysframenum);	
	printk("-------- timer1 send stop ----------\n");
	int j;
	for(j=0; j<1000; j++)
		printk("%u:%u\n",j,count[j]);
	return;
}

static enum hrtimer_restart hrtimer_handler3(struct hrtimer *timer) 
{
	void *read_addr = mapaddr + (timer2_para.local - 0xfc100000);

	hrtimer_forward(timer, timer->base->get_time(), kt2);

	spin_lock_irq(&hrtimer2_lock);
	if(*((u32 *)read_addr) != 0)
	{
		memcpy(checkaddr,mapaddr + 0x800,1500);
		*((u32 *)read_addr) = 0;
		spin_unlock_irq(&hrtimer2_lock);
		printk("I am the slower timer! the flag is NEW DATA!\n");
//		ueul_type2_read(checkaddr);
	}
	else
		spin_unlock_irq(&hrtimer2_lock);

	return HRTIMER_RESTART;
}

/**************************************************************************************************
**函数名：rio_hrtimer2_start
**描述：定时器启动函数。对定时器实现初始化，启动定时器。可以改变定时器的周期（默认值为0.5ms）。
**输入：struct riodt *dev, unsigned int destid
**输出：printk("\n-------- timer send start ---------\n");
**返回值：0
**创建者：张晓雨
**创建日期：2014/10/08
***************************************************************************************************/
static int rio_hrtimer2_start(struct riodt *dev, unsigned int destid)  //配置定时器
{
	kt2 = ktime_set(timer2_para.seconds, timer2_para.nseconds); /*  sec,  nsec */
	hrtimer_init(&timer2, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hrtimer_start(&timer2, kt2, HRTIMER_MODE_REL);
	timer2.function = hrtimer_handler3;
	printk("timer2_para.s = %u,timer2_para.ns = %u\n",timer2_para.seconds,timer2_para.nseconds);
	printk("\n-------- timer2 read flag start ---------\n");
	return 0;
}

/**************************************************************************************************
**函数名：rio_hrtimer2_stop
**描述：定时器停止函数
**输入：
**输出：printk("\n-------- timer send stop-------\n");
**返回值：0
**创建者：张晓雨
**创建日期：2014/10/08
***************************************************************************************************/
static void rio_hrtimer2_stop(void)  //停止定时器
{
	hrtimer_cancel(&timer2);	
	printk("\n-------- timer2 read flag stop ----------\n");
	return;
}

static void send_dsp_route_info(struct riodt *timer_dev)
{
	//struct rio_dma_para rdp1;
	SRIO_ROUTE_INFO route_info;
	/*
	rdp1.port = 0;
	rdp1.destid = 0x94;
	rdp1.local = 0xfc400500;
	rdp1.dest = 0x0c0ba100;
	rdp1.len = 16;
	rdp1.seconds = 0; 
	rdp1.nseconds = 0; 
	rdp1.sendtimes = 1; 
	rdp1.arg = 0;
	*/
	route_info.NewFlag = 1;
	route_info.AMC1_ = 0x0;
	route_info.AMC2_ = 0x20;
	route_info.DSP1_ = 0x74;
	route_info.DSP2_ = 0x76;
	route_info.FPGA1_ = 0x91;
	route_info.FPGA2_ = 0x92;
	
	memcpy(mapaddr + 0x300600, &route_info, sizeof(SRIO_ROUTE_INFO));
	//riodt_map_write(&(timer_dev->dma_dev[1]), timer_destid, timer_data, timer_len, timer_addr, timer_arg);
	riodt_map_write(&(timer_dev->dma_dev[1]), 0x54,0x83000400, 16, 0xfc400600, 0);
}

static void send_ueul_type1(struct riodt *timer_dev, u16 timer_destid, u64 timer_data, unsigned int timer_len, u64 timer_addr, void *timer_arg)
{	
	UEULPHYADPtoPHYType1 type1public;
	UE_UL_TYPE1_PUCCH_C type1pucchc;
	UE_UL_TYPE1_PUCCH_D type1pucchd;
	UE_UL_TYPE1_PUSCH_C type1puschc;
	UE_UL_TYPE1_PUSCH_D type1puschd;

	//PUBLIC_C
	type1public.GHead.NewFlag = 1;//u32
	type1public.GHead.SFN = sysframenum;//u16
	type1public.GHead.SubframeN = subframenum;//u16
	//printk("%u  ",type1public.GHead.SubframeN);
	type1public.UL_TYPE1_PUBLIC_C.PUSCHCOffset = sizeof(UEULPHYADPtoPHYType1) + sizeof(UE_UL_TYPE1_PUCCH_C) + sizeof(UE_UL_TYPE1_PUCCH_D);//u32
	type1public.UL_TYPE1_PUBLIC_C.PUSCHDOffset = sizeof(UEULPHYADPtoPHYType1) + sizeof(UE_UL_TYPE1_PUCCH_C) + sizeof(UE_UL_TYPE1_PUCCH_D) + sizeof(UE_UL_TYPE1_PUSCH_C);//u32
	memcpy(mapaddr + 0x100800,&type1public,sizeof(UEULPHYADPtoPHYType1));
	//PUCCH_C
	type1pucchc.RNTI = 61;//u16
	type1pucchc.UlStates = 0;//u16
	type1pucchc.UlChSel = 0;//u16
	if(sysframenum == 0 && subframenum == 0)
		type1pucchc.PGType = 0;//u16
	else
		type1pucchc.PGType = 2;//u16
	type1pucchc.NumofNP = 20;//u16
	type1pucchc.cqiInfoLen = 0;//u16
	type1pucchc.nPucchIndex = 0;//u16
	type1pucchc.deltaPUCCHshift = 0;//u16
	type1pucchc.betaPUCCH = 0;//u16
	type1pucchc.TA = 0;//u16
	type1pucchc.Subfn = subframenum;//u16
	type1pucchc.Isrs = 0;//u16
	type1pucchc.SRSDuration = 0;//u16
	type1pucchc.Bsrs = 0;//u16
	type1pucchc.Nra = 0;//u16
	type1pucchc.Ktc = 0;//u16
	type1pucchc.Bhop = 0;//u16
	type1pucchc.nRRC = 0;//u16
	type1pucchc.nSRScs = 0;//u16
	type1pucchc.betaSRS = 0;//u16	
	memcpy(mapaddr + 0x100800 + sizeof(UEULPHYADPtoPHYType1),&type1pucchc,sizeof(UE_UL_TYPE1_PUCCH_C));
	//PUCCH_D
	type1pucchd.RNTI = 61;//u16
	type1pucchd.UlChSel = 0;//u16
	type1pucchd.SR = 0;//u16
	type1pucchd.HARQ = 0;//u16
	type1pucchd.CQI = 0;//u16
	type1pucchd.padding = 0;//u16
	memcpy(mapaddr + 0x100800 + sizeof(UEULPHYADPtoPHYType1) + sizeof(UE_UL_TYPE1_PUCCH_C),&type1pucchd,sizeof(UE_UL_TYPE1_PUCCH_D));
	//PUSCH_C
	type1puschc.RNTI = 61;//u16
	type1puschc.UlStates = 0;//u16
	type1puschc.UlChSel = 000;//u16
	if(sysframenum == 0 && subframenum == 0)
		type1puschc.PGType = 0;//u16
	else
		type1puschc.PGType = 2;//u16
	type1puschc.NumofNP = 37;//u16
	type1puschc.PrbStart = 50;//u16
	type1puschc.NumPrb = 20;//u16
	type1puschc.PuschHopFlag = 0;//u16
	type1puschc.ULHop = 0;//u16
	type1puschc.puschHopOffset = 0;//u16
	type1puschc.Qm = 6;//u16
	type1puschc.rvIdx = 0;//u16
	type1puschc.dmrs2 = 0;//u16
	type1puschc.harqInfoLen = 0;//u16
	type1puschc.harqOffset = 0;//u16
	type1puschc.Nbundled = 1;//u16
	type1puschc.riInfoLen = 0;//u16
	type1puschc.riOffset = 0;//u16
	type1puschc.cqiInfoLen = 0;//u16
	type1puschc.cqiOffset = 0;//u16
	type1puschc.betaPUSCH = 0;//u16
	type1puschc.ndi = 0;//u16
	type1puschc.CurrentTxNB = 0;//u16
	type1puschc.Nsb = 0;//u16
	type1puschc.TA = 0;//u16
	type1puschc.Subfn = subframenum;//u16
	type1puschc.Isrs = 0;//u16
	type1puschc.SRSDuration = 0;//u16
	type1puschc.Bsrs = 0;//u16
	type1puschc.Nra = 0;//u16
	type1puschc.Ktc = 0;//u16
	type1puschc.Bhop = 0;//u16
	type1puschc.nRRC = 0;//u16
	type1puschc.nSRScs = 0;//u16
	type1puschc.betaSRS = 0;//u16
	type1puschc.padding = 0;//u16
	type1puschc.tbSize = 14688;//u32
	memcpy(mapaddr + 0x100800 + sizeof(UEULPHYADPtoPHYType1) + sizeof(UE_UL_TYPE1_PUCCH_C) + sizeof(UE_UL_TYPE1_PUCCH_D),&type1puschc,sizeof(UE_UL_TYPE1_PUSCH_C));
	//PUSCH_D
	type1puschd.RNTI = 68;//u16
	type1puschd.UlChSel = 000;//u16
	type1puschd.CQI = 0;//u16
	type1puschd.RI = 0;//u16
	type1puschd.HARQ_ACK = 0;//u32
	memcpy(mapaddr + 0x100800 + sizeof(UEULPHYADPtoPHYType1) + sizeof(UE_UL_TYPE1_PUCCH_C) + sizeof(UE_UL_TYPE1_PUCCH_D) + sizeof(UE_UL_TYPE1_PUSCH_C),&type1puschd,sizeof(UE_UL_TYPE1_PUSCH_D));
	//PUSCH_D SourcePUSCH
	memcpy(mapaddr + 0x100800 + sizeof(UEULPHYADPtoPHYType1) + sizeof(UE_UL_TYPE1_PUCCH_C) + sizeof(UE_UL_TYPE1_PUCCH_D) + sizeof(UE_UL_TYPE1_PUSCH_C) + sizeof(UE_UL_TYPE1_PUSCH_D),sourcepusch,((type1puschc.tbSize + 31)/32)*4);

	riodt_map_write(&(timer_dev->dma_dev[1]), timer_destid, timer_data, sizeof(UEULPHYADPtoPHYType1) + sizeof(UE_UL_TYPE1_PUCCH_C) + sizeof(UE_UL_TYPE1_PUCCH_D) + sizeof(UE_UL_TYPE1_PUSCH_C) + sizeof(UE_UL_TYPE1_PUSCH_D) + ((type1puschc.tbSize + 31)/32)*4, timer_addr, timer_arg);
}

static void send_ueul_type3(struct riodt *timer_dev, u16 timer_destid, u64 timer_data, unsigned int timer_len, u64 timer_addr, void *timer_arg)
{
	UEULPHYADPtoPHYType3 type3;
	type3.GHead.NewFlag = 1;//u32
	type3.GHead.SetFlag.CmdFlag = 1;//u32
	type3.UL_TYPE3_PUBLIC_C.PUSCH_PUCCHOffset = 0;//u32
	type3.UL_TYPE3_PUSCH_PUCCH_C.NumRbHo = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.puschDeltaSS = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.HoppingMode = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.GroupHopEn = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.SeqHopEn = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.DMRS1 = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.CpType = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.cellID = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.NumPrbBw = 100;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.SFDirection = 2;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.SpecSFcfg = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.UECategory = 4;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.TM = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.harqFeedbackMode = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.SrsSubframConfig = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.CSrs = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.SrsMaxUpPts = 0;//u16
	type3.UL_TYPE3_PUSCH_PUCCH_C.padding = 0;//u16
	memcpy(mapaddr, &type3,sizeof(UEULPHYADPtoPHYType3));

	riodt_map_write(&(timer_dev->dma_dev[1]), timer_destid, timer_data, sizeof(UEULPHYADPtoPHYType3), timer_addr, timer_arg);
}

static void enbul_type2_send(struct riodt *timer_dev, u16 timer_destid, u64 timer_data, unsigned int timer_len, u64 timer_addr, void *timer_arg)
{
	ENBULPHYADPtoPHYType2 type2head;
	ENB_UL_TYPE2_PUCCH_C type2pucchc;
	ENB_UL_TYPE2_PUSCH_C type2puschc;
	ENB_UL_TYPE2_PUSCH_D type2puschd;

	//PUBLIC_C
	type2head.GHead.NewFlag = 1;//u32
	type2head.GHead.SFN = sysframenum;//u16
	type2head.GHead.SubframeN = subframenum;//u16
	type2head.UL_TYPE2_PUBLIC_C.PUSCHOffset = sizeof(ENBULPHYADPtoPHYType2) + sizeof(ENB_UL_TYPE2_PUCCH_C);//u32
	printk("PUSCHOffset = %u\n",type2head.UL_TYPE2_PUBLIC_C.PUSCHOffset);
	type2head.UL_TYPE2_PUBLIC_C.PUCCHOffset = sizeof(ENBULPHYADPtoPHYType2);//u32
	printk("PUCCHOffset = %u\n",type2head.UL_TYPE2_PUBLIC_C.PUCCHOffset);
	memcpy(mapaddr + 0x200000,&type2head,sizeof(ENBULPHYADPtoPHYType2));
	//PUCCH_C
	type2pucchc.RNTI = 63;//u16
	type2pucchc.UlChSel = 000;//u16
	type2pucchc.HARQbitinfo = 0;//u16
	type2pucchc.SR = 0;//u16
	type2pucchc.CQI = 9;//u16
	type2pucchc.TA = 0;//u16
	type2pucchc.RAPID = 0;//u16
	type2pucchc.RARNTI = 0;//u16
	type2pucchc.RAmaskindex = 0;//u16
	type2pucchc.padding = 0;//u16
	memcpy(mapaddr + 0x200000 + sizeof(ENBULPHYADPtoPHYType2),&type2pucchc,sizeof(ENB_UL_TYPE2_PUCCH_C));
	//PUSCH_C
	type2puschc.RNTI = 63;//u16
	type2puschc.UlChSel = 000;//u16
	type2puschc.NumofNP = 10;//u16
	type2puschc.CRC = 000;//u16
	type2puschc.HARQbitinfo = 0;//u16
	type2puschc.CQI = 9;//u16
	type2puschc.RIbitinfo = 0;//u16
	type2puschc.TA = 0;//u16
	type2puschc.RAPID = 0;//u16
	type2puschc.RARNTI = 0;//u16
	type2puschc.RAmaskindex = 0;//u16
	type2puschc.padding = 0;//u16
	memcpy(mapaddr + 0x200000 + sizeof(ENBULPHYADPtoPHYType2) + sizeof(ENB_UL_TYPE2_PUCCH_C),&type2puschc,sizeof(ENB_UL_TYPE2_PUSCH_C));
	//PUSCH_D
	type2puschd.RNTI = 63;//u16
	type2puschd.UlChSel = 000;//u16
	type2puschd.datalen = 1908;//u32
	memcpy(mapaddr + 0x200000 + sizeof(ENBULPHYADPtoPHYType2) + sizeof(ENB_UL_TYPE2_PUCCH_C) + sizeof(ENB_UL_TYPE2_PUSCH_C),&type2puschd,sizeof(ENB_UL_TYPE2_PUSCH_D));
	//copy the pusch data
	memcpy(mapaddr + 0x200000 + sizeof(ENBULPHYADPtoPHYType2) + sizeof(ENB_UL_TYPE2_PUCCH_C) + sizeof(ENB_UL_TYPE2_PUSCH_C) + sizeof(ENB_UL_TYPE2_PUSCH_D),sourcepusch,type2puschd.datalen);

	riodt_map_write(&(timer_dev->dma_dev[1]), timer_destid, timer_data, sizeof(ENBULPHYADPtoPHYType2) + sizeof(ENB_UL_TYPE2_PUCCH_C) + sizeof(ENB_UL_TYPE2_PUSCH_C) + sizeof(ENB_UL_TYPE2_PUSCH_D) + type2puschd.datalen, timer_addr, timer_arg);
}


