#include <linux/if_ether.h>
/****lhl¸Ä¶¯20140410****/
#include <linux/list.h>
#include <linux/kernel.h>
#include <stddef.h>
/****lhl¸Ä¶¯½áÊø20140410****/
#include "macfsm.h"
//#include "macpkfmt.h"
//#include "rrc_config.h"




/************************UL schedule LiuHanLi**************************/
/************************³õÊ¼»¯MAC¸÷¸öÈ«¾Ö±äÁ¿²ÎÊý***********************/
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

/*******20140526 ½«RLCµÄÊý×éÇëÇó×ª»»ÎªÁ´±íÇëÇó£¬ÎªÁËÓëÖ®Ç°µÄÉè¼Æ±£³ÖÒ»ÖÂ,Õë¶ÔÒ»¸öÓÃ»§********/
/*****rlc_request_arrayÎªÃ¿¸öÓÃ»§µÄÇëÇóÍ·Ö¸Õë£¬numÊÇ¸ÃÓÃ»§µÄÊý×é½Úµã¸öÊý******/
/*****uesernum:¸ÃrlcÇëÇóÖÐ¶ÔÓ¦µÄµÚuesernum¸öÓÃ»§,´Ó0¿ªÊ¼*****/
RlcBufferRequest * RlcRequest_arraytolist(RLC_Request *rlc_request_array,int num,int uesernum)//numÊÇÇëÇóµÄ³¤¶È
{
	int i;
	RlcBufferRequest *rlcrequest;
	RlcBufferRequest *rlcrequest_temp;
	FIN(RlcRequest_arraytolist(RLC_Request *rlc_request_array,int num,int uesernum));
	SV_PTR_GET(mac_sv);
	rlcrequest=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
	while(rlcrequest==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇë£¬Ö±µ½ÉêÇë³É¹¦
	{
		rlcrequest=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
	}
	INIT_LIST_HEAD(&(rlcrequest->list));
	for(i=0;i<num;i++)
	{
		rlcrequest_temp=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
		while(rlcrequest_temp==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇë£¬Ö±µ½ÉêÇë³É¹¦
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
	SV(Rlc_Request_Num[uesernum])=num;//µ±Ç°ÉêÇë×ÊÔ´µÄµÚindex¸öÓÃ»§µÄÊý×é½Úµã³¤£¬¼´¸ÃÓÃ»§ÓÐÊý¾ÝÒª·¢µÄÂß¼­ÐÅµÀÊý
	FRET(rlcrequest);
}


/*******20140529 ½«RLCµÄÁ´±íÇëÇó×ª»»ÎªÊý×éÇëÇó£¬ÎªÁËÓëÖ®Ç°µÄÉè¼Æ±£³ÖÒ»ÖÂ********/
/*******ÊäÈëRlcBufferRequestÎªRLC reportÁ´±í£¬Êä³ö£º*numÊÇÒª·¢ËÍµÄIOCTLµÄbuffer³¤¶È£¬·µ»ØRLC ±¨¸æµÄÍ·Ö¸Õë***************/
/*******reqnum±íÊ¾¸ÃÓÃ»§¶ÔÓ¦µÄRlc_Request_Num*******/
RLC_Request * RlcRequest_listtoarray( RlcBufferRequest *rlc_request,int reqnum ,int *num)//numÊÇreportµÄ×ÜÊý
{
	struct list_head *pos,*p;
	RlcBufferRequest *temp;
	int i;
	RLC_Request *rlc_report_temp;
	FIN( RlcRequest_listtoarray( RlcBufferRequest *rlc_request,int reqnum ,int *num));
	SV_PTR_GET(mac_sv);
	rlc_report_temp=(RLC_Request *)fsm_mem_alloc(sizeof(RLC_Request)*reqnum);//¶¯Ì¬ÉêÇëreportµÄ×Ü¸öÊý
	while(rlc_report_temp==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
	{
		rlc_report_temp=(RLC_Request *)fsm_mem_alloc(sizeof(RLC_Request)*reqnum);
	}
	pos=NULL,p=NULL,temp=NULL;
	i=0;
	//rlc_report_temp=(RLC_Request *)((int *)rlc_report);//Ö¸ÕëÖ¸ÏòÊý×éµÄÊ×µØÖ·
	list_for_each_safe(pos,p,&(rlc_request->list))//±éÀú
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
    *num=i;//·µ»ØRLC reportµÄ×Ü¸öÊý´óÐ¡
	pos=NULL,p=NULL,temp=NULL;
	list_for_each_safe(pos,p,&(rlc_request->list))//±éÀú
	{
        	temp=list_entry(pos,RlcBufferRequest,list);
        	list_del_init(&(temp->list));
        	fsm_mem_free(temp);//ÊÍ·Å×ÊÔ´
  	}
	FRET(rlc_report_temp);
}



/***************ÓÉRLC²ãµÄbufferÇëÇó£¬¸üÐÂMAC²ãbuffer×´Ì¬±äÁ¿****************/
/*********ÊäÈëRlcBufferRequest* params ÎªÒ»¸öÓÃ»§µÄRLCÇëÇóÁ´±íÍ·Ö¸Õë************/
/***list_head  *enb_buffer_rlcÎªÄ³¸öÓÃ»§µÄBUFFERÊ×µØÖ·£¬Èçenb_buffer_rlc=SV(Enb_MacBuffer_RLC[index])**/
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
	struct list_head *MacBuffer_RLC=enb_buffer_rlc;//Í·Ö¸Õë		
    //SV(DATA_WAIT_ALLOCATION)=true;//ÓÐÊý¾Ý´ý·ÖÅä
	//fsm_printf("[MAC] received rnti = %d\n", params->rnti);
     list_for_each_safe(pos,p,&(RLChead->list))//±éÀú
    {
        temp=list_entry(pos,RlcBufferRequest,list);
        temp_lcid=temp->lcid;
        //length_rlc_request++;
        temp_mac_bufferstatus=NULL;
        list_for_each_entry(temp_mac_bufferstatus, MacBuffer_RLC,list)//±éÀú£¬²éÕÒMACÊÇ·ñÒÑ¾­±£´æÂß¼­ÐÅµÀµÄÊý¾Ý        
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
        if(flag==false)//²éÕÒÊ§°Ü
        {
        	temp_mac_findno=(MacBufferStatus *)fsm_mem_alloc(sizeof(MacBufferStatus));
            while(temp_mac_findno==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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
    list_for_each_safe(pos,p,&(RLChead->list))//±éÀú
    {
        temp=list_entry(pos,RlcBufferRequest,list);
        list_del_init(&(temp->list));
        fsm_mem_free(temp);//ÊÍ·Å×ÊÔ´
    }
    FOUT;
}

/****¸´ÖÆRlcBufferRequest½Úµã£¬Ê¹·µ»Ø½Úµã¿É²åÈëMacBufferStatusÖÐ£¬½â¾önextÎªNULLµÄÎÊÌâ******/
RLC_Request* Rlc_MacRequest_copy(RlcBufferRequest *temp)
{
    FIN(Rlc_MacRequest_copy(RlcBufferRequest *temp));
	RLC_Request *copy=(RLC_Request *)fsm_mem_alloc(sizeof(RLC_Request));
	while(copy==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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
	while(copy==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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

RlcBufferRequest* Mac_RlcRequest_copy(RLC_Request *temp)//¸´ÖÆRlcBufferRequest½Úµã
{
    FIN(Mac_RlcRequest_copy(RLC_Request *temp));
	RlcBufferRequest *copy=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
	while(copy==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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

RLC_Request* Mac_MacRequest_copy(RLC_Request *temp)//¸´ÖÆRlcBufferRequest½Úµã
{
    FIN(Mac_MacRequest_copy(RLC_Request *temp));
	RLC_Request *copy=(RLC_Request *)fsm_mem_alloc(sizeof(RLC_Request));
	while(copy==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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



/********************Ã¿¸öTTI¸üÐÂÂß¼­ÐÅµÀµÄBjÖµ20140526modified ¸ü¸ÄÁËÎÞÇî´óµÄÇé¿ö**********************/
/********ÊäÈëenb_logicalChannel_bj ÎªEnb_LogicalChannel_Bj[i]Í·Ö¸Õë(¶ÔÓ¦Ò»¸öÓÃ»§)£¬ÐèÒªÕë¶ÔÃ¿¸öÓÃ»§ÊäÈë*******/
/******** ÊäÈëlist_head *enb_logicalChannel_config ÎªEnb_LogicalChannel_Config[i]Í·Ö¸Õë£¬ÓëBJÊÇÒ»Ò»¶ÔÓ¦µÄ***********/
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
	list_for_each_entry(temp, head_Bj,list)//±éÀúµ±Ç°ÓÃ»§µÄBJÁ´±í
	{
		temp_Bj_lcid=temp->lcid;
		flag_tail=false;
		temp_Logical_Channel_Config=NULL;
		list_for_each_entry(temp_Logical_Channel_Config, enb_logicalChannel_config,list)//±éÀú¸ÃÓÃ»§µÄÂß¼­ÐÅµÀÊôÐÔ£¬ÕÒµ½¶ÔÓ¦µÄLCIDÅäÖÃ
		 {
		  	if(temp->rnti==temp_Logical_Channel_Config->rnti)//È·±£ÊÇÕë¶Ô¸ÃÓÃ»§µÄ
		  	{
		  		temp_lcc_lcid=temp_Logical_Channel_Config->lcid;
			        if(temp_lcc_lcid==temp_Bj_lcid)
			        {
			            if((temp_Logical_Channel_Config->prioritizedBitRateKbps)==infinity)//ÎÞÇî´óµÄÇé¿ö
			            {
			                temp->lcbj=MAX_BJ/8+1;//´¦ÀíÎª×î´óÖµ¼Ó1
			                flag_tail=true;
			            }
			            else//²»ÊÇÎÞÇî´óÊ±µÄ¸üÐÂ
			            {
				            BucketSize=(temp_Logical_Channel_Config->prioritizedBitRateKbps)*(temp_Logical_Channel_Config->bucketSizeDurationMs)/8;
			                    if(temp->lcbj < BucketSize)
			                       temp->lcbj=temp->lcbj+(temp_Logical_Channel_Config->prioritizedBitRateKbps)*TTI/8;//³ýÒÔ8ÊÇ×ª»»Îªbyte
			                    else
			                        temp->lcbj=BucketSize;
			                    flag_tail=true;
						break;
					}		                	
			        }

		  	}
			else//Âß¼­ÐÅµÀÓëÓÃ»§µÄBJ²»·ûºÏ
			{
				 printk(KERN_INFO"Bj and logical channel ERROR");
				 FOUT;
			}
		}
		if(flag_tail==false)//Ã»ÓÐÕÒµ½ÏëÆ¥ÅäµÄÂß¼­ÐÅµÀ
            		printk(KERN_INFO"FlushBj ERROR");//LogicalChannelConfigºÍLogicalChannelConfigBj²»Æ¥Åä
	}
	FOUT;
}

/**************(¶ÔÃ¿¸öÓÃ»§)*¸ù¾ÝÂß¼­ÐÅµÀÓÅÏÈ¼¶¶ÔÂß¼­ÐÅµÀÅÅÐò***************/
/******ÊäÈëÎªEnb_LogicalChannel_Config[i],ÐèÒªÕë¶ÔÃ¿¸öÓÃ»§×öÊäÈë********/
LogicalChannelConfigInfo* LogicalChannel_ConfigInfo_Rank_Priority(struct list_head * enb_logicalChannel_config)
{

    FIN(LogicalChannel_ConfigInfo_Rank_Priority(struct list_head * enb_logicalChannel_config));
    SV_PTR_GET(mac_sv);
	LogicalChannelConfigInfo *lcc_info_priority=NULL,*temp=NULL,*temp_logicalChannel=NULL;
	lcc_info_priority=(LogicalChannelConfigInfo *)fsm_mem_alloc(sizeof(LogicalChannelConfigInfo ));
	while(lcc_info_priority==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
	{
		lcc_info_priority=(LogicalChannelConfigInfo *)fsm_mem_alloc(sizeof(LogicalChannelConfigInfo ));
	}
	INIT_LIST_HEAD(&(lcc_info_priority->list));
	LogicalChannelConfigInfo *next_node=NULL;
	LogicalChannelConfigInfo *temp_next=NULL;
	bool flag_add=false;
	list_for_each_entry(temp, enb_logicalChannel_config,list)//±éÀú
	{
	    next_node=(LogicalChannelConfigInfo *)fsm_mem_alloc(sizeof(LogicalChannelConfigInfo ));
	    while(next_node==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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
            list_for_each_entry(temp_next, &(lcc_info_priority->list),list)//±éÀú
            {
                if ((next_node->priority) <= (temp_next->priority))
                {
                    list_add_tail(&(next_node->list), &(temp_next->list));//°Ñnext_node¼Óµ½temp_nextµÄÇ°Ãæ
                    flag_add=true;
                    break;
                }
            }
            if(flag_add==false)
                list_add_tail(&(next_node->list), &(lcc_info_priority->list));
        }
    }
	FRET(lcc_info_priority);//·µ»Ø¾ßÓÐÓÅÏÈ¼¶ÅÅ¶ÓµÄLogicalChannelConfigInfoÍ·Ö¸Õë
}

/******¸ù¾ÝÂß¼­ÐÅµÀÓÅÏÈ¼¶Ë³Ðò£¬¶ÔMacBufferStatusÁ´±í°´ÓÅÏÈ¼¶ÅÅÐò********/
/******ÊäÈëÎªEnb_LogicalChannel_Config[i],ÐèÒªÕë¶ÔÃ¿¸öÓÃ»§×öÊäÈë********/
/******ÊäÈëÎªenb_buffer_rlc[i],ÐèÒªÕë¶ÔÃ¿¸öÓÃ»§×öÊäÈë********/
MacBufferStatus* PrioritySort(struct  list_head * enb_logicalChannel_config,struct list_head *enb_buffer_rlc)
{

	MacBufferStatus *PriorityMacBufferStatus,*temp_mbs=NULL,*temp_node;
	LogicalChannelConfigInfo *Priority_logicalChannel=NULL,*temp_logicalChannel=NULL;
	int flag;//±êÖ¾Âß¼­ÐÅµÀÐÅÏ¢ÓëBUFFERÊÇ·ñÆ¥Åä
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
		//while(PriorityMacBufferStatus==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
		//{
			//PriorityMacBufferStatus=(MacBufferStatus *)fsm_mem_alloc(sizeof(MacBufferStatus));
		 //}
		unsigned char temp_Bj_lcid;
	    INIT_LIST_HEAD(&(PriorityMacBufferStatus->list));
		Priority_logicalChannel=LogicalChannel_ConfigInfo_Rank_Priority(enb_logicalChannel_config);
		flag=false;
		list_for_each_entry(temp_logicalChannel, &(Priority_logicalChannel->list),list)//±éÀú
		{
			
			temp_Bj_lcid=temp_logicalChannel->lcid;
			list_for_each_entry(temp_node, enb_buffer_rlc,list)//±éÀú
			{
				//fsm_printf("[mac] temp_Bj_lcid = %d, temp_node->lcid = %d\n", temp_Bj_lcid, temp_node->lcid);
			    if(temp_Bj_lcid==temp_node->lcid)
			    {
			        temp_mbs=(MacBufferStatus *)fsm_mem_alloc(sizeof(MacBufferStatus));
				while(temp_mbs==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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
	list_for_each_safe(pos,p,&(Priority_logicalChannel->list))//±éÀú
    	{
	        temp_logicalChannel=list_entry(pos,LogicalChannelConfigInfo,list);
	        list_del_init(&(temp_logicalChannel->list));//É¾³ý½Úµã
	        fsm_mem_free(temp_logicalChannel);//ÊÍ·Å×ÊÔ´
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
	for(i=0;i<USERNUMMAX;i++)//±éÀúÓÃ»§
	{
		pos=NULL,p=NULL;
		 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))
		{
			temp_lc_config=list_entry(pos,LogicalChannelConfigInfo,list);
			if (m_rnti==temp_lc_config->rnti)//²éÕÒ¾ßÓÐÏàÍ¬RNTIµÄÓÃ»§
			{
				FRET(SV(Enb_LogicalChannel_Config[i]));//·µ»Ø¸ÃÓÃ»§Âß¼­ÐÅµÀÍ·Ö¸Õë
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
	for(i=0;i<USERNUMMAX;i++)//±éÀúÓÃ»§
	{
		pos=NULL,p=NULL;
		 list_for_each_safe(pos,p,SV(Enb_MacBuffer_RLC[i]))
		{
			temp=list_entry(pos,MacBufferStatus,list);
			if (m_rnti==temp->RlcRequestparams->rnti)//²éÕÒ¾ßÓÐÏàÍ¬RNTIµÄÓÃ»§
			{
				FRET(SV(Enb_MacBuffer_RLC[i]));//·µ»Ø¸ÃÓÃ»§Âß¼­ÐÅµÀÍ·Ö¸Õë
			}
			else
				break;
		 }
	}
	printk(KERN_INFO"Get_Enbbuffer_From_Rnti:error\n");
	FRET(NULL);
 }


/************ ¹¦ÄÜ:ÓÉENBÄ³¸öÓÃ»§µÄÇëÇó£¬ÕÒµ½¶ÔÓ¦ÓÃ»§µÄÂß¼­ÐÅµÀÊôÐÔ*************/
/*********ÊäÈëÎªÄ³¸öÓÃ»§µÄÊý¾Ý·¢ËÍÇëÇó*******/
/****Êä³öÎª¸ÃÓÃ»§¶ÔÓ¦µÄÂß¼­ÐÅµÀÊôÐÔÁ´±íÍ·Ö¸Õë******/
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
	if(list_empty(enb_buffer_rlc))//ÊäÈëÓÃ»§µÄbufferÁ´±íÎª¿Õ
	{
		printk(KERN_INFO"Get_LogicalChannelInfo_From_Enbbuffer:input enb_mac buffer error ");
		FRET(NULL);
	}
	else
	{
		for(i=0;i<USERNUMMAX;i++)//±éÀúÓÃ»§
		{
			pos=NULL,p=NULL;
			 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))
			{
				temp_lc_config=list_entry(pos,LogicalChannelConfigInfo,list);
				if (rnti_temp==temp_lc_config->rnti)//²éÕÒ¾ßÓÐÏàÍ¬RNTIµÄÓÃ»§
				{
					FRET(SV(Enb_LogicalChannel_Config[i]));//·µ»Ø¸ÃÓÃ»§Âß¼­ÐÅµÀÍ·Ö¸Õë
				}
				else
					break;
			 }
		}
	}
	printk(KERN_INFO"logical channel and user rnti don't match");
	FRET(NULL);//·µ»Ø¿ÕÖ¸Õë
	
}

 struct list_head * Get_LogicalChannelBj_From_Rnti(unsigned short m_rnti)
 {
 	int i;	
	struct list_head *pos=NULL,*p=NULL;
	LogicalChannelBj *temp_bj;
	MacBufferStatus *temp_rlc;
	FIN(Get_LogicalChannelBj_From_Rnti(unsigned short m_rnti));
	SV_PTR_GET(mac_sv);
	for(i=0;i<USERNUMMAX;i++)//±éÀúÓÃ»§
	{
		pos=NULL,p=NULL;
		 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Bj[i]))
		{
			temp_bj=list_entry(pos,LogicalChannelBj,list);
			if(m_rnti==temp_bj->rnti)//²éÕÒ¾ßÓÐÏàÍ¬RNTIµÄÓÃ»§
			{
				FRET(SV(Enb_LogicalChannel_Bj[i]));//·µ»Ø¸ÃÓÃ»§BJ Í·Ö¸Õë
			}
			else
				break;
		 }
	}
	printk(KERN_INFO"Get_LogicalChannelBj_From_Rnti:error\n");
	FRET(NULL);//·µ»Ø¿ÕÖ¸Õë

 }

/************ ¹¦ÄÜ:ÓÉENBÄ³¸öÓÃ»§µÄÇëÇó£¬ÕÒµ½¶ÔÓ¦ÓÃ»§µÄÂß¼­ÐÅµÀµÄBJ*************/
/*********ÊäÈëÎªÄ³¸öÓÃ»§µÄÊý¾Ý·¢ËÍÇëÇó*******/
/****Êä³öÎª¸ÃÓÃ»§¶ÔÓ¦µÄÂß¼­ÐÅµÀBJ Á´±íÍ·Ö¸Õë******/
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
	if(list_empty(enb_buffer_rlc))//ÊäÈëÓÃ»§µÄbufferÁ´±íÎª¿Õ
	{
		printk(KERN_INFO"Get_LogicalChannelInfo_From_Enbbuffer:input enb_mac buffer error ");
		FRET(NULL);
	}
	else
	{
		for(i=0;i<USERNUMMAX;i++)//±éÀúÓÃ»§
		{
			pos=NULL,p=NULL;
			 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Bj[i]))
			{
				temp_bj=list_entry(pos,LogicalChannelBj,list);
				if(rnti_temp==temp_bj->rnti)//²éÕÒ¾ßÓÐÏàÍ¬RNTIµÄÓÃ»§
				{
					FRET(SV(Enb_LogicalChannel_Bj[i]));//·µ»Ø¸ÃÓÃ»§BJ Í·Ö¸Õë
				}
				else
					break;
			 }
		}
	}
	printk(KERN_INFO"logical channel BJ and user rnti don't match");
	FRET(NULL);//·µ»Ø¿ÕÖ¸Õë	
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
		 if(list_empty( SV(Enb_LogicalChannel_Config[i])))//Á´±íÎª¿Õ
		 {
		 	  temp_add=LogicalChannel_ConfigInfo_copy(lc_info);
		        list_add_tail(&(temp_add->list), SV(Enb_LogicalChannel_Config[i]));//Ìí¼Ó¸ÃÓÃ»§µÄÂß¼­ÐÅµÀÅäÖÃ
		        temp_bj=(LogicalChannelBj *)fsm_mem_alloc(sizeof(LogicalChannelBj));//Í¬Ê±Ìí¼ÓÂß¼­ÐÅµÀBJ
		        while(temp_bj==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
		        {
		            temp_bj=(LogicalChannelBj *)fsm_mem_alloc(sizeof(LogicalChannelBj));
		        }		       
		        INIT_LIST_HEAD(&(temp_bj->list));
		        temp_bj->lcid=lc_info->logicalChannelIdentity;
			temp_bj->rnti=lc_info->rnti;
		        if((temp_add->prioritizedBitRateKbps)==infinity)
//ÎÞÇîµÄ´¦ÀíÎª×î´ó
		            temp_bj->lcbj=MAX_BJ/8+1;
		        else
		            temp_bj->lcbj=0;//ÆäËûÇé¿ö³õÊ¼»¯Îª0
		        list_add_tail(&(temp_bj->list), SV(Enb_LogicalChannel_Bj[i]));//ÒòÎªBJ ºÍÂß¼­ÐÅµÀÊÇÒ»Ò»¶ÔÓ¦µÄ
			//break;
			FOUT;
		 }
		 else//Á´±í·Ç¿Õ
		 {
		 	 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))//±éÀú
			    {
			    	 temp_lc_config=list_entry(pos,LogicalChannelConfigInfo,list);
			    	if(temp_lc_config->rnti==temp_rnti)//ÈôÊÇÕë¶Ô¸ÃÓÃ»§µÄÅäÖÃ
			    	{
			    		pos=NULL,p=NULL;
					flag=false;
			    		 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))//ÖØÐÂ±éÀú£¬Ñ°ÕÒÊÇ·ñÒÑ¾­ÅäÖÃÁË¸ÃÂß¼­ÐÅµÀ£¬ÈçÊÇÔò¸üÐÂ£¬·ñÔòÌí¼Ó½Úµã
			    		 {
			    		 	temp_lc_config=list_entry(pos,LogicalChannelConfigInfo,list);
			    		 	temp_lc_config_lcid=temp_lc_config->lcid;
					        if(temp_lcid==temp_lc_config_lcid)//ÒÑ¾­ÅäÖÃÁË¸ÃÐÅµÀ£¬Ôò¸üÐÂÐÅÏ¢
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
	  				   if(flag==false)//Èç¹ûÃ»ÓÐÅäÖÃ¸ÃÐÅµÀµÄÐÅÏ¢£¬ÔòÌí¼ÓÐÅÏ¢
	  				    {
	  				        temp_add=LogicalChannel_ConfigInfo_copy(lc_info);
	  				        list_add_tail(&(temp_add->list), SV(Enb_LogicalChannel_Config[i]));
	  				        temp_bj=(LogicalChannelBj *)fsm_mem_alloc(sizeof(LogicalChannelBj));
	  				        while(temp_bj==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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
					break;//²»ÊÇÕë¶Ô¸ÃÓÃ»§µÄÅäÖÃ£¬Ìøµ½ÏÂÒ»¸öÓÃ»§
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
->Details:Ê£Óà×ÊÔ´´óÓÚÖØ´«bufferÊ±µÄ·ÖÅä·½°¸
->Input:temp_mac_bufferµ±Ç°Òª·ÖÅä×ÊÔ´µÄÂß¼­ÐÅµÀµÄRLCÇëÇó£¬
->Input:temp_logicalchannel_bj:µ±Ç°Òª´¦ÀíµÄÂß¼­ÐÅµÀµÄÊôÐÔ
->Input:int retxlength:¸ÃÂß¼­ÐÅµÀÇëÇóÖÐÖØ´«PDU³¤¶È
->Input:int txlength¸ÃÂß¼­ÐÅµÀÇëÇóÖÐ´«ÊäPDU³¤¶È
->Output:mac_rlc_report:·´À¡¸øRLCµÄreportÖ¸Õë,
->Output:temp_rlc_report:RLC REPORTµÄÒ»¸ö½Úµã
->Output:*res_lengthÊ£Óà×ÊÔ´³¤¶È
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
		if(*res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//´óÓÚÍ·²¿
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
		else if(*res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//Ð¡ÓÚÍ·²¿
		{
			
			if(*res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
			else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
->Details:Ê£Óà×ÊÔ´Ð¡ÓÚÖØ´«bufferÊ±µÄ·ÖÅä·½°¸
->Input:temp_mac_bufferµ±Ç°Òª·ÖÅä×ÊÔ´µÄÂß¼­ÐÅµÀµÄRLCÇëÇó£¬
->Input:temp_logicalchannel_bj:µ±Ç°Òª´¦ÀíµÄÂß¼­ÐÅµÀµÄÊôÐÔ
->Input:int statuslength:¸ÃÂß¼­ÐÅµÀÇëÇóÖÐ×´Ì¬PDU³¤¶È
->Input:int retxlength:¸ÃÂß¼­ÐÅµÀÇëÇóÖÐÖØ´«PDU³¤¶È
->Input:int txlength¸ÃÂß¼­ÐÅµÀÇëÇóÖÐ´«ÊäPDU³¤¶È
->Output:mac_rlc_report:·´À¡¸øRLCµÄreportÖ¸Õë
->Output:temp_rlc_report:RLC REPORTµÄÒ»¸ö½Úµã 
->Output:*res_lengthÊ£Óà×ÊÔ´³¤¶È
->Special:
*******************************
*/
void leftresource_lessthan_retxbuffer_eachlogicalchannel(RlcBufferRequest *mac_rlc_report,RlcBufferRequest *temp_rlc_report,MacBufferStatus *temp_mac_buffer, LogicalChannelBj *temp_logicalchannel_bj,int retxlength,int txlength,int *res_length)
{
	FIN(leftresource_lessthan_retxbuffer_eachlogicalchannel());
	if(*res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//´óÓÚÍ·²¿
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
	else if(*res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//Ð¡ÓÚÖØ´«Í·²¿
	{
		if(*res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
		else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
->Details:Ê£Óà×ÊÔ´Ð¡ÓÚ×´Ì¬PDUÊ±£¬·ÖÅäÖØ´«PDU
->Input:temp_mac_bufferµ±Ç°Òª·ÖÅä×ÊÔ´µÄÂß¼­ÐÅµÀµÄRLCÇëÇó£¬
->Input:temp_logicalchannel_bj:µ±Ç°Òª´¦ÀíµÄÂß¼­ÐÅµÀµÄÊôÐÔ
->Input:int statuslength:¸ÃÂß¼­ÐÅµÀÇëÇóÖÐ×´Ì¬PDU³¤¶È
->Input:int retxlength:¸ÃÂß¼­ÐÅµÀÇëÇóÖÐÖØ´«PDU³¤¶È
->Input:int txlength¸ÃÂß¼­ÐÅµÀÇëÇóÖÐ´«ÊäPDU³¤¶È
->Output:mac_rlc_report:·´À¡¸øRLCµÄreportÖ¸Õë
->Output:*res_lengthÊ£Óà×ÊÔ´³¤¶È
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
	temp_rlc_report->statusPduSize=0;//²»·Ö×´Ì¬PDU
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
->Details:¶ÔÓÚ×´Ì¬PDU bufferµÄ·ÖÅä
->Input:temp_mac_bufferµ±Ç°Òª·ÖÅä×ÊÔ´µÄÂß¼­ÐÅµÀµÄRLCÇëÇó£¬
->Input:temp_logicalchannel_bj:µ±Ç°Òª´¦ÀíµÄÂß¼­ÐÅµÀµÄÊôÐÔ
->Input:int statuslength:¸ÃÂß¼­ÐÅµÀÇëÇóÖÐ×´Ì¬PDU³¤¶È

->Input:int retxlength:¸ÃÂß¼­ÐÅµÀÇëÇóÖÐÖØ´«PDU³¤¶È
->Input:int txlength¸ÃÂß¼­ÐÅµÀÇëÇóÖÐ´«ÊäPDU³¤¶È
->Output:mac_rlc_report:·´À¡¸øRLCµÄreportÖ¸Õë
->Output:*res_lengthÊ£Óà×ÊÔ´³¤¶È
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
->Details:Ã¿¸öÂß¼­ÐÅµÀµÄ×ÊÔ´·ÖÅä
->Input:temp_mac_bufferµ±Ç°Òª·ÖÅä×ÊÔ´µÄÂß¼­ÐÅµÀµÄRLCÇëÇó£¬
->Input:temp_logicalchannel_bj:µ±Ç°Òª´¦ÀíµÄÂß¼­ÐÅµÀµÄÊôÐÔ
->Input:int statuslength:¸ÃÂß¼­ÐÅµÀÇëÇóÖÐ×´Ì¬PDU³¤¶È
->Input:int retxlength:¸ÃÂß¼­ÐÅµÀÇëÇóÖÐÖØ´«PDU³¤¶È
->Input:int txlength¸ÃÂß¼­ÐÅµÀÇëÇóÖÐ´«ÊäPDU³¤¶È
->Output:mac_rlc_report:·´À¡¸øRLCµÄreportÖ¸Õë£¬
->Special:
*******************************
*/
void ResourceAllocation_foreach_logicalchannel(RlcBufferRequest *mac_rlc_report,MacBufferStatus *temp_mac_buffer, LogicalChannelBj *temp_logicalchannel_bj,int statuslength,int retxlength,int txlength,int *res_length)
{
	FIN(ResourceAllocation_foreach_logicalchannel());
	RlcBufferRequest *temp_rlc_report=NULL;
	
	SV_PTR_GET(mac_sv);	
	if(*res_length>=(statuslength+retxlength+txlength))//TBSize´óÓÚ×ÜÐèÇó
	{
		temp_rlc_report=Mac_RlcRequest_copy(temp_mac_buffer->RlcRequestparams);
		list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
		*res_length=*res_length-(statuslength+retxlength+txlength);
		temp_logicalchannel_bj->lcbj-=(statuslength+retxlength+txlength);	
		// break;
	}
	else if(*res_length>=statuslength)//ÏÈ·Ö×´Ì¬PDU £¬TBSizeÐ¡ÓÚ×ÜÐèÇó£¬µ«´óÓÚ×´Ì¬PDU
	{
		ResourceAllocation_logicalchannel_firststatusbuffer(mac_rlc_report,temp_mac_buffer,temp_logicalchannel_bj,statuslength,retxlength,txlength,res_length);
	}
	else if(*res_length <statuslength)//Ð¡ÓÚ×´Ì¬PDU £¬TBSizeÐ¡ÓÚ×ÜÐèÇó£¬Ð¡ÓÚ×´Ì¬PDU
	{
		ResourceAllocation_logicalchannel_firstretxbuffer(mac_rlc_report,temp_mac_buffer,temp_logicalchannel_bj,retxlength,txlength,res_length);
	}
	FOUT;
}



/*
******************************
->Change Data and time: 20141008
->Function:
->Change:ÎªÁË¼õÉÙº¯Êý¸´ÔÓ¶È£¬Ê¹ÓÃ¶à¸ö×Óº¯Êý
->Details:UE²à×ÊÔ´·ÖÅäËã·¨£ºÁîÅÆÍ°
->Input:msg×ÊÔ´´óÐ¡£¬SV(LogicalChannel_Bj)£¬
->Output:int *num:Ö¸³öreportÊý×é´óÐ¡£¬void *:RLC reportÖ¸Õë
->Special:
*******************************
*/

//void * ResourceAllocation_Algorithm(int resource_len,int *num)//numÊä³ö£¬Ö¸³öreportÊý×é´óÐ¡
RLC_Request * ResourceAllocation_Algorithm(int resource_len,struct list_head *enb_buffer_rlc,struct list_head * enb_logicalChannel_config,struct  list_head *enb_logicalChannel_bj,int *num,int buffer_len)//numÊä³ö£¬Ö¸³öreportÊý×é´óÐ
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
	/*while(mac_rlc_report==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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

	list_for_each_entry(temp_mac_buffer, &(priority_mac_buffer->list),list)//±éÀú
	{
		temp_buffer_lcid=temp_mac_buffer->lcid;
		if(*res_length<=0)//µ±Ç°×ÊÔ´ÒÑ¾­·ÖÅäÍê
			break;
		temp_logicalchannel_bj=NULL;

		list_for_each_entry(temp_logicalchannel_bj,enb_logicalChannel_bj,list)//±éÀú
		{
			if(temp_buffer_lcid==(temp_logicalchannel_bj->lcid))
			{
				// printk(KERN_INFO"lcid:%d  lcbj:%d\n",temp_buffer_lcid,temp_logicalchannel_bj->lcbj);
				statuslength=(temp_mac_buffer->RlcRequestparams->statusPduSize)+(temp_mac_buffer->RlcRequestparams->statusPduHeader);
				retxlength=(temp_mac_buffer->RlcRequestparams->retxQueueSize)+(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
				txlength=(temp_mac_buffer->RlcRequestparams->txQueueSize)+(temp_mac_buffer->RlcRequestparams->txQueueHeader);
				
				if((temp_logicalchannel_bj->lcbj)==(MAX_BJ/8+1) &&(statuslength>0 || retxlength>0 ||txlength>0))//°Ñµ±Ç°ËùÓÐµÄÊ£Óà×ÊÔ´·Ö¸ø¸ÄÂß¼­ÐÅµÀ
				{
					if(*res_length>=(statuslength+retxlength+txlength))//TBSize´óÓÚ×ÜÐèÇó
					{
						temp_rlc_report=Mac_RlcRequest_copy(temp_mac_buffer->RlcRequestparams);
						temp_rlc_report->statusPduSize=temp_rlc_report->statusPduSize+*res_length-(statuslength+retxlength+txlength);//°Ñ¶àµÄ×ÊÔ´¸østatusPduSize
						list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
						*res_length=0;//Ê£Óà×ÊÔ´Îª0
						//temp_logicalchannel_bj->lcbj-=(statuslength+retxlength+txlength);
						break;
					}
					else if(*res_length>=statuslength)//ÏÈ·Ö×´Ì¬PDU
					{
						ResourceAllocation_logicalchannel_firststatusbuffer(mac_rlc_report,temp_mac_buffer,temp_logicalchannel_bj,statuslength,retxlength,txlength,res_length);
						break;
					}
					else if(*res_length <statuslength)//Ð¡ÓÚ×´Ì¬PDU
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
		list_for_each_entry(temp_mac_buffer, &(lcbj_lessthan_zero->list),list)//±éÀú
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
	list_for_each_safe(pos,p,&(priority_mac_buffer->list))//±éÀú
	{
		temp_free=list_entry(pos,MacBufferStatus,list);
		fsm_mem_free(temp_free->RlcRequestparams);
		list_del_init(&(temp_free->list));
		fsm_mem_free(temp_free);
	}
	fsm_mem_free(priority_mac_buffer);

	pos=NULL,p=NULL;
	list_for_each_safe(pos,p,&(lcbj_lessthan_zero->list))//±éÀú
	{
		temp_free=NULL;
		temp_free=list_entry(pos,MacBufferStatus,list);
		fsm_mem_free(temp_free->RlcRequestparams);
		list_del_init(&(temp_free->list));
		if(temp_free !=NULL)
			fsm_mem_free(temp_free);
	}
	fsm_mem_free(lcbj_lessthan_zero);
	//Empty_MACBuffer_Rlc();//·ÖÅä×ÊÔ´ºó£¬Çå¿ÕMacBufferStatus
	
	Empty_MACBuffer_Rlc(enb_buffer_rlc);
	
	FRET(report_array);
}






/***********************×ÊÔ´·ÖÅä**************************/
/***list_head  *enb_buffer_rlcÎªÄ³¸öÓÃ»§µÄBUFFERÊ×µØÖ·£¬Èçenb_buffer_rlc=SV(Enb_MacBuffer_RLC[index])*********/
/***************tb_sizeÎªÃ¿¸öÓÃ»§ µÄ×ÊÔ´***********************/
/*****enb_logicalChannel_configÎªÄ³¸öÓÃ»§µÄÂß¼­ÐÅµÀÅäÖÃ£¬µ÷ÓÃÖ®Ç°ÐèÒª¸ù¾Ý	RNTIÕÒ³öÓëÓÃ»§Æ¥ÅäµÄÂß¼­ÐÅµÀÅäÖÃ******/
/******buffer_len:ÊÇint Rlc_Request_Num[USERNUMMAX]ÖÐÈ¡Öµ£¬¶ÔÓ¦enb_buffer_rlcµÄµÚ¼¸¸öÓÃ»§µÄÁ´±í³¤¶È******/
/*******Êä³ö²ÎÊý£ºrlc_report_numÊÇµ±Ç°ÓÃ»§µÄreportÁ´±í³¤¶È£¬ÓÉÆäËûº¯Êýµ÷¶ÈºóÐèÒªÊÍ·ÅÄÚ´æ******/
/*****Êä³ö²ÎÊý:RLC_Request *ÊÇµ±Ç°ÓÃ»§reportµÄÊý×éÊ×µØÖ·£¬ÓÉÆäËûº¯Êýµ÷ÓÃºóÐèÒªÊÍ·ÅÄÚ´æ****/
/*****¸Ãº¯ÊýÖ»ÄÜµÃµ½Ò»¸öÓÃ»§µÄreportÊ×µØÖ·ºÍ´óÐ¡£¬Èç¹ûÒª·¢ËÍËùÓÐÓÃ»§×îÖÕµÄ
report £¬ÐèÒª½«ËùÓÐÓÃ»§µÄreport×é×°ÆðÀ´ºÍrlc_report_num¼ÓÆðÀ´·ÅÔÚ×îÖÕreportµÄ×îÇ°Ãæ****/
RLC_Request * DoResourceAllocation(int tb_size,struct list_head *enb_buffer_rlc,struct  list_head * enb_logicalChannel_config,struct  list_head *enb_logicalChannel_bj,int buffer_len,int *rlc_report_num)//×ÊÔ´·ÖÅä
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
/*******ENB²à×ÊÔ´·ÖÅäËã·¨£ºÁîÅÆÍ°,RlcBufferRequest MACReportToRlc****************/
/***list_head  *enb_buffer_rlcÎªÄ³¸öÓÃ»§µÄBUFFERÊ×µØÖ·£¬Èçenb_buffer_rlc=SV(Enb_MacBuffer_RLC[index])*********/
/*RLC_Request * ResourceAllocation_Algorithm(int resource_len,struct list_head *enb_buffer_rlc,struct list_head * enb_logicalChannel_config,struct  list_head *enb_logicalChannel_bj,int *num,int buffer_len)//numÊä³ö£¬Ö¸³öreportÊý×é´óÐ¡
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
    while(mac_rlc_report==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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
    list_for_each_entry(temp_mac_buffer, &(priority_mac_buffer->list),list)//±éÀú
    {
        temp_buffer_lcid=temp_mac_buffer->lcid;
	if(res_length<=0)//µ±Ç°×ÊÔ´ÒÑ¾­·ÖÅäÍê
		break;
		temp_logicalchannel_bj=NULL;
        list_for_each_entry(temp_logicalchannel_bj, enb_logicalChannel_bj,list)//±éÀú
        {
            if(temp_buffer_lcid==(temp_logicalchannel_bj->lcid))
            {
               // printk(KERN_INFO"lcid:%d  lcbj:%d\n",temp_buffer_lcid,temp_logicalchannel_bj->lcbj);

            	if((temp_logicalchannel_bj->lcbj)==(MAX_BJ/8+1))//°Ñµ±Ç°ËùÓÐµÄÊ£Óà×ÊÔ´·Ö¸ø¸ÄÂß¼­ÐÅµÀ
            	{
            	    //printk(KERN_INFO"res_length:%d\n",res_length);

                    statuslength=(temp_mac_buffer->RlcRequestparams->statusPduSize)+(temp_mac_buffer->RlcRequestparams->statusPduHeader);
                    retxlength=(temp_mac_buffer->RlcRequestparams->retxQueueSize)+(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
                    txlength=(temp_mac_buffer->RlcRequestparams->txQueueSize)+(temp_mac_buffer->RlcRequestparams->txQueueHeader);
                    if(statuslength>0 || retxlength>0 ||txlength>0)
                    {
                        if(res_length>=(statuslength+retxlength+txlength))//TBSize´óÓÚ×ÜÐèÇó
                        {
                            temp_rlc_report=Mac_RlcRequest_copy(temp_mac_buffer->RlcRequestparams);
				temp_rlc_report->statusPduSize=temp_rlc_report->statusPduSize+res_length-(statuslength+retxlength+txlength);//°Ñ¶àµÄ×ÊÔ´¸østatusPduSize
                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                            res_length=0;//Ê£Óà×ÊÔ´Îª0
                            //temp_logicalchannel_bj->lcbj-=(statuslength+retxlength+txlength);
                            break;
                        }
                        else if(res_length>=statuslength)//ÏÈ·Ö×´Ì¬PDU
                        {
                            temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
				while(temp_rlc_report==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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
                                if(res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//´óÓÚÍ·²¿
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
                                else if(res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//Ð¡ÓÚÍ·²¿
                                {
                                    if(res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
                                    else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
                                if(res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//´óÓÚÍ·²¿
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
                                else if(res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//Ð¡ÓÚÖØ´«Í·²¿
                                {
                                    if(res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
                                    else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
                        else if(res_length <statuslength)//Ð¡ÓÚ×´Ì¬PDU
                        {
                            temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
				while(temp_rlc_report==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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
                                    if(res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//´óÓÚÍ·²¿
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
                                    else if(res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//Ð¡ÓÚÍ·²¿
                                    {
                                        if(res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
                                        else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
                                if(res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//´óÓÚÍ·²¿
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
                                else if(res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//Ð¡ÓÚÖØ´«Í·²¿
                                {
                                    if(res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
                                    else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
                        if(res_length>=(statuslength+retxlength+txlength))//TBSize´óÓÚ×ÜÐèÇó
                        {
                            temp_rlc_report=Mac_RlcRequest_copy(temp_mac_buffer->RlcRequestparams);
                            list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
                            res_length=res_length-(statuslength+retxlength+txlength);
                            temp_logicalchannel_bj->lcbj-=(statuslength+retxlength+txlength);
                            break;
                        }
                        else if(res_length>=statuslength)//ÏÈ·Ö×´Ì¬PDU
                        {
                            temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
				while(temp_rlc_report==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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
                                if(res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//´óÓÚÍ·²¿
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
                                else if(res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//Ð¡ÓÚÍ·²¿
                                {
                                    if(res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
                                    else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
                                if(res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//´óÓÚÍ·²¿
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
                                else if(res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//Ð¡ÓÚÖØ´«Í·²¿
                                {
                                    if(res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
                                    else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
                        else if(res_length <statuslength)//Ð¡ÓÚ×´Ì¬PDU
                        {
                            temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
				while(temp_rlc_report==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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
                                    if(res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//´óÓÚÍ·²¿
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
                                    else if(res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//Ð¡ÓÚÍ·²¿
                                    {
                                        if(res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
                                        else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
                                if(res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//´óÓÚÍ·²¿
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
                                else if(res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//Ð¡ÓÚÖØ´«Í·²¿
                                {
                                    if(res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
                                    else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
	list_for_each_entry(temp_mac_buffer, &(lcbj_lessthan_zero->list),list)//±éÀú
	{
	        statuslength=(temp_mac_buffer->RlcRequestparams->statusPduSize)+(temp_mac_buffer->RlcRequestparams->statusPduHeader);
	        retxlength=(temp_mac_buffer->RlcRequestparams->retxQueueSize)+(temp_mac_buffer->RlcRequestparams->retxQueueHeader);
	        txlength=(temp_mac_buffer->RlcRequestparams->txQueueSize)+(temp_mac_buffer->RlcRequestparams->txQueueHeader);
	        if(statuslength>0 || retxlength>0 ||txlength>0)
	        {
	            if(res_length>=(statuslength+retxlength+txlength))//TBSize´óÓÚ×ÜÐèÇó
	            {
	                temp_rlc_report=Mac_RlcRequest_copy(temp_mac_buffer->RlcRequestparams);
	                list_add_tail(&(temp_rlc_report->list), &(mac_rlc_report->list));
	                res_length=res_length-(statuslength+retxlength+txlength);
	                temp_logicalchannel_bj->lcbj-=(statuslength+retxlength+txlength);
	                break;
	            }
	            else if(res_length>=statuslength)//ÏÈ·Ö×´Ì¬PDU
	            {
	                temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
			while(temp_rlc_report==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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
	                    if(res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//´óÓÚÍ·²¿
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
	                    else if(res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//Ð¡ÓÚÍ·²¿
	                    {
	                        if(res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
	                        else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
	                    if(res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//´óÓÚÍ·²¿
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
	                    else if(res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//Ð¡ÓÚÖØ´«Í·²¿
	                    {
	                        if(res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
	                        else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
	            else if(res_length <statuslength)//Ð¡ÓÚ×´Ì¬PDU
	            {
	                temp_rlc_report=(RlcBufferRequest *)fsm_mem_alloc(sizeof(RlcBufferRequest));
		while(temp_rlc_report==0)//ÉêÇëÄÚ´æÊ§°Ü£¬ÔÙ´ÎÉêÇëÖ±µ½³É¹¦
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
	                        if(res_length>=(temp_mac_buffer->RlcRequestparams->txQueueHeader))//´óÓÚÍ·²¿
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
	                        else if(res_length < (temp_mac_buffer->RlcRequestparams->txQueueHeader))//Ð¡ÓÚÍ·²¿
	                        {
	                            if(res_length>= (temp_mac_buffer->RlcRequestparams->txQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
	                            else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
	                    if(res_length>=(temp_mac_buffer->RlcRequestparams->retxQueueHeader))//´óÓÚÍ·²¿
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
	                    else if(res_length < (temp_mac_buffer->RlcRequestparams-> retxQueueHeader))//Ð¡ÓÚÖØ´«Í·²¿
	                    {
	                        if(res_length>= (temp_mac_buffer->RlcRequestparams->retxQueueSize))//Ð¡ÓÚÍ·£¬´óÓÚÊý¾Ý
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
	                        else//Ð¡ÓÚÍ·£¬Ð¡ÓÚÊý¾Ý
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
    report_array=RlcRequest_listtoarray(mac_rlc_report,buffer_len,num);//report_arrayÊÇÒ»¸öÓÃ»§µÄreportÊ×µØÖ·£¬numÊÇ¸ÃÓÃ»§µÄreport Êý×éµÄ¸öÊý
    //num=report_num;
    pos=NULL,p=NULL;
    list_for_each_safe(pos,p,&(priority_mac_buffer->list))//±éÀú
    {
        temp_free=list_entry(pos,MacBufferStatus,list);
	fsm_mem_free(temp_free->RlcRequestparams);
        list_del_init(&(temp_free->list));
        fsm_mem_free(temp_free);
    }
     pos=NULL,p=NULL;
    list_for_each_safe(pos,p,&(lcbj_lessthan_zero->list))//±éÀú
    {
        temp_free=list_entry(pos,MacBufferStatus,list);
	fsm_mem_free(temp_free->RlcRequestparams);
        list_del_init(&(temp_free->list));
        fsm_mem_free(temp_free);
    }
    Empty_MACBuffer_Rlc(enb_buffer_rlc);//·ÖÅä×ÊÔ´ºó£¬Çå¿ÕMacBufferStatus
    FRET(report_array);
}
*/

/*****************É¾³ýlcid¶ÔÓ¦µÄÂß¼­ÐÅµÀÊôÐÔ,Ò²É¾³ý¸ÃÂß¼­ÐÅµÀµÄBJ***************/
/*******ÊäÈëÎªÒ»¸öÓÃ»§µÄrnti£¬ºÍÒªÉ¾³ýµÄlcid*****/
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
    	  list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))//²éÕÒRNTI¶ÔÓ¦µÄÓÃ»§
    	  {
    	  	temp_free=list_entry(pos,LogicalChannelConfigInfo,list);
    	  	if(rnti==temp_free->rnti)//ÕÒµ½¸ÃÓÃ»§
    	  	{
    	  		pos=NULL,p=NULL;
    	  		 list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))
		    	 {
		    	  	temp_free=list_entry(pos,LogicalChannelConfigInfo,list);
				if(temp_free->lcid==lcid_delete)//ÕÒµ½ÒªÉ¾³ýµÄÂß¼­ÐÅµÀ
			        {
			            list_del_init(&(temp_free->list));//delete a node of LogicalChannel_Config
			            fsm_mem_free(temp_free);
			        }
    	  		 }
			pos=NULL,p=NULL;
		    	list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Bj[i]))//BJÓëEnb_LogicalChannel_ConfigÊÇÒ»Ò»¶ÔÓ¦µÄ
		    	{
			        temp=list_entry(pos,LogicalChannelBj,list);
			        if(temp->lcid==lcid_delete)//ÕÒµ½¶ÔÓ¦µÄÂß¼­ÐÅµÀ
			        {
			            list_del_init(&(temp->list));//delete a node of LogicalChannel_Bj
			            fsm_mem_free(temp);
			        }
		    	}
    	  	}
		else
			break;//RNTI²»¶ÔÓ¦£¬ÖØÐÂ²éÕÒÓÃ»§
    	  }
    }
    FOUT;
}
/********Çå¿Õ¸ÃTTLËùÓÐÓÃ»§µÄRLCÇëÇóÁ´±íµÄ³¤¶È£¬ÎªÏÂ´ÎÇëÇóÇå¿Õ×ÊÔ´**********/
/********ÐèÒªÔÚ»ÆÇíµÄ×ÜÌå(ËùÓÐÓÃ»§)µ÷¶ÈµÄº¯ÊýÖÐµ÷ÓÃÒ»´Î¼´¿É**********/
void Empty_Rlcrequestnum(void)
{
	FIN(Empty_Rlcrequestnum());
    	SV_PTR_GET(mac_sv);
	fsm_mem_set(SV(Rlc_Request_Num),0,sizeof(int)*USERNUMMAX);
	FOUT;
}

/************Çå¿ÕMAC²ãµÄRLCÇëÇóBuffer********************/
/***ÊäÈëÎªÒ»¸öÓÃ»§µÄbufferÍ·Ö¸Õë***/
void Empty_MACBuffer_Rlc(struct list_head *enb_buffer_rlc)
{
    FIN(Empty_MACBuffer_Rlc(struct list_head *enb_buffer_rlc));
    SV_PTR_GET(mac_sv);
    struct list_head *pos=NULL,*p=NULL;
    MacBufferStatus *temp_free=NULL;
    list_for_each_safe(pos,p,enb_buffer_rlc)//±éÀú
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
    list_for_each_safe(pos,p,m_lc_info)//±éÀú
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
    list_for_each_safe(pos,p,m_lcbj_info)//±éÀú
    {
        temp_free=list_entry(pos,LogicalChannelBj,list);
        list_del_init(&(temp_free->list));
        fsm_mem_free(temp_free);
    }
    FOUT;
}

/***********ÊÍ·ÅUE MAC SCHEDULER×ÊÔ´************/
void Free_Enbmac_Scheduler_Resource(void)
{
    struct list_head *pos,*p;
    MacBufferStatus *temp_rlc_free=NULL;
    LogicalChannelBj *temp_bj_free=NULL;
    LogicalChannelConfigInfo *temp_lcginfo_free=NULL;//Âß¼­ÐÅµÀÊô ÐÔ
    int i;
    FIN(Free_Enbmac_Scheduler_Resource(void));
    SV_PTR_GET(mac_sv);  
    for(i=0;i<USERNUMMAX;i++)
    {
	    list_for_each_safe(pos,p,SV(Enb_MacBuffer_RLC[i]))//±éÀú
	    {
	        temp_rlc_free=list_entry(pos,MacBufferStatus,list);
		 fsm_mem_free(temp_rlc_free->RlcRequestparams);
	        list_del_init(&(temp_rlc_free->list));
	        fsm_mem_free(temp_rlc_free);
	    }
	   
	    pos=NULL;
	    p=NULL;
	    list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Bj[i]))//±éÀú
	    {
	        temp_bj_free=list_entry(pos,LogicalChannelBj,list);
	        list_del_init(&(temp_bj_free->list));
	        fsm_mem_free(temp_bj_free);
	    }
		
	    pos=NULL;
	    p=NULL;
	    list_for_each_safe(pos,p,SV(Enb_LogicalChannel_Config[i]))//±éÀú
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

  












