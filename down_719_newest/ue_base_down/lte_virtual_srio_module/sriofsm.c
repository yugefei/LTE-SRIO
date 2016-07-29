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
#include "sriofsm.h"
#include "../lte_system.h"
#include "pkfmt.h"
#include "rrc_type.h"
#include "rrc_type_IEs.h"
#include <linux/string.h>
#include "queue.h"

//	¶¨Òå×´Ì¬»úÖÐµÄ×´Ì¬
/**********20141013 mf modified ************************/
#define ST_INIT	0
#define ST_CFG		1
#define	ST_IDLE	2
#define ST_SEND	3
#define ST_RECV	4
#define ST_SEND_TYPE1_TO_SRIO		5
#define ST_RECV_TYPE2_FROM_SRIO	6
#define ST_PRINT_INFO 7
//#define ST_TEST	4	//²âÊÔ½×¶ÎÌí¼ÓTEST×´Ì¬£¬ÓÃÓÚ½ÓÊÕMSG3·¢ËÍMSG4	modified by MF 20140715
/**********end modified ************************/


//	¶¨ÒåÎïÀíÊÊÅä²ã±¾Éí²âÊÔÓÃIOControlÃüÁî
#define IOCCMD_PSEND_RUN			0x01
#define IOCCMD_PSEND_STOP			0x02
#define IOCCMD_PSEND_INTERVAL	0x03 
#define IOCCMD_SAY_HELLO			0x04

//	¶¨ÒåUE²àMAC²ã¶ÔÎïÀíÊÊÅä²ãµÄIOControlÃüÁî
#define IOCCMD_MACtoPHY_RNTI_Indicate			0x24      //·¢ËÍMSG3Ö®Ç° MAC²ã¸æÖªÊÊÅä²ãRNTIÖµ
#define IOCCMD_MACtoPHY_Preamble_Indicate		0x25      //MSG1
#define IOCCMD_MACtoPHY_recv_sysinfo			0x26      //RRC¸æÖªMAC MAC¸æÖªÊÊÅä²ã¿ªÊ¼½ÓÊÕÏµÍ³ÏûÏ¢
#define IOCCMD_MACtoPHY_stop_recv_sysinfo		0x27      //RRC¸æÖªMAC MAC¸æÖªÊÊÅä²ãÍ£Ö¹½ÓÊÕÏµÍ³ÏûÏ¢
#define IOCCMD_MACtoPHY_recv_paging				0x46      //RRC¸æÖªMAC MAC¸æÖªÊÊÅä²ã¿ªÊ¼½ÓÊÕÑ°ºôÏûÏ¢
/************20141013 mf modified**************/
#define IOCCMD_PHYtoMAC_RA_Req				0x03		//With data format S_RAinfo
#define IOCCMD_PHYtoMAC_TA					0x06


/************end modify************************/
//	¶¨ÒåUE²àÎïÀíÊÊÅä²ã¶ÔMAC²ãµÄIOControlÃüÁî
#define IOCCMD_Harq_feedback					0x18   //when MAC received this command from PHYadapter,MAC 
#define IOCCMD_PDCCHtoMAC_RandomAcc_Req		0x0C   //PDCCHÉÏ ¸æÖªMAC¿ªÊ¼Ëæ»ú½ÓÈë
#define IOCCMD_PDCCHtoMAC_ULGRANT			0x0D   //PHY send a DCI of ul_grant to MAC 
#define IOCCMD_TEST_SEND_MSG3				0x51  //ÊÕµ½IOControlºó£¬·¢ËÍMSG3£¬²âÊÔÃüÁî modified by MF 20140715
/*******20141017 mf modified for test******/
#define IOCCMD_TEST_SEND_TO_ETH				0x52

/***********20141013 mf modified RRC ioctl****************/
#define IOCCMD_RRCtoPHY_Type1_Indicate      0x60
/***********20141108 mf modified**************************/
#define IOCCMD_PDCCHtoMAC_ULGRANT			 0x0D
#define IOCCMD_PHYtoMAC_SYSFRAME            0x0E

#define IOCCMD_SEND_TO_SRIO	0x4E
#define IOCCMD_READ_MEM		0x4F
#define IOCCMD_RA_COMPLETE	0x48
#define IOCCMD_RIODT_STOP	0x4D
#define IOCCMD_LOST_PKT_COUNT	0x4C

/************end modify************************/

#define MemoryStart				0xfc10000
#define MemorySize					10240
#define IOCCMD_SEND_INTERVAL_ADD  0x66
#define IOCCMD_SEND_INTERVAL_MINUS  0x67
#define IOCCMD_PRINT_PKT_FROM_MAC           0x68
#define IOCCMD_STOP_TIMER          0x888
#define IOCCMD_SEND_INFO           0x889


static void init_enter(void);
static void send_packet_period(void);
static void srio_sv_init(void);	
static void srio_close(void);
/********mf modified 20141017 for test******/
static void packet_send_to_eth(void);

//static void packet_send_to_eth(FSM_PKT* pkptr);
static void packet_send_to_upperlayer(void);
static void idle_exit(void);
static void idle_ioctl_handler(void);
void print_tran_info( const char *str);
/**********20141013 mf modified****************************/
static void cfg_ioctl_handler(void);
//static void send_type1(void);
static void recv_tasklet_handler(char* buffer);


static void print_info(void);
//	²âÊÔº¯ÊýÉùÃ÷

static void ioctldata();

/********mf modified 20141017 for test******/
static void test_send_to_eth(void);

static void test_send_msg1(void);

static void test_send_sf(void);
static void type1_pkt_assemble(void);
static void type1_pkt_assemble_test(void);

static void type1_send_to_srio(void);
static void type2_recv_from_srio(void);
static void read_mem(void);

extern unsigned int GetFrameNo(void);
extern unsigned int GetsubFrameNo(void);
extern LinkQueue UnionQueue;
extern void* mapaddr;
extern void rio_hrtimer1_stop_wrapper(void);
extern void send_dbell(u16 sub);
extern int memread(unsigned long readaddr,unsigned int length);
/********************************************************************************
** Function name: srio_main
** Description: ÎïÀíÊÊÅä²ãµÄ×´Ì¬»úÖ÷º¯Êý
** Input:
** Output:
** Returns:
** Created by:
** Created Date:
** ------------------------------------------------------------------------------
** Modified by: MF
** Modified Date: 20141013
** Modefied Description: Ìí¼ÓCFGÌ¬ÓÃÓÚµÈ´ýRRCµÄType1ÅäÖÃ
********************************************************************************/

void srio_main(void)
{
	FSM_ENTER(srio_main);
	FSM_BLOCK_SWITCH
	{
		FSM_STATE_FORCED(ST_INIT, "INIT", srio_sv_init(), )
		{
			FSM_TRANSIT_FORCE(ST_IDLE, , "default", "", "INIT -> IDLE"); 
		}
		FSM_STATE_UNFORCED(ST_IDLE, "IDLE",,)		
		{
			FSM_COND_TEST_IN("IDLE")				
				FSM_TEST_COND(SRIO_PK_FROM_LOWER)				
				FSM_TEST_COND(SRIO_PK_FROM_UPPER)
				FSM_TEST_COND(SRIO_CLOSE)
				FSM_TEST_COND(PACKET_SEND_PERIOD)
				FSM_TEST_COND(TYPE1_SEND_TO_SRIO)
				FSM_TEST_COND(TYPE2_RECV_FROM_SRIO)
				FSM_TEST_COND(PRINT_INFO)
			FSM_COND_TEST_OUT("IDLE")	
			FSM_TRANSIT_SWITCH			
			{	
				FSM_CASE_TRANSIT(0, ST_RECV, , "IDLE -> RECV")	//Å“Ã“ÃŠÃœÃÃ‚Â²Ã£ÃÃ…ÃÂ¢			
				FSM_CASE_TRANSIT(1, ST_SEND, , "IDLE -> SEND") //Â·Â¢Ã‹ÃÃ‰ÃÂ²Ã£ÃÃ…ÃÂ¢
				FSM_CASE_TRANSIT(2, ST_INIT,idle_exit() , "IDLE -> INIT") //Ã—Å½ÃŒÂ¬Â»ÃºÃÃ‹Â³Ã¶
				FSM_CASE_TRANSIT(3, ST_IDLE,send_packet_period(), "IDLE->IDLE")//Â¶Å¡ÃŠÂ±Ã†Ã·Ã–ÃœÃ†ÃšÂ·Â¢Ã‹Ã
				FSM_CASE_TRANSIT(4, ST_SEND_TYPE1_TO_SRIO, , "IDLE -> SEND_TYPE1_TO_SRIO")
				FSM_CASE_TRANSIT(5, ST_RECV_TYPE2_FROM_SRIO, , "IDLE -> RECV_TYPE2_FROM_SRIO")
				FSM_CASE_TRANSIT(6, ST_IDLE,print_info(),"IDLE -> IDLE")
				FSM_CASE_DEFAULT(ST_IDLE,idle_ioctl_handler(), "IDLE->IDLE")	//iocontrol
			}	
		}
		FSM_STATE_FORCED(ST_RECV, "RECV", packet_send_to_upperlayer(), )
		{
			FSM_TRANSIT_FORCE(ST_IDLE, , "default", "", "RECV -> IDLE");
		}
		FSM_STATE_FORCED(ST_SEND, "SEND", packet_send_to_eth(), )   //20141018 for test
		{
			FSM_TRANSIT_FORCE(ST_IDLE, , "default", "", "SEND -> IDLE");
		}
		FSM_STATE_FORCED(ST_SEND_TYPE1_TO_SRIO, "SEND_TYPE1_TO_SRIO", type1_send_to_srio(), )   //20141029 for test
		//FSM_STATE_FORCED(ST_SEND, "SEND", print_tran_info("[MF]STATE:SEND\n"), )
		{
			FSM_TRANSIT_FORCE(ST_IDLE, , "default", "", "SEND_TYPE1_TO_SRIO -> IDLE");
		}
		
		FSM_STATE_FORCED(ST_RECV_TYPE2_FROM_SRIO, "RECV_TYPE2_FROM_SRIO", type2_recv_from_srio(), )   //20141029 for test
		//FSM_STATE_FORCED(ST_SEND, "SEND", print_tran_info("[MF]STATE:SEND\n"), )
		{
			FSM_TRANSIT_FORCE(ST_IDLE, , "default", "", "RECV_TYPE2_FROM_SRIO -> IDLE");
		}
	}
	FSM_EXIT(0)
}

/********************************************************************************
** Function name: init_enter
** Description: ×´Ì¬»ú³õÊ¼»¯º¯Êý
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
		fsm_schedule_self(0, _START_WORK);
	}
	FOUT;
}

/********************************************************************************
** Function name: srio_sv_init
** Description: ¡Á?¨¬??¨²¨¨???¡À?¨¢?3?¨º??¡¥o¡¥¨ºy
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
	SV(recv_interval)=377;
	SV(send_interval)=777;
	SV(recv_pkt_from_enb)=0;
	/*********20141013 mf modified*************/
	//SV(type1_cnt) = 0;
	SV(sfn) = 0;
	SV(subframeN) = 0;
	SV(racomplete) = false;
	memset((char *)(rtn_mmap() + 0x200000+cache_size*2), 0, cache_size);
	init_enter();
	for (i = 0; i < MAX_STORED_PKT; i ++){
		fsm_mem_set(&SV(pkts[i]), 0, sizeof(FSM_PKT*));
	}
	SV(stored_pkt_count) = 0;
	SV(recv_upper_pkt_num) = 0;
	SV(pre_pkt_no) = 0;
	SV(lost_pkt_count) = 0;
	FOUT;//
}

/********************************************************************************
** Function name: srio_close
** Description: ×´Ì¬»ú¹Ø±Õº¯Êý
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
** Description: ÊÕµ½ÉÏ²ã·¢µÄÊý¾Ý°ü£¬ÏÂ·¢µ½ÒÔÌ«Íø(²âÊÔÓÃ)
** Input:
** Output:
** Returns:
** Created by:
** Created Date:
** ------------------------------------------------------------------------------
** Modified by: MF
** Modified Date: 20140717
** Modified Description: Ö±½ÓÏú»Ù°ü ²»·¢ËÍ³öÈ¥ ²âÊÔÓÃ
********************************************************************************/
/***** mf modified 20141017 for test**************/
static void packet_send_to_eth(void)
{
	FSM_PKT* pkptr;
	FSM_PKT* pkptrcopy;
	struct lte_test_srio_head* sh_ptr;
	struct ethhdr* head_ptr;
	char dst_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	int skb_len;
	u32 len;
	static int pkt_no=0;
	FIN(packet_send_to_eth());
	SV_PTR_GET(srio_sv);
	//printk("a pkt from upper layer\n");
	pkptr = fsm_pkt_get();
	skb_len = pkptr->tail - pkptr->data;//20150123
	fsm_printf("[UE SRIO]enter packet_send_to_eth, and the skb_buffer len is %d\n", skb_len);
	pkptrcopy = fsm_pkt_create(skb_len+64);//20150123
	fsm_skb_put(pkptrcopy, skb_len);//20150123
	fsm_mem_cpy(pkptrcopy->data,pkptr->data,skb_len);//20150123
		//fsm_pkt_destroy(pkptr);
		
		MACtoPHYadapter_IciMsg* MactoPhyICI=(MACtoPHYadapter_IciMsg*)fsm_mem_alloc(sizeof(MACtoPHYadapter_IciMsg));

		fsm_mem_cpy(MactoPhyICI, (MACtoPHYadapter_IciMsg *)(pkptr->head), sizeof(MACtoPHYadapter_IciMsg));
		//fsm_printf("[DAFANGZI]The RNTI of the packet is %d\n",MactoPhyICI->rnti );
		
		fsm_pkt_destroy(pkptr);
		//fsm_printf("[UE SRIO]destroy original pkptr\n");
		if(pkptrcopy != NULL)
		{
			if(fsm_skb_headroom(pkptrcopy) < (ETH_HLEN + sizeof(struct lte_test_srio_head)))
			{
				pkptrcopy = fsm_skb_realloc_headeroom(pkptr,sizeof(struct lte_test_srio_head));
				if(pkptrcopy == NULL)
					return;
			}
			fsm_skb_push(pkptrcopy, sizeof(struct lte_test_srio_head));
			sh_ptr = (struct lte_test_srio_head*)pkptrcopy->data;
			sh_ptr->type = fsm_htonl(2);
			sh_ptr->len = fsm_htonl(pkptrcopy->len-sizeof(struct lte_test_srio_head));
			sh_ptr->rnti = MactoPhyICI->rnti;
			fsm_skb_push(pkptrcopy, ETH_HLEN);
			head_ptr = (struct ethhdr*)pkptrcopy->data;
			fsm_mem_cpy(head_ptr->h_dest, dst_addr, ETH_ALEN);
			fsm_mem_cpy(head_ptr->h_source, fsm_intf_addr_get(STRM_TO_ETH), ETH_ALEN);
			head_ptr->h_proto = fsm_htons(DEV_PROTO_SRIO);		
			len = pkptrcopy->len;
			fsm_printf("[SRIO][send to eth]data len:%d\n",pkptrcopy->len);
			fsm_octets_print(pkptrcopy->data,pkptrcopy->len);	
			fsm_pkt_send(pkptrcopy,STRM_TO_ETH); //20150429
			SV(packet_count)++;
		}
		fsm_mem_free(MactoPhyICI); //liu ying tao and liu hanli 
FOUT;
}
	
/********************************************************************************
** Function name: packet_send_to_upperlayer
** Description: ¨º?¦Ì???2?¡¤¡é¦Ì?¨ºy?Y¡ã¨¹¡ê??¨°¨¦?¡¤¡é?¨ª¦Ì?MAC2?(2a¨º?¨®?)
** Input:
** Output:
** Returns:
** Created by:
** Created Date:
** ------------------------------------------------------------------------------
** Modified by: MF
** Modified Date: 20140717
** Modified Description: ?¡À?¨®?¨²?¨´¡ã¨¹ 2?¡¤¡é?¨ª3?¨¨£¤ 2a¨º?¨®?
********************************************************************************/
static void packet_send_to_upperlayer(void)
{
	FSM_PKT* pkptr;
	MACtoPHYadapter_IciMsg * ici_to_phyadapter;
	PHYadaptertoMAC_IciMsg * ici_to_mac;
	Regular_ULgrant * uldci_to_mac;
	UEPHY_TO_MAC_ULgrant * ulgrand_to_mac;
	u32 num = 1;
	struct lte_test_srio_head* sh_ptr;
	FIN(packet_send_to_upperlayer());
	SV_PTR_GET(srio_sv);
	if (SV(racomplete) == true)
	{
		type2_recv_from_srio();
	}
	else
	{
		pkptr = fsm_pkt_get();
		sh_ptr = (struct lte_test_srio_head*)pkptr->data;
		fsm_skb_pull(pkptr, sizeof(struct lte_test_srio_head));
		int i,j;
		SV(recv_count)++;
		
		if(fsm_ntohs(sh_ptr->rnti) >= 81)
		{
			fsm_printf("[UE SRIO]RNTI = %d,destroy\n",fsm_ntohs(sh_ptr->rnti));
			fsm_pkt_destroy(pkptr);
		}
		else
		{
			if(fsm_ntohl(sh_ptr->type) == 2)
			{
				ici_to_mac=(PHYadaptertoMAC_IciMsg*)fsm_mem_alloc(sizeof(PHYadaptertoMAC_IciMsg));
				ici_to_mac->tcid=2;
				ici_to_mac->rnti=fsm_ntohs(sh_ptr->rnti);
				ici_to_mac->frameNo = fsm_ntohs(sh_ptr->sfn);
				ici_to_mac->subframeNo = fsm_ntohs(sh_ptr->subframeN);
				fsm_printf("[UE SRIO]The rnti of the packet is %u, sending to MAC\n", ici_to_mac->rnti);
				fsm_mem_cpy(pkptr->head,ici_to_mac,sizeof(PHYadaptertoMAC_IciMsg));
				fsm_mem_free(ici_to_mac);
				//fsm_printf("[HEXI]TYPE IN SRIO:%c\n",*((char*)pkptr->data)+65);
				fsm_pkt_send(pkptr, STRM_TO_RLCMAC);
				fsm_printf("[srio][send to mac]data->len:%d\n",pkptr->len);
				fsm_octets_print(pkptr->data,pkptr->len);	
			}
			else if(fsm_ntohl(sh_ptr->type) == 1)
			{
				//fsm_skb_pull(pkptr, sizeof(struct lte_test_srio_head));
				fsm_printf((char*)pkptr->data);
				fsm_printf("\n");
				fsm_pkt_destroy(pkptr);
			}
			else if(fsm_ntohl(sh_ptr->type) == 3)
			{
				i=pkptr->tail-pkptr->data;
				uldci_to_mac = (struct Regular_ULgrant *)pkptr->data;
				u32 uld = 0;
				fsm_mem_cpy(&uld, uldci_to_mac, sizeof(u32));
				ulgrand_to_mac = fsm_mem_alloc(sizeof(UEPHY_TO_MAC_ULgrant));
				ulgrand_to_mac->m_rnti = fsm_ntohs(sh_ptr->rnti);
				ulgrand_to_mac->frameNo = fsm_ntohs(sh_ptr->sfn);
				ulgrand_to_mac->subframeNo = fsm_ntohs(sh_ptr->subframeN);
				fsm_mem_cpy(&(ulgrand_to_mac->s_ul_dci), uldci_to_mac, sizeof(Regular_ULgrant));
				fsm_do_ioctrl(STRM_TO_RLCMAC,IOCCMD_PDCCHtoMAC_ULGRANT,(void *)ulgrand_to_mac,sizeof(UEPHY_TO_MAC_ULgrant));
				fsm_mem_free(ulgrand_to_mac);
				fsm_pkt_destroy(pkptr);
			}
			else 
			fsm_pkt_destroy(pkptr);
		}
	}

FOUT;
}

static void type2_recv_from_srio(void)
	{
	FIN(type2_recv_from_srio());
	int offset=0x2800;
	int flag=-1;
	char *ptr;
	flag=read_type2_mem();
	if(flag!=-1)
	{		
			ptr=(char *)fsm_mem_alloc(10240);
			fsm_mem_cpy(ptr,mapaddr+flag*offset+0x800,0x2800);
			*(u32*)(mapaddr+flag*offset+0x800)=0;
			//printk("success get data ! type2_recv_from_srio\n ");
			recv_tasklet_handler(ptr);
	}
	fsm_schedule_self(100, _TYPE2_RECV_FROM_SRIO);
	FOUT;
}

/********************************************************************************
** Function name: idle_exit
** Description: ¹Ø±ÕsrioÄ£¿é
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
	}
	FOUT;
}

/********************************************************************************
** Function name: send_packet_period
** Description: ÖÜÆÚÏòÒÔÌ«Íø·¢°ü(²âÊÔÓÃ)
** Input:
** Output:
** Returns:
** Created by: ÕÅÖ¾Ç¿
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
	//struct PHYadaptertoMAC_IciMsg * ici_to_mac;
	struct ethhdr* head_ptr;
	
	char* data = "send_packet_period says hello world!";
	char dst_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	
	FIN(send_packet_period());
	SV_PTR_GET(srio_sv);
	if(PACKET_SEND_PERIOD)
	{
		pkptr = fsm_pkt_create(128);
		fsm_skb_put(pkptr, 64);
		fsm_mem_cpy(pkptr->data, data, 24);
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
		skb_reset_network_header(pkptr);
		fsm_skb_push(pkptr, ETH_HLEN);
		head_ptr = (struct ethhdr*)pkptr->data;
		fsm_mem_cpy(head_ptr->h_dest, dst_addr, ETH_ALEN);
		fsm_mem_cpy(head_ptr->h_source, fsm_intf_addr_get(STRM_TO_ETH), ETH_ALEN);
		head_ptr->h_proto = fsm_htons(DEV_PROTO_SRIO);
		//fsm_printf("set new timer\n");
		//fsm_printf("timer event is added\n");
		SV(psend_handle) = fsm_schedule_self(SV(interval), _PACKET_SEND_PERIOD);
		fsm_pkt_send(pkptr,STRM_TO_ETH);
		//fsm_pkt_destroy(pkptr);
		++SV(packet_count);
		fsm_printf("Node0 sends hello world packet.\n");
	}
	FOUT;
}

static void type1_pkt_assemble_test(void)
{
	FIN(type1_pkt_assemble_test());
	FSM_PKT* pkptr=NULL;
	FSM_PKT* pkptrfrommac=NULL;
	u16 data_len=0;
	MACtoPHYadapter_IciMsg* MactoPhyICI=NULL;
	u16 sysframenum = 0;
	u16 subframenum = 0;
	int len=0;
	u32 tmp_len=0;
	UEULPHYADPtoPHYType1 type1public;
	UE_UL_TYPE1_PUCCH_C type1pucchc;
	UE_UL_TYPE1_PUCCH_D type1pucchd;
	UE_UL_TYPE1_PUSCH_C type1puschc;
	UE_UL_TYPE1_PUSCH_D type1puschd;
	//PUBLIC_C
	//get mac_pkt and mac ici
	SV_PTR_GET(srio_sv);
	pkptrfrommac = fsm_pkt_get();
	SV(recv_upper_pkt_num) ++;
	//fsm_octets_print(pkptrfrommac->data, 100);
	MactoPhyICI = (MACtoPHYadapter_IciMsg*)fsm_mem_alloc(sizeof(MACtoPHYadapter_IciMsg));
	fsm_mem_cpy(MactoPhyICI, (MACtoPHYadapter_IciMsg *)(pkptrfrommac->head), sizeof(MACtoPHYadapter_IciMsg));
	data_len = pkptrfrommac->tail - pkptrfrommac->data;
	//fsm_printf("[UE SRIO]data_len = %d/n", data_len);
	//create len for test
	len = sizeof(struct UEULPHYADPtoPHYType1) + sizeof(struct UE_UL_TYPE1_PUCCH_C) + sizeof(struct UE_UL_TYPE1_PUCCH_D) + 
	sizeof(struct UE_UL_TYPE1_PUSCH_C) +sizeof(struct UE_UL_TYPE1_PUSCH_D) + data_len + sizeof(u32);
	pkptr = fsm_pkt_create(len);
	if (pkptr == NULL)
	{
		fsm_printf("fsm_pkt_create()failed   FOUT\n");
		FOUT;
	}
	sysframenum = (u16)GetFrameNo();
	subframenum = (u16)GetsubFrameNo();
	//printk("[srio]:sysframenum %d,subframe num %d\n",sysframenum,subframenum);
	/*******************time delay***************/
	if(((subframenum>=0) && (subframenum<2))||((subframenum>=7) && (subframenum<10)))
	{
		if((subframenum>=7) && (subframenum<10))
		{
			if(sysframenum!=1023)
			{
				sysframenum++;
			}
			else
			{
				sysframenum=0;
			}
		}
		subframenum=2;
	}
	else
	{
		subframenum=7;
	}
	
	//printk("[srio]:sysframenum %d,subframe num %d\n",sysframenum,subframenum);
	type1public.GHead.NewFlag = 1;//u32
	type1public.GHead.SFN = sysframenum;//u16
	type1public.GHead.SubframeN = subframenum;//u16
	//printk("%u  ",type1public.GHead.SubframeN);
	type1public.UL_TYPE1_PUBLIC_C.PUSCHCOffset = sizeof(UEULPHYADPtoPHYType1) + sizeof(UE_UL_TYPE1_PUCCH_C) + sizeof(UE_UL_TYPE1_PUCCH_D);//u32
	type1public.UL_TYPE1_PUBLIC_C.PUSCHDOffset = sizeof(UEULPHYADPtoPHYType1) + sizeof(UE_UL_TYPE1_PUCCH_C) + sizeof(UE_UL_TYPE1_PUCCH_D) + sizeof(UE_UL_TYPE1_PUSCH_C);//u32
	//memcpy(mapaddr + 0x100800,&type1public,sizeof(UEULPHYADPtoPHYType1));
	//fsm_printf("UEUL %d\n",sizeof(struct UEULPHYADPtoPHYType1));
	fsm_skb_put(pkptr,sizeof(struct UEULPHYADPtoPHYType1));
	fsm_mem_cpy(pkptr->data + tmp_len, &type1public, sizeof(struct UEULPHYADPtoPHYType1));
	//fsm_printf("758");
	tmp_len=tmp_len+sizeof(UEULPHYADPtoPHYType1);
	//PUCCH_C
	type1pucchc.RNTI = 61;//u16
	type1pucchc.UlStates = 0;//u16
	type1pucchc.UlChSel = 000;//u16
	//fsm_printf("764");
	if (sysframenum == 0 && subframenum == 0)
	{
		type1pucchc.PGType = 0;//u16
	}	
	else
	{
		type1pucchc.PGType = 2;//u16
	}
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
	//fsm_printf("789");
	//memcpy(mapaddr + 0x100800 + sizeof(UEULPHYADPtoPHYType1),&type1pucchc,sizeof(UE_UL_TYPE1_PUCCH_C));
	fsm_skb_put(pkptr,sizeof(UE_UL_TYPE1_PUCCH_C));
	fsm_mem_cpy(pkptr->data + tmp_len,&type1pucchc, sizeof(UE_UL_TYPE1_PUCCH_C));
	tmp_len=tmp_len+sizeof(UE_UL_TYPE1_PUCCH_C);
	//PUCCH_D
	type1pucchd.RNTI = 61;//u16
	type1pucchd.UlChSel = 000;//u16
	type1pucchd.SR = 0;//u16
	type1pucchd.HARQ = 0;//u16
	type1pucchd.CQI = 0;//u16
	type1pucchd.padding = 0;//u16
	//memcpy(mapaddr + 0x100800 + sizeof(UEULPHYADPtoPHYType1) + sizeof(UE_UL_TYPE1_PUCCH_C),&type1pucchd,sizeof(UE_UL_TYPE1_PUCCH_D));
	fsm_skb_put(pkptr,sizeof(UE_UL_TYPE1_PUCCH_D));
	fsm_mem_cpy(pkptr->data + tmp_len,&type1pucchd, sizeof(UE_UL_TYPE1_PUCCH_D));
	tmp_len=tmp_len+sizeof(UE_UL_TYPE1_PUCCH_D);
	//PUSCH_C
	type1puschc.RNTI = 61;//u16
	type1puschc.UlStates = 0;//u16
	type1puschc.UlChSel = 000;//u16
	if(sysframenum == 0 && subframenum == 0)
	{
		type1puschc.PGType = 0;//u16
	}
	else
	{
		type1puschc.PGType = 2;//u16
	}
	//fsm_printf("815");
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
	type1puschc.Subfn = 2;//u16
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
	//memcpy(mapaddr + 0x100800 + sizeof(UEULPHYADPtoPHYType1) + sizeof(UE_UL_TYPE1_PUCCH_C) + sizeof(UE_UL_TYPE1_PUCCH_D),&type1puschc,sizeof(UE_UL_TYPE1_PUSCH_C));
	fsm_skb_put(pkptr,sizeof(UE_UL_TYPE1_PUSCH_C));
	fsm_mem_cpy(pkptr->data + tmp_len,&type1puschc, sizeof(UE_UL_TYPE1_PUSCH_C));
	tmp_len=tmp_len+sizeof(UE_UL_TYPE1_PUSCH_C);
	//fsm_printf("852");
	//PUSCH_D
	type1puschd.RNTI = 61;//u16
	type1puschd.UlChSel = 000;//u16
	type1puschd.CQI = 0;//u16
	type1puschd.RI = 0;//u16
	type1puschd.HARQ_ACK = 0;//u32
	//memcpy(mapaddr + 0x100800 + sizeof(UEULPHYADPtoPHYType1) + sizeof(UE_UL_TYPE1_PUCCH_C) + sizeof(UE_UL_TYPE1_PUCCH_D) + sizeof(UE_UL_TYPE1_PUSCH_C),&type1puschd,sizeof(UE_UL_TYPE1_PUSCH_D));
	fsm_skb_put(pkptr,sizeof(UE_UL_TYPE1_PUSCH_D));
	fsm_mem_cpy(pkptr->data + tmp_len,&type1puschd, sizeof(UE_UL_TYPE1_PUSCH_D));
	tmp_len=tmp_len+sizeof(UE_UL_TYPE1_PUSCH_D);
	//PUSCH_D SourcePUSCH
	//memcpy(mapaddr + 0x100800 + sizeof(UEULPHYADPtoPHYType1) + sizeof(UE_UL_TYPE1_PUCCH_C) + sizeof(UE_UL_TYPE1_PUCCH_D) + sizeof(UE_UL_TYPE1_PUSCH_C) + sizeof(UE_UL_TYPE1_PUSCH_D),vxx_tb_buffer,((type1puschc.tbSize + 31)/32)*4);
	fsm_skb_put(pkptr,data_len+6);
	tmp_len+=4;
	fsm_mem_cpy(pkptr->data+tmp_len,&data_len,2);
	tmp_len+=2;
	fsm_mem_cpy(pkptr->data + tmp_len, pkptrfrommac->data, data_len);
	fsm_pkt_destroy(pkptrfrommac);
	fsm_mem_free(MactoPhyICI);
	SV(pkts[SV(stored_pkt_count)]) = pkptr;
	SV(stored_pkt_count)++;
	//fsm_printf("[UE SRIO] packet %d has been stored.\n", SV(stored_pkt_count));
	//fsm_octets_print(pkptr->data,pkptr->len);
	
	spin_lock(&UnionQueue.my_lock);
	//send_dbell(subframenum);
	
	//printk("Current Push Pos is %d\n",UnionQueue.NextData);
	fsm_mem_cpy((char *)(rtn_mmap() + 0x115000 + (UnionQueue.NextData)*0x4000), pkptr->data, pkptr->len);
	if(!Push(&UnionQueue,UnionQueue.NextData))
		           printk("Push failed...\n");	
	spin_unlock(&UnionQueue.my_lock);
	fsm_octets_print(pkptr->data,pkptr->len);
	//printk("a pkt in queue\n");
	fsm_pkt_destroy(pkptr);
	//fsm_mem_free(MactoPhyICI);
	//SV(pkts[SV(stored_pkt_count)]) = pkptr;
	//SV(stored_pkt_count)++;
	//fsm_printf("[UE SRIO] packet %d has been stored.\n", SV(stored_pkt_count));
	//type1_send_to_srio();
	FOUT;
}

static void type1_pkt_assemble(void){
	FIN(type1_pkt_assemble());
	
	FSM_PKT* pkptr;
	FSM_PKT* pkptrfrommac;
	u32 len;
	u32 tmp_len;
	u32 i;
	u16 data_len;
	MACtoPHYadapter_IciMsg* MactoPhyICI;
	ENBPHYADPtoPHYType1 type1head;
	ENB_DL_TYPE1_PBCH_C type1pbchc;
	ENB_DL_TYPE1_PBCH_D type1pbchd;
	ENB_DL_TYPE1_PHICH_C type1phichc[2];
	ENB_DL_TYPE1_PHICH_D type1phichd[2];
	ENB_DL_TYPE1_PDCCH_C type1pdcchc[5];
	ENB_DL_TYPE1_PDCCH_D type1pdcchd[5];
	ENB_DL_TYPE1_PDSCH_C type1pdschc[5];
	ENB_DL_TYPE1_PDSCH_D type1pdschd[5];
	
	fsm_printf("[UE SRIO]Enter type1_pkt_assemble(void)\n");
	SV_PTR_GET(srio_sv);
	pkptrfrommac = fsm_pkt_get();
	SV(recv_upper_pkt_num) ++;
	//fsm_octets_print(pkptrfrommac->data, 100);
	MactoPhyICI = (MACtoPHYadapter_IciMsg*)fsm_mem_alloc(sizeof(MACtoPHYadapter_IciMsg));
	fsm_mem_cpy(MactoPhyICI, (MACtoPHYadapter_IciMsg *)(pkptrfrommac->head), sizeof(MACtoPHYadapter_IciMsg));
	data_len = pkptrfrommac->tail - pkptrfrommac->data;

	fsm_printf("[UE SRIO]data_len = %d/n", data_len);
	//create len for test
	len = sizeof(struct ENBPHYADPtoPHYType1) + sizeof(struct ENB_DL_TYPE1_PBCH_C) + sizeof(struct ENB_DL_TYPE1_PBCH_D) + 
	2 * sizeof(struct ENB_DL_TYPE1_PHICH_C) + 2 * sizeof(struct ENB_DL_TYPE1_PHICH_D) + 5 * sizeof(struct ENB_DL_TYPE1_PDCCH_C)
	 + 5 * sizeof(struct ENB_DL_TYPE1_PDCCH_D) + 5 * sizeof(struct ENB_DL_TYPE1_PDSCH_C) + 5 * sizeof(struct ENB_DL_TYPE1_PDSCH_D) + 5 * data_len + 5 * sizeof(u32);
	pkptr = fsm_pkt_create(len);
			
	if(pkptr != NULL)
	{
		tmp_len = 0;
		type1head.GHead.NewFlag = 1;
		type1head.GHead.SFN = MactoPhyICI->frameNo;
		type1head.GHead.SubframeN = MactoPhyICI->subframeNo;
		type1head.DL_TYPE1_PUBLIC_C.PDSCHNum = 5; 
		type1head.DL_TYPE1_PUBLIC_C.PDCCHNum = 5; 
		type1head.DL_TYPE1_PUBLIC_C.NumOfUEForPHICH = 2;
		type1head.DL_TYPE1_PUBLIC_C.Zero = 0;
		type1head.DL_TYPE1_PUBLIC_C.PBCH_C_Offset = sizeof(ENBPHYADPtoPHYType1);
		type1head.DL_TYPE1_PUBLIC_C.PBCH_D_Offset = type1head.DL_TYPE1_PUBLIC_C.PBCH_C_Offset + sizeof(ENB_DL_TYPE1_PBCH_C);
		type1head.DL_TYPE1_PUBLIC_C.PHICH_C_Offset =type1head.DL_TYPE1_PUBLIC_C.PBCH_D_Offset + sizeof(ENB_DL_TYPE1_PBCH_D);
		type1head.DL_TYPE1_PUBLIC_C.PHICH_D_Offset = type1head.DL_TYPE1_PUBLIC_C.PHICH_C_Offset+ type1head.DL_TYPE1_PUBLIC_C.NumOfUEForPHICH * sizeof(ENB_DL_TYPE1_PHICH_C);
		type1head.DL_TYPE1_PUBLIC_C.PDCCH_C_Offset = type1head.DL_TYPE1_PUBLIC_C.PHICH_D_Offset + type1head.DL_TYPE1_PUBLIC_C.NumOfUEForPHICH * sizeof(ENB_DL_TYPE1_PHICH_D);
		type1head.DL_TYPE1_PUBLIC_C.PDCCH_D_Offset =type1head.DL_TYPE1_PUBLIC_C.PDCCH_C_Offset+ type1head.DL_TYPE1_PUBLIC_C.PDCCHNum * sizeof(ENB_DL_TYPE1_PDCCH_C);
		type1head.DL_TYPE1_PUBLIC_C.PDSCH_C_Offset = type1head.DL_TYPE1_PUBLIC_C.PDCCH_D_Offset+ type1head.DL_TYPE1_PUBLIC_C.PDCCHNum * sizeof(ENB_DL_TYPE1_PDCCH_D);
		type1head.DL_TYPE1_PUBLIC_C.PDSCH_D_Offset = type1head.DL_TYPE1_PUBLIC_C.PDSCH_C_Offset + type1head.DL_TYPE1_PUBLIC_C.PDSCHNum * sizeof(ENB_DL_TYPE1_PDSCH_C);
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
		type1pbchd.SourcePBCH = 0; //´ý¶¨
		fsm_skb_put(pkptr,sizeof(struct ENB_DL_TYPE1_PBCH_D));
		fsm_mem_cpy(pkptr->data + tmp_len, &type1pbchd, sizeof(struct ENB_DL_TYPE1_PBCH_D));
		tmp_len += sizeof(struct ENB_DL_TYPE1_PBCH_D);
		type1phichc[0].RNTI = MactoPhyICI->rnti;
		type1phichc[0].zero = 0;
		type1phichc[0].I_lowest_index_PRB_RA = 0; //´ý¶¨
		type1phichc[0].NDmrs = 0; //´ý¶¨
		type1phichc[1].RNTI = 62;
		type1phichc[1].zero = 0;
		type1phichc[1].I_lowest_index_PRB_RA = 0; //´ý¶¨
		type1phichc[1].NDmrs = 0; //´ý¶¨
		fsm_skb_put(pkptr,2*sizeof(struct ENB_DL_TYPE1_PHICH_C));
		fsm_mem_cpy(pkptr->data + tmp_len, &type1phichc, 2*sizeof(struct ENB_DL_TYPE1_PHICH_C));
		tmp_len += 2 * sizeof(struct ENB_DL_TYPE1_PHICH_C);
		type1phichd[0].RNTI = MactoPhyICI->rnti;
		type1phichd[0].SourcePHICH = 0;
		type1phichd[1].RNTI = 62;
		type1phichd[1].SourcePHICH = 0;
		fsm_skb_put(pkptr,2*sizeof(struct ENB_DL_TYPE1_PHICH_D));
		fsm_mem_cpy(pkptr->data + tmp_len, &type1phichd, 2*sizeof(struct ENB_DL_TYPE1_PHICH_D));
		tmp_len += 2*sizeof(struct ENB_DL_TYPE1_PHICH_D);
		for(i = 0;i < type1head.DL_TYPE1_PUBLIC_C.PDCCHNum;i ++)
		{
			type1pdcchc[i].RNTI = MactoPhyICI->rnti;
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
			type1pdcchd[i].RNTI = MactoPhyICI->rnti;
			type1pdcchd[i].zero = 0;
			if(SV(sfn) == 1 || SV(subframeN) == 6)
				type1pdcchd[i].DataSource = 0x8ED8F08000000000;
			else
				type1pdcchd[i].DataSource = 0x8ED8F08000000000;
		}
		fsm_skb_put(pkptr,5*sizeof(struct ENB_DL_TYPE1_PDCCH_D));
		fsm_mem_cpy(pkptr->data + tmp_len, &type1pdcchd, 5*sizeof(struct ENB_DL_TYPE1_PDCCH_D));
		tmp_len += 5*sizeof(struct ENB_DL_TYPE1_PDCCH_D);
		for(i = 0;i < type1head.DL_TYPE1_PUBLIC_C.PDSCHNum;i ++)
		{
			type1pdschc[i].RNTI = MactoPhyICI->rnti;
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
			if(SV(sfn) == 1 || SV(subframeN) == 6)
			{
				type1pdschc[i].PDSCHTbSize = 4264; //ÌØÊâframe
			}
			else
			{
				type1pdschc[i].PDSCHTbSize = 5736;
			}
			type1pdschc[i].BitMap = 0xF8000000>>(5 * i);
		}
		fsm_skb_put(pkptr,5*sizeof(struct ENB_DL_TYPE1_PDSCH_C));
		fsm_mem_cpy(pkptr->data + tmp_len, &type1pdschc, 5*sizeof(struct ENB_DL_TYPE1_PDSCH_C));
		tmp_len += 5*sizeof(struct ENB_DL_TYPE1_PDSCH_C);	
		fsm_skb_put(pkptr,5*sizeof(struct ENB_DL_TYPE1_PDSCH_D)+5*data_len+5*sizeof(u32));
		for(i = 0;i < type1head.DL_TYPE1_PUBLIC_C.PDSCHNum;i ++)
		{
			type1pdschd[i].RNTI = MactoPhyICI->rnti;
			type1pdschd[i].PdschData = data_len;
			fsm_mem_cpy(pkptr->data + tmp_len, &type1pdschd, sizeof(struct ENB_DL_TYPE1_PDSCH_D));
			tmp_len += sizeof(struct ENB_DL_TYPE1_PDSCH_D);
			fsm_mem_cpy(pkptr->data + tmp_len, &SV(recv_upper_pkt_num), sizeof(u32));
			tmp_len += sizeof(u32);
			fsm_mem_cpy(pkptr->data + tmp_len, pkptrfrommac->data, data_len);
			tmp_len += data_len;
		}
		fsm_pkt_destroy(pkptrfrommac);
		fsm_printf("[UE SRIO]:pkptr->data len = %d:\n", pkptr->len);
		//fsm_octets_print(pkptr->data, pkptr->len);
		//fsm_pkt_send(pkptrcopy,STRM_TO_ETH);//for test
		if (SV(stored_pkt_count) >= MAX_STORED_PKT){
			fsm_printf("[UE SRIO] stored_pkt_count %d FOUT.\n", SV(stored_pkt_count));
			printk("[UE SRIO]pkt No.%d in FOUT due to storage room not big enough\n", SV(recv_upper_pkt_num));
			FOUT;
		}
		//printk("%d\n", SV(recv_upper_pkt_num));
		SV(pkts[SV(stored_pkt_count)]) = pkptr;
		//type1_send_to_srio();
		fsm_printf("[UE SRIO] packet %d has been stored.\n", SV(stored_pkt_count));
		SV(stored_pkt_count)++;
		type1_send_to_srio();
	}
	FOUT;
}


static void type1_send_to_srio(){
	FIN(type1_send_to_srio())
	int time=0;
	static int inter1=0;
	static int inter2=0;
	int inter=0;
	inter2=fsm_get_curtime();
	inter=inter2-inter1;
	inter1=inter2;
	SV_PTR_GET(srio_sv);
//	fsm_schedule_self(SV(send_interval), _TYPE1_SEND_TO_SRIO);
	FSM_PKT* pkptr;
	int i;
	int tmp_len = 0;
	static int times = 0;
	if (SV(stored_pkt_count) != 0){
	for (i = 0; i < SV(stored_pkt_count); i ++){
		tmp_len += SV(pkts[i])->len;
	}
	pkptr = fsm_pkt_create(tmp_len);
	tmp_len = 0;
	for (i = 0; i < SV(stored_pkt_count); i ++){
		fsm_skb_put(pkptr, SV(pkts[i])->len);
		fsm_mem_cpy(pkptr->data + tmp_len, SV(pkts[i])->data, SV(pkts[i])->len);
		tmp_len += SV(pkts[i])->len;
		fsm_pkt_destroy(SV(pkts[i]));
		fsm_printf("[UE SRIO]SV(pkts[%d]) has been copied and destroied\n", i);
	}
	if(pkptr->len>=cache_size)
	{
		printk("\n[warnning:]pkptr_len over cache_size\n");
	}
	fsm_mem_cpy((char *)(rtn_mmap() + 0x200000), pkptr->data, pkptr->len);
	fsm_mem_cpy((char *)(rtn_mmap() + 0x200000 + pkptr->len), &SV(stored_pkt_count), 2);
	fsm_octets_print(pkptr->data, pkptr->len);
	send_data(0xfc100000 + (times%cache_num)*cache_size+cache_size-2, 2, 0xfc300000 + pkptr->len);
	send_data(0xfc100000 + (times%cache_num)*cache_size, pkptr->len, 0xfc300000);//change address here when Mr.Wan running 
	SV(stored_pkt_count) = 0;
	fsm_pkt_destroy(pkptr);
	times ++;
	}
	FOUT;
}



/********************************************************************************
** Function name: idle_ioctl_handler
** Description: ´¦ÀíIDLE×´Ì¬ÏÂµÄIOControl
** Input:
** Output:
** Returns:
** Created by: ÕÅÖ¾Ç¿
** Created Date: 
** ------------------------------------------------------------------------------
** Modified by: MF
** Modified Date: 
********************************************************************************/
static void idle_ioctl_handler(void)
{
	char* rec_data_ptr;
	u32 *interval_ptr;
	void* ioctl_data;

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
			case IOCCMD_MACtoPHY_RNTI_Indicate:
				fsm_printf("SRIO:IOCCMD_MACtoPHY_RNTI_Indicate.\n");
				if(SV(psend_handle) == 0)
				{
					SV(psend_handle) = fsm_schedule_self(0, _MSG3_FROM_UPPER);
				}
				FOUT;
			case IOCCMD_MACtoPHY_recv_sysinfo:
				fsm_printf("SRIO:IOCCMD_MACtoPHY_recv_sysinfo.\n");
				FOUT;
			case IOCCMD_MACtoPHY_recv_paging:
				fsm_printf("SRIO:IOCCMD_MACtoPHY_recv_paging.\n");
				FOUT;
			case IOCCMD_MACtoPHY_Preamble_Indicate:
				fsm_printf("SRIO:IOCCMD_MACtoPHY_Preamble_Indicate.\n");
				test_send_msg1();
				FOUT;
			/*************20141013 MF modified**************To receive type1 ioctl from RRC*************/
			case IOCCMD_RRCtoPHY_Type1_Indicate:
				FOUT;
				break;
			/**************20141017 mf modified for test****************/
			case IOCCMD_STOP_TIMER:
				printk("in rio_hrtimer1_stop_wrapper()\n");
				rio_hrtimer1_stop_wrapper();
				FOUT;
				break;
		
			case IOCCMD_TEST_SEND_TO_ETH:
				test_send_to_eth();
				FOUT;
				break;
			case IOCCMD_PHYtoMAC_SYSFRAME:
				test_send_sf();
				FOUT;
				break;
			case IOCCMD_PRINT_PKT_FROM_MAC:
				print_info();
				SV(recv_upper_pkt_num)=0;
				FOUT;
				break;
			case IOCCMD_SEND_TO_SRIO:
					fsm_printf("SEND_TO_SRIO.\n");
					//fsm_schedule_self(500000, _TYPE1_SEND_TO_SRIO);
					type1_send_to_srio();
				FOUT;
				break;
			case IOCCMD_READ_MEM:
				fsm_printf("read mem\n");
				read_mem();
				FOUT;
				break;
			case IOCCMD_RA_COMPLETE:
				fsm_printf("[UE SRIO]RA COMPLETE\n");
				SV(racomplete) = true;
				//fsm_schedule_self(0,_TEST_SEND_SF);
				fsm_schedule_self(0, _TYPE2_RECV_FROM_SRIO);
				//fsm_schedule_self(500, _TYPE1_SEND_TO_SRIO);
				FOUT;
				break;
			case IOCCMD_RIODT_STOP:
				fsm_printf("riodt_exit\n");
				riodt_exit();
				FOUT;
				break;	
			case IOCCMD_LOST_PKT_COUNT:
				printk("[UE SRIO] has lost %d pkts\n", SV(lost_pkt_count));
				FOUT;
				break;
			case IOCCMD_SEND_INTERVAL_ADD:
				SV(send_interval)=SV(send_interval)+100;
				printk("SV(send_interval)=%d\n", SV(send_interval));
				break;
				case IOCCMD_SEND_INTERVAL_MINUS:
				if(SV(recv_interval>=100))
				SV(send_interval)=SV(send_interval)-100;
				printk("SV(send_interval)=%d\n", SV(send_interval));
				break;
			default:
				fsm_printf("SRIO:Unrecognized I/O control command.\n");
			FOUT;
		}
	}
}

static void test_send_sf(void)
{
	system_frame *Sf_info = (system_frame *)fsm_mem_alloc(sizeof(system_frame));

	Sf_info->frameNo = 512;
	Sf_info->subframeNo = 7;

	fsm_do_ioctrl(STRM_TO_RLCMAC,IOCCMD_PHYtoMAC_SYSFRAME,(void *)Sf_info,sizeof(Sf_info));
	//fsm_printf("[srio][test_send_sf][-->]SF has sent to MAC.\n");
	fsm_schedule_self(100, _TEST_SEND_SF);
}

static void read_mem()
{
	memread(0xfc100000, 512);
}
/**************20141017 mf modified for test****************/
static void test_send_to_eth(void)
{
	FSM_PKT* pkptr;

	pkptr = fsm_pkt_create(2048);
	//packet_send_to_eth(pkptr);

}

/**************20141103 mf For TEST*************************/

static void test_send_msg1(void)
{
	fsm_printf("[UE SRIO]test_send_msg1\n");
	FIN(test_send_msg1());
	

	FSM_PKT* pkptr;
	MSG1_Content* Msg1;
	struct ethhdr* head_ptr;
	struct lte_test_srio_head* sh_ptr;

	//ioctldata();
	RACH_ConfigDedicated *data;
	data = (RACH_ConfigDedicated *)fsm_data_get();
	//fsm_octets_print(data,sizeof(RACH_ConfigDedicated));
	fsm_printf("[UE SRIO] data->ra_PreambleIndex = %d\n",data->ra_PreambleIndex);

	int *MessageType;//1±íÊ¾ÎªËæ»ú½ÓÈëMSG1ÏûÏ¢
	//*MessageType = 1;
	pkptr = fsm_pkt_create(1028);
	//Msg1 = (MSG1_Content*)fsm_mem_alloc(sizeof(MSG1_Content));
	char dst_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	

	if(fsm_skb_headroom(pkptr) < (ETH_HLEN+sizeof(struct lte_test_srio_head)+sizeof(MSG1_Content)))
			{
				pkptr = fsm_skb_realloc_headeroom(pkptr,(ETH_HLEN+sizeof(struct lte_test_srio_head)+sizeof(MSG1_Content)));
				if(pkptr == NULL)
					return;
			}

	fsm_skb_push(pkptr, sizeof(MSG1_Content));
	Msg1 = (MSG1_Content*)pkptr->data;
	Msg1->cqi = 9;
	Msg1->rapid = data->ra_PreambleIndex;
	fsm_printf("[HEXI]RAPID IN SRIOFSM:%d\n", Msg1->rapid);
	//Msg1->rapid=25;	//for test
	Msg1->rarnti = 80;
	Msg1->ta = 0;

	//fsm_mem_cpy(pkptr->data,Msg1,sizeof(MSG1_Content));

	//fsm_skb_push(pkptr, sizeof(int));
	//fsm_mem_cpy(pkptr->data, (void*)(&MessageType), sizeof(int));
	

	//fsm_printf("messagetype = %d\n", (int*)(pkptr->data));

/*
	if(fsm_skb_headroom(pkptr) < ETH_HLEN)
		{
			pkptr = fsm_skb_realloc_headeroom(pkptr,ETH_HLEN);
			if(pkptr == NULL)
				return;
		}*/
		
		fsm_skb_push(pkptr, sizeof(struct lte_test_srio_head));
		sh_ptr = (struct lte_test_srio_head*)pkptr->data;
		sh_ptr->type = fsm_htonl(1);
		sh_ptr->len = fsm_htonl(pkptr->len-sizeof(struct lte_test_srio_head));
		
		fsm_skb_push(pkptr, ETH_HLEN);
		head_ptr = (struct ethhdr*)pkptr->data;
		fsm_mem_cpy(head_ptr->h_dest, dst_addr, ETH_ALEN);
		fsm_mem_cpy(head_ptr->h_source, fsm_intf_addr_get(STRM_TO_ETH), ETH_ALEN);
		head_ptr->h_proto = fsm_htons(DEV_PROTO_SRIO);	
	//	//fsm_octets_print(&pkptr->protocol, 2);
		fsm_pkt_send(pkptr,STRM_TO_ETH);
		FOUT;
		//SV(packet_count)++;
}

/**************end******************************************/
/********************************************************************************
** Function name: cfg_ioctl_handler
** Description: ´¦ÀíCFG×´Ì¬ÏÂµÄIOControl
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
** Description: ´òÓ¡µ±Ç°×´Ì¬
** Input: const char *str Ðè´òÓ¡µÄÄÚÈÝ
** Output:
** Returns:
** Created by: Âí·¼
** Created Date: 
** ------------------------------------------------------------------------------
** Modified by: 
** Modified Date: 
********************************************************************************/

void print_tran_info( const char *str)
{
	FIN( print_tran_info());
	int curtime=0;
	curtime=fsm_get_curtime();
	fsm_printf("%d ",curtime);
	fsm_printf(str);
	fsm_printf("\n");
FOUT;
}

/********************************************************************************
** Function name: ioctldata
** Description: get²¢destroyioctlµÄdata ²âÊÔÓÃ´úÂë
** Input:
** Output:
** Returns:
** Created by: Âí·¼
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

static void recv_tasklet_handler(char* checkaddr){
	static int recv_counter=0;
	u32 temp=0;
	fsm_mem_cpy(&temp,(checkaddr + 48), 4);
	if(temp<=recv_counter)
	{
	fsm_mem_free(checkaddr);
	return;}
	recv_counter=temp;
	UEPHYADPtoPHYType2 uetype2;
	UE_DL_TYPE2_PBCH_D DL_TYPE2_PBCH_D;
	UE_DL_TYPE2_PHICH_D DL_TYPE2_PHICH_D;
	UE_DL_TYPE2_PDCCH_C DL_TYPE2_PDCCH_C;
	void *PDCCH_D = NULL;
	UE_DL_TYPE2_PDSCH_C DL_TYPE2_PDSCH_C;
	void *PDSCH_D = NULL;
	int i;
	
	FSM_PKT* pkptr;
	PHYadaptertoMAC_IciMsg * ici_to_mac;
	pkptr=fsm_pkt_create(10240);
	/*
	for(i = 0;i < 700;i ++)
	{
		printk("%02x ",*checkaddr);
		 if(i % 16==0)
		{
			printk("\n");
		}
	}*/
	fsm_octets_print(checkaddr,1000);
	
	//TYPE2 head
	uetype2.GHead.NewFlag = *((u32 *)(checkaddr));//32bit
//	printk("NewFlag = %#x   ",uetype2.GHead.NewFlag);
	uetype2.GHead.SFN = *((u16 *)(checkaddr + 4));//16bit
//	printk("SFN = %#x   ",uetype2.GHead.SFN);
	uetype2.GHead.SubframeN = *((u16 *)(checkaddr + 6));//16bit
	//printk("%#x   ",uetype2.GHead.SubframeN);
	if(uetype2.GHead.SubframeN == 9)
	//printk("\n");
	uetype2.DL_TYPE2_PUBLIC_C.PDSCHLength = *((u32 *)(checkaddr + 8));//32bit
	//printk("PDSCHOffset = %#x\n",uetype2.DL_TYPE2_PUBLIC_C.PDSCHLength);
	uetype2.DL_TYPE2_PUBLIC_C.PDCCHOffset = *((u32 *)(checkaddr + 12));//32bit
	//printk("PDCCHOffset = %#x   ",uetype2.DL_TYPE2_PUBLIC_C.PDCCHOffset);
	//PBCH_D para
	DL_TYPE2_PBCH_D.SourcePBCH = *((u32 *)(checkaddr + 16));//32bit
	//printk("SourcePBCH = %#x   ",DL_TYPE2_PBCH_D.SourcePBCH);
	//PHICH_D para
	DL_TYPE2_PHICH_D.HARQIndex = *((u32 *)(checkaddr + 20));//32bit
	//printk("HARQIndex = %#x   ",DL_TYPE2_PHICH_D.HARQIndex);
	//PDCCH_C para
	DL_TYPE2_PDCCH_C.HARQprocessID = *((u32 *)(checkaddr + 24));//32bit
	//printk("HARQprocessID = %#x\n",DL_TYPE2_PDCCH_C.HARQprocessID);
	DL_TYPE2_PDCCH_C.RV = *((u32 *)(checkaddr + 28));//32bit
	//printk("RV = %#x   ",DL_TYPE2_PDCCH_C.RV);
	DL_TYPE2_PDCCH_C.NDI = *((u16 *)(checkaddr + 32));//16bit
	//printk("NDI = %#x   ",DL_TYPE2_PDCCH_C.NDI);
	DL_TYPE2_PDCCH_C.padding = *((u16 *)(checkaddr + 34));//16bit
	//printk("padding = %#x   ",DL_TYPE2_PDCCH_C.padding);
	//PDCCH_D para 64bit
	PDCCH_D = checkaddr + uetype2.DL_TYPE2_PUBLIC_C.PDCCHOffset;
	PDCCH_D = (u64 *)(checkaddr + 36);
	//printk("PDCCH_D = %#llx   ",*((u64 *)PDCCH_D));
	//PDSCH_C para
	DL_TYPE2_PDSCH_C.CRC = *((u32 *)(checkaddr + 44));//32bit
	//printk("CRC = %#x\n",DL_TYPE2_PDSCH_C.CRC);
	//PDSCH_D 
	PDSCH_D = (u32 *)(checkaddr + 48);
	//printk("PDSCH_D : ");
	ici_to_mac=(PHYadaptertoMAC_IciMsg*)fsm_mem_alloc(sizeof(PHYadaptertoMAC_IciMsg));
	ici_to_mac->tcid=2;
	ici_to_mac->rnti=61;
	ici_to_mac->frameNo = uetype2.GHead.SFN;
	ici_to_mac->subframeNo = uetype2.GHead.SubframeN;
	//fsm_printf("[UE SRIO]The rnti of the packet is %u, sending to MAC\n", ici_to_mac->rnti);
	if(pkptr!= NULL)
	{
		if(fsm_skb_headroom(pkptr) < sizeof(PHYadaptertoMAC_IciMsg))
		{
			pkptr = fsm_skb_realloc_headeroom(pkptr, sizeof(PHYadaptertoMAC_IciMsg));
			if(pkptr == NULL)
				printk("realloc head room failed in type2 recv\n");
				fsm_mem_free(ici_to_mac);
				fsm_pkt_destroy(pkptr);
				fsm_mem_free(checkaddr);
				return;
		}
	u16 data_len;
	fsm_mem_cpy(&data_len,(checkaddr + 48+4), 2);
	//fsm_printf("data_len is %d\n",data_len);
	fsm_mem_cpy(pkptr->head,ici_to_mac,sizeof(PHYadaptertoMAC_IciMsg));
	fsm_skb_put(pkptr,data_len);
	fsm_mem_cpy(pkptr->data,(checkaddr + 48+6), data_len);
	fsm_mem_free(ici_to_mac);
	//fsm_printf("[HEXI]TYPE IN SRIO:%c\n",*((char*)pkptr->data)+65);
	fsm_pkt_send(pkptr, STRM_TO_RLCMAC);
	fsm_octets_print(pkptr->data,pkptr->len);
	//printk("[srio][send to mac]data->len:%d,recv_counter %d\n",pkptr->len,recv_counter);
	fsm_mem_free(checkaddr);
	}
}


static void print_info()
{
	SV_PTR_GET(srio_sv);
	printk("SV(recv_upper_pkt_num)=%d\n",SV(recv_upper_pkt_num));
	fsm_schedule_self(100000, _TYPE1_SEND_TO_SRIO);
}
