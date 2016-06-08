#include "../fsm/fsmdec.h"
#include "macpkfmt.h"
#include "fslrio_priv.h"
#include "riodt.h"
#include "vt861.h"
#include "PHY_PHYADP_UL_interfaceV1.h"
#include "PHY_PHYADP_interfaceV3.h"


#ifndef _SRIOFSM_H
#define _SRIOFSM_H

/*******逻辑信道标示*******/
#define PCH 0
#define BCH 1
#define DLSCH 2
#define MCH 3


#define _PACKET_SEND_PERIOD 	1
#define _START_WORK 		    2
#define _MSG3_FROM_UPPER        3 //20140715 mf
#define _PKT_FROM_SRIO			4 //20150429
#define _TYPE1_SEND_TO_SRIO		7
#define _TYPE2_RECV_FROM_SRIO	8
#define _PRINT_INFO           9


#define SRIO_PK_FROM_LOWER (fsm_ev_type()==FSM_EV_TYPE_PKT_IND)
#define SRIO_PK_FROM_UPPER (fsm_ev_type()==FSM_EV_TYPE_PKT_REQ)
#define SRIO_OPEN (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code()== FSM_EV_CORE_OPEN)
#define SRIO_CLOSE (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code() == FSM_EV_CORE_CLOSE)
#define IOCTL_ARRIVAL (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code() == FSM_EV_IOCTRL && fsm_ev_ioctrl_cmd() != IOCCMD_MACtoPHY_RNTI_Indicate)
#define START_WORK (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == _START_WORK)
#define PACKET_SEND_PERIOD (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == _PACKET_SEND_PERIOD)
#define TYPE1_SEND_TO_SRIO (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == _TYPE1_SEND_TO_SRIO)
#define TYPE2_RECV_FROM_SRIO (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == _TYPE2_RECV_FROM_SRIO)
#define PRINT_INFO (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == _PRINT_INFO)
//#define MSG3_FROM_UPPER (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == _MSG3_FROM_UPPER) //20140715 mf
#define MSG3_FROM_UPPER (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code() == FSM_EV_IOCTRL && fsm_ev_ioctrl_cmd() == IOCCMD_MACtoPHY_RNTI_Indicate)
#define _TEST_SEND_SF (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == _PACKET_SEND_PERIOD)

#define MAX_STORED_PKT	100
#define cache_num		5
#define cache_size		0x32000
typedef struct MACtoPHYadapter_IciMsg
{
   	 u16  frameNo ;       //system frame number
  	 u16  subframeNo ;    // subframe number for now
  	 u16 rnti ;         // UE ID
      u8 tcid;         // the type of Transport channel
     //u16 MessageType ; // the type of packet
}__attribute__((packed))MACtoPHYadapter_IciMsg;

typedef struct PHYadaptertoMAC_IciMsg
{
      u8 tcid;         // the type of Transport channel
     //u16 MessageType ; // the type of packet
     u16 rnti ; 

	u16  frameNo ;       //add on 11,17.2014
	u16  subframeNo ;    //add on 11,17.2014

}__attribute__((packed))PHYadaptertoMAC_IciMsg;	

typedef struct RACH_ConfigDedicated
{
  u8   ra_PreambleIndex	;  //明确发出的RA资源选择的随机接入前导
  u8   ra_PRACHMaskIndex	;  //明确发出的RA资源选择的PRACH Mask Index 
}__attribute__((packed))RACH_ConfigDedicated;

/*typedef struct MSG1_Content
{
	u16 rapid;
	u16 rarnti;
	u16 cqi;
	u16 ta;
}__attribute__((packed))MSG1_Content;*/

typedef struct MSG1_Content
{
	u8 rapid;
	u16 rarnti;
	u16 cqi;
	u16 ta;
}__attribute__((packed))MSG1_Content;

/*******************20140715 mf************************/

struct mac_cr_element_s
{
	u32 part1;
	u16 part2;
}__attribute__((packed));

typedef struct lteMacSubhead7Bit_ss{
	u8 m_lcid_e_r_r;	//LCID 5bits,E 1bit,R 1bit
	u8 m_f_l;	//F 1bit,L 7bits
}__attribute__((packed))MAC_SDU_subhead_7bit_s;	//7bit子头

/*******************20140715 mf************************/

/*******************20141108 mf modified***************/


typedef struct Ul_DCI
{
    u32	m_format  	:1;                 //1bit 区分format0和1A
    u32	m_hopping 	:1;                 //1bit  跳频标志
    u32	RIV       	:13;                //13bit:when band==20MHZ type2
    u32	m_mcs		:5;                 //5bit 调制编码格式和RV信息
    u32	m_ndi		:1;                 //1bit 新数据标志
    u32	m_tpc		:2;                 //2bit
    u32 Cyclic_shift:3;                 //3bit 数据解调导频的循环移位
    u32 m_dai		:2;                 //2bit 下行分配数目的标识 when上下行时间配比：#1-6
    u32 m_cqiRequest:1;                 //1bit cqi请求标识
    u32 padding		:2;                 //2bit 填充比特 使其长度与format 1A相同(协议要求)
    u32 emptybits	:1;					//由系统带宽和32bit决定。  
}__attribute__((packed))Regular_ULgrant;// structure of UL DCI format0
typedef struct UEPHY_TO_MAC_ULSCHEDULE
{
	u16	m_rnti;
	u16  frameNo ;       //add on 11,17.2014
	u16  subframeNo ;    //add on 11,17.2014
	Regular_ULgrant  s_ul_dci;
}__attribute__((packed))UEPHY_TO_MAC_ULgrant;//LHLmodified 20141105

typedef struct SYSTEM_FRAME
{
	u32  frameNo ;       //system frame number
	u32  subframeNo ;    // subframe number for now
}__attribute__((packed))system_frame;

typedef struct srio_sv{
int packet_count;
int recv_count;
unsigned int interval;
evHandle psend_handle;
bool racomplete;
u16 sfn;
u16 subframeN;
FSM_PKT* pkts[MAX_STORED_PKT];//for 5ms send to srio test
u16 stored_pkt_count;//for 5ms send to srio test
u32 recv_upper_pkt_num;
u32 recv_pkt_from_enb;
char * mem_zero;
u32 pre_pkt_no;
u32 recv_interval;
u32 send_interval;
u32 lost_pkt_count; 
} srio_sv;

void srio_main(void);

#endif



