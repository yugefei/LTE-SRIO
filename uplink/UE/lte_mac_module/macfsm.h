#include "../fsm/fsmdec.h"

#include <stdbool.h>
#include "rrc_config.h"
#include "macscheduler.h"
#include "macpkfmt.h"

#ifndef _MACFSM_H
#define _MACFSM_H

//IOCTRL Command definition 定义ioctrl命令值 以及 所携带数据时对应的数据结构

#define IOCCMD_RRCtoMAC_recv_sysinfo 	    0x01 //应该配置SRIO 后期会改20141120
#define IOCCMD_RRCtoMAC_stop_recv_sysinfo 	0x02//应该配置SRIO 后期会改
#define IOCCMD_RRCtoMAC_reset           	0x03

#define IOCCMD_RRCtoMAC_RandomAcc_Req	    0x04

//ioctrl commands from RRC with configuration information RRC配置命令，携带配置信息
#define IOCCMD_RRCTOMAC_CONFIG_TAT 			0x05     //TimeAlignmentTimer 
#define IOCCMD_RRCtoMAC_RACHcommonconfig 	0x06     //RACH-ConfigCommon
#define IOCCMD_RRCTOMAC_CONFIG_BCCH 		0x07     //BCCH-Config
#define IOCCMD_RRCTOMAC_CONFIG_PCCH 		0x08     //PCCH-Config
#define IOCCMD_RRCtoMAC_mainconfig 			0x09     //MAC-MainConfig
#define IOCCMD_RRCTOMAC_CONFIG_SPS 			0x10     //SPS-Config
#define IOCCMD_RRCtoMAC_LCconfig  			0x11     //LogicalChannelConfig 
// #define IOCCMD_RRCtoMAC_reconfig            0x12    
#define IOCCMD_RRCtoMAC_LCrelease            0x13   //deleteLogicalChannel

#define IOCCMD_Harq_feedback                 0x18   //when MAC received this command from PHYadapter,MAC consider this HARQ process was successful MAC就认为所有HARQ进程负责的PDU都发送成功


#define IOCCMD_RLCtoMAC_datasend_Req         0x0B
#define IOCCMD_PDCCHtoMAC_RandomAcc_Req      0x0C
#define IOCCMD_PDCCHtoMAC_ULGRANT            0x0D  //PHY send a DCI of ul_grant to MAC
#define IOCCMD_PHYtoMAC_SYSFRAME            0x0E //PHY to MAC system frame number and subframe number
// ioctrl commands send out
#define IOCCMD_MACtoRRC_CRNTI_Indicate       0x21 
#define IOCCMD_MACtoRRC_RandomAcc_Fail       0x22
#define IOCCMD_MACtoRLC_datasend_Allow       0x23
#define IOCCMD_MACtoPHY_RNTI_Indicate        0x24           
#define IOCCMD_MACtoPHY_Preamble_Indicate    0x25     
#define IOCCMD_MACtoPHY_recv_sysinfo         0x26
#define IOCCMD_MACtoPHY_stop_recv_sysinfo    0x27
#define IOCCMD_MACtoRRC_PUCCHSRS_release     0x28  //上行失步时，通知RRC释放PUCCH/SRS的配置

//testing commands 测试用的命令 
#define TESTCMD_RAR_REVF     0x40  //映射成 RAR接收失败
#define TESTCMD_RAR_REVS     0x41  //映射成 RAR接收成功
#define TESTCMD_CR_F         0x42  //映射成 竞争解决失败
#define TESTCMD_CR_S         0x43  //映射成 竞争解决成功
#define TEST_SENDMSG3        0x44  //内部事件，驱动SENDMSG3状态转换
#define TEST_RECV_PADING 0x45
#define TEST_MACtoPHY_PADING 0x46
#define TEST_RECV_SYS 	0x47
#define IOCCMD_MactoPHY_RACOMPLETE 0x48


/*************分割线201501演示添加的用户空间配置命令*********for test***********/
#define  _IOCTLtoUEMAC_RAR_Failed  0x70//配置RAR失败次数
#define  _IOCTLtoUEMAC_Contention_Failed 0x71//配置竞争解决失败次数
#define  _IOCTLtoUEMAC_PKT_NUM  	0x72
/*************分割线********************/


/** HX test **/
//#define            TEST_MSG3_SEND                           0x44
//self events definition 定义事件

#define Start_NonContentionBase_RandomAcc   1
#define Start_ContentionBase_RandomAcc      2
#define RandomAcc_Fail                      3
#define RARrev_Success                      4
#define ContentionResolution_Fail           5
#define Contention_Success                  6
#define SR_Fail                             7                     
 #define RA_Send_Msg3		8//LHL 20140726,第二次及以上发送MSG3，由MAC层触发
#define LC_BJ_CODE	9//MAC层逻辑信道BJ的中断码
//timers expire events definition 定义 定时器超时事件 
#define TimeAlignmentTimer_Expire          11
#define PeriodicBSRTimer_Expire            12
#define RexBSRTimer_Expire                 13
#define WaitforRAresponse_Expire           24 
#define CRTimer_Expire                     15

#define PHR_CE 0 
#define CRNTI_CE 1
#define regular_truncatedBSR_CE 2
#define regular_shortBSR_CE 3
#define regular_longBSR_CE 4
#define period_truncatedBSR_CE 5
#define period_shortBSR_CE 6
#define period_longBSR_CE 7  

#define ULHARQ_ProcessNum 2     //按照上/下行帧的配比配置，目前使用UL/DL=2/8
#define DLHARQ_ProcessNum 10    //按照上/下行帧的配比配置，目前使用UL/DL=2/8

#define MAC_BJ_TIME	100//MAC层逻辑信道BJ的更新周期，单位为10us，即更新周期为1ms
//condition definition   条件宏定义

#define MAC_PK_FROM_LOWER (fsm_ev_type()==FSM_EV_TYPE_PKT_IND)
#define	MAC_PK_FROM_UPPER (fsm_ev_type()==FSM_EV_TYPE_PKT_REQ)
//#define	SEND_MSG3 (fsm_ev_type()==FSM_EV_TYPE_PKT_REQ ||RA_SEND_MSG3)//modified by lhl 20140726
#define MAC_OPEN (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code()== FSM_EV_CORE_OPEN)
#define MAC_CLOSE (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code() == FSM_EV_CORE_CLOSE)
#define IOCTRL_ARRIVAL (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code() == FSM_EV_IOCTRL)


#define RACH_CONFIG (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_RRCtoMAC_RACHcommonconfig ) && fsm_ev_data()> 0 )
#define MAC_RESET (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_RRCtoMAC_reset ) )
//#define RECV_RLCREQ_WAITMSG3 (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_RLCtoMAC_datasend_Req ) )//modified by lhl 20140725
//testing code 
#define TESTCMD_RAR_REVF_T  (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== TESTCMD_RAR_REVF ) )
#define TESTCMD_RAR_REVS_T  (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== TESTCMD_RAR_REVS ) )   
#define TESTCMD_CR_F_T    (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== TESTCMD_CR_F ) )    
#define TESTCMD_CR_S_T   (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== TESTCMD_CR_S ) )   
 
#define 	LogicalChannel_BJ  (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == LC_BJ_CODE ) 
#define TimeAlignmentTimerExpire (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == TimeAlignmentTimer_Expire )        
#define PeriodicBSRTimerExpire (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == PeriodicBSRTimer_Expire )
#define RexBSRTimerExpire (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == RexBSRTimer_Expire )
#define WaitforRAresponseExpire (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == WaitforRAresponse_Expire)
#define CRTimerExpire (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == CRTimer_Expire )

//涉及参数问题，还是在ioctl统一处理
//#define RANDOM_ACCESS_FROM_MAC ( fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == Start_ContentionBase_RandomAcc )
//#define RANDOM_ACCESS_FROM_MAC_NC ( fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == Start_NonContentionBase_RandomAcc )
//#define RANDOM_ACCESS_FROM_RRC_NC (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_RRCtoMAC_RandomAcc_Req) && fsm_ev_data()> 0 )
//#define RANDOM_ACCESS_FROM_RRC_C (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_RRCtoMAC_RandomAcc_Req) && fsm_ev_data()== NULL )
//#define RANDOM_ACCESS_FROM_PDCCH_NC (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_PDCCHtoMAC_RandomAcc_Req) && fsm_ev_data()> 0 )
//#define RANDOM_ACCESS_FROM_PDCCH_C (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_PDCCHtoMAC_RandomAcc_Req) && fsm_ev_data()== NULL )


//#define START_C_RANDOM_ACCESS (RANDOM_ACCESS_FROM_MAC ||RANDOM_ACCESS_FROM_RRC_C || RANDOM_ACCESS_FROM_PDCCH_C )
//#define START_NC_RANDOM_ACCESS (RANDOM_ACCESS_FROM_PDCCH_NC || RANDOM_ACCESS_FROM_RRC_NC )

#define START_C_RANDOM_ACCESS ( fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == Start_ContentionBase_RandomAcc ) 
#define START_NC_RANDOM_ACCESS ( fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == Start_NonContentionBase_RandomAcc ) 
#define RANDOM_ACCESS_FAIL  ( (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == RandomAcc_Fail) || WaitforRAresponseExpire || TESTCMD_RAR_REVF_T ) //包括了RAR接收超时 HQ 20140419
#define CONTENTION_FAIL  ( (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == ContentionResolution_Fail) || CRTimerExpire || TESTCMD_CR_F_T  ) //包括了CRtimer超时 HQ 20140419
//#define CONTENTION_FAIL  ( (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == ContentionResolution_Fail)  || TESTCMD_CR_F_T  )//去掉了CTtimer超时，CRtimer超时后会单独处理，自中断会产生CONTENTION_FAIL
#define RARREV_SUCCESS ( (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == RARrev_Success) || TESTCMD_RAR_REVS_T )
#define CONTENTION_SUCCESS ( (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == Contention_Success) || TESTCMD_CR_S_T  )
#define SR_FAIL (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == SR_Fail)
//#define HAVE_SENDMSG3 (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == TEST_SENDMSG3) //testing code
#define RA_SEND_MSG3 (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == RA_Send_Msg3)//LHL 20140726
/*define data structure 定义数据结构*/


//MAC自定义 

typedef struct system_Config
{ 
	struct MAC_MainConfig  MACMainConfigInfo ;
	struct RachConfigCommon  RACHCommonConfigInfo  ;
	struct PCCH_Config    PCCHConfigInfo;
	struct BCCH_Config    BCCHConfigInfo;
	struct SPS_Config     SPSConfigInfo;
	MAC_LogicalChannelConfig_IoctrlMsg  CCCHConfigInfo ; //增加CCCH的配置信息，默认配置
}systemConfig;


//HARQ相关数据结构 
typedef struct HARQ_statu_parameters
{
	u16 CURRENT_TX_NB;
	bool HARQ_FEEDBACK ;
	u32  CURRENT_IRV;
}HARQ_statu_parameters;

typedef struct HARQ_statu_Info
{
	u32 processID;
	bool avaiable_flag; // true表示该进程空闲可用，false表示不可用。
	HARQ_statu_parameters statu;
	u32 *HARQ_buffer_pointer; //类型待斟酌，应该是个无类型的。或者指向MACPDU的指针
}HARQstatuInfo;

typedef struct HARQ_feedback
{
	u32 processID;
	bool HARQ_FEEDBACK ;
}HARQ_feedback;


typedef struct MAC_control_element_tag
{
	bool  addinPDU_flag;//TRUE表示需要复用到PDU中
	u8  LCID; //标识MAC控制单元的类型,通过LCID标识
	void *  MAC_CE_ptr;//指向具体的控制单元 ，在取具体内容时根据控制单元的类型进行类型转换
}MAC_controlelement_tag;




/*****************HQ修改完成20140531********************/
typedef struct Timer 
{
	u32 time_value ;//定时时间，单位为ms
	int* timer_sign; //定时器的标志，用于对定时器进行操作，比如取消定时器 //新框架定义的fsm_schedule_self()返回值类型为int*  20140531HQ
	bool flag;//如果该值为false则表示定时器未计时,如果等于true则表示该定时器仍在计时
}Timer; 

// RACH-ConfigDedicated 指示非竞争随机接入用的两个index 
/*typedef struct RACH_ConfigDedicated
{
	u32   ra_PreambleIndex	;  //明确发出的RA资源选择的随机接入前导
	u32   ra_PRACHMaskIndex	;  //明确发出的RA资源选择的PRACH Mask Index 
}__attribute__((packed))RACH_ConfigDedicated;*///20150115 LHL
typedef struct RACH_ConfigDedicated
{
	u8   ra_PreambleIndex	;  //明确发出的RA资源选择的随机接入前导
	u8   ra_PRACHMaskIndex	;  //明确发出的RA资源选择的PRACH Mask Index 
}__attribute__((packed))RACH_ConfigDedicated;
typedef struct RNTI_indication
{
	u32 rnti_type;//rnti的类型 1=C-RNTI  2=t-cnti 3=b-crnti 4=sps-rnti  5=p-crnti
	u32 rnti_value;//rnti的具体值
}__attribute__((packed))RNTI_indication;

/*****************************以下是HQ修改20140413******************************/
static unsigned short int BackoffTable[16]={
0,10,20,30,40,60,80,120,160,240,320,480,960,0,0,0
}; //后3个保留 

typedef struct RA_Type
{
	u32 ra_type;//0:false，1:pdcch IOCTL发起的，2:MAC层发起,3:RRC以IOCTL发起
}__attribute__((packed))RA_Type;

typedef struct SYSTEM_FRAME
{
	u16  frameNo ;       //system frame number
	u16  subframeNo ;    // subframe number for now
}__attribute__((packed))system_frame;

/*state variables definition 定义状态变量*/

typedef struct  mac_sv{
	u16  C_RNTI ;        // user ID
	u16  T_C_RNTI ; 	//20150120gai
	RACH_ConfigDedicated RA_info; 
	//unsigned char ra_preamble_index;
	//unsigned int  ra_PRACHMask_index;
	/*
	u32  frameNo ;       //system frame number
	u32  subframeNo ;    // subframe number for now
	*/ //modified LHL 20141105
	system_frame sys_frame;
	system_frame recv_frame;
	system_frame ue_schedule_frame;//20141112 modified LHL,在收到ULGRANT后调度使用，指示复用模块，复用模块使用后清空
	u32  PREAMBLE_TRANSMISSION_COUNTER ;  
	u32  SR_COUNTER ;   //SR transmission counter
	u32 backoff_index ; // use for random access
	u16 TA_fromRAR;//RAR消息中携带的Timing advance command  20140502
	u16 TA_value;//LHL MODIFIED 20141021,保留每次ENB更新的TA值
	u32 TA_Periodic_time;//LHL modifi20141021 保存RRC配置的TA定时器周期
	UL_resource  UL_resource_info; //information of the ul_grant
	HARQstatuInfo ULHARQ_status[ULHARQ_ProcessNum]; // the statu of HARQ process
	systemConfig  systemconfigInfo; //include RACHPCCH BCCH MacMain CCCH
	
	/*****************以下是lhl修改********************/
	//LogicalChannelConfigInfo *LC_info_ptr;
	LogicalChannelConfigInfo *LogicalChannel_Config;//hl更改，逻辑信道属性
	LogicalChannelBj *LogicalChannel_Bj;	//lhl更改,逻辑信道的Bj链表
	MacBufferStatus *MacBuffer_RLC; //lhl 改,MAC层保存并更新RLC层的请求报告
	MacBufferStatus_BSR_Info *Regularbsr;	//hl更改,常规BSR
	MacBufferStatus_BSR_Info *Periodicbsr;	//hl更改,周期BSR
	MacBufferStatus_BSR_Info *bsr; //lhl更改,BSR
	bool  LCGZeroToData; //=false 标志所有逻辑信道组数据从无到有
	bool  m_freshUlBsr; //=false 指示是否需要发送BSR(为true时不保证有资源)
	//bool  ALLOCATION_RESOURCE_BSR_INFO; //=false 设置标志表示是否有资源发bsr（为true时保证有资源)
	bool  DATA_WAIT_ALLOCATION;//=false 指标志是否有新的RLC报告请求
	u32 Rlc_Request_Num;//20140526modified，表示RLC请求的逻辑信道数量(数组的长度)
	/*****************lhl修改完成********************/
	//定时器
	Timer  TATimer; //systemconfigInfo.MACMainConfigInfo.timeAlignmentTimerDedicated 或者单独的命令
	Timer  CRTimer; //systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.mac_ContentionResolutionTimer
	Timer  RetxBSRTimer;//systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.retxBSR_Timer
	Timer  PeriodicBSRTimer;//systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.periodicBSR_Timer
	Timer  WaitforRAresponseTimer;//systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.raResponseWindowSize
	u32 	TA_timer_flag;//TA定时器是否取消过的标志，为了解决取消死机的问题 0:未取消过，1:取消过。每次开启时置为0，该取消时置为1
	//PHR还有两个定时器

	/**HeXi 20140423**/
	temp_contention_resolution *m_temp_cr;
	MAC_controlelement_tag  MAC_CE_Tags[8]; //UE MAC PDU has five kinds of MAC control units MAC PDU有5种控制单元
	SKBUFF* msg3_buf_ptr;
	//	bool contention_resolution_flag ;     
	//modified by lhl 20140716
	RA_Type ratype;
	u32 sendmsg3;//0:没发送MSG3，1:发送MSG3
	u32 pdcch_rnti;//0:PDCCH不是通过C_RNTI寻址，1:是通过C_RNTI寻址
	u32 Tbsize_Complex;//modified by lhl ,20140718,to 复用模块，可以发的总数据量
	u32 ra_allocation_res;//modified by lhl 20140725,指示当前随机接入是否为RLC request 分配了资源
	//0:当前随机接入没有为request 分配资源
	// 1:已分配资源，第一次发MSG3
	// 2:已分配资源，非第一次发MSG3
	//u32 flag123;
	u32 rar_failed_num;//20150104 联调添加变量，控制RAR失败次数
	u32 contention_failed_num;//20150104 联调添加变量，控制竞争解决失败次数
	u32 lost_pkt_num_uplink;//for test 
	u32 pkt_num_uplink;//for test
	u32 lost_pkt_num_downlink;//for test 
	u32 pkt_num_downlink;//for test
}mac_sv;  

void mac_main(void);
//void send_RRCConnectionRequest(struct UL_CCCH_Message *ulccchRRCremsg);
//struct UL_CCCH_Message *gen_ul_ccchmsg_send_rrcquest(void);                   //配置RRCrequest消息
#endif



