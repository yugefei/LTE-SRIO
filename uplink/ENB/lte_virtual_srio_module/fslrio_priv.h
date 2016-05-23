#ifndef FSLRIO_PRIVATE_H
#define FSLRIO_PRIVATE_H

#define FSL_DMA_MR_CS		0x00000001
#define FSL_DMA_MR_CC		0x00000002
#define FSL_DMA_MR_CA		0x00000008
#define FSL_DMA_MR_EIE		0x00000040
#define FSL_DMA_MR_XFE		0x00000020
#define FSL_DMA_MR_EOLNIE	0x00000100
#define FSL_DMA_MR_EOLSIE	0x00000080
#define FSL_DMA_MR_EOSIE	0x00000200
#define FSL_DMA_MR_CDSM		0x00000010
#define FSL_DMA_MR_CTM		0x00000004
#define FSL_DMA_MR_EMP_EN	0x00200000
#define FSL_DMA_MR_EMS_EN	0x00040000
#define FSL_DMA_MR_DAHE		0x00002000
#define FSL_DMA_MR_SAHE		0x00001000
#define FSL_DMA_MR_SRW          0x00000400
/* Special MR definition for MPC8349 */
#define FSL_DMA_MR_EOTIE	0x00000080
#define FSL_DMA_MR_PRC_RM	0x00000800

#define FSL_DMA_SR_CH		0x00000020
#define FSL_DMA_SR_PE		0x00000010
#define FSL_DMA_SR_CB		0x00000004
#define FSL_DMA_SR_TE		0x00000080
#define FSL_DMA_SR_EOSI		0x00000002
#define FSL_DMA_SR_EOLSI	0x00000001
#define FSL_DMA_SR_EOCDI	0x00000001
#define FSL_DMA_SR_EOLNI	0x00000008

#define FSL_DMA_SATR_SBPATMU			0x20000000
#define FSL_DMA_SATR_STRANSINT_RIO		0x00c00000
#define FSL_DMA_SATR_SREADTYPE_SNOOP_READ	0x00050000
#define FSL_DMA_SATR_SREADTYPE_BP_IORH		0x00020000
#define FSL_DMA_SATR_SREADTYPE_BP_NREAD		0x00040000
#define FSL_DMA_SATR_SREADTYPE_BP_MREAD		0x00070000

#define FSL_DMA_DATR_NLWR                       0x40000000
#define FSL_DMA_DATR_DBPATMU			0x20000000
#define FSL_DMA_DATR_DTRANSINT_RIO		0x00c00000
#define FSL_DMA_DATR_DWRITETYPE_SNOOP_WRITE	0x00050000
#define FSL_DMA_DATR_DWRITETYPE_BP_FLUSH	0x00010000

#define FSL_DMA_NLNDAR_NDEOSIE    0x00000008
#define FSL_DMA_NLNDAR_EOLND        0x00000001
#define FSL_DMA_CLNDAR_EOSIE        0x00000008

#define FSL_DMA_MR_BWC_CHAIN  0xf
#define FSL_DMA_MR_BWC_DIRECT  0x9
#define FSL_DMA_MR_BWC_SHIFT    24
#define FSL_DMA_MR_BWC_MASK     0x0f000000

#define FSL_DMA_BASE_ADDR	(0x100000ULL + 0xffe000000ULL)
#define FSL_DMA_CHAN_LEN	0x80
#define DMA_CHECK_BUSY_TIMEOUT		1000000U
#define DMA_SET_CB_TIMEOUT		1000000U

#define DMA_STATE_CC_SHIFT 1
#define DMA_STATE_TE_SHIFT 6
#define DMA_STATE_CB_SHIFT 0
#define DMA_STATE_CS_SHIFT 3

#define DMA_IDLE_STATUS 0x00
#define DMA_OTHER_STATUS 0x0f

#define DMA_OK  0
#define DMA_ERR 1
#define DMA_USED 1
#define DMA_FREE 0

struct fsl_dma_ld_hw {
	volatile u32 src_attr;
	volatile u32 src_addr;
	volatile u32 dst_attr;
	volatile u32 dst_addr;
	volatile u32 next_ln_ex_addr;
	volatile u32 next_ln_addr;
	volatile u32 count;
	volatile u32 reserve;
} __attribute__((aligned(32)));

struct fsldma_chan_regs {
	volatile u32 mr;	/* 0x00 - Mode Register */
	volatile u32 sr;	/* 0x04 - Status Register */
	volatile u32 eclndar;	/* 0x08 - Current descriptor address register */
        volatile u32 clndar;
	volatile u32 satr;	/* 0x10 - Source Address Register */
	volatile u32 sar;	/* 0x14 - Source Address Register */
	volatile u32 datr;	/* 0x18 - Destination Address Register */
	volatile u32 dar;	/* 0x1c - Destination Address Register */
	volatile u32 bcr;	/* 0x20 - Byte Count Register */
	volatile u32 enlndar0;	/* 0x24 - Next Descriptor Address Register */
        volatile u32 nlndar0;
        volatile u32 res;
        volatile u32 eclsdar0;
        volatile u32 clsdar0;
        volatile u32 enlsdar0;
        volatile u32 nlsdar0;
        volatile u32 ssr0;
        volatile u32 dsr0;
};

#define RIO_MAX_TX_RING_SIZE	2048
#define RIO_MAX_RX_RING_SIZE	2048

struct rio_msg_regs {
	u32 omr;	/* 0xD_3000 - Outbound message 0 mode register */
	u32 osr;	/* 0xD_3004 - Outbound message 0 status register */
	u32 pad1;
	u32 odqdpar;	/* 0xD_300C - Outbound message 0 descriptor queue
			   dequeue pointer address register */
	u32 pad2;
	u32 osar;	/* 0xD_3014 - Outbound message 0 source address
			   register */
	u32 odpr;	/* 0xD_3018 - Outbound message 0 destination port
			   register */
	u32 odatr;	/* 0xD_301C - Outbound message 0 destination attributes
			   Register*/
	u32 odcr;	/* 0xD_3020 - Outbound message 0 double-word count
			   register */
	u32 pad3;
	u32 odqepar;	/* 0xD_3028 - Outbound message 0 descriptor queue
			   enqueue pointer address register */
	u32 pad4[13];
	u32 imr;	/* 0xD_3060 - Inbound message 0 mode register */
	u32 isr;	/* 0xD_3064 - Inbound message 0 status register */
	u32 pad5;
	u32 ifqdpar;	/* 0xD_306C - Inbound message 0 frame queue dequeue
			   pointer address register*/
	u32 pad6;
	u32 ifqepar;	/* 0xD_3074 - Inbound message 0 frame queue enqueue
			   pointer address register */
	u32 pad7[226];
	u32 odmr;	/* 0xD_3400 - Outbound doorbell mode register */
	u32 odsr;	/* 0xD_3404 - Outbound doorbell status register */
	u32 res0[4];
	u32 oddpr;	/* 0xD_3418 - Outbound doorbell destination port
			   register */
	u32 oddatr;	/* 0xD_341c - Outbound doorbell destination attributes
			   register */
	u32 res1[3];
	u32 odretcr;	/* 0xD_342C - Outbound doorbell retry error threshold
			   configuration register */
	u32 res2[12];
	u32 dmr;	/* 0xD_3460 - Inbound doorbell mode register */
	u32 dsr;	/* 0xD_3464 - Inbound doorbell status register */
	u32 pad8;
	u32 dqdpar;	/* 0xD_346C - Inbound doorbell queue dequeue Pointer
			   address register */
	u32 pad9;
	u32 dqepar;	/* 0xD_3474 - Inbound doorbell Queue enqueue pointer
			   address register */
	u32 pad10[26];
	u32 pwmr;	/* 0xD_34E0 - Inbound port-write mode register */
	u32 pwsr;	/* 0xD_34E4 - Inbound port-write status register */
	u32 pad11;
	u32 pwqbar;	/* 0xD_34EC - Inbound port-write queue base address
			   register */
};


struct rio_dbell_ring {
	void *virt;
	dma_addr_t phys;
};

struct rio_msg_tx_ring {
	void *virt;
	dma_addr_t phys;
	void *virt_buffer[RIO_MAX_TX_RING_SIZE];
	dma_addr_t phys_buffer[RIO_MAX_TX_RING_SIZE];
	int tx_slot;
	int size;
	void *dev_id;
};

struct rio_msg_rx_ring {
	void *virt;
	dma_addr_t phys;
	void *virt_buffer[RIO_MAX_RX_RING_SIZE];
	int rx_slot;
	int size;
	void *dev_id;
};

struct rio_atmu_regs {
	u32 rowtar;
	u32 rowtear;
	u32 rowbar;
	u32 pad2;
	u32 rowar;
	u32 rows1r;
	u32 rows2r;
	u32 rows3r;
};

struct rio_priv {
	struct device *dev;
	void __iomem *regs_win;
	struct rio_atmu_regs __iomem *atmu_regs;
	struct rio_atmu_regs __iomem *maint_atmu_regs;
	struct rio_atmu_regs __iomem *dbell_atmu_regs;
	void __iomem *dbell_win;
	void __iomem *maint_win;
	struct rio_msg_regs __iomem *msg_regs;
	struct rio_dbell_ring dbell_ring;
	struct rio_msg_tx_ring msg_tx_ring;
	struct rio_msg_rx_ring msg_rx_ring;
	int errirq;
	int bellirq;
	int txirq;
	int rxirq;
};
#endif
