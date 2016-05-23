#ifndef RRC_UTILS_H
#define RRC_UTILS_H

#include "../fsm/fsmdec.h"
#include "rrc_type.h"


#define MAX_UEFSM_NUM         5   //max number of ue fsms 
#define MAX_SRB_NUM 		  13  //max number of srb of each ue 
#define MAX_DRB_NUM 		  12  //max number of drb of each ue 
#define Max_Conn_Time             0

/* ͳ�Ʊ������� */
//��ʼ����rrcfsm_enb_module.c
typedef struct rrc_sv_enb_ue{
	int uefsmid;
	u16 crnti;
} rrc_sv_enb_ue;

//������ص����ݽṹ
//store information on active signaling radio bearer instance
struct  LteSignalingRadioBearerInfo 
{
	u8 srbStatus;			//��ʶ�Ƿ����0��ʾ����
	u8 srbIdentity;			//0->SRB0, 1->SRB1, 2->SRB2
	struct RlcConfig rlcConfig;
	u8 lcid;				//�߼��ŵ�id��0->SRB0, 1->SRB1, 2->SRB2, 3->DRB0, 4->DRB1��
 	struct LogicalChannelConfig logicalChannelConfig;  //�߼��ŵ�����
};

// store information on active data radio bearer instance
struct LteDataRadioBearerInfo 
{
	u8 drbStatus;
	u8 drbIdentity;
	int eps_BearerIdentity;
	struct RlcConfig rlcConfig;
	u8 lcid;
	struct LogicalChannelConfig logicalChannelConfig;
};

// defined in rrc_utils.c
extern struct LteSignalingRadioBearerInfo* enbSRBConfig[MAX_UEFSM_NUM][MAX_SRB_NUM];
extern struct LteDataRadioBearerInfo* enbDRBConfig[MAX_UEFSM_NUM][MAX_DRB_NUM];


/*
 *
 *	ICI informations
 *
 */

// the ICI information in the transimition between RLC and RRC
typedef struct URLC_IciMsg{
	u16 rnti;   
	u8 pbCh;    //1:PCCH, 2:BCCH, 0:others
	u8 rbId;
//	u16 psn;
}__attribute__((packed))URLC_IciMsg;

// the ICI information in the transimition between PDCP and RRC
typedef struct UPDCP_IciMsg{
	u16 rnti;
	u8 pbCh;     //PBCh = 1:PCCH, PBCh = 2: BCCH, 0:CCCH
	u8 rbId;
}__attribute__((packed)) UPDCP_IciMsg;


/*
 *
 *  IOCTL messages
 *
 */

//RRC to MAC ioctl msg(Logical Channel Config)
typedef struct MAC_LogicalChannelConfig_IoctrlMsg{
	u16 crnti;
	int logicalChannelIdentity;
	struct LogicalChannelConfig logicalChannelConfig;
};

typedef struct MAC_Release_LogicalChannel_IoctrlMsg{
	u16 crnti;
	int logicalChannelIdentity;
};


//RRC to RLC ioctl msg
typedef struct T_UmUpParas{
	u16 snFiledLength;     // Size5/size10 :UM ģʽPDU��SN����ռ��bit������������UMģʽ��
};

typedef struct  T_UmDwParas{
	u16 snFiledLength;     // Size5/size10 :UM ģʽPDU��SN����ռ��bit������������UMģʽ��
	u32 timerReordering;  // 100ms:UMģʽ��t-reordering��С
};

typedef struct T_AmUpParas{
	u32 timerPollRetransmit;   //150ms:AMģʽ��tPollRetransmit
	u16 PollPDU;    //32PDU:��װ��PDU���ﵽ��ֵʱ������ѯ
	u16 PollBYTE;    //1000KB:��װ��PDU���ﵽ��ֵʱ������ѯ
	u16 maxRetxThreshold;   // 4:AMģʽ��PDU������ش�����
};

typedef struct T_AmDwParas{
	u32 timerStatusProhibit;   //150ms: AMģʽ��t-StatusProhibit��С
	u32 timerReordering;   //100ms:AMģʽ��t-reordering��С
};

typedef struct CRLC_ConfigReq_IoctrlMsg{
	  u16 crnti;      //��ʾĿ��ue
      u8 rbIdentity;
//	  u8 configCause;      //0: �½�һ�����أ� 1: ������һ������
	  u8 lcIdentity;
	  u16 Mode; 
	  struct T_UmDwParas umDwParas ;    // Modeȡ0ʱ����ֵ��Ч
	  struct T_UmUpParas umUpParas ;     // Modeȡ1ʱ����ֵ��Ч
	  struct T_AmDwParas amDwParas ;     // Modeȡ2ʱ����ֵ��Ч
	  struct T_AmUpParas amUpParas ;     // Modeȡ3ʱ����ֵ��Ч
};

/* the IOCTRL information in the transimition between RLC and RRC*/
typedef struct CRLC_DeactReq_IoctrlMsg{
	u16 rnti;
	u8 rbIdentity;
}CRLC_DeactReq_IoctrlMsg;

/* the IOCTRL information in the transimition between RLC and RRC*/
typedef struct CRLC_SuspendReq_IoctrlMsg{
	u16 rnti;
	u8 rbIdentity;
}CRLC_SuspendReq_IoctrlMsg;

/* the IOCTRL information in the transimition between RLC and RRC*/
typedef struct CRLC_ResumeReq_IoctrlMsg{
	u16 rnti;
	u8 rbIdentity;
}CRLC_ResumeReq_IoctrlMsg;


/*
 *
 *  IOCTL event code (defined and used by other layers' ioctl_handler) 
 *
 */


//RRC to USERSPACE
#define IOCCMD_RRCTOUS_UE_CONN_REQ  0x01						//1.UE��idle̬,������enbʱ,�ϱ��߲�
#define IOCCMD_RRCTOUS_UE_CONN_SUCCESS  0x02					//2.UE���ӽ����ɹ�������CONN_NORMAL̬,�ϱ��߲�
#define IOCCMD_RRCTOUS_UE_RECONFIG_SUCCESS  0x03				//3.�Ը�UE�������óɹ�,�ϱ��߲�

// Liu Yingtao 2014/10/11
#define IOCCMD_USTORRC_RECONFIG_START   0x60	   //reconfig start
#define IOCCMD_USTORRC_RECONFIG_ADDSRB  0x61		//add add_srb message  
#define IOCCMD_USTORRC_RECONFIG_ADDDRB  0x62		//add add_drb message
#define IOCCMD_USTORRC_RECONFIG_DELDRB  0x63		//add del_drb message
#define IOCCMD_USTORRC_RECONFIG_MACMAIN 0x64		//add mac_mainConfig message
#define IOCCMD_USTORRC_RECONFIG_SPS     0x65		//add sps_config message
//#define IOCCMD_USTORRC_RECONFIG_PHYCD   0x66		//add phyConfDedic message
#define IOCCMD_USTORRC_RECONFIG_STOP    0x67	   //reconfig stop
#define IOCCMD_USTORRC_RRC_CONN_RELEASE 0x68
#define IOCCMD_USTORRC_RRC_CONN_RECONFIG 0x69

#define IOCCMD_USTORRC_RRC_CONN_ACCEPT 	0x04       //��ǰenb��ue״̬��û�õ�
//2.�û��ռ�ܾ���UE����
#define IOCCMD_USTORRC_RRC_CONN_REJECT 	0x05       //��ǰenb��ue״̬��û�õ�
//3.�û��ռ䷢������������
//#define IOCCMD_USTORRC_CONN_RECONFIG 	0x06
//4.�û��ռ䷢�������ͷ�
//#define IOCCMD_USTORRC_RRC_CONN_RELEASE 	0x07 
//5.�û��ռ䷢��Ѱ��
#define IOCCMD_USTORRC_PAGING 0x12


//RRC to RLC
//#define IOCCMD_RRCTORLC_BUILD 	0x01     //����RLCʵ��,����Я����������rlc_config
//#define IOCCMD_RRCTORLC_RECONFIG 	0x02     //Я����������rlc_config
//#define IOCCMD_RRCTORLC_RELEASE 	0x03     //�ͷ�RLCʵ��
//#define IOCCMD_RRCTORLC_SUSPEND 	0x04     //����RLCʵ�� #define IOCCMD_RRCTORLC_RESUME 	    0x05     //�ָ�RLCʵ��
#define 		IOCCMD_RRCTORLC_RECONFIG			0x24
#define 		IOCCMD_RRCTORLC_STATUS				0x25
#define 		IOCCMD_RRCTORLC_DEACT				0x26
#define 		IOCCMD_RRCTORLC_SUSPEND				0x27
#define 		IOCCMD_RRCTORLC_RESUME				0x28
#define			IOCCMD_RRCTORLC_BUILD				0x29


//RRC to MAC
//#define IOCCMD_RRCTOMAC_UEFSM_BUILD_SUCCESS 	0x01     //eNB��MAC�յ����������ϵ�Msg3
#define IOCCMD_RRCTOMAC_CONFIG_LCC 	    0x41    //config LogicalChannel,����Я�����ݲ���MAC_LogicalChannelConfig_IoctrlMsg
#define IOCCMD_RRCTOMAC_RELEASE_LCC 	0x42    //release LogicalChannel,����Я������MAC_Release_LogicalChannel_IoctrlMsg
#define IOCCMD_RRCTOMAC_RELEASE_UEFSM 	0x43    //release uefsm, with crnti.
#define IOCCMD_RRCTOMAC_CONFIG_SPS      0x05
#define IOCCMD_RRCTOMAC_CONFIG_MAC_MAIN 0x06
//ioctl from mac
#define IOCCMD_MACTORRC_REPORT_CRNTI	 0x31  
//UE����ENB, �������ɹ���MAC�ϱ�C-RNTI��RRC

//ioctl from rlc
#define IOCCMD_RLCTORRC_STATUS_IND	    		0x08     //�ش���������������ش��������ϱ�

//system code used by rrcfsm_enb_ue
#define RRC_FSM_ENB_UE_OPEN	   0x10
#define RRC_FSM_ENB_UE_CLOSE	   0x11

//IOCTL event code (defined and used by rrcfsm_enb's rrc_ioctl_handler())
//ioctl from user space
//1.�û��ռ�ܾ���UE����


/*
 *
 *	event code  
 *
 */

//fsm_post_msg
//pkcket event code (used by rrcfsm_enb_ue to distinguish different packet events)
#define PKT_RLC_IND_RRC_CONN_REQUEST 	0x01    //���յ����ӽ���������
#define PKT_RLC_IND_RRC_CONN_SETUP_COMPLETE 	0x02    //���յ����ӽ�����ɱ���
#define PKT_RLC_IND_RRC_CONN_RECONFIG_COMPLETE 	0x03    //���յ�������������ɱ���


// Define fsm_ev_code when fsm_ev_type() == FSM_EV_TYPE_SELF 
//ST_INIT
#define CODE_RRC_OPEN 	0

//ST_IDLE
#define CODE_RCV_RRC_CONN_REQUEST 	1
#define CODE_SEND_MIB 8
#define CODE_SEND_SIB1 9
#define CODE_SEND_SI 10
#define CODE_SEND_PAGING 11

//ST_CONN_SETUP
#define CODE_RCV_RRC_CONN_SETUP_COMPLETE 	2
#define CODE_MAX_CONN_TIMEOUT 	3

//ST_CONN_NORMAL
#define CODE_RRC_CONN_RECONFIG 	4
#define CODE_RRC_CONN_RELEASE 	5

//ST_CONN_RECONFIG
#define CODE_RCV_RRC_CONN_RECONFIG_COMPLETE 	6

//ST_CONN_REESTABLISH 						
#define CODE_RCV_RRC_CONN_REESTABLISH 			7


static evHandle Max_Conn_Timeout = 0;       //���ӳ�ʱ��ʱ��
static evHandle Send_MIB = 0;               //����MIB��ʱ��
static evHandle Send_SIB1= 0;				//����SIB1��ʱ��
static evHandle Send_SI= 0;					//����SI��ʱ�


//delay����������ʱ�¼�,���ȱ�״̬��
void setTimer(int timerNum, int delay);

//��timerδ������Ϊ��,��ȡ�����¼�
void cancleTimer(int timerNum);

void packet_send_to_rlc(char *msg, int msg_len, u32 message_type, u16 rnti);
void packet_send_to_pdcp(char *msg, int msg_len, u32 message_type, u16 rnti);


#endif
