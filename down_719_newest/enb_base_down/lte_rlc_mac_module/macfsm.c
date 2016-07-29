#include <linux/if_ether.h>
#include <linux/list.h>


#include "macfsm.h"
#include "../lte_system.h"


//#include "queue_manager.h"
//#include "mac_schedule.h"

#define ST_INIT 0
#define	ST_IDLE 1
#define ST_RASCHED	2
#define ST_DLSCHED	3
#define ST_ULSCHED	4


static void mac_init_enter(void);
static void mac_sv_init(void);	
static void mac_close(void);
//default function 20141124 LHL
static void defaultconfig();
static void macmain_defaultconfig();
static void sps_defaultconfig();
static void CCCH_defaultconfig();
//default function 20141124 LHL


static void idle_default_handler(void);//IDLE״̬��Ĭ�ϴ�����
static void dl_schedule(void);//�������е���
static void ul_schedule(void);//�������е��� 

static void handle_ra_req(void);//���������������
static void handle_ulsched_req(void);//�������е�������
static void handle_rlcdata_req(void);//����RLC���ݷ�������
static void ioctrl_handler(void);//�������IOCTRL����(��״̬ת���޹ص�����) 

static void update_ta(Ue_ta_info *ta_info);//LHL 20141011
static void update_frame(PHY_TO_MAC_frame *frame_info);//LHL 20141017

// ����״̬���õĺ���
void test_queue_manager(struct list_head *listhead);
void print_tran_info( const char *str);
static MAC_LogicalChannelConfig_IoctrlMsg * rrc_lc_config(unsigned short rnti,int lcid);
static void test_print_pkt_num(void);

struct test_s
{	
	char name[5];
	int num;	
};




void mac_main(void)
{
FSM_ENTER(mac_main());
FSM_BLOCK_SWITCH
	{
	FSM_STATE_FORCED(ST_INIT, "INIT", mac_init_enter(), )		
		{
		FSM_TRANSIT_FORCE(ST_IDLE,print_tran_info("INIT -> IDLE") , "default", "", "INIT -> IDLE");
		}		
			
	FSM_STATE_UNFORCED(ST_IDLE, "IDLE",,)		
		{
		FSM_COND_TEST_IN("IDLE")				
			FSM_TEST_COND(MAC_RESET)				
			FSM_TEST_COND(RA_REQ)
			FSM_TEST_COND(DL_SCHED_REQ)
			FSM_TEST_COND(UL_SCHED)
			
		FSM_COND_TEST_OUT("IDLE")	
		FSM_TRANSIT_SWITCH			
			{	
			FSM_CASE_TRANSIT(0, ST_INIT,    print_tran_info("IDLE -> INIT"), "IDLE -> INIT")				
			FSM_CASE_TRANSIT(1, ST_RASCHED,handle_ra_req(), "IDLE -> RASCHED")
			FSM_CASE_TRANSIT(2, ST_DLSCHED,handle_rlcdata_req(), "IDLE -> DLSCHED")		
			FSM_CASE_TRANSIT(3, ST_ULSCHED,ul_schedule(), "IDLE -> ULSCHED")	
			FSM_CASE_DEFAULT(ST_IDLE,idle_default_handler() , "IDLE->IDLE")	//transit to idle state	by default.
			}
		}
	FSM_STATE_FORCED(ST_RASCHED, "RASCHED",, )
		{
		FSM_TRANSIT_FORCE(ST_IDLE,print_tran_info("RASCHED -> IDLE"), "default", "", "RASCHED -> IDLE");
		}
	FSM_STATE_FORCED(ST_ULSCHED, "ULSCHED", , )
		{
		FSM_TRANSIT_FORCE(ST_IDLE,, "default", "", "ULSCHED -> IDLE");//testing code, "default", "", "ULSCHED -> IDLE");
		}
	FSM_STATE_FORCED(ST_DLSCHED, "DLSCHED", , )
		{
		FSM_TRANSIT_FORCE(ST_IDLE,dl_schedule(), "default", "", "DLSCHED -> IDLE");
		}	
	}
FSM_EXIT(0)
}

static void mac_init_enter(void)
{
	FIN(mac_init_enter()());
	//SV_PTR_GET(mac_sv);
	//print_tran_info("FSM-into-INIT");
	mac_sv_init();
	defaultconfig();//RRC default 20141124LHL 
	//test code as follows: 
	//Init_LogicalChannel_ConfigInfo(rrc_lc_config(61, 1));//testing code  //�����߼��ŵ� 
	Init_LogicalChannel_ConfigInfo(rrc_lc_config(61, 0));//testing code  //�����߼��ŵ� 
	//Init_LogicalChannel_ConfigInfo(rrc_lc_config(62, 1));//testing code  //�����߼��ŵ� 
	Init_LogicalChannel_ConfigInfo(rrc_lc_config(62, 0));//testing code  //�����߼��ŵ� 
	//fsm_printf("MAC logical channel config \n");//testing code  //�����߼��ŵ� 
	
	FOUT;
}
static void macmain_defaultconfig()
{
	FIN(macmain_defaultconfig());
	SV_PTR_GET(mac_sv);
	SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.maxHARQ_Tx) = maxHARQ_Tx_n5;
	//fsm_printf("test maxHARQTX:%d \n ",SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.maxHARQ_Tx));//testing code
	//SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.periodicBSR_Timer)= periodicBSR_Timer_infinity;//�ò���ֵ��ʾ�ö�ʱ��������
	//SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.retxBSR_Timer)= retxBSR_Timer_sf2560 ;
	SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.ttiBundling)= false ;
	SV(systemconfigInfo.MACMainConfigInfo.drx_Config.choice.setup.haveShortDRX)= false ;//means release
	SV(systemconfigInfo.MACMainConfigInfo.type)= 1 ; //means phr-Config release ??  
	FOUT;
}
static void sps_defaultconfig()
{
	FIN(sps_defaultconfig());
	SV_PTR_GET(mac_sv);
	SV(systemconfigInfo.SPSConfigInfo.haveSPS_ConfigDL)=false;
	SV(systemconfigInfo.SPSConfigInfo.haveSPS_ConfigUL)=false; 
	FOUT;
}
static void defaultconfig()
{
	FIN(defaultconfig());
	macmain_defaultconfig();
	sps_defaultconfig();
	CCCH_defaultconfig();//CCCH�ŵ�Ĭ������
	//fsm_schedule_self(MAC_BJ_TIME, LC_BJ_CODE);	//for test
	FOUT;
}

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
	//fsm_printf("[UEMAC][init]CCCH_defaultconfig completed\n");
	FOUT;
}
static void mac_sv_init(void)
{
	int i;
	int index;
	FIN(mac_sv_init());
	SV_PTR_GET(mac_sv);
	SV(UL_resource_flag)=1;

	SV(ULschedQue_p) = (struct list_head *)fsm_mem_alloc(sizeof(struct list_head));//����ͷ�����ڴ�
	SV(RAschedQue_p) = (struct list_head *)fsm_mem_alloc(sizeof(struct list_head));//����ͷ�����ڴ�
	INIT_LIST_HEAD(SV(ULschedQue_p));//��ʼ����ͷ
	INIT_LIST_HEAD(SV(RAschedQue_p));//��ʼ����ͷ
	init_rnti_array_val();//��ʼ��RNTI��Ϣ��
	SV(m_temp_cr)=(temp_contention_resolution*)fsm_mem_alloc(sizeof(temp_contention_resolution));
	SV(phy_to_mac_frame).subframeN=0;
	SV(phy_to_mac_frame).sfn=0;
	SV(UL_sched_flag) = 0;
	SV(cnt_test)=1;
	init_Bitmap();
	for(i=0;i<5;i++){
		fsm_mem_set(&SV(schedule_scheme[i]),0,sizeof(struct result_sched_algorithm));
	}

	/*for(index=0;index<USERNUMMAX;index++)//LHL modified 20141011
	{
		SV(TBsize_ue[index].rnti)=0;
		SV(TBsize_ue[index].tbsize)=0;
	}*///ʹ��schedule_scheme
	//LHL 20141011
	for(i=0;i<USERNUMMAX;i++)
	{
		SV(ue_ta[i].rnti)=0;
		SV(ue_ta[i].ta)=0;
		SV(ue_ta[i].update_flag)=0;
	}//LHL 20141011

	SV(send_rar_flag)=1;//20150104�������Դ��룬�Ժ�Ҫȥ������־�Ƿ�RAR������ͨ���û�
	/*�ռ��IOCTL���ò���RAR�����Դ�����ƵĴ���*/
	
	Init_Enbmac_Scheduler();//��ʼ����������صı��� 
//	test_queue_manager(SV(ULschedQue_p));//���Ժ���
	fsm_schedule_self(1000000,TIME_TODO_ULSCHED);//���е������ڱ�Ӧ����10ms Ϊ�˲��Է�����������Ϊ10s
	//test
	SV(lost_pktnum_uplink)=0;
	SV(total_pktnum_uplink)=0;
	SV(lost_pktnum_downlink)=0;
	SV(total_pktnum_downlink)=0;
	//test end
	
	
FOUT;
}

static void mac_close(void)
{
	FIN(mac_close());
	SV_PTR_GET(mac_sv);
	if(SV(ULschedQue_p) != NULL)
	{
		clean_ULschedQue(SV(ULschedQue_p));
		fsm_mem_free(SV(ULschedQue_p));
	}
    	
	if(SV(RAschedQue_p) != NULL)
	{
		clean_RAschedQue(SV(RAschedQue_p));
		fsm_mem_free(SV(RAschedQue_p));
	}
	 if(SV(m_temp_cr) != NULL)
	    {
	    	fsm_mem_free(SV(m_temp_cr));
		SV(m_temp_cr) = NULL;
	    }
   	Free_Enbmac_Scheduler_Resource();
FOUT;
}



static void idle_default_handler()
{ 
//������״̬ת���޹ص��¼�:�²����ݰ������״̬�޹ص�ioctrl����
int i;
FSM_PKT *skb_lower;
FSM_PKT *skb_upper;
	FIN(idle_default_handler());
	SV_PTR_GET(mac_sv);

	if(MAC_CLOSE)
	{
		mac_close();
    	fsm_printf("MAC FSM closed \n");//testing code		
	}
	//GengCanxi����2014��7��23
	if(TC_RNTI_CHECK)
	{
		delete_overtime_tc_rnti();
		//test 
    	//fsm_printf("delete the overtime TC-RNTI(such as, when UE hasn't receive the msg2) \n");//testing code		
	}
	
    if(MAC_PK_FROM_LOWER)//��������PHY������û��İ���Ϊһ��һ���û��ٸ�MAC
    {//ͨ��ICI��Ϣ�жϰ����ͣ����ĸ��û��ģ��⸴��ͨ����Ӧ��LC����RLC 
        //�ο�����ͼ HQ ע��
    	//fsm_printf("handle the data packet from lower layer\n");//testing code
    	skb_lower=fsm_pkt_get();
    	decomplexEndMacPdu(skb_lower);
    	//fsm_pkt_destroy(skb_lower);
    }
    if(MAC_PK_FROM_UPPER)
    {//ͨ��ICI��Ϣ�жϰ����� ���� ͨ����Ӧ��TC������������� 
        //�ο�����ͼ HQ ע��
        //fsm_printf("handle the data packet from upper layer\n");//testing code
        skb_upper=fsm_pkt_get();//ÿ�δ���һ���û�������
    	complexEnbMacPdu(skb_upper);
    	//fsm_pkt_destroy(skb_upper);
        
    }
    if(IOCTRL_ARRIVAL)
    { /*��״̬�޹ص�ioctrl����*/  
        ioctrl_handler();
    }
FOUT;
}  

static void ioctrl_handler(void)
{ 
	void *tmpdata_ptr;
	int m_rnti;
	FIN(ioctl_handler());
	SV_PTR_GET(mac_sv);
	//print_tran_info("fun ioctrl handler");
	switch(fsm_ev_ioctrl_cmd())
	{
		case IOCCMD_TEST_WITHDATA : //testing code
			//fsm_printf("ioctrl handle\n");
			tmpdata_ptr = fsm_data_get();		
			//fsm_printf("test: the user is %s with RNTI %d \n",((struct test_s*)tmpdata_ptr)->name,((struct test_s*)tmpdata_ptr)->num);
			fsm_data_destroy(tmpdata_ptr);
		break;
		case IOCCMD_PHYtoMAC_SR ://�������е�������
		    handle_ulsched_req();
		break;
		case IOCCMD_RRCtoMAC_LC_config://�߼��ŵ�����
			tmpdata_ptr = fsm_data_get();		
			fsm_printf("MAC receive lc_config order \n");//testing code 
			Init_LogicalChannel_ConfigInfo((MAC_LogicalChannelConfig_IoctrlMsg *)tmpdata_ptr);
			fsm_data_destroy(tmpdata_ptr);
		break;
		case IOCCMD_RRCtoMAC_LC_release :
			tmpdata_ptr = fsm_data_get();		
			fsm_printf("MAC receive lc_release order \n");//testing code 
			Delete_LogicalChannel_ConfigInfo(((struct MAC_Release_LogicalChannel_IoctrlMsg *)tmpdata_ptr)->crnti,
						((struct MAC_Release_LogicalChannel_IoctrlMsg *)tmpdata_ptr)->lcid);
			fsm_data_destroy(tmpdata_ptr);
		break;
		case IOCCMD_RRCtoMAC_UE_release://�ͷŸ�UE������������Ϣ
			tmpdata_ptr = fsm_data_get();
			m_rnti=((struct MAC_Release_Uefsm *)tmpdata_ptr)->crnti;
			recall_rnti(m_rnti);
			fsm_printf("receive the order to release this UE : \n",((struct MAC_Release_Uefsm *)tmpdata_ptr)->crnti);
			fsm_data_destroy(tmpdata_ptr);
		//ɾ����UE��Ӧ�Ĵ������ݻ������
		 Empty_MACBuffer_Rlc( Get_Enbbuffer_From_Rnti(m_rnti));
		//ɾ����UE��Ӧ�������߼��ŵ�������
		Empty_LogicalChannelInfo(Get_LogicalChannelInfo_From_Rnti(m_rnti));
		Empty_LogicalChannelBj(Get_LogicalChannelBj_From_Rnti(m_rnti));
		release_UE_rnti(m_rnti);//�ͷŸ�UE��RNTI 20141120
		break;
		case IOCCMD_PHYtoMAC_TA:
			tmpdata_ptr = fsm_data_get();
			//fsm_printf("[MAC]IOCCME_PHTTOMAC_TA\n");
			update_ta((Ue_ta_info *)tmpdata_ptr);
			fsm_data_destroy(tmpdata_ptr);
		break;
		case IOCCMD_PHYtoMAC_FRAME:
			tmpdata_ptr = fsm_data_get();
			update_frame((PHY_TO_MAC_frame *)tmpdata_ptr);
			fsm_data_destroy(tmpdata_ptr);
		break;
		case _IOCTLtoENBMAC_RAR_Failed: //20150104������ӵĴ��룬����RAR�����Դ�����ƵĴ���
			SV(send_rar_flag)=0;
		break;
		case _IOCTLtoENBMAC_RAR_Send:
			SV(send_rar_flag)=1;
		break;
		case _IOCTLtoENBMAC_PKT_NUM:
			test_print_pkt_num();
		break;
		default:
		break;
	}
	
FOUT;
}
static void test_print_pkt_num()
{
	FIN(test_print_pkt_num());
	SV_PTR_GET(mac_sv);
	printk("[ENB MAC]lost_pktnum_uplink:%d\n",SV(lost_pktnum_uplink));
	printk("[ENB MAC]total_pktnum_uplink:%d\n",SV(total_pktnum_uplink));
	printk("[ENB MAC]lost_pktnum_downlink:%d\n",SV(lost_pktnum_downlink));
	printk("[ENB MAC]total_pktnum_downlink:%d\n",SV(total_pktnum_downlink));
	FOUT;
}
/************************************************************************
*author:LHL
*description:����TA
*version1.0-20141011
************************************************************************/
static void update_ta(Ue_ta_info *ta_info)
{
	int m_rnti;
	int i;
	u32 flag=0; 
	FIN(update_ta());
	SV_PTR_GET(mac_sv);
	m_rnti=ta_info->rnti;
	//fsm_printf("[MAC]TA is %d\n", ta_info->ta);
	for(i=0;i<DL_SCHEDULE_NUM;i++)
	{
		if(SV(ue_ta[i]).rnti== m_rnti)
		{
			flag=1;
			SV(ue_ta[i]).ta=ta_info->ta;
			SV(ue_ta[i]).update_flag=1;
		}
	}
	if(flag==0)
	{
		for(i=0;i<DL_SCHEDULE_NUM;i++)
		{
			if(SV(ue_ta[i]).rnti==0)// has not been used
			{
				SV(ue_ta[i]).rnti= m_rnti;
				SV(ue_ta[i]).ta=ta_info->ta;
				SV(ue_ta[i]).update_flag=1;
				break;
			}
		}
	}
	FOUT;
}
/************************************************************************
*author:LHL
*description:���µ�ǰ֡�ź���֡��
*version1.0-20141017
************************************************************************/
static void update_frame(PHY_TO_MAC_frame *frame_info)
{
	FIN(update_frame());
	SV_PTR_GET(mac_sv);
	SV(phy_to_mac_frame).sfn=frame_info->sfn;
	SV(phy_to_mac_frame).subframeN=frame_info->subframeN;
}
/************************************************************************
*author:HQ
*description:������е��ȹ�������ӦRLC�����ݷ�������������Ӧ��DCI��
*version1.0-201406017
************************************************************************/
static void handle_rlcdata_req()//����RLC���ݷ�������
{
	char *tempdata_ptr;
	RLC_Request *rlc_req;
	RLC_Request *rlc_req_temptr;	
	int rlc_req_lc_totalnum;
	int i,ue_num;
	unsigned short tmp_rnti;

	void *datareport;//20141231 for test
	RLC_Report *testtmp=NULL;//for test 20141231
	int k=0;//for test 20141231
	FIN(handle_rlcdata_req());
	
	SV_PTR_GET(mac_sv);
	tempdata_ptr = (char *)fsm_data_get();//����������Я��������
	fsm_printf("[mac] receive data request!\n");
	rlc_req_lc_totalnum = *((u32 *)tempdata_ptr); //���ϲ㱣֤���ֶδ��� 

	//fsm_printf("[ENB MAC]rlc_req_lc_totalnum:%d\n",rlc_req_lc_totalnum);
		
	if(rlc_req_lc_totalnum == 0)
	{
		//fsm_printf("error :RLC datareq is zero \n");
		FOUT;
	}
	else if(rlc_req_lc_totalnum >= 1)
		{	//�������û�������ֳ���
			rlc_req = (RLC_Request *)(tempdata_ptr+sizeof(u32));
			rlc_req_temptr = rlc_req + 1;
			SV(Rlc_Request_Num[0]) = 1;		
			for(i=1,ue_num=0;i<rlc_req_lc_totalnum;i++) 
			{				
				if(rlc_req_temptr->rnti == (rlc_req_temptr-1)->rnti)
					SV(Rlc_Request_Num[ue_num])++;
				else 
					SV(Rlc_Request_Num[++ue_num])++;	
				rlc_req_temptr++;			
			}
		}
	//���²��Դ���Ϊ�˼�⴦���Ƿ���ȷ ����ɾ�� 
	/*for(i=0; i<USERNUMMAX; i++)//testing code 
	{ 
		if( SV(Rlc_Request_Num[i]) != 0)
		{
			fsm_printf("Rlc_Request_Num[%d]:%d\n",i,SV(Rlc_Request_Num[i]));
	    }

	}*/ //testing code end 
	

	fsm_printf("[MAC] ue_num=%d\n",ue_num);
	for(i = 0; i <= ue_num; i++)//ȡ��ÿ���û������󣬸�����Ӧ�Ļ���
	{
		//fsm_printf("[ENB MAC] rlc_req.rnti=%d",rlc_req->rnti);
	   DoRefreshRLCBuffserRequest (RlcRequest_arraytolist(rlc_req,SV(Rlc_Request_Num[i]),i),SV(Enb_MacBuffer_RLC[i]));
	   rlc_req += SV(Rlc_Request_Num[i]);
	}
	fsm_data_destroy((void *) tempdata_ptr);
	//���²��Դ���Ϊ�˼�⴦���Ƿ���ȷ ����ɾ�� 
	/*for(i=0; i<USERNUMMAX; i++)//testing code 
	{ 
		if( SV(Rlc_Request_Num[i]) != 0)
		{
			fsm_printf("Rlc_Request_Num[%d]:%d\n",i,SV(Rlc_Request_Num[i]));
			struct list_head *pos,*p;
			MacBufferStatus *temp1;
			int j=0;
    		pos=NULL,p=NULL,temp1=NULL;
		    list_for_each_safe(pos,p,SV(Enb_MacBuffer_RLC[i]))//����
		    {
		    	j++;
		        temp1=list_entry(pos,MacBufferStatus,list);
		        printk(KERN_INFO"%d:temp_rnti %d\n",j,temp1->RlcRequestparams->rnti);
		        printk(KERN_INFO"%d:temp_lcid %d\n",j,temp1->lcid);
		    }
	    }

	}*///testing code end 
	//print_tran_info("IDLE -> DLSCHED");//testing code

FOUT;
}

static void dl_schedule()//�������е���
{
	int i,j,k;
	int tb_size, buffer_len;
	struct list_head * enb_logicalChannel_config;
	struct list_head *enb_logicalChannel_bj;
	int *rlc_report_num;
	void *tempdata_ptr;
	RLC_Report *rlc_rep_oneUE_ptr;
	RLC_Report *rlc_report_temptr;
	void *rlc_report_ptr;	
	int rlc_rep_num_total = 0;
	int rnti;
	u32 ue_num;
	struct list_head *pos=NULL,*p=NULL;
	MacBufferStatus *m_temp;
	RLC_Request *m_dci_input;
	u32 flag=0;
	FIN(dl_schedule());

	SV_PTR_GET(mac_sv);
	Reset_Prb_dlBitmap();//����BITMAP
	
	rlc_report_num = (u32 *)fsm_mem_alloc(sizeof(u32));
	for(i=0; i<USERNUMMAX && SV(Rlc_Request_Num[i]); i++)//���ݴ������ݻ�������ȼ���һ���д������ݵ�LC������
		rlc_rep_num_total += SV(Rlc_Request_Num[i]);
	
	ue_num=i;//��ǰTTI��Ҫ���ȵ�UE��LHL 20150110
	
	rlc_report_temptr = (RLC_Report *)fsm_mem_alloc(rlc_rep_num_total * sizeof(RLC_Report));//��ʱ��reportָ��
	rlc_rep_num_total = 0;
	//����������Դ���� //����Ŀǰ������Դ������� ÿ���û�����Դ�̶� �õ�ÿ���û������䵽��tb_size 
	//tb_size = 100;//��λbyte //testing code 
	//Do_sched_algorithm();//�Ժ�Ҫ��̫���ˣ�����Ϳ�����Ҫ���TBSIZE�Ƿ�һ��????????????????
	for(i=0; i<USERNUMMAX && SV(Rlc_Request_Num[i]); i++)
	{
		//ȡ��һ���û��������ݻ�����Ϣ 
		enb_logicalChannel_config = Get_LogicalChannelInfo_From_Enbbuffer(SV(Enb_MacBuffer_RLC[i]));

		//test
		if(enb_logicalChannel_config == NULL)
			continue;

		flag = 1;
		enb_logicalChannel_bj = Get_LogicalChannelBj_From_Enbbuffer(SV(Enb_MacBuffer_RLC[i]));
		buffer_len = SV(Rlc_Request_Num[i]);
		rnti=Getrnti_From_Enbbuffer(SV(Enb_MacBuffer_RLC[i]));//modified by lhl,20140715	
		//fsm_printf("[ENB MAC]rlc request rnti:%d\n",rnti);

		Do_sched_algorithm(rnti,ue_num,i);//test Geng20150105
		
		tb_size=Do_cal_datasize(i);//GCX20150110
		
		//tb_size=Do_cal_datasize(rnti);//modified by lhl,20140715,tb_size��λbyte 
		/******�ָ���**********/
		//tb_size=1530;//for test 20150105
		/******�ָ���**********/
		//fsm_printf("test code tb_seize:%d\n",tb_size);//test code
		list_for_each_safe(pos,p,SV(Enb_MacBuffer_RLC[i]))
		 {
		 	m_temp=list_entry(pos,MacBufferStatus,list);
			m_dci_input=m_temp->RlcRequestparams;
			//fsm_printf("test code order:%d\n",m_dci_input->rnti);
			break;
		 }

		Order_Dl_Sched(m_dci_input,ue_num,i);	//for test!
		
		//Ϊ���û��ĸ����߼��ŵ�������Դ //������Ӧ�ĸ���RLC�ķ�������
		//fsm_printf("tb_size is %d,buffer_len is %d\n",tb_size,buffer_len);
		if (SV(Enb_MacBuffer_RLC[i]) == NULL)
			fsm_printf("SV(Enb_MacBuffer_RLC[i]) == NULL\n");
		if (enb_logicalChannel_config == NULL)
			fsm_printf("enb_logicalChannel_config == NULL\n");
		if (enb_logicalChannel_bj == NULL)
			fsm_printf("enb_logicalChannel_bj == NULL\n");
				
		rlc_rep_oneUE_ptr = DoResourceAllocation(tb_size,SV(Enb_MacBuffer_RLC[i]),enb_logicalChannel_config,
													enb_logicalChannel_bj,buffer_len,rlc_report_num);
		
		//fsm_printf("ENB MAC has already alloced resources\n");
	
		//�����û��ĸ����߼��ŵ���Դ����Ľ�����Ƶ��ܵı����� 
		//for(k=0;k<rlc_report_num;k++)
			//fsm_printf("mac_rlc_report:txQueueHeader:%d,mac_rlc_report->txQueueSize:%d\n",rlc_rep_oneUE_ptr[k].txQueueHeader,rlc_rep_oneUE_ptr[k].txQueueSize);
		fsm_mem_cpy((void *)(rlc_report_temptr+rlc_rep_num_total), 
						rlc_rep_oneUE_ptr,(*rlc_report_num)*sizeof(RLC_Report));
		rlc_rep_num_total += *rlc_report_num; //��¼�������LC�ĸ���
		//���ɸ��û���Ӧ��������Դ�����DCI ���͸����������		
		 
		//test code
		//fsm_printf("test code order:%d\n",m_dci_input->rnti);
		//Order_Dl_Sched(m_dci_input);//���������������??????????????	//move up
		
		fsm_mem_free((void *)rlc_rep_oneUE_ptr);
		rlc_rep_oneUE_ptr=NULL;
		
	}
    //�������û���RLC���������������������RLC�� 
	if(flag != 0)
	{
		rlc_report_ptr = fsm_mem_alloc(rlc_rep_num_total * sizeof(RLC_Report) + sizeof(u32));
		fsm_mem_cpy(rlc_report_ptr, &rlc_rep_num_total, sizeof(u32));
		fsm_mem_cpy(rlc_report_ptr+sizeof(u32), rlc_report_temptr,rlc_rep_num_total * sizeof(RLC_Report));

		//fsm_printf("[LHL]REQUEST NUMBER:%d\n",rlc_rep_num_total);
		fsm_do_ioctrl(STRM_TO_RLC,IOCCMD_MACtoRLC_datasend_Allow, rlc_report_ptr, rlc_rep_num_total * sizeof(RLC_Report) + sizeof(u32));//for test
		fsm_mem_free((void *)rlc_report_ptr);
	}
					
	fsm_mem_free((void *)rlc_report_num);//�ͷ�ָ�� 
	fsm_mem_free((void *)rlc_report_temptr);//�ͷ�ָ�� 
	Empty_Rlcrequestnum();//���Rlc_Request_Num[]����
	//print_tran_info("DLSCHED -> IDLE");//testing code
	
FOUT;
}




/************************************************************************
*author:HQ
*description:������е��ȹ������ȵ���RA�����ٵ�����ͨ��������Դ������С�
*version1.0-20140601 �ڵ���ǰ�������Ƿ�Ϊ�ա�
*version1.1-20140617 �޸� �ڵ���ǰ�����Ӧ�Ķ��б�־,�ж��Ƿ���Ҫ���е���
*version1.2-20141011 LHL ��RAschedQue_p��������ͬRA_RNTI���û����num+S_RAinfo�Ľṹ����Ϊ��������complexRarPdu������
************************************************************************/
static void ul_schedule()
{ 

	struct S_RAinfo ra_UEinfo;
	struct S_RAinfo ra_UEinfo_temp;
	struct S_UEinfo ul_UEinfo;
	DATA_RAR_PDU * rar_info_ptr;//���Ⱥ����ɵ�RAR��Ϣ
	SV_PTR_GET(mac_sv);
	int resleft;//ʣ����Դ
	void *ue_ra_req;
	int *temp;
	int ue_index;
	FIN(ul_schedule());
	//print_tran_info("IDLE -> ULSCHED");

	//������Դ�� 
	SV(UL_resource_flag) = 1;//������ԴΪ����״̬
	if(SV(RA_sched_flag)) //�ȼ��RA���У���ΪRA������Դ���� 
	{
		//fsm_printf("[ENB MAC] SV(RA_sched_flag))\n");
		//Ϊ����RA�����е��û�������Դ ֱ������Ϊ�ջ���������Դ������
		while(SV(UL_resource_flag) > 0  && !(list_empty_careful(SV(RAschedQue_p))) )
		{//��Դ���� �� RA���в�Ϊ��
		//�����ǽ���ͬRA_RNTI���û���������ȡ�����γ�num+struct S_RAinfo��ʽ������complexRarPdu()������
			ra_UEinfo = take_first_RAschedQue(SV(RAschedQue_p));//�Ӷ���ͷ��ȡ��һ���û�
			ue_ra_req=fsm_mem_alloc(sizeof(S_RAinfo)*(ra_UEinfo.total_num)+sizeof(int));//LHL midified 20141011
			temp=(int *)ue_ra_req;
			*temp=ra_UEinfo.total_num;
			fsm_mem_cpy((void *)((int *)ue_ra_req+1),&ra_UEinfo, sizeof(S_RAinfo));
			for(ue_index=1;ue_index<ra_UEinfo.total_num;ue_index++)
			{
				ra_UEinfo_temp=take_first_RAschedQue(SV(RAschedQue_p));//ȡ�������������
				if(ra_UEinfo_temp.total_num == ra_UEinfo.total_num && ra_UEinfo_temp.index == ue_index)//�������
				{
					fsm_mem_cpy(((S_RAinfo *)((int *)ue_ra_req+1))+ue_index,&ra_UEinfo_temp, sizeof(S_RAinfo));
				}
			}//LHL midified 20141011
			//��Ӧ��������
			//����RAR PDU
			
			//����������Դ����
			//��������DCI
			//int Do_RAR_DCI1C(struct S_RAinfo *ra_UEinfo):::::20141024GCX
			//���ú�����������RAR	
			/*************�ָ���*******************************/
			if(SV(send_rar_flag)!=0)//20150104�������Դ�����ƣ�����RAR���Ժ���Ҫif�ж�
			{
				complexRarPdu(ue_ra_req);
				//��SK_BUF�ķ�ʽ�������������
				//������Ӧ��DCI
				resleft=Do_RAR_DCI0( &ra_UEinfo);//������������modified by lhl20140715
				
				if(resleft==0)//û����Դ
					SV(UL_resource_flag)=0;//������Դ��־
				fsm_mem_free(ue_ra_req);
			}
			/**********�ָ���******************************************/
			//��ʱע�͵���ʹ�������if ���Ժ�Ҫʹ������� ����Ҫif�жϣ�ifֻ��Ϊ�˲��Դ������
			/*8
			complexRarPdu(ue_ra_req);
			//��SK_BUF�ķ�ʽ�������������
			//������Ӧ��DCI
			resleft=Do_RAR_DCI0( &ra_UEinfo);//������������modified by lhl20140715
			
			if(resleft==0)//û����Դ
				SV(UL_resource_flag)=0;//������Դ��־
			fsm_mem_free(ue_ra_req);
			*/
			
			//��IOCTRL�ķ�ʽ���͸����������,Do_RAR_DCI�����ѷ���	
		}
		SV(RA_sched_flag)= !(list_empty_careful(SV(RAschedQue_p)));//���¶��б�־
	}
	
	if(!(list_empty_careful(SV(ULschedQue_p))))
		SV(UL_sched_flag)=1;	
	//fsm_printf("[ENB MAC] SV(UL_sched_flag):%d\n",SV(UL_sched_flag));
	if(SV(UL_sched_flag))
	{//�ٽ������е��� �Ӷ�����ȡ��һ���û� ֱ������Ϊ�ջ���������Դ��������
		//fsm_printf("[ENB MAC] SV(ULschedflag)\n");
		while(SV(UL_resource_flag) > 0  && !(list_empty_careful(SV(ULschedQue_p))) )	
		{
			ul_UEinfo = take_first_ULschedQue(SV(ULschedQue_p));//�Ӷ���ͷ��ȡ��һ���û�
			//������Դ����
			fsm_printf("###In function ul_schedule() the &ul_UEinfo's RNTI:%d",ul_UEinfo.rnti);
	
			resleft=Order_Ul_Sched(&ul_UEinfo);//����Ulgrant ,��IOCTL�������������
			if(resleft==0)
				SV(UL_resource_flag)=0;//û����Դ
			//������Ӧ��DCI
			//��IOCTRL�ķ�ʽ���͸����������	
			//Do_Ul_SchedInd(&ul_UEinfo);
		}
		SV(UL_sched_flag) = !(list_empty_careful(SV(ULschedQue_p)));//���¶��б�־

	}
	//���RA���� ��ΪUE�ȴ�RAR��ʱ���ܵ����ƣ�δ����Ӧ��RA�������ֻ����10ms,��һ�����е�������
    clean_RAschedQue(SV(RAschedQue_p));
	SV(RA_sched_flag) = 0;//����RA���б�־Ϊ"����Ҫ����"

	fsm_schedule_self(1000000,TIME_TODO_ULSCHED);//������ʱ��  //���е������ڱ�Ӧ����10ms Ϊ�˲��Է�����������Ϊ10s
FOUT;
}

/************************************************************************
*author:HQ
*description:����RA����Ϊ���������û�������Դ����֯����RAR��
*version1.0-20140601 
*version1.1-  ���޸�Ϊ�����ж�ʣ��������Դ���ʱ���Ƚ�ʣ����Դ�Ƿ�
				С��RA��������Ҫ����Դ��С������ӦRA-req����������ӦRA-req
************************************************************************/
static void handle_ra_req()//���������������
{
	void *tmpdata_ptr;
	//DATA_RAR_PDU *data_rar;//modified lhl 20140909
	int resleft;//��¼ʣ����Դ��modified by lhl 20140715
	int usernum;//��¼�û�����
	int i=0;
	FIN(handle_ra_req());	
	SV_PTR_GET(mac_sv);
	tmpdata_ptr = fsm_data_get();//��ø��û�����Ӧ��Ϣ
	//print_tran_info("IDLE -> RASCHED");
	//fsm_printf("receive RA from PHY  ");//testing code
	if(SV(UL_resource_flag) == 0) //��׼ȷ��ʵ�֣���Ҫ����ȷ�ıȽϣ�ʣ����Դ�Ƿ�С��RA��������Ҫ����Դ
	{	
		//������ԴĿǰû�пɱ��������Դ
		//�����û����뵽RA���ȶ�����,�ȴ�����Դʱ�ٱ�����
		usernum=(int *)tmpdata_ptr;
		for(i=i;i<usernum;i++)
		{			
			insert_RAschedQue(SV(RAschedQue_p), (struct S_RAinfo *)(((int *)tmpdata_ptr+1)+i));
		}
		SV(RA_sched_flag) = 1;//����RA���б�־Ϊ"��Ҫ����"
		
		//fsm_printf("UE RA-RNTI:%d ,RAPID:%d \n",((struct S_RAinfo *)((int *)tmpdata_ptr+1))->ra_rnti,((struct S_RAinfo *)((int *)tmpdata_ptr+1))->rapid);//testing code
	}
	if(SV(UL_resource_flag) > 0) 
	{	
		//TEST!//
		/*S_RAinfo *Msg1_get=(S_RAinfo*)fsm_mem_alloc(sizeof(S_RAinfo));
		fsm_mem_cpy(Msg1_get,(S_RAinfo *)(tmpdata_ptr+sizeof(int)),sizeof(S_RAinfo));
		fsm_printf("[srio][test_send_msg1][--]Message1 index1 = %u,%u,%u,%u,%u\n",Msg1_get->index,Msg1_get->ra_rnti,Msg1_get->total_num,Msg1_get->cqi,Msg1_get->rapid);
		fsm_mem_cpy(Msg1_get,(S_RAinfo *)(tmpdata_ptr+sizeof(int)+sizeof(S_RAinfo)),sizeof(S_RAinfo));
		fsm_printf("[srio][test_send_msg1][--]Message1 index2 = %u.\n",Msg1_get->index);
		fsm_mem_cpy(Msg1_get,(S_RAinfo *)(tmpdata_ptr+sizeof(int)+2*sizeof(S_RAinfo)),sizeof(S_RAinfo));
		fsm_printf("[srio][test_send_msg1][--]Message1 index3 = %u.\n",Msg1_get->index);*/
		//END!//

		//������Դ���Ա����䣬����Ӧ��������
		//fsm_printf("response to the RA_REQ from UE(RA-RNTI) :%d,RAPID:%d \n",((struct S_RAinfo *)((u32 *)tmpdata_ptr+1))->ra_rnti,((struct S_RAinfo *)((u32 *)tmpdata_ptr+1))->rapid);
		//testing code
		//����RAR PDU
		//data_rar=(DATA_RAR_PDU *)fsm_mem_alloc(sizeof(DATA_RAR_PDU));//modified lhl 20140909
		//data_rar= Do_Data_of_MacRarPdu_ulgrant(data_rar, (struct S_RAinfo *)tmpdata_ptr);//������������modified by lhl20140715
		//���ú�����������RAR	
		//������Դ���ȣ�RARҲ�����а�
		////int Do_RAR_DCI1C(struct S_RAinfo *ra_UEinfo):::::20141024GCX
		
		/***********�ָ���****�������Դ���*************/
		if(SV(send_rar_flag)==0)//20150104�û��ռ����ò���RAR
		{
			fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
			FOUT;
		}
		/***********�ָ���******end***********/
		complexRarPdu((void *)tmpdata_ptr);//modified lhl 20140909 ,���ݵ�Ӧ����ָ��?????????????
		//��SK_BUF�ķ�ʽ�������������
		//������Ӧ��DCI,Ӧ��������������DCI?????????????????????????

		//resleft=Do_RAR_DCI1C( (struct S_RAinfo *)((u32 *)tmpdata_ptr+1));//������������modified by lhl20140715,Ӧ�ò������������DCI�������ݰ�һ���͵�????

		resleft=Do_RAR_DCI1A( (struct S_RAinfo *)((u32 *)tmpdata_ptr+1));//����������
		if(resleft==0)//û����Դ
			SV(UL_resource_flag)=0;//������Դ��־
		//��IOCTRL�ķ�ʽ���͸���������㣬Do_RAR_DCI�������Ѿ�����
	}
	fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
FOUT;

}

/************************************************************************
*author:HQ
*description:�������е�������ֻ�ǽ��û����뵽�ȴ����ȵĶ�����
*version1.0-20140601 
************************************************************************/
static void handle_ulsched_req()//�������е�������
{
	void *tmpdata_ptr;
	FIN(handle_ulsched_req());	
	SV_PTR_GET(mac_sv);
	tmpdata_ptr = fsm_data_get();//��ø��û�����Ӧ��Ϣ
	fsm_printf("receive SR from PHY  ");//testing code
	insert_ULschedQue(SV(ULschedQue_p), (struct S_UEinfo *)tmpdata_ptr);//�����û����뵽���е��ȶ�����,�ȴ�������
	SV(UL_sched_flag) = 1;//����UL���б�־Ϊ"��Ҫ����"
	//fsm_printf("UE RNTI:%d\n",((struct S_UEinfo *)tmpdata_ptr)->rnti);//testing code
	fsm_data_destroy(tmpdata_ptr);//�ͷ��ڴ�
FOUT;
}


/*****************Testing functions*********************/

void test_queue_manager(struct list_head *listhead)
{
	struct S_UEinfo ueinfo[5]={{1,11},{2,12},{3,13},{4,14},{5,15}};
	struct S_UEinfo myue;
	insert_ULschedQue(listhead,&ueinfo[0]);
	insert_ULschedQue(listhead,&ueinfo[4]);
	//insert_queue(listhead,S_ULsched_QueueEntry,&ueinfo[4]) //ʹ�ú궨��ķ�ʽ
	insert_ULschedQue(listhead,&ueinfo[2]);
	print_ULschedQue(listhead);
   //take_first_entry(listhead,S_ULsched_QueueEntry,&myue) //ʹ�ú궨��ķ�ʽ
	//fsm_printf("use DEFINE take a UE RNTI:%d,CQI:%d\n",myue.rnti,myue.cqi);
	print_ULschedQue(listhead);
	insert_ULschedQue(listhead,&ueinfo[0]);
	print_ULschedQue(listhead);
	myue = take_first_ULschedQue(listhead); //ʹ�ú������õķ�ʽ 
	fsm_printf("call func take a UE RNTI:%d,CQI:%d\n",myue.rnti,myue.cqi);
	print_ULschedQue(listhead);
	//print_queue(listhead,S_ULsched_QueueEntry)
	clean_ULschedQue(listhead);//��ն���
	clean_ULschedQue(listhead);
	//clean_queue(listhead,S_ULsched_QueueEntry)//ʹ�ú������õķ�ʽ 
	//myue = take_first_ULschedQue(listhead); //���ԶԿն��еĲ��� 
    //fsm_printf("call func take a UE RNTI:%d,CQI:%d\n",myue.rnti,myue.cqi);
	fsm_printf("empty or not :%d \n",list_empty_careful(listhead));//�������Ƿ�Ϊ�գ��øú�����ǰ����ɾ��ʱ�õ��Ǻ���list_del_init����
    //��ӡ��1��˵������Ϊ��
}

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

/**********************Testing functions end*********************************/

static MAC_LogicalChannelConfig_IoctrlMsg * rrc_lc_config(unsigned short rnti,int lcid)
{
	MAC_LogicalChannelConfig_IoctrlMsg *lcinfo =(MAC_LogicalChannelConfig_IoctrlMsg *)fsm_mem_alloc(sizeof(MAC_LogicalChannelConfig_IoctrlMsg));
	struct Ul_SpecificParameters param[3] = {{1,infinity,bucketSizeDuration_ms50,0},{2,kBps16,bucketSizeDuration_ms50,2},{3,kBps16,bucketSizeDuration_ms100,3}};

	FIN(MAC_LogicalChannelConfig_IoctrlMsg * rrc_lc_config());

	lcinfo->rnti = rnti ; //��ӦRNTIֵ
	lcinfo->logicalChannelIdentity = lcid ; //��ӦLCID
    lcinfo->logicalChannelConfig.haveUl_SpecificParameters = true;
    lcinfo->logicalChannelConfig.ul_SpecificParameters = param[lcid]; //param[]�±���LCID��Ӧ 
    FRET(lcinfo);
}

	
	
	
	




