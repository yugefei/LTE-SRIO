#include <linux/if_ether.h>
/****lhl�Ķ�20140410****/
#include <linux/list.h>
#include <linux/kernel.h>
#include <stddef.h>
/****lhl�Ķ�����20140410****/
#include "macfsm.h"
//#include "macpkfmt.h"
//#include "rrc_config.h"




/************************UL schedule LiuHanLi**************************/
/************************��ʼ��MAC����ȫ�ֱ�������***********************/
void Init_Enbmac_Scheduler(void)
{
       int i;
	FIN(Init_Enbmac_Scheduler(void));
	SV_PTR_GET(mac_sv);
	//SV(LCGZeroToData)=false;
	//SV(DATA_WAIT_ALLOCATION)=false;	
	for(i=0;i<USERNUMMAX;i++)
	{
		SV(Enb_MacBuffer_RLC[i])=(struct list_head *)fsm_mem_alloc(sizeof(struct list_head));
		SV(Enb_LogicalChannel_Bj[i])=(struct list_head *)fsm_mem_alloc(sizeof(struct list_head));
		SV(Enb_LogicalChannel_Config[i])=(struct list_head *)fsm_mem_alloc(sizeof(struct list_head));
		INIT_LIST_HEAD(SV(Enb_MacBuffer_RLC[i]));
		INIT_LIST_HEAD(SV(Enb_LogicalChannel_Bj[i]));
		INIT_LIST_HEAD(SV(Enb_LogicalChannel_Config[i]));
	}
	FOUT;
}

/*******20140526 ��RLC����������ת��Ϊ��������Ϊ����֮ǰ����Ʊ���һ��,���һ���û�********/
/*****rlc_request_arrayΪÿ���û�������ͷָ�룬num�Ǹ��û�������ڵ����******/
/*****uesernum:��rlc�����ж�Ӧ�ĵ�uesernum���û�,��0��ʼ*****/
RlcBufferRequest * RlcRequest_arraytolist(RLC_Request *rlc_request_array,int num,int uesernum)//num������ĳ���
{
	int i;
	RlcBufferRequest *rlcrequest;
	RlcBufferRequest *rlcrequest_temp;
	FIN(RlcRequest_arraytolist(RLC_Request *rlc_request_array,int num,int uesernum));
	SV_PTR_GET(mac_sv);
	rlcrequest=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
	while(rlcrequest==0)//�����ڴ�ʧ�ܣ��ٴ����룬ֱ������ɹ�
	{
		rlcrequest=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
	}
	INIT_LIST_HEAD(&(rlcrequest->list));
	for(i=0;i<num;i++)
	{
		rlcrequest_temp=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
		while(rlcrequest_temp==0)//�����ڴ�ʧ�ܣ��ٴ����룬ֱ������ɹ�
		{
			rlcrequest_temp=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
		}
		INIT_LIST_HEAD(&(rlcrequest_temp->list));
		rlcrequest_temp->rnti=rlc_request_array[i].rnti;
		rlcrequest_temp->lcid=rlc_request_array[i].lcid;
		rlcrequest_temp->txQueueSize=rlc_request_array[i].txQueueSize;
		rlcrequest_temp->txQueueHeader=rlc_request_array[i].txQueueHeader;
		rlcrequest_temp->retxQueueSize=rlc_request_array[i].retxQueueSize;
		rlcrequest_temp->retxQueueHeader=rlc_request_array[i].retxQueueHeader;
		rlcrequest_temp->statusPduSize=rlc_request_array[i].statusPduSize;
		rlcrequest_temp->statusPduHeader=rlc_request_array[i].statusPduHeader;
		list_add_tail(&(rlcrequest_temp->list), &(rlcrequest->list));
	}
	SV(Rlc_Request_Num[uesernum])=num;//��ǰ������Դ�ĵ�index���û�������ڵ㳤�������û�������Ҫ�����߼��ŵ���
	FRET(rlcrequest);
}


/*******20140529 ��RLC����������ת��Ϊ��������Ϊ����֮ǰ����Ʊ���һ��********/
/*******����RlcBufferRequestΪRLC report���������*num��Ҫ���͵�IOCTL��buffer���ȣ�����RLC �����ͷָ��***************/
/*******reqnum��ʾ���û���Ӧ��Rlc_Request_Num*******/
RLC_Request * RlcRequest_listtoarray( RlcBufferRequest *rlc_request,int reqnum ,int *num)//num��report������
{
	struct list_head *pos,*p;
	RlcBufferRequest *temp;
	int i;
	RLC_Request *rlc_report_temp;
	FIN( RlcRequest_listtoarray( RlcBufferRequest *rlc_request,int reqnum ,int *num));
	SV_PTR_GET(mac_sv);
	rlc_report_temp=(RLC_Request *)fsm_mem_alloc(sizeof(RLC_Request)*reqnum);//��̬����report���ܸ���
	while(rlc_report_temp==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
	{
		rlc_report_temp=(RLC_Request *)fsm_mem_alloc(sizeof(RLC_Request)*reqnum);
	}
	pos=NULL,p=NULL,temp=NULL;
	i=0;
	//rlc_report_temp=(RLC_Request *)((int *)rlc_report);//ָ��ָ��������׵�ַ
	list_for_each_safe(pos,p,&(rlc_request->list))//����
	{
		temp=list_entry(pos,RlcBufferRequest,list);
		rlc_report_temp[i].rnti=temp->rnti;
		rlc_report_temp[i].lcid=temp->lcid;
		rlc_report_temp[i].txQueueSize=temp->txQueueSize;
		rlc_report_temp[i].txQueueHeader=temp->txQueueHeader;
		rlc_report_temp[i].retxQueueSize=temp->retxQueueSize;
		rlc_report_temp[i].retxQueueHeader=temp->retxQueueHeader;
		rlc_report_temp[i].statusPduSize=temp->statusPduSize;
		rlc_report_temp[i].statusPduHeader=temp->statusPduHeader;
		i++;
	}
    *num=i;//����RLC report���ܸ�����С
	pos=NULL,p=NULL,temp=NULL;
	list_for_each_safe(pos,p,&(rlc_request->list))//����
	{
        	temp=list_entry(pos,RlcBufferRequest,list);
        	list_del_init(&(temp->list));
        	fsm_mem_free(temp);//�ͷ���Դ
  	}
	FRET(rlc_report_temp);
}



/***************��RLC���buffer���󣬸���MAC��buffer״̬����****************/
/*********����RlcBufferRequest* params Ϊһ���û���RLC��������ͷָ��************/
/***list_head  *enb_buffer_rlcΪĳ���û���BUFFER�׵�ַ����enb_buffer_rlc=SV(Enb_MacBuffer_RLC[index])**/
void * DoRefreshRLCBuffserRequest (RlcBufferRequest* params,struct list_head *enb_buffer_rlc)	
{
	RlcBufferRequest *RLChead=params,*temp=NULL;
	struct list_head *pos,*p;
	MacBufferStatus *temp_mac_bufferstatus=NULL;
	MacBufferStatus *temp_mac_findno=NULL;
	unsigned char temp_lcid,temp_mac_bufferstatus_lcid;
    FIN(DoRefreshRLCBuffserRequest(RlcBufferRequest* params));
    SV_PTR_GET(mac_sv);	
	bool flag=false;
	struct list_head *MacBuffer_RLC=enb_buffer_rlc;//ͷָ��		
    //SV(DATA_WAIT_ALLOCATION)=true;//�����ݴ�����
	//fsm_printf("[MAC] received rnti = %d\n", params->rnti);
     list_for_each_safe(pos,p,&(RLChead->list))//����
    {
        temp=list_entry(pos,RlcBufferRequest,list);
        temp_lcid=temp->lcid;
        //length_rlc_request++;
        temp_mac_bufferstatus=NULL;
        list_for_each_entry(temp_mac_bufferstatus, MacBuffer_RLC,list)//����������MAC�Ƿ��Ѿ������߼��ŵ�������        
        {
            temp_mac_bufferstatus_lcid=temp_mac_bufferstatus->lcid;
            if(temp_lcid==temp_mac_bufferstatus_lcid)
            {
                temp_mac_bufferstatus->RlcRequestparams=Rlc_MacRequest_copy(temp);
				//fsm_printf("[MAC] temp_mac_bufferstatus->RlcRequestparams->rnti = %d\n", temp_mac_bufferstatus->RlcRequestparams->rnti);
                flag=true;
                break;
            }
        }
        if(flag==false)//����ʧ��
        {
        	temp_mac_findno=(MacBufferStatus *)fsm_mem_alloc(sizeof(MacBufferStatus));
            while(temp_mac_findno==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
            {
                temp_mac_findno=(MacBufferStatus *)fsm_mem_alloc(sizeof(MacBufferStatus));
            }
            INIT_LIST_HEAD(&(temp_mac_findno->list));
            temp_mac_findno->lcid=temp_lcid;
            temp_mac_findno->RlcRequestparams=Rlc_MacRequest_copy(temp);
			//fsm_printf("[MAC] temp_mac_findno->RlcRequestparams->rnti = %d\n", temp_mac_findno->RlcRequestparams->rnti);
            list_add_tail(&(temp_mac_findno->list), MacBuffer_RLC);
        }
        flag=false;
    }
    temp=NULL;
    list_for_each_safe(pos,p,&(RLChead->list))//����
    {
        temp=list_entry(pos,RlcBufferRequest,list);
        list_del_init(&(temp->list));
        fsm_mem_free(temp);//�ͷ���Դ
    }
    FOUT;
}

/****����RlcBufferRequest�ڵ㣬ʹ���ؽڵ�ɲ���MacBufferStatus�У����nextΪNULL������******/
RLC_Request* Rlc_MacRequest_copy(RlcBufferRequest *temp)
{
    FIN(Rlc_MacRequest_copy(RlcBufferRequest *temp));
	RLC_Request *copy=(RLC_Request *)fsm_mem_alloc(sizeof(RLC_Request));
	while(copy==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
	{
		copy=(RLC_Request *)fsm_mem_alloc(sizeof(RLC_Request));
	}
	copy->lcid=temp->lcid;
	copy->retxQueueHeader=temp->retxQueueHeader;
	copy->retxQueueSize=temp->retxQueueSize;
	copy->rnti=temp->rnti;
	copy->statusPduHeader=temp->statusPduHeader;
	copy->statusPduSize=temp->statusPduSize;
	copy->txQueueHeader=temp->txQueueHeader;
	copy->txQueueSize=temp->txQueueSize;
	FRET(copy);
}

LogicalChannelConfigInfo* LogicalChannel_ConfigInfo_copy(MAC_LogicalChannelConfig_IoctrlMsg *temp)
{
    FIN(LogicalChannel_ConfigInfo_copy(MAC_LogicalChannelConfig_IoctrlMsg *temp));
	LogicalChannelConfigInfo *copy=(LogicalChannelConfigInfo *)fsm_mem_alloc(sizeof(LogicalChannelConfigInfo));
	while(copy==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
	{
		copy=(LogicalChannelConfigInfo *)fsm_mem_alloc(sizeof(LogicalChannelConfigInfo));
	}
	INIT_LIST_HEAD(&(copy->list));
	copy->lcid=temp->logicalChannelIdentity;
	copy->rnti=temp->rnti;
	copy->priority=(temp->logicalChannelConfig).ul_SpecificParameters.priority;
    copy->prioritizedBitRateKbps=(temp->logicalChannelConfig).ul_SpecificParameters.prioritisedBitRate;
    copy->bucketSizeDurationMs=(temp->logicalChannelConfig).ul_SpecificParameters.bucketSizeDuration;
    copy->logicalChannelGroup=(temp->logicalChannelConfig).ul_SpecificParameters.logicalChannelGroup;
	FRET(copy);
}

RlcBufferRequest* Mac_RlcRequest_copy(RLC_Request *temp)//����RlcBufferRequest�ڵ�
{
    FIN(Mac_RlcRequest_copy(RLC_Request *temp));
	RlcBufferRequest *copy=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
	while(copy==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
	{
		copy=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
	}
	INIT_LIST_HEAD(&(copy->list));
	copy->lcid=temp->lcid;
	copy->retxQueueHeader=temp->retxQueueHeader;
	copy->retxQueueSize=temp->retxQueueSize;
	copy->rnti=temp->rnti;
	copy->statusPduHeader=temp->statusPduHeader;
	copy->statusPduSize=temp->statusPduSize;
	copy->txQueueHeader=temp->txQueueHeader;
	copy->txQueueSize=temp->txQueueSize;
	FRET(copy);
}

RLC_Request* Mac_MacRequest_copy(RLC_Request *temp)//����RlcBufferRequest�ڵ�
{
    FIN(Mac_MacRequest_copy(RLC_Request *temp));
	RLC_Request *copy=(RLC_Request *)fsm_mem_alloc(sizeof(RLC_Request));
	while(copy==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
	{
		copy=(RLC_Request *)fsm_mem_alloc(sizeof(RLC_Request));
	}
	copy->lcid=temp->lcid;
	copy->retxQueueHeader=temp->retxQueueHeader;
	copy->retxQueueSize=temp->retxQueueSize;
	copy->rnti=temp->rnti;
	copy->statusPduHeader=temp->statusPduHeader;
	copy->statusPduSize=temp->statusPduSize;
	copy->txQueueHeader=temp->txQueueHeader;
	copy->txQueueSize=temp->txQueueSize;
	FRET(copy);
}



/********************ÿ��TTI�����߼��ŵ���Bjֵ20140526modified ���������������**********************/
/********����enb_logicalChannel_bj ΪEnb_LogicalChannel_Bj[i]ͷָ��(��Ӧһ���û�)����Ҫ���ÿ���û�����*******/
/******** ����list_head *enb_logicalChannel_config ΪEnb_LogicalChannel_Config[i]ͷָ�룬��BJ��һһ��Ӧ��***********/
void FlushBj(struct  list_head *enb_logicalChannel_bj, struct list_head *enb_logicalChannel_config)
{
	 struct list_head  *head_Bj=enb_logicalChannel_bj;
	 LogicalChannelBj  *temp=NULL;
	LogicalChannelConfigInfo *temp_Logical_Channel_Config;
	int i;
	int temp_Bj_lcid,temp_lcc_lcid,BucketSize;
    	FIN(FlushBj(struct  list_head *enb_logicalChannel_bj, struct list_head *enb_logicalChannel_config));
   	 SV_PTR_GET(mac_sv);	
	bool flag_tail=false;
	list_for_each_entry(temp, head_Bj,list)//������ǰ�û���BJ����
	{
		temp_Bj_lcid=temp->lcid;
		flag_tail=false;
		temp_Logical_Channel_Config=NULL;
		list_for_each_entry(temp_Logical_Channel_Config, enb_logicalChannel_config,list)//�������û����߼��ŵ����ԣ��ҵ���Ӧ��LCID����
		 {
		  	if(temp->rnti==temp_Logical_Channel_Config->rnti)//ȷ������Ը��û���
		  	{
		  		temp_lcc_lcid=temp_Logical_Channel_Config->lcid;
			        if(temp_lcc_lcid==temp_Bj_lcid)
			        {
			            if((temp_Logical_Channel_Config->prioritizedBitRateKbps)==infinity)//���������
			            {
			                temp->lcbj=MAX_BJ/8+1;//����Ϊ���ֵ��1
			                flag_tail=true;
			            }
			            else//���������ʱ�ĸ���
			            {
				            BucketSize=(temp_Logical_Channel_Config->prioritizedBitRateKbps)*(temp_Logical_Channel_Config->bucketSizeDurationMs)/8;
			                    if(temp->lcbj < BucketSize)
			                       temp->lcbj=temp->lcbj+(temp_Logical_Channel_Config->prioritizedBitRateKbps)*TTI/8;//����8��ת��Ϊbyte
			                    else
			                        temp->lcbj=BucketSize;
			                    flag_tail=true;
						break;
					}		                	
			        }

		  	}
			else//�߼��ŵ����û���BJ������
			{
				 printk(KERN_INFO"Bj and logical channel ERROR");
				 FOUT;
			}
		}
		if(flag_tail==false)//û���ҵ���ƥ����߼��ŵ�
            		printk(KERN_INFO"FlushBj ERROR");//LogicalChannelConfig��LogicalChannelConfigBj��ƥ��
	}
	FOUT;
}

/**************(��ÿ���û�)*�����߼��ŵ����ȼ����߼��ŵ�����***************/
/******����ΪEnb_LogicalChannel_Config[i],��Ҫ���ÿ���û�������********/
LogicalChannelConfigInfo* LogicalChannel_ConfigInfo_Rank_Priority(struct list_head * enb_logicalChannel_config)
{

    FIN(LogicalChannel_ConfigInfo_Rank_Priority(struct list_head * enb_logicalChannel_config));
    SV_PTR_GET(mac_sv);
	LogicalChannelConfigInfo *lcc_info_priority=NULL,*temp=NULL,*temp_logicalChannel=NULL;
	lcc_info_priority=(LogicalChannelConfigInfo *)fsm_mem_alloc(sizeof(LogicalChannelConfigInfo ));
	while(lcc_info_priority==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
	{
		lcc_info_priority=(LogicalChannelConfigInfo *)fsm_mem_alloc(sizeof(LogicalChannelConfigInfo ));
	}
	INIT_LIST_HEAD(&(lcc_info_priority->list));
	LogicalChannelConfigInfo *next_node=NULL;
	LogicalChannelConfigInfo *temp_next=NULL;
	bool flag_add=false;
	list_for_each_entry(temp, enb_logicalChannel_config,list)//����
	{
	    next_node=(LogicalChannelConfigInfo *)fsm_mem_alloc(sizeof(LogicalChannelConfigInfo ));
	    while(next_node==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
	    {
		 next_node=(LogicalChannelConfigInfo *)fsm_mem_alloc(sizeof(LogicalChannelConfigInfo ));
	    }
		//fsm_printf("[mac] before sort lcid : %d\n", temp->lcid);
	    next_node->lcid=temp->lcid;
	 	next_node->rnti=temp->rnti;
        next_node->priority=temp->priority;
        next_node->prioritizedBitRateKbps=temp->prioritizedBitRateKbps;
        next_node->bucketSizeDurationMs=temp->bucketSizeDurationMs;
        next_node->logicalChannelGroup=temp->logicalChannelGroup;
        INIT_LIST_HEAD(&(next_node->list));
        if (list_empty(&(lcc_info_priority->list)))
            list_add_tail(&(next_node->list), &(lcc_info_priority->list));
        else
        {
            flag_add=false;
            list_for_each_entry(temp_next, &(lcc_info_priority->list),list)//����
            {
                if ((next_node->priority) <= (temp_next->priority))
                {
                    list_add_tail(&(next_node->list), &(temp_next->list));//��next_node�ӵ�temp_next��ǰ��
                    flag_add=true;
                    break;
                }
            }
            if(flag_add==false)
                list_add_tail(&(next_node->list), &(lcc_info_priority->list));
        }
    }
	FRET(lcc_info_priority);//���ؾ������ȼ��Ŷӵ�LogicalChannelConfigInfoͷָ��
}

/******�����߼��ŵ����ȼ�˳�򣬶�MacBufferStatus�������ȼ�����********/
/******����ΪEnb_LogicalChannel_Config[i],��Ҫ���ÿ���û�������********/
/******����Ϊenb_buffer_rlc[i],��Ҫ���ÿ���û�������********/
MacBufferStatus* PrioritySort(struct  list_head * enb_logicalChannel_config,struct list_head *enb_buffer_rlc)
{

	MacBufferStatus *PriorityMacBufferStatus,*temp_mbs=NULL,*temp_node;
	LogicalChannelConfigInfo *Priority_logicalChannel=NULL,*temp_logicalChannel=NULL;
	int flag;//��־�߼��ŵ���Ϣ��BUFFER�Ƿ�ƥ��
	struct list_head *pos,*p;
    FIN(PrioritySort(struct  list_head * enb_logicalChannel_config,struct list_head *enb_buffer_rlc));
    SV_PTR_GET(mac_sv);
	if (list_empty(enb_buffer_rlc))
	{
		printk(KERN_INFO"PrioritySort:input enb_mac buffer error ");
		FRET(NULL);
	}
	else
	{
		PriorityMacBufferStatus=(MacBufferStatus *)fsm_mem_alloc(sizeof(MacBufferStatus));
		//while(PriorityMacBufferStatus==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
		//{
			//PriorityMacBufferStatus=(MacBufferStatus *)fsm_mem_alloc(sizeof(MacBufferStatus));
		 //}
		unsigned char temp_Bj_lcid;
	    INIT_LIST_HEAD(&(PriorityMacBufferStatus->list));
		Priority_logicalChannel=LogicalChannel_ConfigInfo_Rank_Priority(enb_logicalChannel_config);
		flag=false;
		list_for_each_entry(temp_logicalChannel, &(Priority_logicalChannel->list),list)//����
		{
			
			temp_Bj_lcid=temp_logicalChannel->lcid;
			list_for_each_entry(temp_node, enb_buffer_rlc,list)//����
			{
				//fsm_printf("[mac] temp_Bj_lcid = %d, temp_node->lcid = %d\n", temp_Bj_lcid, temp_node->lcid);
			    if(temp_Bj_lcid==temp_node->lcid)
			    {
			        temp_mbs=(MacBufferStatus *)fsm_mem_alloc(sizeof(MacBufferStatus));
				while(temp_mbs==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
				{
					temp_mbs=(MacBufferStatus *)fsm_mem_alloc(sizeof(MacBufferStatus));
				 }
	                INIT_LIST_HEAD(&(temp_mbs->list));
			        temp_mbs->lcid=temp_node->lcid;
			        temp_mbs->RlcRequestparams=Mac_MacRequest_copy(temp_node->RlcRequestparams);
			        list_add_tail(&(temp_mbs->list), &(PriorityMacBufferStatus->list));
				flag=true;
			        break;
			    }
			}
		}
	}
	if(flag==false)
	{
		printk(KERN_INFO"the function of PrioritySort() error :channel and buffer don't match\n");		
	}
	temp_logicalChannel=NULL;
	pos=NULL,p=NULL;
	list_for_each_safe(pos,p,&(Priority_logicalChannel->list))//����
    	{
	        temp_logicalChannel=list_entry(pos,LogicalChannelConfigInfo,list);
	        list_del_init(&(temp_logicalChannel->list));//ɾ���ڵ�
	        fsm_mem_free(temp_logicalChannel);//�ͷ���Դ
   	 }
	FRET(PriorityMacBufferStatus);
}

unsigned short Getrnti_From_Enbbuffer(struct list_head *enb_buffer_rlc)
{
	struct list_head *pos=NULL,*p=NULL;
	MacBufferStatus *temp_rlc;
	unsigned short rnti;
	FIN(Getrnti_From_Enbbuffer(struct list_head *enb_buffer_rlc));
	SV_PTR_GET(mac_sv);
	 list_for_each_safe(pos,p,enb_buffer_rlc)
	 {
	 	temp_rlc=list_entry(pos,MacBufferStatus,list);
		rnti=temp_rlc->RlcRequestparams->rnti;
		break;
	 }
	 FRET(rnti);
}
 struct list_head * Get_LogicalChannelInfo_From_Rnti(unsigned short m_rnti)
 {
 	int i;
       struct list_head *pos=NULL,*p=NULL;
	LogicalChannelConfigInfo *temp_lc_config;
	FIN(Get_LogicalChannelInfo_From_Rnti(unsigned short m_rnti));
	SV_PTR_GET(mac_sv);
	for(i=0;i<USERNUMMAX;i++)//�����û�
	{
		pos=NULL,p=NULL;
		 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))
		{
			temp_lc_config=list_entry(pos,LogicalChannelConfigInfo,list);
			if (m_rnti==temp_lc_config->rnti)//���Ҿ�����ͬRNTI���û�
			{
				FRET(SV(Enb_LogicalChannel_Config[i]));//���ظ��û��߼��ŵ�ͷָ��
			}
			else
				break;
		 }
	}
	printk(KERN_INFO"Get_LogicalChannelInfo_From_Rnti:error\n");
	FRET(NULL);
 }
 
 struct list_head * Get_Enbbuffer_From_Rnti(unsigned short m_rnti)
 {
 	int i;
       struct list_head *pos=NULL,*p=NULL;
	MacBufferStatus *temp;
	FIN(Get_Enbbuffer_From_Rnti(unsigned short m_rnti));
	SV_PTR_GET(mac_sv);
	for(i=0;i<USERNUMMAX;i++)//�����û�
	{
		pos=NULL,p=NULL;
		 list_for_each_safe(pos,p,SV(Enb_MacBuffer_RLC[i]))
		{
			temp=list_entry(pos,MacBufferStatus,list);
			if (m_rnti==temp->RlcRequestparams->rnti)//���Ҿ�����ͬRNTI���û�
			{
				FRET(SV(Enb_MacBuffer_RLC[i]));//���ظ��û��߼��ŵ�ͷָ��
			}
			else
				break;
		 }
	}
	printk(KERN_INFO"Get_Enbbuffer_From_Rnti:error\n");
	FRET(NULL);
 }


/************ ����:��ENBĳ���û��������ҵ���Ӧ�û����߼��ŵ�����*************/
/*********����Ϊĳ���û������ݷ�������*******/
/****���Ϊ���û���Ӧ���߼��ŵ���������ͷָ��******/
 struct list_head * Get_LogicalChannelInfo_From_Enbbuffer(struct list_head *enb_buffer_rlc)
{
	int i;
	int rnti_temp;
	struct list_head *pos=NULL,*p=NULL;
	LogicalChannelConfigInfo *temp_lc_config;
	MacBufferStatus *temp_rlc;
	FIN(Get_LogicalChannelInfo_From_Enbbuffer(struct list_head *enb_buffer_rlc));
	SV_PTR_GET(mac_sv);
	 list_for_each_safe(pos,p,enb_buffer_rlc)
	 {
	 	temp_rlc=list_entry(pos,MacBufferStatus,list);
		rnti_temp=temp_rlc->RlcRequestparams->rnti;
		break;
	 } 	
	if(list_empty(enb_buffer_rlc))//�����û���buffer����Ϊ��
	{
		printk(KERN_INFO"Get_LogicalChannelInfo_From_Enbbuffer:input enb_mac buffer error ");
		FRET(NULL);
	}
	else
	{
		for(i=0;i<USERNUMMAX;i++)//�����û�
		{
			pos=NULL,p=NULL;
			 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))
			{
				temp_lc_config=list_entry(pos,LogicalChannelConfigInfo,list);
				if (rnti_temp==temp_lc_config->rnti)//���Ҿ�����ͬRNTI���û�
				{
					FRET(SV(Enb_LogicalChannel_Config[i]));//���ظ��û��߼��ŵ�ͷָ��
				}
				else
					break;
			 }
		}
	}
	printk(KERN_INFO"logical channel and user rnti don't match");
	FRET(NULL);//���ؿ�ָ��
	
}

 struct list_head * Get_LogicalChannelBj_From_Rnti(unsigned short m_rnti)
 {
 	int i;	
	struct list_head *pos=NULL,*p=NULL;
	LogicalChannelBj *temp_bj;
	MacBufferStatus *temp_rlc;
	FIN(Get_LogicalChannelBj_From_Rnti(unsigned short m_rnti));
	SV_PTR_GET(mac_sv);
	for(i=0;i<USERNUMMAX;i++)//�����û�
	{
		pos=NULL,p=NULL;
		 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Bj[i]))
		{
			temp_bj=list_entry(pos,LogicalChannelBj,list);
			if(m_rnti==temp_bj->rnti)//���Ҿ�����ͬRNTI���û�
			{
				FRET(SV(Enb_LogicalChannel_Bj[i]));//���ظ��û�BJ ͷָ��
			}
			else
				break;
		 }
	}
	printk(KERN_INFO"Get_LogicalChannelBj_From_Rnti:error\n");
	FRET(NULL);//���ؿ�ָ��

 }

/************ ����:��ENBĳ���û��������ҵ���Ӧ�û����߼��ŵ���BJ*************/
/*********����Ϊĳ���û������ݷ�������*******/
/****���Ϊ���û���Ӧ���߼��ŵ�BJ ����ͷָ��******/
 struct list_head * Get_LogicalChannelBj_From_Enbbuffer(struct list_head *enb_buffer_rlc)
{
	int i;
	int rnti_temp;
	struct list_head *pos=NULL,*p=NULL;
	LogicalChannelBj *temp_bj;
	MacBufferStatus *temp_rlc;
	FIN(Get_LogicalChannelBj_From_Enbbuffer(struct list_head *enb_logicalchannel_bj));
	SV_PTR_GET(mac_sv);
	 list_for_each_safe(pos,p,enb_buffer_rlc)
	 {
	 	temp_rlc=list_entry(pos,MacBufferStatus,list);
		rnti_temp=temp_rlc->RlcRequestparams->rnti;
		break;
	 }
	if(list_empty(enb_buffer_rlc))//�����û���buffer����Ϊ��
	{
		printk(KERN_INFO"Get_LogicalChannelInfo_From_Enbbuffer:input enb_mac buffer error ");
		FRET(NULL);
	}
	else
	{
		for(i=0;i<USERNUMMAX;i++)//�����û�
		{
			pos=NULL,p=NULL;
			 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Bj[i]))
			{
				temp_bj=list_entry(pos,LogicalChannelBj,list);
				if(rnti_temp==temp_bj->rnti)//���Ҿ�����ͬRNTI���û�
				{
					FRET(SV(Enb_LogicalChannel_Bj[i]));//���ظ��û�BJ ͷָ��
				}
				else
					break;
			 }
		}
	}
	printk(KERN_INFO"logical channel BJ and user rnti don't match");
	FRET(NULL);//���ؿ�ָ��	
}

void Init_LogicalChannel_ConfigInfo(MAC_LogicalChannelConfig_IoctrlMsg *lc_info)
{
    struct list_head *pos=NULL,*p=NULL;
    LogicalChannelConfigInfo *temp_lc_config=NULL;
    LogicalChannelConfigInfo *temp_add=NULL;
    LogicalChannelBj *temp_bj=NULL;
    FIN(Init_LogicalChannel_ConfigInfo(MAC_LogicalChannelConfig_IoctrlMsg *lc_info));
    SV_PTR_GET(mac_sv);
    bool flag=false;    
    int temp_lcid=lc_info->logicalChannelIdentity;
    int temp_rnti=lc_info->rnti;
    int temp_lc_config_lcid;
	int i=0;
	for(i=0;i<USERNUMMAX;i++)
	{	
		 if(list_empty( SV(Enb_LogicalChannel_Config[i])))//����Ϊ��
		 {
		 	  temp_add=LogicalChannel_ConfigInfo_copy(lc_info);
		        list_add_tail(&(temp_add->list), SV(Enb_LogicalChannel_Config[i]));//��Ӹ��û����߼��ŵ�����
		        temp_bj=(LogicalChannelBj *)fsm_mem_alloc(sizeof(LogicalChannelBj));//ͬʱ����߼��ŵ�BJ
		        while(temp_bj==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
		        {
		            temp_bj=(LogicalChannelBj *)fsm_mem_alloc(sizeof(LogicalChannelBj));
		        }		       
		        INIT_LIST_HEAD(&(temp_bj->list));
		        temp_bj->lcid=lc_info->logicalChannelIdentity;
			temp_bj->rnti=lc_info->rnti;
		        if((temp_add->prioritizedBitRateKbps)==infinity)
//����Ĵ���Ϊ���
		            temp_bj->lcbj=MAX_BJ/8+1;
		        else
		            temp_bj->lcbj=0;//���������ʼ��Ϊ0
		        list_add_tail(&(temp_bj->list), SV(Enb_LogicalChannel_Bj[i]));//��ΪBJ ���߼��ŵ���һһ��Ӧ��
			//break;
			FOUT;
		 }
		 else//����ǿ�
		 {
		 	 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))//����
			    {
			    	 temp_lc_config=list_entry(pos,LogicalChannelConfigInfo,list);
			    	if(temp_lc_config->rnti==temp_rnti)//������Ը��û�������
			    	{
			    		pos=NULL,p=NULL;
					flag=false;
			    		 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))//���±�����Ѱ���Ƿ��Ѿ������˸��߼��ŵ�����������£�������ӽڵ�
			    		 {
			    		 	temp_lc_config=list_entry(pos,LogicalChannelConfigInfo,list);
			    		 	temp_lc_config_lcid=temp_lc_config->lcid;
					        if(temp_lcid==temp_lc_config_lcid)//�Ѿ������˸��ŵ����������Ϣ
					        {
					            if((lc_info->logicalChannelConfig).haveUl_SpecificParameters==true)
					            {
					                temp_lc_config->priority=(lc_info->logicalChannelConfig).ul_SpecificParameters.priority;
					                temp_lc_config->prioritizedBitRateKbps=(lc_info->logicalChannelConfig).ul_SpecificParameters.prioritisedBitRate;
					                temp_lc_config->bucketSizeDurationMs=(lc_info->logicalChannelConfig).ul_SpecificParameters.bucketSizeDuration;
					                temp_lc_config->logicalChannelGroup=(lc_info->logicalChannelConfig).ul_SpecificParameters.logicalChannelGroup;
					                flag=true;
					               // break;
					               FOUT;
					            }
					        }
			    		 }
	  				   if(flag==false)//���û�����ø��ŵ�����Ϣ���������Ϣ
	  				    {
	  				        temp_add=LogicalChannel_ConfigInfo_copy(lc_info);
	  				        list_add_tail(&(temp_add->list), SV(Enb_LogicalChannel_Config[i]));
	  				        temp_bj=(LogicalChannelBj *)fsm_mem_alloc(sizeof(LogicalChannelBj));
	  				        while(temp_bj==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
	  				        {
	  				            temp_bj=(LogicalChannelBj *)fsm_mem_alloc(sizeof(LogicalChannelBj));
	  				        }
	  				        INIT_LIST_HEAD(&(temp_bj->list));
	  				        temp_bj->lcid=lc_info->logicalChannelIdentity;
						temp_bj->rnti=lc_info->rnti;
	  				        if((temp_add->prioritizedBitRateKbps)==infinity)
	  				            temp_bj->lcbj=MAX_BJ/8+1;
	  				        else
	  				            temp_bj->lcbj=0;
	  				        list_add_tail(&(temp_bj->list), SV(Enb_LogicalChannel_Bj[i]));
						//break;
						FOUT;
	  				    }
				        
			    	}
				else
					break;//������Ը��û������ã�������һ���û�
		 	 }
			//break;
		 }
	}
    FOUT;
}


/*
******************************
->Change Data and time: 20141008
->Function:
->Change:
->Details:ʣ����Դ�����ش�bufferʱ�ķ��䷽��
->Input:temp_mac_buffer��ǰҪ������Դ���߼��ŵ���RLC����
->Input:temp_logicalchannel_bj:��ǰҪ������߼��ŵ�������
->Input:int retxlength:���߼��ŵ��������ش�PDU����
->Input:int txlength���߼��ŵ������д���PDU����
->Output:mac_rlc_report:������RLC��reportָ��,
->Output:temp_rlc_report:RLC REPORT��һ���ڵ�
->Output:*res_lengthʣ����Դ����
->Special:
*******************************
*/
void leftresource_morethan_retxbuffer_eachlogicalchannel(RlcBufferRequest *mac_rlc_report,RlcBufferRequest *temp_rlc_report,MacBufferStatus *temp_mac_buffer, LogicalChannelBj *temp_logicalchannel_bj,int retxlength,int txlength,int *res_length)
{
	FIN(leftresource_morethan_retxbuffer_eachlogicalchannel());
	temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
	temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
	*res_length=*res_length-retxlength;
	temp_logicalchannel_bj->lcbj-=retxlength;
	//temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
	// temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
	if(*res_length>=txlength)
	{
		temp_rlc_report->txQueueHeader=temp_mac_buffer->RlcRequestparams->txQueueHeader;
		temp_rlc_report->txQueueSize=temp_mac_buffer->RlcRequestparams->txQueueSize;
		temp_logicalchannel_bj->lcbj-=txlength;
		// temp_mac_buffer->RlcRequestparams->txQueueHeader=0;
		// temp_mac_buffer->RlcRequestparams->txQueueSize=0;
		list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
		*res_length-=txlength;
		//  break;
	}
	else
	{
		if(*res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//����ͷ��
		{
			temp_rlc_report->txQueueHeader=temp_mac_buffer->RlcRequestparams->txQueueHeader;
			*res_length=*res_length-(temp_mac_buffer->RlcRequestparams->txQueueHeader);
			temp_rlc_report->txQueueSize=*res_length;
			temp_logicalchannel_bj->lcbj-=(temp_mac_buffer->RlcRequestparams->txQueueHeader+temp_rlc_report->txQueueSize);
			// temp_mac_buffer->RlcRequestparams->txQueueHeader=0;
			// temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
			list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
			*res_length=0;
			// break;
		}
		else if(*res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//С��ͷ��
		{
			
			if(*res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//С��ͷ����������
			{
				temp_rlc_report->txQueueSize=temp_mac_buffer->RlcRequestparams->txQueueSize;
				temp_rlc_report->txQueueHeader=*res_length-(temp_mac_buffer->RlcRequestparams->txQueueSize);

				temp_logicalchannel_bj->lcbj-=*res_length;
				//  temp_mac_buffer->RlcRequestparams->txQueueHeader-=temp_rlc_report->txQueueHeader;
				// temp_mac_buffer->RlcRequestparams->txQueueSize=0;
				*res_length=0;
				list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
				//  break;
			}
			else//С��ͷ��С������
			{
				temp_rlc_report->txQueueSize=*res_length;
				temp_rlc_report->txQueueHeader=0;
				temp_logicalchannel_bj->lcbj-=*res_length;
				//temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
				*res_length=0;
				list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
				// break;
			}
		}
	}
	FOUT;
}


/*
******************************
->Change Data and time: 20141008
->Function:
->Change:
->Details:ʣ����ԴС���ش�bufferʱ�ķ��䷽��
->Input:temp_mac_buffer��ǰҪ������Դ���߼��ŵ���RLC����
->Input:temp_logicalchannel_bj:��ǰҪ������߼��ŵ�������
->Input:int statuslength:���߼��ŵ�������״̬PDU����
->Input:int retxlength:���߼��ŵ��������ش�PDU����
->Input:int txlength���߼��ŵ������д���PDU����
->Output:mac_rlc_report:������RLC��reportָ��
->Output:temp_rlc_report:RLC REPORT��һ���ڵ� 
->Output:*res_lengthʣ����Դ����
->Special:
*******************************
*/
void leftresource_lessthan_retxbuffer_eachlogicalchannel(RlcBufferRequest *mac_rlc_report,RlcBufferRequest *temp_rlc_report,MacBufferStatus *temp_mac_buffer, LogicalChannelBj *temp_logicalchannel_bj,int retxlength,int txlength,int *res_length)
{
	FIN(leftresource_lessthan_retxbuffer_eachlogicalchannel());
	if(*res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//����ͷ��
	{
		temp_logicalchannel_bj->lcbj-=*res_length;
		temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
		*res_length=*res_length-(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
		temp_rlc_report->retxQueueSize=*res_length;
		temp_rlc_report->txQueueHeader=0;
		temp_rlc_report->txQueueSize=0;
		// temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
		// temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
		list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
		*res_length=0;
		// break;
	}
	else if(*res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//С���ش�ͷ��
	{
		if(*res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//С��ͷ����������
		{
			temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
			temp_rlc_report->retxQueueHeader=*res_length-(temp_mac_buffer->RlcRequestparams->retxQueueSize);

			temp_logicalchannel_bj->lcbj-=*res_length;
			// temp_mac_buffer->RlcRequestparams->retxQueueHeader-=temp_rlc_report->retxQueueHeader;
			//temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
			temp_rlc_report->txQueueHeader=0;
			temp_rlc_report->txQueueSize=0;
			*res_length=0;
			list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
			// break;
		}
		else//С��ͷ��С������
		{
			temp_rlc_report->retxQueueSize=*res_length;
			temp_rlc_report->retxQueueHeader=0;
			temp_rlc_report->txQueueHeader=0;
			temp_rlc_report->txQueueSize=0;
			temp_logicalchannel_bj->lcbj-=*res_length;
			// temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
			*res_length=0;
			list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
			//break;
		}
	}
	FOUT;
}


/*
******************************
->Change Data and time: 20141008
->Function:
->Change:
->Details:ʣ����ԴС��״̬PDUʱ�������ش�PDU
->Input:temp_mac_buffer��ǰҪ������Դ���߼��ŵ���RLC����
->Input:temp_logicalchannel_bj:��ǰҪ������߼��ŵ�������
->Input:int statuslength:���߼��ŵ�������״̬PDU����
->Input:int retxlength:���߼��ŵ��������ش�PDU����
->Input:int txlength���߼��ŵ������д���PDU����
->Output:mac_rlc_report:������RLC��reportָ��
->Output:*res_lengthʣ����Դ����
->Special:
*******************************
*/
void ResourceAllocation_logicalchannel_firstretxbuffer(RlcBufferRequest *mac_rlc_report,MacBufferStatus *temp_mac_buffer, LogicalChannelBj *temp_logicalchannel_bj,int retxlength,int txlength,int *res_length)
{
	FIN(ResourceAllocation_logicalchannel_firstretxbuffer);
	RlcBufferRequest *temp_rlc_report;
	
	temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
	fsm_mem_set(temp_rlc_report,0,sizeof(RlcBufferRequest));
	INIT_LIST_HEAD(&(temp_rlc_report->list));        
	temp_rlc_report->lcid=temp_mac_buffer->RlcRequestparams->lcid;
	temp_rlc_report->rnti=temp_mac_buffer->RlcRequestparams->rnti;
	temp_rlc_report->statusPduHeader=0;
	temp_rlc_report->statusPduSize=0;//����״̬PDU
	if(*res_length >= retxlength)
	{
		leftresource_morethan_retxbuffer_eachlogicalchannel(mac_rlc_report,temp_rlc_report,temp_mac_buffer, temp_logicalchannel_bj,retxlength,txlength, res_length);
	}
	else if(*res_length < retxlength)
	{
		leftresource_lessthan_retxbuffer_eachlogicalchannel(mac_rlc_report,temp_rlc_report,temp_mac_buffer, temp_logicalchannel_bj,retxlength, txlength,res_length);
	}
	FOUT;
}


/*
******************************
->Change Data and time: 20141008
->Function:
->Change:
->Details:����״̬PDU buffer�ķ���
->Input:temp_mac_buffer��ǰҪ������Դ���߼��ŵ���RLC����
->Input:temp_logicalchannel_bj:��ǰҪ������߼��ŵ�������
->Input:int statuslength:���߼��ŵ�������״̬PDU����

->Input:int retxlength:���߼��ŵ��������ش�PDU����
->Input:int txlength���߼��ŵ������д���PDU����
->Output:mac_rlc_report:������RLC��reportָ��
->Output:*res_lengthʣ����Դ����
->Special:
*******************************
*/
void ResourceAllocation_logicalchannel_firststatusbuffer(RlcBufferRequest *mac_rlc_report,MacBufferStatus *temp_mac_buffer, LogicalChannelBj *temp_logicalchannel_bj,int statuslength,int retxlength,int txlength,int *res_length)
{
	FIN(ResourceAllocation_logicalchannel_firststatusbuffer());
	RlcBufferRequest *temp_rlc_report;
	
	temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
	fsm_mem_set(temp_rlc_report,0,sizeof(RlcBufferRequest));
	INIT_LIST_HEAD(&(temp_rlc_report->list));
	temp_rlc_report->lcid=temp_mac_buffer->RlcRequestparams->lcid;
	temp_rlc_report->rnti=temp_mac_buffer->RlcRequestparams->rnti;
	temp_rlc_report->statusPduHeader=temp_mac_buffer->RlcRequestparams->statusPduHeader;
	temp_rlc_report->statusPduSize=temp_mac_buffer->RlcRequestparams->statusPduSize;
	*res_length=*res_length-statuslength;        
	if(*res_length >= retxlength)
	{
		leftresource_morethan_retxbuffer_eachlogicalchannel(mac_rlc_report,temp_rlc_report,temp_mac_buffer, temp_logicalchannel_bj,retxlength,txlength, res_length);
	}
	else if(*res_length < retxlength)
	{
		leftresource_lessthan_retxbuffer_eachlogicalchannel(mac_rlc_report,temp_rlc_report,temp_mac_buffer, temp_logicalchannel_bj,retxlength, txlength,res_length);
	}
	FOUT;
}


/*
******************************
->Change Data and time: 20141008
->Function:
->Change:
->Details:ÿ���߼��ŵ�����Դ����
->Input:temp_mac_buffer��ǰҪ������Դ���߼��ŵ���RLC����
->Input:temp_logicalchannel_bj:��ǰҪ������߼��ŵ�������
->Input:int statuslength:���߼��ŵ�������״̬PDU����
->Input:int retxlength:���߼��ŵ��������ش�PDU����
->Input:int txlength���߼��ŵ������д���PDU����
->Output:mac_rlc_report:������RLC��reportָ�룬
->Special:
*******************************
*/
void ResourceAllocation_foreach_logicalchannel(RlcBufferRequest *mac_rlc_report,MacBufferStatus *temp_mac_buffer, LogicalChannelBj *temp_logicalchannel_bj,int statuslength,int retxlength,int txlength,int *res_length)
{
	FIN(ResourceAllocation_foreach_logicalchannel());
	RlcBufferRequest *temp_rlc_report=NULL;
	
	SV_PTR_GET(mac_sv);	
	if(*res_length>=(statuslength+retxlength+txlength))//TBSize����������
	{
		temp_rlc_report=Mac_RlcRequest_copy(temp_mac_buffer->RlcRequestparams);
		list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
		*res_length=*res_length-(statuslength+retxlength+txlength);
		temp_logicalchannel_bj->lcbj-=(statuslength+retxlength+txlength);	
		// break;
	}
	else if(*res_length>=statuslength)//�ȷ�״̬PDU ��TBSizeС�������󣬵�����״̬PDU
	{
		ResourceAllocation_logicalchannel_firststatusbuffer(mac_rlc_report,temp_mac_buffer,temp_logicalchannel_bj,statuslength,retxlength,txlength,res_length);
	}
	else if(*res_length <statuslength)//С��״̬PDU ��TBSizeС��������С��״̬PDU
	{
		ResourceAllocation_logicalchannel_firstretxbuffer(mac_rlc_report,temp_mac_buffer,temp_logicalchannel_bj,retxlength,txlength,res_length);
	}
	FOUT;
}



/*
******************************
->Change Data and time: 20141008
->Function:
->Change:Ϊ�˼��ٺ������Ӷȣ�ʹ�ö���Ӻ���
->Details:UE����Դ�����㷨������Ͱ
->Input:msg��Դ��С��SV(LogicalChannel_Bj)��
->Output:int *num:ָ��report�����С��void *:RLC reportָ��
->Special:
*******************************
*/

//void * ResourceAllocation_Algorithm(int resource_len,int *num)//num�����ָ��report�����С
RLC_Request * ResourceAllocation_Algorithm(int resource_len,struct list_head *enb_buffer_rlc,struct list_head * enb_logicalChannel_config,struct  list_head *enb_logicalChannel_bj,int *num,int buffer_len)//num�����ָ��report������
{

	

	//void *report_array;
	RLC_Request *report_array;
	//int *report_num;
	MacBufferStatus *lcbj_lessthan_zero;
	MacBufferStatus *temp_lessthan_zero;
	int temp_buffer_lcid;
	MacBufferStatus *priority_mac_buffer,*temp_mac_buffer,*temp_free;
	RlcBufferRequest *mac_rlc_report,*temp_rlc_report;
	LogicalChannelBj *temp_logicalchannel_bj;    
	int *res_length;
	int statuslength,retxlength,txlength;
	struct list_head *pos,*p;
	FIN(ResourceAllocation_Algorithm(int resource_len));
	SV_PTR_GET(mac_sv);
	priority_mac_buffer=NULL;
	temp_mac_buffer=NULL;
	temp_free=NULL;
	mac_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
	temp_rlc_report=NULL;
	lcbj_lessthan_zero =(MacBufferStatus *)fsm_mem_alloc(sizeof(MacBufferStatus));
	INIT_LIST_HEAD(&(lcbj_lessthan_zero->list));
	/*while(mac_rlc_report==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
	{
		mac_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
	}*/
	INIT_LIST_HEAD(&(mac_rlc_report->list));
	temp_logicalchannel_bj=NULL;
	res_length=&resource_len;
	statuslength=0,retxlength=0,txlength=0;
	pos=NULL,p=NULL;
	//priority_mac_buffer=PrioritySort();
	priority_mac_buffer=PrioritySort(enb_logicalChannel_config,enb_buffer_rlc);

	list_for_each_entry(temp_mac_buffer, &(priority_mac_buffer->list),list)//����
	{
		temp_buffer_lcid=temp_mac_buffer->lcid;
		if(*res_length<=0)//��ǰ��Դ�Ѿ�������
			break;
		temp_logicalchannel_bj=NULL;

		list_for_each_entry(temp_logicalchannel_bj,enb_logicalChannel_bj,list)//����
		{
			if(temp_buffer_lcid==(temp_logicalchannel_bj->lcid))
			{
				// printk(KERN_INFO"lcid:%d  lcbj:%d\n",temp_buffer_lcid,temp_logicalchannel_bj->lcbj);
				statuslength=(temp_mac_buffer->RlcRequestparams->statusPduSize)+(temp_mac_buffer->RlcRequestparams->statusPduHeader);
				retxlength=(temp_mac_buffer->RlcRequestparams->retxQueueSize)+(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
				txlength=(temp_mac_buffer->RlcRequestparams->txQueueSize)+(temp_mac_buffer->RlcRequestparams->txQueueHeader);
				
				if((temp_logicalchannel_bj->lcbj)==(MAX_BJ/8+1) &&(statuslength>0 || retxlength>0 ||txlength>0))//�ѵ�ǰ���е�ʣ����Դ�ָ����߼��ŵ�
				{
					if(*res_length>=(statuslength+retxlength+txlength))//TBSize����������
					{
						temp_rlc_report=Mac_RlcRequest_copy(temp_mac_buffer->RlcRequestparams);
						temp_rlc_report->statusPduSize=temp_rlc_report->statusPduSize+*res_length-(statuslength+retxlength+txlength);//�Ѷ����Դ��statusPduSize
						list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
						*res_length=0;//ʣ����ԴΪ0
						//temp_logicalchannel_bj->lcbj-=(statuslength+retxlength+txlength);
						break;
					}
					else if(*res_length>=statuslength)//�ȷ�״̬PDU
					{
						ResourceAllocation_logicalchannel_firststatusbuffer(mac_rlc_report,temp_mac_buffer,temp_logicalchannel_bj,statuslength,retxlength,txlength,res_length);
						break;
					}
					else if(*res_length <statuslength)//С��״̬PDU
					{
						ResourceAllocation_logicalchannel_firstretxbuffer(mac_rlc_report,temp_mac_buffer,temp_logicalchannel_bj,retxlength,txlength,res_length);
						break;
					}
				}
				else if((temp_logicalchannel_bj->lcbj)>=0)
				{
					fsm_printf("lcbj>=0\n");
					ResourceAllocation_foreach_logicalchannel(mac_rlc_report,temp_mac_buffer, temp_logicalchannel_bj,statuslength,retxlength,txlength,res_length);
					break;
				}
				else if((temp_logicalchannel_bj->lcbj)<0)
				{	
					fsm_printf("lcbj<0\n");
					temp_lessthan_zero=(MacBufferStatus *)fsm_mem_alloc(sizeof(MacBufferStatus));
					INIT_LIST_HEAD(&(temp_lessthan_zero->list));				
					
					fsm_mem_cpy(temp_lessthan_zero,temp_mac_buffer,sizeof(MacBufferStatus));
					temp_lessthan_zero->RlcRequestparams=(RLC_Request *)fsm_mem_alloc(sizeof(RLC_Request));
					fsm_mem_cpy(temp_lessthan_zero->RlcRequestparams,temp_mac_buffer->RlcRequestparams,sizeof(RLC_Request));
					list_add_tail(&(temp_lessthan_zero->list), &(lcbj_lessthan_zero->list));
					break;
				}			
				
			}
		}
	}

	if(*res_length>0)
	{
		temp_mac_buffer=NULL;
		//fsm_printf("*res_length>0\n");
		list_for_each_entry(temp_mac_buffer, &(lcbj_lessthan_zero->list),list)//����
		{	
			if(statuslength>0 || retxlength>0 ||txlength>0)
			{
				//fsm_printf("*res_length>0 inner\n");
				ResourceAllocation_foreach_logicalchannel(mac_rlc_report,temp_mac_buffer, temp_logicalchannel_bj,statuslength,retxlength, txlength,res_length);
			}
		}
	}
	//report_array=RlcRequest_listtoarray(mac_rlc_report,num); 

	//fsm_printf("mac_rlc_report:txQueueHeader:%d,mac_rlc_report->txQueueSize:%d\n",mac_rlc_report->txQueueHeader,mac_rlc_report->txQueueSize);
	report_array=RlcRequest_listtoarray(mac_rlc_report,buffer_len,num);

	pos=NULL,p=NULL;
	list_for_each_safe(pos,p,&(priority_mac_buffer->list))//����
	{
		temp_free=list_entry(pos,MacBufferStatus,list);
		fsm_mem_free(temp_free->RlcRequestparams);
		list_del_init(&(temp_free->list));
		fsm_mem_free(temp_free);
	}
	fsm_mem_free(priority_mac_buffer);

	pos=NULL,p=NULL;
	list_for_each_safe(pos,p,&(lcbj_lessthan_zero->list))//����
	{
		temp_free=NULL;
		temp_free=list_entry(pos,MacBufferStatus,list);
		fsm_mem_free(temp_free->RlcRequestparams);
		list_del_init(&(temp_free->list));
		if(temp_free !=NULL)
			fsm_mem_free(temp_free);
	}
	fsm_mem_free(lcbj_lessthan_zero);
	//Empty_MACBuffer_Rlc();//������Դ�����MacBufferStatus
	
	Empty_MACBuffer_Rlc(enb_buffer_rlc);
	
	FRET(report_array);
}






/***********************��Դ����**************************/
/***list_head  *enb_buffer_rlcΪĳ���û���BUFFER�׵�ַ����enb_buffer_rlc=SV(Enb_MacBuffer_RLC[index])*********/
/***************tb_sizeΪÿ���û� ����Դ***********************/
/*****enb_logicalChannel_configΪĳ���û����߼��ŵ����ã�����֮ǰ��Ҫ����	RNTI�ҳ����û�ƥ����߼��ŵ�����******/
/******buffer_len:��int Rlc_Request_Num[USERNUMMAX]��ȡֵ����Ӧenb_buffer_rlc�ĵڼ����û���������******/
/*******���������rlc_report_num�ǵ�ǰ�û���report�����ȣ��������������Ⱥ���Ҫ�ͷ��ڴ�******/
/*****�������:RLC_Request *�ǵ�ǰ�û�report�������׵�ַ���������������ú���Ҫ�ͷ��ڴ�****/
/*****�ú���ֻ�ܵõ�һ���û���report�׵�ַ�ʹ�С�����Ҫ���������û����յ�
report ����Ҫ�������û���report��װ������rlc_report_num��������������report����ǰ��****/
RLC_Request * DoResourceAllocation(int tb_size,struct list_head *enb_buffer_rlc,struct  list_head * enb_logicalChannel_config,struct  list_head *enb_logicalChannel_bj,int buffer_len,int *rlc_report_num)//��Դ����
{
	//int num;
	RLC_Request *rlc_temp=NULL;
	RLC_Request *UEmac_Rlc_Report=NULL;
    FIN( DoResourceAllocation(int tb_size,struct list_head *enb_buffer_rlc,struct  list_head * enb_logicalChannel_config,struct  list_head *enb_logicalChannel_bj,int buffer_len,int *rlc_report_num));
    SV_PTR_GET(mac_sv);	
	UEmac_Rlc_Report=ResourceAllocation_Algorithm(tb_size,enb_buffer_rlc,enb_logicalChannel_config,enb_logicalChannel_bj,rlc_report_num,buffer_len);
	//SV(DATA_WAIT_ALLOCATION)=false;  
	FRET(UEmac_Rlc_Report);
}
/*******ENB����Դ�����㷨������Ͱ,RlcBufferRequest MACReportToRlc****************/
/***list_head  *enb_buffer_rlcΪĳ���û���BUFFER�׵�ַ����enb_buffer_rlc=SV(Enb_MacBuffer_RLC[index])*********/
/*RLC_Request * ResourceAllocation_Algorithm(int resource_len,struct list_head *enb_buffer_rlc,struct list_head * enb_logicalChannel_config,struct  list_head *enb_logicalChannel_bj,int *num,int buffer_len)//num�����ָ��report�����С
{
    RLC_Request *report_array;
    //int *report_num;
    MacBufferStatus *lcbj_lessthan_zero;
    MacBufferStatus *temp_lessthan_zero;
    FIN(ResourceAllocation_Algorithm(int msg,struct list_head *enb_buffer_rlc,struct list_head * enb_logicalChannel_config,struct  list_head *enb_logicalChannel_bj,int *num,int index));
    SV_PTR_GET(mac_sv);
    MacBufferStatus *priority_mac_buffer=NULL,*temp_mac_buffer=NULL,*temp_free=NULL;
    RlcBufferRequest *mac_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest)),*temp_rlc_report=NULL;
    lcbj_lessthan_zero=(MacBufferStatus *)fsm_mem_alloc(sizeof(MacBufferStatus));
    INIT_LIST_HEAD(&(lcbj_lessthan_zero->list));
    while(mac_rlc_report==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
    {
    	mac_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
    }
    INIT_LIST_HEAD(&(mac_rlc_report->list));
    LogicalChannelBj *temp_logicalchannel_bj=NULL;
    int temp_buffer_lcid;
    int *res_length=resource_len;
    int statuslength=0,retxlength=0,txlength=0;
    struct list_head *pos=NULL,*p=NULL;
    priority_mac_buffer=PrioritySort(enb_logicalChannel_config,enb_buffer_rlc);
    list_for_each_entry(temp_mac_buffer, &(priority_mac_buffer->list),list)//����
    {
        temp_buffer_lcid=temp_mac_buffer->lcid;
	if(res_length<=0)//��ǰ��Դ�Ѿ�������
		break;
		temp_logicalchannel_bj=NULL;
        list_for_each_entry(temp_logicalchannel_bj, enb_logicalChannel_bj,list)//����
        {
            if(temp_buffer_lcid==(temp_logicalchannel_bj->lcid))
            {
               // printk(KERN_INFO"lcid:%d  lcbj:%d\n",temp_buffer_lcid,temp_logicalchannel_bj->lcbj);

            	if((temp_logicalchannel_bj->lcbj)==(MAX_BJ/8+1))//�ѵ�ǰ���е�ʣ����Դ�ָ����߼��ŵ�
            	{
            	    //printk(KERN_INFO"res_length:%d\n",res_length);

                    statuslength=(temp_mac_buffer->RlcRequestparams->statusPduSize)+(temp_mac_buffer->RlcRequestparams->statusPduHeader);
                    retxlength=(temp_mac_buffer->RlcRequestparams->retxQueueSize)+(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
                    txlength=(temp_mac_buffer->RlcRequestparams->txQueueSize)+(temp_mac_buffer->RlcRequestparams->txQueueHeader);
                    if(statuslength>0 || retxlength>0 ||txlength>0)
                    {
                        if(res_length>=(statuslength+retxlength+txlength))//TBSize����������
                        {
                            temp_rlc_report=Mac_RlcRequest_copy(temp_mac_buffer->RlcRequestparams);
				temp_rlc_report->statusPduSize=temp_rlc_report->statusPduSize+res_length-(statuslength+retxlength+txlength);//�Ѷ����Դ��statusPduSize
                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                            res_length=0;//ʣ����ԴΪ0
                            //temp_logicalchannel_bj->lcbj-=(statuslength+retxlength+txlength);
                            break;
                        }
                        else if(res_length>=statuslength)//�ȷ�״̬PDU
                        {
                            temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
				while(temp_rlc_report==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
				{
					temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
				}
                            INIT_LIST_HEAD(&(temp_rlc_report->list));
                            temp_rlc_report->lcid=temp_mac_buffer->RlcRequestparams->lcid;
                            temp_rlc_report->rnti=temp_mac_buffer->RlcRequestparams->rnti;
                            temp_rlc_report->statusPduHeader=temp_mac_buffer->RlcRequestparams->statusPduHeader;
                            temp_rlc_report->statusPduSize=temp_mac_buffer->RlcRequestparams->statusPduSize;
                            res_length=res_length-statuslength;
                            //temp_logicalchannel_bj->lcbj-=statuslength;
                            temp_mac_buffer->RlcRequestparams->statusPduHeader=0;
                            temp_mac_buffer->RlcRequestparams->statusPduSize=0;
                            if(res_length >= retxlength)
                            {
                                temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
                                temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
                                res_length=res_length-retxlength;
                                //temp_logicalchannel_bj->lcbj-=retxlength;
                                temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
                                temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
                                if(res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//����ͷ��
                                {
                                    temp_rlc_report->txQueueHeader=temp_mac_buffer->RlcRequestparams->txQueueHeader;
                                    res_length=res_length-(temp_mac_buffer->RlcRequestparams->txQueueHeader);
                                    temp_rlc_report->txQueueSize=res_length;
                                   // temp_logicalchannel_bj->lcbj-=(temp_mac_buffer->RlcRequestparams->txQueueHeader+temp_rlc_report->txQueueSize);
                                    temp_mac_buffer->RlcRequestparams->txQueueHeader=0;
                                    temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
                                    list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                    res_length=0;
                                    break;
                                }
                                else if(res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//С��ͷ��
                                {
                                    if(res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//С��ͷ����������
                                    {
                                        temp_rlc_report->txQueueSize=temp_mac_buffer->RlcRequestparams->txQueueSize;
                                        temp_rlc_report->txQueueHeader=res_length-(temp_mac_buffer->RlcRequestparams->txQueueSize);

                                       // temp_logicalchannel_bj->lcbj-=res_length;
                                        temp_mac_buffer->RlcRequestparams->txQueueHeader-=temp_rlc_report->txQueueHeader;
                                        temp_mac_buffer->RlcRequestparams->txQueueSize=0;
                                        res_length=0;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        break;
                                    }
                                    else//С��ͷ��С������
                                    {
                                        temp_rlc_report->txQueueSize=res_length;
                                        temp_rlc_report->txQueueHeader=0;
                                        //temp_logicalchannel_bj->lcbj-=res_length;
                                        temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
                                        res_length=0;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        break;
                                    }

                                }
                            }
                            else if(res_length < retxlength)
                            {
                                if(res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//����ͷ��
                                {
                                   // temp_logicalchannel_bj->lcbj-=res_length;
                                    temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
                                    res_length=res_length-(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
                                    temp_rlc_report->retxQueueSize=res_length;
                                    temp_rlc_report->txQueueHeader=0;
                                    temp_rlc_report->txQueueSize=0;
                                    temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
                                    temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
                                    list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                    res_length=0;
                                    break;
                                }
                                else if(res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//С���ش�ͷ��
                                {
                                    if(res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//С��ͷ����������
                                    {
                                        temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
                                        temp_rlc_report->retxQueueHeader=res_length-(temp_mac_buffer->RlcRequestparams->retxQueueSize);

                                        //temp_logicalchannel_bj->lcbj-=res_length;
                                        temp_mac_buffer->RlcRequestparams->retxQueueHeader-=temp_rlc_report->retxQueueHeader;
                                        temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
                                        temp_rlc_report->txQueueHeader=0;
                                        temp_rlc_report->txQueueSize=0;
                                        res_length=0;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        break;
                                    }
                                    else//С��ͷ��С������
                                    {
                                        temp_rlc_report->retxQueueSize=res_length;
                                        temp_rlc_report->retxQueueHeader=0;
                                        temp_rlc_report->txQueueHeader=0;
                                        temp_rlc_report->txQueueSize=0;
                                        //temp_logicalchannel_bj->lcbj-=res_length;
                                        temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
                                        res_length=0;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        break;
                                    }
                                }
                            }
                        }
                        else if(res_length <statuslength)//С��״̬PDU
                        {
                            temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
				while(temp_rlc_report==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
				{
					temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
				}
                            INIT_LIST_HEAD(&(temp_rlc_report->list));
                            temp_rlc_report->lcid=temp_mac_buffer->RlcRequestparams->lcid;
                            temp_rlc_report->rnti=temp_mac_buffer->RlcRequestparams->rnti;
                            temp_rlc_report->statusPduHeader=0;
                            temp_rlc_report->statusPduSize=0;
                            if(res_length >= retxlength)
                            {
                                temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
                                temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
                                res_length=res_length-retxlength;
                                //temp_logicalchannel_bj->lcbj-=retxlength;
                                temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
                                temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
                                if(res_length>=txlength)
                                {
                                    temp_rlc_report->txQueueHeader=temp_mac_buffer->RlcRequestparams->txQueueHeader;
                                    temp_rlc_report->txQueueSize=temp_mac_buffer->RlcRequestparams->txQueueSize;
                                   // temp_logicalchannel_bj->lcbj-=txlength;
                                    temp_mac_buffer->RlcRequestparams->txQueueHeader=0;
                                    temp_mac_buffer->RlcRequestparams->txQueueSize=0;
                                    list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                    res_length-=txlength;
                                    break;
                                }
                                else
                                {
                                    if(res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//����ͷ��
                                    {
                                        temp_rlc_report->txQueueHeader=temp_mac_buffer->RlcRequestparams->txQueueHeader;
                                        res_length=res_length-(temp_mac_buffer->RlcRequestparams->txQueueHeader);
                                        temp_rlc_report->txQueueSize=res_length;
                                        //temp_logicalchannel_bj->lcbj-=(temp_mac_buffer->RlcRequestparams->txQueueHeader+temp_rlc_report->txQueueSize);
                                        temp_mac_buffer->RlcRequestparams->txQueueHeader=0;
                                        temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        res_length=0;
                                        break;
                                    }
                                    else if(res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//С��ͷ��
                                    {
                                        if(res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//С��ͷ����������
                                        {
                                            temp_rlc_report->txQueueSize=temp_mac_buffer->RlcRequestparams->txQueueSize;
                                            temp_rlc_report->txQueueHeader=res_length-(temp_mac_buffer->RlcRequestparams->txQueueSize);

                                            //temp_logicalchannel_bj->lcbj-=res_length;
                                            temp_mac_buffer->RlcRequestparams->txQueueHeader-=temp_rlc_report->txQueueHeader;
                                            temp_mac_buffer->RlcRequestparams->txQueueSize=0;
                                            res_length=0;
                                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                            break;
                                        }
                                        else//С��ͷ��С������
                                        {
                                            temp_rlc_report->txQueueSize=res_length;
                                            temp_rlc_report->txQueueHeader=0;
                                            //temp_logicalchannel_bj->lcbj-=res_length;
                                            temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
                                            res_length=0;
                                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                            break;
                                        }
                                    }
                                }
                            }
                            else if(res_length < retxlength)
                            {
                                if(res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//����ͷ��
                                {
                                    //temp_logicalchannel_bj->lcbj-=res_length;
                                    temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
                                    res_length=res_length-(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
                                    temp_rlc_report->retxQueueSize=res_length;
                                    temp_rlc_report->txQueueHeader=0;
                                    temp_rlc_report->txQueueSize=0;
                                    temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
                                    temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
                                    list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                    res_length=0;
                                    break;
                                }
                                else if(res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//С���ش�ͷ��
                                {
                                    if(res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//С��ͷ����������
                                    {
                                        temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
                                        temp_rlc_report->retxQueueHeader=res_length-(temp_mac_buffer->RlcRequestparams->retxQueueSize);

                                        //temp_logicalchannel_bj->lcbj-=res_length;
                                        temp_mac_buffer->RlcRequestparams->retxQueueHeader-=temp_rlc_report->retxQueueHeader;
                                        temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
                                        temp_rlc_report->txQueueHeader=0;
                                        temp_rlc_report->txQueueSize=0;
                                        res_length=0;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        break;
                                    }
                                    else//С��ͷ��С������
                                    {
                                        temp_rlc_report->retxQueueSize=res_length;
                                        temp_rlc_report->retxQueueHeader=0;
                                        temp_rlc_report->txQueueHeader=0;
                                        temp_rlc_report->txQueueSize=0;
                                        //temp_logicalchannel_bj->lcbj-=res_length;
                                        temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
                                        res_length=0;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
               else if((temp_logicalchannel_bj->lcbj)>=0)
                {
                    statuslength=(temp_mac_buffer->RlcRequestparams->statusPduSize)+(temp_mac_buffer->RlcRequestparams->statusPduHeader);
                    retxlength=(temp_mac_buffer->RlcRequestparams->retxQueueSize)+(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
                    txlength=(temp_mac_buffer->RlcRequestparams->txQueueSize)+(temp_mac_buffer->RlcRequestparams->txQueueHeader);
                    if(statuslength>0 || retxlength>0 ||txlength>0)
                    {
                        if(res_length>=(statuslength+retxlength+txlength))//TBSize����������
                        {
                            temp_rlc_report=Mac_RlcRequest_copy(temp_mac_buffer->RlcRequestparams);
                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                            res_length=res_length-(statuslength+retxlength+txlength);
                            temp_logicalchannel_bj->lcbj-=(statuslength+retxlength+txlength);
                            break;
                        }
                        else if(res_length>=statuslength)//�ȷ�״̬PDU
                        {
                            temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
				while(temp_rlc_report==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
				{
					temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
				}
                            INIT_LIST_HEAD(&(temp_rlc_report->list));
                            temp_rlc_report->lcid=temp_mac_buffer->RlcRequestparams->lcid;
                            temp_rlc_report->rnti=temp_mac_buffer->RlcRequestparams->rnti;
                            temp_rlc_report->statusPduHeader=temp_mac_buffer->RlcRequestparams->statusPduHeader;
                            temp_rlc_report->statusPduSize=temp_mac_buffer->RlcRequestparams->statusPduSize;
                            res_length=res_length-statuslength;
                            temp_logicalchannel_bj->lcbj-=statuslength;
                            temp_mac_buffer->RlcRequestparams->statusPduHeader=0;
                            temp_mac_buffer->RlcRequestparams->statusPduSize=0;
                            if(res_length >= retxlength)
                            {
                                temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
                                temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
                                res_length=res_length-retxlength;
                                temp_logicalchannel_bj->lcbj-=retxlength;
                                temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
                                temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
                                if(res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//����ͷ��
                                {
                                    temp_rlc_report->txQueueHeader=temp_mac_buffer->RlcRequestparams->txQueueHeader;
                                    res_length=res_length-(temp_mac_buffer->RlcRequestparams->txQueueHeader);
                                    temp_rlc_report->txQueueSize=res_length;
                                    temp_logicalchannel_bj->lcbj-=(temp_mac_buffer->RlcRequestparams->txQueueHeader+temp_rlc_report->txQueueSize);
                                    temp_mac_buffer->RlcRequestparams->txQueueHeader=0;
                                    temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
                                    list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                    res_length=0;
                                    break;
                                }
                                else if(res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//С��ͷ��
                                {
                                    if(res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//С��ͷ����������
                                    {
                                        temp_rlc_report->txQueueSize=temp_mac_buffer->RlcRequestparams->txQueueSize;
                                        temp_rlc_report->txQueueHeader=res_length-(temp_mac_buffer->RlcRequestparams->txQueueSize);

                                        temp_logicalchannel_bj->lcbj-=res_length;
                                        temp_mac_buffer->RlcRequestparams->txQueueHeader-=temp_rlc_report->txQueueHeader;
                                        temp_mac_buffer->RlcRequestparams->txQueueSize=0;
                                        res_length=0;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        break;
                                    }
                                    else//С��ͷ��С������
                                    {
                                        temp_rlc_report->txQueueSize=res_length;
                                        temp_rlc_report->txQueueHeader=0;
                                        temp_logicalchannel_bj->lcbj-=res_length;
                                        temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
                                        res_length=0;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        break;
                                    }

                                }
                            }
                            else if(res_length < retxlength)
                            {
                                if(res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//����ͷ��
                                {
                                    temp_logicalchannel_bj->lcbj-=res_length;
                                    temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
                                    res_length=res_length-(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
                                    temp_rlc_report->retxQueueSize=res_length;
                                    temp_rlc_report->txQueueHeader=0;
                                    temp_rlc_report->txQueueSize=0;
                                    temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
                                    temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
                                    list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                    res_length=0;
                                    break;
                                }
                                else if(res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//С���ش�ͷ��
                                {
                                    if(res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//С��ͷ����������
                                    {
                                        temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
                                        temp_rlc_report->retxQueueHeader=res_length-(temp_mac_buffer->RlcRequestparams->retxQueueSize);

                                        temp_logicalchannel_bj->lcbj-=res_length;
                                        temp_mac_buffer->RlcRequestparams->retxQueueHeader-=temp_rlc_report->retxQueueHeader;
                                        temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
                                        temp_rlc_report->txQueueHeader=0;
                                        temp_rlc_report->txQueueSize=0;
                                        res_length=0;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        break;
                                    }
                                    else//С��ͷ��С������
                                    {
                                        temp_rlc_report->retxQueueSize=res_length;
                                        temp_rlc_report->retxQueueHeader=0;
                                        temp_rlc_report->txQueueHeader=0;
                                        temp_rlc_report->txQueueSize=0;
                                        temp_logicalchannel_bj->lcbj-=res_length;
                                        temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
                                        res_length=0;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        break;
                                    }
                                }
                            }
                        }
                        else if(res_length <statuslength)//С��״̬PDU
                        {
                            temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
				while(temp_rlc_report==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
				{
					temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
				}
                            INIT_LIST_HEAD(&(temp_rlc_report->list));
                            temp_rlc_report->lcid=temp_mac_buffer->RlcRequestparams->lcid;
                            temp_rlc_report->rnti=temp_mac_buffer->RlcRequestparams->rnti;
                            temp_rlc_report->statusPduHeader=0;
                            temp_rlc_report->statusPduSize=0;
                            if(res_length >= retxlength)
                            {
                                temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
                                temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
                                res_length=res_length-retxlength;
                                temp_logicalchannel_bj->lcbj-=retxlength;
                                temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
                                temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
                                if(res_length>=txlength)
                                {
                                    temp_rlc_report->txQueueHeader=temp_mac_buffer->RlcRequestparams->txQueueHeader;
                                    temp_rlc_report->txQueueSize=temp_mac_buffer->RlcRequestparams->txQueueSize;
                                    temp_logicalchannel_bj->lcbj-=txlength;
                                    temp_mac_buffer->RlcRequestparams->txQueueHeader=0;
                                    temp_mac_buffer->RlcRequestparams->txQueueSize=0;
                                    list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                    res_length-=txlength;
                                    break;
                                }
                                else
                                {
                                    if(res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//����ͷ��
                                    {
                                        temp_rlc_report->txQueueHeader=temp_mac_buffer->RlcRequestparams->txQueueHeader;
                                        res_length=res_length-(temp_mac_buffer->RlcRequestparams->txQueueHeader);
                                        temp_rlc_report->txQueueSize=res_length;
                                        temp_logicalchannel_bj->lcbj-=(temp_mac_buffer->RlcRequestparams->txQueueHeader+temp_rlc_report->txQueueSize);
                                        temp_mac_buffer->RlcRequestparams->txQueueHeader=0;
                                        temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        res_length=0;
                                        break;
                                    }
                                    else if(res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//С��ͷ��
                                    {
                                        if(res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//С��ͷ����������
                                        {
                                            temp_rlc_report->txQueueSize=temp_mac_buffer->RlcRequestparams->txQueueSize;
                                            temp_rlc_report->txQueueHeader=res_length-(temp_mac_buffer->RlcRequestparams->txQueueSize);

                                            temp_logicalchannel_bj->lcbj-=res_length;
                                            temp_mac_buffer->RlcRequestparams->txQueueHeader-=temp_rlc_report->txQueueHeader;
                                            temp_mac_buffer->RlcRequestparams->txQueueSize=0;
                                            res_length=0;
                                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                            break;
                                        }
                                        else//С��ͷ��С������
                                        {
                                            temp_rlc_report->txQueueSize=res_length;
                                            temp_rlc_report->txQueueHeader=0;
                                            temp_logicalchannel_bj->lcbj-=res_length;
                                            temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
                                            res_length=0;
                                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                            break;
                                        }
                                    }
                                }
                            }
                            else if(res_length < retxlength)
                            {
                                if(res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//����ͷ��
                                {
                                    temp_logicalchannel_bj->lcbj-=res_length;
                                    temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
                                    res_length=res_length-(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
                                    temp_rlc_report->retxQueueSize=res_length;
                                    temp_rlc_report->txQueueHeader=0;
                                    temp_rlc_report->txQueueSize=0;
                                    temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
                                    temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
                                    list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                    res_length=0;
                                    break;
                                }
                                else if(res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//С���ش�ͷ��
                                {
                                    if(res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//С��ͷ����������
                                    {
                                        temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
                                        temp_rlc_report->retxQueueHeader=res_length-(temp_mac_buffer->RlcRequestparams->retxQueueSize);

                                        temp_logicalchannel_bj->lcbj-=res_length;
                                        temp_mac_buffer->RlcRequestparams->retxQueueHeader-=temp_rlc_report->retxQueueHeader;
                                        temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
                                        temp_rlc_report->txQueueHeader=0;
                                        temp_rlc_report->txQueueSize=0;
                                        res_length=0;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        break;
                                    }
                                    else//С��ͷ��С������
                                    {
                                        temp_rlc_report->retxQueueSize=res_length;
                                        temp_rlc_report->retxQueueHeader=0;
                                        temp_rlc_report->txQueueHeader=0;
                                        temp_rlc_report->txQueueSize=0;
                                        temp_logicalchannel_bj->lcbj-=res_length;
                                        temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
                                        res_length=0;
                                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
	         else if((temp_logicalchannel_bj->lcbj)<0)
	        {
	        	temp_lessthan_zero=(MacBufferStatus *)fsm_mem_alloc(sizeof(MacBufferStatus));
			fsm_mem_cpy(temp_lessthan_zero,temp_mac_buffer,sizeof(MacBufferStatus));
		 	list_add_tail(&(temp_lessthan_zero->list), &(lcbj_lessthan_zero->list));
	        }
                break;
            }
        }
    }
   if(res_length>0)
   {
    	temp_mac_buffer=NULL;
	list_for_each_entry(temp_mac_buffer, &(lcbj_lessthan_zero->list),list)//����
	{
	        statuslength=(temp_mac_buffer->RlcRequestparams->statusPduSize)+(temp_mac_buffer->RlcRequestparams->statusPduHeader);
	        retxlength=(temp_mac_buffer->RlcRequestparams->retxQueueSize)+(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
	        txlength=(temp_mac_buffer->RlcRequestparams->txQueueSize)+(temp_mac_buffer->RlcRequestparams->txQueueHeader);
	        if(statuslength>0 || retxlength>0 ||txlength>0)
	        {
	            if(res_length>=(statuslength+retxlength+txlength))//TBSize����������
	            {
	                temp_rlc_report=Mac_RlcRequest_copy(temp_mac_buffer->RlcRequestparams);
	                list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                res_length=res_length-(statuslength+retxlength+txlength);
	                temp_logicalchannel_bj->lcbj-=(statuslength+retxlength+txlength);
	                break;
	            }
	            else if(res_length>=statuslength)//�ȷ�״̬PDU
	            {
	                temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
			while(temp_rlc_report==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
			{
				temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
			}
	                INIT_LIST_HEAD(&(temp_rlc_report->list));
	                temp_rlc_report->lcid=temp_mac_buffer->RlcRequestparams->lcid;
	                temp_rlc_report->rnti=temp_mac_buffer->RlcRequestparams->rnti;
	                temp_rlc_report->statusPduHeader=temp_mac_buffer->RlcRequestparams->statusPduHeader;
	                temp_rlc_report->statusPduSize=temp_mac_buffer->RlcRequestparams->statusPduSize;
	                res_length=res_length-statuslength;
	                temp_logicalchannel_bj->lcbj-=statuslength;
	                temp_mac_buffer->RlcRequestparams->statusPduHeader=0;
	                temp_mac_buffer->RlcRequestparams->statusPduSize=0;
	                if(res_length >= retxlength)
	                {
	                    temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
	                    temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
	                    res_length=res_length-retxlength;
	                    temp_logicalchannel_bj->lcbj-=retxlength;
	                    temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
	                    temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
	                    if(res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//����ͷ��
	                    {
	                        temp_rlc_report->txQueueHeader=temp_mac_buffer->RlcRequestparams->txQueueHeader;
	                        res_length=res_length-(temp_mac_buffer->RlcRequestparams->txQueueHeader);
	                        temp_rlc_report->txQueueSize=res_length;
	                        temp_logicalchannel_bj->lcbj-=(temp_mac_buffer->RlcRequestparams->txQueueHeader+temp_rlc_report->txQueueSize);
	                        temp_mac_buffer->RlcRequestparams->txQueueHeader=0;
	                        temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
	                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                        res_length=0;
	                        break;
	                    }
	                    else if(res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//С��ͷ��
	                    {
	                        if(res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//С��ͷ����������
	                        {
	                            temp_rlc_report->txQueueSize=temp_mac_buffer->RlcRequestparams->txQueueSize;
	                            temp_rlc_report->txQueueHeader=res_length-(temp_mac_buffer->RlcRequestparams->txQueueSize);

	                            temp_logicalchannel_bj->lcbj-=res_length;
	                            temp_mac_buffer->RlcRequestparams->txQueueHeader-=temp_rlc_report->txQueueHeader;
	                            temp_mac_buffer->RlcRequestparams->txQueueSize=0;
	                            res_length=0;
	                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                            break;
	                        }
	                        else//С��ͷ��С������
	                        {
	                            temp_rlc_report->txQueueSize=res_length;
	                            temp_rlc_report->txQueueHeader=0;
	                            temp_logicalchannel_bj->lcbj-=res_length;
	                            temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
	                            res_length=0;
	                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                            break;
	                        }

	                    }
	                }
	                else if(res_length < retxlength)
	                {
	                    if(res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//����ͷ��
	                    {
	                        temp_logicalchannel_bj->lcbj-=res_length;
	                        temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
	                        res_length=res_length-(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
	                        temp_rlc_report->retxQueueSize=res_length;
	                        temp_rlc_report->txQueueHeader=0;
	                        temp_rlc_report->txQueueSize=0;
	                        temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
	                        temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
	                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                        res_length=0;
	                        break;
	                    }
	                    else if(res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//С���ش�ͷ��
	                    {
	                        if(res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//С��ͷ����������
	                        {
	                            temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
	                            temp_rlc_report->retxQueueHeader=res_length-(temp_mac_buffer->RlcRequestparams->retxQueueSize);

	                            temp_logicalchannel_bj->lcbj-=res_length;
	                            temp_mac_buffer->RlcRequestparams->retxQueueHeader-=temp_rlc_report->retxQueueHeader;
	                            temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
	                            temp_rlc_report->txQueueHeader=0;
	                            temp_rlc_report->txQueueSize=0;
	                            res_length=0;
	                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                            break;
	                        }
	                        else//С��ͷ��С������
	                        {
	                            temp_rlc_report->retxQueueSize=res_length;
	                            temp_rlc_report->retxQueueHeader=0;
	                            temp_rlc_report->txQueueHeader=0;
	                            temp_rlc_report->txQueueSize=0;
	                            temp_logicalchannel_bj->lcbj-=res_length;
	                            temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
	                            res_length=0;
	                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                            break;
	                        }
	                    }
	                }
	            }
	            else if(res_length <statuslength)//С��״̬PDU
	            {
	                temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
		while(temp_rlc_report==0)//�����ڴ�ʧ�ܣ��ٴ�����ֱ���ɹ�
		{
			temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
		}
	                INIT_LIST_HEAD(&(temp_rlc_report->list));
	                temp_rlc_report->lcid=temp_mac_buffer->RlcRequestparams->lcid;
	                temp_rlc_report->rnti=temp_mac_buffer->RlcRequestparams->rnti;
	                temp_rlc_report->statusPduHeader=0;
	                temp_rlc_report->statusPduSize=0;
	                if(res_length >= retxlength)
	                {
	                    temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
	                    temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
	                    res_length=res_length-retxlength;
	                    temp_logicalchannel_bj->lcbj-=retxlength;
	                    temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
	                    temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
	                    if(res_length>=txlength)
	                    {
	                        temp_rlc_report->txQueueHeader=temp_mac_buffer->RlcRequestparams->txQueueHeader;
	                        temp_rlc_report->txQueueSize=temp_mac_buffer->RlcRequestparams->txQueueSize;
	                        temp_logicalchannel_bj->lcbj-=txlength;
	                        temp_mac_buffer->RlcRequestparams->txQueueHeader=0;
	                        temp_mac_buffer->RlcRequestparams->txQueueSize=0;
	                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                        res_length-=txlength;
	                        break;
	                    }
	                    else
	                    {
	                        if(res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//����ͷ��
	                        {
	                            temp_rlc_report->txQueueHeader=temp_mac_buffer->RlcRequestparams->txQueueHeader;
	                            res_length=res_length-(temp_mac_buffer->RlcRequestparams->txQueueHeader);
	                            temp_rlc_report->txQueueSize=res_length;
	                            temp_logicalchannel_bj->lcbj-=(temp_mac_buffer->RlcRequestparams->txQueueHeader+temp_rlc_report->txQueueSize);
	                            temp_mac_buffer->RlcRequestparams->txQueueHeader=0;
	                            temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
	                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                            res_length=0;
	                            break;
	                        }
	                        else if(res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//С��ͷ��
	                        {
	                            if(res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//С��ͷ����������
	                            {
	                                temp_rlc_report->txQueueSize=temp_mac_buffer->RlcRequestparams->txQueueSize;
	                                temp_rlc_report->txQueueHeader=res_length-(temp_mac_buffer->RlcRequestparams->txQueueSize);

	                                temp_logicalchannel_bj->lcbj-=res_length;
	                                temp_mac_buffer->RlcRequestparams->txQueueHeader-=temp_rlc_report->txQueueHeader;
	                                temp_mac_buffer->RlcRequestparams->txQueueSize=0;
	                                res_length=0;
	                                list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                                break;
	                            }
	                            else//С��ͷ��С������
	                            {
	                                temp_rlc_report->txQueueSize=res_length;
	                                temp_rlc_report->txQueueHeader=0;
	                                temp_logicalchannel_bj->lcbj-=res_length;
	                                temp_mac_buffer->RlcRequestparams->txQueueSize-=res_length;
	                                res_length=0;
	                                list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                                break;
	                            }
	                        }
	                    }
	                }
	                else if(res_length < retxlength)
	                {
	                    if(res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//����ͷ��
	                    {
	                        temp_logicalchannel_bj->lcbj-=res_length;
	                        temp_rlc_report->retxQueueHeader=temp_mac_buffer->RlcRequestparams->retxQueueHeader;
	                        res_length=res_length-(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
	                        temp_rlc_report->retxQueueSize=res_length;
	                        temp_rlc_report->txQueueHeader=0;
	                        temp_rlc_report->txQueueSize=0;
	                        temp_mac_buffer->RlcRequestparams->retxQueueHeader=0;
	                        temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
	                        list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                        res_length=0;
	                        break;
	                    }
	                    else if(res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//С���ش�ͷ��
	                    {
	                        if(res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//С��ͷ����������
	                        {
	                            temp_rlc_report->retxQueueSize=temp_mac_buffer->RlcRequestparams->retxQueueSize;
	                            temp_rlc_report->retxQueueHeader=res_length-(temp_mac_buffer->RlcRequestparams->retxQueueSize);

	                            temp_logicalchannel_bj->lcbj-=res_length;
	                            temp_mac_buffer->RlcRequestparams->retxQueueHeader-=temp_rlc_report->retxQueueHeader;
	                            temp_mac_buffer->RlcRequestparams->retxQueueSize=0;
	                            temp_rlc_report->txQueueHeader=0;
	                            temp_rlc_report->txQueueSize=0;
	                            res_length=0;
	                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                            break;
	                        }
	                        else//С��ͷ��С������
	                        {
	                            temp_rlc_report->retxQueueSize=res_length;
	                            temp_rlc_report->retxQueueHeader=0;
	                            temp_rlc_report->txQueueHeader=0;
	                            temp_rlc_report->txQueueSize=0;
	                            temp_logicalchannel_bj->lcbj-=res_length;
	                            temp_mac_buffer->RlcRequestparams->retxQueueSize-=res_length;
	                            res_length=0;
	                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                            break;
	                        }
	                    }
	                }
	            }
	        }
	    }	
	
    }	
    report_array=RlcRequest_listtoarray(mac_rlc_report,buffer_len,num);//report_array��һ���û���report�׵�ַ��num�Ǹ��û���report ����ĸ���
    //num=report_num;
    pos=NULL,p=NULL;
    list_for_each_safe(pos,p,&(priority_mac_buffer->list))//����
    {
        temp_free=list_entry(pos,MacBufferStatus,list);
	fsm_mem_free(temp_free->RlcRequestparams);
        list_del_init(&(temp_free->list));
        fsm_mem_free(temp_free);
    }
     pos=NULL,p=NULL;
    list_for_each_safe(pos,p,&(lcbj_lessthan_zero->list))//����
    {
        temp_free=list_entry(pos,MacBufferStatus,list);
	fsm_mem_free(temp_free->RlcRequestparams);
        list_del_init(&(temp_free->list));
        fsm_mem_free(temp_free);
    }
    Empty_MACBuffer_Rlc(enb_buffer_rlc);//������Դ�����MacBufferStatus
    FRET(report_array);
}
*/

/*****************ɾ��lcid��Ӧ���߼��ŵ�����,Ҳɾ�����߼��ŵ���BJ***************/
/*******����Ϊһ���û���rnti����Ҫɾ����lcid*****/
void Delete_LogicalChannel_ConfigInfo(int unsigned short rnti,unsigned char lcid_delete)
{
    int i;
    LogicalChannelConfigInfo *temp_free=NULL;
    LogicalChannelBj *temp=NULL;
    struct list_head *pos=NULL,*p=NULL;
    FIN(Delete_LogicalChannel_ConfigInfo(int unsigned short rnti,unsigned char lcid_delete));
    SV_PTR_GET(mac_sv);
    for(i=0;i<USERNUMMAX;i++)
    {
    	pos=NULL,p=NULL;
    	  list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))//����RNTI��Ӧ���û�
    	  {
    	  	temp_free=list_entry(pos,LogicalChannelConfigInfo,list);
    	  	if(rnti==temp_free->rnti)//�ҵ����û�
    	  	{
    	  		pos=NULL,p=NULL;
    	  		 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))
		    	 {
		    	  	temp_free=list_entry(pos,LogicalChannelConfigInfo,list);
				if(temp_free->lcid==lcid_delete)//�ҵ�Ҫɾ�����߼��ŵ�
			        {
			            list_del_init(&(temp_free->list));//delete a node of LogicalChannel_Config
			            fsm_mem_free(temp_free);
			        }
    	  		 }
			pos=NULL,p=NULL;
		    	list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Bj[i]))//BJ��Enb_LogicalChannel_Config��һһ��Ӧ��
		    	{
			        temp=list_entry(pos,LogicalChannelBj,list);
			        if(temp->lcid==lcid_delete)//�ҵ���Ӧ���߼��ŵ�
			        {
			            list_del_init(&(temp->list));//delete a node of LogicalChannel_Bj
			            fsm_mem_free(temp);
			        }
		    	}
    	  	}
		else
			break;//RNTI����Ӧ�����²����û�
    	  }
    }
    FOUT;
}
/********��ո�TTL�����û���RLC��������ĳ��ȣ�Ϊ�´����������Դ**********/
/********��Ҫ�ڻ��������(�����û�)���ȵĺ����е���һ�μ���**********/
void Empty_Rlcrequestnum(void)
{
	FIN(Empty_Rlcrequestnum());
    	SV_PTR_GET(mac_sv);
	fsm_mem_set(SV(Rlc_Request_Num),0,sizeof(int)*USERNUMMAX);
	FOUT;
}

/************���MAC���RLC����Buffer********************/
/***����Ϊһ���û���bufferͷָ��***/
void Empty_MACBuffer_Rlc(struct list_head *enb_buffer_rlc)
{
    FIN(Empty_MACBuffer_Rlc(struct list_head *enb_buffer_rlc));
    SV_PTR_GET(mac_sv);
    struct list_head *pos=NULL,*p=NULL;
    MacBufferStatus *temp_free=NULL;
    list_for_each_safe(pos,p,enb_buffer_rlc)//����
    {
        temp_free=list_entry(pos,MacBufferStatus,list);
	fsm_mem_free(temp_free->RlcRequestparams);
        list_del_init(&(temp_free->list));
        fsm_mem_free(temp_free);
    }
    FOUT;
}
void Empty_LogicalChannelInfo(struct list_head *m_lc_info)
{
    struct list_head *pos=NULL,*p=NULL;
    LogicalChannelConfigInfo *temp_free=NULL;
    FIN(Empty_LogicalChannelInfo(struct list_head *m_lc_info));
    SV_PTR_GET(mac_sv);    
    list_for_each_safe(pos,p,m_lc_info)//����
    {
        temp_free=list_entry(pos,LogicalChannelConfigInfo,list);
        list_del_init(&(temp_free->list));
        fsm_mem_free(temp_free);
    }
    FOUT;
}

void Empty_LogicalChannelBj(struct list_head *m_lcbj_info)
{
    struct list_head *pos=NULL,*p=NULL;
    LogicalChannelBj *temp_free=NULL;
    FIN(Empty_LogicalChannelBj(struct list_head *m_lcbj_info));
    SV_PTR_GET(mac_sv);    
    list_for_each_safe(pos,p,m_lcbj_info)//����
    {
        temp_free=list_entry(pos,LogicalChannelBj,list);
        list_del_init(&(temp_free->list));
        fsm_mem_free(temp_free);
    }
    FOUT;
}

/***********�ͷ�UE MAC SCHEDULER��Դ************/
void Free_Enbmac_Scheduler_Resource(void)
{
    struct list_head *pos,*p;
    MacBufferStatus *temp_rlc_free=NULL;
    LogicalChannelBj *temp_bj_free=NULL;
    LogicalChannelConfigInfo *temp_lcginfo_free=NULL;//�߼��ŵ��� ��
    int i;
    FIN(Free_Enbmac_Scheduler_Resource(void));
    SV_PTR_GET(mac_sv);  
    for(i=0;i<USERNUMMAX;i++)
    {
	    list_for_each_safe(pos,p,SV(Enb_MacBuffer_RLC[i]))//����
	    {
	        temp_rlc_free=list_entry(pos,MacBufferStatus,list);
		 fsm_mem_free(temp_rlc_free->RlcRequestparams);
	        list_del_init(&(temp_rlc_free->list));
	        fsm_mem_free(temp_rlc_free);
	    }
	   
	    pos=NULL;
	    p=NULL;
	    list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Bj[i]))//����
	    {
	        temp_bj_free=list_entry(pos,LogicalChannelBj,list);
	        list_del_init(&(temp_bj_free->list));
	        fsm_mem_free(temp_bj_free);
	    }
		
	    pos=NULL;
	    p=NULL;
	    list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))//����
	    {
	        temp_lcginfo_free=list_entry(pos,LogicalChannelConfigInfo,list);
	        list_del_init(&(temp_lcginfo_free->list));
	        fsm_mem_free(temp_lcginfo_free);
	    }
		
	fsm_mem_free(SV(Enb_MacBuffer_RLC[i]));
	fsm_mem_free(SV(Enb_LogicalChannel_Bj[i]));
	fsm_mem_free(SV(Enb_LogicalChannel_Config[i]));
    }
    FOUT;
}

  












