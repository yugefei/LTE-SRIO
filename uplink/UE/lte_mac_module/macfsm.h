#include "../fsm/fsmdec.h"

#include <stdbool.h>
#include "rrc_config.h"
#include "macscheduler.h"
#include "macpkfmt.h"

#ifndef _MACFSM_H
#define _MACFSM_H

//IOCTRL Command definition ����ioctrl����ֵ �Լ� ��Я������ʱ��Ӧ�����ݽṹ

#define IOCCMD_RRCtoMAC_recv_sysinfo 	    0x01 //Ӧ������SRIO ���ڻ��20141120
#define IOCCMD_RRCtoMAC_stop_recv_sysinfo 	0x02//Ӧ������SRIO ���ڻ��
#define IOCCMD_RRCtoMAC_reset           	0x03

#define IOCCMD_RRCtoMAC_RandomAcc_Req	    0x04

//ioctrl commands from RRC with configuration information RRC�������Я��������Ϣ
#define IOCCMD_RRCTOMAC_CONFIG_TAT 			0x05     //TimeAlignmentTimer 
#define IOCCMD_RRCtoMAC_RACHcommonconfig 	0x06     //RACH-ConfigCommon
#define IOCCMD_RRCTOMAC_CONFIG_BCCH 		0x07     //BCCH-Config
#define IOCCMD_RRCTOMAC_CONFIG_PCCH 		0x08     //PCCH-Config
#define IOCCMD_RRCtoMAC_mainconfig 			0x09     //MAC-MainConfig
#define IOCCMD_RRCTOMAC_CONFIG_SPS 			0x10     //SPS-Config
#define IOCCMD_RRCtoMAC_LCconfig  			0x11     //LogicalChannelConfig 
// #define IOCCMD_RRCtoMAC_reconfig            0x12    
#define IOCCMD_RRCtoMAC_LCrelease            0x13   //deleteLogicalChannel

#define IOCCMD_Harq_feedback                 0x18   //when MAC received this command from PHYadapter,MAC consider this HARQ process was successful MAC����Ϊ����HARQ���̸����PDU�����ͳɹ�


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
#define IOCCMD_MACtoRRC_PUCCHSRS_release     0x28  //����ʧ��ʱ��֪ͨRRC�ͷ�PUCCH/SRS������

//testing commands �����õ����� 
#define TESTCMD_RAR_REVF     0x40  //ӳ��� RAR����ʧ��
#define TESTCMD_RAR_REVS     0x41  //ӳ��� RAR���ճɹ�
#define TESTCMD_CR_F         0x42  //ӳ��� �������ʧ��
#define TESTCMD_CR_S         0x43  //ӳ��� ��������ɹ�
#define TEST_SENDMSG3        0x44  //�ڲ��¼�������SENDMSG3״̬ת��
#define TEST_RECV_PADING 0x45
#define TEST_MACtoPHY_PADING 0x46
#define TEST_RECV_SYS 	0x47
#define IOCCMD_MactoPHY_RACOMPLETE 0x48


/*************�ָ���201501��ʾ��ӵ��û��ռ���������*********for test***********/
#define  _IOCTLtoUEMAC_RAR_Failed  0x70//����RARʧ�ܴ���
#define  _IOCTLtoUEMAC_Contention_Failed 0x71//���þ������ʧ�ܴ���
#define  _IOCTLtoUEMAC_PKT_NUM  	0x72
/*************�ָ���********************/


/** HX test **/
//#define            TEST_MSG3_SEND                           0x44
//self events definition �����¼�

#define Start_NonContentionBase_RandomAcc   1
#define Start_ContentionBase_RandomAcc      2
#define RandomAcc_Fail                      3
#define RARrev_Success                      4
#define ContentionResolution_Fail           5
#define Contention_Success                  6
#define SR_Fail                             7                     
 #define RA_Send_Msg3		8//LHL 20140726,�ڶ��μ����Ϸ���MSG3����MAC�㴥��
#define LC_BJ_CODE	9//MAC���߼��ŵ�BJ���ж���
//timers expire events definition ���� ��ʱ����ʱ�¼� 
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

#define ULHARQ_ProcessNum 2     //������/����֡��������ã�Ŀǰʹ��UL/DL=2/8
#define DLHARQ_ProcessNum 10    //������/����֡��������ã�Ŀǰʹ��UL/DL=2/8

#define MAC_BJ_TIME	100//MAC���߼��ŵ�BJ�ĸ������ڣ���λΪ10us������������Ϊ1ms
//condition definition   �����궨��

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

//�漰�������⣬������ioctlͳһ����
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
#define RANDOM_ACCESS_FAIL  ( (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == RandomAcc_Fail) || WaitforRAresponseExpire || TESTCMD_RAR_REVF_T ) //������RAR���ճ�ʱ HQ 20140419
#define CONTENTION_FAIL  ( (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == ContentionResolution_Fail) || CRTimerExpire || TESTCMD_CR_F_T  ) //������CRtimer��ʱ HQ 20140419
//#define CONTENTION_FAIL  ( (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == ContentionResolution_Fail)  || TESTCMD_CR_F_T  )//ȥ����CTtimer��ʱ��CRtimer��ʱ��ᵥ���������жϻ����CONTENTION_FAIL
#define RARREV_SUCCESS ( (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == RARrev_Success) || TESTCMD_RAR_REVS_T )
#define CONTENTION_SUCCESS ( (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == Contention_Success) || TESTCMD_CR_S_T  )
#define SR_FAIL (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == SR_Fail)
//#define HAVE_SENDMSG3 (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == TEST_SENDMSG3) //testing code
#define RA_SEND_MSG3 (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == RA_Send_Msg3)//LHL 20140726
/*define data structure �������ݽṹ*/


//MAC�Զ��� 

typedef struct system_Config
{ 
	struct MAC_MainConfig  MACMainConfigInfo ;
	struct RachConfigCommon  RACHCommonConfigInfo  ;
	struct PCCH_Config    PCCHConfigInfo;
	struct BCCH_Config    BCCHConfigInfo;
	struct SPS_Config     SPSConfigInfo;
	MAC_LogicalChannelConfig_IoctrlMsg  CCCHConfigInfo ; //����CCCH��������Ϣ��Ĭ������
}systemConfig;


//HARQ������ݽṹ 
typedef struct HARQ_statu_parameters
{
	u16 CURRENT_TX_NB;
	bool HARQ_FEEDBACK ;
	u32  CURRENT_IRV;
}HARQ_statu_parameters;

typedef struct HARQ_statu_Info
{
	u32 processID;
	bool avaiable_flag; // true��ʾ�ý��̿��п��ã�false��ʾ�����á�
	HARQ_statu_parameters statu;
	u32 *HARQ_buffer_pointer; //���ʹ����ã�Ӧ���Ǹ������͵ġ�����ָ��MACPDU��ָ��
}HARQstatuInfo;

typedef struct HARQ_feedback
{
	u32 processID;
	bool HARQ_FEEDBACK ;
}HARQ_feedback;


typedef struct MAC_control_element_tag
{
	bool  addinPDU_flag;//TRUE��ʾ��Ҫ���õ�PDU��
	u8  LCID; //��ʶMAC���Ƶ�Ԫ������,ͨ��LCID��ʶ
	void *  MAC_CE_ptr;//ָ�����Ŀ��Ƶ�Ԫ ����ȡ��������ʱ���ݿ��Ƶ�Ԫ�����ͽ�������ת��
}MAC_controlelement_tag;




/*****************HQ�޸����20140531********************/
typedef struct Timer 
{
	u32 time_value ;//��ʱʱ�䣬��λΪms
	int* timer_sign; //��ʱ���ı�־�����ڶԶ�ʱ�����в���������ȡ����ʱ�� //�¿�ܶ����fsm_schedule_self()����ֵ����Ϊint*  20140531HQ
	bool flag;//�����ֵΪfalse���ʾ��ʱ��δ��ʱ,�������true���ʾ�ö�ʱ�����ڼ�ʱ
}Timer; 

// RACH-ConfigDedicated ָʾ�Ǿ�����������õ�����index 
/*typedef struct RACH_ConfigDedicated
{
	u32   ra_PreambleIndex	;  //��ȷ������RA��Դѡ����������ǰ��
	u32   ra_PRACHMaskIndex	;  //��ȷ������RA��Դѡ���PRACH Mask Index 
}__attribute__((packed))RACH_ConfigDedicated;*///20150115 LHL
typedef struct RACH_ConfigDedicated
{
	u8   ra_PreambleIndex	;  //��ȷ������RA��Դѡ����������ǰ��
	u8   ra_PRACHMaskIndex	;  //��ȷ������RA��Դѡ���PRACH Mask Index 
}__attribute__((packed))RACH_ConfigDedicated;
typedef struct RNTI_indication
{
	u32 rnti_type;//rnti������ 1=C-RNTI  2=t-cnti 3=b-crnti 4=sps-rnti  5=p-crnti
	u32 rnti_value;//rnti�ľ���ֵ
}__attribute__((packed))RNTI_indication;

/*****************************������HQ�޸�20140413******************************/
static unsigned short int BackoffTable[16]={
0,10,20,30,40,60,80,120,160,240,320,480,960,0,0,0
}; //��3������ 

typedef struct RA_Type
{
	u32 ra_type;//0:false��1:pdcch IOCTL����ģ�2:MAC�㷢��,3:RRC��IOCTL����
}__attribute__((packed))RA_Type;

typedef struct SYSTEM_FRAME
{
	u16  frameNo ;       //system frame number
	u16  subframeNo ;    // subframe number for now
}__attribute__((packed))system_frame;

/*state variables definition ����״̬����*/

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
	system_frame ue_schedule_frame;//20141112 modified LHL,���յ�ULGRANT�����ʹ�ã�ָʾ����ģ�飬����ģ��ʹ�ú����
	u32  PREAMBLE_TRANSMISSION_COUNTER ;  
	u32  SR_COUNTER ;   //SR transmission counter
	u32 backoff_index ; // use for random access
	u16 TA_fromRAR;//RAR��Ϣ��Я����Timing advance command  20140502
	u16 TA_value;//LHL MODIFIED 20141021,����ÿ��ENB���µ�TAֵ
	u32 TA_Periodic_time;//LHL modifi20141021 ����RRC���õ�TA��ʱ������
	UL_resource  UL_resource_info; //information of the ul_grant
	HARQstatuInfo ULHARQ_status[ULHARQ_ProcessNum]; // the statu of HARQ process
	systemConfig  systemconfigInfo; //include RACH�PPCCH BCCH MacMain CCCH
	
	/*****************������lhl�޸�********************/
	//LogicalChannelConfigInfo *LC_info_ptr;
	LogicalChannelConfigInfo *LogicalChannel_Config;//hl���ģ��߼��ŵ�����
	LogicalChannelBj *LogicalChannel_Bj;	//lhl����,�߼��ŵ���Bj����
	MacBufferStatus *MacBuffer_RLC; //lhl ��,MAC�㱣�沢����RLC������󱨸�
	MacBufferStatus_BSR_Info *Regularbsr;	//hl����,����BSR
	MacBufferStatus_BSR_Info *Periodicbsr;	//hl����,����BSR
	MacBufferStatus_BSR_Info *bsr; //lhl����,BSR
	bool  LCGZeroToData; //=false ��־�����߼��ŵ������ݴ��޵���
	bool  m_freshUlBsr; //=false ָʾ�Ƿ���Ҫ����BSR(Ϊtrueʱ����֤����Դ)
	//bool  ALLOCATION_RESOURCE_BSR_INFO; //=false ���ñ�־��ʾ�Ƿ�����Դ��bsr��Ϊtrueʱ��֤����Դ)
	bool  DATA_WAIT_ALLOCATION;//=false ָ��־�Ƿ����µ�RLC��������
	u32 Rlc_Request_Num;//20140526modified����ʾRLC������߼��ŵ�����(����ĳ���)
	/*****************lhl�޸����********************/
	//��ʱ��
	Timer  TATimer; //systemconfigInfo.MACMainConfigInfo.timeAlignmentTimerDedicated ���ߵ���������
	Timer  CRTimer; //systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.mac_ContentionResolutionTimer
	Timer  RetxBSRTimer;//systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.retxBSR_Timer
	Timer  PeriodicBSRTimer;//systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.periodicBSR_Timer
	Timer  WaitforRAresponseTimer;//systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.raResponseWindowSize
	u32 	TA_timer_flag;//TA��ʱ���Ƿ�ȡ�����ı�־��Ϊ�˽��ȡ������������ 0:δȡ������1:ȡ������ÿ�ο���ʱ��Ϊ0����ȡ��ʱ��Ϊ1
	//PHR����������ʱ��

	/**HeXi 20140423**/
	temp_contention_resolution *m_temp_cr;
	MAC_controlelement_tag  MAC_CE_Tags[8]; //UE MAC PDU has five kinds of MAC control units MAC PDU��5�ֿ��Ƶ�Ԫ
	SKBUFF* msg3_buf_ptr;
	//	bool contention_resolution_flag ;     
	//modified by lhl 20140716
	RA_Type ratype;
	u32 sendmsg3;//0:û����MSG3��1:����MSG3
	u32 pdcch_rnti;//0:PDCCH����ͨ��C_RNTIѰַ��1:��ͨ��C_RNTIѰַ
	u32 Tbsize_Complex;//modified by lhl ,20140718,to ����ģ�飬���Է�����������
	u32 ra_allocation_res;//modified by lhl 20140725,ָʾ��ǰ��������Ƿ�ΪRLC request ��������Դ
	//0:��ǰ�������û��Ϊrequest ������Դ
	// 1:�ѷ�����Դ����һ�η�MSG3
	// 2:�ѷ�����Դ���ǵ�һ�η�MSG3
	//u32 flag123;
	u32 rar_failed_num;//20150104 ������ӱ���������RARʧ�ܴ���
	u32 contention_failed_num;//20150104 ������ӱ��������ƾ������ʧ�ܴ���
	u32 lost_pkt_num_uplink;//for test 
	u32 pkt_num_uplink;//for test
	u32 lost_pkt_num_downlink;//for test 
	u32 pkt_num_downlink;//for test
}mac_sv;  

void mac_main(void);
//void send_RRCConnectionRequest(struct UL_CCCH_Message *ulccchRRCremsg);
//struct UL_CCCH_Message *gen_ul_ccchmsg_send_rrcquest(void);                   //����RRCrequest��Ϣ
#endif



