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
	u16    sfn; //             //系统帧号，0-1023
	u16    subframeN;//        //子帧号，0--9
} __attribute__((packed))PHY_TO_MAC_frame;
//LHL 20141124 MAC主配置
typedef struct system_Config
{ 
	struct MAC_MainConfig  MACMainConfigInfo ;
	struct RachConfigCommon  RACHCommonConfigInfo  ;
	struct PCCH_Config    PCCHConfigInfo;
	struct BCCH_Config    BCCHConfigInfo;
	struct SPS_Config     SPSConfigInfo;
	MAC_LogicalChannelConfig_IoctrlMsg  CCCHConfigInfo ; //增加CCCH的配置信息，默认配置
}systemConfig;


typedef struct mac_sv
{
	struct list_head* ULschedQue_p;//上行调度，待分配上行资源的用户队列
	struct list_head* RAschedQue_p;//RA随机接入，待响应的用户队列
	int UL_sched_flag;// 1表示上行调度队列不为空，需要进行上行调度;0表示不需要调度
	int RA_sched_flag;//1//表示RA调度队列不为空，需要进行RA调度;0表示不需要调度
	int UL_resource_flag; //0表示上行资源已经分配完 1表示上行资源还有剩余 >0也可以表示剩余资源量
	int RAR_receive_crnti;//flag if there is C-RNTI at msg3;{0,1}
    struct rnti_array rntiarray[NUM_RNTI];
	int tc_rnti_notes[NUM_RNTI];//记录tc-rnti的实时情况
    struct result_sched_algorithm schedule_scheme[DL_SCHEDULE_NUM];
    
   // bool DATA_WAIT_ALLOCATION;
	int Rlc_Request_Num[USERNUMMAX];//20140624modified，表示RLC请求的逻辑信道数量(数组的长度)
	struct list_head * Enb_MacBuffer_RLC[USERNUMMAX];//20140623modify lhl,每个用户的数据指针头部
	struct list_head * Enb_LogicalChannel_Config[USERNUMMAX];
	struct list_head * Enb_LogicalChannel_Bj[USERNUMMAX];
	temp_contention_resolution *m_temp_cr;
//	complex_frame schedule_frame[DL_SCHEDULE_NUM];//LHL 20141017,由GCX调用填写，有何玺使用，并清空
	PHY_TO_MAC_frame phy_to_mac_frame;
//	u8 prb_bitmap2[100];
	u8 prb_bitmap7[100];
	u8 next_prb_bitmap2[100];
	u8 next_prb_bitmap7[100];
	u8 dl_bitmap[100];
//	struct rnti_array rntiarray[NUM_RNTI];
//	struct result_sched_algorithm schedule_scheme[DL_SCHEDULE_NUM];
//	DL_TBsize_ue TBsize_ue[USERNUMMAX];//LHL20141011,GCX调度后填充，HX复用时使用，初始化为0
	Ue_ta_info ue_ta[USERNUMMAX];//LHLmodified  用户的TA,由PHYIOCTL 更新，复用模块使用，并把flag置为0；
	systemConfig systemconfigInfo;
	int cnt_test;
	u32 send_rar_flag;//20150104联调添加的调试代码，初始为1表示要发RAR，收到用户空间IOCTL后为0，不发RAR
	u32 lost_pktnum_uplink;
	u32 total_pktnum_uplink;
	u32 lost_pktnum_downlink;
	u32 total_pktnum_downlink;
} mac_sv;


/* IOCTRL Command definition */
#define IOCCMD_RRCtoMAC_reset           	 0x01
#define IOCCMD_RRCtoMAC_LC_config          	 0x41 //携带参数 
#define IOCCMD_RRCtoMAC_LC_release           0x42 //携带参数 C_RNTI LCid 
#define IOCCMD_RRCtoMAC_UE_release           0x43 //携带参数 C_RNTI 释放该RNTI对应的UE的所有配置信息
#define IOCCMD_MACtoRRC_RNTI_indicate        0x31 //携带参数 C_RNTI 告知RRC RNTI值

#define IOCCMD_MACTOPHY_UL_DCI 0x12 //20141121
#define IOCCMD_MACTOPHY_DL_DCI 0x13
#define IOCCMD_MACTOPHY_RAR_DCI 0x14

#define IOCCMD_RLCtoMAC_datasend_Req         0x0B //携带数据 
#define IOCCMD_MACtoRLC_datasend_Allow       0x23 //携带数据 

#define IOCCMD_PHYtoMAC_RA_Req               0x03   //携带参数，RA-RNTI,RAPID(可能有多个),TA,
#define IOCCMD_PHYtoMAC_SR                   0x04   //物理层接收到某个UE的SR,携带参数C-RNTI
#define IOCCMD_PHYtoMAC_TA			0x06//物理层配置TA值给MAC，带参数UE_TA_INFO
#define IOCCMD_PHYtoMAC_FRAME			0x07//物理层配置帧号值给MAC，带参数PHY_TO_MAC_frame
#define IOCCMD_TEST_WITHDATA                 0x05  //测试带参数的IOCTL



/**********分割线***20150104联调测试代码，配置ENB不发RAR来演示错误处理***for test**********/
#define _IOCTLtoENBMAC_RAR_Failed  0x70 //配置ENB MAC不发RAR
#define _IOCTLtoENBMAC_RAR_Send 0x71//配置ENB MAC发RAR,相当于撤销上一条命令
#define _IOCTLtoENBMAC_PKT_NUM 0x72
/**********分割线****************/

#define IOCCMD_MACtoSRIO_RA_Complete 0x48


/*IOCRTL Command data structure*/
/*typedef struct MAC_LogicalChannelConfig_IoctrlMsg{
	u16 crnti;
	int logicalChannelIdentity;
	struct LogicalChannelConfig logicalChannelConfig;
};
*/

//LHL 20141011
/*typedef struct DL_TBSIZE_UE{//下行每个用户当前TTI可以发送的最大长度
	u16 rnti;//由耿灿锡资源分配时填充
	u32 tbsize;//由HX复用时使用，使用后清空为0
}DL_TBsize_ue;*///暂时使用这个schedule_scheme 中的tbsize

struct MAC_Release_LogicalChannel_IoctrlMsg{
	u16 crnti;
	int lcid;
}__attribute__((packed));

struct MAC_Release_Uefsm{
	u16 crnti;
}__attribute__((packed));

/* // RA请求的格式  暂时以S_RAinfo 为准 
typedef struct RA_req_info
{
	u16 ra_rnti;
	u8 rapid;//ra_preamble_index 暂时只实现为只含一个rapid
}__attribute__((packed))RA_req_info;
*/

/*self evens denition*/

#define TIME_TODO_ULSCHED  0x10  //该事件由定时器超时产生，表示可以进行上行调度

/*condition definition 条件宏定义 */

#define MAC_PK_FROM_LOWER (fsm_ev_type()==FSM_EV_TYPE_PKT_IND)
#define	MAC_PK_FROM_UPPER (fsm_ev_type()==FSM_EV_TYPE_PKT_REQ)
#define MAC_OPEN (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code()== FSM_EV_CORE_OPEN)
#define MAC_CLOSE (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code() == FSM_EV_CORE_CLOSE)
#define IOCTRL_ARRIVAL (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code() == FSM_EV_IOCTRL)

#define MAC_RESET (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_RRCtoMAC_reset ) )
#define RA_REQ (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_PHYtoMAC_RA_Req ) )
#define DL_SCHED_REQ (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_RLCtoMAC_datasend_Req ) )	//条件可能需要补充
#define UL_SCHED_REQ (IOCTRL_ARRIVAL && (fsm_ev_ioctrl_cmd()== IOCCMD_PHYtoMAC_SR ) )	//条件可能需要补充
#define UL_SCHED (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == TIME_TODO_ULSCHED)



void mac_main(void);

#endif



