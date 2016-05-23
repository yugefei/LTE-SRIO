#include <linux/if_ether.h>
/****lhl¸Ä¶¯20140410****/
#include <linux/list.h>
#include <linux/kernel.h>
#include <stddef.h>
/****lhl¸Ä¶¯½áÊø20140410****/ 
#include "macfsm.h"
#include "macpkfmt.h"
#include "macscheduler.h"
#include "rrc_config.h"
#include "../lte_system.h"

#define LONG_BSR_SIZE 4
#define DL_PDU 2
#define RAR_PDU 1
#define SKB_REDUN 10


//¸Ãº¯ÊýÓÉdecomplex()º¯Êýµ÷ÓÃ£¬ÓÃÀ´´¦ÀíTA¿ØÖÆµ¥Ôª 
//HQ
/**
 * @function: deal with Timing Advance control element
 * @param ta_index: Timing Advance Command
 */
void MACCETA_handle(unsigned char ta_index) {   
	FIN(MACCETA_handle());
	//fsm_printf("[HEXI]RUN TA TIMER:%d\n",ta_index);

    SV_PTR_GET(mac_sv);
    if(SV(TATimer.flag)==true)
        fsm_schedule_cancel(SV(TATimer.timer_sign));
	//SV(TATimer.time_value)=(ta_index-31)*16+SV(TATimer.time_value);//¾ßÌå¼ÆËã´ý¶¨
	
	SV(TA_value)=(ta_index-31)*16+SV(TA_value);//LHL 20141021
	SV(TATimer.time_value)=SV(TA_Periodic_time);
	SV(TATimer.timer_sign)=fsm_schedule_self(SV(TATimer.time_value)*100,TimeAlignmentTimer_Expire);
	SV(TATimer.flag)=true;
		
FOUT;
}


/**************complex and decomplex functions HeXi 20140423 ******************/
/**
 * @function: decomplex the RAR PDU to get the MAC RAR that belongs to the user
 * @param skb: the sk_buff that contains the RAR PDU
 * @return: is there MAC RAR in the RAR PDU that belongs to the user
 */
bool decomplexRarPdu(FSM_PKT *skb){		//½â³ö¶ÔÓ¦×Ô¼ºµÄRAR SDU	//RAR½â¸´ÓÃ
	FIN(decomplexRarPdu());
	u32 offset;
	u32 c_flag;	//ÊÇ·ñ»¹ÓÐ¸ü¶àÓò
	short my_id,tadvance;//ra_PreambleIndex;TAÖµ
	u32 ul_grant,bi;		//ULGRANTÖµ,BIÖµ
	u32 head_len,rapid_in_subhead;	//Í·²¿³¤¶È£»×ÓÍ·ÖÐµÄrapidÖµ
	
	u32 sdu_numb=0,m_cnt=0;	//RARÊýÄ¿;¼ÆÊý
	u32 from_len=sizeof(char);//Æ«ÒÆÁ¿
	bool continue_flag=false;	//Ñ­»·¼ÌÐø±êÖ¾
	u32 len=sizeof(MAC_RAR_subhead_withbi);	//»ñÈ¡Ä³¸öµ¥Ôª³¤¶È
	u32 typ_flag=0;		//20140626¸ÄÀàÐÍ
	u32 m_tb_size=0;	//TB SIZEÖµ
	bool return_value=false;	//ÊÇ·ñ½â³ö·¢¸ø ×Ô¼ºµÄRAR
	MAC_RAR_subhead_withbi *bi_subhead=(MAC_RAR_subhead_withbi*)fsm_mem_alloc(sizeof(MAC_RAR_subhead_withbi));	//20140430¸Ä
	MAC_RAR_subhead *rar_subhead=(MAC_RAR_subhead*)fsm_mem_alloc(sizeof(MAC_RAR_subhead));	//20140430¸Ä
	MAC_RAR_sdu *rar_sdu=(MAC_RAR_sdu*)fsm_mem_alloc(sizeof(MAC_RAR_sdu));	//20140430¸Ä
	RAR_ULgrant *rar_ulgrant=(RAR_ULgrant*)fsm_mem_alloc(sizeof(RAR_ULgrant));	//20141111modified
	PHYadaptertoMAC_IciMsg *phy_ici=(PHYadaptertoMAC_IciMsg*)fsm_mem_alloc(sizeof(PHYadaptertoMAC_IciMsg));

	SV_PTR_GET(mac_sv);
	
	fsm_mem_set(bi_subhead,0,sizeof(MAC_RAR_subhead_withbi));	//20140430¸Ä
	fsm_mem_set(rar_subhead,0,sizeof(MAC_RAR_subhead));	//20140430¸Ä
	fsm_mem_set(rar_sdu,0,sizeof(MAC_RAR_sdu));	//20140430¸Ä
	fsm_mem_set(rar_ulgrant,0,sizeof(RAR_ULgrant));	//20141111modified
	fsm_mem_set(phy_ici,0,sizeof(PHYadaptertoMAC_IciMsg));

	/*fsm_printf("[MAC RAR]ORIGINAL DATA:\n");
	for(offset=0;offset<3;offset++){
		fsm_printf("%c,",*((char *)skb->data+offset));
	}
	fsm_printf("\n");*/
	//fsm_octets_print(newskb->data,4);
	
	/*
	 * for test
	 */
	SV(pkt_num_downlink)=SV(pkt_num_downlink)+1;
	
	fsm_mem_cpy(bi_subhead,skb->data+from_len,len);	//²é¿´T×Ö¶Î//20140626¸ÄdataÀïÃæÓÐtype×Ö¶Î
	//fsm_printf("[MAC RAR]BI SUBHEAD:%c:\n",bi_subhead->m_e_t_r_r_bi+65);
	
	typ_flag=bi_subhead->m_e_t_r_r_bi>>6;	//20140626¸Ä
	if(typ_flag==0||typ_flag==2){		//ÓÐBI×ÓÍ·
		c_flag=bi_subhead->m_e_t_r_r_bi>>7;
		bi=(bi_subhead->m_e_t_r_r_bi)&15;
		SV(backoff_index)=bi;
		from_len=from_len+len;
		head_len=from_len;
		if(c_flag==1){		//»¹ÓÐ¸ü¶àÓò
			continue_flag=true;
		}
	}
	else{
		continue_flag=true;
		head_len=1;
	}
	while (continue_flag){
		sdu_numb++;
		len=sizeof(MAC_RAR_subhead);
		fsm_mem_cpy(rar_subhead,skb->data+from_len,len);	//È¡³ö×ÓÍ·
		from_len=from_len+sizeof(MAC_RAR_subhead);
		c_flag=rar_subhead->m_e_t_rapid>>7;
		if(c_flag!=1)
			continue_flag=false;
	}

	fsm_printf("[HEXI]RAR SDU NUMBER AND THE OFFSET:%d %d\n",sdu_numb,from_len);

	while(sdu_numb>m_cnt){//?????????????????????????????????????????????????????
		len=sizeof(MAC_RAR_subhead);
		fsm_mem_cpy(rar_subhead,skb->data+head_len,len);	//È¡³ö×ÓÍ·
		head_len=head_len+len;
		rapid_in_subhead=(rar_subhead->m_e_t_rapid)&63;
		fsm_printf("[MAC RAR]RAPID:%d\n",rapid_in_subhead);

		len=sizeof(MAC_RAR_sdu);
		fsm_mem_cpy(rar_sdu,skb->data+from_len,len);		//È¡³öSDU

		//fsm_printf("[HEXI]T_C_RNTI IN ALL RARS:%d\n",rar_sdu->m_tcrnti);
		
		from_len=from_len+len;
		/*************·Ö¸îÏß*************/
		if(SV(rar_failed_num)==0)//Áªµ÷Ìí¼ÓµÄ¿ØÖÆ´úÂë
		{
			//fsm_printf("[HEXI]SV(rar_failed_num)==0!\n");
			my_id=SV(RA_info.ra_PreambleIndex);	//TEMPORY 
			
		}
		else
		{
			SV(rar_failed_num)=SV(rar_failed_num)-1;
			my_id=99;//Ò»¸ö²»¿ÉÄÜµÄÇ°µ¼Âë
		}
		/**************·Ö¸îÏß*******************/
		//my_id=25;
		fsm_printf("[HEXI]rapid_in_subhead:%d\n",rapid_in_subhead);
		fsm_printf("[HEXI]my_id:%d\n",my_id);
		if(rapid_in_subhead==my_id){	//ÊÇ×Ô¼ºµÄRAR
			return_value=true;
			SV(T_C_RNTI)=rar_sdu->m_tcrnti;
			fsm_printf("[HEXI]T_C_RNTI IN RAR:%d\n",SV(T_C_RNTI));
			
			tadvance=(rar_sdu->m_r_ta)&127;
			tadvance=tadvance<<4;
			tadvance=tadvance+(rar_sdu->m_ta_ulgrant>>4);
			SV(TA_fromRAR)=tadvance;//modified by HQ 20140502			
			//SV(TA_value)=tadvance*16;//LHL 20141021,TA*16TS,TSÊÇÎïÀí²ãµÄÒ»¸öÊ±¼äµ¥Î»
			//fsm_printf("TA_fromRAR is %d ms \n",SV(TA_value));//testing code 
			ul_grant=rar_sdu->m_ta_ulgrant<<4;
			ul_grant=ul_grant<<12;
			ul_grant=ul_grant+rar_sdu->m_ulgrant;
			//ul_grant=ul_grant<<12;
			fsm_mem_cpy(rar_ulgrant,&ul_grant,sizeof(u32));
			//m_tb_size=DoReceiveRARULgrant_Tbsize(ul_grant);	//ÕâÒ»¾ämakeÃ»Í¨¹ý£¬ºÃÏñ¸úÉùÃ÷ÓÐ¹Ø£¿		//20140428 ¸Ä

			SV(recv_frame).frameNo=phy_ici->frameNo;	//add on 11,17.2014
			SV(recv_frame).subframeNo=phy_ici->subframeNo;	//add on 11,17.2014

			m_tb_size=DoReceiveRARULgrant_Tbsize(rar_ulgrant);
			fsm_printf("[MAC][decomplex]m_tb_size:%d\n",m_tb_size);
			SV(UL_resource_info).m_tbsize=m_tb_size;		
			SV(UL_resource_info).resource_flag=true;		//the member is not addded yet
			break;
		}
		m_cnt++;
	}
	
	if(sdu_numb==m_cnt){
		SV(lost_pkt_num_downlink)=SV(lost_pkt_num_downlink)+1;
	}
	
	fsm_mem_free(bi_subhead);
	fsm_mem_free(rar_subhead);
	fsm_mem_free(rar_sdu);
	fsm_mem_free(rar_ulgrant);	//20141111modified
	fsm_mem_free(phy_ici);
	FRET(return_value);
}

/**
 * @function: fill in the C_RNTI control element
 * @param m_crnti: the structure of C_RNTI control element
 * @return: is there C_RNTI control element to send
 */
bool lteMacCEC_rntiSend(MAC_CE_Crnti *m_crnti){	//ÊÇ·ñÓÐc-rnti¿ØÖÆµ¥Ôª·¢ËÍ
	FIN(lteMacCEC_rntiSend());

	u32 tag_pos;
	SV_PTR_GET(mac_sv);
	
	for(tag_pos=0;tag_pos<MACCE_ARRAY_size;tag_pos++){
		if(SV(MAC_CE_Tags[tag_pos]).LCID==C_RNTI_LCID){
			fsm_printf("[HEXI]C_RNTI CONTROL ELEMENT FOUND!\n");

			m_crnti->m_crnti=*((u16*)(SV(MAC_CE_Tags[tag_pos]).MAC_CE_ptr));
			
			//fsm_printf("[MAC CRNTI]RNTI IN SV:%d\n",SV(C_RNTI));
			
			FRET(SV(MAC_CE_Tags[tag_pos]).addinPDU_flag);
		}
	}
	
	FRET(false);
}

/**
 * @function: fill in the Power Headroom control element
 * @param m_power_headroom: the structure of Power Headroom control element
 * @return: is there Power Headroom control element tfsm_printf("[HEXI]UE ID AND ESTABLUSHMENT CAUSE AND THE OFFSET:%d,%d,%d\n",(m_rrc_request->ue_Identity.s_TMSI.mmec+m_rrc_request->ue_Identity.s_TMSI.m_TMSI),m_rrc_request->establishmentCause,offset);o send
 */
bool lteMacCEPhSend(MAC_CE_power_headroom *m_power_headroom){		//ÊÇ·ñÓÐ¹¦ÂÊÓàÁ¿¿ØÖÆµ¥Ôª·¢ËÍ
	FIN(lteMacCEPhSend(MAC_CE_power_headroom *m_power_headroom));
	
	u32 tag_pos;

	SV_PTR_GET(mac_sv);
	for(tag_pos=0;tag_pos<MACCE_ARRAY_size;tag_pos++){
		if(SV(MAC_CE_Tags[tag_pos]).LCID==PHR_LCID){
			m_power_headroom=(MAC_CE_power_headroom*)(SV(MAC_CE_Tags[tag_pos]).MAC_CE_ptr);

			FRET(SV(MAC_CE_Tags[tag_pos]).addinPDU_flag);
		}
	}
	FRET(false);
}
	
/**
 * @function: find the PDU transport in the CCCH and back it up
 * @param skb: the sk_buff contains MAC PDU from RLC layer
 * @param ici_len
 * @return
 */
u32 lteMacCcchSend(FSM_PKT *skb,u32 ici_len){		//ÅÐ¶ÏÓÐÃ»ÓÐCCCHÐÅµÀÉÏµÄÊý¾Ý²¢±¸·ÝÓÃ×÷¾ºÕù½â¾ö//20140430¸Ä£¡
	FIN(lteMacCcchSend());

	u32 len=0,lcid=-1,from_len=0,sdu_len=0,offset=0,f_domain=-1,skb_len=0;
	long contention_resolution;
	u32 continue_flag=1;
	u32 ccch_or_not = 1;//HQ modified 20140709 
	RRCConnectionRequest *m_rrc_request=(RRCConnectionRequest *)fsm_mem_alloc(sizeof(RRCConnectionRequest));	//20140430¸Ä
	MAC_SDU_subhead_7bit *m_7bit_subhead=(MAC_SDU_subhead_7bit*)fsm_mem_alloc(sizeof(fsm_mem_alloc));	//20140430¸Ä
	MAC_SDU_subhead_15bit *m_15bit_subhead=(MAC_SDU_subhead_15bit*)fsm_mem_alloc(sizeof(MAC_SDU_subhead_15bit));	//20140430¸Ä
	//Ccch_Msg *m_ccch_msg=(UL_CCCH_Message*)fsm_mem_alloc(sizeof(UL_CCCH_Message));
	
	SV_PTR_GET(mac_sv);
	
	fsm_mem_set(m_rrc_request,0,sizeof(RRCConnectionRequest));	//20140430¸Ä
	fsm_mem_set(m_7bit_subhead,0,sizeof(MAC_SDU_subhead_7bit));	//20140430¸Ä
	fsm_mem_set(m_15bit_subhead,0,sizeof(MAC_SDU_subhead_15bit));
	//fsm_mem_set(m_ccch_msg,0,sizeof(UL_CCCH_Message));
	len=sizeof(MAC_SDU_subhead_7bit);
	fsm_mem_cpy(m_7bit_subhead,skb->head+ici_len+from_len,len);
	continue_flag=m_7bit_subhead->m_lcid_e_r_r>>5;
	lcid=(m_7bit_subhead->m_lcid_e_r_r)&31;
	f_domain=m_7bit_subhead->m_f_l>>7;
	fsm_printf("[MAC CCCHSNED]CONTINUE FLAG:%d;LCID:%d;DATA TYPE FROM CCCH:%d\n",continue_flag,lcid,f_domain);
	/*for(i=0;i<4;i++){
		fsm_printf("%c,",*(skb->data+i));
	}
	fsm_printf("\n");*/
	//offset=sizeof(u32);	//I don't know why
	offset=0;
	
	while(continue_flag==1){
		if(lcid==0){								//ÓÐccchµÄÊý¾Ý¾Í±£´æ
		    //fsm_printf("There are two SDU from CCCH ,error \n");//testing code
		    ccch_or_not = 0;//±ê×¢ÊÇCCCHÉÏµÄÊý¾Ý 
			len=sizeof(RRCConnectionRequest);
			fsm_mem_cpy(m_rrc_request,skb->data+offset,len);
			//SV(m_temp_cr)->m_part_1=(m_rrc_request->ue_Identity.randomValue)&0x0000ffff;	//½«randomValueµÄµÍ32Î»±£´æ
			//SV(m_temp_cr)->m_part_2=(m_rrc_request->ue_Identity.randomValue&0x000f0000)>>32;	//½«randomValueµÄµÍ33~40Î»±£´æ
			/*
			SV(m_temp_cr)->m_part_1=(m_rrc_request->ue_Identity)&0x0000ffff;
			SV(m_temp_cr)->m_part_2=(m_rrc_request->ue_Identity&0x000f0000)>>32;
			*/
			len=sizeof(SV(m_temp_cr)->m_part_1);
			fsm_mem_cpy(&(SV(m_temp_cr)->m_part_1),&(m_rrc_request->ue_Identity),len+1);
			
			fsm_printf("[HEXI]SV(m_temp_cr)->m_part_1=%d\n",SV(m_temp_cr)->m_part_1);
			
			fsm_mem_cpy(&(SV(m_temp_cr)->m_part_2),&(m_rrc_request->ue_Identity),1);
			
			fsm_printf("[HEXI]SV(m_temp_cr)->m_part_2=%d\n",SV(m_temp_cr)->m_part_2);
			
			SV(m_temp_cr)->m_part_2=SV(m_temp_cr)->m_part_2+(m_rrc_request->establishmentCause&0x000f)<<8;	//½«establishmentCauseµÄµÍ8Î»±£´æÔÚm_part_2µÄ¸ß°ËÎ»
			
			fsm_printf("[HEXI]SV(m_temp_cr)->m_part_2=%d\n",SV(m_temp_cr)->m_part_2);
			
			/*//20140708 adition start by HEXI ÎªÁËÒÔÕû¸ösk_buffµÄ½á¹¹À´±¸·Ýmsg3  ÓÃÓÚµÚ¶þ´ÎÒÔ¼°ÒÔºóµÄ¾ºÕùËæ»ú½ÓÈëµÄMSG3
			SV(msg3_buf_ptr)= fsm_pkt_create(128);
			skb_len = skb->data - skb->head ;
			fsm_skb_reserve(SV(msg3_buf_ptr),skb_len);
			fsm_mem_cpy(SV(msg3_buf_ptr)->head,skb->head,skb_len);
			skb_len = skb->tail - skb->data;
			fsm_skb_put(SV(msg3_buf_ptr),skb_len);
			fsm_mem_cpy(SV(msg3_buf_ptr)->data,skb->data,skb_len);
			//20140708 adition end  by HEXI */
			break;
		}
		if(f_domain==1){	//15bit×ÓÍ·		20140430¸Ä
			len=sizeof(MAC_SDU_subhead_15bit);
			from_len=from_len+len;
			sdu_len=(m_15bit_subhead->m_f_l)&127;
			sdu_len=sdu_len<<8;
			sdu_len=sdu_len+m_15bit_subhead->m_l;
			offset=offset+sdu_len;

			}
			else{		//7bit×ÓÍ·		//20140430¸Ä
				from_len=from_len+len;
				sdu_len=(m_7bit_subhead->m_f_l)&127;
				offset=offset+sdu_len;
			}
		len=sizeof(MAC_SDU_subhead_7bit);
		fsm_mem_cpy(m_7bit_subhead,skb->head+ici_len+from_len,len);
		continue_flag=m_7bit_subhead->m_lcid_e_r_r>>5;
		lcid=(m_7bit_subhead->m_lcid_e_r_r)&31;
		f_domain=m_7bit_subhead->m_f_l>>7;
		
	}
		if(lcid==0){								//ÓÐccchµÄÊý¾Ý¾Í±£´æ
		    //fsm_printf("This SDU is from CCCH ");//testing code
		    ccch_or_not = 0;//±ê×¢ÊÇCCCHÉÏµÄÊý¾Ý 
			len=sizeof(RRCConnectionRequest);
			fsm_mem_cpy(m_rrc_request,skb->data+offset,len);

			//fsm_printf("[HEXI]UE ID AND ESTABLUSHMENT CAUSE AND THE OFFSET:%d,%d,%d\n",(m_rrc_request->ue_Identity.s_TMSI.mmec+m_rrc_request->ue_Identity.s_TMSI.m_TMSI),m_rrc_request->establishmentCause,offset);

			//SV(m_temp_cr)->m_part_1=(m_rrc_request->ue_Identity.randomValue)&0x0000ffff;	//½«randomValueµÄµÍ32Î»±£´æ
			//SV(m_temp_cr)->m_part_2=(m_rrc_request->ue_Identity.randomValue&0x000f0000)>>32;	//½«randomValueµÄµÍ33~40Î»±£´æ
			len=sizeof(SV(m_temp_cr)->m_part_1);
			fsm_mem_cpy(&(SV(m_temp_cr)->m_part_1),&(m_rrc_request->ue_Identity),len+1);
			
			fsm_printf("[HEXI]SV(m_temp_cr)->m_part_1=%d\n",SV(m_temp_cr)->m_part_1);
			
			fsm_mem_set(&(SV(m_temp_cr)->m_part_2),0,sizeof(u16));
			fsm_mem_cpy(&(SV(m_temp_cr)->m_part_2),&(m_rrc_request->ue_Identity),1);
			
			fsm_printf("[HEXI]SV(m_temp_cr)->m_part_2=%d\n",SV(m_temp_cr)->m_part_2);
			
			SV(m_temp_cr)->m_part_2=SV(m_temp_cr)->m_part_2+(m_rrc_request->establishmentCause&0x000f)<<8;	//½«establishmentCauseµÄµÍ8Î»±£´æÔÚm_part_2µÄ¸ß°ËÎ»
			//fsm_printf("[MAC CCCHSEND]%d\n",m_rrc_request->establishmentCause);
			
			fsm_printf("[HEXI]SV(m_temp_cr)->m_part_2=%d\n",SV(m_temp_cr)->m_part_2);
			
		/*	//20140708 adition start by HEXI ÎªÁËÒÔÕû¸ösk_buffµÄ½á¹¹À´±¸·Ýmsg3  ÓÃÓÚµÚ¶þ´ÎÒÔ¼°ÒÔºóµÄ¾ºÕùËæ»ú½ÓÈëµÄMSG3
			SV(msg3_buf_ptr)= fsm_pkt_create(128);
			skb_len = skb->data - skb->head ;
			fsm_skb_reserve(SV(msg3_buf_ptr),skb_len);
			fsm_mem_cpy(SV(msg3_buf_ptr)->head,skb->head,skb_len);
			skb_len = skb->tail - skb->data;
			fsm_skb_put(SV(msg3_buf_ptr),skb_len);
			fsm_mem_cpy(SV(msg3_buf_ptr)->data,skb->data,skb_len);
			//20140708 adition end  by HEXI */
		}
	fsm_mem_free(m_rrc_request);
	fsm_mem_free(m_7bit_subhead);
	fsm_mem_free(m_15bit_subhead);
	FRET(ccch_or_not);
		//FRET(0);
}


/**
 * @function: fill in the ICI from MAC to RLC
 * @param ici_msg: the structure of the ICI
 * @param pbch: the channel that carries the PDU
 * @param lcid: identity of the logical channel
 */
void setMACtoRLC_IciMsg(MACtoRLC_IciMsg *ici_msg,PBCH pbch,u32 lcid){	//20140430¸Ä ÌîÐ´MACtoRLC_IciMsg
	FIN(setMACtoRLC_IciMsg());

	SV_PTR_GET(mac_sv);
	ici_msg->lcid=lcid;
	ici_msg->pbch=pbch;
	ici_msg->rnti=SV(C_RNTI);	
	FOUT;
}

/**
 * @function: fill in the ICI from MAC to SRIO
 * @param ici_msg: the structure of the ICI
 * @param tcid: identity of the transpotation channel
 */
/*void setMACtoPHY_IciMsg( MACtoPHYadapter_IciMsg *ici_msg,u32 tcid){	//20140430¸Ä ÌîÐ´MACtoRLC_IciMsg
	FIN(setMACtoRLC_IciMsg());
	SV_PTR_GET(mac_sv);
	ici_msg->tcid=tcid;
	ici_msg->rnti=SV(C_RNTI)==0?SV(T_C_RNTI):SV(C_RNTI);

	ici_msg->frameNo=SV(sys_frame).frameNo;
	ici_msg->subframeNo=SV(sys_frame).subframeNo;
	SV(sys_frame).frameNo=0;
	SV(sys_frame).subframeNo=0;
		
	//¸ü¶à³ÉÔ±µÄÌî³ä´ý¶¨
	FOUT;
}*/
void setMACtoPHY_IciMsg( MACtoPHYadapter_IciMsg *ici_msg,u32 tcid,u16 rnti){	//20140430¸Ä ÌîÐ´MACtoRLC_IciMsg
	FIN(setMACtoRLC_IciMsg());
	SV_PTR_GET(mac_sv);
	ici_msg->tcid=tcid;
	ici_msg->rnti=rnti==0?(SV(C_RNTI)==0?SV(T_C_RNTI):SV(C_RNTI)):rnti;

	ici_msg->frameNo=SV(sys_frame).frameNo;
	ici_msg->subframeNo=SV(sys_frame).subframeNo;
	SV(sys_frame).frameNo=0;
	SV(sys_frame).subframeNo=0;
		
	//¸ü¶à³ÉÔ±µÄÌî³ä´ý¶¨
	FOUT;
}

/**
 * @function: get the data to fill in the BSR control element
 * @param lcg_id: indicate the identity of logical channel group if there is a short BSR control element to send
 * @param shortbsr_buffer_size: indicate the buffer size if there is a short BSR control element to send
 * @param longbsr_buf_sizes: indicate each buffer size of the four logical channel groups if there is a long BSR control element to send
 * @param size_of_longbsr: total size of the long BSR
 * @return 0 if none BSR need be sent;1 if a short BSR needs to be sent;>1 if a long BSR need be sent
 */
u32 lteMacCEBSRSend(u32 *lcg_id,u32 *shortbsr_buffer_size,u32 longbsr_buf_sizes[],u32 size_of_longbsr){//0±íÊ¾Ã»ÓÐ£¬1±íÊ¾¶ÌBSR£¬´óÓÚ1±íÊ¾³¤BSR//ÊÇ·ñÓÐBSR¿ØÖÆµ¥Ôª£¬²¢±£´æÏà¹ØÐÅÏ¢
        FIN(lteMacCEBSRSend());  
		//bool beak_flag=false;
	u32 tag_pos,lcg_pos;
	
	u32 lcg_numb=0;
	u32 len=sizeof(MacCeListElement_s);  

	//unsigned char regular_flag=SEND_REGULAR_BSR,period_flag=SEND_PERIODIC_BSR;	//provided bt Liu Hanli.It is for judging which BSR is to send.However I can judge whiout them.I wonder if I'm right.
	MacCeListElement_s *m_bsr_infor=(MacCeListElement_s*)fsm_mem_alloc(sizeof(MacCeListElement_s));	//20140430¸Ä
	SV_PTR_GET(mac_sv);

	fsm_mem_set(m_bsr_infor,0,sizeof(MacCeListElement_s));	//20140430¸Ä
	for(tag_pos=0;tag_pos<MACCE_ARRAY_size;tag_pos++){		//ÕâÀïÊµ¼ÊÉÏÒÑ¾­ÓÅÏÈÁË³£¹æBSR

		//fsm_printf("[BSR_SEND]LCID IN BSR DETECT:%d\n",SV(MAC_CE_Tags[tag_pos]).LCID);

		if(SV(MAC_CE_Tags[tag_pos]).LCID==SHORT_BSR){	//¶ÌBSR
		    fsm_mem_cpy(m_bsr_infor, SV(MAC_CE_Tags[tag_pos]).MAC_CE_ptr,len);
		//	memcpy(m_bsr_infor,&SV(MAC_CE_Tags[i]),len);//201405012 ÐèÒªÐÞ¸Ä
			*shortbsr_buffer_size=m_bsr_infor->m_TotalLcgData;
			for(lcg_pos=0;lcg_pos<LCG_SIZE;lcg_pos++){
				if(m_bsr_infor->m_bufferStatus[lcg_pos]!=0){	//Ä³¸öÂß¼­ÐÅµÀ×éµÄID²»ÎªÁã
					lcg_numb++;
					*lcg_id=lcg_pos;
					longbsr_buf_sizes[lcg_pos]=m_bsr_infor->m_bufferStatus[lcg_pos];
				}
				else
					longbsr_buf_sizes[lcg_pos]=0;
				if(lcg_numb>1)
					*lcg_id=0;
			}
			fsm_mem_free(m_bsr_infor);
			FRET(lcg_numb);
		}
		else if(SV(MAC_CE_Tags[tag_pos]).LCID==LONG_BSR){
			 fsm_mem_cpy(m_bsr_infor, SV(MAC_CE_Tags[tag_pos]).MAC_CE_ptr,len);
			//memcpy(m_bsr_infor,&SV(MAC_CE_Tags[i]),len);
			*shortbsr_buffer_size=m_bsr_infor->m_TotalLcgData;
			for(lcg_pos=0;lcg_pos<LCG_SIZE;lcg_pos++){
				//fsm_printf("[BSR_SEND]THE %dTH BUFFER STATUS is %d\n",lcg_pos,m_bsr_infor->m_bufferStatus[lcg_pos]);

				if(m_bsr_infor->m_bufferStatus[lcg_pos]!=0){
					lcg_numb++;
					*lcg_id=lcg_pos;
					longbsr_buf_sizes[lcg_pos]=m_bsr_infor->m_bufferStatus[lcg_pos];
				}
				else
					longbsr_buf_sizes[lcg_pos]=0;
				if(lcg_numb>1)
					*lcg_id=0;
			}
			*shortbsr_buffer_size=0;		//Ã»ÓÐBSR
			fsm_mem_free(m_bsr_infor);
			FRET(lcg_numb);
		}
	}
	fsm_mem_free(m_bsr_infor);
	FRET(0);
}

/**
 * @function: calculate the length of the head of the downlink MAC PDU
 * @param skb: the sk_buff contains the PDU from SRIO layer
 * @return: the length of the head
 */
u32 lteMacGetDlHeadLength(FSM_PKT *skb){	//»ñÈ¡Í·²¿³¤¶È£¨ÏÂÐÐ£©
	FIN(lteMacGetDlHeadLength());

	u32 m_e,m_lcid,m_f;

	u32 last_len=0,subhead_7bit_len=0,subhead_15bit_len=0,from_len=1;	//20140626¸Ä//ÒòÎª°üÀ¨ÁËtype×Ö¶Î
	MAC_SDU_subhead_15bit *m_15bit_subhead=(MAC_SDU_subhead_15bit*)fsm_mem_alloc(sizeof(MAC_SDU_subhead_15bit));	//20140430¸Ä
	MAC_SDU_subhead_last *fixed_subhead=(MAC_SDU_subhead_last*)fsm_mem_alloc(sizeof(MAC_SDU_subhead_last));	//20140430¸Ä
	MAC_SDU_subhead_7bit *m_7bit_subhead=(MAC_SDU_subhead_7bit*)fsm_mem_alloc(sizeof(MAC_SDU_subhead_7bit));	//20140430¸Ä

	fsm_mem_set(m_15bit_subhead,0,sizeof(MAC_SDU_subhead_15bit));	//20140430¸Ä
	fsm_mem_set(fixed_subhead,0,sizeof(MAC_SDU_subhead_last));	//20140430¸Ä
	fsm_mem_set(m_7bit_subhead,0,sizeof(MAC_SDU_subhead_7bit));	//20140430¸Ä
	
	last_len=sizeof(MAC_SDU_subhead_last);
	subhead_7bit_len=sizeof(MAC_SDU_subhead_7bit);
	subhead_15bit_len=sizeof(MAC_SDU_subhead_15bit);
	fsm_mem_cpy(fixed_subhead,skb->data+from_len,last_len);	//20140626¸Ä//´Ótype×Ö¶ÎÖ®ºó¿ªÊ¼¼ì²â
	m_e=fixed_subhead->m_lcid_e_r_r>>5;
	//20140626É¾³ý
	while(m_e==1){		//ÓÐ¸ü¶àµÄÓò
		m_lcid=(fixed_subhead->m_lcid_e_r_r)&31;
		
		fsm_printf("[HEXI]LCID IN GETTING HEAD LENGTH AND LENGTH OF HEAD:%d,%d\n",m_lcid,from_len);
		
		switch(m_lcid){
		case PADDING_LCID :
			from_len=from_len+last_len;
			break;
		case DRX_LCID :
			from_len=from_len+last_len;
			break;
		case TIMING_ADVANCE_LCID :
			from_len=from_len+last_len;
			break;
		case CONTENTION_RESOLUTION_LCID :
			from_len=from_len+last_len;
			break;
		default:
			fsm_mem_cpy(m_7bit_subhead,skb->data+from_len,subhead_7bit_len);
			m_f=m_7bit_subhead->m_f_l>>7;
			if(m_f==1){
				from_len=from_len+subhead_15bit_len;
			}
			else{
				from_len=from_len+subhead_7bit_len;
			}
			break;
		}
		fsm_mem_cpy(fixed_subhead,skb->data+from_len,last_len);
		m_e=fixed_subhead->m_lcid_e_r_r>>5;		//20140626¸Ä
	}
		m_lcid=(fixed_subhead->m_lcid_e_r_r)&31;
		
		fsm_printf("[HEXI]LCID IN GETTING HEAD LENGTH AND LENGTH OF HEAD:%d,%d\n",m_lcid,from_len);
		
	switch(m_lcid){		//whileÑ­»·ºó»¹Ê£Ò»Ïî
	case PADDING_LCID :
		from_len=from_len+last_len;
		break;
	case DRX_LCID :
		from_len=from_len+last_len;
		break;
	case TIMING_ADVANCE_LCID :
		from_len=from_len+last_len;
		break;
	case CONTENTION_RESOLUTION_LCID :
		from_len=from_len+last_len;
		break;
	default:
		fsm_mem_cpy(m_7bit_subhead,skb->data+from_len,subhead_7bit_len);
		m_f=m_7bit_subhead->m_f_l>>7;
		if(m_f==1){
			
			fsm_printf("[HEXI]COMPLEX 15 BIT SUBHEAD!\n");
		
			from_len=from_len+subhead_15bit_len;
		}
		else{
			
			fsm_printf("[HEXI]COMPLEX 7 BIT SUBHEAD!\n");
		
			from_len=from_len+subhead_7bit_len;
		}
		break;
	}
	fsm_mem_free(m_15bit_subhead);
	fsm_mem_free(fixed_subhead);
	fsm_mem_free(m_7bit_subhead);
	FRET(from_len);
}

/**
 * @function: exclude the information in PCH, BCCH in the decomplexing to offer the result whether the MSG4 is successful
 * @param c_rnti: rnti in the PHY-T-MAC-ICI
 */

void Pdcch_c_rnti(unsigned short c_rnti){//½â¸´ÓÃÅÅ³ýPCH,BCCHÐÅµÀµÄÐÅÏ¢£¬ÎªÅÐ¶ÏMSG4ÊÇ·ñ³É¹¦Ìá¹©±êÖ¾
	FIN(Pdcch_c_rnti(unsigned short c_rnti));
	SV_PTR_GET(mac_sv);
	if(SV(sendmsg3)==1){//ÒÑ·¢ËÍmsg3
		if((c_rnti==SV(C_RNTI)) && SV(C_RNTI)!=0)//PDCCHÊÇÍ¨¹ýC_RNTIÑ°Ö·
		{
			SV(pdcch_rnti)=1;//±êÖ¾ÖÃÎª1
			//if((SV(RA_Type.ra_type)==1) &&SV(CRTimer.flag)==true)//PDCCHÉÏ·¢ÆðµÄËæ»ú½ÓÈë
			if(SV(CRTimer.flag)==true)	//test,for struct RA_Type in the last row is unkown
			{
				fsm_schedule_self(0, Contention_Success );//3//3GPP³¤ÆÚÑÝ½øP121 	
				//fsm_printf("UE MAC Pdcch_c_rnti:Contention Resolution successfully\n");
			}				
		}
		else if ((c_rnti !=SV(C_RNTI)) && SV(C_RNTI)!=0){//PDCCH²»ÊÇÍ¨¹ýCRNTIÑ°Ö·
			SV(pdcch_rnti)=0;//±êÖ¾ÖÃÎª0
			fsm_schedule_self(0, ContentionResolution_Fail );//3
			//fsm_printf("UE MAC Pdcch_c_rnti:Contention Resolution fail\n");
		}
	}
	else
		SV(pdcch_rnti)=0;
	FOUT;
}


	

/**
 * @function: decomplex MAC SDU,along with MAC control elements, into MAC PDU
 * @param skb: the sk_buff contains the data of the SDU from RLC layer
 */
void decomplexUeDataPdu(FSM_PKT *skb){		//½â¸´ÓÃ  
	FIN(decomplexUeDataPdu());
	
	u32 lcid,f_domain;	//LCIDÖµ£»³¤¶ÈÖµ
	u32 part1;	//¾ºÕù½â¾öµ¥ÔªµÄÇ°ËÄ¸ö×Ö½Ú
	short part2,timing;	//¾ºÕù½â¾öµ¥ÔªºóÁ½¸ö×Ö½Ú£»Timing Advance CommandÖµ 
	FSM_PKT *newskb;
	u32 len;	//»ñÈ¡Ä³¸öµ¥Ôª³¤¶È,ÁÙÊ±´æ´¢
	char m_type;	//type×Ö¶Î
	
	u32 continue_flag=1,padding_flag=0;	//Ñ­»·¼ÌÐø±êÊ¶£»ÊÇ·ñÓÐpaddingµ¥Ôª
	u32 numb=0,from_len=0,head_len,sdu_len=0;	//Êý¾Ýµ¥ÔªÊýÄ¿;Æ«ÒÆÁ¿;Í·²¿³¤¶È;Êý¾Ýµ¥ÔªÆ«ÒÆÁ¿
	MAC_SDU_subhead_15bit *m_15bit_subhead=(MAC_SDU_subhead_15bit*)fsm_mem_alloc(sizeof(MAC_SDU_subhead_15bit));	//20140430¸Ä
	MAC_SDU_subhead_last *m_fixed_subhead=(MAC_SDU_subhead_last*)fsm_mem_alloc(sizeof(MAC_SDU_subhead_last));	//20140430¸Ä
	MAC_SDU_subhead_7bit *m_7bit_subhead=(MAC_SDU_subhead_7bit*)fsm_mem_alloc(sizeof(MAC_SDU_subhead_7bit));	//20140430¸Ä
	MAC_SH_padding *m_padding_subhead=(MAC_SH_padding*)fsm_mem_alloc(sizeof(MAC_SH_padding));	//20140430¸Ä
	MAC_CE_content_resolution_identity *m_content_resolution=(MAC_CE_content_resolution_identity*)fsm_mem_alloc(sizeof(MAC_CE_content_resolution_identity));	//20140430¸Ä
	MAC_CE_time_advance *m_time_advance=(MAC_CE_time_advance*)fsm_mem_alloc(sizeof(MAC_CE_time_advance));	//20140430¸Ä
	MACtoRLC_IciMsg *m_rlc_type2_icimsg=(MACtoRLC_IciMsg*)fsm_mem_alloc(sizeof(MACtoRLC_IciMsg));		//20140430¸Ä	//20140430¸Ä
	PHYadaptertoMAC_IciMsg *m_phy_ici=(PHYadaptertoMAC_IciMsg*)fsm_mem_alloc(sizeof(PHYadaptertoMAC_IciMsg));

	SV_PTR_GET(mac_sv);
	
	fsm_mem_set(m_15bit_subhead,0,sizeof(MAC_SDU_subhead_15bit));	//20140430¸Ä
	fsm_mem_set(m_fixed_subhead,0,sizeof(MAC_SDU_subhead_last));	//20140430¸Ä
	fsm_mem_set(m_7bit_subhead,0,sizeof(MAC_SDU_subhead_7bit));	//20140430¸Ä
	fsm_mem_set(m_content_resolution,0,sizeof(MAC_CE_content_resolution_identity));	//20140430¸Ä
	fsm_mem_set(m_time_advance,0,sizeof(MAC_CE_time_advance));	//20140430¸Ä
	fsm_mem_set(m_rlc_type2_icimsg,0,sizeof(MACtoRLC_IciMsg));	//20140430¸Ä
	fsm_mem_set(m_padding_subhead,0,sizeof(MAC_SH_padding));	//20140430¸Ä
	fsm_mem_set(m_phy_ici,0,sizeof(PHYadaptertoMAC_IciMsg));


	u32 i;
	//fsm_printf("[HEXI]SKB->DATA BEFORE DECOMPLEX:\n");
	/*for(i=0;i<10;i++){
		fsm_printf("%c ",*(skb->data+i)+65);	
	}
	fsm_printf("\n");*/

    //ÏÈÐèÒª¸ù¾ÝPHYICIÅÐ¶ÏÒ»ÏÂÊý¾ÝÀ´×ÔÄÄÌõ´«ÊäÐÅµÀ  HQ 20140502

	/*
	 * for test
	 */
	SV(pkt_num_downlink)=SV(pkt_num_downlink)+1;


	len=sizeof(PHYadaptertoMAC_IciMsg);
	fsm_mem_cpy(m_phy_ici,skb->head,len);
	if(m_phy_ici->tcid==BCH){
		//¹ã²¥µÄPDU£¬Í¸´«
		fsm_printf("recieve BCCH data packet\n");//testing code
		setMACtoRLC_IciMsg(m_rlc_type2_icimsg,BCCH,0);
		len=sizeof(MACtoRLC_IciMsg);
		fsm_mem_cpy(skb->head,m_rlc_type2_icimsg,len);	//½«MAC TO RLCµÄICIÐÅÏ¢·ÅÖÃµ½SK_buffÖÐ
		//Ç°ÌáÊÇÎïÀíÊÊÅä²ãÉÏµÝµÄSK_BUFFµÄÍ·²¿¾ßÓÐ×ã¹»µÄ¿Õ¼ä£¬ÕâµãÐèÒªÎïÀíÊÊÅä²ã×¢Òâ ÎÊÌâ
		//fsm_pkt_send(skb,STRM_TO_RLC);

		fsm_pkt_send(newskb,STRM_TO_IPADP);

		fsm_printf("[HEXI] packet sent to rlc:len:%d\n",skb->len);
		fsm_octets_print(skb->data,skb->len);
		fsm_mem_free(m_15bit_subhead);
		fsm_mem_free(m_7bit_subhead);
		fsm_mem_free(m_padding_subhead);
		fsm_mem_free(m_content_resolution);
		fsm_mem_free(m_time_advance);
		fsm_mem_free(m_rlc_type2_icimsg);
		fsm_mem_free(m_phy_ici);
		fsm_mem_free(m_fixed_subhead);
		FOUT;
	}
	if(m_phy_ici->tcid==PCH){
		//Ñ°ºôÏûÏ¢£¬ÔÝ¶¨ÊÇÍ¸´« ´ý¶¨ÎÊÌâ
		fsm_printf("recieve PCCH data packet\n");//testing code
		setMACtoRLC_IciMsg(m_rlc_type2_icimsg,PCCH,0);
		len=sizeof(MACtoRLC_IciMsg);
		fsm_mem_cpy(skb->head,m_rlc_type2_icimsg,len);	//½«MAC TO RLCµÄICIÐÅÏ¢·ÅÖÃµ½SK_buffÖÐ
		//Ç°ÌáÊÇÎïÀíÊÊÅä²ãÉÏµÝµÄSK_BUFFµÄÍ·²¿¾ßÓÐ×ã¹»µÄ¿Õ¼ä£¬ÕâµãÐèÒªÎïÀíÊÊÅä²ã×¢Òâ ´ý¶¨ÎÊÌâ
		//fsm_pkt_send(skb,STRM_TO_RLC);

		fsm_pkt_send(newskb,STRM_TO_IPADP);

		fsm_printf("[HEXI] packet sent to rlc:len:%d\n",skb->len);
		fsm_octets_print(skb->data, skb->len);
		fsm_mem_free(m_15bit_subhead);
		fsm_mem_free(m_7bit_subhead);
		fsm_mem_free(m_padding_subhead);
		fsm_mem_free(m_content_resolution);
		fsm_mem_free(m_time_advance);
		fsm_mem_free(m_rlc_type2_icimsg);
		fsm_mem_free(m_phy_ici);
		fsm_mem_free(m_fixed_subhead);
		FOUT;
	}
	if(m_phy_ici->tcid==DLSCH){
		fsm_printf("recieve DLSCH data packet, \n");//testing code
		len=sizeof(char);
		head_len=lteMacGetDlHeadLength(skb);	//ÒÑ½âSDUµÄÎ»ÖÃ
		
		//fsm_printf("[HEXI]LENGTH OF HEAD IN DECOMPLEX:%d\n",head_len);
		fsm_mem_cpy(&m_type,skb->data,len);//ÐèÒªÏÈÌáÈ¡³öµÚÒ»¸ö×Ö½ÚµÄÊý¾Ý  HQ 20140502
		fsm_printf("[HEXI]TYPE IN DECOMPLEX:%c\n",(m_type+65));
		
		from_len=len;	//(Í·²¿)ÒÑ±»½â¸´ÓÃµÄ³¤¶È
		if(m_type==RAR_PDU){	//Í¨¹ýTYPEÅÐ¶ÏÊÇ²»ÊÇRAR PDU
	    	// HQ 20140424ÐÞ¸Ä
			//fsm_printf("is RAR PDU data packet\n");//testing code
			if(true==SV(WaitforRAresponseTimer.flag)){ //Èç¹ûRAR½ÓÊÕ¶¨Ê±Æ÷ÈÔÔÚ¼ÆÊ± ÔòÍ£Ö¹¸Ã¶¨Ê±Æ÷ ²¢´¦ÀíRAR  
				fsm_schedule_cancel(SV(WaitforRAresponseTimer.timer_sign));
				SV(WaitforRAresponseTimer.flag)=false;
				SV(WaitforRAresponseTimer.timer_sign)=NULL;	//20140626¸Ä//timer_signÊÇÖ¸Õë
		    
				if(decomplexRarPdu(skb)==true ) //³É¹¦½ÓÊÕRAR
					fsm_schedule_self(0,RARrev_Success);
				else 
					fsm_schedule_self(0,RandomAcc_Fail);

			}
			else { //½ÓÊÕÒÑ³¬£¬½ÓÊÕ´°¿Ú¹Ø±Õ£¬²»´¦ÀíÊÕµ½µÄRAR
			
				SV(lost_pkt_num_downlink)=SV(lost_pkt_num_downlink)+1;	//for test
				
			}
			fsm_pkt_destroy(skb);//¶ª°ü
			fsm_printf("decomplex for RAR function done\n");//testing code
			fsm_mem_free(m_15bit_subhead);
	   		fsm_mem_free(m_7bit_subhead);
	   		fsm_mem_free(m_padding_subhead);
	   		fsm_mem_free(m_content_resolution);
			fsm_mem_free(m_time_advance);
	   		fsm_mem_free(m_rlc_type2_icimsg);
	   		fsm_mem_free(m_phy_ici);
			fsm_mem_free(m_fixed_subhead);
			FOUT; 
		//ÐÞ¸Ä½áÊø
		}

		if(m_type==DL_PDU){	//Í¨¹ýTYPEÅÐ¶ÏÊÇ²»ÊÇDL_PDU
			Pdcch_c_rnti(m_phy_ici->rnti);
	   		
			fsm_printf("recieve DL_PDU data packet\n");//testing code
			while(continue_flag==1)
			{
				len=sizeof(MAC_SH_padding);
				fsm_mem_cpy(m_padding_subhead,skb->data+from_len,len);	//m_padding_subhead¾ÍÊÇ¿ØÖÆµ¥Ôª×ÓÍ·
				continue_flag=m_padding_subhead->m_lcid_e_r_r>>5;
				lcid=(m_padding_subhead->m_lcid_e_r_r)&31;
				numb++;
				fsm_printf("[UE MAC]lcid:%d\n",lcid);
				switch(lcid){
					case CONTENTION_RESOLUTION_LCID:	//20140428 ¸Ä
						if(SV(CRTimer.flag)==true){  //¶¨Ê±Æ÷Ã»ÓÐ³¬Ê± 	
							fsm_schedule_cancel(SV(CRTimer.timer_sign));  //Í£Ö¹CR¶¨Ê±Æ÷  HQ 20140424ÐÞ¸Ä
							SV(CRTimer.flag)=false;				//20140626 warning!!!!!ÕâÀï»áËÀ»ú
							SV(CRTimer.timer_sign)=NULL;		//20140626¸Ä//timer_signÊÇÖ¸Õë
							len=sizeof(MAC_SDU_subhead_last);
							fsm_mem_cpy(m_fixed_subhead,skb->data+from_len,len);	//È¡³öÍ·²¿
							fsm_printf("[HEXI]DECOMPLEX:OFFSET OF CONTENTIONRESOLUTION:%d\n",from_len);

							from_len=from_len+len;
							len=sizeof(MAC_CE_content_resolution_identity);
							
							fsm_printf("[HEXI]LENGTH OF HEAD IN DECOMPLEX DL_PDU:%d\n",head_len);
							
							fsm_mem_cpy(m_content_resolution,skb->data+head_len,len);	//È¡³öSDU
							part1=m_content_resolution->m_resolusion_identity_1;
							part2=m_content_resolution->m_resolusion_identity_2;

							fsm_printf("[MAC DECOMPLEX]PRAT1:%d,PART2:%d;ORIGINAL DATA:PART1:%d,PART2:%d\n",part1,part2,SV(m_temp_cr)->m_part_1,SV(m_temp_cr)->m_part_2);

							/*************·Ö¸îÏß*************20150104Áªµ÷Ìí¼ÓµÄ²âÊÔ´úÂë*/
							if(SV(contention_failed_num)!=0)//Áªµ÷Ìí¼ÓµÄ¿ØÖÆ´úÂë
							{							
								SV(contention_failed_num)=SV(contention_failed_num)-1;
								part1=0;//ËæÒâÐ´µÄ¾ºÕù½â¾öµ¥Ôª
								part2=0;
							}
							/**************·Ö¸îÏß*******************/

							if(part1==SV(m_temp_cr)->m_part_1&&part2==SV(m_temp_cr)->m_part_2){
							//	SV(contention_resolution_flag)=true;	//flagÊÇÈ«¾Ö±äÁ¿
								fsm_schedule_self(0, Contention_Success);
								//fsm_printf("[MAC DECOMPLEX]Contention_Success\n");
								
								
								/*
								 *IO_CTRL TO SRIO
								 */
								 fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MactoPHY_RACOMPLETE, NULL, 0);
							}
							else{
								// SV(contention_resolution_flag)=false; 
								
								
								SV(lost_pkt_num_downlink)=SV(lost_pkt_num_downlink)+1;	//for test
				
								
								
								fsm_schedule_self(0, ContentionResolution_Fail);
								fsm_mem_free(m_15bit_subhead);
		   						fsm_mem_free(m_7bit_subhead);
		   						fsm_mem_free(m_padding_subhead);
		   						fsm_mem_free(m_content_resolution);
								fsm_mem_free(m_time_advance);
		   						fsm_mem_free(m_rlc_type2_icimsg);
		   						fsm_mem_free(m_phy_ici);
								fsm_mem_free(m_fixed_subhead);
								FOUT; 
							}
							head_len=head_len+len;
						}
						break;
					case TIMING_ADVANCE_LCID:
						len=sizeof(MAC_SDU_subhead_last);
						fsm_mem_cpy(m_fixed_subhead,skb->data+from_len,len);
						from_len=from_len+len;
						len=sizeof(MAC_CE_time_advance);
						fsm_mem_cpy(m_time_advance,skb->data+head_len,len);
						head_len=head_len+len;
						timing=(m_time_advance->m_r_r_command)&63;

						MACCETA_handle(timing);
						break;
					case DRX_LCID:
						from_len=from_len+len;
						break;
					case PADDING_LCID:
						padding_flag=1;
						from_len=from_len+len;
						break;
					default:
						continue_flag=0;	//Èç¹û²»ÊÇÈÎºÎMAC¿ØÖÆµ¥Ôª£¬ÔòÊÇMAC SDU¶ÔÓ¦µÄ×ÓÍ·£¬ÄÇÃ´Ìø³öÑ­»·½øÐÐÏÂÃæµÄ²Ù×÷
						break;
					
				}		
			}			
		
			if(lcid>=0&&lcid<11){
				continue_flag=1;
				while(continue_flag==1){
					len=sizeof(MAC_SDU_subhead_7bit);
					fsm_mem_cpy(m_7bit_subhead,skb->data+from_len,len);
					continue_flag=m_7bit_subhead->m_lcid_e_r_r>>5;
					lcid=(m_7bit_subhead->m_lcid_e_r_r)&31;
					f_domain=m_7bit_subhead->m_f_l>>7;
					if(f_domain==1){	//15bit×ÓÍ·		20140430¸Ä
						len=sizeof(MAC_SDU_subhead_15bit);
						fsm_mem_cpy(m_15bit_subhead,skb->data+from_len,len);
					
						setMACtoRLC_IciMsg(m_rlc_type2_icimsg,0,lcid);	//ÉèÖÃICIÏûÏ¢	

						from_len=from_len+len;

						sdu_len=(m_15bit_subhead->m_f_l)&127;
						sdu_len=sdu_len<<8;
						sdu_len=sdu_len+m_15bit_subhead->m_l;
						newskb=fsm_pkt_create(sdu_len+sizeof(MACtoRLC_IciMsg)+SKB_REDUN);	//20140626¸Ä //ÈßÓà
						fsm_skb_reserve(newskb,sdu_len);
						//fsm_skb_put(newskb,sdu_len+sizeof(MACtoRLC_IciMsg));

						len=sizeof(MACtoRLC_IciMsg);
						fsm_mem_cpy(newskb->head,m_rlc_type2_icimsg,len);	//Õâ¸ö¶¯×÷¶Ô£
						//fsm_mem_cpy(newskb->data,skb->data+head_len,sdu_len);
						fsm_mem_cpy(fsm_skb_push(newskb,sdu_len),skb->data+head_len,sdu_len);
						head_len=head_len+sdu_len;		//Ö¸ÏòÏÂÒ»¸öSDUµÄ¿ªÊ¼Î»ÖÃ
						//fsm_pkt_send(newskb,STRM_TO_RLC);
						
						fsm_pkt_send(newskb,STRM_TO_IPADP);

						fsm_printf("[HEXI] packet sent to rlc:len:%d\n",newskb->len);
						fsm_octets_print(newskb->data, newskb->len);
					}
					else{		//7bit×ÓÍ·		//20140430¸Ä
						setMACtoRLC_IciMsg(m_rlc_type2_icimsg,0,lcid);
						from_len=from_len+len;
						sdu_len=(m_7bit_subhead->m_f_l)&127;
						newskb=fsm_pkt_create(sdu_len+sizeof(MACtoRLC_IciMsg)+SKB_REDUN);	//20140626¸Ä //ÈßÓà
						fsm_skb_reserve(newskb,sdu_len);
						//fsm_skb_put(newskb,sdu_len+sizeof(MACtoRLC_IciMsg));

						len=sizeof(MACtoRLC_IciMsg);
						fsm_mem_cpy(newskb->head,m_rlc_type2_icimsg,len);

						fsm_mem_cpy(fsm_skb_push(newskb,sdu_len),skb->data+head_len,sdu_len);
						//fsm_mem_cpy(newskb->data,skb->data+head_len,sdu_len);
						head_len=head_len+sdu_len;
						//fsm_pkt_send(newskb,STRM_TO_RLC);

						fsm_pkt_send(newskb,STRM_TO_IPADP);

						fsm_printf("[HEXI] packet sent to rlc:len:%d\n",newskb->len);
						fsm_octets_print(newskb->data, newskb->len);
					}
				}
			}
			
			/*
			 * for test
			 */
			 else{
			 	SV(lost_pkt_num_downlink)=SV(lost_pkt_num_downlink)+1;
			 	
			 	fsm_mem_free(m_15bit_subhead);
   				fsm_mem_free(m_7bit_subhead);
   				fsm_mem_free(m_padding_subhead);
   				fsm_mem_free(m_content_resolution);
				fsm_mem_free(m_time_advance);
   				fsm_mem_free(m_rlc_type2_icimsg);
   				fsm_mem_free(m_phy_ici);
				fsm_mem_free(m_fixed_subhead);
   				fsm_printf("decomplex function done\n");//testing code
				FOUT;
			 }
		}
	}
	
	/*
	 * for test
	 */
	 else{
	 	SV(lost_pkt_num_downlink)=SV(lost_pkt_num_downlink)+1;
	 }
	
   	fsm_mem_free(m_15bit_subhead);
   	fsm_mem_free(m_7bit_subhead);
   	fsm_mem_free(m_padding_subhead);
   	fsm_mem_free(m_content_resolution);
	fsm_mem_free(m_time_advance);
   	fsm_mem_free(m_rlc_type2_icimsg);
   	fsm_mem_free(m_phy_ici);
	fsm_mem_free(m_fixed_subhead);
	fsm_pkt_destroy(skb);
   	fsm_printf("decomplex function done\n");//testing code
	FOUT;
}

/**
 * @functoin: complex MAC PDU into MAC SDU and MAC control elements, and deal with them
 * @param skb: the sk_buff contains MAC PDU from SRIO layer
 */
void complexUeMacPdu(FSM_PKT *skb){  //¸´ÓÃ
	FIN(complexUeMacPdu());
	u32 i,test_len=0;	//Ñ­»·ËùÓÃ
	u16 c_rnti,rnti_to_ici;	//C-RNTIÖµ
	u32 e,lcid ;	//eÖµ,lcidÖµ,
	u32 bsr_flag;	//bsrÊýÄ¿
	u32 *lcg_id,*shortbsr_buf_size;	//Âß¼­ÐÅµÀID£»BSRÖÐbuffer size
	
	u32 len=0,from_len=0,total_len=0,left_len,head_len,f_flag=0,sdu_len,re_len=0;	//»ñÈ¡Ä³¸öµ¥Ôª³¤¶È£¬ÁÙÊ±´æ´¢;Æ«ÒÆÁ¿£»Î´ÓÃ;Í·²¿³¤¶È£»Ñ­»·¼ÌÐø±êÖ¾;Êý¾Ýµ¥ÔªÆ«ÒÆÁ¿
	u32 m_7bit_numb=0,m_15bit_numb=0;	//Ã»ÓÃµ½
	u32 longbsr_buf_sizes[LONG_BSR_SIZE]={0,0,0,0};	//BSRÖÐµÄbuffer size
	bool crnti_flag=false, ph_flag=false,first_flag=true,con_flag=true;	//ÊÇ·ñÓÃcrnti¿ØÖÆµ¥Ôª£»ÊÇ·ñÓÐ¹¦ÂÊ¿ØÖÆµ¥Ôª£»ÊÇ·ñÊÇµÚÒ»¸öµ¥Ôª;ÊÇ·ñ»¹ÓÐ¿Õ¼ä ÄÜÌî¸ü¶à¿ØÖÆµ¥Ôª
	MAC_SDU_subhead_last *m_fixed_subhead=(MAC_SDU_subhead_last*)fsm_mem_alloc(sizeof(MAC_SDU_subhead_last));	//20140430¸Ä
	MAC_SDU_subhead_7bit *m_7bit_subhead=(MAC_SDU_subhead_7bit*)fsm_mem_alloc(sizeof(MAC_SDU_subhead_7bit));	//20140430¸Ä
	MAC_SDU_subhead_15bit *m_15bit_subhead=(MAC_SDU_subhead_15bit*)fsm_mem_alloc(sizeof(MAC_SDU_subhead_15bit));	//20140430¸Ä
	MAC_CE_Crnti *m_crnti=(MAC_CE_Crnti*)fsm_mem_alloc(sizeof(MAC_CE_Crnti));	//20140430¸Ä
	MAC_CE_power_headroom *m_power_headroom=(MAC_CE_power_headroom*)fsm_mem_alloc(sizeof(MAC_CE_power_headroom));	//20140430¸Ä
	MAC_CE_shortBSR *m_short_bsr=(MAC_CE_shortBSR*)fsm_mem_alloc(sizeof(MAC_CE_shortBSR));	//20140430¸Ä
	MAC_CE_longBSR *m_long_bsr=(MAC_CE_longBSR*)fsm_mem_alloc(sizeof(MAC_CE_longBSR));	//20140430¸Ä
	RLCtoMAC_IciMsg *m_rlc_type1_ici=(RLCtoMAC_IciMsg*)fsm_mem_alloc(sizeof(RLCtoMAC_IciMsg));	//20140430¸Ä	//20140430¸Ä
	MACtoPHYadapter_IciMsg *m_phy_ici=(MACtoPHYadapter_IciMsg*)fsm_mem_alloc(sizeof(MACtoPHYadapter_IciMsg));//20140506 HQ
	MacCeListElement_s *m_bsr_infor=(MacCeListElement_s*)fsm_mem_alloc(sizeof(MacCeListElement_s));	//20140430¸Ä
	void *head_backup;
	SV_PTR_GET(mac_sv);

	lcg_id=(u32*)fsm_mem_alloc(sizeof(u32));
	shortbsr_buf_size=(u32*)fsm_mem_alloc(sizeof(u32));
	fsm_mem_set(m_fixed_subhead,0,sizeof(MAC_SDU_subhead_last));	//20140430¸Ä
	fsm_mem_set(m_7bit_subhead,0,sizeof(MAC_SDU_subhead_7bit));		//20140430¸Ä
	fsm_mem_set(m_15bit_subhead,0,sizeof(MAC_SDU_subhead_15bit));		//20140430¸Ä
	fsm_mem_set(m_crnti,0,sizeof(MAC_CE_Crnti));		//20140430¸Ä
	fsm_mem_set(m_power_headroom,0,sizeof(MAC_CE_power_headroom));//20140430¸Ä
	fsm_mem_set(m_short_bsr,0,sizeof(MAC_CE_shortBSR));		//20140430¸Ä
	fsm_mem_set(m_long_bsr,0,sizeof(MAC_CE_longBSR));		//20140430¸Ä
	//fsm_mem_set(m_rlc_type2_ici,0,sizeof(RLC_MAC_IciMsgPB));		//20140430¸Ä
	fsm_mem_set(m_rlc_type1_ici,0,sizeof(RLCtoMAC_IciMsg));		//20140430¸Ä
	fsm_mem_set(m_bsr_infor,0,sizeof(MacCeListElement_s));	//20140430¸Ä
	fsm_mem_set(m_phy_ici,0,sizeof(MACtoPHYadapter_IciMsg)); //20140506
	re_len=skb_headroom(skb);
	head_backup=fsm_mem_alloc(SKB_REDUN+re_len);
	fsm_mem_cpy(head_backup,skb->head,re_len);
	re_len=0;
//20140709 start HQ ÐÞ¸Ä ¹ØÓÚC_RNTI MAC¿ØÖÆµ¥Ôª µÄ¸´ÓÃ 
	
	
	/*
	 * for test
	 */
	SV(pkt_num_uplink)=SV(pkt_num_uplink)+1;

	len=sizeof(RLCtoMAC_IciMsg);
	fsm_mem_cpy(m_rlc_type1_ici,skb->head,len);
	rnti_to_ici=m_rlc_type1_ici->rnti;	//20150120 hexi
	if(skb->data==skb->tail){	//ÎÞSDU,Ö»·¢¿ØÖÆµ¥Ôª
		e=0;
		head_len=0;
		sdu_len=0;
	}
	else
		e=1;	//20131110modified

	total_len=SV(Tbsize_Complex);
	fsm_printf("[COMPLEX]TBSIZE:%d\n",SV(Tbsize_Complex));	
	
	
	left_len=total_len;
/*		left_len=left_len-((skb->tail)-(skb->head));*/
	//left_len=256;
	left_len=1530;
	//fsm_printf("[COMPLEX]THE LENGTH LEFT,TOTAL:%d,%d\n",left_len,total_len);
	
//ÔÚ¸´ÓÃº¯ÊýÍâ£¬½ÓÈë×´Ì¬ÏÂÅÐ¶Ï Êý¾ÝÊÇ·ñÀ´×ÔÓÚCCCH£¬¸üÓÐÒâÒå  HQ 20140709 ÐÞ¸Ä 
/*		else{
		e=1;	//¿ØÖÆµ¥ÔªÖ®ºó£¬Ò»¶¨»¹ÓÐSDU 
		len=sizeof(RLCtoMAC_IciMsg);
		lteMacCcchSend(skb,len);//ÓÐÊý¾Ýµ¥Ôª¼ì²âÓÐÃ»ÓÐccch	20140430¸Ä
	}
*/       
	
	if((skb->tail-skb->data)+m_rlc_type1_ici->len>left_len){
		SV(lost_pkt_num_uplink)=SV(lost_pkt_num_uplink)+1;
		fsm_mem_free(lcg_id);
		fsm_mem_free(shortbsr_buf_size);
		fsm_mem_free(m_fixed_subhead);
		fsm_mem_free(m_7bit_subhead);
		fsm_mem_free(m_15bit_subhead);
		fsm_mem_free(m_crnti);
		fsm_mem_free(m_power_headroom);
		fsm_mem_free(m_short_bsr);
		fsm_mem_free(m_long_bsr);
		fsm_mem_free(m_rlc_type1_ici);
		fsm_mem_free(m_phy_ici);
		fsm_mem_free(m_bsr_infor);
		fsm_mem_free(head_backup);
		clean_CE_tags();// modified by HQ 20140512 
		fsm_printf("complex function done by error!\n");//testing code 
		FOUT;
	}
	

	crnti_flag=lteMacCEC_rntiSend(m_crnti); 	//for test
	ph_flag=lteMacCEPhSend(m_power_headroom);
	bsr_flag=lteMacCEBSRSend(lcg_id,shortbsr_buf_size,longbsr_buf_sizes,LONG_BSR_SIZE);//»ñÈ¡bsr_flag ¸ù¾ÝËüÀ´ÅÐ¶ÏÊÇ·ñ·¢ËÍbsr ÒÔ¼°³¤»¹ÊÇ¶Ìbsr

	if(crnti_flag){
		//fsm_printf("[COMPLEX]C_RNTI CONTROL ELEMENT FOUND!\n");			

		test_len++;
		len=sizeof(MAC_CE_Crnti)+sizeof(MAC_SDU_subhead_last);
		if(left_len>=len&&con_flag){
			re_len=re_len+len;
			left_len=left_len-len;
		}
		else{
			crnti_flag=false;
			con_flag=false;
		}
		
		//re_len=re_len+sizeof(MAC_CE_Crnti)+sizeof(MAC_SDU_subhead_last);
	}
	if(ph_flag){
		//fsm_printf("[COMPLEX]POWER HEADROOM CONTROL ELEMENT FOUND!\n");			

		len=sizeof(MAC_CE_power_headroom)+sizeof(MAC_SDU_subhead_last);
		if(left_len>=len&&con_flag){
			re_len=re_len+len;
			left_len=left_len-len;
		}
		else{
			ph_flag=false;
			con_flag=false;
		}
		//re_len=re_len+sizeof(MAC_CE_power_headroom)+sizeof(MAC_SDU_subhead_last);
	}
	if(bsr_flag==1){
		//fsm_printf("[COMPLEX]SHORT BSR CONTROL ELEMENT FOUND!\n");			

		test_len++;

		len=sizeof(MAC_CE_shortBSR)+sizeof(MAC_SDU_subhead_last);
		if(left_len>=len&&con_flag){
			re_len=re_len+len;
			left_len=left_len-len;
		}
		else{
			bsr_flag=0;
			con_flag=false;
		}
		//re_len=re_len+sizeof(MAC_CE_shortBSR)+sizeof(MAC_SDU_subhead_last);
	}

	//fsm_printf("[COMPLEX]LEFT LENGTH BEFORE LONG BSR:%d\n",left_len);

	if(bsr_flag>1){
	
		test_len++;
	
		if(con_flag)
			fsm_printf("[COMPLEX]LONG BSR CONTROL ELEMENT FOUND!\n");
		else
			fsm_printf("[COMPLEX]CANNOT PUT LONG BSR IN!\n");

		len=sizeof(MAC_CE_longBSR)+sizeof(MAC_SDU_subhead_last);
		if(left_len>=len&&con_flag){

			//fsm_printf("[HEXI]:ENOUGH ROOM TO CONTAIN BSR!\n");

			re_len=re_len+len;
			left_len=left_len-len;
		}
		else{
			//fsm_printf("[HEXI]:NO ENOUGH ROOM TO CONTAIN BSR!\n");

			bsr_flag=0;
			con_flag=false;
		}
		//re_len=re_len+sizeof(MAC_CE_longBSR)+sizeof(MAC_SDU_subhead_last);
	}
	//re_len¼ÓÈë¿ØÖÆµ¥ÔªµÄ³¤¶È;(skb->data-skb->head)±£ÁôÔ­±¾³¤¶È£»(sizeof(MACtoPHYadapter_IciMsg)-sizeof(RLCtoMAC_IciMsg))ICIÐÅÏ¢Ö®¼äµÄ³¤¶È²î
	re_len=re_len+skb->data-skb->head+sizeof(MACtoPHYadapter_IciMsg)-sizeof(RLCtoMAC_IciMsg);
	//fsm_printf("[COMPLEX]THE LENGTH SHOULD BE RESERVED,TOTAL LENGTH OF SK_BUFF:%d,%d\n",re_len,skb->data-skb->head);
	//skb=my_fsm_skb_realloc_headeroom(skb,re_len);
	/*u32 test_lcid,test_rnti;
	RLCtoMAC_IciMsg test_ici;
	fsm_mem_cpy(m_fixed_subhead,skb->head+sizeof(RLCtoMAC_IciMsg),sizeof(MAC_SDU_subhead_last));
	fsm_mem_cpy(&test_ici,skb->head,sizeof(RLCtoMAC_IciMsg));
	test_lcid=m_fixed_subhead->m_lcid_e_r_r&31;
	test_rnti=test_ici.rnti;
	fsm_printf("[HEXI]LCID AND RNTI OF CCCH BEFORE REALLOC:%d %d\n",test_lcid,test_rnti);*/
	skb=fsm_skb_realloc_headeroom(skb,re_len);

	/*fsm_mem_cpy(m_fixed_subhead,(char*)head_backup+sizeof(RLCtoMAC_IciMsg),sizeof(MAC_SDU_subhead_last));
	fsm_mem_cpy(&test_ici,(char*)head_backup,sizeof(RLCtoMAC_IciMsg));
	test_lcid=m_fixed_subhead->m_lcid_e_r_r&31;
	test_rnti=test_ici.rnti;
	fsm_printf("[HEXI]LCID AND RNTI OF CCCH AFTER REALLOC:%d %d\n",test_lcid,test_rnti);*/

	//fsm_printf("[COMPLEX]THE LENGTH SHOULD BE RESERVED:%d,HEADROOM OF SK_BUFF:%d,DATAROOM OF SK_BUFF:%d\n",re_len,skb->data-skb->head,skb->tail-skb->data);
     //²ÎÊýÎªÖ¸Õë£¬µ«ÊÇÃ»ÓÐ³õÊ¼»¯£¬ÕâÊÇ»á³ö´íµÄ HQ 20140502		
	if(ph_flag){	//Ìí¼Ó¿ØÖÆµ¥Ôª
		len=sizeof(MAC_CE_power_headroom);
		m_power_headroom->m_r_r_ph=1;	//FOR TEST
		fsm_mem_cpy(fsm_skb_push(skb,len),m_power_headroom,len);	//½«¿ØÖÆµ¥Ôª²¿·Ö¸´ÖÆµ½NEWSDUÀïÃæ
		//fsm_printf("[HEXI]LENGTH OF THE DATAROOM AFTER ADDING POWER HEADROOM:%d,PUSH LENGTH:%d\n",(skb->tail-skb->data),len);
		//fsm_printf("[COMPLEX]ORIGINAL DATA OF SK_BUFF:%c,ADDING DATA:%c\n",skb,len);
	}
	
	/*if(crnti_flag){
		len=sizeof(MAC_CE_Crnti);
		fsm_mem_cpy(fsm_skb_push(skb,len),m_crnti,len);	//½«¿ØÖÆµ¥Ôª²¿·Ö¸´ÖÆµ½NEWSDUÀïÃæ
		
		fsm_printf("[MAC COMPLEX]CRNTI IN COMPLEX:%d\n",m_crnti->m_crnti);
		
		//fsm_printf("[HEXI]LENGTH OF THE DATAROOM AFTER ADDING C-RNTI:%d\n",(skb->tail-skb->data));
	}*/
	if(bsr_flag!=0){	//ÊÇ·ñ·¢ËÍBSR

		if(bsr_flag==1){
			m_short_bsr->m_lcgid_buffersize=*lcg_id;
			m_short_bsr->m_lcgid_buffersize=m_short_bsr->m_lcgid_buffersize<<6;
			m_short_bsr->m_lcgid_buffersize=m_short_bsr->m_lcgid_buffersize+(*shortbsr_buf_size);
			len=sizeof(MAC_CE_shortBSR);
			fsm_mem_cpy(fsm_skb_push(skb,len),m_short_bsr,len);	//²åÈë¶ÌBSR
			/*if(SV(PeriodicBSRTimer).flag==true && SV(PeriodicBSRTimer).timer_sign!=NULL)
			{
				fsm_schedule_cancel(SV(PeriodicBSRTimer).timer_sign);		
			}
			SV(PeriodicBSRTimer).time_value = SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.periodicBSR_Timer)*100;
			SV(PeriodicBSRTimer).timer_sign=fsm_schedule_self(SV(PeriodicBSRTimer).time_value,PeriodicBSRTimer_Expire);
			SV(PeriodicBSRTimer).flag=true;
			//fsm_printf("[HEXI]LENGTH OF THE DATAROOM AFTER ADDING SHORT BSR:%d\n",(skb->tail-skb->data));
			if(SV(RetxBSRTimer).flag==true && SV(RetxBSRTimer).timer_sign!=NULL)
			{
				fsm_schedule_cancel(SV(RetxBSRTimer).timer_sign);		
			}
			SV(RetxBSRTimer).time_value = SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.retxBSR_Timer)*100;
			SV(RetxBSRTimer).timer_sign = fsm_schedule_self(SV(RetxBSRTimer).time_value,RexBSRTimer_Expire );
			SV(RetxBSRTimer).flag = true; */	
		}
		else{
			//20140626¸Ä

			//fsm_printf("PUT IN THE LONG BSR CE!\n");

			m_long_bsr->m_buffersize1=longbsr_buf_sizes[0];
			m_long_bsr->m_buffersize1=m_long_bsr->m_buffersize1<<2;
			m_long_bsr->m_buffersize1=m_long_bsr->m_buffersize1+(longbsr_buf_sizes[1]&48)>>4;	//buffersize²»¿ÉÄÜ´óÓÚ255
			m_long_bsr->m_buffersize2=(longbsr_buf_sizes[1]&15);
			m_long_bsr->m_buffersize2=m_long_bsr->m_buffersize2<<6;
			m_long_bsr->m_buffersize2=m_long_bsr->m_buffersize2+longbsr_buf_sizes[2];
			m_long_bsr->m_buffersize2=m_long_bsr->m_buffersize2<<6;
			m_long_bsr->m_buffersize2=m_long_bsr->m_buffersize2+longbsr_buf_sizes[3];
			//½áÊø
			//fsm_printf("[COMPLEX]BSR VALUE:%c,%d\n",m_long_bsr->m_buffersize1+65,m_long_bsr->m_buffersize2);

			len=sizeof(MAC_CE_longBSR);
			fsm_mem_cpy(fsm_skb_push(skb,len),m_long_bsr,len);	//²åÈë³¤BSR
			//fsm_printf("[HEXI]LENGTH OF THE DATAROOM AFTER ADDING LONG BSR:%d\n",(skb->tail-skb->data));
			/*if(SV(PeriodicBSRTimer).flag==true && SV(PeriodicBSRTimer).timer_sign!=NULL)
			{
				fsm_schedule_cancel(SV(PeriodicBSRTimer).timer_sign);		
			}
			SV(PeriodicBSRTimer).time_value = SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.periodicBSR_Timer)*100;
			SV(PeriodicBSRTimer).timer_sign = fsm_schedule_self(SV(PeriodicBSRTimer).time_value,PeriodicBSRTimer_Expire);
			SV(PeriodicBSRTimer).flag = true;
			if(SV(RetxBSRTimer).flag==true && SV(RetxBSRTimer).timer_sign!=NULL)
			{
				fsm_schedule_cancel(SV(RetxBSRTimer).timer_sign);		
			}
			SV(RetxBSRTimer).time_value = SV(systemconfigInfo.MACMainConfigInfo.ul_SCH_Config.retxBSR_Timer)*100;
			SV(RetxBSRTimer).timer_sign = fsm_schedule_self(SV(RetxBSRTimer).time_value,RexBSRTimer_Expire );
			SV(RetxBSRTimer).flag = true; */			
		}
		Free_Bsr_Info();		//20140428 ¸Ä //ÊÍ·ÅÖ®Ç°LHLÉú³ÉBSRÊ±·ÖÅäµÄÄÚ´æ
	}
	//fsm_printf("[HEXI]LENGTH OF THE DATAROOM AFTER ADDING CONTROL SUBHEAD:%d\n",(skb->tail-skb->data));
	
	if(crnti_flag){
		len=sizeof(MAC_CE_Crnti);
		fsm_mem_cpy(fsm_skb_push(skb,len),m_crnti,len);	//½«¿ØÖÆµ¥Ôª²¿·Ö¸´ÖÆµ½NEWSDUÀïÃæ
		rnti_to_ici=SV(T_C_RNTI);
		fsm_printf("[MAC COMPLEX]CRNTI IN COMPLEX:%d\n",m_crnti->m_crnti);
		
		//fsm_printf("[HEXI]LENGTH OF THE DATAROOM AFTER ADDING C-RNTI:%d\n",(skb->tail-skb->data));
	}

	len=sizeof(RLCtoMAC_IciMsg);
	head_len=m_rlc_type1_ici->len;
	
	fsm_mem_cpy(m_7bit_subhead,skb->head+len,sizeof(MAC_SDU_subhead_7bit));
	m_7bit_subhead->m_f_l=m_7bit_subhead->m_f_l>>7;
	fsm_printf("THE TYPE OF SDU:%d\n",m_7bit_subhead->m_f_l);
	
	
	test_len+=head_len;
	//fsm_printf("[COMPLEX]THE ORIGINAL LENGTH AND LENGTH OF THE HEADS:%d,%d\n",m_rlc_type1_ici->len,head_len);
	//fsm_printf("[HEXI]LENGTH OF THE DATAROOM AFTER ADDING SDU SUBHEAD:%d\n",(skb->tail-skb->data));
	fsm_skb_push(skb,head_len);		
	fsm_mem_cpy(skb->data,(u8*)head_backup+len,head_len);	//Ìí¼ÓSDUµÄÍ·²¿ÐÅÏ¢µ½data²¿·Ö 	//for test

	/*fsm_mem_cpy(m_fixed_subhead,skb->data,sizeof(MAC_SDU_subhead_last));
	test_lcid=m_fixed_subhead->m_lcid_e_r_r&31;
	fsm_printf("[HEXI]LCID OF CCCH:%d\n",test_lcid);*/
	
	if(bsr_flag!=0){
		first_flag=false;	//±íÊ¾ºóÃæµÄ¿ØÖÆµ¥Ôª¶¼²»ÊÇµÚÒ»¸öÁË
		if(bsr_flag==1){
			lcid=SHORT_BSR;
			m_fixed_subhead->m_lcid_e_r_r=e<<5;
			m_fixed_subhead->m_lcid_e_r_r=m_fixed_subhead->m_lcid_e_r_r+lcid;
			len=sizeof(MAC_SDU_subhead_last);
			fsm_mem_cpy(fsm_skb_push(skb,len),m_fixed_subhead,len);		//²åÈëÍ·²¿
			head_len=head_len+len;			//Ìí¼ÓÁË¶ÌBSR×ÓÍ·ºó£¬Í·²¿³¤¶ÈÔö¼Ó
		}
		else{

			
			//fsm_printf("PUT IN THE LONG BSR HEAD!\n");


			lcid=LONG_BSR;
			m_fixed_subhead->m_lcid_e_r_r=e<<5;
			m_fixed_subhead->m_lcid_e_r_r=m_fixed_subhead->m_lcid_e_r_r+lcid;
			len=sizeof(MAC_SDU_subhead_last);
			fsm_mem_cpy(fsm_skb_push(skb,len),m_fixed_subhead,len);		//²åÈëÍ·²¿
			head_len=head_len+len;
		}
	}
	fsm_mem_set(m_fixed_subhead,0,sizeof(MAC_SDU_subhead_last));	//20140430¸Ä
	if(crnti_flag){
		lcid=27;
		if(first_flag==false){
			e=1;
		}
		else{
			e=0;
			first_flag=false;
		}
		m_fixed_subhead->m_lcid_e_r_r=e<<5;
		m_fixed_subhead->m_lcid_e_r_r=m_fixed_subhead->m_lcid_e_r_r+lcid;
		len=sizeof(MAC_SDU_subhead_last);
		fsm_mem_cpy(fsm_skb_push(skb,len),m_fixed_subhead,len);		//²åÈë×ÓÍ·²¿
		head_len=head_len+len;
	}
	fsm_mem_set(m_fixed_subhead,0,sizeof(MAC_SDU_subhead_last));	//20140430¸Ä
	if(ph_flag){
		lcid=26;
		if(first_flag==false){
			e=1;
		}
		else{
			e=0;
			first_flag=false;
		}
		m_fixed_subhead->m_lcid_e_r_r=(e<<5);
		m_fixed_subhead->m_lcid_e_r_r=m_fixed_subhead->m_lcid_e_r_r+lcid;
		len=sizeof(MAC_SDU_subhead_last);
		fsm_mem_cpy(fsm_skb_push(skb,len),m_fixed_subhead,len);		//²åÈë×ÓÍ·²¿
		head_len=head_len+len;
		
		//fsm_printf("[COMPLEX]PH SUBHED:%c\n",m_fixed_subhead->m_lcid_e_r_r+10);
	}
	//fsm_printf("[HEXI]LENGTH OF THE DATAROOM AFTER ADDING CONTROL ELEMENTS:%d\n",(skb->tail-skb->data));
	
    	setMACtoPHY_IciMsg(m_phy_ici, DLSCH, rnti_to_ici);//Ìî³äMACtoPHYµÄICIÐÅÏ¢ //20140506 HQ
    	fsm_printf("\n[COMPLEX]RNTI TO PHY:%d;RNTI IN RLC:%d\n",m_phy_ici->rnti,m_rlc_type1_ici->rnti);//testing code 
    	fsm_mem_cpy(skb->head,m_phy_ici,sizeof(MACtoPHYadapter_IciMsg));//½«ICI¼ÓÈëµ½sk_bufÍ·²¿//20140506 HQ
    	
    	fsm_printf("[HEXI]TEST_LEN=%d\n",test_len);
    	/*fsm_printf("SKB->DATA:\n");
    	for(i=0;i<5;i++){
    		fsm_printf("%c ",*(skb->data+i)+65);
    	}*/
    	
    	//fsm_octets_print(skb->data,7);
    	
	fsm_pkt_send(skb,STRM_TO_SRIO);		//20140428 ¸Ä
	fsm_printf("[HEXI] packet sent to srio:len:%d\n",skb->len);
	fsm_octets_print(skb->data, skb->len);

	SV(Tbsize_Complex)=0;

	fsm_mem_free(lcg_id);
	fsm_mem_free(shortbsr_buf_size);
	fsm_mem_free(m_fixed_subhead);
	fsm_mem_free(m_7bit_subhead);
	fsm_mem_free(m_15bit_subhead);
	fsm_mem_free(m_crnti);
	fsm_mem_free(m_power_headroom);
	fsm_mem_free(m_short_bsr);
	fsm_mem_free(m_long_bsr);
	fsm_mem_free(m_rlc_type1_ici);
	fsm_mem_free(m_phy_ici);
	fsm_mem_free(m_bsr_infor);
	fsm_mem_free(head_backup);
	clean_CE_tags();// modified by HQ 20140512 
	fsm_printf("complex function done\n");//testing code 

/*fsm_printf("[HEXI]DATA AFTER COMPLEX:\n");
len=skb->tail-skb->data;
fsm_printf("[HEXI]LENGTH OF THE DATAROOM:%d\n",len);
from_len=0;
while(len>from_len){
	fsm_printf("%c,\n",*(skb->data+from_len));
	from_len++;
}
fsm_printf("\n");*/

	FOUT;
}	//¸´ÓÃº¯Êý¡£¸ù¾ÝICIÐÅÏ¢À´Ìí¼Ó¿ØÖÆµ¥Ôª(¶ÔÍâ½Ó¿Ú)
	
/**
 * @function: reset the MAC control element tags
 */
void clean_CE_tags(){	//Çå³ý¿ØÖÆ±êÖ¾
	u32 tag_pos=0;
	SV_PTR_GET(mac_sv);
	FIN(clean_CE_tags());
	for(tag_pos=0;tag_pos<MACCE_ARRAY_size;tag_pos++)
		fsm_mem_set(&SV(MAC_CE_Tags[tag_pos]),0, sizeof(MAC_controlelement_tag));
	FOUT;
}


/************** HeXi end ******************/



