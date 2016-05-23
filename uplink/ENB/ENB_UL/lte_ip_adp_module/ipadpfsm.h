/*******************************Copyright (c)*********************************************
**                University of Electronic Science and Technology of China
**                  School of Communication and Information Engineering
**                          http://www.uestc.edu.cn
**
**--------------------------- File Info ---------------------------------------------------
** File name:           ipadpfsm.h
** Last modified Date:  2014-09-08
** Last Version:        2.00
** Descriptions:        design the ipadp head and state transmit event. 
**                      Based on Linux 10.04. 
**------------------------------------------------------------------------------------------
** Created by:          Lou lina
** Created date:        
**------------------------------------------------------------------------------------------
** Modified by:   		Li xiru
** Modified date: 		2014-09-08
** Version:    			2.00
** Descriptions:  		add the Ici message.
**
*******************************************************************************************/
#include "../fsm/fsmdec.h"

#ifndef _IPADPFSM_H
#define _IPADPFSM_H

/*typedef struct Buffer      //pkt对列,20141201	noted in 20150108
{
	FSM_PKT * pkt;
	struct list_head  list;
} pktbuffer; */

typedef struct ipadp_sv{
u32 hello_count;
u32 packet_count;
u32 interval;
evHandle psend_handle;
//bool V_Flag; 	//noted in 20150318
} ipadp_sv;


struct drb_map{
	u16 user_id;
	u8 drb_id;
	u32 addr;
};
/*typedef struct URLC_IciMsg{   //added in 20140729,for the ICI between IPAPD and RLC
	u16 rnti; 
	u8 pbCh;     //PBCh = 1:PCCH, PBCh = 2: BCCH, 0:CCCH
        u8 rbId;
	u16 psn;
}__attribute__((packed)) URLC_IciMsg;
*/

/*typedef struct CRLC_RbidBuild_IOCTRLMsg
{
	//u16 rnti;
	//u8 rbId;
	bool V_Flag;
}CRLC_RbidBuild_IOCTRLMsg;	//add the definition of CRLC_RbidBuild_IOCTRLMsg 20141215
*/
/* the ICI information in the transimition between PDCP and RRC, IPADP*/
/*typedef struct UPDCP_IciMsg{
	u16 rnti;	
	u8 pbCh;     //PBCh = 1:PCCH, PBCh = 2: BCCH, 0:CCCH
	u8 rbId;
}__attribute__((packed)) UPDCP_IciMsg;*/

struct lte_test_ipadp_head
{
  u32 type;		//0 for IP, 1 for ipadp
  u32 len;
  u16 user_id;
  u8 drb_id;
}__attribute__((packed)); 

/*UE interface information MAC-RLC*/
typedef enum PBCH {PCCH = 1, BCCH = 2, ELSE = 0}PBCH; 

typedef struct IPADPtoMAC_IciMsg{
      u16 rnti; // UE sign
      PBCH pbCh;  //PBCh = 1 indicate PCCH ; PBCh = 2 indicate BCCH; 0:else
	  u16 len; // the length of the subheaders corresponding to the SDUs from RLC
}__attribute__((packed))IPADPtoMAC_IciMsg;


typedef struct MACtoIPADP_IciMsg{  //modified by HQ 20140504 
      u16 rnti; // UE sign
	 //PBCH pbch; //PBCh = 1 indicate PCCH ; PBCh = 2 indicate BCCH; 0:else
	  u8 lcid; //logical channel ID
}__attribute__((packed))MACtoIPADP_IciMsg;

typedef struct lteMacSubhead7Bit_s{
	u8 m_lcid_e_r_r;	//LCID 5bits,E 1bit,R 1bit
	u8 m_f_l;	//F 1bit,L 7bits
}__attribute__((packed))MAC_SDU_subhead_7bit;	//7bit子头

typedef struct lteMacSubhead15Bit_s{
	u8 m_lcid_e_r_r;	//LCID 5bits,E 1bit,R 1bit
	u8 m_f_l;	//F 1bit,L 7bits
	u8 m_l;		//L 8bits
}__attribute__((packed))MAC_SDU_subhead_15bit;	//15bit子头

#define _DO_IOCTL_PERIOD 	1
#define _START_WORK 		2
#define _SEND_PACKET_PERIOD	3

#define IPADP_PK_FROM_LOWER (fsm_ev_type()==FSM_EV_TYPE_PKT_IND)
#define IPADP_PK_FROM_UPPER (fsm_ev_type()==FSM_EV_TYPE_PKT_REQ)
#define IPADP_OPEN (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code()== FSM_EV_CORE_OPEN)
#define IPADP_CLOSE (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code() == FSM_EV_CORE_CLOSE)
#define IOCTL_ARRIVAL (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code() == FSM_EV_IOCTRL)
#define START_WORK (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == _START_WORK)
#define DO_IOCTL_PERIOD (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == _DO_IOCTL_PERIOD)
#define SEND_PACKET_PERIOD (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == _SEND_PACKET_PERIOD)	
	
/* IOCTL between IPADP and PDCP */
#define	CTRL_RBID_BUILD	0X37

/* IOCTL between IPADP and RRC */
#define	CTRL_RBID_MAP	0X38

#define LCIDERR 0X05  //added in 20150318
#define MFL 0X80
#define ML 0X00FF

void ipadp_main(void);

#endif



