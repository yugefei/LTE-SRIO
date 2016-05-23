#include <linux/if_ether.h>
#include "macfsm.h"
#include "../lte_system.h"
#include "../pkfmt.h"
#include "mac_scheduler.h"
#include"queue_manager.h"



/*
*****************  �������� (static)  *****************
*/
/**** About DATA manage  *****/
static unsigned int GetMcsFromCqi (u16 cqi);
static unsigned int GetNprb(void);
static unsigned int Get_ITbSize(u16 cqi);
static unsigned int Get_Format1C_TbSize(u16 cqi);
static unsigned int Get_Ul_TbSize(u16 cqi,int nprb);
static unsigned int Get_Ul_PerPrb_Datasize(u16 cqi);/* u16 subframe*/
static unsigned int Get_Dl_TbSize (u16 cqi,int nprb);
static unsigned int Get_Dl_PerPrb_Datasize(u16 cqi, u16 subframe);
static int cal_ul_abs(int divisor,int dividend);
static int Cal_usable_ResOfBitmap(u16 cqi,u16 subframe);


/**** About control RNTI  *****/
static void note_tc_rnti(void);
static unsigned short find_type_rnti(u16 receive_rnti);
static unsigned short DoAllocate_Rnti(int m_type_rnti);
void release_bitmap(u16 receive_rnti);

/**** About random access  *****/
static unsigned short Do_ulgrant_rb_assignment(u16 subframe,u16 cqi);
static unsigned int Do_ulgrant_ulDelay(u16 subframe,u16 cqi);
static unsigned int Do_ulgrant_mcs(u16 cqi);
static unsigned int Do_ulgrant_hoppingflag(void);
static unsigned int Do_ulgrant_tpc(void);
static unsigned int Do_ulgrant_cqirequest(void);
static unsigned short Do_Data_of_MacRarPdu_TA(u16 ta);
static unsigned short Do_Data_of_MacRarPdu_BI(u16 subframe,u16 cqi);
static unsigned short Do_Data_of_MacRarPdu_RAPID(u16 rapid);
static unsigned short Do_Data_of_MacRarPdu_tcrnti(void);
static unsigned int Do_DLRAR_RIV(void);


/**** About UL-schedule  *****/
static unsigned int cal_bsrsize(int m_bsr, int type_bsr);
static unsigned int Do_UlDci_format(void);
static unsigned int Do_UlDci_hopping(void);
static unsigned short Do_UlDci_RIV(u16 subframe,u16 cqi,unsigned int bsr);
static unsigned int Do_UlDci_ndi(void);
static unsigned int Do_UlDci_mcs(u16 cqi);
static unsigned int Do_UlDci_tpc(void);
static unsigned int Do_UlDci_cqirequest();
static unsigned int Do_UlDci_Cyclic_shift();
static unsigned int Do_UlDci_dai(void);
static unsigned int Do_Ul_TbSize (u16 cqi,int nprb);


/**** About DL-schedule  *****/
static int Cal_weight_ue(void);
static unsigned int Do_DLDci_RIV(int index);
static unsigned int Do_DlDci_mcs(u16 cqi);
static unsigned int Do_DlDci_ndi(void);
static unsigned int Do_DlDci_rv(void);
static unsigned int Do_DlDci_num_harq(void);
static unsigned int Do_DlDci_tpc(void);
static unsigned int Do_DlDci_dai(void);
static u8  Do_DlDci_cfi(void);

/*
*****************  ����ʵ��   *****************
*/

/*
******************************
->Change Data and time:
->Function:About DATA manage
->Change:
->Details:���漸��������Ҫ��������ݵĴ���ͼ���
->Special:GetNprb()�������ŵ�����ȡֵΪ1.4/3/5/10/15/20����Ϊlinux�ں˲�֧�ָ�����������(int)(1.4)=1.
*******************************
*/
static unsigned int GetMcsFromCqi (u16 cqi)
{
	unsigned int mcs;
	
    FIN(GetMcsFromCqi());
    mcs = McsforCqi[cqi];
    FRET(mcs);
}

static unsigned int GetNprb()
{
	int nprb;

    FIN(GetNprb());
    switch((int)(CHANNEL_BANDWIDTH))
    {
        case 1   : nprb=6 ;break;
        case 3   : nprb=15;break;
        case 5   : nprb=25;break;
        case 10  : nprb=50;break;
        case 15  : nprb=75;break;
        case 20  : nprb=100;break;
        default  :fsm_printf("the channel bandwidth isn't at the correct scope\n");break;
    }
    FRET(nprb);
}
static unsigned int Get_ITbSize(u16 cqi)
{
	unsigned int mcs,itbs;
	
    FIN(Get_ITbSize());
    mcs=GetMcsFromCqi (cqi);
    itbs = Ul_McsToItbsize[mcs];
    FRET(itbs);
}

static unsigned int Get_Ul_TbSize(u16 cqi,int nprb)
{
	unsigned int mcs,itbs;
	
    FIN(Get_Ul_TbSize());
    mcs=GetMcsFromCqi (cqi);
    
    itbs = Ul_McsToItbsize[mcs];
    FRET(TransportBlockSizeTable[nprb - 1][itbs]);
}
//������֡�ּ���ȫ����Դ���ã����������ƺ�������·����ϸ��
static unsigned int Get_Ul_PerPrb_Datasize(u16 cqi)/* u16 subframe*/
{
    unsigned int mcs;
    unsigned int modulation_order;
    unsigned int datasize;

    FIN(Get_Ul_PerPrb_Datasize());
    mcs=GetMcsFromCqi(cqi);
    modulation_order=Ul_ModulationSchemeForMcs[mcs];
	datasize=modulation_order*12*(CPMODE_OFDM*2);

    FRET(datasize);
}
static unsigned int Get_Dl_TbSize(u16 cqi,int nprb)
{
	unsigned int mcs,itbs;

    FIN(Get_Dl_TbSize());
    mcs=GetMcsFromCqi(cqi);
    
    itbs = Dl_McsToItbsize[mcs];
    FRET(TransportBlockSizeTable[nprb - 1][itbs]);
}
static unsigned int Get_Dl_PerPrb_Datasize(u16 cqi, u16 subframe)
{
	unsigned int mcs;
	unsigned int modulation_order;
	unsigned int datasize;

    FIN(Get_Dl_PerPrb_Datasize());    
    mcs=GetMcsFromCqi(cqi);
    modulation_order=Dl_ModulationSchemeForMcs[mcs];
	if(subframe==1 || subframe==6)
		datasize=modulation_order*12*(CPMODE_OFDM*2-CFI_OFDM-SPECIAL_OFDM)-8;//424 ��ȥ������֡ռ�õĲ��֣�����Ҫ��ȥ����RSռ�õ�
    else
		datasize=modulation_order*12*(CPMODE_OFDM*2-CFI_OFDM)-12;//612 ��ȥRSռ�õ�
    FRET(datasize);
}
//�������ֵ���޵�С��������������ͱ�����������̵����ޡ�
static int cal_ul_abs(int divisor,int dividend)
{
	int val;
	FIN(cal_ul_abs());
	if(divisor % dividend != 0)
		val=(int)(divisor / dividend)+1;
	else
		val=(int)(divisor / dividend);

	FRET(val);
}

/*
******************************
->Change Data and time:��һ�� 2014.5.16
->Function:About control RNTI
->Change:������ʵ�ָ�Ϊ���鷽ʽʵ�֣����Ӽ򵥷���
->Details:�ò��ֺ������MAC��RNTI�Ĺ�����Ҫ��msg2����TC-RNTI�ķ��䣬���յ�msg3��ʱ��judge�����жϴӶ���ȡ���գ�������¼�ȵȲ�����
->Special:
*******************************
*/
//0x003D-0041 0x0042-0104	
//rnti�����ʼ��,����ִ��.ĿǰֻȡNUM_RNTI��rnti���Ժ����չ
void init_rnti_array_val()
{
	int i;
	FIN(init_rnti_array_val());
	SV_PTR_GET(mac_sv);
	for(i=0;i<NUM_RNTI;i++)
		{
			SV(rntiarray[i].m_rnti) = i+61;//
			SV(rntiarray[i].Type_rnti) = UNALLOCATED_RNTI;
			SV(tc_rnti_notes[i])= 0;//��ʼ��tcrnti�ļ�¼��
			
		}
	SV(RAR_receive_crnti)=0;//��ʼ��CRNTI���Ƶ�Ԫ�ı�ʶ
	fsm_schedule_self(2000000 , TC_RNTI_CHECK_TIMER);//�����¼���ʱ���趨Ϊ20ms,Ŀ��:����TC-RNTIʱ����20s��TC-RNTI���뱻��������TC-RNTI�ջ�
	FOUT;
}
void init_Bitmap()
{
	int i;
	FIN(init_Bitmap());
	SV_PTR_GET(mac_sv);
	
	for(i=0;i<100;i++)
		{
			SV(prb_bitmap7[i])=0;
			SV(next_prb_bitmap7[i])=0;
			SV(next_prb_bitmap2[i])=0;
			SV(dl_bitmap[i])=0;
		}
	
	FOUT;
}
static void note_tc_rnti()
{
	int i;
	FIN(note_tc_rnti());
	SV_PTR_GET(mac_sv);
	for(i=0;i<NUM_RNTI;i++)
		{
			if(SV(rntiarray[i].Type_rnti) == TC_RNTI)//�����TC-RNTI
				SV(tc_rnti_notes[i])=1;
		}
	FOUT;
}
void delete_overtime_tc_rnti()
{
	int i;
	FIN(delete_overtime_tc_rnti());
	SV_PTR_GET(mac_sv);
	//����������ʱ��
	fsm_schedule_self(2000000 , TC_RNTI_CHECK_TIMER);
	for(i=0;i<NUM_RNTI;i++)
		{
			if( SV(tc_rnti_notes[i])== 1 && SV(rntiarray[i].Type_rnti)==TC_RNTI)//20ms�����������TC-RNTI����tcrnti�ļ�¼���¼Ϊ��tc-rnti
				SV(rntiarray[i].Type_rnti) = UNALLOCATED_RNTI;
		}
	note_tc_rnti();//���¼�¼TC-RNTI״̬
	FOUT;
}

//���ؽ��յ���rnti��Ӧ������
//�����������ã���ȷ��rnti���������ͣ��Ӷ��жϵ�ǰϵͳ����ʲô״̬
static unsigned short find_type_rnti(u16 receive_rnti)
{
	int i;
	FIN(find_rnti());
	SV_PTR_GET(mac_sv);
	for(i=0;i<NUM_RNTI;i++)
		{
			if(SV(rntiarray[i]).m_rnti==receive_rnti)
				FRET(SV(rntiarray[i]).Type_rnti);
		}
	FRET(0);
}

static unsigned short DoAllocate_Rnti(int m_type_rnti)
{
	int i;
	FIN(DoAllocate_Rnti());
	SV_PTR_GET(mac_sv);
		for(i=0;i<NUM_RNTI;i++)
		{
		//07��30�ӣ���������Ŀǰ�������˷���TC-RNTI�����������&&��tc-ranti�ı�����飬��ֹ��20ms��ͬһ��rntiֵ���ظ����䣬����tc-rnti��ʱ����Ĵ���
			if(UNALLOCATED_RNTI==SV(rntiarray[i]).Type_rnti && SV(tc_rnti_notes[i])!=1)
				{
					SV(rntiarray[i]).Type_rnti=m_type_rnti;
					break;
				}
		}
	FRET(SV(rntiarray[i]).m_rnti);
}



//��¼C-RNTI��TC-RNTI->C-RNTI
void convert_TcRntiToCRnti(u16 receive_rnti)
{
	int i;
	FIN(convert_TcRntiToCRnti());
	
	SV_PTR_GET(mac_sv);
	
	for(i=0;i<NUM_RNTI;i++)
		{
			if(receive_rnti==SV(rntiarray[i]).m_rnti)
				{
					if(SV(rntiarray[i]).Type_rnti==UNALLOCATED_RNTI || SV(rntiarray[i]).Type_rnti==CRNTI_TYPE)
						fsm_printf("this value rnti %d isn't TC-RNTI!error!",SV(rntiarray[i]).m_rnti);
					else
						SV(rntiarray[i]).Type_rnti=CRNTI_TYPE;
				}
		}
	//fsm_printf("[Geng]: the function convert_TcRntiToCRnti was exe, it should be happend in send msg4!\n");
	FOUT;
}


void release_bitmap(u16 receive_rnti)
{

}

//���շ����ȥ��rntiֵ
void recall_rnti(u16 receive_rnti)
{
	int i;
	
	FIN(recall_tc_rnti());
	SV_PTR_GET(mac_sv);
	for(i=0;i<NUM_RNTI;i++)
		{
			if(receive_rnti==SV(rntiarray[i]).m_rnti)
				{
					SV(rntiarray[i]).Type_rnti=UNALLOCATED_RNTI;
					break;
				}
		}
	FOUT;
}


void release_UE_rnti(u16 receive_rnti)
{
	recall_rnti(receive_rnti);
	release_bitmap(receive_rnti);
}
//rnti���жϴ��������øú�����������������rntiֵ��ͬʱҲ�����ж�rnti���͵Ĺ��ܡ�

//����:Ҫ�жϵ�rnti
//���:0�����RNTIֵ����1����RNTIΪTC-RNTI��2����RNTIΪC-RNTI��

//GENG 2014/9/11����
int Do_judge_rnti(u16 receive_rnti)
{

    FIN(Do_judge_rnti());
 	SV_PTR_GET(mac_sv);
	if( CRNTI_TYPE== find_type_rnti(receive_rnti) )//C-RNTI
		{
			FRET(2);
//fsm_printf("[Geng]: the type of rnti is C-RNTI\n");					
		}
	if( TC_RNTI==find_type_rnti(receive_rnti) )//TC-RNTI
		{
			
			if( 1==SV(RAR_receive_crnti) )//ͬʱ�����MAC���Ƶ�Ԫ�д���C-RNTI
				{
					recall_rnti(receive_rnti);//����receive_rnti(��TC-RNTI�ջ�)
//fsm_printf("[Geng]: the type of rnti is TC-RNTI, and msg3  have C-RNTI's MAC contorl data \n");
					SV(RAR_receive_crnti)=0;//
				}
			else
			{
				//fsm_printf("[Geng]: the type of rnti is TC-RNTI, and msg3 don't have C-RNTI's MAC contorl data \n");
			}
			FRET(1);	
		}
    if( 0==find_type_rnti(receive_rnti))
    	{
    		//fsm_printf("##error: system hasn't allocated the rnti\n");
			FRET(0);
    	}	
	
}


/*
******************************
->Change Data and time:��һ�� 2014.5.30
->Function:  resoure management 
->Change:����������������϶��в�����ʵ�����е��ȹ���
->Details:
->Special:
*******************************
*/

//���ڼ��prb_bitmap�Ƿ���ʣ����Դ��prb_bitmap2��prb_bitmap7��
//Ŀǰ��Դ�����ԭ����˳����䣬���������ĳ��prb_bitmapλ������0�������������Դ��δ�����䡣
//����:cqi��mac��bitmapӳ������㣬���ǲ�ͬ���ն˵�cqi��ͬ����Ʒ�ʽ���ܲ�ͬ���Ӷ�����ÿ��prb���Գ��ص���������ͬ
static int Cal_usable_ResOfBitmap(u16 cqi,u16 subframe)
{
	int i,remain_res,idle_bit2,idle_bit7;
	FIN(Cal_usable_ResOfBitmap());
	SV_PTR_GET(mac_sv);
	idle_bit2=idle_bit7=0;//���bitmap2��7����ʣ��λ����������0.
	if(subframe==2)
		{
			for(i=0;i<100;i++)
				{
					if(0==SV(next_prb_bitmap2[i]))
						{
							idle_bit2=100-i;
							break;
						}
				}
			for(i=0;i<100;i++)
				{
					if(0==SV(prb_bitmap7[i]))
						{
							idle_bit7=100-i;
							break;
						}
				}
		}
	if(subframe==7)
		{
			for(i=0;i<100;i++)
				{
					if(0==SV(next_prb_bitmap2[i]))
						{
							idle_bit2=100-i;
							break;
						}
				}
			for(i=0;i<100;i++)
				{
					if(0==SV(next_prb_bitmap7[i]))
						{
							idle_bit7=100-i;
							break;
						}
				}
		}
	
			
	remain_res=Get_Ul_PerPrb_Datasize(cqi) * (idle_bit2 + idle_bit7);
	FRET(remain_res);
}
//���prb_bitmap������
//ÿ��֡����һ��
void Reset_Prb_ulBitmap()
{
	int i;
	FIN(Reset_Prb_Bitmap());
	SV_PTR_GET(mac_sv);
	
	for(i=0;i<100;i++)
		{
			SV(prb_bitmap7[i])=SV(next_prb_bitmap7[i]);
			SV(next_prb_bitmap7[i])=0;
			SV(next_prb_bitmap2[i])=0;
		}
	
	FOUT;
}
//ÿ����֡��Ҫ����һ��
void Reset_Prb_dlBitmap()
{
		int i;
	FIN(Reset_prb_dlbitmap());
	SV_PTR_GET(mac_sv);
	
	for(i=0;i<100;i++)
		{
			SV(dl_bitmap[i])=0;
		}
	
	FOUT;
}

/*
******************************
->Change Data and time:��һ�� 2014.5.16 �ڶ��� 2014.5.31 ������ 2014.6.1  ���Ĵ� 2014.6.20
->Function:  About random access
->Change1:����λ�ζ���ulgrant
->Change2:����������û�����RAR_PDU�ķ��ͣ��ı��˷��͸�����ģ��DATA_RAR_PDU�Ľṹ��
->Change3:����rar-DCI��ICI��
->Change4:һ��RARNTI---���RPAID,  ��Do_Data_of_MacRarPdu_ulgrant��������Ϊ�Ѿ������ڴ��ָ��
->Details:
->Special:
*******************************
*/
//Geng flag:ָ���ǲ���DCI0�ĵ��ã������DCI0�ĵ��ã��������ȡֵ�������ı�bitmap״̬
//0:DCI0
static unsigned short Do_ulgrant_rb_assignment(u16 subframe,u16 cqi)
{
	int PerPrb_Datasize,lcrbs,RBstart,Nprb;
	int i,a;
	u16 RIV,rb_assignment;
	

    FIN(Do_ulgrant_rb_assignment());
	SV_PTR_GET(mac_sv);
  
   
    PerPrb_Datasize=Get_Ul_PerPrb_Datasize(cqi);//number of PRB
	lcrbs=cal_ul_abs(SIZE_MSG3,PerPrb_Datasize);//ȡ����ֵ���ޣ��õ�����Ҫ�����PRB����
    
    //a:���ø���ֵ��Ŀ����  �޶�����bitmap�Ĵ���  �������ɹ� a=3 ����ѭ��(��Ϊ��󿼲�����bitmap)
    //������ܵ���ʱ��Ϊ2���������ȿ�����7���䣬��ο����¸�2����֮��ͬ��
    for(a=1;a<3;a++)
    {
        if(2==subframe && 1==a) //�������2��֡���յ�����������
        {
            for(i=0;i<=100-lcrbs;i++)
            {
                if(0==SV(prb_bitmap7[i]))
                {
                    RBstart=i;

						 for(;i<RBstart+lcrbs;i++)
                    	{
                       		 SV(prb_bitmap7[i])=1;
                    	}
						a=3;
                   		 break;
						
                   
                }
            }
            if(i==101-lcrbs)	//���ִ�������漸�е�if��䣬break����Ա�֤ i!=100-lcrbs��
            subframe=7;
    	}

        if(7==subframe && 1==a)//�������7��֡���յ�����������
        {
            for(i=0;i<=100-lcrbs;i++)
            {
                if(0==SV(next_prb_bitmap2[i]))
                {
             		RBstart=i;	
					for(;i<RBstart+lcrbs;i++)
                    	{
                       		 SV(next_prb_bitmap2[i])=1;
                    	}
					a=3;
                   	 break;
				
                }
            }
            if(i==101-lcrbs)
            subframe=2;
        }
	 if(2==subframe && 2==a) //20141018�������7��֡���յ�����������,�����¸�֡��2��֡��Դ���㣬��ʼ�����¸�֡��7��֡��Դ
        {
            for(i=0;i<=100-lcrbs;i++)
            {
                if(0==SV(next_prb_bitmap7[i]))
                {
                  RBstart=i;
//fsm_printf("[Geng]In function Do_ulgrant_rb_assignment:rbstart is-%d;",RBstart);//Geng test 20150109
				
						 for(;i<RBstart+lcrbs;i++)
                    	{
                       		 SV(next_prb_bitmap7[i])=1;
                    	}
						a=3;
                   		 break;
			
                }
            }
            if(i==101-lcrbs)	//���ִ�������漸�е�if��䣬break����Ա�֤ i!=100-lcrbs��
            subframe=7;
    	}
    }
    //Type 2 is a continuous way of resoure allocation.

        Nprb=GetNprb();
    if(lcrbs <= 1 + Nprb/2)         //down limit
    {
        RIV=Nprb*(lcrbs-1)+RBstart;//RIV��ô���?
    }

    else
    {
        RIV=Nprb*(Nprb-lcrbs+1)+(Nprb-1-RBstart);
    }
    //ϵͳĿǰ����Ϊ20MHZ����Ӧ��PRB=100����˲�����PRB��ĿС��44��ʱ������������ݸ�ʽ�ı仯��
    if((Do_ulgrant_hoppingflag()==0))
    {
        rb_assignment=RIV;

    }
    if( (Do_ulgrant_hoppingflag()==1))
    {
    	//����Э���֪��Ƶbit��ĿΪ2�����趨��ƵģʽָʾUE��Ŀǰ�����ƵbitΪ01��01(2bit) 000(b bit) RIV(5 bit)
    	rb_assignment=256 + RIV;
    	
    }
	     //Geng test 20150108
	//fsm_printf("[Geng]In the function Do_ulgrant_rb_assignment:subframe is:%d;	RBstart is:%d;	lcrbs is:%d;	RIV is:%d;\n",subframe,RBstart,lcrbs,RIV);

	FRET(rb_assignment);
}
//Geng uldelay should work before RIV function
static unsigned int Do_ulgrant_ulDelay(u16 subframe,u16 cqi)
{
	int PerPrb_Datasize,lcrbs,RBstart,Nprb;
	int i,a;
	u8 UL_delay;
	u32 flag=1;

    FIN(Do_ulgrant_ulDelay());
	SV_PTR_GET(mac_sv);

    PerPrb_Datasize=Get_Ul_PerPrb_Datasize(cqi);//number of PRB
	lcrbs=cal_ul_abs(SIZE_MSG3,PerPrb_Datasize);//ȡ����ֵ���ޣ��õ�����Ҫ�����PRB����
    //when the predistribution subframe resource isn't enough, delay=1, means the next up subframe resource, and so on.
	a=0;//a�����ú����ĵ�������ͬ
	UL_delay=0;
	
	while(flag)
    {
//fsm_printf("\n\n[Geng] In function Do_ulgrant_ulDelay:::::test if the function is working !!!!!!!!\n\n");

        if(2==subframe)
        {
            for(i=0;i<=100-lcrbs;i++)
            {
                if(0==SV(prb_bitmap7[i]) && 0==a)
                {
                	UL_delay=0;
                	FRET(UL_delay);
                }
                if(0==SV(prb_bitmap7[i]) && 1==a)
                {
                   	UL_delay=1;
                	FRET(UL_delay);
                }
            }
            if(i==101-lcrbs)
            {
                a=a+1;
                subframe=7;
//fsm_printf("[Geng] In function Do_ulgrant_ulDelay, the value of a is:%d\n",a);
//fsm_printf("(PS:happen in subframe is 2\n)");
            }

        }

        if(7==subframe)
        {
            for(i=0;i<=100-lcrbs;i++)
            {
                if(0==SV(next_prb_bitmap2[i]) && 0==a)
                {
                    UL_delay=0;
                	FRET(UL_delay);
                }
                if(0==SV(next_prb_bitmap2[i]) && 1==a)
                {
                    UL_delay=1;
                	FRET(UL_delay);
                }
            }
            if(i==101-lcrbs)
            {
                a=a+1;
                subframe=2;
//fsm_printf("[Geng] In function Do_ulgrant_ulDelay, the value of a is:%d\n",a);
//fsm_printf("(PS:happen in subframe is 7\n)");
            }

        }
	if(a==2)
			{
			//fsm_printf("[Geng] In function Do_ulgrant_ulDelay, there isn't enough resource to allocate!");
			//fsm_printf("(PS:JUST FOR TEST,in normal program if there isn't enough resource, We will not do RAR_schedule!\n)");
			FRET(1);
			}
    }
   
}
static unsigned int Do_ulgrant_mcs(u16 cqi)
{
    FIN(Do_ulgrant_mcs());
    FRET(GetMcsFromCqi(cqi));
}
static unsigned int Do_ulgrant_hoppingflag()
{
    FIN(Do_ulgrant_hoppingflag());
    FRET(0);
}
static unsigned int Do_ulgrant_tpc()
{
    FIN(Do_ulgrant_tpc());
    FRET(0);
}
static unsigned int Do_ulgrant_cqirequest()
{
    //mark the need of cqi;
    FIN(Do_ulgrant_cqirequest());
    FRET(1);
}
static unsigned short Do_Data_of_MacRarPdu_TA(u16 ta)
{
    FIN(Do_Data_of_MacRarPdu_TA());
    FRET(ta);
}
static unsigned short Do_Data_of_MacRarPdu_BI(u16 subframe,u16 cqi)
{
    //
    FIN(Do_Data_of_MacRarPdu_BI());
    if(Do_ulgrant_ulDelay(subframe,cqi)==1)
	{
		FRET(1);
	} 
    else
        FRET(0);//backoff=0;
}
static unsigned short Do_Data_of_MacRarPdu_RAPID(u16 rapid)
{
	
    FIN(Do_Data_of_MacRarPdu_RAPID());
    FRET(rapid);
}
static unsigned short Do_Data_of_MacRarPdu_tcrnti()
{
    FIN(Do_Data_of_MacRarPdu_tcrnti());
    FRET(DoAllocate_Rnti(TC_RNTI));
}
//Competing_Res_Allocation


//����RARPDU�����ݣ������ؽ����������ݵ�ָ��
//DCI������Ϊ֮ǰδ���ǵ�����ʱ��û��д
//HQ modified 20140618 �޸ĺ�������,������Ҫ����ָ�룬�����ڴ������ͷŲ�ƥ��
//�ú�����Ӧ���Ǵ���һ��RA_RNTI����Ӧ�ĵ�RA���󣬿��ܰ������RAPID

//gengcanxi:�ú��������Ҳ��handle_ra_req���������õĶ��У�������Ƕ����е�һ���û�������
//           ���ǿ�����ͬһ��RA-RNTI��Ҳ�п��ܲ���ͬһ��RA-RNTI������ÿ���û�Ӧ��ֻ��һ��RAPID
//             �ú���ֻ�ǲ���һ���û�����Ӧ��RAR��Ϣ���ݣ���������ģ�飬����ģ�鸺�𽫾���
//             ��ͬ��RA-RNTI��MAC RAR��װ��һ��MAC PDU���з��͡���ʱ������˵��һ��RA-RNTI��Ӧ���RAPID
//LHL ��ָ����ʽ���أ��Ͳ���Ҫ����ֵ�ˣ���Ϊ��һ�������ĵ�ַ�����ⲿ�����
//void * Do_Data_of_MacRarPdu_ulgrant(DATA_RAR_PDU * p_rar_pdu, struct S_RAinfo *p_ra_UEinfo,int index

//2014.0916:���ڸ���UE���ŵ����������ͬ������ͬһʱ�����뾺����Դ��UE���������Դ��СӦ�ò�ͬ�������ݲ�����HQ�����ݽṹ
//2014.09.28:indexֵ�ɵ����ߴ��룬ָ��ͬһ��RA-RNTI�û���ʣ��Ҫ������û������ж��ٸ������û���Ϊ1ʱ������ȡ������ͬһ����Դ������Դ
//���ú�������ÿ�λ�δ������û�����index���ɡ�index>=1

void Do_Data_of_MacRarPdu_ulgrant(DATA_RAR_PDU * p_rar_pdu, struct S_RAinfo *p_ra_UEinfo,int index)//����������rapid������?
{
	
	u8 temp_prb_bitmap2[100];
	u8 temp_prb_bitmap7[100];
	int temp_i;
    FIN(Do_Data_of_MacRarPdu_ulgrant());
	SV_PTR_GET(mac_sv);

	for(temp_i=0;temp_i<100;temp_i++)
{
temp_prb_bitmap7[temp_i]=SV(prb_bitmap7[temp_i]);
		temp_prb_bitmap2[temp_i]=SV(next_prb_bitmap2[temp_i]);
}
		
   	p_rar_pdu->s_ulgrant.m_mcs=Do_ulgrant_mcs(p_ra_UEinfo->cqi);

   	p_rar_pdu->s_ulgrant.m_hoppingflag=Do_ulgrant_hoppingflag();
	p_rar_pdu->s_ulgrant.m_ulDelay=Do_ulgrant_ulDelay(p_ra_UEinfo->subframeN,p_ra_UEinfo->cqi);
	
p_rar_pdu->s_ulgrant.rb_assignment=Do_ulgrant_rb_assignment(p_ra_UEinfo->subframeN,p_ra_UEinfo->cqi);
    	p_rar_pdu->s_ulgrant.m_tpc=Do_ulgrant_tpc();
    	p_rar_pdu->s_ulgrant.m_cqiRequest=Do_ulgrant_cqirequest();
	p_rar_pdu->s_ulgrant.emptybits=0;

	p_rar_pdu->m_bi=Do_Data_of_MacRarPdu_BI(p_ra_UEinfo->subframeN,p_ra_UEinfo->cqi);
	p_rar_pdu->m_rapid=Do_Data_of_MacRarPdu_RAPID(p_ra_UEinfo->rapid);
	p_rar_pdu->m_ta=Do_Data_of_MacRarPdu_TA(p_ra_UEinfo->ta);
	p_rar_pdu->m_tcrnti=Do_Data_of_MacRarPdu_tcrnti();
	if(index != 1)
		{
		for(temp_i=0;temp_i<100;temp_i++)
			SV(prb_bitmap7[temp_i])=temp_prb_bitmap7[temp_i];
		for(temp_i=0;temp_i<100;temp_i++)
			SV(next_prb_bitmap2[temp_i])=temp_prb_bitmap2[temp_i];
		}


//fsm_printf("\n[Geng]In the function Do_Data_of_MacRarPdu_ulgrant the value of TC-RNTI is:%d;	RAPID is:%d;	rb_assignment is:%d;	msc is:%d\n",p_rar_pdu->m_tcrnti,p_rar_pdu->m_rapid,p_rar_pdu->s_ulgrant.rb_assignment,p_rar_pdu->s_ulgrant.m_mcs);

	FOUT;

}

//�������������Ӧռ�õ���������С������ͳһ����1��PRB
static unsigned int Do_DLRAR_RIV()
{
	int Nprb,lcrbs,rb_start,i;
	u32 RIV;
	FIN(Do_DLRAR_RIV());
	SV_PTR_GET(mac_sv);
	
	lcrbs=DL_RAR_DATA;
	RIV=0;
	for(i=0;i<=100-lcrbs;i++)
		{
			if(0==SV(dl_bitmap[i]))
			{
				rb_start=i;
				for(; i < rb_start + lcrbs; i++)
				{
					SV(dl_bitmap[i])=1;
				}
				break;
			}
			if(i==99 && 1==SV(dl_bitmap[i]))
				{
					//fsm_printf("the DL resource is full!\n");
					FRET(0);
				}	
		}
	Nprb=GetNprb();
    if(lcrbs <= 1 + Nprb/2)        
    {
        RIV=Nprb*(lcrbs-1)+rb_start;
    }
    else
    {
        RIV=Nprb*(Nprb-lcrbs+1)+(Nprb-1-rb_start);
    }
	//Geng test 20150108
	//fsm_printf("[Geng]In the function Do_DLRAR_RIV RBstart is:%d;	lcrbs is:%d;	RIV is:%d;\n",rb_start,lcrbs,RIV);
	FRET(RIV);

}



int Do_RAR_DCI1A(struct S_RAinfo *ra_UEinfo)
{
	ENBMAC_TO_PHY_Rardci * p_rar_ici_dci;
	
    FIN(Do_RAR_DCI1A());
	
	p_rar_ici_dci=(ENBMAC_TO_PHY_Rardci *)fsm_mem_alloc(sizeof(ENBMAC_TO_PHY_Rardci));

	p_rar_ici_dci->m_rnti				=ra_UEinfo->ra_rnti;
	p_rar_ici_dci->m_tbsize				=Get_Dl_TbSize(ra_UEinfo->cqi,DL_RAR_DATA);
	p_rar_ici_dci->dci_format=DCI1A;
	p_rar_ici_dci->cfi=Do_DlDci_cfi();

	p_rar_ici_dci->rar_dci.m_format			=DCIFORMAT1A;
	p_rar_ici_dci->rar_dci.map_vrb			=LVRB;
	p_rar_ici_dci->rar_dci.m_riv			=Do_DLRAR_RIV();
	p_rar_ici_dci->rar_dci.m_mcs			=Do_DlDci_mcs(ra_UEinfo->cqi);
	p_rar_ici_dci->rar_dci.num_harq			=Do_DlDci_num_harq();
	p_rar_ici_dci->rar_dci.m_ndi			=Do_DlDci_ndi();
	p_rar_ici_dci->rar_dci.m_rv				=Do_DlDci_rv();
	p_rar_ici_dci->rar_dci.m_tpc			=Do_DlDci_tpc();
	p_rar_ici_dci->rar_dci.m_dai			=Do_DlDci_dai();
	p_rar_ici_dci->rar_dci.emptybits		=0;	

	//Test code Geng 20150108
	/*fsm_printf("\n##After Test Do_RAR_DCI1A:");
		fsm_printf("\nSome important paramters are:");
		fsm_printf("  RA-RNTI:%d",p_rar_ici_dci->m_rnti);
		fsm_printf("  dci_format:%d",p_rar_ici_dci->dci_format);
		fsm_printf("  m_tbsize:%d",p_rar_ici_dci->m_tbsize);
		fsm_printf("  m_mcs:%d",p_rar_ici_dci->rar_dci.m_mcs);
		fsm_printf("  RIV:%d",p_rar_ici_dci->rar_dci.m_riv);
		fsm_printf("  m_dai:%d",p_rar_ici_dci->rar_dci.m_dai);
	*/
	fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACTOPHY_RAR_DCI, (void *) p_rar_ici_dci, sizeof(ENBMAC_TO_PHY_Rardci));
	
	fsm_mem_free(p_rar_ici_dci);
	FRET(Cal_usable_ResOfBitmap(ra_UEinfo->cqi,ra_UEinfo->subframeN));  
}


/*//format1Cע��������1A
int Do_RAR_DCI1C(struct S_RAinfo *ra_UEinfo)
{
	ENBMAC_TO_PHY_Rardci * p_rar_ici_dci;
	
    FIN(Do_RAR_DCI());
    p_rar_ici_dci=(ENBMAC_TO_PHY_Rardci *)fsm_mem_alloc(sizeof(ENBMAC_TO_PHY_Rardci));

	p_rar_ici_dci->m_rnti				=ra_UEinfo->ra_rnti;
	p_rar_ici_dci->m_tbsize				=Get_Format1C_TbSize(ra_UEinfo->cqi);//���Ϊʲô�������ģ���RIV�Ƕ�Ӧ����?
	p_rar_ici_dci->dci_format=2;//format 1A
	p_rar_ici_dci->cfi=Do_DlDci_cfi();
	
    p_rar_ici_dci->rar_dci.m_gap				=1;//��δ�ҵ���������ʱʹ��Gap2(Ƶ�����)
    //20141022����Ϊ�������ݣ������û��ǹ̶��ģ��������ϵͳĿǰ��RIV����bitmap���Ӧ��
    //�������������ǰ��UE��δ��ȡC-RNTI������Ϊ�������о�̬���Ƚ��������������ϣ��궨������5���е�һ��RNTI���õ�RIVֵ(5��ֵ����ͬ��)
    p_rar_ici_dci->rar_dci.RIV					=Do_DL_RIV(ra_UEinfo->rapid);
	//�˴���û�и�����ȫ��RIV����Դ����Ӧ�ú����е����й�ϵ
	p_rar_ici_dci->rar_dci.I_TBS				=Get_ITbSize(ra_UEinfo->cqi);
	p_rar_ici_dci->rar_dci.emptybits			=0;
	//Test code Geng 20141027
	fsm_printf("\n##After Test Do_RAR_DCI1C:");
	fsm_printf("\nSome important paramters are:");
	fsm_printf("  RA-RNTI:%d",p_rar_ici_dci->m_rnti);
	fsm_printf("  dci_format:%d",p_rar_ici_dci->dci_format);
	fsm_printf("  m_tbsize:%d",p_rar_ici_dci->m_tbsize);
	fsm_printf("  CFI:%d",p_rar_ici_dci->cfi);
	fsm_printf("  RIV:%d",p_rar_ici_dci->rar_dci.RIV);
	fsm_printf("  m_gap:%d",p_rar_ici_dci->rar_dci.m_gap);
	fsm_printf("  I_TBS:%d\n",p_rar_ici_dci->rar_dci.I_TBS);

	fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACTOPHY_RAR_DCI, (void *) p_rar_ici_dci, sizeof(ENBMAC_TO_PHY_Rardci));
	fsm_mem_free(p_rar_ici_dci);
	FRET(Cal_usable_ResOfBitmap(ra_UEinfo->cqi,ra_UEinfo->subframeN));  
}
*/

int Do_RAR_DCI0(struct S_RAinfo *ra_UEinfo)
{
	//UL_ICI_DCI * p_ul_ici_dci;//LHL 20141011
	ENBMAC_TO_PHY_ULscheduleDCI *p_ul_rar_dci;//LHL 20141011
    FIN(Do_RAR_DCI0());
    p_ul_rar_dci=(ENBMAC_TO_PHY_ULscheduleDCI *)fsm_mem_alloc(sizeof(ENBMAC_TO_PHY_ULscheduleDCI));

	p_ul_rar_dci->m_rnti=ra_UEinfo->ra_rnti;
	p_ul_rar_dci->m_tbsize=Do_Ul_TbSize(ra_UEinfo->cqi,cal_ul_abs(SIZE_MSG3,Get_Ul_PerPrb_Datasize(ra_UEinfo->cqi)));//LHL 20141011,��Ҫ�͹�����
	p_ul_rar_dci->dci_format=DCI0;
	
    p_ul_rar_dci->s_ul_dci.m_format		=Do_UlDci_format();//����format0��format1A
    p_ul_rar_dci->s_ul_dci.m_hopping	=Do_UlDci_hopping();
    p_ul_rar_dci->s_ul_dci.m_riv		=Do_ulgrant_rb_assignment(ra_UEinfo->subframeN, ra_UEinfo->cqi);//��ulgrant�е���Դ������Ӧ���Ǳ���һ�µ�
    p_ul_rar_dci->s_ul_dci.m_ndi		=Do_UlDci_ndi();
    p_ul_rar_dci->s_ul_dci.m_mcs		=Do_UlDci_mcs(ra_UEinfo->cqi);
    p_ul_rar_dci->s_ul_dci.m_tpc		=Do_UlDci_tpc();
    p_ul_rar_dci->s_ul_dci.m_cqiRequest	=Do_UlDci_cqirequest();
    p_ul_rar_dci->s_ul_dci.Cyclic_shift	=Do_UlDci_Cyclic_shift();
    p_ul_rar_dci->s_ul_dci.m_dai		=Do_UlDci_dai();
    p_ul_rar_dci->s_ul_dci.padding		=0;
	p_ul_rar_dci->s_ul_dci.emptybits	=0;
	//Test code Geng 20141027
	/*fsm_printf("\n##After Test Do_RAR_DCI0:");
		fsm_printf("\nSome important paramters are:");
		fsm_printf("  RA-RNTI:%d",p_ul_rar_dci->m_rnti);
		fsm_printf("  dci_format:%d",p_ul_rar_dci->dci_format);
		fsm_printf("  m_tbsize:%d",p_ul_rar_dci->m_tbsize);
		fsm_printf("  m_mcs:%d",p_ul_rar_dci->s_ul_dci.m_mcs);
		fsm_printf("  RIV:%d",p_ul_rar_dci->s_ul_dci.m_riv);
		fsm_printf("  m_dai:%d",p_ul_rar_dci->s_ul_dci.m_dai);
	

	*/
	fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACTOPHY_UL_DCI, (void *) p_ul_rar_dci, sizeof(ENBMAC_TO_PHY_ULscheduleDCI));
	fsm_mem_free(p_ul_rar_dci);
	FRET(Cal_usable_ResOfBitmap(ra_UEinfo->cqi,ra_UEinfo->subframeN));
    
}



/*
******************************
->Change Data and time:��һ�� 2014.5.16 �ڶ��� 2014.5.29 ������ 2014.5.31 ���Ĵ� 2014.6.5 �����2014.06.20
->Function:  About UL-schedule
->Change1:����λ�ζ���UL-DCI
->Change2:����skbuff�ķ�ʽ��ͬʱ�ֿ�����ICI��DCI��������SRIO��
->Change3:����IOCTL�ķ�ʽ�����»ص�֮ǰ�Ķ��壬ֱ������ICI+DCI�������͡�
->Change4:��struct S_UEinfo�Ľṹ�������datasizeof_bsr�������洢��ǰ�����û���bsr��С
->Change5:������Order_Ul_Sched����ֵ��void--->���Ϊint�����ص�ǰbitmapʣ����Դ��
->Details:
->Special:
*******************************
*/
//BSR�Ĵ�������0:��bsr  1:��bsr
static unsigned int cal_bsrsize(int m_bsr, int type_bsr)
{
	u8 short_buffer_size;
	u8 long_buffer_size0,long_buffer_size1,long_buffer_size2,long_buffer_size3;
	unsigned int bsr;
		
	FIN(cal_bsrsize());
	
	if(0==type_bsr)
		{
			short_buffer_size=m_bsr & 0x0000003f;
			bsr=BufferSizeLevelBsrTable[short_buffer_size];
		}
	if(1==type_bsr)
		{
			 long_buffer_size0=m_bsr & 0x00fc0000;
			 long_buffer_size1=m_bsr & 0x0003f000;
			 long_buffer_size2=m_bsr & 0x00000fc0;
			 long_buffer_size3=m_bsr & 0x0000003f;
	
			 bsr=(BufferSizeLevelBsrTable[long_buffer_size0]+BufferSizeLevelBsrTable[long_buffer_size1]+BufferSizeLevelBsrTable[long_buffer_size2]+BufferSizeLevelBsrTable[long_buffer_size3]);
		}
	FRET(bsr);
}

//�����ܹ���bsr�Ĵ�С��������ϴ������ݣ����ӵ�S_UEinfo�Ķ����С�
void Add_sueinfo_Node(PHYtoMAC_Info *temp, int m_bsr, int type_bsr)
{
	struct S_UEinfo * p_ul_UEinfo;
	
    FIN(Add_sueinfo_Node());
    SV_PTR_GET(mac_sv);
	SV(UL_sched_flag) = 1;//20141110 LHL
	//fsm_printf("[Geng]SV(UL_sched_flag):%d\n",SV(UL_sched_flag));
    p_ul_UEinfo=(S_UEinfo *)fsm_mem_alloc(sizeof(S_UEinfo));
    while(p_ul_UEinfo==NULL)//�����ڴ�ʧ��
		p_ul_UEinfo=(S_UEinfo *)fsm_mem_alloc(sizeof(S_UEinfo));
  
	p_ul_UEinfo->datasizeof_bsr		=cal_bsrsize(m_bsr,type_bsr);
	p_ul_UEinfo->rnti				=temp->rnti;
	p_ul_UEinfo->cqi				=temp->cqi;
	p_ul_UEinfo->crc				=temp->crc;
	p_ul_UEinfo->harqindex			=temp->harqindex;
	//p_ul_UEinfo->pgtype				=temp->pgtype;
	p_ul_UEinfo->pmi				=temp->pmi;
	p_ul_UEinfo->sfn				=temp->sfn;
	p_ul_UEinfo->sr					=temp->sr;
	p_ul_UEinfo->subframeN			=temp->subframeN;
	p_ul_UEinfo->ta					=temp->ta;
	//fsm_printf("###BSR_SIZE is:%d",p_ul_UEinfo->datasizeof_bsr);
	//fsm_printf("[Geng]In function Add_sueinfo_Node rnti is:%d\n",p_ul_UEinfo->rnti);
	insert_ULschedQue(SV(ULschedQue_p), p_ul_UEinfo);
	//test_code Geng
	//fsm_printf("\n###finsh inser node!\n");
	FOUT;
}


static unsigned int Do_UlDci_format()
{
    FIN(Do_UlDci_format());
    FRET(0);//format0
}
static unsigned int Do_UlDci_hopping()
{
    FIN(Do_UlDci_hopping());
    FRET(0);
}

static unsigned short Do_UlDci_RIV(u16 subframe,u16 cqi,unsigned int bsr)
{
    int PerPrb_Datasize,lcrbs,RBstart,Nprb;
    int i,a;
    u16 RIV;

    FIN(Do_UlDci_RIV());
	SV_PTR_GET(mac_sv);
    PerPrb_Datasize=Get_Ul_PerPrb_Datasize(cqi);
	lcrbs=cal_ul_abs(bsr,PerPrb_Datasize);//����BSR����������С������prb�ĸ����Ͼ���ֵ

	for(a=1;a<3;a++)
    {
        if(2==subframe)
        {
            for(i=0;i<=100-lcrbs;i++)
            {
                if(0==SV(prb_bitmap7[i]))
                {
                    RBstart=i;
                    for(;i<RBstart+lcrbs;i++)
                    {
                        SV(prb_bitmap7[i])=1;
                    }
                    a=3;
                    break;

                }
            }
            if(i==101-lcrbs)
            subframe=7;
    }

        if(7==subframe)
        {
            for(i=0;i<=100-lcrbs;i++)
            {
                if(0==SV(next_prb_bitmap2[i]))
                {
                    RBstart=i;
                    for(;i<RBstart+lcrbs;i++)
                    {
                        SV(next_prb_bitmap2[i])=1;
                    }
                    a=3;
                    break;
                }
            }
            if(i==101-lcrbs)
            subframe=2;
        }
    }
    Nprb=GetNprb();
    if(lcrbs <= 1 + Nprb/2)        
    {
        RIV=Nprb*(lcrbs-1)+RBstart;
    }
    else
    {
        RIV=Nprb*(Nprb-lcrbs+1)+(Nprb-1-RBstart);
    }
	if(Do_UlDci_hopping()==1)
		{
			//�����Ҫ���ǵ�Ƶ����ô��Ҫ����Դ������������ǰ����bit��������Ƶָʾ��
			//fsm_printf("We need take of the hopping,and change the resource 'bit' allocate");
			
		}
		     //Geng test 20150108
	//fsm_printf("[Geng]In the function Do_UlDci_RIV:subframe is:%d;	RBstart is:%d;	lcrbs is:%d;	RIV is:%d;\n",subframe,RBstart,lcrbs,RIV);
    FRET(RIV);
}
static unsigned int Do_UlDci_ndi()
{
    FIN(Do_UlDci_ndi());
    FRET(0);;
}
static unsigned int Do_UlDci_mcs(u16 cqi)
{
    FIN(Do_UlDci_mcs());
    FRET(GetMcsFromCqi (cqi));
}
static unsigned int Do_UlDci_tpc()
{
    FIN(Do_UlDci_tpc());
    FRET(0);
}
static unsigned int Do_UlDci_cqirequest()
{
    FIN(Do_UlDci_cqirequest());
    FRET(1);
}
static unsigned int Do_UlDci_Cyclic_shift()
{
    FIN(Do_UlDci_Cyclic_shift());
    FRET(0);
}
static unsigned int Do_UlDci_dai()
{
    FIN(Do_UlDci_dai());
	//fsm_printf("[Geng]In function Do_UlDci_dai##Dai=2!!\n");
    FRET(2);//1234
}
static unsigned int Do_Ul_TbSize (u16 cqi,int nprb)
{
    FIN(Do_Ul_TbSize ());
	//fsm_printf("In function Do_Ul_TbSize the TB_size IS:%d\n",Get_Ul_TbSize (cqi,nprb));
    FRET(Get_Ul_TbSize (cqi,nprb));
}
//���е���ָ��:ִ�к󷵻�ʣ����Դ����С
int Order_Ul_Sched(struct S_UEinfo *p_ul_UEinfo)
{
	//UL_ICI_DCI * p_ul_ici_dci;//LHL 20141011
	ENBMAC_TO_PHY_ULscheduleDCI *p_ul_ici_dci;//LHL 20141011
    FIN(Order_Ul_Sched());
    p_ul_ici_dci=(ENBMAC_TO_PHY_ULscheduleDCI *)fsm_mem_alloc(sizeof(ENBMAC_TO_PHY_ULscheduleDCI));

	p_ul_ici_dci->m_rnti=p_ul_UEinfo->rnti;
	p_ul_ici_dci->m_tbsize=Do_Ul_TbSize(p_ul_UEinfo->cqi,cal_ul_abs(p_ul_UEinfo->datasizeof_bsr,Get_Ul_PerPrb_Datasize(p_ul_UEinfo->cqi)));//LHL 20141011,��Ҫ�͹�����



	p_ul_ici_dci->dci_format=DCI0;
	
    p_ul_ici_dci->s_ul_dci.m_format		=Do_UlDci_format();
    p_ul_ici_dci->s_ul_dci.m_hopping	=Do_UlDci_hopping();
    p_ul_ici_dci->s_ul_dci.m_riv			=Do_UlDci_RIV(p_ul_UEinfo->subframeN, p_ul_UEinfo->cqi, p_ul_UEinfo->datasizeof_bsr);
    p_ul_ici_dci->s_ul_dci.m_ndi		=Do_UlDci_ndi();
    p_ul_ici_dci->s_ul_dci.m_mcs		=Do_UlDci_mcs(p_ul_UEinfo->cqi);
    p_ul_ici_dci->s_ul_dci.m_tpc		=Do_UlDci_tpc();
    p_ul_ici_dci->s_ul_dci.m_cqiRequest	=Do_UlDci_cqirequest();
    p_ul_ici_dci->s_ul_dci.Cyclic_shift	=Do_UlDci_Cyclic_shift();
    p_ul_ici_dci->s_ul_dci.m_dai		=Do_UlDci_dai();
    p_ul_ici_dci->s_ul_dci.padding		=0;
	p_ul_ici_dci->s_ul_dci.emptybits	=0;
	//Test code Geng 20141027
	/*fsm_printf("\n##After Test Order_Ul_Sched:");
		fsm_printf("\nSome important paramters are:");
		//fsm_printf("  RNTI:%u",p_ul_ici_dci->m_rnti);
		fsm_printf("  RNTI:%d",p_ul_ici_dci->m_rnti);
		fsm_printf("  dci_format:%u",p_ul_ici_dci->dci_format);
		fsm_printf("  m_tbsize:%u",p_ul_ici_dci->m_tbsize);
		fsm_printf("  m_mcs:%u",p_ul_ici_dci->s_ul_dci.m_mcs);
		fsm_printf("  RIV:%u",p_ul_ici_dci->s_ul_dci.m_riv);
		fsm_printf("  m_dai:%u",p_ul_ici_dci->s_ul_dci.m_dai);
		fsm_printf("  m_dai:%d\n",p_ul_ici_dci->s_ul_dci.m_dai);*/

	
	fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACTOPHY_UL_DCI, (void *) p_ul_ici_dci, sizeof(ENBMAC_TO_PHY_ULscheduleDCI));
	fsm_mem_free(p_ul_ici_dci);
	FRET(Cal_usable_ResOfBitmap(p_ul_UEinfo->cqi,p_ul_UEinfo->subframeN));
    
}

/*
******************************
->Change Data and time:��һ�� 2014.5.16 �ڶ��� 2014.5.29 ������ 2014.5.31
->Function:  About UL-schedule
->Change1:����λ�ζ���DL-DCI
->Change2:����skbuff�ķ�ʽ��ͬʱ�ֿ�����ICI��DCI��������SRIO��ͬʱ�����ṹ��result_sched_algorithm�����澲̬���ȵķ��䷽��
->Change3:����IOCTL�ķ�ʽ�����»ص�֮ǰ�Ķ��壬ֱ������ICI+DCI�������͡�
->Details:
->Special:
*******************************
*/
//���е����㷨���õ������ȵ��û��������ȼ���ͬʱ������Դ���䷽����
//Ŀǰ���ϵͳ��ʹ�ù̶�����ķ�ʽ��5�������û�
//schedule_scheme����Ϊȫ�ֱ�������������Ŀǰ�ľ�̬���ȷ�����
//bitmap:32bit��ȡǰ��25bitΪ��Чλ������ȫ��������25bit��ÿ���û�ռbitmap��5��bit

//PS:��Ҫ��һ����ȡ�û������ĺ���
//�ڱ�����ȷ����ǰ�û������ж�Ӧ��ЩRNTI����ȷ�����Ǿ����������֡�ź���֡�ţ�ÿ��RNTI�Ŀɳ��ص���������С

static int Cal_weight_ue()
{
	int weight,rnti;
	
	FIN(Cal_weight_ue());
	SV_PTR_GET(mac_sv);

	weight=1;//�������в��ù�ƽ����ÿ���û������ȼ���ͬ���������Ը���CQI����ͬҵ��ȸı����ȼ�.
	FRET(weight);
}


//���һ���û�������Դ���䣬�ɹ�����1��ʧ�ܷ���0
//��ע:�˴���num_ueָ����RLC���������ݷ��͵�UE��������indexָ��ÿ���û�i�����
int Do_sched_algorithm(u16 rnti, int num_ue, int index)//��ע���˴���num_ueָ����RLC���������ݷ��͵�ue�ĸ���
{
	int i,percentage;
	static int rest_re_lcrb;//����
	FIN(Do_sched_algorithm());
	SV_PTR_GET(mac_sv);

	SV(schedule_scheme[index]).m_rnti=rnti;
	
	
	for(i=0;i<100;i++)
		{
			if(0==SV(dl_bitmap[i]) && index==0)
				{
					rest_re_lcrb=100-i;
					break;
				}
			if(index!=0)
				break;
		}
	//fsm_printf("In Do_Sched_algorithm the lcrb of rest is:%d\n",rest_re_lcrb);
	if(index==num_ue-1)
		SV(schedule_scheme[index]).lcrbs=rest_re_lcrb-(rest_re_lcrb/num_ue)*(num_ue-1);
	else
		SV(schedule_scheme[index]).lcrbs=rest_re_lcrb/num_ue*Cal_weight_ue();//����Ϊ��ʾ
	for(i=0;i<=100-SV(schedule_scheme[index]).lcrbs;i++)
       {
          if(0==SV(dl_bitmap[i]))
            {
               SV(schedule_scheme[index]).rb_start=i;
               for(;i<SV(schedule_scheme[index]).rb_start+SV(schedule_scheme[index]).lcrbs;i++)
			   	{
                  SV(dl_bitmap[i])=1;
                }
                   break;
            }
			if(1==SV(dl_bitmap[i])&& i == 100-SV(schedule_scheme[index]).lcrbs)
				FRET(0);//û���㹻����Դ������0
        }

			
	SV(schedule_scheme[index]).tbsize=Get_Dl_TbSize(DL_CQI,SV(schedule_scheme[index]).lcrbs);
		//��ǰ������֡
			
			if(SV(phy_to_mac_frame).subframeN!=0 && SV(phy_to_mac_frame).subframeN != 5 &&SV(phy_to_mac_frame).subframeN <=7)
				{	
					SV(schedule_scheme[index]).sfn=SV(phy_to_mac_frame).sfn;
					SV(schedule_scheme[index]).subframeN=SV(phy_to_mac_frame).subframeN+DL_TA;
				}
			else if(SV(phy_to_mac_frame).subframeN>7)
				{
					SV(schedule_scheme[index]).sfn=SV(phy_to_mac_frame).sfn+1;
					SV(schedule_scheme[index]).subframeN=SV(phy_to_mac_frame).subframeN+DL_TA-10;
				}
			else
				{
					SV(schedule_scheme[index]).sfn=SV(phy_to_mac_frame).sfn;
					SV(schedule_scheme[index]).subframeN=SV(phy_to_mac_frame).subframeN+1+DL_TA;
				}
		//���Ǽ�ȥ����PBCH���ŵ���ռ��Դ��������datasize�����Է�����Щ�ŵ�������PRB47-52��
			if(SV(schedule_scheme[index]).rb_start+SV(schedule_scheme[index]).lcrbs-1<47  || 52<SV(schedule_scheme[index]).rb_start)
				{
					SV(schedule_scheme[index]).m_data_size=((SV(schedule_scheme[index]).lcrbs)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[index]).subframeN)/8);
				}
			else
				{
				//����������PRB����ÿ���û�ռ�˶��ٸ����õ��ٷ�ֵ
					if(SV(schedule_scheme[index]).rb_start<47)
								{
									if(SV(schedule_scheme[index]).rb_start+SV(schedule_scheme[index]).lcrbs-1<52)
										percentage=(SV(schedule_scheme[index]).rb_start+SV(schedule_scheme[index]).lcrbs-47)*100/6;//��ֹС�����ں˲�֧�ָ�����
									if(SV(schedule_scheme[index]).rb_start+SV(schedule_scheme[index]).lcrbs-1>=52)
										percentage=100;
								}
					if(SV(schedule_scheme[index]).rb_start>=47)
								{
									if(SV(schedule_scheme[index]).rb_start+SV(schedule_scheme[index]).lcrbs-1<52)
										percentage=SV(schedule_scheme[index]).lcrbs*100/6;
									if(SV(schedule_scheme[index]).rb_start+SV(schedule_scheme[index]).lcrbs-1>=52)
										percentage=(52-SV(schedule_scheme[index]).rb_start+1)*100/6;
								}
				//���ݰٷ�ֵ�Ͳ�ͬ����֡������������
					if(SV(schedule_scheme[index]).subframeN == 0)
						SV(schedule_scheme[index]).m_data_size=(((SV(schedule_scheme[index]).lcrbs)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[index]).subframeN)-(PBCH_OFDM+SSCH_OFDM)*percentage/100)/8);
					else if(SV(schedule_scheme[index]).subframeN == 1 || SV(schedule_scheme[index]).subframeN == 6)
						SV(schedule_scheme[index]).m_data_size=(((SV(schedule_scheme[index]).lcrbs)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[index]).subframeN)-PSCH_OFDM*percentage/100)/8);
					else if(SV(schedule_scheme[index]).subframeN == 5)
						SV(schedule_scheme[index]).m_data_size=(((SV(schedule_scheme[index]).lcrbs)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[index]).subframeN)-SSCH_OFDM*percentage/100)/8);
					else
						SV(schedule_scheme[index]).m_data_size=((SV(schedule_scheme[index]).lcrbs)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[index]).subframeN)/8);
				}

			FRET(1);
			
			/*ע�Ͳ����ǹ̶�5���û�������
			if(i != 2)//UE1UE2UE4UE5
				{
					//SV(schedule_scheme[i]).m_bitmap=bitmap[i];
					SV(schedule_scheme[i]).m_rnti=i+61;//20141017��������:���������Ҫ��5�û�rntiΪ61-65
					SV(schedule_scheme[i]).m_data_size=((5*4)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[i]).subframeN)/8);//1060,1530
				}
			else//UE3��PRB47-52��PBCH��PSCH�ŵ�ռ�����ŵ���Դ����Ҫ�����ȥ
				{
				if(SV(schedule_scheme[i]).subframeN == 0)
					SV(schedule_scheme[i]).m_data_size=(((5*4)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[i]).subframeN)-PBCH_OFDM-SSCH_OFDM)/8);//1488
				else if(SV(schedule_scheme[i]).subframeN == 1 &&SV(schedule_scheme[i]).subframeN == 6)
					SV(schedule_scheme[i]).m_data_size=(((5*4)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[i]).subframeN)-PSCH_OFDM)/8);//1051
				else if(SV(schedule_scheme[i]).subframeN == 5)
					SV(schedule_scheme[i]).m_data_size=(((5*4)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[i]).subframeN)-SSCH_OFDM)/8);//1521
				else
					SV(schedule_scheme[i]).m_data_size=((5*4)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[i]).subframeN)/8);//1060
				//SV(schedule_scheme[i]).m_bitmap=bitmap[i];
				SV(schedule_scheme[i]).m_rnti=i+61;//20141017��������:���������Ҫ��5�û�rntiΪ61-65
				}
			*/

}
//����rnti��ֵ�����ظ�rntiֵ��Ӧ����������������Ͱʹ��byte
int Do_cal_datasize(int index)
{
	
	FIN(Do_cal_datasize());
	SV_PTR_GET(mac_sv);


	FRET(SV(schedule_scheme[index]).m_data_size);//modified by lhl û��ƥ���RNTI������0
}

	
//���һ���û�������Դ���䣬�ɹ�����1��ʧ�ܷ���0
//��ע:�˴���num_ueָ����RLC���������ݷ��͵�UE��������indexָ��ÿ���û�i�����
static unsigned int Do_DLDci_RIV(int index)
{
    int lcrbs,RBstart,Nprb;
    int i;
    u32 RIV;

    FIN(Do_UlDci_RIV());
	SV_PTR_GET(mac_sv);

	//ĿǰԤ��10��rntiֵ��
	lcrbs=SV(schedule_scheme[index]).lcrbs;
	RBstart=SV(schedule_scheme[index]).rb_start;
	Nprb=GetNprb();

	if(lcrbs <= 1 + Nprb/2)        
    {
        RIV=Nprb*(lcrbs-1)+RBstart;
    }
    else
    {
        RIV=Nprb*(Nprb-lcrbs+1)+(Nprb-1-RBstart);
    }
	if(Do_UlDci_hopping()==1)
		{
			//�����Ҫ���ǵ�Ƶ����ô��Ҫ����Դ������������ǰ����bit��������Ƶָʾ��
			//fsm_printf("We need take of the hopping,and change the resource 'bit' allocate");
			
		}
    FRET(RIV);
}

static unsigned int Do_DlDci_mcs(u16 cqi)
{
    FIN(Do_DlDci_mcs());
    FRET(McsforCqi[cqi]);//
}
static unsigned int Do_DlDci_ndi()
{
    FIN(Do_DlDci_ndi());
    FRET(0);//
}
static unsigned int Do_DlDci_rv()
{
    FIN(Do_DlDci_rv());
    FRET(0);//�ӿ��ĵ�
}
static unsigned int Do_DlDci_num_harq()
{
    FIN(Do_DlDci_num_harq());
    FRET(0);//
}
static unsigned int Do_DlDci_tpc()
{
    FIN(Do_DlDci_tpc());
    FRET(0);//
}
static unsigned int Do_DlDci_dai()
{
    FIN(Do_DlDci_dai());
    FRET(2);//1234
}



static u8  Do_DlDci_cfi()
{
	FIN(Do_DlDci_cfi ());
	FRET(1);
}

//��������:����DCI�����������������
//��������: �й�RLCREQ��buffer��
//�����е��Ⱥ���Order_Dl_Sched()���á�


void Order_Dl_Sched(RLC_Request *mac_buffer,int num_ue, int index)
{
	
	ENBMAC_TO_PHY_DLscheduleDCI * p_dl_ici_dci;
	
    FIN(Order_Dl_Sched());
	SV_PTR_GET(mac_sv);
    p_dl_ici_dci=(ENBMAC_TO_PHY_DLscheduleDCI *)fsm_mem_alloc(sizeof(ENBMAC_TO_PHY_DLscheduleDCI));

	p_dl_ici_dci->s_dl_dci.m_format			=DCIFORMAT1A;
	p_dl_ici_dci->s_dl_dci.map_vrb			=LVRB;
	p_dl_ici_dci->s_dl_dci.m_riv			=Do_DLDci_RIV(index);
	p_dl_ici_dci->s_dl_dci.m_mcs			=Do_DlDci_mcs(DL_CQI);
	p_dl_ici_dci->s_dl_dci.num_harq			=Do_DlDci_num_harq();
	p_dl_ici_dci->s_dl_dci.m_ndi			=Do_DlDci_ndi();
	p_dl_ici_dci->s_dl_dci.m_rv				=Do_DlDci_rv();
	p_dl_ici_dci->s_dl_dci.m_tpc			=Do_DlDci_tpc();
	p_dl_ici_dci->s_dl_dci.m_dai			=Do_DlDci_dai();
	p_dl_ici_dci->s_dl_dci.emptybits		=0;

	p_dl_ici_dci->m_rnti=mac_buffer->rnti;
	p_dl_ici_dci->m_tbsize=Get_Dl_TbSize(DL_CQI,SV(schedule_scheme[index]).lcrbs);
	p_dl_ici_dci->dci_format=DCI1A;
	p_dl_ici_dci->cfi=Do_DlDci_cfi();//modified LHL 20141011
/*
	fsm_printf("[Geng]Order_Dl_Sched RNTI:%d\n",p_dl_ici_dci->m_rnti);
	fsm_printf("[Geng]Order_Dl_Sched m_tbsize:%d\n",p_dl_ici_dci->m_tbsize);
	fsm_printf("[Geng]Order_Dl_Sched RIV:%d\n",p_dl_ici_dci->s_dl_dci.m_riv);
	fsm_printf("[Geng]Order_Dl_Sched MCS:%d\n",p_dl_ici_dci->s_dl_dci.m_mcs);
	*/
	fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACTOPHY_DL_DCI, (void *) p_dl_ici_dci, sizeof(ENBMAC_TO_PHY_DLscheduleDCI));
	fsm_mem_free(p_dl_ici_dci);
	FOUT;
}



