#include <linux/if_ether.h>
#include <linux/list.h>
#include <linux/kernel.h>

#include "../fsm/fsmdec.h"
#include "../lte_system.h"
#include "mac_scheduler.h"
#include "queue_manager.h"
#include "macpkfmt.h"
#include "enb_macscheduler.h"
#include "rrc_config.h"
#ifndef _MACFSM_H
#define _MACFSM_H


#define NUM_RNTI 200
#define USERNUMMAX 10
#define DL_SCHEDULE_NUM 5

typedef struct PHY_TO_MAC_FRAME{
	u16    sfn; //             //ϵͳ֡�ţ�0-1023
	u16    subframeN;//        //��֡�ţ�0--9
} __attribute__((packed))PHY_TO_MAC_frame;
//LHL 20141124 MAC������
typedef struct system_Config
{ 
	struct MAC_MainConfig  MACMainConfigInfo ;
	struct RachConfigCommon  RACHCommonConfigInfo  ;
	struct PCCH_Config    PCCHConfigInfo;
	struct BCCH_Config    BCCHConfigInfo;
	struct SPS_Config     SPSConfigInfo;
	MAC_LogicalChannelConfig_IoctrlMsg  CCCHConfigInfo ; //����CCCH��������Ϣ��Ĭ������
}systemConfig;


typedef struct mac_sv
{
	struct list_head* ULschedQue_p;//���е��ȣ�������������Դ���û�����
	struct list_head* RAschedQue_p;//RA������룬����Ӧ���û�����
	int UL_sched_flag;// 1��ʾ���е��ȶ��в�Ϊ�գ���Ҫ�������е���;0��ʾ����Ҫ����
	int RA_sched_flag;//1//��ʾRA���ȶ��в�Ϊ�գ���Ҫ����RA����;0��ʾ����Ҫ����
	int UL_resource_flag; //0��ʾ������Դ�Ѿ������� 1��ʾ������Դ����ʣ�� >0Ҳ���Ա�ʾʣ����Դ��
	int RAR_receive_crnti;//flag if there is C-RNTI at msg3;{0,1}
    struct rnti_array rntiarray[NUM_RNTI];
	int tc_rnti_notes[NUM_RNTI];//��¼tc-rnti��ʵʱ���
    struct result_sched_algorithm schedule_scheme[DL_SCHEDULE_NUM];
    
   // bool DATA_WAIT_ALLOCATION;
	int Rlc_Request_Num[USERNUMMAX];//20140624modified����ʾRLC������߼��ŵ�����(����ĳ���)
	struct list_head * Enb_MacBuffer_RLC[USERNUMMAX];//20140623modify lhl,ÿ���û�������ָ��ͷ��
	struct list_head * Enb_LogicalChannel_Config[USERNUMMAX];
	struct list_head * Enb_LogicalChannel_Bj[USERNUMMAX];
	temp_contention_resolution *m_temp_cr;
//	complex_frame schedule_frame[DL_SCHEDULE_NUM];//LHL 20141017,��GCX������д���к���ʹ�ã������
	PHY_TO_MAC_frame phy_to_mac_frame;
//	u8 prb_bitmap2[100];
	u8 prb_bitmap7[100];
	u8 next_prb_bitmap2[100];
	u8 next_prb_bitmap7[100];
	u8 dl_bitmap[100];
//	struct rnti_array rntiarray[NUM_RNTI];
//	struct result_sched_algorithm schedule_scheme[DL_SCHEDULE_NUM];
//	DL_TBsize_ue TBsize_ue[USERNUMMAX];//LHL20141011,GCX���Ⱥ���䣬HX����ʱʹ�ã���ʼ��Ϊ0
	Ue_ta_info ue_ta[USERNUMMAX];//LHLmodified  �û���TA,��PHYIOCTL ���£�����ģ��ʹ�ã�����flag��Ϊ0��
	systemConfig systemconfigInfo;
	int cnt_test;
	u32 send_rar_flag;//20150104������ӵĵ��Դ��룬��ʼΪ1��ʾҪ��RAR���յ��û��ռ�IOCTL��Ϊ0������RAR
	u32 lost_pktnum_uplink;
	u32 total_pktnum_uplink;
	u32 lost_pktnum_downlink;
	u32 total_pktnum_downlink;
} mac_sv;


/* IOCTRL Command definition */
#define IOCCMD_RRCtoMAC_reset           	 0x01
#define IOCCMD_RRCtoMAC_LC_config          	 0x41 //Я������ 
#define IOCCMD_RRCtoMAC_LC_release           0x42 //Я������ C_RNTI LCid 
#define IOCCMD_RRCtoMAC_UE_release           0x43 //Я������ C_RNTI �ͷŸ�RNTI��Ӧ��UE������������Ϣ
#define IOCCMD_MACtoRRC_RNTI_indicate        0x31 //Я������ C_RNTI ��֪RRC RNTIֵ

#define IOCCMD_MACTOPHY_UL_DCI 0x12 //20141121
#define IOCCMD_MACTOPHY_DL_DCI 0x13
#define IOCCMD_MACTOPHY_RAR_DCI 0x14

#define IOCCMD_RLCtoMAC_datasend_Req         0x0B //Я������ 
#define IOCCMD_MACtoRLC_datasend_Allow       0x23 //Я������ 

#define IOCCMD_PHYtoMAC_RA_Req               0x03   //Я��������RA-RNTI,RAPID(�����ж��),TA,
#define IOCCMD_PHYtoMAC_SR                   0x04   //�������յ�ĳ��UE��SR,Я������C-RNTI
#define IOCCMD_PHYtoMAC_TA			0x06//���������TAֵ��MAC��������UE_TA_INFO
#define IOCCMD_PHYtoMAC_FRAME			0x07//���������֡��ֵ��MAC��������PHY_TO_MAC_frame
#define IOCCMD_TEST_WITHDATA                 0x05  //���Դ�������IOCTL



/**********�ָ���***20150104�������Դ��룬����ENB����RAR����ʾ������***for test**********/
#define _IOCTLtoENBMAC_RAR_Failed  0x70 //����ENB MAC����RAR
#define _IOCTLtoENBMAC_RAR_Send 0x71//����ENB MAC��RAR,�൱�ڳ�����һ������
#define _IOCTLtoENBMAC_PKT_NUM 0x72
/**********�ָ���****************/

#define IOCCMD_MACtoSRIO_RA_Complete 0x48


/*IOCRTL Command data structure*/
/*typedef struct MAC_LogicalChannelConfig_IoctrlMsg{
	u16 crnti;
	int logicalChannelIdentity;
	struct LogicalChannelConfig logicalChannelConfig;
};
*/

//LHL 20141011
/*typedef struct DL_TBSIZE_UE{//����ÿ���û���ǰTTI���Է��͵���󳤶�
	u16 rnti;//�ɹ�������Դ����ʱ���
	u32 tbsize;//��HX����ʱʹ�ã�ʹ�ú����Ϊ0
}DL_TBsize_ue;*///��ʱʹ�����schedule_scheme �е�tbsize

struct MAC_Release_LogicalChannel_IoctrlMsg{
	u16 crnti;
	int lcid;
}__attribute__((packed));

struct MAC_Release_Uefsm{
	u16 crnti;
}__attribute__((packed));

/* // RA����ĸ�ʽ  ��ʱ��S_RAinfo Ϊ׼ 
typedef struct RA_req_info
{
	u16 ra_rnti;
	u8 rapid;//ra_preamble_index ��ʱֻʵ��Ϊֻ��һ��rapid
}__attribute__((packed))RA_req_info;
*/

/*self evens denition*/

#define TIME_TODO_ULSCHED  0x10  //���¼��ɶ�ʱ����ʱ��������ʾ���Խ������е���

/*condition definition �����궨�� */

#define MAC_PK_FROM_LOWER (fsm_ev_type()==FSM_EV_TYPE_PKT_IND)
#define	MAC_PK_FROM_UPPER (fsm_ev_type()==FSM_EV_TYPE_PKT_REQ)
#define MAC_OPEN (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code()== FSM_EV_CORE_OPEN)
#define MAC_CLOSE (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code() == FSM_EV_CORE_CLOSE)
#define IOCTRL_ARRIVAL (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code() == FSM_EV_IOCTRL)

#define MAC_RESET (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_RRCtoMAC_reset ) )
#define RA_REQ (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_PHYtoMAC_RA_Req ) )
#define DL_SCHED_REQ (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_RLCtoMAC_datasend_Req ) )	//����������Ҫ����
#define UL_SCHED_REQ (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_PHYtoMAC_SR ) )	//����������Ҫ����
#define UL_SCHED (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == TIME_TODO_ULSCHED)



void mac_main(void);

#endif



