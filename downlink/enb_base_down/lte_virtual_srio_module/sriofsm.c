/****************************************************************
** Filename:Sriofsm.c
** Copyright:uestc
** Descriptions:
** v1.0, 20140928, MaFang written
** --------------------------------------------------------------
** modification history:
** Modified by:
** Modified date:
** Descriptions:
**
****************************************************************/


#include <linux/if_ether.h>
#include <linux/interrupt.h>
#include <linux/jiffies.h>
#include "sriofsm.h"
#include "../lte_system.h"
#include "pkfmt.h"
#include <linux/string.h>
#include "queue.h"

//	??š°?¡Á?š¬??š²?DŠÌ?¡Á?š¬?
/**********20141013 mf modified ************************/
#define ST_INIT	0
#define ST_CFG	1
#define	ST_IDLE	2
#define ST_SEND	3
#define ST_RECV	4
#define ST_SEND_TYPE1_TO_SRIO		5
#define ST_RECV_TYPE2_FROM_SRIO	6
//#define ST_TEST	4	//2ašº??¡Á??š¬šª?š®TEST¡Á?š¬?¡ê?š®?š®š²?š®šº?MSG3¡€¡é?šªMSG4	modified by MF 20140715
/**********end modified ************************/


//	??š°???š€šªšºšº??2?¡À?šŠšª2ašº?š®?IOControl?š¹š¢?
#define IOCCMD_PSEND_RUN			0x01
#define IOCCMD_PSEND_STOP			0x02
#define IOCCMD_PSEND_INTERVAL	0x05 
#define IOCCMD_SAY_HELLO			0x04

//	??š°?UE2š€MAC2?????š€šªšºšº??2?ŠÌ?IOControl?š¹š¢?
#define IOCCMD_MACtoPHY_RNTI_Indicate			0x24      //¡€¡é?šªMSG3???¡ã MAC2????ašºšº??2?RNTI?ŠÌ
#define IOCCMD_MACtoPHY_Preamble_Indicate		0x25      //MSG1
#define IOCCMD_MACtoPHY_recv_sysinfo			0x26      //RRC???aMAC MAC???ašºšº??2??ašº??š®šº??ŠÌšª3???¡é
#define IOCCMD_MACtoPHY_stop_recv_sysinfo		0x27      //RRC???aMAC MAC???ašºšº??2?šª¡ê?1?š®šº??ŠÌšª3???¡é
#define IOCCMD_MACtoPHY_recv_paging				0x46      //RRC???aMAC MAC???ašºšº??2??ašº??š®šº??¡ão????¡é
/************20141013 mf modified**************/
#define IOCCMD_PHYtoMAC_RA_Req				0x03		//With data format S_RAinfo
#define IOCCMD_PHYtoMAC_TA					0x06
#define IOCCMD_PHYtoMAC_FRAME				0x07


/************end modify************************/
//	??š°?UE2š€??š€šªšºšº??2???MAC2?ŠÌ?IOControl?š¹š¢?
#define IOCCMD_Harq_feedback					0x18   //when MAC received this command from PHYadapter,MAC 
#define IOCCMD_PDCCHtoMAC_RandomAcc_Req		0x0C   //PDCCHšŠ? ???aMAC?ašº????š²?š®šš?
#define IOCCMD_PDCCHtoMAC_ULGRANT			0x0D   //PHY send a DCI of ul_grant to MAC 
#define IOCCMD_TEST_SEND_MSG3				0x51  //šº?ŠÌ?IOControloš®¡ê?¡€¡é?šªMSG3¡ê?2ašº??š¹š¢? modified by MF 20140715
#define IOCCMD_TEST_SEND_TO_ETH				0x52
#define IOCCMD_RRCtoPHY_Type1_Indicate      0x60
#define IOCCMD_SEND_MSG1						0x70
#define IOCCMD_SEND_ULDATA					0x71
#define IOCCMD_SEND_TA						0x72
#define IOCCMD_DLSCHEDULE						0x13
#define IOCCMD_RARDCI							0x14
#define IOCCMD_ULSCHEDULE						0x12
#define IOCCMD_SEND_MSG3						0x76
#define IOCCMD_SEND_SF						0x77
#define IOCCMD_SEND_TO_SRIO	0x4E
#define IOCCMD_READ_MEM		0x4F
#define IOCCMD_RA_COMPLETE	0x48
#define IOCCMD_RIODT_STOP	0x4D
#define IOCCMD_LOST_PKT_COUNT	0x4C
#define IOCCMD_RECV_INTERVAL_ADD 0x66
#define IOCCMD_RECV_INTERVAL_MINUS 0x67
#define IOCCMD_PRINT_PKT_FROM_UE 0x68
#define IOCCMD_STOP_TIMER 0x888
#define IOCCMD_SEND_INFO           0x889
#define MemoryStart				0xfc10000
#define MemorySize					10240
static struct tasklet_struct recv_tasklet;
static void recv_tasklet_handler(char *ptr);
static void init_enter(void);
static void send_packet_period(void);
static void srio_sv_init(void);	
static void srio_close(void);
static void packet_send_to_eth(void);
static void packet_send_to_upperlayer(void);
static void idle_exit(void);
static void idle_ioctl_handler(void);
void print_tran_info( const char *str);
static void cfg_ioctl_handler(void);
static void ioctldata();
static void test_send_to_eth(void);
static void test_send_msg1(void);
static void test_send_ta(void);
static void test_send_msg3(void);
static void test_send_sf(void);
static void test_send_uldata(void);
static void type1_pkt_assemble_test();
extern unsigned int GetFrameNo(void);// used for read FrameNo from 719
extern unsigned int GetsubFrameNo(void);//used for read sub Frame Number from 719

u32 createLongBsr(FSM_PKT *skb,u32 offset);
u32 createCRnti(FSM_PKT *skb,u32 offset);
u32 createHead(FSM_PKT *skb,u32 control_numb,u32 data_numb,char typ);
static void createmachead7bit(MAC_SDU_subhead_7bit *macsubhead,u8 lcid,u8 sdu_len,u8 continueflag);
static void msgFromCCCH(FSM_PKT* skb);
static void skbFromRlc(FSM_PKT* pkptr);
FSM_PKT* generatepkt(u16 rnti);

/*****************************end***************************************/

static void send_uldci_to_ue(void);
static void type1_send_to_srio(void);
static void type2_recv_from_srio(void);
static void read_mem(void);
extern int read_type2_mem();
extern void rio_hrtimer1_stop_wrapper(void);
extern void * mapaddr;
extern LinkQueue UnionQueue[QUEUE_MAX_NUM];
extern unsigned long long AddrStart[QUEUE_MAX_NUM];

u64 DataSource[5]={0x8ED8F08000000000,
				   0x8F00F08000000000,
				   0x8F28F08000000000,
				   0x8F50F08000000000,
				   0x8F78F08000000000};



volatile int export_frameNo;
volatile int export_subframeNo;
EXPORT_SYMBOL(export_frameNo);
EXPORT_SYMBOL(export_subframeNo);


extern unsigned long long VirAddrStart[QUEUE_MAX_NUM];
/*
 												{ 0xfc100800+0*QUEUE_OFFSET*0xfa0,
											       0xfc100800+1*QUEUE_OFFSET*0xfa0,
											       0xfc100800+2*QUEUE_OFFSET*0xfa0,
												   0xfc100800+3*QUEUE_OFFSET*0xfa0,
												   0xfc100800+4*QUEUE_OFFSET*0xfa0,
												   0xfc100800+5*QUEUE_OFFSET*0xfa0,
												   0xfc100800+6*QUEUE_OFFSET*0xfa0,
												   0xfc100800+7*QUEUE_OFFSET*0xfa0,
												   0xfc100800+8*QUEUE_OFFSET*0xfa0,
												   0xfc100800+9*QUEUE_OFFSET*0xfa0,
											    };
*/

extern void send_dsp_route_info_wrapper(void);

/********************************************************************************
** Function name: srio_main
** Description: ??š€šªšºšº??2?ŠÌ?¡Á?š¬??š²?¡Âo¡¥šºy
** Input:
** Output:
** Returns:
** Created by:
** Created Date:
** ------------------------------------------------------------------------------
** Modified by: MF
** Modified Date: 20141013
** Modefied Description: š¬šª?š®CFGš¬?š®?š®š²ŠÌšš?yRRCŠÌ?Type1????
********************************************************************************/

void srio_main(void)
{
	FSM_ENTER(srio_main);
	FSM_BLOCK_SWITCH
	{
		FSM_STATE_FORCED(ST_INIT, "INIT", srio_sv_init(), )
		{
			FSM_TRANSIT_FORCE(ST_IDLE,, "default", "", "INIT -> IDLE"); 
		}
		FSM_STATE_UNFORCED(ST_IDLE, "IDLE",,)		
		{
			FSM_COND_TEST_IN("IDLE")				
				FSM_TEST_COND(SRIO_PK_FROM_LOWER)				
				FSM_TEST_COND(SRIO_PK_FROM_UPPER)
				FSM_TEST_COND(SRIO_CLOSE)
				FSM_TEST_COND(PACKET_SEND_PERIOD)
				FSM_TEST_COND(TEST_SEND_SF_PERIOD)
				FSM_TEST_COND(TEST_SEND_TA_PERIOD)
				FSM_TEST_COND(TYPE2_RECV_FROM_SRIO)
			FSM_COND_TEST_OUT("IDLE")	
			FSM_TRANSIT_SWITCH			
			{	
				FSM_CASE_TRANSIT(0, ST_RECV, , "IDLE -> RECV")	//?????????????2?¡ê???????¡é			
				FSM_CASE_TRANSIT(1, ST_SEND, , "IDLE -> SEND") //?¡€?¡é?????????2?¡ê???????¡é
				FSM_CASE_TRANSIT(2, ST_INIT,idle_exit() , "IDLE -> INIT") //???????????o?????3??
				FSM_CASE_TRANSIT(3, ST_IDLE,send_packet_period(), "IDLE->IDLE")//???????¡À???¡€?????????¡€?¡é????
				FSM_CASE_TRANSIT(4, ST_IDLE, test_send_sf(), "IDLE->IDLE")//20140715 mf 
				FSM_CASE_TRANSIT(5, ST_IDLE, test_send_ta(), "IDLE->IDLE")//20140715 mf 
				FSM_CASE_TRANSIT(7, ST_RECV_TYPE2_FROM_SRIO, , "IDLE -> RECV_TYPE2_FROM_SRIO")
				FSM_CASE_DEFAULT(ST_IDLE,idle_ioctl_handler(), "IDLE->IDLE")	//iocontrol
			}	
		}
		FSM_STATE_FORCED(ST_RECV, "RECV", packet_send_to_upperlayer(), )
		{
			FSM_TRANSIT_FORCE(ST_IDLE, , "default", "", "RECV -> IDLE");
		}
		FSM_STATE_FORCED(ST_SEND, "SEND", packet_send_to_eth(), )   //20141029 for test
		{
			FSM_TRANSIT_FORCE(ST_IDLE, , "default", "", "SEND -> IDLE");
		}
		FSM_STATE_FORCED(ST_RECV_TYPE2_FROM_SRIO, "RECV_TYPE2_FROM_SRIO", type2_recv_from_srio(), )   //20141029 for test
		{
			FSM_TRANSIT_FORCE(ST_IDLE, , "default", "", "RECV_TYPE2_FROM_SRIO -> IDLE");
		}
	}
	FSM_EXIT(0)
}

/********************************************************************************
** Function name: init_enter
** Description: ¡Á?š¬??š²3?šº??¡¥o¡¥šºy
** Input:
** Output:
** Returns:
** Created by:
** Created Date:
** ------------------------------------------------------------------------------
** Modified by: 
** Modified Date: 
********************************************************************************/
static void init_enter(void)
{
	FIN(init_enter());
	if(SRIO_OPEN)
	{
//		fsm_schedule_self(0, _START_WORK);
	}
	FOUT;
}

/********************************************************************************
** Function name: srio_sv_init
** Description: ¡Á?š¬??š²šš???¡À?š¢?3?šº??¡¥o¡¥šºy
** Input:
** Output:
** Returns:
** Created by:
** Created Date:
** ------------------------------------------------------------------------------
** Modified by: 
** Modified Date: 
********************************************************************************/
static void srio_sv_init(void)
{
	FIN(srio_sv_init());//
	fsm_printf("in srio_sv_init\n");
	u32 i;
	SV_PTR_GET(srio_sv);//
	SV(packet_count) = 0;//
	SV(interval) = 100000;//
	SV(psend_handle) = 0;//
	SV(sfn) = 0;
	SV(subframeN) = 0;
	SV(racomplete) = false;
	SV(recv_interval)=377;
	SV(send_interval)=777;
	SV(recv_pkt_from_ue)=0;
	init_enter();
	for (i = 0; i < USER_NUM; i ++)
	{
		SV(Dci_Store.rnti[i]) = 0;
	}
	for (i = 0; i < MAX_STORED_PKT; i ++){
		fsm_mem_set(&SV(pkts[i]),0,sizeof(FSM_PKT*));
		
		fsm_printf("[ENB SRIO]%p\n", SV(pkts[i]));
	}
	SV(stored_pkt_count) = 0;
	SV(recv_upper_pkt_num) = 0;
	SV(pre_pkt_no) = 0;
	SV(lost_pkt_count) = 0;
	test_send_sf(); 
	for (i = 0; i < cache_num; i ++){
		SV(ptr_to_tasklet[i]) = fsm_mem_alloc(cache_size);
		fsm_mem_set(SV(ptr_to_tasklet[i]), 0, cache_size);
	}
	FOUT;
}

/********************************************************************************
** Function name: srio_close
** Description: ¡Á?š¬??š²1?¡À?o¡¥šºy
** Input:
** Output:
** Returns:
** Created by:
** Created Date:
** ------------------------------------------------------------------------------
** Modified by: 
** Modified Date: 
********************************************************************************/
static void srio_close(void)
{
	FIN(srio_close());
	SV_PTR_GET(srio_sv);
	fsm_printf("srio has sent %d packets.\n", SV(packet_count));
	//riodt_exit(); //20150429
	if(SV(psend_handle))
	{
		fsm_schedule_cancel(SV(psend_handle));
		SV(psend_handle) = 0;
	}
	FOUT;
}

/********************************************************************************
** Function name: packet_send_to_eth
** Description: šº?ŠÌ?šŠ?2?¡€¡éŠÌ?šºy?Y¡ãš¹¡ê???¡€¡éŠÌ?š°?š¬?šª?(2ašº?š®?)
** Input:
** Output:
** Returns:
** Created by:
** Created Date:
** ------------------------------------------------------------------------------
** Modified by: MF
** Modified Date: 20140717
** Modified Description: ?¡À?š®?š²?šŽ¡ãš¹ 2?¡€¡é?šª3?šš£€ 2ašº?š®?
********************************************************************************/
/***** mf modified 20141029 for MACSRIO test**************/
static void packet_send_to_eth(void)
//static void packet_send_to_eth(FSM_PKT* pkptr)
{
	FSM_PKT* pkptr;
	FSM_PKT* pkptrcopy;
	struct lte_test_srio_head* sh_ptr;
	struct ethhdr* head_ptr;
	DCI_STORE Dci_Store;
	Data_Dl_DCI Dl_Dci;
	u16 rnti;
	u16 i;
	u32 len;
	FIN(packet_send_to_eth());
	u32 flag = 0;
	SV_PTR_GET(srio_sv);
	//printk("Entering...\n");
	if (SV(racomplete) == false){
		Dci_Store = SV(Dci_Store);
		char dst_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
		
		
		pkptr = fsm_pkt_get();
		MACtoPHYadapter_IciMsg* MactoPhyICI=(MACtoPHYadapter_IciMsg*)fsm_mem_alloc(sizeof(MACtoPHYadapter_IciMsg));

		fsm_mem_cpy(MactoPhyICI, (MACtoPHYadapter_IciMsg *)(pkptr->head), sizeof(MACtoPHYadapter_IciMsg));
		pkptrcopy = fsm_pkt_create(pkptr->tail-pkptr->data+64);
		fsm_skb_put(pkptrcopy, (pkptr->tail-pkptr->data));
		fsm_mem_cpy(pkptrcopy->data,pkptr->data,(pkptr->tail-pkptr->data));
		fsm_pkt_destroy(pkptr);
		if(pkptrcopy != NULL)
		{
			if(fsm_skb_headroom(pkptrcopy) < (ETH_HLEN + sizeof(struct lte_test_srio_head)))
				{
					pkptrcopy = fsm_skb_realloc_headeroom(pkptrcopy,(sizeof(struct lte_test_srio_head)));
					if(pkptrcopy == NULL)
						return;
				}
			fsm_skb_push(pkptrcopy, sizeof(struct lte_test_srio_head));
			sh_ptr = (struct lte_test_srio_head*)pkptrcopy->data;
			sh_ptr->type = fsm_htonl(2);
			sh_ptr->len = fsm_htonl(pkptrcopy->len-sizeof(struct lte_test_srio_head));
			sh_ptr->rnti = fsm_htons(MactoPhyICI->rnti);
			sh_ptr->sfn = fsm_htons(SV(sfn));
			sh_ptr->subframeN = fsm_htons(SV(subframeN));
			fsm_printf("[ENB SRIO]The rnti of the packet is %u, sending to ETH\n", sh_ptr->rnti);
			fsm_skb_push(pkptrcopy, ETH_HLEN);
			head_ptr = (struct ethhdr*)pkptrcopy->data;
			fsm_mem_cpy(head_ptr->h_dest, dst_addr, ETH_ALEN);
			fsm_mem_cpy(head_ptr->h_source, fsm_intf_addr_get(STRM_TO_ETH), ETH_ALEN);
			head_ptr->h_proto = fsm_htons(DEV_PROTO_SRIO);	
			fsm_printf("[srio]:pkptrcopy->data len = %d:\n", pkptrcopy->len);
			fsm_octets_print(pkptrcopy->data, pkptrcopy->tail-pkptrcopy->data);
			fsm_pkt_send(pkptrcopy,STRM_TO_ETH);
			SV(packet_count)++;
		}
	}
	else
	{
		//send to srio
		type1_pkt_assemble_test();
	}
	
	FOUT;
}

/********************************************************************************
** Function name: type1_pkt_assemble_test
** Description:used for assemble type1 pkts
** Input:
** Output:
** Returns:
** Created by:Godsx
** Created Date:151222
** ------------------------------------------------------------------------------
** Modified by: 
** Modified Date: 
** Modified Description:
********************************************************************************/
static void type1_pkt_assemble_test()
{
	FIN(type1_pkt_assemble());
	//unsigned int prevtime,currenttime,usetime;
	//prevtime = fsm_get_curtime();
	//static int count_pkt=0;
	FSM_PKT* pkptr;
	FSM_PKT* pkptrfrommac;
	u32 len;
	u32 tmp_len;
	u16 sysframenum;
	u16 subframenum;
	u32 i;
	u16 data_len;
	static u32 send_count=1;
	SV_PTR_GET(srio_sv);
	sysframenum = (u16)GetFrameNo();
	subframenum = (u16)GetsubFrameNo();
	if(subframenum>=9)
	{
		subframenum=(subframenum+1)%10;
		sysframenum=sysframenum+1;
	}
	else
	{
		subframenum=subframenum+1;
	}
	if((subframenum==2)||(subframenum==7))
	{
		subframenum=(subframenum+1)%10;
	}
	if(send_count==1)
	{
	subframenum=0;
	}
	if(send_count==2)
	{
	subframenum=5;
	}
	if(send_count==3)
	{
	subframenum=1;
	}
	if(send_count==4)
	{
	subframenum=6;
	}
	pkptrfrommac = fsm_pkt_get();
	fsm_octets_print(pkptrfrommac->data, pkptrfrommac->tail-pkptrfrommac->data);
	MACtoPHYadapter_IciMsg* MactoPhyICI=(MACtoPHYadapter_IciMsg*)fsm_mem_alloc(sizeof(MACtoPHYadapter_IciMsg));
	fsm_mem_cpy(MactoPhyICI, (MACtoPHYadapter_IciMsg *)(pkptrfrommac->head), sizeof(MACtoPHYadapter_IciMsg));
	data_len = pkptrfrommac->tail - pkptrfrommac->data;
	ENBPHYADPtoPHYType1 type1head;
	ENB_DL_TYPE1_PBCH_C type1pbchc;
	ENB_DL_TYPE1_PBCH_D type1pbchd;
	ENB_DL_TYPE1_PHICH_C type1phichc[2];
	ENB_DL_TYPE1_PHICH_D type1phichd[2];
	ENB_DL_TYPE1_PDCCH_C type1pdcchc[5];
	ENB_DL_TYPE1_PDCCH_D type1pdcchd[5];
	ENB_DL_TYPE1_PDSCH_C type1pdschc[5];
	ENB_DL_TYPE1_PDSCH_D type1pdschd[5];

	
	//create len for test
	len = sizeof(struct ENBPHYADPtoPHYType1) + sizeof(struct ENB_DL_TYPE1_PBCH_C) + sizeof(struct ENB_DL_TYPE1_PBCH_D) + 
	2 * sizeof(struct ENB_DL_TYPE1_PHICH_C) + 2 * sizeof(struct ENB_DL_TYPE1_PHICH_D) + 5 * sizeof(struct ENB_DL_TYPE1_PDCCH_C)
	 + 5 * sizeof(struct ENB_DL_TYPE1_PDCCH_D) + 5 * sizeof(struct ENB_DL_TYPE1_PDSCH_C) + 5 * sizeof(struct ENB_DL_TYPE1_PDSCH_D) + 5*sizeof(struct ENB_DL_TYPE1_PDSCH_D)+5*720;
	pkptr = fsm_pkt_create(len);

	if(pkptr != NULL)
	{
		tmp_len = 0;
		type1head.GHead.NewFlag = 1;
		type1head.GHead.SFN = sysframenum;
		type1head.GHead.SubframeN = subframenum;
		type1head.DL_TYPE1_PUBLIC_C.PDSCHNum = 5; //µ±Ç°×ÓÖ¡PDSCHÐÅµÀÊýÁ¿,×îÐ¡ÏµÍ³²ÎÊýÎª5,µ÷ÊÔÊ±ÓÉ1¡«5±ä»¯
		type1head.DL_TYPE1_PUBLIC_C.PDCCHNum = 5; //µ±Ç°×ÓÖ¡PDCCHÐÅµÀÊýÁ¿,×îÐ¡ÏµÍ³²ÎÊýÎª5,µ÷ÊÔÊ±ÓÉ1¡«5±ä»¯
		type1head.DL_TYPE1_PUBLIC_C.NumOfUEForPHICH = 2; //µ±Ç°×ÓÖ¡PHICH³ÐÔØµÄÉÏÐÐÓÃ»§µÄÊýÄ¿,×îÐ¡ÏµÍ³²ÎÊýÎª2
		type1head.DL_TYPE1_PUBLIC_C.Zero = 0; //±£Áô,×ÖœÚ¶ÔÆë
		type1head.DL_TYPE1_PUBLIC_C.PBCH_C_Offset = sizeof(ENBPHYADPtoPHYType1);
		type1head.DL_TYPE1_PUBLIC_C.PBCH_D_Offset = type1head.DL_TYPE1_PUBLIC_C.PBCH_C_Offset+ sizeof(ENB_DL_TYPE1_PBCH_C);
		type1head.DL_TYPE1_PUBLIC_C.PHICH_C_Offset = type1head.DL_TYPE1_PUBLIC_C.PBCH_D_Offset  + sizeof(ENB_DL_TYPE1_PBCH_D);
		type1head.DL_TYPE1_PUBLIC_C.PHICH_D_Offset = type1head.DL_TYPE1_PUBLIC_C.PHICH_C_Offset+ type1head.DL_TYPE1_PUBLIC_C.NumOfUEForPHICH * sizeof(ENB_DL_TYPE1_PHICH_C);
		type1head.DL_TYPE1_PUBLIC_C.PDCCH_C_Offset = type1head.DL_TYPE1_PUBLIC_C.PHICH_D_Offset+ type1head.DL_TYPE1_PUBLIC_C.NumOfUEForPHICH * sizeof(ENB_DL_TYPE1_PHICH_D);
		type1head.DL_TYPE1_PUBLIC_C.PDCCH_D_Offset = type1head.DL_TYPE1_PUBLIC_C.PDCCH_C_Offset + type1head.DL_TYPE1_PUBLIC_C.PDCCHNum * sizeof(ENB_DL_TYPE1_PDCCH_C);
		type1head.DL_TYPE1_PUBLIC_C.PDSCH_C_Offset =type1head.DL_TYPE1_PUBLIC_C.PDCCH_D_Offset  + type1head.DL_TYPE1_PUBLIC_C.PDCCHNum * sizeof(ENB_DL_TYPE1_PDCCH_D);
		type1head.DL_TYPE1_PUBLIC_C.PDSCH_D_Offset =type1head.DL_TYPE1_PUBLIC_C.PDSCH_C_Offset + type1head.DL_TYPE1_PUBLIC_C.PDSCHNum * sizeof(ENB_DL_TYPE1_PDSCH_C);
		fsm_skb_put(pkptr,sizeof(struct ENBPHYADPtoPHYType1));
		fsm_mem_cpy(pkptr->data + tmp_len, &type1head, sizeof(struct ENBPHYADPtoPHYType1));
		tmp_len += sizeof(struct ENBPHYADPtoPHYType1);
		type1pbchc.NumPrbBw = 100;
		type1pbchc.PhichDurtion = 0;
		type1pbchc.GPhichNg = 0;
		type1pbchc.spare = 0;
		fsm_skb_put(pkptr,sizeof(struct ENB_DL_TYPE1_PBCH_C));
		fsm_mem_cpy(pkptr->data + tmp_len, &type1pbchc, sizeof(struct ENB_DL_TYPE1_PBCH_C));

		tmp_len += sizeof(struct ENB_DL_TYPE1_PBCH_C);
		//PBCH_D²ÎÊý
		type1pbchd.SourcePBCH = 0; //Žý¶š
		
		fsm_skb_put(pkptr,sizeof(struct ENB_DL_TYPE1_PBCH_D));
		fsm_mem_cpy(pkptr->data + tmp_len, &type1pbchd, sizeof(struct ENB_DL_TYPE1_PBCH_D));

		tmp_len += sizeof(struct ENB_DL_TYPE1_PBCH_D);
		//PHICH_C²ÎÊý,ÁœžöÓÃ»§
		type1phichc[0].RNTI = 61;
		type1phichc[0].zero = 0;
		type1phichc[0].I_lowest_index_PRB_RA = 0; //Žý¶š
		type1phichc[0].NDmrs = 0; //Žý¶š
		type1phichc[1].RNTI = 62;
		type1phichc[1].zero = 0;
		type1phichc[1].I_lowest_index_PRB_RA = 0; //Žý¶š
		type1phichc[1].NDmrs = 0; //Žý¶š
		fsm_skb_put(pkptr,2*sizeof(struct ENB_DL_TYPE1_PHICH_C));
		fsm_mem_cpy(pkptr->data + tmp_len, &type1phichc, 2*sizeof(struct ENB_DL_TYPE1_PHICH_C));
		tmp_len += 2 * sizeof(struct ENB_DL_TYPE1_PHICH_C);
		type1phichd[0].RNTI = 61;
		type1phichd[0].SourcePHICH = 0;
		type1phichd[1].RNTI = 62;
		type1phichd[1].SourcePHICH = 0;
		fsm_skb_put(pkptr,2*sizeof(struct ENB_DL_TYPE1_PHICH_D));
		fsm_mem_cpy(pkptr->data + tmp_len, &type1phichd, 2*sizeof(struct ENB_DL_TYPE1_PHICH_D));
		tmp_len += 2*sizeof(struct ENB_DL_TYPE1_PHICH_D);
		for(i = 0;i < type1head.DL_TYPE1_PUBLIC_C.PDCCHNum;i ++)
		{
			type1pdcchc[i].RNTI = 61 + i;
			type1pdcchc[i].CommonPdcchFlag = 0;
			type1pdcchc[i].PdcchFormat = 0;
			type1pdcchc[i].DCIFormat = 2;
			type1pdcchc[i].DciBitLen = 31;
		}
		fsm_skb_put(pkptr,5*sizeof(struct ENB_DL_TYPE1_PDCCH_C));
		fsm_mem_cpy(pkptr->data + tmp_len, &type1pdcchc, 5*sizeof(struct ENB_DL_TYPE1_PDCCH_C));
		tmp_len += 5*sizeof(struct ENB_DL_TYPE1_PDCCH_C);
		for(i = 0;i < type1head.DL_TYPE1_PUBLIC_C.PDCCHNum;i ++)
		{
			type1pdcchd[i].RNTI = 61 + i;
			type1pdcchd[i].zero = 0;
			type1pdcchd[i].DataSource = DataSource[i];
		}
		fsm_skb_put(pkptr,5*sizeof(struct ENB_DL_TYPE1_PDCCH_D));
		fsm_mem_cpy(pkptr->data + tmp_len, &type1pdcchd, 5*sizeof(struct ENB_DL_TYPE1_PDCCH_D));
		tmp_len += 5*sizeof(struct ENB_DL_TYPE1_PDCCH_D);
		for(i = 0;i < type1head.DL_TYPE1_PUBLIC_C.PDSCHNum;i ++)
		{
			type1pdschc[i].RNTI = 61 + i;
			type1pdschc[i].NumCW = 1;
			type1pdschc[i].NumPrbofUe = 20;
			type1pdschc[i].UeCategory = 3;
			type1pdschc[i].UeTransMod = 2;
			type1pdschc[i].NumHarqPro = 8;
			type1pdschc[i].RvIdx = 0;
			type1pdschc[i].Modulation = 1;
			type1pdschc[i].NumLayers = 2;
			type1pdschc[i].DelayMod = 0;
			type1pdschc[i].PA = 4;
			type1pdschc[i].zero = 0;
			if(subframenum == 1 || subframenum == 6)
			{
				type1pdschc[i].PDSCHTbSize = 4264; //ÌØÊâframe
			}
			else
			{
				type1pdschc[i].PDSCHTbSize = 5736; //ÆÕÍšframe
			}
			type1pdschc[i].BitMap = 0xF8000000>>(5 * i);
		}
		fsm_skb_put(pkptr,5*sizeof(struct ENB_DL_TYPE1_PDSCH_C));
		fsm_mem_cpy(pkptr->data + tmp_len, &type1pdschc, 5*sizeof(struct ENB_DL_TYPE1_PDSCH_C));
		tmp_len += 5*sizeof(struct ENB_DL_TYPE1_PDSCH_C);	
		fsm_skb_put(pkptr,5*sizeof(struct ENB_DL_TYPE1_PDSCH_D)+5*720);
		for(i = 0;i < type1head.DL_TYPE1_PUBLIC_C.PDSCHNum;i ++)
		{
			type1pdschd[i].RNTI = 61 + i;
			type1pdschd[i].PdschData = 720;
			fsm_mem_cpy(pkptr->data + tmp_len, &type1pdschd, sizeof(struct ENB_DL_TYPE1_PDSCH_D));
			tmp_len += sizeof(struct ENB_DL_TYPE1_PDSCH_D);
			fsm_mem_cpy(pkptr->data + tmp_len, &send_count, 4);
			fsm_mem_cpy(pkptr->data + tmp_len+4, &data_len, 2);
			tmp_len += 6;
			fsm_mem_cpy(pkptr->data + tmp_len, pkptrfrommac->data, data_len);
			tmp_len += data_len;
			tmp_len=tmp_len+720-(data_len+6);
		}
		//copy to srio
		spin_lock(&UnionQueue[subframenum].my_lock);
		fsm_mem_cpy((char *)(VirAddrStart[subframenum]+ (UnionQueue[subframenum].NextData)*0xfa0), pkptr->data, pkptr->len);
		if(!Push(&UnionQueue[subframenum],UnionQueue[subframenum].NextData))
			           printk("Push failed...\n");	
		spin_unlock(&UnionQueue[subframenum].my_lock);
		//sendcount++;
		send_count++;
		//printk("LTE send_count = %u\n",send_count);
		//currenttime = fsm_get_curtime();
		//usetime = currenttime - prevtime;
		//printk("LTE subframenum = %u\n",subframenum);
		fsm_pkt_destroy(pkptrfrommac);
		fsm_octets_print(pkptr->data, pkptr->tail-pkptr->data);
		fsm_pkt_destroy(pkptr);
	}
	FOUT;
}

/********************************************************************************
** Function name: packet_send_to_upperlayer
** Description: šº?ŠÌ???2?¡€¡éŠÌ?šºy?Y¡ãš¹¡ê??š°šŠ?¡€¡é?šªŠÌ?MAC2?(2ašº?š®?)
** Input:
** Output:
** Returns:
** Created by:
** Created Date:
** ------------------------------------------------------------------------------
** Modified by: MF
** Modified Date: 20140717
** Modified Description: ?¡À?š®?š²?šŽ¡ãš¹ 2?¡€¡é?šª3?šš£€ 2ašº?š®?
********************************************************************************/
static void packet_send_to_upperlayer(void)
{
	FSM_PKT* pkptr;
	static int pkt_no;
	MACtoPHYadapter_IciMsg * ici_to_phyadapter;
	PHYadaptertoMAC_IciMsg * ici_to_mac;
	MSG1_Content * Msg1_recv;
	S_RAinfo * Msg1_req;
	void* Msg1;
	u32 num = 1;
	struct lte_test_srio_head* sh_ptr;
	FIN(packet_send_to_upperlayer());
	SV_PTR_GET(srio_sv);
	if (SV(racomplete) == true){
		pkptr = fsm_pkt_get();
		sh_ptr = (struct lte_test_srio_head*)pkptr->data;
		fsm_skb_pull(pkptr, sizeof(struct lte_test_srio_head));
		fsm_printf("[ENB SRIO] ENTER packet_send_to_upperlayer(), and the fsm_ntohl(sh_ptr->type) is %d\n",fsm_ntohl(sh_ptr->type));
		if(fsm_ntohl(sh_ptr->type) == 2)
		{
			ici_to_mac=(PHYadaptertoMAC_IciMsg*)fsm_mem_alloc(sizeof(PHYadaptertoMAC_IciMsg));
			ici_to_mac->tcid=2;
			ici_to_mac->rnti=sh_ptr->rnti;
			ici_to_mac->ue_info.rnti = sh_ptr->rnti;
			ici_to_mac->ue_info.sfn = 2;
			ici_to_mac->ue_info.subframeN = 7;
			ici_to_mac->ue_info.crc = 0;
			ici_to_mac->ue_info.harqindex = 0;
			ici_to_mac->ue_info.harq_result = 0;
			ici_to_mac->ue_info.sr = 0;
			ici_to_mac->ue_info.cqi = 9;
			ici_to_mac->ue_info.pmi = 0;
			ici_to_mac->ue_info.ta = 32;
			fsm_mem_cpy(pkptr->head,ici_to_mac,sizeof(PHYadaptertoMAC_IciMsg));
			fsm_printf("[ENB SRIO]pkptr->data len = %d\n",pkptr->len);
			fsm_pkt_send(pkptr, STRM_TO_RLCMAC);
			pkt_no++;
		//	printk("%d \n", pkt_no);
		}
		else if(fsm_ntohl(sh_ptr->type) == 1)
		{
			Msg1_recv = (MSG1_Content *)pkptr->data;
			fsm_printf("[ENB SRIO]Received packet cqi = %u,rapid = %u\n", Msg1_recv->cqi,Msg1_recv->rapid);

			Msg1 = fsm_mem_alloc(sizeof(u32) + num * sizeof(S_RAinfo));
			fsm_mem_cpy(Msg1,(void *)(&num),sizeof(u32));
			Msg1_req = (S_RAinfo *)fsm_mem_alloc(sizeof(S_RAinfo));
			Msg1_req->total_num = 1;
			Msg1_req->index = 0;
			Msg1_req->ra_rnti = Msg1_recv->rarnti;
			Msg1_req->sfn = 0;
			Msg1_req->subframeN = 2;
			Msg1_req->crc = 0;
			Msg1_req->harqindex = 0;
			Msg1_req->harq_result = 0;
			Msg1_req->cqi = Msg1_recv->cqi;
			Msg1_req->pmi = 0;
			Msg1_req->sr = 0;
			Msg1_req->ta = Msg1_recv->ta;
			Msg1_req->rapid = Msg1_recv->rapid;
			fsm_mem_cpy((Msg1 + sizeof(u32)),(void *)Msg1_req, sizeof(S_RAinfo));
			fsm_do_ioctrl(STRM_TO_RLCMAC,IOCCMD_PHYtoMAC_RA_Req,(void *)Msg1,sizeof(u32)+sizeof(S_RAinfo));
			fsm_pkt_destroy(pkptr);
			test_send_ta();
		}
		else 
			fsm_pkt_destroy(pkptr);
	}else{
		pkptr = fsm_pkt_get();
		sh_ptr = (struct lte_test_srio_head*)pkptr->data;
		fsm_skb_pull(pkptr, sizeof(struct lte_test_srio_head));
		fsm_printf("[ENB SRIO] ENTER packet_send_to_upperlayer(), and the fsm_ntohl(sh_ptr->type) is %d\n",fsm_ntohl(sh_ptr->type));
		if(fsm_ntohl(sh_ptr->type) == 2)
		{
			ici_to_mac=(PHYadaptertoMAC_IciMsg*)fsm_mem_alloc(sizeof(PHYadaptertoMAC_IciMsg));
			ici_to_mac->tcid=2;
			ici_to_mac->rnti=sh_ptr->rnti;
			ici_to_mac->ue_info.rnti = sh_ptr->rnti;
			ici_to_mac->ue_info.sfn = 2;
			ici_to_mac->ue_info.subframeN = 7;
			ici_to_mac->ue_info.crc = 0;
			ici_to_mac->ue_info.harqindex = 0;
			ici_to_mac->ue_info.harq_result = 0;
			ici_to_mac->ue_info.sr = 0;
			ici_to_mac->ue_info.cqi = 9;
			ici_to_mac->ue_info.pmi = 0;
			ici_to_mac->ue_info.ta = 32;
			fsm_mem_cpy(pkptr->head,ici_to_mac,sizeof(PHYadaptertoMAC_IciMsg));
			fsm_printf("[ENB SRIO]pkptr->data len = %d\n",pkptr->len);
			fsm_octets_print(pkptr->data, pkptr->tail-pkptr->data);
			fsm_pkt_send(pkptr, STRM_TO_RLCMAC);
			pkt_no++;
			printk("%d \n", pkt_no);
		}
		else if(fsm_ntohl(sh_ptr->type) == 1)
		{
			Msg1_recv = (MSG1_Content *)pkptr->data;
			fsm_printf("[ENB SRIO]Received packet cqi = %u,rapid = %u\n", Msg1_recv->cqi,Msg1_recv->rapid);

			Msg1 = fsm_mem_alloc(sizeof(u32) + num * sizeof(S_RAinfo));
			fsm_mem_cpy(Msg1,(void *)(&num),sizeof(u32));
			Msg1_req = (S_RAinfo *)fsm_mem_alloc(sizeof(S_RAinfo));
			Msg1_req->total_num = 1;
			Msg1_req->index = 0;
			Msg1_req->ra_rnti = Msg1_recv->rarnti;
			Msg1_req->sfn = 0;
			Msg1_req->subframeN = 2;
			Msg1_req->crc = 0;
			Msg1_req->harqindex = 0;
			Msg1_req->harq_result = 0;
			Msg1_req->cqi = Msg1_recv->cqi;
			Msg1_req->pmi = 0;
			Msg1_req->sr = 0;
			Msg1_req->ta = Msg1_recv->ta;
			Msg1_req->rapid = Msg1_recv->rapid;
			fsm_mem_cpy((Msg1 + sizeof(u32)),(void *)Msg1_req, sizeof(S_RAinfo));
			fsm_do_ioctrl(STRM_TO_RLCMAC,IOCCMD_PHYtoMAC_RA_Req,(void *)Msg1,sizeof(u32)+sizeof(S_RAinfo));
			fsm_pkt_destroy(pkptr);
			test_send_ta();
		}
		else 
			fsm_pkt_destroy(pkptr);
	}
	FOUT;
}

static void type2_recv_from_srio(void)
{
	FIN(type2_recv_from_srio());
	int offset=0x8FC0;
	int flag=-1;
	char *ptr;
	flag=read_type2_mem();

	if(flag!=-1)
	{		
			ptr=(char *)fsm_mem_alloc(36800);
			fsm_mem_cpy(ptr,mapaddr+flag*offset+0x100800,36800);
			*(u32*)(mapaddr+flag*offset+0x100800)=0;
			//recv_tasklet_handler(ptr);

	}
	fsm_schedule_self(100, _TYPE2_RECV_FROM_SRIO);
	FOUT;
}


/********************************************************************************
** Function name: idle_exit
** Description: 1?¡À?srio?¡ê?šŠ
** Input:
** Output:
** Returns:
** Created by:
** Created Date:
** ------------------------------------------------------------------------------
** Modified by: 
** Modified Date: 
********************************************************************************/
static void idle_exit(void)
{
	FIN(idle_exit());
	if(SRIO_CLOSE)
	{
		srio_close();
		//tasklet_kill(&recv_tasklet);
	}
	FOUT;
}

/********************************************************************************
** Function name: send_packet_period
** Description: ?š¹?š²?š°š°?š¬?šª?¡€¡é¡ãš¹(2ašº?š®?)
** Input:
** Output:
** Returns:
** Created by: ??????
** Created Date: 20140710
** ------------------------------------------------------------------------------
** Modified by: MF
** Modified Date: 
********************************************************************************/
static void send_packet_period(void)
{

	FSM_PKT* pkptr;
	//struct lte_test_srio_head* sh_ptr;
	//struct MACtoPHYadapter_IciMsg * ici_to_phyadapter;
	//struct PHYadaptertoMAC_IciMsg * ici_to_macpacket_send_to_upperlayer()
;
	struct ethhdr* head_ptr;
	
	char* data = "hello world!";
	char dst_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	
	FIN(send_packet_period());
	SV_PTR_GET(srio_sv);
	//fsm_printf("[ENB SRIO] ENTER send_packet_period()\n");
	if(PACKET_SEND_PERIOD)
	{
		pkptr = fsm_pkt_create(128);
		fsm_skb_put(pkptr, 64);
		
	/*
		if(fsm_skb_headroom(pkptr) < (ETH_HLEN + sizeof(struct lte_test_srio_head))+sizeof(struct MACtoPHYadapter_IciMsg))
		{
			pkptr = fsm_skb_realloc_headeroom(pkptr,ETH_HLEN + sizeof(struct lte_test_srio_head)+sizeof(struct MACtoPHYadapter_IciMsg));
			if(pkptr == NULL)
				return;
		}
		*/
		if(fsm_skb_headroom(pkptr) < ETH_HLEN)
		{
			pkptr = fsm_skb_realloc_headeroom(pkptr,ETH_HLEN);
			if(pkptr == NULL)
				return;
		}
		fsm_mem_cpy(pkptr->data, data, 12);
		/*
		fsm_skb_push(pkptr, sizeof(struct MACtoPHYadapter_IciMsg));
		ici_to_phyadapter=(struct MACtoPHYadapter_IciMsg *)pkptr->data;
		ici_to_phyadapter->frameNo=1;
		ici_to_phyadapter->MessageType=1;
		ici_to_phyadapter->rnti=1;
		ici_to_phyadapter->subframeNo=1;
		ici_to_phyadapter->tcid=1;
		fsm_skb_push(pkptr, sizeof(struct lte_test_srio_head));
		sh_ptr = (struct lte_test_srio_head*)pkptr->data;
		sh_ptr->type = fsm_htonl(0);
		sh_ptr->len = fsm_htonl(pkptr->len - sizeof(struct lte_test_srio_head));
		*/
		//skb_reset_network_header(pkptr);
		fsm_skb_push(pkptr, ETH_HLEN);
		head_ptr = (struct ethhdr*)pkptr->data;
		fsm_mem_cpy(head_ptr->h_dest, dst_addr, ETH_ALEN);
		fsm_mem_cpy(head_ptr->h_source, fsm_intf_addr_get(STRM_TO_ETH), ETH_ALEN);
		head_ptr->h_proto = fsm_htons(DEV_PROTO_SRIO);
		//fsm_printf("set new timer\n");
		//fsm_printf("timer event is added\n");
		SV(psend_handle) = fsm_schedule_self(SV(interval), _PACKET_SEND_PERIOD);
		//fsm_pkt_send(pkptr,STRM_TO_ETH);
		//fsm_pkt_destroy(pkptr);
		++SV(packet_count);
		//fsm_printf("[ENB SRIO]Node0 sends hello world packet periodly.\n");
	}
	FOUT;
}


/********************************************************************************
** Function name: idle_ioctl_handler
** Description: ??š€šªIDLE¡Á?š¬???ŠÌ?IOControl
** Input:
** Output:
** Returns:
** Created by: ??????
** Created Date: 
** ------------------------------------------------------------------------------
** Modified by: MF
** Modified Date: 
********************************************************************************/
static void idle_ioctl_handler(void)
{
	char* rec_data_ptr;
	u32 *interval_ptr;
	DCI_STORE Dci_Store;
	ENBMAC_TO_PHY_DLschedule* Dl_Schedule;
	ENBMAC_TO_PHY_ULschedule* Ul_Schedule;
	ENBMAC_TO_PHY_Rardci* Rar_Dci;
	void* ioctl_data;
	u32 i;
	u16 rnti=0;
	

	const char* data_ptr = "Hello MAC,I AM SRIO\n"; 
	
	FIN(ioctl_handler());
	SV_PTR_GET(srio_sv);
	if(IOCTL_ARRIVAL)
	{
		switch(fsm_ev_ioctrl_cmd())
		{
			case IOCCMD_PSEND_RUN:
				if(SV(psend_handle) == 0)
				{
					SV(psend_handle) = fsm_schedule_self(SV(interval), _PACKET_SEND_PERIOD);
				}
			FOUT;
			case IOCCMD_PSEND_STOP:
				if(SV(psend_handle))
				{
					fsm_schedule_cancel(SV(psend_handle));
					SV(psend_handle)= 0;
					
				}
			FOUT;
			case IOCCMD_PSEND_INTERVAL:
				interval_ptr = (u32*)fsm_data_get();
				SV(interval) = *interval_ptr;
				fsm_data_destroy(interval_ptr);
				if(SV(psend_handle))
				{
					fsm_schedule_cancel(SV(psend_handle));
					SV(psend_handle) = fsm_schedule_self(SV(interval), _PACKET_SEND_PERIOD);	
				}
				else
				{
					SV(psend_handle) = fsm_schedule_self(SV(interval), _PACKET_SEND_PERIOD);
				}
			FOUT;
			case IOCCMD_SAY_HELLO:
				rec_data_ptr = (char*)fsm_data_get();
				fsm_printf(rec_data_ptr);
				fsm_data_destroy(rec_data_ptr);
				fsm_do_ioctrl(STRM_TO_RLCMAC, IOCCMD_SAY_HELLO, (void*)data_ptr, 22);	
			FOUT;
			//20140715 mf
			/*
			case IOCCMD_TEST_SEND_MSG3:
				fsm_printf("SRIO:IOCCMD_TEST_SEND_MSG3.\n");
				if(SV(psend_handle) == 0)
				{
					SV(psend_handle) = fsm_schedule_self(SV(interval), _MSG3_FROM_UPPER);
				}
				FOUT;
				*/
			case IOCCMD_MACtoPHY_RNTI_Indicate:
				fsm_printf("SRIO:IOCCMD_MACtoPHY_RNTI_Indicate.\n");
				
				FOUT;
			case IOCCMD_MACtoPHY_recv_sysinfo: // 20140715 mf ???????a?3??
				fsm_printf("SRIO:IOCCMD_MACtoPHY_recv_sysinfo.\n");
				//send_sysinfo();
				FOUT;
			case IOCCMD_MACtoPHY_recv_paging:
				fsm_printf("SRIO:IOCCMD_MACtoPHY_recv_paging.\n");
				//send_paging();
				FOUT;
			case IOCCMD_MACtoPHY_Preamble_Indicate:



				fsm_printf("SRIO:IOCCMD_MACtoPHY_Preamble_Indicate.\n");
				//send_rar();
				FOUT;
			/*************20141013 MF modified**************To receive type1 ioctl from RRC*************/
			case IOCCMD_RRCtoPHY_Type1_Indicate:
				//ioctl_data = fsm_data_get();
				//send_type1();
				FOUT;
				break;
			/**************20141017 mf modified for test****************/
			case IOCCMD_TEST_SEND_TO_ETH:
				test_send_to_eth();
				FOUT;
				break;
			/**************20141029 MACSRIOš¢aŠÌ¡Â mf modified*************/
			case IOCCMD_SEND_MSG1:
				fsm_printf("[srio][idle_ioctl_handler][-->]IOCCMD_SEND_MSG1.\n");
				test_send_msg1();
				FOUT;
				break;
			case IOCCMD_SEND_MSG3:
				fsm_printf("[srio][idle_ioctl_handler][-->]IOCCMD_SEND_MSG3.\n");
				test_send_msg3();
				FOUT;
				break;
			case IOCCMD_SEND_TA:
				fsm_printf("[srio][idle_ioctl_handler][-->]IOCCMD_SEND_TA.\n");
				test_send_ta();
				FOUT;
				break;
			case IOCCMD_SEND_ULDATA:
				fsm_printf("[srio][idle_ioctl_handler][-->]IOCCMD_SEND_ULDATA.\n");
				test_send_uldata();
				FOUT;
				break;
			case IOCCMD_SEND_SF:
				fsm_printf("[srio][idle_ioctl_handler][-->]IOCCMD_SEND_SF.\n");
				test_send_sf();
				FOUT;
				break;
			case IOCCMD_DLSCHEDULE:
			/*	printk("[srio][idle_ioctl_handler][-->]IOCCMD_DLSCHEDULE.\n");
				Dci_Store = SV(Dci_Store);
				Dl_Schedule = (ENBMAC_TO_PHY_DLschedule*)fsm_data_get();
				rnti = Dl_Schedule->m_rnti;
				//fsm_printf("[srio]dl dci  rnti=%d\n",rnti);
				//FOUT;
				for (i = 0; i < USER_NUM; i ++)
				{
					if (Dci_Store.rnti[i] == 0)
					{
						Dci_Store.rnti[i] == rnti;
						Dci_Store.DL_DCI[i] = Dl_Schedule->dl_dci;
						break;
					}
					else
					{
						if (Dci_Store.rnti[i] == rnti)
						{
							Dci_Store.DL_DCI[i] = Dl_Schedule->dl_dci;
							break;
						}
					}
				}
				printk("[srio][idle_ioctl_handler][-->]IOCCMD_DLSCHEDULE.out.\n");
				FOUT;*/
				break;
			case IOCCMD_ULSCHEDULE:
				//fsm_printf("[srio][idle_ioctl_handler][-->]IOCCMD_ULSCHEDULE.\n");
				send_uldci_to_ue();
				FOUT;
				break;
			case IOCCMD_SEND_INFO:
				printk("in send_dsp_route_info_wrapper()\n");
				send_dsp_route_info_wrapper();
				FOUT;
				break;
			case IOCCMD_RARDCI:
				//fsm_printf("[srio][idle_ioctl_handler][-->]IOCCMD_RARDCI.\n");
				Dci_Store = SV(Dci_Store);
				Rar_Dci = (ENBMAC_TO_PHY_Rardci*)fsm_data_get();
				rnti = Rar_Dci->m_rnti;
				//fsm_printf("[MF]IOCCMD has got rnti = %d\n", rnti);
				for (i = 0; i < USER_NUM; i ++)
				{
					if (Dci_Store.rnti[i] == 0)
					{
						Dci_Store.rnti[i] == rnti;
						Dci_Store.RAR_DCI[i] = Rar_Dci->rar_dci;
						break;
					}
					else
					{
						if (Dci_Store.rnti[i] == rnti)
						{
							Dci_Store.RAR_DCI[i] = Rar_Dci->rar_dci;
							break;
						}
					}
				}
				FOUT;
				break;
				case IOCCMD_SEND_TO_SRIO:
					fsm_printf("SEND_TO_SRIO.\n");
				//	type1_pkt_assemble();
				FOUT;
				break;
				case IOCCMD_READ_MEM:
					fsm_printf("read mem\n");
					read_mem();
				FOUT;
				case IOCCMD_STOP_TIMER:
					printk("in rio_hrtimer1_stop_wrapper()\n");
					rio_hrtimer1_stop_wrapper();
				FOUT;
				break;
				case IOCCMD_RA_COMPLETE:
					fsm_printf("[ENB SRIO]RA COMPLETE\n");
					SV(racomplete) = true;
					//fsm_schedule_self(0, _TYPE2_RECV_FROM_SRIO);
					//fsm_schedule_self(1000, _TYPE1_SEND_TO_SRIO);
				FOUT;
				break;
				case IOCCMD_RIODT_STOP:
				fsm_printf("[UE SRIO]riodt_exit()\n");
				riodt_exit();
				FOUT;
				break;
				case IOCCMD_LOST_PKT_COUNT:
				printk("[ENB SRIO] has lost %d pkts\n", SV(lost_pkt_count));
				case IOCCMD_RECV_INTERVAL_ADD:
				SV(recv_interval)=SV(recv_interval)+100;
				printk("SV(recv_interval)=%d\n", SV(recv_interval));
				break;
				case IOCCMD_RECV_INTERVAL_MINUS:
				if(SV(recv_interval>=100))
				SV(recv_interval)=SV(recv_interval)-100;
				printk("SV(recv_interval)=%d\n", SV(recv_interval));
				break;
				case IOCCMD_PRINT_PKT_FROM_UE:
				printk("SV(recv_pkt_from_ue)=%d\n", SV(recv_pkt_from_ue));
				SV(recv_pkt_from_ue)=0;
				break;
			default:
				fsm_printf("SRIO:Unrecognized I/O control command.\n");
			FOUT;
		}
	}
}

static void send_uldci_to_ue(void)
{
	FIN(send_uldci_to_ue());
	u32 i;
	FSM_PKT* pkptr;
	struct lte_test_srio_head* sh_ptr;
	struct ethhdr* head_ptr;
	DCI_STORE Dci_Store;
	ENBMAC_TO_PHY_ULschedule* Ul_Schedule;
	u16 rnti;
	char dst_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

	
	SV_PTR_GET(srio_sv);

	Dci_Store = SV(Dci_Store);
	Ul_Schedule = (ENBMAC_TO_PHY_ULschedule*)fsm_data_get();
	if(Ul_Schedule==NULL)
	{
	printk("Ul_Schedule is NULL\n");
	return;
	}
	//fsm_data_destroy(Ul_Schedule);
	//FOUT;
	rnti = Ul_Schedule->m_rnti;
	for (i = 0; i < USER_NUM; i ++)
	{
		if (Dci_Store.rnti[i] == 0)
		{
			Dci_Store.rnti[i] == rnti;
			Dci_Store.UL_DCI[i] = Ul_Schedule->s_ul_dci;
			break;
		}
		else
		{
			if (Dci_Store.rnti[i] == rnti)
			{
				Dci_Store.UL_DCI[i] = Ul_Schedule->s_ul_dci;
				break;
			}
		}
	}

	pkptr = fsm_pkt_create(ETH_HLEN + sizeof(struct lte_test_srio_head) + sizeof(Data_Ul_DCI));
	//fsm_printf("[ENB MF]Ul_Schedule->s_ul_dci.RIV = %d\n",(Ul_Schedule->s_ul_dci).RIV);
	u32 uls =0;
	fsm_mem_cpy(&uls, &(Ul_Schedule->s_ul_dci), sizeof(u32));
	//fsm_printf("[ENB MF]Ul_Schedule = %d\n",uls);
	fsm_skb_put(pkptr, sizeof(Data_Ul_DCI));
	fsm_mem_cpy(pkptr->data, &(Ul_Schedule->s_ul_dci), sizeof(Data_Ul_DCI));

	//fsm_printf("[ENB MF]pkt->data = %d\n", *((u32*)pkptr->data));
	u32 len = pkptr->tail - pkptr->data;
	//fsm_printf("[DFZ]len = %d\n", len);
	u32 j =0;
	/*for (j = 0; j < len; j ++)
	{
		fsm_printf("%d ", *((u32*)pkptr->data+j*sizeof(u32)));
	}
	fsm_printf("\n");*/
	if(pkptr != NULL)
	{
	
		if(fsm_skb_headroom(pkptr) < (ETH_HLEN + sizeof(struct lte_test_srio_head)))
			{
			pkptr = fsm_skb_realloc_headeroom(pkptr,ETH_HLEN + sizeof(struct lte_test_srio_head));
			if(pkptr == NULL)
				return;
			}
		
		fsm_skb_push(pkptr, sizeof(struct lte_test_srio_head));
		sh_ptr = (struct lte_test_srio_head*)pkptr->data;
		sh_ptr->type = fsm_htonl(3);
		sh_ptr->len = fsm_htonl(pkptr->len-sizeof(struct lte_test_srio_head));
		sh_ptr->rnti = fsm_htons(rnti);
		sh_ptr->sfn = fsm_htons(SV(sfn));
		sh_ptr->subframeN = fsm_htons(SV(subframeN));
		
		fsm_skb_push(pkptr, ETH_HLEN);
		head_ptr = (struct ethhdr*)pkptr->data;
		fsm_mem_cpy(head_ptr->h_dest, dst_addr, ETH_ALEN);
		fsm_mem_cpy(head_ptr->h_source, fsm_intf_addr_get(STRM_TO_ETH), ETH_ALEN);
		head_ptr->h_proto = fsm_htons(DEV_PROTO_SRIO);	
		//fsm_octets_print(&pkptr->protocol, 2);
		//fsm_printf("[ENB MF] ULDCI RNTI = %d\n", rnti);
		//fsm_printf("[ENB MF AFTER]pkt->data = %d\n", *((u32*)(pkptr->data + ETH_HLEN + sizeof(struct lte_test_srio_head))));
		//fsm_pkt_send(pkptr,STRM_TO_ETH);
		fsm_pkt_destroy(pkptr);
		SV(packet_count)++;
	}
	FOUT;
				
}
static void test_send_msg1(void)
{
	u32 i;
	u32 num = 3;
	void* Msg1 = fsm_mem_alloc(sizeof(u32) + num * sizeof(S_RAinfo));
	fsm_mem_cpy(Msg1,(void *)(&num),sizeof(u32));
	for (i = 0; i < num;i ++)
	{
		S_RAinfo *Msg1_req = (S_RAinfo *)fsm_mem_alloc(sizeof(S_RAinfo));

		Msg1_req->total_num = num;
		Msg1_req->index = i;
		Msg1_req->ra_rnti = 61;
		Msg1_req->sfn = 0;
		Msg1_req->subframeN = 2;
		Msg1_req->crc = 0;
		Msg1_req->harqindex = 0;
		Msg1_req->harq_result = 0;
		Msg1_req->cqi = 9;
		Msg1_req->pmi = 0;
		Msg1_req->sr = 0;
		Msg1_req->ta = 0;
		Msg1_req->rapid = i+1;

		fsm_mem_cpy((Msg1 + sizeof(u32) + i*sizeof(S_RAinfo)),(void *)Msg1_req, sizeof(S_RAinfo));
		fsm_mem_free((void *)Msg1_req);
	}

	fsm_do_ioctrl(STRM_TO_RLCMAC,IOCCMD_PHYtoMAC_RA_Req,(void *)Msg1,sizeof(u32)+num*sizeof(S_RAinfo));
	//fsm_printf("[srio][test_send_msg1][-->]Message1 has sent to MAC.\n");
	
	
}
static void test_send_msg3(void)
{
	FSM_PKT* pkptr;
	pkptr = fsm_pkt_create(2048);
	msgFromCCCH(pkptr);
}

static void test_send_ta(void)
{
	Ue_ta_info *Ta_info = (Ue_ta_info *)fsm_mem_alloc(sizeof(Ue_ta_info));

	Ta_info->rnti = 61;
	Ta_info->update_flag = 1;
	Ta_info->ta = 42;

	//fsm_do_ioctrl(STRM_TO_RLCMAC,IOCCMD_PHYtoMAC_TA,(void *)Ta_info,sizeof(Ue_ta_info));
	//fsm_printf("[srio][test_send_ta][-->]TA has sent to MAC.\n");
	fsm_schedule_self(10000, _TEST_SEND_TA);
}

static void test_send_uldata(void)
{
	FSM_PKT* pkptr;
	//pkptr = fsm_pkt_create(248);
	//createHead(pkptr, 2, 0, 2);
	pkptr=generatepkt(61);
	fsm_pkt_send(pkptr,STRM_TO_RLCMAC);
}

static void test_send_sf(void)
{
	SV_PTR_GET(srio_sv);
	PHY_TO_MAC_frame *Sf_info = (PHY_TO_MAC_frame *)fsm_mem_alloc(sizeof(PHY_TO_MAC_frame));

	Sf_info->sfn = SV(sfn);
	Sf_info->subframeN = SV(subframeN);

	//fsm_do_ioctrl(STRM_TO_RLCMAC,IOCCMD_PHYtoMAC_FRAME,(void *)Sf_info,sizeof(Sf_info));
	//fsm_printf("[srio][test_send_sf][-->]SF has sent to MAC.sf = %d, subframeN = %d\n", SV(sfn), SV(subframeN));

	SV(sfn) ++;
	SV(subframeN) ++;

	if (SV(sfn) > 1023)
		SV(sfn) = 0;
	if (SV(subframeN) > 9)
		SV(subframeN) = 0;
	export_frameNo = SV(sfn);
	export_subframeNo = SV(subframeN);
	fsm_schedule_self(100, _TEST_SEND_SF);
	//fsm_schedule_self(10000, _TEST_SEND_SF);
	//fsm_schedule_self(500000, _TYPE1_SEND_TO_SRIO);
}

static void read_mem()
{
	memread(0xfc100000, 256);
}


/**************20141017 mf modified for test****************/
static void test_send_to_eth(void)
{
	FSM_PKT* pkptr;

	pkptr = fsm_pkt_create(2048);
	//packet_send_to_eth(pkptr);

}


/********************************************************************************
** Function name: cfg_ioctl_handler
** Description: ??š€šªCFG¡Á?š¬???ŠÌ?IOControl
** Input:
** Output:
** Returns:
** Created by: MF
** Created Date: 20141013
** ------------------------------------------------------------------------------
** Modified by: MF
** Modified Date: 
********************************************************************************/
static void cfg_ioctl_handler(void)
{
	FIN(ioctl_handler());

	void* ioctl_data;
	
	if(IOCTL_ARRIVAL)
	{
		switch(fsm_ev_ioctrl_cmd())
		{
			/*************20141013 MF modified**************To receive type1 ioctl from RRC*************/
			default:
				fsm_printf("SRIO:Unrecognized I/O control command.\n");
			FOUT;
		}
	}
}




/********************************************************************************
** Function name: print_tran_info
** Description: ?š°š®?ŠÌ¡À?¡ã¡Á?š¬?
** Input: const char *str Dšš?š°š®?ŠÌ??š²ššY
** Output:
** Returns:
** Created by: ?šª¡€?
** Created Date: 
** ------------------------------------------------------------------------------
** Modified by: 
** Modified Date: 
********************************************************************************/

void print_tran_info( const char *str)
{
	FIN( print_tran_info());
	u32 curtime=0;
	curtime=fsm_get_curtime();
	fsm_printf("%d ",curtime);
	fsm_printf(str);
	fsm_printf("\n");
FOUT;
}

/********************************************************************************
** Function name: ioctldata
** Description: get2¡édestroyioctlŠÌ?data 2ašº?š®??š²??
** Input:
** Output:
** Returns:
** Created by: ?šª¡€?
** Created Date: 
** ------------------------------------------------------------------------------
** Modified by: 
** Modified Date: 
********************************************************************************/

void ioctldata()
{
	FIN(ioctldata());
	void *data;
	data = fsm_data_get();
	fsm_data_destroy(data);
	FOUT;
}

/********************20141030 MACSRIOTEST HX*************************************/
FSM_PKT* generatepkt(u16 rnti) //šŠš²3šŠŠÌ??š²ššYš°??-šŠšš??
{
   char* data1="hello MAC one";
   char* data2="hello MAC two";
   FSM_PKT* pkptr;
   u32 len=0,reservelen=10,macheadlen=0,datalen=0,icilen=sizeof(RLCtoMAC_IciMsg);
   FIN(generatepkt());
   PHYadaptertoMAC_IciMsg *ici_msg=(PHYadaptertoMAC_IciMsg*)fsm_mem_alloc(sizeof(PHYadaptertoMAC_IciMsg));
   MAC_SDU_subhead_7bit *macsubhead=(MAC_SDU_subhead_7bit*)fsm_mem_alloc(sizeof(MAC_SDU_subhead_7bit));
	PHYtoMAC_Info ue_infor;
   macheadlen=2*sizeof(MAC_SDU_subhead_7bit);
   datalen=14*2;
   len=macheadlen+datalen+reservelen+sizeof(RLCtoMAC_IciMsg);
   pkptr=fsm_pkt_create(len);
   
   ici_msg->rnti=rnti;
   //ici_msg->len=macheadlen;
	ici_msg->tcid=2;
	ue_infor.rnti = rnti;
	ue_infor.sfn = 32;
	ue_infor.subframeN = 0;
	ue_infor.crc = 0;
	ue_infor.harqindex = 0;
	ue_infor.harq_result = 0;
	ue_infor.sr = 0;
	ue_infor.cqi = 9;
	ue_infor.pmi = 0;
	ue_infor.ta = 0;
	fsm_mem_cpy(&(ici_msg->ue_info),&ue_infor,sizeof(PHYtoMAC_Info));
	icilen=2*sizeof(MAC_SDU_subhead_7bit);
	//fsm_printf("[DAFANGZI]LENGTH OF TWO 7BIT HEADS:%d\n",icilen);
	fsm_skb_put(pkptr,icilen+64);
   fsm_mem_cpy(pkptr->head,ici_msg,sizeof(RLCtoMAC_IciMsg));//¡Á¡ãšš?ICID??¡é
   createmachead7bit(macsubhead,2,14,1);//šŠš²3šŠš°???¡Áš®šª¡€
   fsm_mem_cpy(pkptr->data,macsubhead,sizeof(MAC_SDU_subhead_7bit));//¡Á¡ãšš?ŠÌ?SK_BUFF
   createmachead7bit(macsubhead,8,14,0);//šŠš²3šŠ¡Á?oš®š°???¡Áš®šª¡€
   fsm_mem_cpy(pkptr->data+sizeof(MAC_SDU_subhead_7bit),macsubhead,sizeof(MAC_SDU_subhead_7bit));//¡Á¡ãšš?ŠÌ?SK_BUFF
   //fsm_skb_reserve(pkptr,macheadlen*2+reservelen+sizeof(RLCtoMAC_IciMsg));//šª¡€2??š¢?¡Á?1?????
   fsm_mem_cpy(pkptr->data+icilen,data1,14);//¡Á¡ãšš?SUD1
   fsm_mem_cpy(pkptr->data+14+icilen,data2,14);//¡Á¡ãšš?SDU2
   
   fsm_mem_free(ici_msg);
   fsm_mem_free(macsubhead);
   FRET(pkptr);
}




u32 createLongBsr(FSM_PKT *skb,u32 offset){
	FIN(createLongBsr());
	u32 len,os;
	MAC_CE_longBSR *m_long_bsr=(MAC_CE_longBSR*)fsm_mem_alloc(sizeof(MAC_CE_longBSR));
	m_long_bsr->m_buffersize1=5;
	m_long_bsr->m_buffersize2=259;	//1,16,4,3
	len=sizeof(MAC_CE_longBSR);
	fsm_mem_cpy(skb->data+offset,m_long_bsr,len);
	os=offset+len;
	FRET(os);
}

u32 createCRnti(FSM_PKT *skb,u32 offset){
	FIN(createCRnti());
	u32 len,os;
	MAC_CE_Crnti *m_crnti=(MAC_CE_Crnti*)fsm_mem_alloc(sizeof(MAC_CE_Crnti));
	m_crnti->m_crnti-offset%10;
	len=sizeof(MAC_CE_Crnti);
	fsm_mem_cpy(skb->data+offset,m_crnti,len);
	os=offset+len;
	FRET(os);
}


u32 createHead(FSM_PKT *skb,u32 control_numb,u32 data_numb,char typ){
	FIN(createHead());	

	u32 i=0;
	u32 lcid=29;
	u32 len=0,from_len=0;
	u32 data_len=0;
	//char typ=1;//type=1 ¡Àšªšº?RAR type=2¡Àšªšº?dataPDU
	char* data1="hello MAC one";
	MAC_SDU_subhead_last *last_subhead=(MAC_SDU_subhead_last*)fsm_mem_alloc(sizeof(MAC_SDU_subhead_last));
	MAC_SDU_subhead_7bit *subhead_7bit=(MAC_SDU_subhead_7bit*)fsm_mem_alloc(sizeof(MAC_SDU_subhead_7bit));
	
	PHYadaptertoMAC_IciMsg *m_phy_ici=(PHYadaptertoMAC_IciMsg*)fsm_mem_alloc(sizeof(PHYadaptertoMAC_IciMsg));
	fsm_mem_set(m_phy_ici,0,sizeof(PHYadaptertoMAC_IciMsg));
	m_phy_ici->tcid=2;
	m_phy_ici->rnti=61;
	//m_phy_ici->MessageType=0;
	len=sizeof(PHYadaptertoMAC_IciMsg);
	fsm_mem_cpy(skb->head,m_phy_ici,len);

	//len=sizeof(char);
	//fsm_mem_cpy(skb->data+from_len,&typ,len);
	//from_len+=len;
	//fsm_printf("ORIGENAL DATA:\n");
	for(i=0;i<control_numb-1;i++){
		if(i%2==0){
			last_subhead->m_lcid_e_r_r=62;
			len=sizeof(MAC_SDU_subhead_last);
			//fsm_mem_cpy(skb->data+from_len,last_subhead,len);
			fsm_mem_cpy(fsm_skb_put(skb,len),last_subhead,len);
			from_len=from_len+len;

			fsm_printf("%c,",last_subhead->m_lcid_e_r_r);
		}
		else{
			last_subhead->m_lcid_e_r_r=59;
			len=sizeof(MAC_SDU_subhead_last);
			//fsm_mem_cpy(skb->data+from_len,last_subhead,len);
			fsm_mem_cpy(fsm_skb_put(skb,len),last_subhead,len);
			from_len=from_len+len;

			fsm_printf("%c,",last_subhead->m_lcid_e_r_r);
		}
	}
	last_subhead->m_lcid_e_r_r=30;
	len=sizeof(MAC_SDU_subhead_last);
	//fsm_mem_cpy(skb->data+from_len,last_subhead,len);
	fsm_mem_cpy(fsm_skb_put(skb,len),last_subhead,len);
	from_len=from_len+len;
	//fsm_printf("%c\n",last_subhead->m_lcid_e_r_r);

/*	return from_len;*/
/*	for(i=0;i<data_numb-1;i++){	//SDU ¡Áš®šª¡€
		fsm_mem_set(subhead_7bit,0,sizeof(MAC_SDU_subhead_7bit));
		subhead_7bit->m_lcid_e_r_r=37;
		len=14;
		subhead_7bit->m_f_l=len;
		//data_len=data_len+len;
		len=sizeof(MAC_SDU_subhead_7bit);
		fsm_mem_cpy(skb->data+from_len,subhead_7bit,len);
		from_len=from_len+len;
	}
	fsm_mem_set(subhead_7bit,0,len);
	subhead_7bit->m_lcid_e_r_r=5;
	len=14;
	subhead_7bit->m_f_l=len;
	//data_len=data_len+len;
	len=sizeof(MAC_SDU_subhead_7bit);
	fsm_mem_cpy(skb->data+from_len,subhead_7bit,len);
	from_len=from_len+len;*/

	for(i=0;i<control_numb-1;i++){
		if(i%2==0){
			len=createLongBsr(skb,from_len);
			from_len=len;
		}
		else{
			len=createCRnti(skb,from_len);
			from_len=len;
		}
	}
	len=createLongBsr(skb,from_len);
	from_len=len;
	/*for(i=0;i<data_numb;i++){
		fsm_mem_cpy(skb->data+from_len,data1,14);
		from_len+=14;
	}*/
	
	FRET(from_len);
	//FOUT;
}

static void createmachead7bit(MAC_SDU_subhead_7bit *macsubhead,u8 lcid,u8 sdu_len,u8 continueflag)	
{
   FIN(createmachead7bit());
   if(1==continueflag)
     macsubhead->m_lcid_e_r_r=lcid+0x20;//E???2????1
   if(0==continueflag)
     macsubhead->m_lcid_e_r_r=lcid;
   macsubhead->m_f_l=sdu_len;
   FOUT;
}

static void msgFromCCCH(FSM_PKT* skb){
	RRCConnectionRequest rrc_req;
	PHYadaptertoMAC_IciMsg *ici_to_mac=(PHYadaptertoMAC_IciMsg*)fsm_mem_alloc(sizeof(PHYadaptertoMAC_IciMsg));
	MAC_SDU_subhead_7bit *mac_7bit_subhead=(MAC_SDU_subhead_7bit *)fsm_mem_alloc(sizeof(MAC_SDU_subhead_7bit));
	fsm_mem_set(ici_to_mac,0,sizeof(PHYadaptertoMAC_IciMsg));
	fsm_mem_set(mac_7bit_subhead,0,sizeof(MAC_SDU_subhead_7bit));
	u32 cntt1=512;
	u32 len=sizeof(u32);
	u32 cntt2=1;

	rrc_req.type=1;
	//rrc_req.ue_Identity=cntt1;
	rrc_req.establishmentCause=highPriorityAccess;
	fsm_mem_set(&(rrc_req.ue_Identity),0,sizeof(rrc_req.ue_Identity));
	//fsm_mem_cpy(&(rrc_req.ue_Identity.s_TMSI),&cntt1,len);
	rrc_req.ue_Identity.s_TMSI.m_TMSI=cntt1;
	rrc_req.ue_Identity.s_TMSI.mmec=cntt2;
	//fsm_printf("[HEXI]UE ID AND ESTABLUSHMENT CAUSE IN CONCTRUCTOIN:%d,%d,%d\n",rrc_req.ue_Identity.s_TMSI.mmec,rrc_req.ue_Identity.s_TMSI.m_TMSI,rrc_req.establishmentCause);
	/*len=sizeof(short);
	fsm_mem_cpy(&(rrc_req.establishmentCause),&cntt2,len);*/
	len=sizeof(RRCConnectionRequest);
	ici_to_mac->rnti= 61; 
	ici_to_mac->tcid= 2;
	//ici_to_mac->Ue_Info
	createmachead7bit(mac_7bit_subhead,0,len,0);
	len=sizeof(RLCtoMAC_IciMsg);
	fsm_mem_cpy(skb->head,ici_to_mac,len);
	len=sizeof(MAC_SDU_subhead_7bit);
	fsm_mem_cpy(fsm_skb_put(skb,len),mac_7bit_subhead,len);
	len=sizeof(RRCConnectionRequest);
	fsm_mem_cpy(fsm_skb_put(skb,len),&rrc_req,len);

	fsm_pkt_send(skb,STRM_TO_RLCMAC);
	//fsm_printf("[srio][msgFromCCCH][-->]MSG3 has sent to MAC.\n");
}


static void skbFromRlc(FSM_PKT* pkptr)
{
	FIN(skbFromRlc());
	u32 len=0,from_len=0;
	RLCtoMAC_IciMsg *ici_to_mac=(RLCtoMAC_IciMsg*)fsm_mem_alloc(sizeof(RLCtoMAC_IciMsg));
	char *sdu_data="hello world";
	MAC_SDU_subhead_7bit *mac_7bit_subhead=(MAC_SDU_subhead_7bit *)fsm_mem_alloc(sizeof(MAC_SDU_subhead_7bit));
	//FIN(test_send_msg4());
	//fsm_printf("[SRIO] enter test_send_msg4");
	//pkptr = fsm_pkt_get();
	//fsm_pkt_destroy(pkptr);


	//pkptr = fsm_pkt_create(128);
	//fsm_skb_reserve(pkptr ,sizeof(RLCtoMAC_IciMsg));//?š¢?šª¡€2?ŠÌ????? ¡€?ICI
	//ici_to_mac->tcid= 2;
	//ici_to_mac->MessageType =1; 
	ici_to_mac->rnti= 61; 
	ici_to_mac->len=sizeof(MAC_SDU_subhead_7bit);
	ici_to_mac->pbCh=2;
	len=sizeof(RLCtoMAC_IciMsg);
	fsm_mem_cpy(pkptr->head,ici_to_mac,len);//¡€?šš?šª¡€2?

	createmachead7bit(mac_7bit_subhead,5,12,0);
	fsm_mem_cpy(pkptr->head+len,mac_7bit_subhead,sizeof(MAC_SDU_subhead_7bit));
	//msg4_add_MacCR_element(pkptr,12);//š¬šª?š®MACŠÌ?šºy?YŠÌ?SK_BUF?D
	fsm_mem_cpy(fsm_skb_put(pkptr,12),sdu_data,12);
	fsm_mem_free(ici_to_mac);//šºšª¡€??š²??
	fsm_pkt_send(pkptr,STRM_TO_RLCMAC);
	//š¬šª?š®RRC šºy?YŠÌ?SK_BUF?D  
	
FOUT;
}

static void recv_tasklet_handler(char *checkaddr){
/**********************************************************/
	UEPHYADPtoPHYType2 uetype2;
	UE_DL_TYPE2_PBCH_D DL_TYPE2_PBCH_D;
	UE_DL_TYPE2_PHICH_D DL_TYPE2_PHICH_D;
	UE_DL_TYPE2_PDCCH_C DL_TYPE2_PDCCH_C;
	void *PDCCH_D = NULL;
	UE_DL_TYPE2_PDSCH_C DL_TYPE2_PDSCH_C;
	void *PDSCH_D = NULL;

	//TYPE2 head
	uetype2.GHead.NewFlag = *((u32 *)(checkaddr));//32bit
//	printk("NewFlag = %#x   ",uetype2.GHead.NewFlag);
	uetype2.GHead.SFN = *((u16 *)(checkaddr + 4));//16bit
//	printk("SFN = %#x   ",uetype2.GHead.SFN);
	uetype2.GHead.SubframeN = *((u16 *)(checkaddr + 6));//16bit
	printk("%#x   ",uetype2.GHead.SubframeN);
	if(uetype2.GHead.SubframeN == 9)
	printk("\n");
	uetype2.DL_TYPE2_PUBLIC_C.PDSCHLength = *((u32 *)(checkaddr + 8));//32bit
//	printk("PDSCHOffset = %#x\n",uetype2.DL_TYPE2_PUBLIC_C.PDSCHLength);
	uetype2.DL_TYPE2_PUBLIC_C.PDCCHOffset = *((u32 *)(checkaddr + 12));//32bit
//	printk("PDCCHOffset = %#x   ",uetype2.DL_TYPE2_PUBLIC_C.PDCCHOffset);
	//PBCH_D para
	DL_TYPE2_PBCH_D.SourcePBCH = *((u32 *)(checkaddr + 16));//32bit
//	printk("SourcePBCH = %#x   ",DL_TYPE2_PBCH_D.SourcePBCH);
	//PHICH_D para
	DL_TYPE2_PHICH_D.HARQIndex = *((u32 *)(checkaddr + 20));//32bit
//	printk("HARQIndex = %#x   ",DL_TYPE2_PHICH_D.HARQIndex);
	//PDCCH_C para
	DL_TYPE2_PDCCH_C.HARQprocessID = *((u32 *)(checkaddr + 24));//32bit
//	printk("HARQprocessID = %#x\n",DL_TYPE2_PDCCH_C.HARQprocessID);
	DL_TYPE2_PDCCH_C.RV = *((u32 *)(checkaddr + 28));//32bit
//	printk("RV = %#x   ",DL_TYPE2_PDCCH_C.RV);
	DL_TYPE2_PDCCH_C.NDI = *((u16 *)(checkaddr + 32));//16bit
//	printk("NDI = %#x   ",DL_TYPE2_PDCCH_C.NDI);
	DL_TYPE2_PDCCH_C.padding = *((u16 *)(checkaddr + 34));//16bit
//	printk("padding = %#x   ",DL_TYPE2_PDCCH_C.padding);
	//PDCCH_D para 64bit
//	PDCCH_D = checkaddr + uetype2.DL_TYPE2_PUBLIC_C.PDCCHOffset;
	PDCCH_D = (u64 *)(checkaddr + 36);
//	printk("PDCCH_D = %#llx   ",*((u64 *)PDCCH_D));
	//PDSCH_C para
	DL_TYPE2_PDSCH_C.CRC = *((u32 *)(checkaddr + 44));//32bit
//	printk("CRC = %#x\n",DL_TYPE2_PDSCH_C.CRC);
	//PDSCH_D 
	PDSCH_D = (u32 *)(checkaddr + 48);
//	printk("PDSCH_D : ");
/*	for(i = 0;i < uetype2.DL_TYPE2_PUBLIC_C.PDSCHLength;i ++)
	{
		printk("%x ",*((unsigned char *)(PDSCH_D + i)));
		 if(i == 16)
		{
//			printk("\n");
//			printk("*****************************************************************\n");
			break;
		}
	}*/
		
}


