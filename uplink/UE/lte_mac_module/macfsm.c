#include "../fsm/fsmdec.h"
#include <linux/if_ether.h>
/****lhl�Ķ�20140410****/
#include <linux/list.h>
#include <linux/kernel.h>
#include <stddef.h>
/****lhl�Ķ�����20140410****/ 
#include "macfsm.h"
#include "macpkfmt.h"
#include "macscheduler.h"
#include "rrc_config.h"
#include "../lte_system.h"


/* fsm state id definition  ����״̬*/
#define ST_INIT 0
#define ST_IDLE 1
#define ST_CRA	2 /*contention-based random access process */
#define ST_NCRA	3
#define ST_CON  4
#define ST_SENDMSG3 5 //20140430 HQ

//testing functions ���Ժ���   HQ 
#define IOCCMD_TEST_lostUL  0x30 //����TA_timer��ʱ
#define NCRATEST 0x31

/*funcation declaration �������� */
//static void init_enter(void);   
//static void ue_mac_close(void);
static void ue_mac_sv_init(void);//��ʼ��״̬����
static void ue_mac_sv_close(void);
static void defaultconfig(void);//Ĭ������
static void macmain_defaultconfig(void);
static void sps_defaultconfig(void);
static void CCCH_defaultconfig(void);

static void ue_mac_reset(void);
static void ue_mac_rach_config(void);
static void ue_mac_main_config(void);
static void ue_mac_logCh_config(void);
static void ue_mac_PCCH_config(void);
static void ue_mac_BCCH_config(void);
static void ue_mac_SPS_Config(void);
static void TATimer_config(void);
static void ue_mac_lc_release(void);

static void idle_default_handler(void);
static void cra_default_handler(void);
static void ncra_default_handler(void);
static void con_default_handler(void);
static void sendmsg3_default_handler(void);

static void test_print_pkt_num(void);

/****random access processure  __Chen Lang *******/
static unsigned char RandomlySelectRaPreamble(void);
static void StartWaitingForRaResponse(void);
static void SendRaPreamble(RACH_ConfigDedicated *randomaccess_info);
static void doStartNonContentionBasedRandomAccessProcedure();
static void doStartContentionBasedRandomAccessProcedure();
static void NC_RaResponseFailed(void);
static void C_RaResponseFailed(void);
static void cleanharqBuff(void);
static void ContentionFailed(void);
static void waitsending_msg3(void);//defined by HQ 20140430 
static void send_msg3(void); //defined by HQ 20140430 
static void cra_success(void);
static void ncra_success(void);
//static void randomaccess_success(void);


static void RARTA_handleA(void);
static void RARTA_handleB(void);


//handle timer expiry ��ʱ����ʱ�¼��Ĵ���
static void handle_timeAlignmentTimerExpire(void);//����ʧ����timeAlignmentTimer��ʱ
static void handle_PeriodicBSRTimerExpire(void);//��������BSR��ʱ����ʱ
static void handle_RetxBSRTimerExpire(void);//�����ش�BSR��ʱ����ʱ
static void handle_CRTimerExpire(void);
//Handle IOCTRL Command 
static void ioctrl_handler(void);
static void reports_handler(void);//�����ϱ��¼���BSR PHR 
//static void handle_SR_Fail(void); //�����˵�δ����
static void handle_HARQ_feedback(void);
static void send_SR(void);


void print_tran_info( const char *str);
void random_test(void); 
void testdoStartContentionBasedRandomAccessProcedure(void);
void testdoStartNonContentionBasedRandomAccessProcedure(void);
void RA_RRCconfig_testingfun(void); // �����õĺ��������RRC��������Ϣ 
void CRAtoCON_testingfun(void);
void NCRAtoCON_testingfun(void);
void stop_WRAP_timer(void);
void stop_CR_timer(void);
void stop_RetxBSR_timer();
void stop_TA_timer();
void stop_PeriodicBSR_timer();
void test1_idle_default_handler(void);
void test2_idle_default_handler(void);
static void test_init_logicalchannel(u16 lcid);

/*
******************************
->Change Data and time: 
->Function:Initialization parameters
->Change:
->Details:״̬��
->input:
->output:
->Special:
*******************************
*/
void mac_main()
{
	FSM_ENTER(mac_main);
	FSM_BLOCK_SWITCH
	{
		FSM_STATE_FORCED(ST_INIT, "INIT", ue_mac_sv_init(), )
		{
			FSM_TRANSIT_FORCE(ST_IDLE, , "default", "", "INIT -> IDLE");
		}
		FSM_STATE_UNFORCED(ST_IDLE, "IDLE", , )
		{
			FSM_COND_TEST_IN("IDLE")				
				FSM_TEST_COND(START_C_RANDOM_ACCESS)
				FSM_TEST_COND(START_NC_RANDOM_ACCESS)
				FSM_TEST_COND(MAC_RESET)
			FSM_COND_TEST_OUT("IDLE")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_CRA, doStartContentionBasedRandomAccessProcedure(), "IDLE -> CRA")
				FSM_CASE_TRANSIT(1, ST_NCRA, doStartNonContentionBasedRandomAccessProcedure(), "IDLE -> NCRA")
				//FSM_CASE_TRANSIT(2, ST_IDLE, print_tran_info("reset IDLE -> IDLE"), "IDLE -> IDLE")
				FSM_CASE_TRANSIT(2, ST_IDLE, ue_mac_reset(), "IDLE -> IDLE")
				FSM_CASE_DEFAULT(ST_IDLE,idle_default_handler() , "IDLE->IDLE")	//transit to idle state	by default.
			}
		}
		FSM_STATE_UNFORCED(ST_CRA,"CRA", ,)
		{
			FSM_COND_TEST_IN("CRA")
				FSM_TEST_COND(TimeAlignmentTimerExpire)
				FSM_TEST_COND(RANDOM_ACCESS_FAIL)
				FSM_TEST_COND(RARREV_SUCCESS)
				FSM_TEST_COND(CONTENTION_FAIL )
				FSM_TEST_COND(CONTENTION_SUCCESS)
				FSM_TEST_COND(MAC_RESET)
			FSM_COND_TEST_OUT("CRA")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_IDLE,handle_timeAlignmentTimerExpire(), "CRA-> IDLE")
				FSM_CASE_TRANSIT(1, ST_IDLE, C_RaResponseFailed(), "CRA -> IDLE")
				FSM_CASE_TRANSIT(2, ST_SENDMSG3 , waitsending_msg3(), "CRA -> SENDMSG3")
				FSM_CASE_TRANSIT(3, ST_IDLE, ContentionFailed(), "CRA -> IDLE")
				FSM_CASE_TRANSIT(4, ST_CON , cra_success() , "CRA -> CON")
				//FSM_CASE_TRANSIT(4, ST_IDLE, print_tran_info("reset CRA -> IDLE"), "CRA -> IDLE")
				FSM_CASE_TRANSIT(5, ST_IDLE, ue_mac_reset(), "CRA -> IDLE")
				FSM_CASE_DEFAULT(ST_CRA,cra_default_handler() , "CRA->CRA")	//transit to CRA state	by default.
			}
		}
		FSM_STATE_UNFORCED(ST_SENDMSG3,"SENDMSG3", ,)
		{
			FSM_COND_TEST_IN("SENDMSG3")
				//FSM_TEST_COND(HAVE_SENDMSG3) //testing code 
				FSM_TEST_COND(TimeAlignmentTimerExpire)
				FSM_TEST_COND(MAC_PK_FROM_UPPER)//LHL 20140726
				FSM_TEST_COND(RA_SEND_MSG3)//LHL 20140726
				FSM_TEST_COND(MAC_RESET)
			FSM_COND_TEST_OUT("SENDMSG3")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_IDLE,handle_timeAlignmentTimerExpire(), "SENDMSG3-> IDLE")
				FSM_CASE_TRANSIT(1, ST_CRA, send_msg3(), "SENDMSG3 -> CRA")
				FSM_CASE_TRANSIT(2, ST_CRA, send_msg3(), "SENDMSG3 -> CRA")//����con״̬
				//FSM_CASE_TRANSIT(1, ST_IDLE, print_tran_info("reset SENDMSG3 -> IDLE"), "SENDMSG3 -> IDLE")
				FSM_CASE_TRANSIT(3, ST_IDLE,ue_mac_reset(), "SENDMSG3 -> IDLE")
				FSM_CASE_DEFAULT(ST_SENDMSG3,sendmsg3_default_handler() , "SENDMSG3->SENDMSG3")	//transit to SENDMSG3 state	by default.
			}
		}		
		FSM_STATE_UNFORCED(ST_NCRA,"NCRA", , )
		{
			FSM_COND_TEST_IN("NCRA")
				FSM_TEST_COND(TimeAlignmentTimerExpire)
				FSM_TEST_COND(RANDOM_ACCESS_FAIL)
				FSM_TEST_COND(RARREV_SUCCESS)
				FSM_TEST_COND(MAC_RESET)
			FSM_COND_TEST_OUT("NCRA")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_IDLE,handle_timeAlignmentTimerExpire(), "NCRA-> IDLE")
				FSM_CASE_TRANSIT(1, ST_IDLE,NC_RaResponseFailed(), "NCRA -> IDLE")
				FSM_CASE_TRANSIT(2, ST_CON, ncra_success(), "NCRA -> CON")
				// FSM_CASE_TRANSIT(2, ST_IDLE,print_tran_info("reset NCRA -> IDLE"), "NCRA -> IDLE")
				FSM_CASE_TRANSIT(3, ST_IDLE,ue_mac_reset(), "NCRA -> IDLE")
				FSM_CASE_DEFAULT(ST_NCRA,ncra_default_handler() , "NCRA -> NCRA")	//transit to NCRA state	by default.
			}
		}
		FSM_STATE_UNFORCED(ST_CON,"CON", , )		//д��������20140320
		{
			FSM_COND_TEST_IN("CON")
				FSM_TEST_COND(TimeAlignmentTimerExpire)
				FSM_TEST_COND(SR_FAIL)
				FSM_TEST_COND(MAC_RESET)
			FSM_COND_TEST_OUT("CON")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_IDLE,handle_timeAlignmentTimerExpire(), "CON -> IDLE")//handle_timeAlignmentTimerExpire()
				FSM_CASE_TRANSIT(1, ST_CRA, doStartContentionBasedRandomAccessProcedure() , "CON -> CRA")
				//FSM_CASE_TRANSIT(2, ST_IDLE,print_tran_info("reset CON -> IDLE"), "CON -> IDLE")
				FSM_CASE_TRANSIT(2, ST_IDLE,ue_mac_reset(), "CON -> IDLE")
				FSM_CASE_DEFAULT(ST_CON,con_default_handler() , "CON -> CON")	//transit to CON state	by default.
			}
		}
	}
	FSM_EXIT(0)
}



/*
******************************
->Change Data and time: 
->Function:Initialization parameters
->Change:
->Details: ��ʼ�� �Լ�Ĭ������
->input:
->output:��ʼ��ȫ�ֱ���
->Special:
*******************************
*/
static void ue_mac_sv_init()
{
	FIN(ue_mac_sv_init());
	int len;
	
	SV_PTR_GET(mac_sv);
	print_tran_info("FSM INIT-init SV");//testing code
	SV(TA_Periodic_time)=300000;//testing code ,ʵ��ӦΪһ��Ĭ��ֵ��Ĭ��ֵ����
	Init_Uemac_Scheduler();
	SV(sys_frame.frameNo)=0;//modified LHL 20141105��ʼ��ϵͳ֡����֡��
	SV(sys_frame.subframeNo)=0;
	SV(recv_frame).subframeNo=0;//���
	SV(recv_frame).frameNo=0;
	SV(ue_schedule_frame.frameNo)=0;
	SV(ue_schedule_frame.subframeNo)=0;
	//SV(flag123)=0;//LHL test 0924
	//SV(TA_fromRAR)=0;
	SV(TA_value)=0;//LHL 20141021
	SV(m_temp_cr)=(temp_contention_resolution*)fsm_mem_alloc(sizeof(temp_contention_resolution));
	//��ʼ��������ʱ��
	
	SV(TATimer.time_value) = 0;
	SV(TATimer.timer_sign) = NULL;
	SV(TATimer.flag) = false;
	SV(CRTimer.time_value) = 0;
	SV(CRTimer.timer_sign) = NULL;
	SV(CRTimer.flag) = false;
	SV(RetxBSRTimer.time_value) = 0;
	SV(RetxBSRTimer.timer_sign) = NULL;
	SV(RetxBSRTimer.flag) = false;
	SV(PeriodicBSRTimer.time_value) = 0;
	SV(PeriodicBSRTimer.timer_sign) = NULL;
	SV(PeriodicBSRTimer.flag) = false;	
	SV(WaitforRAresponseTimer.time_value) = 0;
	SV(WaitforRAresponseTimer.timer_sign) = NULL;
	SV(WaitforRAresponseTimer.flag) = false;
	SV(msg3_buf_ptr) = NULL;	
	SV(ra_allocation_res)=0;
	defaultconfig();//���һЩĬ������
	RA_RRCconfig_testingfun(); // �����������������õĺ��������RRC��������Ϣ
	SV(UL_resource_info.resource_flag)= false; //testing code
	//SV(UL_resource_info.m_tbsize)= 2400;//��λӦ��Ϊbit//testing code 
	//SV(C_RNTI) = 11;
	//��ʼ������ȫ�ֱ���
	fsm_mem_set(&SV(ratype),0,sizeof(RA_Type));
	SV(sendmsg3)=0;//0:û����MSG3��1:����MSG3
	SV(pdcch_rnti)=0;//0:PDCCH����ͨ��C_RNTIѰַ��1:��ͨ��C_RNTIѰַ
	SV(Tbsize_Complex)=0;//modified by lhl ,20140718,to ����ģ�飬���Է�����������
	//test_init_logicalchannel(1);//TEST 20141103
	//test_init_logicalchannel(3);//TEST 20141103
	SV(contention_failed_num)=0;
	SV(rar_failed_num)=0;
	SV(lost_pkt_num_uplink)=0;
	SV(pkt_num_uplink)=0;
	SV(lost_pkt_num_downlink)=0;
	SV(pkt_num_downlink)=0;
FOUT;
}

//TEST FUNCTION20141103
static void test_init_logicalchannel(u16 lcid)
{
	FIN(test_init_logicalchannel());
	SV_PTR_GET(mac_sv);
	MAC_LogicalChannelConfig_IoctrlMsg *lc_info=(MAC_LogicalChannelConfig_IoctrlMsg *)fsm_mem_alloc(sizeof(MAC_LogicalChannelConfig_IoctrlMsg));
	lc_info->logicalChannelIdentity=lcid;
	lc_info->logicalChannelConfig.haveUl_SpecificParameters=true;
	lc_info->logicalChannelConfig.ul_SpecificParameters.priority=2;
	lc_info->logicalChannelConfig.ul_SpecificParameters.prioritisedBitRate=kBps128;
	lc_info->logicalChannelConfig.ul_SpecificParameters.logicalChannelGroup=1;	
	Init_LogicalChannel_ConfigInfo(lc_info); 
	fsm_mem_free(lc_info);//��Ӧ�ͷ��ڴ�
	FOUT;
}

/*
******************************
->Change Data and time: 
->Function:״̬���ر�ʱ�ͷ���Դ
->Change:
->Details:
->input:
->output:�ͷ��ڴ�
->Special:
*******************************
*/
static void ue_mac_sv_close()
{
	FIN(ue_mac_sv_close());
	SV_PTR_GET(mac_sv);
	if(SV(m_temp_cr) != NULL)
	{
		fsm_mem_free(SV(m_temp_cr));
		SV(m_temp_cr) = NULL;
	}
	Free_Uemac_Scheduler_Resource();
	if(SV(msg3_buf_ptr)!=NULL)
	{
		fsm_pkt_destroy(SV(msg3_buf_ptr));
		SV(msg3_buf_ptr)=NULL;
	}
	FOUT;
}

/*
******************************
->Change Data and time: 
->Function:Initialization parameters
->Change:
->Details:Ĭ�����ã���Ҫ�ǿ���ʱ������
->input:
->output:MAC����ҪĬ������(SPS��CCCH��ϵͳ����)
->Special:
*******************************
*/
static void defaultconfig()
{
	FIN(defaultconfig());
	macmain_defaultconfig();
	sps_defaultconfig();
	CCCH_defaultconfig();//CCCH�ŵ�Ĭ������
	//fsm_schedule_self(MAC_BJ_TIME, LC_BJ_CODE);	//for test
	FOUT;
}

/*
******************************
->Change Data and time: 
->Function:MAC��ҪĬ������
->Change:
->Details:
->input:
->output:��systemconfigInfo.MACMainConfigInfo������
->Special:
*******************************
*/
static void macmain_defaultconfig()
{
	FIN(macmain_defaultconfig());
	SV_PTR_GET(mac_sv);
	SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.maxHARQ_Tx) = maxHARQ_Tx_n5;
	//fsm_printf("test maxHARQTX:%d \n ",SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.maxHARQ_Tx));//testing code
	SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.periodicBSR_Timer)= periodicBSR_Timer_infinity;//�ò���ֵ��ʾ�ö�ʱ��������
	SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.retxBSR_Timer)= retxBSR_Timer_sf2560 ;
	SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.ttiBundling)= false ;
	SV(systemconfigInfo.MACMainConfigInfo.drx_Config.choice.setup.haveShortDRX)= false ;//means release
	SV(systemconfigInfo.MACMainConfigInfo.type)= MAC_MainConfig_TYPE_RELEASE; //means phr-Config release ??  
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:SPSĬ������
->Change:
->Details:
->input:
->output:��systemconfigInfo.SPSConfigInfo������
->Special:
*******************************
*/
static void sps_defaultconfig()
{
	FIN(sps_defaultconfig());
	SV_PTR_GET(mac_sv);
	SV(systemconfigInfo.SPSConfigInfo.haveSPS_ConfigDL)=false;
	SV(systemconfigInfo.SPSConfigInfo.haveSPS_ConfigUL)=false; 
FOUT;
}
/*
******************************
->Change Data and time: 
->Function:CCCHĬ������
->Change:
->Details:
->input:
->output:��systemconfigInfo.CCCHConfigInfo������
->Special:
*******************************
*/
static void CCCH_defaultconfig()
{
	FIN(CCCH_defaultconfig());
	SV_PTR_GET(mac_sv);
	MAC_LogicalChannelConfig_IoctrlMsg *ccch_info=(MAC_LogicalChannelConfig_IoctrlMsg *)fsm_mem_alloc(sizeof(MAC_LogicalChannelConfig_IoctrlMsg));
	SV(systemconfigInfo.CCCHConfigInfo.logicalChannelIdentity)=0;
	SV(systemconfigInfo.CCCHConfigInfo.logicalChannelConfig.haveUl_SpecificParameters)=true;
	SV(systemconfigInfo.CCCHConfigInfo.logicalChannelConfig.ul_SpecificParameters.priority)=1;
	SV(systemconfigInfo.CCCHConfigInfo.logicalChannelConfig.ul_SpecificParameters.prioritisedBitRate)= infinity;
	SV(systemconfigInfo.CCCHConfigInfo.logicalChannelConfig.ul_SpecificParameters.logicalChannelGroup)= 0;
	fsm_mem_cpy(ccch_info, &SV(systemconfigInfo.CCCHConfigInfo),sizeof(MAC_LogicalChannelConfig_IoctrlMsg));  
	Init_LogicalChannel_ConfigInfo(ccch_info); 
	fsm_mem_free(ccch_info);//��Ӧ�ͷ��ڴ�
	fsm_printf("[UEMAC][init]CCCH_defaultconfig completed\n");
	FOUT;
}

/*
******************************
->Change Data and time: 
->Function:
->Change:
->Details:IDLE״̬�µĳ��ں���
->input:
->output:
->Special:
*******************************
*/
static void idle_exit()
{
	FIN(idle_exit());
	FOUT;
}

/***** HuangQiong *****/
/*
******************************
->Change Data and time: 20140411;20141105
->Function: IDLE״̬��Ĭ��ת�ƵĴ�����
->Change:����BJ�Ķ�ʱ�����¼�
->Details:��Ҫ����״̬���¼���IOCTL�¼�����ת����ͬ��״̬
->input:
->output:
->Special:
*******************************
*/
static void idle_default_handler()
{
	RLC_Request rlc_request_array[1];
	char *tmpdata_ptr;
	int tmpdata;
	FSM_PKT* pkptr;//test
	FIN(idle_default_handler());
	SV_PTR_GET(mac_sv);
	print_tran_info("[UEMAC][idle_default]MAC idle_default_handler");//testing code 
	if(MAC_CLOSE)
	{
		print_tran_info("[UEMAC][idle_default]MAC FSM is closed ");//testing code
		ue_mac_sv_close();
	}
	if(MAC_PK_FROM_LOWER)
	{//ͨ��ICI��Ϣ�жϰ����ͣ�Ӧ���ǹ㲥��Ϣ�����÷��ͺ���������RLC
		print_tran_info("[UEMAC][idle_default][-->]MAC IDLE receive a data packet from PHYadapter\n"); //testing code
		//fsm_pkt_destroy(fsm_pkt_get());
		if(SV(CRTimer.flag)==true)
			fsm_printf("[UEMAC][idle_default]SV(CRTimer.flag)=true\n");//testing code 
		else
			fsm_printf("[UEMAC][idle_default]SV(CRTimer.flag)=false\n");//testing code 	 
		if(SV(TATimer.timer_sign)==NULL)
		{
			//������ʧ�������IDLE̬
			fsm_printf("TA timer,destroy pkt\n");
			//fsm_pkt_destroy(fsm_pkt_get());
			decomplexUeDataPdu(fsm_pkt_get()); 
		}
		else
			decomplexUeDataPdu(fsm_pkt_get()); //SRIO��һ�����������������������֪��Ϊʲô? 20140701
	}
	if(MAC_PK_FROM_UPPER )
	{//��IDLE״̬��Ӧ���ǲ�������������,���Դ�ӡһ��������Ϣ
		print_tran_info("[UEMAC][idle_default][-->]MAC IDLE receive a data packet from RLC, error, and then start CRA\n");//testing code 
		//fsm_schedule_self(0, Start_ContentionBase_RandomAcc);//���Ը��ý⸴�ã���ʱע�͵� 
		if(SV(TATimer.timer_sign)==NULL)
		{
			//������ʧ�������IDLE̬
			//fsm_pkt_destroy(fsm_pkt_get());
			fsm_printf("TA timer,destroy pkt\n");
			//fsm_pkt_destroy(fsm_pkt_get());
			complexUeMacPdu(fsm_pkt_get());
			if(SV(Tbsize_Complex)!=0)
				SV(Tbsize_Complex)=0;//����֮������TBSIZE
		}
		else
		{
			complexUeMacPdu(fsm_pkt_get());
			if(SV(Tbsize_Complex)!=0)
				SV(Tbsize_Complex)=0;//����֮������TBSIZE
		}
	}
	if(TimeAlignmentTimerExpire)
	{
		handle_timeAlignmentTimerExpire();
	}
	if(LogicalChannel_BJ)//modified 20141105 LHL,����BJ
	{
		FlushBj();
		fsm_schedule_self(MAC_BJ_TIME, LC_BJ_CODE);
	}
	if(IOCTRL_ARRIVAL)
	{//����IOCTL����
		print_tran_info("[UEMAC][idle_default]MAC IDLE default ioctl hander,");//testing code
		u32 cmd1=fsm_ev_ioctrl_cmd();
		fsm_printf("[MAC][DEFAULT_CMD]%d\n",cmd1);
		switch(fsm_ev_ioctrl_cmd())
		{
			//����RLC��������������
			case IOCCMD_RLCtoMAC_datasend_Req :
				tmpdata_ptr = (char *)fsm_data_get();
				tmpdata = *((u32*)tmpdata_ptr);//ȡ��ָʾ���鳤�ȵ���Ϣ				
				fsm_printf("[UEMAC][idle_default]MAC IDLE receive a RLCdatareq,");//testing code
				fsm_printf("[UEMAC][idle_default]tmpdata:%d ",tmpdata);//testing code
				fsm_printf("[UEMAC][idle_default]txQueueSize:%d\n",((RLC_Request *)(tmpdata_ptr+sizeof(u32)))->txQueueSize);//testing code
				DoRefreshRLCBuffserRequest(RlcRequest_arraytolist((RLC_Request *)(tmpdata_ptr+sizeof(u32)),tmpdata));//���´������ݻ�����Ϣ
				//tmpdata_ptr+sizeof(int)//����ƶ�4���ֽ� ָ������ͷ
				fsm_data_destroy((void *)tmpdata_ptr);//�ͷ��ڴ�
				if(SV(LCGZeroToData)== true)//HQ201407040��� �ж��Ƿ񴥷�regularBSR
					DoProduceBsr_LCGZeroToData();//�ú���ִ�����SV(LCGZeroToData)��Ϊfalse	 	 
				//fsm_schedule_self(0,Start_ContentionBase_RandomAcc); //����������� ��ʱ�䵥λ��10us ���ʱ�����ö೤����
				fsm_schedule_self(1000,Start_ContentionBase_RandomAcc); //1000 for test
				SV(ratype.ra_type)=2;
			break;
			//����PHY��RA��������
			case IOCCMD_PDCCHtoMAC_RandomAcc_Req: 	
			//��������Ĵ�����һ�� ���Դ˴�û��break	  
				tmpdata_ptr = fsm_data_get();
				print_tran_info("[UEMAC][idle_default]IDLE receive a RA req from other layer,");
				if(tmpdata_ptr > 0)//��ָʾ�˹��ڽ����ǰ����
				{
					fsm_printf("[UEMAC][idle_default]IDLE receive a ncra order ");
					fsm_mem_cpy(&(SV(RA_info)),tmpdata_ptr,sizeof(RACH_ConfigDedicated));
					fsm_printf("[UEMAC][idle_default]the RAPID is %d\n",SV(RA_info.ra_PreambleIndex));
					if(tmpdata_ptr != NULL)
					{
						fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
						fsm_printf("[UEMAC][idle_default]fsm_ev_data,then free the memory\n");
					}
					fsm_schedule_self(0, Start_NonContentionBase_RandomAcc );//�����Ǿ���������� //�������������������ע�͵�
				}
				else //û��ָʾ���ڽ����ǰ����
				{
					print_tran_info("[UEMAC][idle_default]IDLE receive a cra order ");
					SV(ratype.ra_type)=1;
					fsm_schedule_self(0, Start_ContentionBase_RandomAcc );//���������������
				}
			break;
			//����RRC��RA��������
			case IOCCMD_RRCtoMAC_RandomAcc_Req :
				tmpdata_ptr = fsm_data_get();
				print_tran_info("[UEMAC][idle_default]IDLE receive a RA req from other layer,");
				if(tmpdata_ptr > 0)//��ָʾ�˹��ڽ����ǰ����
				{
					fsm_printf("[UEMAC][idle_default]IDLE receive a ncra order ");
					fsm_mem_cpy(&(SV(RA_info)),tmpdata_ptr,sizeof(RACH_ConfigDedicated));
					fsm_printf("[UEMAC][idle_default]the RAPID is %d\n",SV(RA_info.ra_PreambleIndex));
					if(tmpdata_ptr != NULL)
					{
						fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
						fsm_printf("[UEMAC][idle_default]fsm_ev_data,then free the memory\n");
					}
					fsm_schedule_self(0, Start_NonContentionBase_RandomAcc );//�����Ǿ���������� //�������������������ע�͵�
					//û������ ���� 20140531HQ���� 
				}
				else //û��ָʾ���ڽ����ǰ����
				{
					print_tran_info("[UEMAC][idle_default]IDLE receive a cra order ");
					SV(ratype.ra_type)=3;
					fsm_schedule_self(0, Start_ContentionBase_RandomAcc );//���������������
				}
			break;
			//����������״̬�޹ص�����
			case IOCCMD_PHYtoMAC_SYSFRAME:
				tmpdata_ptr = fsm_data_get();
				SV(sys_frame.frameNo)=((system_frame *)tmpdata_ptr)->frameNo;
				SV(sys_frame.subframeNo)=((system_frame *)tmpdata_ptr)->subframeNo;
				fsm_data_destroy(tmpdata_ptr);
			break;
			default:
				ioctrl_handler();
			break;
		}
	}
	reports_handler();//����BSR PHR���ϱ��¼� 
	FOUT;
}
/*
static void idle_default_handler()
{
//������״̬ת���޹ص��¼�:�²����ݰ������״̬�޹ص�ioctrl���BSR/PHR�����ڶ�ʱ����ʱ
	void *tmpdata_ptr;
   FIN(idle_default_handler());
   SV_PTR_GET(mac_sv);
   print_tran_info("idle_default_handler");
   if(MAC_CLOSE)
   {
      print_tran_info("MAC FSM is closed "); //testing code
      ue_mac_sv_close();
   }
   if(MAC_PK_FROM_LOWER)
   {//ͨ��ICI��Ϣ�жϰ����ͣ�Ӧ���ǹ㲥��Ϣ�����÷��ͺ���������RLC
      print_tran_info("IDLE receive a data packet from PHYadapter"); //testing code
      //decomplexUeDataPdu(fsm_pkt_get());

   }
   if(MAC_PK_FROM_UPPER )
   {//��IDLE״̬��Ӧ���ǲ�������������,���Դ�ӡһ��������Ϣ
      print_tran_info("IDLE receive a data packet from RLC, error, and then start CRA");//testing code 
      //fsm_schedule_self(0, Start_ContentionBase_RandomAcc);
      //complexUeMacPdu(fsm_pkt_get());//���������� 
     fsm_pkt_destroy(fsm_pkt_get());//testing code
     fsm_printf("destory packet\n");
   }
   if(IOCTRL_ARRIVAL)
   {
      print_tran_info("IDLE default ioctl hander");//testing code
      if(fsm_ev_ioctrl_cmd()== IOCCMD_RLCtoMAC_datasend_Req)
      {
		  tmpdata_ptr = fsm_data_get();
          //DoRefreshRLCBuffserRequest((RlcBufferRequest *)tmpdata_ptr);//���´������ݻ�����Ϣ
          fsm_schedule_self(1,Start_ContentionBase_RandomAcc); //����������� ��ʱ�䵥λ��10us ���ʱ�����ö೤����
          fsm_data_destroy(tmpdata_ptr);
       }
      else if(fsm_ev_ioctrl_cmd()== IOCCMD_RRCtoMAC_RandomAcc_Req || fsm_ev_ioctrl_cmd()== IOCCMD_PDCCHtoMAC_RandomAcc_Req )//��RRC��PDCCH����ָʾ���������
           {
             tmpdata_ptr = fsm_data_get();
             print_tran_info("IDLE receive a RA req from other layer ");
             if(tmpdata_ptr > 0)//��ָʾ�˹��ڽ����ǰ����
             {
              print_tran_info("IDLE receive a ncra order ");
              fsm_mem_cpy(&(SV(RA_info)),tmpdata_ptr,sizeof(RACH_ConfigDedicated));
              fsm_printf("the RAPID is %d\n",SV(RA_info.ra_PreambleIndex));
			  if(tmpdata_ptr != NULL)
			  {
			  	fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
				fsm_printf("fsm_ev_data,then free the memory\n");
			  }
                 
               //fsm_schedule_self(400, Start_NonContentionBase_RandomAcc );//�����Ǿ���������� //�������������������ע�͵�
               //���ǵ���ӡ�Ứ�Ѽ���΢���ʱ�䣬�򽫶�ʱʱ���趨Ϊ1ms������ͬ����ȥ��������ӡ���������ʱ����Լ��ٵ�100u����;��ʵ����Ҫ�����������              
             }
             else //û��ָʾ���ڽ����ǰ����
             {
               print_tran_info("IDLE receive a cra order ");
               fsm_schedule_self(0, Start_ContentionBase_RandomAcc );//���������������
             }

           }
           else 
             {
               ioctrl_handler();  //��״̬�޹ص�ioctrl����
             } 
    }
 FOUT;
}
*/

/*
******************************
->Change Data and time: 20140411��20141105
->Function: CRA״̬��Ĭ��ת�ƵĴ�����
->Change:����BJ�Ķ�ʱ�����¼�
->Details:��Ҫ����״̬���¼���IOCTL�¼�����ת����ͬ��״̬
->input:
->output:
->Special:
*******************************
*/
static void cra_default_handler()
{
	void *tmpdata_ptr;
	u32 tmpdata;
	FIN(cra_default_handler());
	SV_PTR_GET(mac_sv);
	print_tran_info("[UEMAC][cra_default]cra default ");//testing code
	if(SV(sendmsg3)==1 && SV(C_RNTI)!=0)
		fsm_schedule_self(0, Contention_Success );//TEST  	
	if(MAC_CLOSE)
	{
		print_tran_info("[UEMAC][cra_default]MAC FSM is closed "); //testing code
		ue_mac_sv_close();
	}
	if(MAC_PK_FROM_LOWER)
	{
		//HQ make note 20140710
		//�����DL_SCH ��ͨPDU
		//Ϊ���жϾ��������������Ҫ���Ӷ���PHY�ϱ���RNTI��UE�Լ���C_RNTI(�������) ���жԱ� 		
		decomplexUeDataPdu(fsm_pkt_get());
	}
	if(MAC_PK_FROM_UPPER)
	{
		fsm_pkt_destroy(fsm_pkt_get());
		fsm_printf("[UEMAC][cra_default]receive packet from RLC,error! \n");
	}
	if(LogicalChannel_BJ)//modified 20141105 LHL,����BJ
	{
		FlushBj();
		fsm_schedule_self(MAC_BJ_TIME, LC_BJ_CODE);
	}
	if(IOCTRL_ARRIVAL)
	{
		switch(fsm_ev_ioctrl_cmd())
		{
			//����RLC��������������
			case IOCCMD_RLCtoMAC_datasend_Req ://20150106����������״̬�·�����������ֻ������MSG3��û��MSG4
			//���յ���data request�����
				fsm_printf("[UE MAC]cra_default_handler:IOCCMD_RLCtoMAC_datasend_Req\n");
				if(SV(sendmsg3) && SV(C_RNTI) )//�ѷ���msg3 �Ҵ�������״̬��
				{
					tmpdata_ptr = (char *)fsm_data_get();
					tmpdata = *((u32*)tmpdata_ptr);//ȡ��ָʾ���鳤�ȵ���Ϣ	
					DoRefreshRLCBuffserRequest(RlcRequest_arraytolist((RLC_Request *)(tmpdata_ptr+sizeof(u32)),tmpdata));//���´������ݻ�����Ϣ
					//tmpdata_ptr+sizeof(int)//����ƶ�4���ֽ� ָ������ͷ
					fsm_data_destroy((void *)tmpdata_ptr);//�ͷ��ڴ�
					if(SV(LCGZeroToData)== true)//HQ201407040��� �ж��Ƿ񴥷�regularBSR
						DoProduceBsr_LCGZeroToData();//�ú���ִ�����SV(LCGZeroToData)��Ϊfalse	 	 
					//cra_success();//���øú�������������Ϊ�ָ����еĵ�Ч���벻������ԭ�����������
					//û�н���IOCTL

					/*******�ָ�******/
					SV(RA_info.ra_PreambleIndex) = 0;	//���ra_preamble index ra_prach_mask_index
					SV(RA_info.ra_PRACHMaskIndex) = 0; 
					SV(PREAMBLE_TRANSMISSION_COUNTER) = 0;//��������������0
					cleanharqBuff();//���HARQ��msg3�Ļ���
					SV(ra_allocation_res)=0;
					if(SV(msg3_buf_ptr) != NULL)
					{
						fsm_pkt_destroy(SV(msg3_buf_ptr));//modified by lhl 20140717
						SV(msg3_buf_ptr) = NULL; //���msg3��sk_buf����
					}
					SV(T_C_RNTI) = 0;//����T_C_RNTI
					if(SV(CRTimer.flag)==true) //ֹͣCR��ʱ��
					{
						SV(CRTimer.timer_sign)= NULL;
						SV(CRTimer.flag)= false;
						SV(CRTimer.time_value)=0;
					}
					SV(sendmsg3)=0;//��MSG3��־��Ϊ0
					//SV(ratype.ra_type)=0;//�������������Ϊ0 
					SV(pdcch_rnti)=0;
					/*******�ָ�******/
					doStartContentionBasedRandomAccessProcedure();//�������ھ�����������룬20150106LHL
					SV(ratype.ra_type)=2;
				}
				else//��������
				{
					tmpdata_ptr = (char *)fsm_data_get();
					fsm_data_destroy((void *)tmpdata_ptr);//�ͷ��ڴ�
				}				
			break;
			default:
				ioctrl_handler();//��״̬�޹ص�ioctrl����
			break;
		}
	}
		
	//����״̬�£�������RLC_DATA_REQ������ζ�ż�����ǰ�����������̡�
	//if(WaitforRAresponseExpire)
	//RAR���ճ�ʱ�Ĵ��� ������ʧ��
	/*if(CRTimerExpire)//modified by lhl 20140729,����Ҫ��
	{
	handle_CRTimerExpire();
	fsm_schedule_self(0,CONTENTION_FAIL);
	}*/
	//������ʱ����ʱ�Ĵ���  ������ʧ��
	FOUT;
}


/*
******************************
->Change Data and time: 20141105
->Function: NCRA״̬��Ĭ��ת�ƵĴ�����
->Change:����BJ�Ķ�ʱ�����¼�
->Details:��Ҫ����״̬���¼���IOCTL�¼�����ת����ͬ��״̬
->input:
->output:
->Special:
*******************************
*/
static void ncra_default_handler()
{
	FIN(ncra_default_handler());
	print_tran_info("[UEMAC][nra_default]ncra default ");//testing code
	if(MAC_CLOSE)
	{
		print_tran_info("[UEMAC][nra_default]MAC FSM is closed "); //testing code
		ue_mac_sv_close();
	}
	if(MAC_PK_FROM_LOWER)
	{
		decomplexUeDataPdu(fsm_pkt_get());
	}
	if(MAC_PK_FROM_UPPER)
	{
		fsm_printf("[UEMAC][nra_default]receive packet from RLC,error! \n");
	}
	if(LogicalChannel_BJ)//modified 20141105 LHL,����BJ
	{
		FlushBj();
		fsm_schedule_self(MAC_BJ_TIME, LC_BJ_CODE);
	}
	if(IOCTRL_ARRIVAL)
		ioctrl_handler();//��״̬�޹ص�ioctrl����
	//����״̬�£�������RLC_DATA_REQ������ζ�ż�����ǰ�����������̡�
	FOUT;
}
/*
******************************
->Change Data and time: 20141105
->Function: CON״̬��Ĭ��ת�ƵĴ�����
->Change:����BJ�Ķ�ʱ�����¼�
->Details:��Ҫ����״̬���¼���IOCTL�¼�����ת����ͬ��״̬
->input:
->output:
->Special:
*******************************
*/
static void con_default_handler()
{
	//������Ҫע�⣬��һ��ǰ�ᣬҪ��RLC�㱣֤���ڵõ����ͻ����ŷ������ݰ���MAC
	char *tmpdata_ptr;
	int tmpdata;
	FSM_PKT* pkptr;	//FOR TEST
	FIN(con_default_handler());
	SV_PTR_GET(mac_sv);
	fsm_printf("[MAC][con_default_handler]TA flag:%d\n",SV(TATimer.flag));
	if(MAC_CLOSE)
	{
		print_tran_info("[UEMAC][con_default]MAC FSM is closed "); //testing code
		ue_mac_sv_close();
	}
	if(SV(DATA_WAIT_ALLOCATION)==true && SV(UL_resource_info.resource_flag)==true)
	{//��������Դ�� �����������
		//DoResourceAllocation(SV(UL_resource_info.m_tbsize)); 
		SV(Tbsize_Complex)=SV(UL_resource_info.m_tbsize)/8;//20140718LHL ��λΪbyte,����ģ��ʹ��
		DoResourceAllocation(GetTBsize_Allocation(SV(UL_resource_info.m_tbsize)));//����MAC���Ƶ�Ԫ
		SV(UL_resource_info.resource_flag)=false;
	}
	if(MAC_PK_FROM_LOWER)
	{//ͨ��ICI��Ϣ�жϰ����� �⸴�� ���÷��ͺ���������RLC
		print_tran_info("[UEMAC][con_default]CON receive a data packet from PHYadapter");//testing code
		decomplexUeDataPdu(fsm_pkt_get());
	}
	if(MAC_PK_FROM_UPPER)
	{//ͨ��ICI��Ϣ�жϰ����� ���� ���÷��ͺ���������PHYadapter
		print_tran_info("[UEMAC][con_default]CON receive a data packet from RLC");//testing code
		//pkptr=fsm_pkt_get();
		//fsm_pkt_send(pkptr,STRM_TO_SRIO);
		complexUeMacPdu(fsm_pkt_get());
		if(SV(Tbsize_Complex)!=0)
			SV(Tbsize_Complex)=0;//����֮������TBSIZE
		//fsm_pkt_destroy(fsm_pkt_get());//testing code
		//fsm_printf("destory packet\n");
	}
  	if(LogicalChannel_BJ)//modified 20141105 LHL,����BJ
	{
		FlushBj();
		fsm_schedule_self(MAC_BJ_TIME, LC_BJ_CODE);
	}
	if(IOCTRL_ARRIVAL)
	{ //����IOCTRL Command
		if(fsm_ev_ioctrl_cmd()== IOCCMD_RLCtoMAC_datasend_Req)
		{
			tmpdata_ptr = (char *)fsm_data_get();
			tmpdata = *((u32*)tmpdata_ptr);//ȡ��ָʾ���鳤�ȵ���Ϣ
			//print_tran_info("CON receive a RLCdatareq");//testing code
			//fsm_printf("tmpdata:%d \n",tmpdata);//testing code
			//fsm_printf("txQueueSize:%d\n",((RLC_Request *)(tmpdata_ptr+sizeof(int)))->txQueueSize);//testing code
			DoRefreshRLCBuffserRequest(RlcRequest_arraytolist((RLC_Request *)(tmpdata_ptr+sizeof(u32)),tmpdata));//���´������ݻ�����Ϣ
			fsm_data_destroy((void *)tmpdata_ptr);//�ͷ��ڴ�
			if(SV(LCGZeroToData)== true)//HQ201407040��� �ж��Ƿ񴥷�regularBSR
				//RefreshBufferStatusForBSR();
				DoProduceBsr_LCGZeroToData();//�ú���ִ�����SV(LCGZeroToData)��Ϊfalse
			
			/*******for test *********/
			SV(UL_resource_info.resource_flag) = true;
			/********for test *********/
			if(SV(UL_resource_info.resource_flag) == true)
			{
				//GetTBsize_Allocation(SV(UL_resource_info.m_tbsize));//����tbsize,��λbyte,�����˷���BSR����Դ
				SV(UL_resource_info.m_tbsize)=1400*8;//for test
				SV(Tbsize_Complex)=SV(UL_resource_info.m_tbsize)/8;//20140718LHL ��λΪbyte,����ģ��ʹ��
				//fsm_printf("ready resource \n");
				if(! (list_empty(&(SV(MacBuffer_RLC)->list))))
					DoResourceAllocation(GetTBsize_Allocation(SV(UL_resource_info.m_tbsize)));  //��ʼ��Դ�������
				SV(UL_resource_info.resource_flag)=false;
				//fsm_printf("start UL Schedule \n");
				}
			else 
				send_SR();
			//HQ 20140702ע��
			//�����ж��Ƿ���Ҫ��ʼSR���̣�����Ҫ�����Ƿ���regularBSR��������
			//Ŀǰʵ����RLC��datareq�Ļ��ƺ�MAC��Դ�������ȷ���� ����յ�req���ᴥ��regularBSR 
			//�����ȫ����Э��ʵ��������SR���� RLC��Ҫ�޸�req�ķ��ͻ��Ƭ�
			//MAC����Ҫ���������һ��״̬���ȴ�SR��Ӧ�� �Լ���ش��� 
		}
		else 
			ioctrl_handler();  //��״̬�޹ص�ioctrl����		
		print_tran_info("[UEMAC][con_default]CON default ioctl hander");//testing codes
	}
	reports_handler();//����BSR PHR���ϱ��¼� 
FOUT;
}
/*
******************************
->Change Data and time: 20141105
->Function:sendmsg3״̬��Ĭ��ת�ƵĴ�����
->Change:����BJ�Ķ�ʱ�����¼�
->Details:��Ҫ����״̬���¼���IOCTL�¼�����ת����ͬ��״̬
->input:
->output:
->Special:
*******************************
*/
static void sendmsg3_default_handler()
{
	char  *tmpdata_ptr;
	int tmpdata;
	SV_PTR_GET(mac_sv);
	FIN(sendmsg3_default_handler());
	if(MAC_CLOSE)
	{
		print_tran_info("[UEMAC][msg3_default]MAC FSM is closed "); //testing code
		ue_mac_sv_close();
	}
	if(LogicalChannel_BJ)//modified 20141105 LHL,����BJ
	{
		FlushBj();
		fsm_schedule_self(MAC_BJ_TIME, LC_BJ_CODE);
	}
	/*testing code
	if(MAC_PK_FROM_UPPER)
	{
		print_tran_info("receive a data packet from RLC,send it");//testing code
		//complexUeMacPdu(fsm_pkt_get());//���������� 
		fsm_pkt_destroy(fsm_pkt_get());//testing code
		fsm_printf("destory packet\n");  
		fsm_schedule_self(50,TEST_SENDMSG3);
	}
	//testing code end */
	if(IOCTRL_ARRIVAL)
	{
		switch(fsm_ev_ioctrl_cmd())
		{
			default:
				ioctrl_handler();
			break;
		}
	}
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:���͵�������
->Change:
->Details:Ŀǰû������ķ���SR������ģ��SRһֱ����ʧ�ܣ��������������
->input:
->output:
->Special:
*******************************
*/
static void send_SR()
{
	FIN(send_SR());
	SV_PTR_GET(mac_sv);
	fsm_printf("[UE MAC]send_SR\n");
	fsm_schedule_self(0,SR_Fail);//�趨ΪSR����ʧ��
	SV(ratype.ra_type)=2;
	FOUT;
}

/*
******************************
->Change Data and time: 
->Function:����״̬��Ĭ��ת�ƵĴ�����
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void ioctrl_handler()
{
	void *tempdata_ptr;
	UEPHY_TO_MAC_ULgrant *tempulgrant;
	u32 rar_failed_times;//201501��ʾ�ƻ�һ���û��ռ�������ӵı���
	u32 contention_failed_times;//201501��ʾ�ƻ�һ���û��ռ�������ӵı���
	FIN(ioctrl_handler());

	SV_PTR_GET(mac_sv);

	int cmd_value=fsm_ev_ioctrl_cmd();

	switch(cmd_value)
	{
		case IOCCMD_RRCtoMAC_recv_sysinfo :  
			fsm_printf("[MAC][RECVSYS]\n");
			fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACtoPHY_recv_sysinfo  , NULL, 0);
			//����ioctrl��������������㣬ָʾ�����ʹ�ù㲥RNTI����ϵͳ��Ϣ
		break;
		case IOCCMD_RRCtoMAC_stop_recv_sysinfo : 
			fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACtoPHY_stop_recv_sysinfo , NULL, 0); 
			//����ioctrl��������������㣬ָʾ�����ֹͣ����ϵͳ��Ϣ
		break ;
		case IOCCMD_RRCTOMAC_CONFIG_TAT : 
			fsm_printf("[UEMAC][RRCTOMAC_TA]rrctomac_taconfig\n");
			//TATimer_config();//����RRC����TA��ʱ������������ 
		break;
		case IOCCMD_RRCtoMAC_mainconfig :
			fsm_printf("[UEMAC][RRCTOMAC_mainconfig]rrctomac_mainconfig\n");
			ue_mac_main_config(); 
		break;
		case IOCCMD_RRCtoMAC_RACHcommonconfig : 
			fsm_printf("[UEMAC][RRCTOMAC_rachconfig]rrctomac_rachconfig\n");
			ue_mac_rach_config();
		break;
		case IOCCMD_RRCtoMAC_LCconfig   : 
			fsm_printf("[UEMAC][RRCTOMAC_lcconfig]rrctomac_lcconfig\n");
			ue_mac_logCh_config();
		break;
		case IOCCMD_RRCTOMAC_CONFIG_BCCH : 
			fsm_printf("[UEMAC][RRCTOMAC_bcchconfig]rrctomac_bcchconfig\n");
			ue_mac_BCCH_config();
		break;
		case IOCCMD_RRCTOMAC_CONFIG_PCCH : 
			fsm_printf("[UEMAC][RRCTOMAC_pcchconfig]rrctomac_pcchconfig\n");
			ue_mac_PCCH_config();
		break;
		case IOCCMD_RRCTOMAC_CONFIG_SPS  : 
			fsm_printf("[UEMAC][RRCTOMAC_spsconfig]rrctomac_spsconfig\n");
			ue_mac_SPS_Config();
		break;
		case IOCCMD_RRCtoMAC_LCrelease : 
			//release LC ����ĳ���ŵ�
			ue_mac_lc_release();
		break;
		case IOCCMD_Harq_feedback : 
			handle_HARQ_feedback();
		break;
		case IOCCMD_PDCCHtoMAC_ULGRANT : //PHY��PDCCH�յ��ϵĺ���UL_grant��DCI,���͸�MAC
		//MAC�����յ���ul_grant �޸�������Դ״̬
		//����MSG4�������룬�ǳ�ʼ�����������
			
			tempdata_ptr = fsm_data_get();
			tempulgrant=(UEPHY_TO_MAC_ULgrant *)tempdata_ptr;
			fsm_printf("[LHL]TEMP ULGRANT:%d\n",tempulgrant->ulgrant.RIV);
			SV(recv_frame).frameNo=tempulgrant->frameNo;
			SV(recv_frame).subframeNo=tempulgrant->subframeNo;
			if(tempulgrant->m_rnti == SV(C_RNTI))
				 SV(pdcch_rnti)=1;//PDCCHͨ��m_RNTI����
			if(SV(C_RNTI) && SV(sendmsg3) && SV(pdcch_rnti) && (SV(ratype.ra_type)==2) )//3//3GPP�����ݽ�P121
			{
				fsm_printf("[UEMAC][ioctl_handler]UE MAC ULGRANT:Contention Resolution successfully\n");
				fsm_schedule_self(0, Contention_Success );
			}
			else if(SV(C_RNTI) && SV(sendmsg3) && !SV(pdcch_rnti) && (SV(ratype.ra_type)==2) )
			{
				fsm_printf("[UEMAC][ioctl_handler]UE MAC ULGRANT:Contention Resolution fail\n");
				fsm_schedule_self(0, ContentionResolution_Fail );
			}
			fsm_printf("[UEMAC][ioctl_handler]UE MAC RECV ULGRANT\n");
			SV(UL_resource_info.m_tbsize) = DoReceiveULgrant_Tbsize(tempulgrant->ulgrant);
			fsm_printf("[MAC][ioctrl_handler]SV(UL_resource_info.m_tbsize):%d\n",SV(UL_resource_info.m_tbsize));
			//SV(UL_resource_info.m_tbsize) = DoReceiveULgrant_Tbsize(*((int *)tempdata_ptr)); //���崦���ȷ��UL_grant�����ݽṹ֮���ٶ� 
			//����Э����� ֻҪ�յ�ul_grant �������retxBSR-Timer������Ҫ�ж��Ƿ�����������ݴ���ġ�Э�� 36321-80c 5.4.5��
			SV(UL_resource_info.resource_flag) = true;
			fsm_data_destroy(tempdata_ptr);
			if(SV(RetxBSRTimer.flag) == true && SV(RetxBSRTimer.timer_sign) != NULL)
				fsm_schedule_cancel(SV(RetxBSRTimer.timer_sign));
			SV(RetxBSRTimer.time_value)	= SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.retxBSR_Timer);
			SV(RetxBSRTimer.timer_sign) = fsm_schedule_self(SV(RetxBSRTimer.time_value), RexBSRTimer_Expire);
			SV(RetxBSRTimer.flag)= true;
		break;
		case IOCCMD_TEST_lostUL : //һ����������
			fsm_schedule_self(100,TimeAlignmentTimer_Expire);
		break;
		case TEST_RECV_SYS :  
			fsm_printf("[MAC][RECVSYS]\n");
			fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACtoPHY_recv_sysinfo  , NULL, 0);
		//����ioctrl��������������㣬ָʾ�����ʹ�ù㲥RNTI����ϵͳ��Ϣ
		break;
		case TEST_RECV_PADING://test code recv pading
			fsm_printf("[MAC][RECVPAG]\n");
			fsm_do_ioctrl(STRM_TO_SRIO, TEST_MACtoPHY_PADING , NULL, 0);
		break;
		case _IOCTLtoUEMAC_RAR_Failed:
			tempdata_ptr = fsm_data_get();
			rar_failed_times=*((u32 *)tempdata_ptr);
			SV(rar_failed_num)=rar_failed_times;
			fsm_data_destroy(tempdata_ptr);
		break;
		case _IOCTLtoUEMAC_Contention_Failed:
			tempdata_ptr = fsm_data_get();
			contention_failed_times=*((u32 *)tempdata_ptr);
			SV(contention_failed_num)=contention_failed_times;
			fsm_data_destroy(tempdata_ptr);
		break;
		case _IOCTLtoUEMAC_PKT_NUM:
			test_print_pkt_num();
		break;
		default:
			//fsm_printf("[LHL]DEFAULT CMD VALUE:%d\n",cmd_value); 
		break;
/*����������������*/
	}	
	FOUT;
}
static void test_print_pkt_num()
{
	FIN(test_print_pkt_num());
	SV_PTR_GET(mac_sv);
	printk("[UEMAC]uplink lost pkt num:%d\n",SV(lost_pkt_num_uplink));
	printk("[UEMAC]uplink total pkt num:%d\n",SV(pkt_num_uplink));
	printk("[UEMAC]downlink lost pkt num:%d\n",SV(lost_pkt_num_downlink));
	printk("[UEMAC]downlink total pkt num:%d\n",SV(pkt_num_downlink));
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:����BSR PHR���ϱ��¼�
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void reports_handler()
{
	FIN(reports_handler());
	if(PeriodicBSRTimerExpire)
		handle_PeriodicBSRTimerExpire();
	if(RexBSRTimerExpire)
		handle_RetxBSRTimerExpire();
	//����PHR ��δʵ��
FOUT;
}
/*
******************************
->Change Data and time: 
->Function:TA��ʱ������
->Change:
->Details:�յ�RRC ��Ӧ��������������ö�ʱ��
->input:
->output:
->Special:
*******************************
*/
static void TATimer_config() 
{
	void *tmpdata_ptr;
	FIN(TATimer_config());
	SV_PTR_GET(mac_sv);
	int time;
	tmpdata_ptr = fsm_data_get();
	fsm_mem_cpy(&time,tmpdata_ptr, sizeof( struct TimeAlignmentTimer));
	SV(TA_Periodic_time)=time;//LHL 20141021
	//SV(TATimer.time_value)=SV(TA_Periodic_time);//LHL 20141021
	//SV(TATimer.flag)=true;
	//SV(TATimer.timer_sign)=fsm_schedule_self(SV(TATimer.time_value)*100, TimeAlignmentTimer_Expire );
	if(SV(TATimer.flag)==true)
	{//LHL 20141021TA��ʱ���������У���ʱȡ����ʱ�������¿���
		fsm_printf("[UE MAC][TATimer_config]TATimer_config\n");//LHL for test 20141021
		fsm_schedule_cancel(SV(TATimer.timer_sign));
		SV(TATimer.time_value)=SV(TA_Periodic_time);//LHL 20141021
		SV(TATimer.flag)=true;
		SV(TATimer.timer_sign)=fsm_schedule_self(SV(TATimer.time_value)*100, TimeAlignmentTimer_Expire );
		//SV(TA_timer_flag)=0;
	}//����ʱ�� û�������򲻿�����ʱ�� ֻ���涨ʱ�����ڡ�
	fsm_data_destroy(tmpdata_ptr);
FOUT;
}
/*
******************************
->Change Data and time: 
->Function:����HARQ����
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void handle_HARQ_feedback()
{
	void *tmpdata_ptr;	
	FIN(handle_HARQ_feedback());
	SV_PTR_GET(mac_sv);
	HARQ_statu_parameters ACK_statu={0,true,0};
	tmpdata_ptr = fsm_data_get();
	if( ((struct HARQ_feedback*)tmpdata_ptr)->HARQ_FEEDBACK == true )
	{
		SV(ULHARQ_status)[((HARQ_feedback*)tmpdata_ptr)->processID].avaiable_flag = true;
		SV(ULHARQ_status)[((HARQ_feedback*)tmpdata_ptr)->processID].HARQ_buffer_pointer = NULL;
		SV(ULHARQ_status)[((HARQ_feedback*)tmpdata_ptr)->processID].statu=ACK_statu;
	}
	//�������ش���Ĭ��feedback����ACK
	fsm_data_destroy(tmpdata_ptr);
FOUT;
}

/*  
//�ú������ϣ���Ϊ_fsm_current_state_ptr()�����ã����ڸ���״̬��Ĭ�ϴ������зֱ���RLC_DATE_REQ
static void handle_RLCdatasend_Req()
{
  	FIN(handle_RLCdatasend_Req());
    int *_fsm_current_state_ptr;
    int i=0;//�����õı���
  	SV_PTR_GET(mac_sv);
    DoRefreshRLCBuffserRequest((RlcBufferRequest *) fsm_ev_data());
 	_fsm_current_state_ptr = fsm_current_state_ptr_get(); //��ôд����õĲ����ǵ�ǰ״̬��ID
  	if ((*_fsm_current_state_ptr)==ST_IDLE)
  	{
  	    fsm_schedule_self(1,Start_ContentionBase_RandomAcc);  //ʱ�䵥λ��10us ���ʱ�����ö೤����
  	}
  	if( (*_fsm_current_state_ptr)==ST_CON )
    {
      if(check_resourceinfo()==AVAILABLE)
           i++; //��ʼ��Դ�������
      else
         send_SR();
    }
 	//����״̬�£�����������������ζ�ż�����ǰ�����������̡�
FOUT;
}
*/

/*
******************************
->Change Data and time: 
->Function:����TA��ʱ����ʱ
->Change:
->Details:���ö�ʱ�������HARQ���桢�ͷ�������Դ
->input:
->output:
->Special:
*******************************
*/
static void handle_timeAlignmentTimerExpire()
{
	FIN(handle_timeAlignmentTimerExpire());  
	SV_PTR_GET(mac_sv);
	SV(TATimer.time_value)=0;
	SV(TATimer.flag)=false;//���ö�ʱ���ı�־
	SV(TATimer.timer_sign)=NULL;
	cleanharqBuff(); //���HARQ����
	//fsm_do_ioctrl(STRM_TO_IP, IOCCMD_MACtoRRC_PUCCHSRS_release  , NULL , 0);  //֪ͨRRC�ͷ�PUCCH/SRS������
	//�ͷ�������Դ
	SV(UL_resource_info.resource_flag)=false;//�ͷ�������Դ
	SV(UL_resource_info.m_tbsize)=0;
											//�ͷ�������Դ����??? 
	print_tran_info("[UEMAC][handle_tatimer]LostUL"); //testing code 
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:��������BSR��ʱ����ʱ
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void handle_PeriodicBSRTimerExpire()
{
	SV_PTR_GET(mac_sv);
	FIN(handle_PeriodicBSRTimerExpire());
	DoProduceBsr_PeriodicBSRTimer();//����periodic BSR
	SV(PeriodicBSRTimer).time_value = SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.periodicBSR_Timer)*100;
	SV(PeriodicBSRTimer).timer_sign = fsm_schedule_self(SV(PeriodicBSRTimer).time_value,PeriodicBSRTimer_Expire);
	SV(PeriodicBSRTimer).flag = true;
	fsm_printf("[UEMAC][handle_periodicbsrtimer]handle PeriodicBSRTimer expire\n");//testing code 
FOUT;
}
/*
******************************
->Change Data and time: 
->Function:�����ش�BSR��ʱ����ʱ
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void handle_RetxBSRTimerExpire()
{
	SV_PTR_GET(mac_sv);
	FIN(handle_RetxBSRTimerExpire());
	DoProduceBsr_RetxBSRTimer();
	SV(RetxBSRTimer.timer_sign) = NULL;
	SV(RetxBSRTimer.flag) = false;	
	fsm_printf("[UEMAC][handle_retxbsrtimer]handle RetxBSRTimer expire\n");//testing code 
}
/*
******************************
->Change Data and time: 
->Function:�����ش�CR��ʱ����ʱ
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void handle_CRTimerExpire()
{
	SV_PTR_GET(mac_sv);
	FIN(handle_CRTimerExpire());	
	SV(CRTimer.timer_sign) = NULL;
	SV(CRTimer.flag) = false;	
	fsm_printf("[UEMAC][handle_crtimer]CRTimer expire\n");//testing code 
}


/*
******************************
->Change Data and time: 
->Function: reset ������
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void ue_mac_reset()//modified by LHL 20140717
{
	FIN( ue_mac_reset());
	SV_PTR_GET(mac_sv);
	//initialize Bj for each logical channel to zero;��ʼ��ÿ���߼��ŵ���BJΪ0 
	Zero_LogicalChannel_Bj_Reset();
	//stop (if running) all timers; ֹͣ�������ڼ�ʱ�Ķ�ʱ��
	stop_WRAP_timer();//ֹͣWaitforRAresponseTimer��ʱ��
	stop_CR_timer();//ֹͣCR��ʱ��
	stop_RetxBSR_timer();
	//stop_TA_timer();
	stop_PeriodicBSR_timer();
	//	consider timeAlignmentTimer as expired and perform the corresponding actions in subclause 5.2;
	
	//	set the NDIs for all uplink HARQ processes to the value 0;
	SV(PREAMBLE_TRANSMISSION_COUNTER) = 0;//	stop, if any, ongoing RACH procedure;
	SV(SR_COUNTER)= 0; 
	//	discard explicitly signalled ra-PreambleIndex and ra-PRACH-MaskIndex, if any;
	if(SV(ratype.ra_type)==1 ||SV(ratype.ra_type)==3)//ͨ��RRC��PDCCH��ʾָʾ���������ǰ����
	{
		SV(RA_info.ra_PreambleIndex)=0;//�����κ���ʾ��������ǰ����
		SV(RA_info.ra_PRACHMaskIndex)=0;
	}
	//	flush Msg3 buffer;
	if(SV(msg3_buf_ptr)!=NULL)
	{
		fsm_pkt_destroy(SV(msg3_buf_ptr));	
		SV(msg3_buf_ptr) = NULL; 
	}
	//	cancel, if any, triggered Scheduling Request procedure;
	Free_Bsr_Info();//	cancel, if any, triggered Buffer Status Reporting procedure;
	Empty_MACBuffer_Rlc();//���RLC���������󻺴� ���Զ���
	//	cancel, if any, triggered Power Headroom Reporting procedure;
	//	flush the soft buffers for all DL HARQ processes;
	//	for each DL HARQ process, consider the next received transmission for a TB as the very first transmission;
	SV(T_C_RNTI) = 0; //	release, if any, Temporary C-RNTI.
	if(SV(m_temp_cr) != NULL)
	{
		fsm_mem_free(SV(m_temp_cr));
		SV(m_temp_cr) = NULL;
	}
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function: ��������������
->Change:
->Details:���յ�RRC��IOCTLʱ����
->input:
->output:
->Special:
*******************************
*/
static void ue_mac_rach_config()
{
	void *tmpdata_ptr;	
	FIN(ue_mac_rach_config());
	SV_PTR_GET(mac_sv);
	tmpdata_ptr = fsm_data_get();
	//��ȡioctrlЯ�������ݣ�����������Ϣ
	SV(systemconfigInfo.RACHCommonConfigInfo) = *((struct RachConfigCommon*)tmpdata_ptr); 
	//fsm_mem_cpy(&(SV(systemconfigInfo.RACHCommonConfigInfo)), tmpdata_ptr, sizeof(struct RachConfigCommon));
	//fsm_printf("[UEMAC][rach_config]maxHARQ_Msg3Tx :%d ",	SV(systemconfigInfo.RACHCommonConfigInfo.maxHARQ_Msg3Tx) );//testing code
	//fsm_printf("[UEMAC][rach_config]mac_ContentionResolutionTimer : %d \n",SV(systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.mac_ContentionResolutionTimer));
	fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
	FOUT;
}

/*
******************************
->Change Data and time: 
->Function:MAC������
->Change:
->Details:���յ�RRC��IOCTLʱ����
->input:
->output:
->Special:
*******************************
*/
static void ue_mac_main_config()
{
	void *tmpdata_ptr;	
	FIN(ue_mac_main_config());
	SV_PTR_GET(mac_sv);
	tmpdata_ptr = fsm_data_get();	
	SV(systemconfigInfo.MACMainConfigInfo) = *((struct MAC_MainConfig*)tmpdata_ptr); //��ȡioctrlЯ�������ݣ�����������Ϣ
	fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:PCCH����
->Change:
->Details:���յ�RRC��IOCTLʱ����
->input:
->output:
->Special:
*******************************
*/
static void ue_mac_PCCH_config()
{
	void *tmpdata_ptr;	
	FIN( ue_mac_PCCH_config());
	SV_PTR_GET(mac_sv);
	tmpdata_ptr = fsm_data_get();		
	SV(systemconfigInfo.PCCHConfigInfo) = *((struct PCCH_Config*)tmpdata_ptr);  //��ȡioctrlЯ�������ݣ�����������Ϣ
	fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:BCCH����
->Change:
->Details:���յ�RRC��IOCTLʱ����
->input:
->output:
->Special:
*******************************
*/
static void ue_mac_BCCH_config()
{
	void *tmpdata_ptr;
	FIN(ue_mac_BCCH_config());
	SV_PTR_GET(mac_sv);
	tmpdata_ptr = fsm_data_get();	
	SV(systemconfigInfo.BCCHConfigInfo)= *((struct BCCH_Config*)tmpdata_ptr);  //��ȡioctrlЯ�������ݣ�����������Ϣ 
	fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:SPS����
->Change:
->Details:���յ�RRC��IOCTLʱ����
->input:
->output:
->Special:
*******************************
*/
static void ue_mac_SPS_Config()
{
	void *tmpdata_ptr;
	FIN(ue_mac_SPS_Config());
	SV_PTR_GET(mac_sv);
	tmpdata_ptr = fsm_data_get();
	SV(systemconfigInfo.SPSConfigInfo)= *((struct SPS_Config*)tmpdata_ptr); //��ȡioctrlЯ�������ݣ�����������Ϣ //���Թ��������Ĳ���û������
	fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
	FOUT;
}

/*
******************************
->Change Data and time: 
->Function:�߼��ŵ�����
->Change:
->Details:���յ�RRC��IOCTLʱ����
->input:
->output:
->Special:
*******************************
*/
static void ue_mac_logCh_config() //modified by HQ 20120506
{
	void *tmpdata_ptr;
	FIN(ue_mac_logCh_config());
	MAC_LogicalChannelConfig_IoctrlMsg *lc_configinfo=(MAC_LogicalChannelConfig_IoctrlMsg*)fsm_mem_alloc(sizeof(MAC_LogicalChannelConfig_IoctrlMsg));
	tmpdata_ptr = fsm_data_get();	
	fsm_mem_cpy(lc_configinfo, tmpdata_ptr, sizeof(MAC_LogicalChannelConfig_IoctrlMsg));//�����ݿ��������� 
	fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
	Init_LogicalChannel_ConfigInfo(lc_configinfo);//���õĺ�����Ҫע���ͷ�lc_configinfoָ�� 20140506
	//fsm_printf("[UEMAC][logch_config]LCID:%d, ",lc_configinfo->logicalChannelIdentity);
	//fsm_printf("[UEMAC][logch_config]RRC TO MAC:LCGROUP:%d\n",lc_configinfo->logicalChannelConfig.ul_SpecificParameters.logicalChannelGroup);
	//fsm_printf("[UEMAC][logch_config]prioritisedBitRate: %d \n",lc_configinfo->logicalChannelConfig.ul_SpecificParameters.prioritisedBitRate);
	fsm_mem_free(lc_configinfo);	
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:ɾ��ĳ���߼��ŵ�
->Change:
->Details:���յ�RRC��IOCTLʱ����
->input:
->output:
->Special:
*******************************
*/
static void ue_mac_lc_release()
{
	void *tmpdata_ptr;
	FIN(ue_mac_lc_release());
	tmpdata_ptr = fsm_data_get();
	Delete_LogicalChannel_ConfigInfo(*((unsigned char *)tmpdata_ptr));
	fsm_data_destroy(tmpdata_ptr);
	FOUT;
}

/**************************  HuangQiong end ***********************************/

/***************random access functions ChenLang  *********************/
/*
******************************
->Change Data and time: 
->Function:���ѡ���������msg1��ǰ����
->Change:
->Details:
->input:
->output:ѡ���ǰ����
->Special:
*******************************
*/
static u8 RandomlySelectRaPreamble()
{
	FIN(RandomlySelectRaPreamble());
	SV_PTR_GET(mac_sv);
	u8 raPreambleID;
	u8 NumberOfRA_Preambles=(SV(systemconfigInfo.RACHCommonConfigInfo.preambleInfo.numberOfRA_Preambles));
	fsm_get_random_bytes(&raPreambleID , sizeof(char));
	raPreambleID = raPreambleID%NumberOfRA_Preambles;
	//fsm_printf("[UEMAC][selectpreamble]We get random number: %d\n", raPreambleID);//testing code
	FRET(raPreambleID);
}
/*
******************************
->Change Data and time: 
->Function:����WaitforRAresponseTimer��ʱ������msg2�Ľ��մ���
->Change:
->Details:����MSG1�����
->input:
->output:
->Special:
*******************************
*/
static void StartWaitingForRaResponse()
{
	FIN(StartWaitingForRaResponse());
	SV_PTR_GET(mac_sv);
	//modified by HQ
	SV(WaitforRAresponseTimer.time_value)=SV(systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.raResponseWindowSize);
	// 1subframe=1ms=100 (10us)
	fsm_printf("[UEMAC][wait_raresponse]run here,start WRAtimer\n");//testing code
	SV(WaitforRAresponseTimer.timer_sign) = fsm_schedule_self(SV(WaitforRAresponseTimer.time_value)*100, WaitforRAresponse_Expire );
	//set up waitRaResponse_timer //������ //�¿����fsm_schdule_self()�ķ���ֵ��int *  �޸�timer�ṹ //����ͨ�� ��������
	SV(WaitforRAresponseTimer.flag)=true;
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:����msg1
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void SendRaPreamble(RACH_ConfigDedicated *randomaccess_info)
{
	FIN(SendRaPreamble());
	//modified by HQ
	fsm_printf("[UEMAC][sendrapreamble]run here,start send RAP \n");//testing code
	//fsm_octets_print(randomaccess_info,sizeof(RACH_ConfigDedicated));// for test
	fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACtoPHY_Preamble_Indicate, (void*)randomaccess_info , sizeof(randomaccess_info));
	//send the information of random access to PHYadapter
	fsm_mem_free(randomaccess_info);//20140722 modified by lhl �ͷ�IOCTL������ڴ�
	FOUT;
 }

/*
******************************
->Change Data and time: 
->Function:����Ǿ���������룬����msg1������RAR���մ���
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void doStartNonContentionBasedRandomAccessProcedure() //modified by HQ  20140413
{
	FIN(doStartNonContentionBasedRandomAccessProcedure());
	SV_PTR_GET(mac_sv);
	RACH_ConfigDedicated *randomaccess_info=(RACH_ConfigDedicated *)fsm_mem_alloc(sizeof(RACH_ConfigDedicated ));
	int mg3_buffer;
	print_tran_info("[UEMAC][noncontention_ra]startNCRA IDLE -> NCRA");//testing code
	if(SV(PREAMBLE_TRANSMISSION_COUNTER ) == 0)   //�������ĳ�ʼ��
	{ 
		SV(PREAMBLE_TRANSMISSION_COUNTER ) = 1; //��PREAMBLE_TRANSMISSION_COUNTER��1 
		SV(backoff_index) = 0;  //UE�����backoff��Ϊ0ms    
		mg3_buffer = 0;   //���MSG3����//��δʵ��
	}
	fsm_printf("[UEMAC][noncontention_ra]RA counter :%d\n",SV(PREAMBLE_TRANSMISSION_COUNTER ));//testing code
	//�ڽ��յ��Ǿ�����������ʱ���ͽ�����ָʾ��Ϣ������
	randomaccess_info->ra_PreambleIndex=SV(RA_info.ra_PreambleIndex);
	//fsm_printf("[HEXI]PREAMBLE INDEX IN MACFSM:%d\n",SV(RA_info.ra_PreambleIndex));
	
	randomaccess_info->ra_PRACHMaskIndex= SV(RA_info.ra_PRACHMaskIndex);
	SendRaPreamble(randomaccess_info);//�������ط����βΣ����øú�����Ҫ��ʵ��
	StartWaitingForRaResponse();//start waiting for the RAR
	FOUT;
}


/*
******************************
->Change Data and time: 
->Function:������������룬����msg1������RAR���մ���
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void doStartContentionBasedRandomAccessProcedure() //modified by HQ  20140419
{
	FIN(doStartContentionBasedRandomAccessProcedure());
	SV_PTR_GET(mac_sv);
	RACH_ConfigDedicated *randomaccess_info=(RACH_ConfigDedicated *)fsm_mem_alloc(sizeof(RACH_ConfigDedicated));
	int mg3_buffer;
	//print_tran_info("[UEMAC][contention_ra]startCRA IDLE -> CRA");//testing code
	if(SV(PREAMBLE_TRANSMISSION_COUNTER )== 0)   //�������ĳ�ʼ��
	{ 
		SV(PREAMBLE_TRANSMISSION_COUNTER )=1; //��PREAMBLE_TRANSMISSION_COUNTER��1 
		SV(backoff_index) = 0;  //UE�����backoff��Ϊ0ms    
		mg3_buffer=0;   //���MSG3����//��δʵ��
	}
	fsm_printf("[UEMAC][contention_ra]RA counter :%d\n",SV(PREAMBLE_TRANSMISSION_COUNTER ));//testing code
	randomaccess_info->ra_PreambleIndex=RandomlySelectRaPreamble();//���ѡ��rapreamble
	SV(RA_info.ra_PreambleIndex)=randomaccess_info->ra_PreambleIndex;//����rapid,�����ȶ�RAR //HQ 20140506 
	
	/*for test*/
	//randomaccess_info->ra_PreambleIndex=2;//for test 20141103
	//SV(RA_info.ra_PreambleIndex)=randomaccess_info->ra_PreambleIndex;//for test20141103
	/*for test*/
	fsm_printf("[UEMAC][contention_ra]MAC ra_PreambleIndex:%d\n",SV(RA_info.ra_PreambleIndex));//test code
	/*randomaccess_info->ra_PRACHMaskIndex=0;
	SV(RA_info.ra_PRACHMaskIndex)=randomaccess_info->ra_PRACHMaskIndex;*/
	SendRaPreamble(randomaccess_info);//���������Ĳ���ָʾ�������
	StartWaitingForRaResponse();//start waiting for the RAR
	FOUT;
}


/*
******************************
->Change Data and time: 
->Function:�Ǿ����� ����RARʧ�ܴ�����
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void NC_RaResponseFailed() 
{
	FIN(NC_RaResponseFailed());
	SV_PTR_GET(mac_sv);
	u32 PreambleTransMax=SV(systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.preambleTransMax);
	print_tran_info("[UEMAC][nc_ra_failed]NCRA -> IDLE");//testing code
	if(SV(WaitforRAresponseTimer.flag)==true)//����Ƕ�ʱ����ʱ����������Ӧ�ı�־ ��Ϊ���δ��ʱ ��ʱ��Ӧ�ûᱻȡ�� ��־������Ϊfalse
	{ 
		SV(WaitforRAresponseTimer.flag)= false;
		SV(WaitforRAresponseTimer.timer_sign)= NULL;
	}
	SV(PREAMBLE_TRANSMISSION_COUNTER)++ ;
	if (SV(PREAMBLE_TRANSMISSION_COUNTER)==PreambleTransMax + 1)
	{
		//modified by HQ    	
		fsm_printf("[UEMAC][nc_ra_failed]MAC:notice RRC has try RA for max times\n");//testing code
		// fsm_do_ioctrl(STRM_TO_RRC, IOCCMD_MACtoRRC_RandomAcc_Fail  , NULL , 0);//Notify RRC the random access failed
		//modified by HQ
		SV(RA_info.ra_PreambleIndex)=0;//HQ 20140506 //���֮ǰ�Ĳ���ֵ
		SV(RA_info.ra_PRACHMaskIndex)=0; //HQ 20140506 //���֮ǰ�Ĳ���ֵ 
	}
	else
	{
		fsm_printf("[UEMAC][nc_ra_failed]MAC:start a new NCRA \n");//testing code 
		fsm_schedule_self(100,Start_NonContentionBase_RandomAcc);//trigger a new random access procedure
	}
	FOUT;
}


/*
******************************
->Change Data and time: 
->Function:������ ����RARʧ�ܴ�����
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void C_RaResponseFailed() 
{
	FIN(C_RaResponseFailed());
	SV_PTR_GET(mac_sv);
	u32 PreambleTransMax=SV(systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.preambleTransMax);
	u16 backoff_time=0,backoff_param=0;//��λΪms ����backoff_index���
	print_tran_info("[UEMAC][c_ra_failed]MAC:CRA -> IDLE RAR receive fail");//testing code
	if(SV(WaitforRAresponseTimer.flag)==true)//����Ƕ�ʱ����ʱ����������Ӧ�ı�־
	{
		SV(WaitforRAresponseTimer.flag)= false;
		SV(WaitforRAresponseTimer.timer_sign)= NULL;
	}
	SV(PREAMBLE_TRANSMISSION_COUNTER)++ ;
	if(SV(PREAMBLE_TRANSMISSION_COUNTER)==PreambleTransMax + 1)
		//modified by HQ
		fsm_printf("[UEMAC][c_ra_failed]MAC:notice RRC has try RA for max times\n");//testing code
		//fsm_do_ioctrl(STRM_TO_RRC, IOCCMD_MACtoRRC_RandomAcc_Fail  , NULL , 0);//Notify RRC the random access failed
	//modified by HQ
	else
	{ 
		backoff_param=BackoffTable[SV(backoff_index)]; //get the backoff parameter from BackoffTable 
		//fsm_printf("[UEMAC][c_ra_failed]MAC:back off parame : %d \n",backoff_param);//testing code
		if(backoff_param != 0)//�������Ϊ��
		{
			fsm_get_random_bytes(&backoff_time , sizeof(backoff_time)); //get a random number with 16bit.
			backoff_time=backoff_time % backoff_param;    //��0-backoff_param֮�����ѡ��һ������ֵ
			fsm_printf("[UEMAC][c_ra_failed]MAC:with %d byte,get a random backoff:%d \n",sizeof(backoff_time),backoff_time);//testing code
		}
		fsm_schedule_self(backoff_time*100,Start_ContentionBase_RandomAcc);//trigger a new random access procedure as backoff_param indicates
		//������ra-preamble�����ѡ�񣬲ο�Э�飬��������Ӵ���
	}
/*    else 
    {
     backoff_param=BackoffTable[SV(backoff_index)]; //get the backoff parameter from BackoffTable  
     fsm_get_random_bytes(&backoff_time,sizeof(backoff_time)); //get a random number with 16bit.
     fsm_printf("with %d byte,get a random backoff:%d \n",sizeof(backoff_time),backoff_time);//testing code
     backoff_time=backoff_time % backoff_param;    //��0-backoff_param֮�����ѡ��һ������ֵ
     if(backoff_time==0)
       fsm_schedule_self(100,Start_ContentionBase_RandomAcc);//����ʱ�����Ϊ0//��ʾ���˱�
     else 
       fsm_schedule_self(backoff_time*100,Start_ContentionBase_RandomAcc);//trigger a new random access procedure as backoff_param indicates
    }
*/
FOUT;
}

/*����msg3,����ʱ��Ҫ����SDU���ھ��������ʵ���������������� ���ͺ���Ҫ����CR��ʱ�� */ 
/*Ŀǰ���ù��ܺ������ǲ��ñ����ķ�ʽ������LCID���и��ã�����CCCH */
/*����һ�ֽ������������һ������״̬SENDMSG3 �ϲ����ݰ����� �����ת�Ƶ�CRA״̬ */

//����һ
/*
static void send_msg3() //defined by HQ 20140430 
{
  FIN(send_msg3());   
  SV_PTR_GET(mac_sv);
   if(true==SV(UL_resource_info.resource_flag))//����Ƿ�����Դ����
   {
      DoResourceAllocation(SV(UL_resource_info.m_tbSize)); //������Դ���� Ȼ��ظ�RLC_Data_REQ
       //����Msg3,��CCCH������RLC��SDU  //��Ҫ��RLC�·�SDU��ſ��Խ��иò���
      //��װMAC PDU   
      //�������������ʱ��
      SV(CRTimer.time_value)=SV(systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.mac_ContentionResolutionTimer); //��λms
      SV(CRTimer.timer_sign)=fsm_schedule_self(SV(CRTimer.time_value)*100+100, CRTimer_Expire);
      //���ﶨʱʱ������1ms,����RLC�·�SDU�Ľ���ʱ�䣬�൱�ڶ�ʱ������ǰһ�������ˣ������һЩ������ 
      SV(CRTimer.flag)=true;
   }
   else 
   	  print_tran_info("no UL_Resource,error!");
FOUT;
}
*/

//����2
/*
******************************
->Change Data and time: 
->Function:�ɹ�����RAR�󣬷���MSG3֮ǰ�Ĵ�����
->Change:
->Details:����MSG3�����ϲ�RLC������(��һ���������) ��������MAC��msg3����
->input:
->output:
->Special:
*******************************
*/
static void waitsending_msg3() //defined by HQ 20140430 
{
	RNTI_indication *data_ptr;
	FIN(waitsending_msg3());   
	SV_PTR_GET(mac_sv);
	RARTA_handleB();//��������ʱ������RAR�ɹ�������TA����Ĵ��� 
	//print_tran_info("[UEMAC][waitsend_msg3]CRA->SENDMSG3");
	//HQ modified start 20140709 ����T_RNTI�Ĵ���
	/* if(SV(C_RNTI) == 0)//û��C_RNTI
	{
		data_ptr = (RNTI_indication *)fsm_mem_alloc(sizeof(RNTI_indication));
		data_ptr->rnti_type = 2; 
		data_ptr->rnti_value = SV(T_C_RNTI);
		fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACtoPHY_RNTI_Indicate, (void *)data_ptr, sizeof(RNTI_indication));
		//��T_C_RNTI��֪�����
	}*/
	//HQ HQ modified end 20140709 
	//LHL modified 20140717 msg3����T_C_RNTI���ŵ�
	if( SV(T_C_RNTI)!=0)//�������
	{
		data_ptr = (RNTI_indication *)fsm_mem_alloc(sizeof(RNTI_indication));
		data_ptr->rnti_type = 2; 
		data_ptr->rnti_value = SV(T_C_RNTI);
		fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACtoPHY_RNTI_Indicate, (void *)data_ptr, sizeof(RNTI_indication));
		fsm_mem_free(data_ptr);
	}
	//HQ HQ modified end 20140717
	fsm_printf("[UEMAC][waitsend_msg3]MAC SV(PREAMBLE_TRANSMISSION_COUNTER):%d\n",SV(PREAMBLE_TRANSMISSION_COUNTER));
	/*if(SV(PREAMBLE_TRANSMISSION_COUNTER) == 1 )//��һ�ν���
	{
		if(SV(DATA_WAIT_ALLOCATION)==true && SV(UL_resource_info.resource_flag)==true)//����Ƿ�����Դ����
		{
			//DoresourceAllocation()�����Ĳ����ǣ���byteΪ��λ��UL_resource_info.m_tbsize��bitΪ��λ
		if(SV(C_RNTI)!= 0 ) //Ԥ����C-RNTI���Ƶ�Ԫ����Դ )
		{
			SV(Tbsize_Complex)=SV(UL_resource_info.m_tbsize)/8;//20140718LHL ��λΪbyte,����ģ��ʹ��
	    		DoResourceAllocation(GetTBsize_Allocation(SV(UL_resource_info.m_tbsize)-24));//20140531 ,20140718LHL:32�ǿ���MAC���Ƶ�Ԫ����
		}
		else//RRCδ���ӣ���Ԥ��C_RNTI���Ƶ�Ԫ2010721 LHL
		{
			SV(Tbsize_Complex)=SV(UL_resource_info.m_tbsize)/8;//20140718LHL ��λΪbyte,����ģ��ʹ��
	    		DoResourceAllocation(GetTBsize_Allocation(SV(UL_resource_info.m_tbsize)));//20140531 ,20140718LHL:32�ǿ���MAC���Ƶ�Ԫ����
		}
		fsm_printf("MAC SEND MSG3:DoResourceAllocation \n");
		}
		else 
	   		print_tran_info("MAC SEND MSG3::no UL_Resource,error!");//testing code
	}
	else if(SV(PREAMBLE_TRANSMISSION_COUNTER) > 1 )
	{  	
		SV(Tbsize_Complex)=SV(UL_resource_info.m_tbsize)/8;//20140721LHL ��λΪbyte,����ģ��ʹ��    	
  		fsm_printf("MAC SEND MSG3:this isn't the first time to do contention based random access ,needn't to  DoResourceAllocation \n");
	}*/ //modified by lhl 20140725

	if(SV(ra_allocation_res)==0)
	{
		if(SV(DATA_WAIT_ALLOCATION)==true && SV(UL_resource_info.resource_flag)==true)//����Ƿ�����Դ����
		{
			//DoresourceAllocation()�����Ĳ����ǣ���byteΪ��λ��UL_resource_info.m_tbsize��bitΪ��λ
			SV(ra_allocation_res)=1;
			if(SV(C_RNTI)!= 0 ) //Ԥ����C-RNTI���Ƶ�Ԫ����Դ )
			{
				SV(Tbsize_Complex)=SV(UL_resource_info.m_tbsize)/8;//20140718LHL ��λΪbyte,����ģ��ʹ��
				DoResourceAllocation(GetTBsize_Allocation(SV(UL_resource_info.m_tbsize)-24));//20140531 ,20140718LHL:32�ǿ���MAC���Ƶ�Ԫ����
				SV(UL_resource_info.resource_flag)=false;
			}
			else//RRCδ���ӣ���Ԥ��C_RNTI���Ƶ�Ԫ2010721 LHL
			{
				SV(Tbsize_Complex)=SV(UL_resource_info.m_tbsize)/8;//20140718LHL ��λΪbyte,����ģ��ʹ��
				DoResourceAllocation(GetTBsize_Allocation(SV(UL_resource_info.m_tbsize)));//20140531 ,20140718LHL:32�ǿ���MAC���Ƶ�Ԫ����
				SV(UL_resource_info.resource_flag)=false;
			}
			//fsm_printf("[UEMAC][waitsend_msg3]DoResourceAllocation \n");
		}
		else 
			print_tran_info("[UEMAC][waitsend_msg3]no UL_Resource,error!");//testing code
	}
	else
	{
		SV(ra_allocation_res)=2;
		SV(Tbsize_Complex)=SV(UL_resource_info.m_tbsize)/8;//20140721LHL ��λΪbyte,����ģ��ʹ�� 
		fsm_schedule_self(0, RA_Send_Msg3);//LHL 20140726 ,�ǵ�һ�η�MSG3����MAC����
		fsm_printf("[UEMAC][waitsend_msg3]this isn't the first time to do contention based random access ,needn't to  DoResourceAllocation \n");
	}
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:����MSG3
->Change:
->Details:ע��MACҪ�������͵�MSG3�Է��ش�MSG3
->input:
->output:
->Special:
*******************************
*/
static void send_msg3() //defined by HQ 20140430  
{
	//���msg3�Ĳ�ͬ���ݣ���������ж��ķ���������ͬ
	//Ŀǰʵ����: msg3��������CCCH�ϵ�SDU---->������Ҳʵ����
	int	skb_len=0,len=0; 
	FSM_PKT *skb;
	FIN(send_msg3());

	SV_PTR_GET(mac_sv);
	//����Msg3,��CCCH������RLC��SDU  //��Ҫ��RLC�·�SDU��ſ��Խ��иò���
	//��װMAC PDU 
	//fsm_printf("[UEMAC][send_msg3]send msg3,SENDMSG3->CRA \n");
	skb = fsm_pkt_get();
	// fsm_pkt_destroy(fsm_pkt_get());
	// fsm_printf("in fact it was destroyed ");
	fsm_printf("[UE MAC]RA ALLOCATION RESULT:%d\n",SV(ra_allocation_res));
	if(SV(ra_allocation_res)==1)//modified by lhl 20140725
	{
		//����msg3��sk_buf
		//20140709 adition start by HQ Ϊ��������sk_buff�Ľṹ������msg3  ���ڵڶ����Լ��Ժ�ľ�����������MSG3
		/*SV(msg3_buf_ptr)= fsm_pkt_create(128);
		skb_len = skb->data - skb->head ;
		fsm_skb_reserve(SV(msg3_buf_ptr),skb_len);
		fsm_mem_cpy(SV(msg3_buf_ptr)->head,skb->head,skb_len);
		skb_len = skb->tail - skb->data;
		fsm_skb_put(SV(msg3_buf_ptr),skb_len);
		fsm_mem_cpy(SV(msg3_buf_ptr)->data,skb->data,skb_len);*/
		if(SV(msg3_buf_ptr)!=NULL)
			fsm_pkt_destroy(SV(msg3_buf_ptr));
		SV(msg3_buf_ptr)=skb;//3
		skb=fsm_pkt_duplicate(SV(msg3_buf_ptr));//20140729 lhl
	
		//20140709 adition end  by HQ 	

		len=sizeof(RLCtoMAC_IciMsg);
		//����lteMacCcchSend(skb,len)���SDU�ǲ���ccch�ϵ����ݣ�����᷵��0,������SDU�������򷵻�1	
		if(lteMacCcchSend(skb,len) && SV(C_RNTI)!= 0 ) //�������CCCH�ϵ����� ����C_RNTI_MAC���Ƶ�Ԫ
		{	
			//fsm_printf("[LHL]C_RNTI CONTROL ELEMENT!\n");
			SV(MAC_CE_Tags)[CRNTI_CE].addinPDU_flag=true;
			//SV(MAC_CE_Tags)[CRNTI_CE].LCID=CCCH_LCID;
			SV(MAC_CE_Tags)[CRNTI_CE].LCID=C_RNTI_LCID;
			SV(MAC_CE_Tags)[CRNTI_CE].MAC_CE_ptr=(void *)&SV(C_RNTI);
			
			
			//fsm_printf("[MAC FSM]RNTI IN SV:%d\n",SV(C_RNTI));
			
			
		}
		SV(sendmsg3)=1;
		complexUeMacPdu(skb);
		
	
		if(SV(Tbsize_Complex)!=0)
			SV(Tbsize_Complex)=0;//����֮������TBSIZE
		fsm_printf("[UEMAC][send_msg3]:this is the first time to do CRA \n");//testing code 
	}
	else if(SV(msg3_buf_ptr) != NULL && SV(ra_allocation_res)==2)  
	{
		len=sizeof(RLCtoMAC_IciMsg);
		skb=fsm_pkt_duplicate(SV(msg3_buf_ptr));//20140729 lhl
		//����lteMacCcchSend(skb,len)���SDU�ǲ���ccch�ϵ����ݣ�����᷵��0,������SDU�������򷵻�1	
		if(lteMacCcchSend(skb,len) && SV(C_RNTI)!= 0 ) //�������CCCH�ϵ����� ����C_RNTI_MAC���Ƶ�Ԫ
		{
			//fsm_printf("[LHL]C_RNTI CONTROL ELEMENT!\n",SV(ra_allocation_res));
			SV(MAC_CE_Tags)[CRNTI_CE].addinPDU_flag=true;
			//SV(MAC_CE_Tags)[CRNTI_CE].LCID=CCCH_LCID;
			SV(MAC_CE_Tags)[CRNTI_CE].LCID=C_RNTI_LCID;
			SV(MAC_CE_Tags)[CRNTI_CE].MAC_CE_ptr=(void *)&SV(C_RNTI);
		}
		SV(sendmsg3)=1;	
		complexUeMacPdu(skb); 	
		if(SV(Tbsize_Complex)!=0)//?????????????????????????????������
			SV(Tbsize_Complex)=0;//����֮������TBSIZE ���ش���ô�� û����Դ???
		fsm_printf("[UEMAC][send_msg3]:this isn't the first time to CRA \n");//testing code 
	}
	//testing code �յ�����ֱ��ת����SRIO
	//  fsm_pkt_send(fsm_pkt_get(), STRM_TO_SRIO);
	//�������������ʱ��
	SV(CRTimer.time_value)=SV(systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.mac_ContentionResolutionTimer); //��λms
	//fsm_printf("[UEMAC][send_msg3]CRtimer value:%d\n",SV(CRTimer.time_value));
	SV(CRTimer.timer_sign)=fsm_schedule_self(SV(CRTimer.time_value)*100, CRTimer_Expire);//����
	SV(CRTimer.flag)=true;
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:���HARQ����
->Change:
->Details:��ʱû��ʵ��
->input:
->output:
->Special:
*******************************
*/
static void cleanharqBuff()
{
	FIN(cleanharqBuff());
	//print_tran_info("[UEMAC][cleanharqbuf]clean HARQ buffer");//testing code
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:�������ʧ�ܵĴ�����
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void ContentionFailed() 
{
	FIN(ContentionFailed());
	SV_PTR_GET(mac_sv);
	int result=1;//TEST
	u32 PreambleTransMax=SV(systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.preambleTransMax);
	u32 backoff_time=0,backoff_param=0;//��λΪms ����backoff_index���

	fsm_printf("[UEMAC][con_failed]CRA -> IDLE contention fail ");//testing code 
	if(SV(CRTimer.flag)==true) //LHL 20140729 CR��ʱ����ʱ������Ӧ�����ñ�־ 
	{
		fsm_printf("[UEMAC][con_failed]because CRtimer expire \n");
		SV(CRTimer.timer_sign)= NULL;
		SV(CRTimer.flag)= false;
	}
	//if(SV(TATimer.time_value)== SV(TA_fromRAR) && SV(TATimer.flag)==true) //����ʧ�ܣ���ֹ֮ͣǰ������TATimer MACЭ��5.1.6
	
	if(SV(TATimer.flag)==true) 
	{//HQ 20140428 
		//fsm_printf("[UEMAC][con_failed]CR fail,stop TAtimer\n");//testing code 
		if(SV(TATimer.timer_sign) != NULL)
		{
			result=fsm_schedule_cancel (SV(TATimer.timer_sign));
		}
		//fsm_printf("[UEMAC][contentionfailed]result:%d\n",result);//TEST
		SV(TATimer.timer_sign)= NULL;
		SV(TATimer.flag)=false;
		SV(TATimer.time_value)=0;
	}
	SV(T_C_RNTI)=0;
	cleanharqBuff();
	SV(PREAMBLE_TRANSMISSION_COUNTER)++;
	if (SV(PREAMBLE_TRANSMISSION_COUNTER)==PreambleTransMax + 1)//modified by HQ
	{
		//fsm_printf("[UEMAC][con_failed]:notice RRC has try RA for max times\n");//testing code 
		SV(sendmsg3)=0;
		SV(ratype.ra_type)=0;
		SV(pdcch_rnti)=0;
		SV(ra_allocation_res)=0;
		fsm_do_ioctrl(STRM_TO_RRC, IOCCMD_MACtoRRC_RandomAcc_Fail  , NULL , 0);//Notify RRC the random access failed//add on 20141208
	}
	
	//modified by HQ
	else
	{
		SV(ra_allocation_res)=1;
		backoff_param=BackoffTable[SV(backoff_index)]; //get the backoff parameter from BackoffTable  
		//fsm_printf("[UEMAC][con_failed]:back off parame : %d \n",backoff_param);//testing code
		if(backoff_param != 0)//�������Ϊ��
		{
			fsm_get_random_bytes(&backoff_time , sizeof(backoff_time)); //get a random number with 16bit.
			backoff_time=backoff_time % backoff_param;    //��0-backoff_param֮�����ѡ��һ������ֵ
			//fsm_printf("[UEMAC][con_failed]:with %d byte,get a random backoff:%d \n",sizeof(backoff_time),backoff_time);//testing code
		}
		fsm_schedule_self(backoff_time*100,Start_ContentionBase_RandomAcc);//trigger a new random access procedure as backoff_param indicates
		//������ra-preamble�����ѡ�񣬲ο�Э�飬��������Ӵ���
	}
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:�Ǿ����������ɹ��Ĵ�����
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void ncra_success()
{
	FIN(ncra_success);
	SV_PTR_GET(mac_sv);
	RARTA_handleA();//�Ǿ�������ʱ������RAR�ɹ� ���������ɹ� TA����Ĵ��� 
	SV(RA_info.ra_PreambleIndex) = 0;	//���ra_preamble index ra_prach_mask_index
	SV(RA_info.ra_PRACHMaskIndex) = 0; 
	SV(PREAMBLE_TRANSMISSION_COUNTER) = 0;//��������������0
	SV(T_C_RNTI) = 0;//����T_C_RNTI 
	//fsm_printf("[UEMAC][nc_success]:\n noncontention based random access success \n");//testing code 
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:�����������ɹ��Ĵ�����
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static void cra_success()
{
	RNTI_indication *data_ptr;
	FIN(cra_success());
	SV_PTR_GET(mac_sv);
	SV(RA_info.ra_PreambleIndex) = 0;	//���ra_preamble index ra_prach_mask_index
	SV(RA_info.ra_PRACHMaskIndex) = 0; 
	SV(PREAMBLE_TRANSMISSION_COUNTER) = 0;//��������������0
	cleanharqBuff();//���HARQ��msg3�Ļ���
	SV(ra_allocation_res)=0;
	if(SV(msg3_buf_ptr) != NULL)
	{
		fsm_pkt_destroy(SV(msg3_buf_ptr));//modified by lhl 20140717
		SV(msg3_buf_ptr) = NULL; //���msg3��sk_buf����
	}
	if(SV(C_RNTI) == 0)
		SV(C_RNTI) = SV(T_C_RNTI); //T_C_RNTI���� 
	SV(T_C_RNTI) = 0;//����T_C_RNTI
	if(SV(C_RNTI) > 0) //��C_rntiָʾ������� 
	{
		data_ptr = (RNTI_indication *)fsm_mem_alloc(sizeof(RNTI_indication));
		data_ptr->rnti_type = 1; 
		data_ptr->rnti_value = SV(C_RNTI);
		fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACtoPHY_RNTI_Indicate, (void *)data_ptr, sizeof(RNTI_indication));//��C_RNTI��֪�����
		fsm_mem_free(data_ptr);//LHL20141018
	}
	if(SV(CRTimer.flag)==true) //ֹͣCR��ʱ��
	{
		SV(CRTimer.timer_sign)= NULL;
		SV(CRTimer.flag)= false;
		SV(CRTimer.time_value)=0;
	}
	SV(sendmsg3)=0;//��MSG3��־��Ϊ0
	SV(ratype.ra_type)=0;//�������������Ϊ0 
	SV(pdcch_rnti)=0;
	fsm_printf("[UEMAC][cra_success]:contention based random access success \n");//testing code 
	printk("[UEMAC][cra_success]:contention based random access success \n");//testing code
	FOUT;
}
/********************************************************************/

/*************************HQ 20140428 **************************/
/*
******************************
->Change Data and time: 20141021
->Function:�Ǿ��������´���RAR��TA
->Change:TA��ʱ�����ڣ�ΪRRC����
->Details:
->input:
->output:
->Special:
*******************************
*/
static void RARTA_handleA()  
{
	FIN(RARTA_handleA());	
	SV_PTR_GET(mac_sv);	
	if(SV(TATimer.flag)==true && SV(TATimer.timer_sign) != NULL)//��ʱ����δ��ʱ ����ȡ��
		fsm_schedule_cancel(SV(TATimer.timer_sign));
	//SV(TATimer.time_value)=SV(TA_fromRAR);//LHL modified 20141021
	
	SV(TATimer.time_value)=SV(TA_Periodic_time);//LHL 20141021
	SV(TATimer.timer_sign)=fsm_schedule_self(SV(TATimer.time_value)*100,TimeAlignmentTimer_Expire);
	fsm_printf("[mac][RARTA_handleA()]ta timer value:%d\n",SV(TATimer.time_value)*100);
	SV(TATimer.flag)=true;
	//fsm_printf("[UEMAC][rarta_handlea]:NCRA handle TA command \n");//testing code 
	FOUT;
}
/*
******************************
->Change Data and time: 2014.10.21
->Function:���������´���RAR��TA
->Change:TA��ʱ�����ڣ���RRC����
->Details:
->input:
->output:
->Special:
*******************************
*/
static void RARTA_handleB()  
{
	FIN(RARTA_handleB());
	/**delete for test**/
	
	SV_PTR_GET(mac_sv);
	if(SV(TATimer.flag)==false)
	{ //TA��ʱ��δ����,��Ӧ�ø�TA
		//SV(TATimer.time_value)=SV(TA_fromRAR);//LHL modified 20141021,TA��ʱ��������RRC���õģ�ֵ���ֲ���
		SV(TA_value)=SV(TA_fromRAR)*16;//
		SV(TATimer.time_value)=SV(TA_Periodic_time);
		SV(TATimer.timer_sign)=fsm_schedule_self(SV(TATimer.time_value)*100,TimeAlignmentTimer_Expire);
		fsm_printf("[mac][RARTA_handleB()]ta timer value:%d\n",SV(TATimer.time_value)*100);
		SV(TATimer.flag)=true;
	}
	//else SV(TA_value)=0;//��ʱ�������У�����Ը�TA ,20141021
	//fsm_printf("[UEMAC][rarta_handle]:CRA handle TA command \n");//testing code 
	
	FOUT;
}


/*************************HQ 20140428 end **************************/

/*********************************************************************/
/* test functions __HuangQiong */

/*
******************************
->Change Data and time: 
->Function:��ӡ��ǰʱ��
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void print_tran_info( const char *str)
{
	FIN( print_tran_info());
	int curtime=0;
	curtime=fsm_get_curtime();
	//fsm_printf("[UEMAC][print_info]%d ",curtime);
	fsm_printf(str);
	fsm_printf("\n");
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:���Ժ���
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void random_test()   //HQ 20140410 ���Դ�0-63�����ѡȡһ����
{
	FIN(random_test());
	u8 randNum[10];
	u32 i = 0;
	fsm_printf( "[UEMAC][ra_test]:Get some real random number.\n");

	for (i=0; i<10; i++)
	{
		fsm_get_random_bytes(&randNum[i], sizeof(char));
		randNum[i]=randNum[i]%64;
		fsm_printf("[UEMAC][ra_test]:We get random number: %d\n", randNum[i]);//testing code
	} 
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:���Ժ���
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void RA_RRCconfig_testingfun() // �����õĺ��������RRC��������Ϣ HQ 20140428 
{
	FIN(RA_RRCconfig_testingfun());
	SV_PTR_GET(mac_sv);
	SV(systemconfigInfo.RACHCommonConfigInfo.preambleInfo.numberOfRA_Preambles)= 64;
	SV(systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.preambleTransMax)=8;
	SV(systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.raResponseWindowSize)=800000;//8;������Ҫ ���ýϳ�ʱ��800s
	SV(systemconfigInfo.RACHCommonConfigInfo.raSupervisionInfo.mac_ContentionResolutionTimer)=800000;// 800s;
	SV(systemconfigInfo.RACHCommonConfigInfo.maxHARQ_Msg3Tx)=5;
	SV(backoff_index)= 2 ; 
	fsm_printf("[UEMAC][ra_rrcconfig]:RACH config have done \n");//testing code
	FOUT;
}

/*
******************************
->Change Data and time: 
->Function:���Ժ���
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void testdoStartContentionBasedRandomAccessProcedure()
{
	FIN(testdoStartContentionBasedRandomAccessProcedure());
	print_tran_info("IDLE -> CRA");
	//fsm_schedule_self(400,RARrev_Success);//testing code //����Ϊ4ms,WAPTimer��δ��ʱ 
	//fsm_schedule_self(100000, RandomAcc_Fail );//testing code
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:���Ժ���
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void testdoStartNonContentionBasedRandomAccessProcedure() //�ǽ��룬Ĭ�ϳɹ� 
{
	FIN(testdoStartNonContentionBasedRandomAccessProcedure());
	print_tran_info("IDLE -> NCRA");
	//fsm_schedule_self(400,RARrev_Success);//testing code //����Ϊ4ms,WAPTimer��δ��ʱ 
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:ֹͣWaitforRAresponseTimer��ʱ��
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void stop_WRAP_timer()
{
	FIN(stop_WRAP_timer());
	SV_PTR_GET(mac_sv);
	if(SV(WaitforRAresponseTimer.flag)==true)
	{
		fsm_schedule_cancel(SV(WaitforRAresponseTimer.timer_sign));
		SV(WaitforRAresponseTimer.flag)=false;
		SV(WaitforRAresponseTimer.timer_sign)=NULL;
	}
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:���Ժ���
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void NCRAtoCON_testingfun() 
{
	FIN(NCRAtoCON_testingfun());
	print_tran_info("NCRA -> CON");
	stop_WRAP_timer(); //�ö�ʱ����ֹͣӦ�����ڳɹ�����RAR��
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:ֹͣCRTimer��ʱ��
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void stop_CR_timer()
{
	FIN(stop_CR_timer());
	SV_PTR_GET(mac_sv);
	if(SV(CRTimer.flag)==true)
	{
		fsm_schedule_cancel(SV(CRTimer.timer_sign));
		SV(CRTimer.flag)=false;
		SV(CRTimer.timer_sign)=NULL;
	}
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:ֹͣTATimer��ʱ��
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void stop_TA_timer()
{
	FIN(stop_TA_timer());
	SV_PTR_GET(mac_sv);
	if(SV(TATimer.flag)==true)
	{
		fsm_schedule_cancel(SV(TATimer.timer_sign));
		SV(TATimer.flag)=false;
		SV(TATimer.timer_sign)=NULL;
	}
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:ֹͣRetxBSRTimer��ʱ��
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void stop_RetxBSR_timer()
{
	FIN(stop_RetxBSR_timer());
	SV_PTR_GET(mac_sv);
	if(SV(RetxBSRTimer.flag)==true)
	{
		fsm_schedule_cancel(SV(RetxBSRTimer.timer_sign));
		SV(RetxBSRTimer.flag)=false;
		SV(RetxBSRTimer.timer_sign)=NULL;
	}
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:ֹͣPeriodicBSRTimer��ʱ��
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void stop_PeriodicBSR_timer()
{
	FIN(stop_PeriodicBSR_timer());
	SV_PTR_GET(mac_sv);
	if(SV(PeriodicBSRTimer.flag)==true)
	{
		fsm_schedule_cancel(SV(PeriodicBSRTimer.timer_sign));
		SV(PeriodicBSRTimer.flag)=false;
		SV(PeriodicBSRTimer.timer_sign)=NULL;
	}
	FOUT;
}


/*
******************************
->Change Data and time: 
->Function:���Ժ���
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void CRAtoCON_testingfun()
{
	FIN(NCRAtoCON_testingfun());
	print_tran_info("CRA -> CON");
	stop_CR_timer(); //�ö�ʱ����ֹͣӦ�����ڽ��վ��������Ԫȷ�Ͼ����ɹ���
	FOUT;
}




//testing code  
//�ʺϳ��� IOCTL_TEST�ļ���siro.c�е����� -crareq�ǲ������ݵģ� -ncrareq����ʹ�� 
//  -sendraorder �����Ƿ���SRIOģ�飬SRIOģ������MAC���� IOCCMD_PDCCHtoMAC_RandomAcc_Req ��Я������ 
//������� doStartNonContentionBasedRandomAccessProcedure()����ʹ��
/*
******************************
->Change Data and time: 
->Function:���Ժ���
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void test1_idle_default_handler()
{
	void *tmpdata_ptr;
	FIN(idle_default_handler());
	SV_PTR_GET(mac_sv);
	print_tran_info("MAC:idle_default_handler");
	if(MAC_CLOSE)
	{
		print_tran_info("MAC FSM is closed "); //testing code
		ue_mac_sv_close();
	}
	if(MAC_PK_FROM_LOWER)
	{	//ͨ��ICI��Ϣ�жϰ����ͣ�Ӧ���ǹ㲥��Ϣ�����÷��ͺ���������RLC
		print_tran_info("MAC:IDLE receive a data packet from PHYadapter"); //testing code
		//decomplexUeDataPdu(fsm_pkt_get());
		fsm_pkt_destroy(fsm_pkt_get());//testing code
	}
	if(MAC_PK_FROM_UPPER )
	{//��IDLE״̬��Ӧ���ǲ�������������,���Դ�ӡһ��������Ϣ
		print_tran_info("MAC:IDLE receive a data packet from RLC, error, and then start CRA");//testing code 
		SV(ratype.ra_type)=2;
		fsm_schedule_self(0, Start_ContentionBase_RandomAcc);
		fsm_pkt_destroy(fsm_pkt_get());//testing code
	}
	if(IOCTRL_ARRIVAL)
	{//����IOCTL����
		print_tran_info("MAC:IDLE default ioctl hander");//testing code
		switch(fsm_ev_ioctrl_cmd())
		{
		//����RLC��������������
		case IOCCMD_RLCtoMAC_datasend_Req :
			tmpdata_ptr = fsm_data_get();
			print_tran_info("MAC:IDLE receive a RLCdatareq");
			//DoRefreshRLCBuffserRequest((RlcBufferRequest *) tmpdata_ptr);//���´������ݻ�����Ϣ
			fsm_data_destroy(tmpdata_ptr);
			fsm_schedule_self(0,Start_ContentionBase_RandomAcc); //����������� ��ʱ�䵥λ��10us ���ʱ�����ö೤����
		break;

		//����PHY��RA��������
		case IOCCMD_PDCCHtoMAC_RandomAcc_Req : 	
				tmpdata_ptr = fsm_data_get();
				print_tran_info("IDLE receive a ncra order ");
				fsm_mem_cpy(&(SV(RA_info)),tmpdata_ptr,sizeof(RACH_ConfigDedicated));
				fsm_printf("RAPID: %d \n",SV(RA_info.ra_PreambleIndex));		
				if(tmpdata_ptr != NULL)
				fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
				//fsm_schedule_self(0, Start_NonContentionBase_RandomAcc );//�����Ǿ����������
		break; 
		//����RRC��RA��������
		case IOCCMD_RRCtoMAC_RandomAcc_Req :
				print_tran_info("MAC:IDLE receive a cra order ");
				fsm_schedule_self(0, Start_ContentionBase_RandomAcc );//���������������		
		break;

		//����ֻ�ǲ����õĴ��룬���Աܹ�do_ioctl�����������������
		//�����������Ĵ���
		/*//����PHY��RA��������
		case IOCCMD_PDCCHtoMAC_RandomAcc_Req: 	
		//��������Ĵ�����һ�� ���Դ˴�û��break	  
		//����RRC��RA��������
		case IOCCMD_RRCtoMAC_RandomAcc_Req :
		    tmpdata_ptr = fsm_data_get();
            print_tran_info("IDLE receive a RA req from other layer ");
            if(tmpdata_ptr > 0)//��ָʾ�˹��ڽ����ǰ����
            {
            	print_tran_info("IDLE receive a ncra order ");
            	fsm_mem_cpy(&(SV(RA_info)),tmpdata_ptr,sizeof(RACH_ConfigDedicated));
            	fsm_printf("the RAPID is %d\n",SV(RA_info.ra_PreambleIndex));
        		//fsm_schedule_self(0, Start_NonContentionBase_RandomAcc );//�����Ǿ���������� //�������������������ע�͵�
				if(tmpdata_ptr != NULL)
				{
				  	fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
					fsm_printf("fsm_ev_data,then free the memory\n");
				}

			}
			else //û��ָʾ���ڽ����ǰ����
			{
				print_tran_info("IDLE receive a cra order ");
				fsm_schedule_self(0, Start_ContentionBase_RandomAcc );//���������������
			}			
		break;

		*/

		//����������״̬�޹ص�����
		default:
			ioctrl_handler();  	
		break;
		}
	}
FOUT;
}

//testing code  �ʺ�IOCTL_TEST�ļ���siro.c�е�����ǲ������ݵ���� 
//������������ testdostart......����ʹ��
/*
******************************
->Change Data and time: 
->Function:���Ժ���
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
void test2_idle_default_handler()
{
	void *tmpdata_ptr;
	FIN(idle_default_handler());

	SV_PTR_GET(mac_sv);
	print_tran_info("idle_default_handler");
	if(MAC_CLOSE)
	{
		print_tran_info("MAC FSM is closed "); //testing code
		ue_mac_sv_close();
	}
	if(MAC_PK_FROM_LOWER)
	{	//ͨ��ICI��Ϣ�жϰ����ͣ�Ӧ���ǹ㲥��Ϣ�����÷��ͺ���������RLC
		print_tran_info("IDLE receive a data packet from PHYadapter"); //testing code
		//decomplexUeDataPdu(fsm_pkt_get());
		fsm_pkt_destroy(fsm_pkt_get());//testing code
	}
	if(MAC_PK_FROM_UPPER )
	{//��IDLE״̬��Ӧ���ǲ�������������,���Դ�ӡһ��������Ϣ
		print_tran_info("IDLE receive a data packet from RLC, error, and then start CRA");//testing code 
		fsm_schedule_self(0, Start_ContentionBase_RandomAcc);
		fsm_pkt_destroy(fsm_pkt_get());//testing code
	}
	if(IOCTRL_ARRIVAL)
	{//����IOCTL����
		print_tran_info("IDLE default ioctl hander");//testing code
		switch(fsm_ev_ioctrl_cmd())
		{
		//����RLC��������������
		case IOCCMD_RLCtoMAC_datasend_Req :
			tmpdata_ptr = fsm_data_get();
			print_tran_info("IDLE receive a RLCdatareq");
			//DoRefreshRLCBuffserRequest((RlcBufferRequest *) tmpdata_ptr);//���´������ݻ�����Ϣ
			fsm_data_destroy(tmpdata_ptr);
			fsm_schedule_self(0,Start_ContentionBase_RandomAcc); //����������� ��ʱ�䵥λ��10us ���ʱ�����ö೤����
		break;
		//�����ǲ��ԵĴ���
		//����PHY��RA��������
		case NCRATEST:
				print_tran_info("IDLE receive a ncra test ");
				//fsm_schedule_self(0, Start_NonContentionBase_RandomAcc );//�������������ԭ���� 
		break;
		case IOCCMD_PDCCHtoMAC_RandomAcc_Req : 	
				print_tran_info("IDLE receive a ncra order ");
				//fsm_schedule_self(0, Start_NonContentionBase_RandomAcc );//�����Ǿ����������
		break; 
		//����RRC��RA��������
		case IOCCMD_RRCtoMAC_RandomAcc_Req :
				print_tran_info("IDLE receive a cra order ");
				fsm_schedule_self(0, Start_ContentionBase_RandomAcc );//���������������
		break;
		//����ֻ�ǲ����õĴ��룬���Աܹ�do_ioctl�����������������
		//����������״̬�޹ص�����
		default:
			ioctrl_handler();
		break;
		}
	}
	FOUT;
}
/*
******************************
->Change Data and time: 
->Function:���Ժ���
->Change:
->Details:
->input:
->output:
->Special:
*******************************
*/
static ioctrl_test()//ͨ���û��ռ�������������״̬�����¼�������״̬��
{
	FIN(ioctrl_test());
	switch(fsm_ev_ioctrl_cmd())
	{
		case TESTCMD_RAR_REVF  :
			fsm_printf("receive RAR failed\n");
			fsm_schedule_self(50, RandomAcc_Fail);
		break;
		case TESTCMD_RAR_REVS :
			fsm_printf("receive RAR successfully\n");
			fsm_schedule_self(50, RARrev_Success);
		break;
		case TESTCMD_CR_F :
			fsm_printf("Contention Resolution Failed\n");
			fsm_schedule_self(50, ContentionResolution_Fail);
		break;
		case TESTCMD_CR_S :
			fsm_printf("Contention Resolution successfully\n");
			fsm_schedule_self(50, Contention_Success );
		break;	
		default:
		break;
	}
	FOUT;
}




