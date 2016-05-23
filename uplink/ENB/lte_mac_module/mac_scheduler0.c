#include <linux/if_ether.h>
#include "macfsm.h"
#include "../lte_system.h"
#include "../pkfmt.h"
#include "mac_scheduler.h"
#include"queue_manager.h"



/*
*****************  函数声明 (static)  *****************
*/
/**** About DATA manage  *****/
static unsigned int GetMcsFromCqi (u16 cqi);
static unsigned int GetNprb();
static unsigned int Get_ITbSize(u16 cqi);
static unsigned int Get_Format1C_TbSize(u16 cqi);
static unsigned int Get_Ul_TbSize(u16 cqi,int nprb);
static unsigned int Get_Ul_PerPrb_Datasize(u16 cqi);/* u16 subframe*/
static unsigned int Get_Dl_TbSize (u16 cqi,int nprb);
static unsigned int Get_Dl_PerPrb_Datasize(u16 cqi, u16 subframe);
static int cal_ul_abs(int divisor,int dividend);
static int Cal_usable_ResOfBitmap(u16 cqi,u16 subframe);


/**** About control RNTI  *****/
static void note_tc_rnti();
static unsigned short find_type_rnti(u16 receive_rnti);
static unsigned short convert_rapid_rnti(u16 RAPID);
static unsigned short DoAllocate_Rnti(int m_type_rnti);
static unsigned short Simple_System_Allocate_Rnti(int m_type_rnti,u16 RAPID);
static void recall_rnti(u16 receive_rnti);



/**** About random access  *****/
static unsigned short Do_ulgrant_rb_assignment(u16 subframe,u16 cqi);
static unsigned int Do_ulgrant_ulDelay(u16 subframe,u16 cqi);
static unsigned int Do_ulgrant_mcs(u16 cqi);
static unsigned int Do_ulgrant_hoppingflag();
static unsigned int Do_ulgrant_tpc();
static unsigned int Do_ulgrant_cqirequest();
static unsigned short Do_Data_of_MacRarPdu_TA(u16 ta);
static unsigned short Do_Data_of_MacRarPdu_BI(u16 subframe,u16 cqi);
static unsigned short Do_Data_of_MacRarPdu_RAPID(u16 rapid);
static unsigned short Do_Data_of_MacRarPdu_tcrnti(u16 rapid);
static unsigned int Do_DL_RIV(u16 rapid);


/**** About UL-schedule  *****/
static unsigned int cal_bsrsize(int m_bsr, int type_bsr);
static unsigned int Do_UlDci_format();
static unsigned int Do_UlDci_hopping();
static unsigned short Do_UlDci_RIV(u16 subframe,u16 cqi,unsigned int bsr);
static unsigned int Do_UlDci_ndi();
static unsigned int Do_UlDci_mcs(u16 cqi);
static unsigned int Do_UlDci_tpc();
static unsigned int Do_UlDci_cqirequest();
static unsigned int Do_UlDci_Cyclic_shift();
static unsigned int Do_UlDci_dai();
static unsigned int Do_Ul_TbSize (u16 cqi,int nprb);


/**** About DL-schedule  *****/
static unsigned int Do_DlDci_bitmap(u16 rnti);
static unsigned int Do_DlDci_resAlloc();
static unsigned int Do_DlDci_mcs(u16 cqi);
static unsigned int Do_DlDci_ndi();
static unsigned int Do_DlDci_rv();
static unsigned int Do_DlDci_harqProcess();
static unsigned int Do_DlDci_tpc();
static unsigned int Do_DlDci_dai();
static unsigned int Do_Dl_TbSize (u16 rnti);
static u8  Do_DlDci_cfi();

/*
*****************  函数实现   *****************
*/

/*
******************************
->Change Data and time:
->Function:About DATA manage
->Change:
->Details:下面几个函数主要是完成数据的处理和计算
->Special:GetNprb()函数，信道带宽取值为1.4/3/5/10/15/20，因为linux内核不支持浮点数，所以(int)(1.4)=1.
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
static unsigned int Get_Format1C_TbSize(u16 cqi)
{
	unsigned int itbs;
	
    FIN(Get_Format1C_TbSize());
    itbs=Get_ITbSize (cqi);
    FRET(TBSizeTableofFormat1c[itbs]);
   
}

static unsigned int Get_Ul_TbSize(u16 cqi,int nprb)
{
	unsigned int mcs,itbs;
	
    FIN(Get_Ul_TbSize());
    mcs=GetMcsFromCqi (cqi);
    
    itbs = Ul_McsToItbsize[mcs];
    FRET(TransportBlockSizeTable[nprb - 1][itbs]);
}
//上行子帧现假设全部资源可用，待物理层设计好上行链路后再细化
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
		datasize=modulation_order*12*(CPMODE_OFDM*2-CFI_OFDM-SPECIAL_OFDM)-8;//424 除去特殊子帧占用的部分，还需要减去天线RS占用的
    else
		datasize=modulation_order*12*(CPMODE_OFDM*2-CFI_OFDM)-12;//612 减去RS占用的
    FRET(datasize);
}
//计算绝对值上限的小函数，输入除数和被除数，输出商的上限。
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
->Change Data and time:第一次 2014.5.16
->Function:About control RNTI
->Change:由链表实现改为数组方式实现，更加简单方便
->Details:该部分函数完成MAC层RNTI的管理，主要有msg2进行TC-RNTI的分配，接收到msg3的时候judge函数判断从而采取回收，升级记录等等操作。
->Special:
*******************************
*/
//0x003D-0041 0x0042-0104	
//rnti数组初始化,尽早执行.目前只取NUM_RNTI个rnti，以后可扩展
void init_rnti_array_val()
{
	int i;
	FIN(init_rnti_array_val());
	SV_PTR_GET(mac_sv);
	for(i=0;i<NUM_RNTI;i++)
		{
			SV(rntiarray[i].m_rnti) = i+61;//20141017耿灿锡改:和下行固定的rnti值分开，从66-265
			SV(rntiarray[i].Type_rnti) = UNALLOCATED_RNTI;
			SV(tc_rnti_notes[i])= 0;//初始化tcrnti的记录表
			
		}
	SV(RAR_receive_crnti)=0;//初始化CRNTI控制单元的标识
	fsm_schedule_self(2000000 , TC_RNTI_CHECK_TIMER);//创建事件，时间设定为20ms,目的:分配TC-RNTI时刻起，20s内TC-RNTI必须被处理，否则TC-RNTI收回
	FOUT;
}
static void note_tc_rnti()
{
	int i;
	FIN(note_tc_rnti());
	SV_PTR_GET(mac_sv);
	for(i=0;i<NUM_RNTI;i++)
		{
			if(SV(rntiarray[i].Type_rnti) == TC_RNTI)//如果是TC-RNTI
				SV(tc_rnti_notes[i])=1;
		}
	FOUT;
}
void delete_overtime_tc_rnti()
{
	int i;
	FIN(delete_overtime_tc_rnti());
	SV_PTR_GET(mac_sv);
	//重新启动定时器
	fsm_schedule_self(2000000 , TC_RNTI_CHECK_TIMER);
	for(i=0;i<NUM_RNTI;i++)
		{
			if( SV(tc_rnti_notes[i])== 1 && SV(rntiarray[i].Type_rnti)==TC_RNTI)//20ms过后，如果存在TC-RNTI且其tcrnti的记录表记录为有tc-rnti
				SV(rntiarray[i].Type_rnti) = UNALLOCATED_RNTI;
		}
	note_tc_rnti();//重新记录TC-RNTI状态
	FOUT;
}

//返回接收到的rnti对应的类型
//可以用来调用，以确认rnti是那种类型，从而判断当前系统处于什么状态
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
}
static unsigned short convert_rapid_rnti(u16 RAPID)
{
	unsigned short rnti;
	FIN(convert_rapid_rnti());
	if(RAPID==1)
		rnti=RNTI_A;
	if(RAPID==2)
		rnti=RNTI_B;
	if(RAPID==3)
		rnti=RNTI_C;
	if(RAPID==4)
		rnti=RNTI_D;
	if(RAPID==5)
		rnti=RNTI_E;
	FRET(rnti);
}
static unsigned short DoAllocate_Rnti(int m_type_rnti)
{
	int i;
	FIN(DoAllocate_Rnti());
SV_PTR_GET(mac_sv);
		for(i=5;i<NUM_RNTI;i++)
		{
		//07、30加，耿灿锡，目前仅考虑了分配TC-RNTI的情况，所以&&了tc-ranti的标记数组，防止在20ms内同一个rnti值被重复分配，引起tc-rnti定时清除的错误
			if(UNALLOCATED_RNTI==SV(rntiarray[i]).Type_rnti && SV(tc_rnti_notes[i])!=1)
				{
					SV(rntiarray[i]).Type_rnti=m_type_rnti;
					break;
				}
		}
	FRET(SV(rntiarray[i]).m_rnti);
}

//输入:需要分配的RNTI的类型,输出:函数分配的RNTI的值.目前,只分配TC-RNTI,故而m_type_rnti取值为1.
static unsigned short Simple_System_Allocate_Rnti(int m_type_rnti,u16 RAPID)
{
	int i,rnti;
	FIN(Simple_System_Allocate_Rnti());
	SV_PTR_GET(mac_sv);
	switch(convert_rapid_rnti(RAPID))
		{
		case RNTI_A:
			{
				if(UNALLOCATED_RNTI==find_type_rnti(RNTI_A))
					{
						SV(rntiarray[0]).Type_rnti=m_type_rnti;
						rnti=RNTI_A;
					}	
				else
					rnti=DoAllocate_Rnti(m_type_rnti);
			}
			break;
		case RNTI_B:
			{
				if(UNALLOCATED_RNTI==find_type_rnti(RNTI_B))
					{
						SV(rntiarray[1]).Type_rnti=m_type_rnti;
						rnti=RNTI_B;
					}
				else
					rnti=DoAllocate_Rnti(m_type_rnti);
			}
			break;
		case RNTI_C:
			{
				if(UNALLOCATED_RNTI==find_type_rnti(RNTI_C))
					{
						SV(rntiarray[2]).Type_rnti=m_type_rnti;
						rnti=RNTI_C;
					}
				else
					rnti=DoAllocate_Rnti(m_type_rnti);
			}
			break;
		case RNTI_D:
			{
				if(UNALLOCATED_RNTI==find_type_rnti(RNTI_D))
					{
						SV(rntiarray[3]).Type_rnti=m_type_rnti;
						rnti=RNTI_D;
					}
				else
					rnti=DoAllocate_Rnti(m_type_rnti);
			}
			break;
		case RNTI_E:
			{
				if(UNALLOCATED_RNTI==find_type_rnti(RNTI_E))
					{
						SV(rntiarray[4]).Type_rnti=m_type_rnti;
						rnti=RNTI_E;
					}
				else
					rnti=DoAllocate_Rnti(m_type_rnti);
			}
			break;
		default:
			{
				rnti=DoAllocate_Rnti(m_type_rnti);
			}
			break;
		}
fsm_printf("[XXX] In Simple_System_Allocate_Rnti function TC-RNTI:%d\n",rnti);
	FRET(rnti);
	
}

//记录C-RNTI，TC-RNTI->C-RNTI
void convert_TcRntiToCRnti(u16 receive_rnti)
{
int i;
	FIN(convert_TcRntiToCRnti());
	
	SV_PTR_GET(mac_sv);
	
	for(i=0;i<NUM_RNTI;i++)
		{
			if(receive_rnti==SV(rntiarray[i]).m_rnti)
				{
					SV(rntiarray[i]).Type_rnti=C_RNTI;
				}
		}
	FOUT;
}

//回收分配出去的rnti值
static void recall_rnti(u16 receive_rnti)
{
	int i;
	
	FIN(recall_tc_rnti());
	SV_PTR_GET(mac_sv);
	for(i=0;i<NUM_RNTI;i++)
		{
			if(receive_rnti==SV(rntiarray[i]).m_rnti)
				{
					SV(rntiarray[i]).Type_rnti=UNALLOCATED_RNTI;
				}
		}
	FOUT;
}
//rnti的判断处理函数，用该函数处理来自物理层的rnti值，同时也具有判断rnti类型的功能。

//输入:要判断的rnti
//输出:0代表该RNTI值出错，1代表RNTI为TC-RNTI，2代表RNTI为C-RNTI。

//GENG 2014/9/11更改
int Do_judge_rnti(u16 receive_rnti)
{

    FIN(Do_judge_rnti());
 	SV_PTR_GET(mac_sv);
	if( C_RNTI == find_type_rnti(receive_rnti) )//C-RNTI
		{
			FRET(2);					
		}
	if( TC_RNTI==find_type_rnti(receive_rnti) )//TC-RNTI
		{
			
			if( 1==SV(RAR_receive_crnti) )//同时，如果MAC控制单元中存在C-RNTI
				{
					recall_rnti(receive_rnti);//将该receive_rnti(即TC-RNTI收回)
					SV(RAR_receive_crnti)=0;//
				}
			else
			{
				fsm_printf("[xxx]: This UE is first access!\n");
			}
			FRET(1);	
		}
    if( 0==find_type_rnti(receive_rnti))
    	{
    		fsm_printf("##error: system hasn't allocated the rnti\n");
			FRET(0);
    	}	
	
}


/*
******************************
->Change Data and time:第一次 2014.5.30
->Function:  resoure management 
->Change:新增两个函数，配合队列操作，实现上行调度管理
->Details:
->Special:
*******************************
*/

//用于检查prb_bitmap是否有剩余资源，prb_bitmap2、prb_bitmap7；
//目前资源分配的原则是顺序分配，即如果发现某个prb_bitmap位不等于0，则代表后面的资源均未被分配。
//输入:cqi，mac层bitmap映射物理层，但是不同的终端的cqi不同则调制方式可能不同，从而导致每个prb可以承载的数据量不同
static int Cal_usable_ResOfBitmap(u16 cqi,u16 subframe)
{
	int i,remain_res,idle_bit2,idle_bit7;
	FIN(Cal_usable_ResOfBitmap());
	SV_PTR_GET(mac_sv);
	idle_bit2=idle_bit7=0;//如果bitmap2和7均无剩余位，则函数返回0.
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
//清空prb_bitmap函数。
//20141018改
void Reset_Prb_Bitmap()
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

/*
******************************
->Change Data and time:第一次 2014.5.16 第二次 2014.5.31 第三次 2014.6.1  第四次 2014.6.20
->Function:  About random access
->Change1:采用位段定义ulgrant
->Change2:由于是逐个用户进行RAR_PDU的发送，改变了发送给复用模块DATA_RAR_PDU的结构。
->Change3:新增rar-DCI和ICI等
->Change4:一个RARNTI---多个RPAID,  且Do_Data_of_MacRarPdu_ulgrant函数参量为已经分配内存的指针
->Details:
->Special:
*******************************
*/

static unsigned short Do_ulgrant_rb_assignment(u16 subframe,u16 cqi)
{
	int PerPrb_Datasize,lcrbs,RBstart,Nprb;
	int i,a;
	u16 RIV,rb_assignment;
	

    FIN(Do_ulgrant_rb_assignment());
	SV_PTR_GET(mac_sv);
   
    PerPrb_Datasize=Get_Ul_PerPrb_Datasize(cqi);//number of PRB
	lcrbs=cal_ul_abs(SIZE_MSG3,PerPrb_Datasize);//取绝对值上限，得到至少要分配的PRB个数
    
    //a:设置该数值的目的是  限定考察bitmap的次数  如果分配成功 a=3 结束循环(因为最大考察两次bitmap)
    //如果接受到的时刻为2，则在首先考虑在7分配，其次考察下个2，反之相同。
    for(a=1;a<3;a++)
    {
        if(2==subframe && 1==a) //如果是在2子帧接收到的上行请求
        {
            for(i=0;i<100-lcrbs;i++)
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
            if(i==100-lcrbs)	//如果执行了上面几行的if语句，break后可以保证 i!=100-lcrbs。
            subframe=7;
    	}

        if(7==subframe && 1==a)//如果是在7子帧接收到的上行请求
        {
            for(i=0;i<100-lcrbs;i++)
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
            if(i==100-lcrbs)
            subframe=2;
        }
		 if(2==subframe && 2==a) //20141018如果是在7子帧接收到的上行请求,并且下个帧的2子帧资源不足，开始分配下个帧的7子帧资源
        {
            for(i=0;i<100-lcrbs;i++)
            {
                if(0==SV(next_prb_bitmap7[i]))
                {
                    RBstart=i;
                    for(;i<RBstart+lcrbs;i++)
                    {
                        SV(next_prb_bitmap7[i])=1;
                    }
					a=3;
                    break;
                }
            }
            if(i==100-lcrbs)	//如果执行了上面几行的if语句，break后可以保证 i!=100-lcrbs。
            subframe=7;
    	}
    }
    //Type 2 is a continuous way of resoure allocation.
    Nprb=GetNprb();
    if(lcrbs <= 1 + Nprb/2)         //down limit
    {
        RIV=Nprb*(lcrbs-1)+RBstart;//RIV这么算的?
    }
    else
    {
        RIV=Nprb*(Nprb-lcrbs+1)+(Nprb-1-RBstart);
    }
    //系统目前带宽为20MHZ，对应的PRB=100，因此不考虑PRB数目小于44个时，所引起的数据格式的变化。
    if((Do_ulgrant_hoppingflag()==0))
    {
        rb_assignment=RIV;

    }
    if( (Do_ulgrant_hoppingflag()==1))
    {
    	//根据协议可知跳频bit数目为2个，设定调频模式指示UE，目前假设调频bit为01；01(2bit) 000(b bit) RIV(5 bit)
    	rb_assignment=256 + RIV;
    	
    }
	FRET(rb_assignment);
}
static unsigned int Do_ulgrant_ulDelay(u16 subframe,u16 cqi)
{
	int PerPrb_Datasize,lcrbs,RBstart,Nprb;
	int i,a;
	u8 UL_delay;
	u32 flag=1;

    FIN(Do_ulgrant_ulDelay());
	SV_PTR_GET(mac_sv);

    PerPrb_Datasize=Get_Ul_PerPrb_Datasize(cqi);//number of PRB
	lcrbs=cal_ul_abs(SIZE_MSG3,PerPrb_Datasize);//取绝对值上限，得到至少要分配的PRB个数
    //when the predistribution subframe resource isn't enough, delay=1, means the next up subframe resource, and so on.
	a=0;//a的作用和上文的作用相同
	UL_delay=0;
	
	while(flag)
    {
        if(2==subframe)
        {
            for(i=0;i<100-lcrbs;i++)
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
            if(i==100-lcrbs)
            {
                a=a+1;
                subframe=7;
            }

        }

        else if(7==subframe)
        {
            for(i=0;i<100-lcrbs;i++)
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
            if(i==100-lcrbs)
            {
                a=a+1;
                subframe=2;
            }

        }
	else
		break;
    }
   
}
static unsigned int Do_ulgrant_mcs(u16 cqi)
{
    FIN(Do_ulgrant_mcs());
    FRET(GetMcsFromCqi (cqi));
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
static unsigned short Do_Data_of_MacRarPdu_tcrnti(u16 rapid)
{
    FIN(Do_Data_of_MacRarPdu_tcrnti());
    FRET(Simple_System_Allocate_Rnti(TC_RNTI,rapid));
}
//Competing_Res_Allocation


//生成RARPDU的数据，并返回将产生的数据的指针
//DCI部分因为之前未考虑到，暂时还没编写
//HQ modified 20140618 修改函数参数,鉴于需要返回指针，避免内存分配和释放不匹配
//该函数是应该是处理一个RA_RNTI所对应的的RA请求，可能包含多个RAPID

//gengcanxi:该函数处理的也是handle_ra_req函数所采用的队列，处理的是队列中的一个用户的请求，
//           他们可能是同一个RA-RNTI，也有可能不是同一个RA-RNTI，但是每个用户应该只有一个RAPID
//             该函数只是产生一个用户所对应的RAR信息数据，发往复用模块，复用模块负责将具有
//             相同的RA-RNTI的MAC RAR组装成一个MAC PDU进行发送。此时就是所说的一个RA-RNTI对应多个RAPID
//LHL 以指针形式返回，就不需要返回值了，因为第一个参数的地址是在外部申请的
//void * Do_Data_of_MacRarPdu_ulgrant(DATA_RAR_PDU * p_rar_pdu, struct S_RAinfo *p_ra_UEinfo,int index

//2014.0916:由于各个UE的信道质量情况不同，所以同一时间申请竞争资源的UE所申请的资源大小应该不同，所以暂不采用HQ的数据结构
//2014.09.28:index值由调用者传入，指代同一个RA-RNTI用户数剩余要处理的用户个数有多少个，当用户数为1时，即可取消分配同一个资源起点的资源
//调用函数传入每次还未处理的用户个数index即可。index>=1

void Do_Data_of_MacRarPdu_ulgrant(DATA_RAR_PDU * p_rar_pdu, struct S_RAinfo *p_ra_UEinfo,int index)//函数有问题rapid是数组?
{
	
	u8 temp_prb_bitmap2[100];
	u8 temp_prb_bitmap7[100];
	int temp_i;
    FIN(Do_Data_of_MacRarPdu_ulgrant());
	SV_PTR_GET(mac_sv);

	for(temp_i=0;temp_i<100;temp_i++)
		temp_prb_bitmap7[temp_i]=SV(prb_bitmap7[temp_i]);
	for(temp_i=0;temp_i<100;temp_i++)
		temp_prb_bitmap2[temp_i]=SV(next_prb_bitmap2[temp_i]);
	//
	//temp_prb_bitmap7[100]=SV(prb_bitmap7[100]);//这句话有问题，不能这么用?????????????????????
	//temp_prb_bitmap2[100]=SV(prb_bitmap2[100]);//20140928由于处在随机接入过程中，保存资源分配前的资源分配情况，以给多个竞争用户分配同一个资源起点的资源
	
    p_rar_pdu->s_ulgrant.m_mcs=Do_ulgrant_mcs(p_ra_UEinfo->cqi);
    p_rar_pdu->s_ulgrant.m_hoppingflag=Do_ulgrant_hoppingflag();
	p_rar_pdu->s_ulgrant.rb_assignment=Do_ulgrant_rb_assignment(p_ra_UEinfo->subframeN,p_ra_UEinfo->cqi);
	if(index != 1)
		{
		for(temp_i=0;temp_i<100;temp_i++)
			SV(prb_bitmap7[temp_i])=temp_prb_bitmap7[temp_i];
		for(temp_i=0;temp_i<100;temp_i++)
			SV(next_prb_bitmap2[temp_i])=temp_prb_bitmap2[temp_i];
		}
    p_rar_pdu->s_ulgrant.m_tpc=Do_UlDci_ndi();
    p_rar_pdu->s_ulgrant.m_cqiRequest=Do_ulgrant_tpc();
    p_rar_pdu->s_ulgrant.m_ulDelay=Do_ulgrant_ulDelay(p_ra_UEinfo->subframeN,p_ra_UEinfo->cqi);
	p_rar_pdu->s_ulgrant.emptybits=0;

	p_rar_pdu->m_bi=Do_Data_of_MacRarPdu_BI(p_ra_UEinfo->subframeN,p_ra_UEinfo->cqi);
	p_rar_pdu->m_rapid=Do_Data_of_MacRarPdu_RAPID(p_ra_UEinfo->rapid);

	p_rar_pdu->m_ta=Do_Data_of_MacRarPdu_TA(p_ra_UEinfo->ta);
	p_rar_pdu->m_tcrnti=Do_Data_of_MacRarPdu_tcrnti(p_ra_UEinfo->rapid);
fsm_printf("\n[xxx]In the function Do_Data_of_MacRarPdu_ulgrant the value of TC-RNTI is:%d\n",p_rar_pdu->m_tcrnti);
	FOUT;

}

/*
输入:随机接入队列，当前节点的指针
输出:随机接入调度完成后，剩余的资源
		如果没有资源，则返回0
*/
static unsigned int Do_DL_RIV(u16 rapid)
{
	int Nprb,lcrbs;
	int RBstart,RIV;
	int i;
u16 rnti;
	FIN(Do_DL_RIV());
	SV_PTR_GET(mac_sv);
	Nprb=GetNprb();
	lcrbs=Nprb/DL_SCHEDULE_NUM;
lcrbs=lcrbs/4;//decrease the value of RIV to send;
rnti=convert_rapid_rnti(rapid);
	switch(rnti)//5个用户中的第几个，0:0-19PRB 1:20-39prb,以此类推
	{
		case RNTI_A: RBstart=0;break;
		case RNTI_B : RBstart=20;break;
		case RNTI_C : RBstart=40;break;
		case RNTI_D : RBstart=60;break;
		case RNTI_E : RBstart=80;break;
		default: fsm_printf("Do_DL_RIV function sth is wrong!");break;
	}
//note:the length of RIV->RAR_DCI,is 9bit----means the biggest value is:2^9-1=511
	if(lcrbs <= 1 + Nprb/2)         //down limit
    	{
        	RIV=Nprb*(lcrbs-1)+RBstart;//420
    	}
    	else
    	{
	        RIV=Nprb*(Nprb-lcrbs+1)+(Nprb-1-RBstart);
	}
//test code Geng 20141027
fsm_printf("\nIn the function DL_RIV the value of RIV is:%d\n",RIV);
	FRET(RIV);
	
}

//此函数生成的是整个RAR下行数据包的DCI，由于RA-RNTI相同,多个UE可能仅RAPID不同;
//但是在目前最简系统中，我们随机选择一个正在进行随机接入的UE的下行资源用来发送RAR，
//就不会发生冲突(因为其还处于随机接入过程，没有下行数据发送，信道没有被占用)
int Do_RAR_DCI1C(struct S_RAinfo *ra_UEinfo)
{
	ENBMAC_TO_PHY_Rardci * p_rar_ici_dci;
	
    FIN(Do_RAR_DCI());
    p_rar_ici_dci=(ENBMAC_TO_PHY_Rardci *)fsm_mem_alloc(sizeof(ENBMAC_TO_PHY_Rardci));

	p_rar_ici_dci->m_rnti				=ra_UEinfo->ra_rnti;
	p_rar_ici_dci->m_tbsize				=Get_Format1C_TbSize(ra_UEinfo->cqi);//这个为什么是这样的，与RIV是对应的吗?
	p_rar_ici_dci->dci_format=4;//format 1C
	p_rar_ici_dci->cfi=Do_DlDci_cfi();
	
    p_rar_ici_dci->rar_dci.m_gap				=1;//还未找到出处，暂时使用Gap2(频域距离)
    //20141022由于为下行数据，下行用户是固定的，所以最简系统目前的RIV是与bitmap相对应的
    //由于在随机接入前，UE并未获取C-RNTI，所以为了让下行静态调度结果与随机分配相结合，宏定义任意5个中的一个RNTI，得到RIV值(5个值是相同的)
    p_rar_ici_dci->rar_dci.RIV					=Do_DL_RIV(ra_UEinfo->rapid);
	//此处还没有更改完全，RIV的资源分配应该和下行调度有关系
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

int Do_RAR_DCI0(struct S_RAinfo *ra_UEinfo)
{
	//UL_ICI_DCI * p_ul_ici_dci;//LHL 20141011
	ENBMAC_TO_PHY_ULscheduleDCI *p_ul_rar_dci;//LHL 20141011
    FIN(Do_RAR_DCI0());
    p_ul_rar_dci=(ENBMAC_TO_PHY_ULscheduleDCI *)fsm_mem_alloc(sizeof(ENBMAC_TO_PHY_ULscheduleDCI));

	p_ul_rar_dci->m_rnti=ra_UEinfo->ra_rnti;
	p_ul_rar_dci->m_tbsize=Do_Ul_TbSize(ra_UEinfo->cqi,cal_ul_abs(SIZE_MSG3,Get_Ul_PerPrb_Datasize(ra_UEinfo->cqi)));//LHL 20141011,需要和耿讨论
	p_ul_rar_dci->dci_format=0;
	
    p_ul_rar_dci->s_ul_dci.m_format		=Do_UlDci_format();//区分format0和format1A
    p_ul_rar_dci->s_ul_dci.m_hopping	=Do_UlDci_hopping();
    p_ul_rar_dci->s_ul_dci.RIV			=Do_ulgrant_rb_assignment(ra_UEinfo->subframeN, ra_UEinfo->cqi);//与ulgrant中的资源分配结果应该是保持一致的
    p_ul_rar_dci->s_ul_dci.m_ndi		=Do_UlDci_ndi();
    p_ul_rar_dci->s_ul_dci.m_mcs		=Do_UlDci_mcs(ra_UEinfo->cqi);
    p_ul_rar_dci->s_ul_dci.m_tpc		=Do_UlDci_tpc();
    p_ul_rar_dci->s_ul_dci.m_cqiRequest	=Do_UlDci_cqirequest();
    p_ul_rar_dci->s_ul_dci.Cyclic_shift	=Do_UlDci_Cyclic_shift();
    p_ul_rar_dci->s_ul_dci.m_dai		=Do_UlDci_dai();
    p_ul_rar_dci->s_ul_dci.padding		=0;
	p_ul_rar_dci->s_ul_dci.emptybits	=0;
	//Test code Geng 20141027
	fsm_printf("\n##After Test Do_RAR_DCI0:");
		fsm_printf("\nSome important paramters are:");
		fsm_printf("  RA-RNTI:%d",p_ul_rar_dci->m_rnti);
		fsm_printf("  dci_format:%d",p_ul_rar_dci->dci_format);
		fsm_printf("  m_tbsize:%d",p_ul_rar_dci->m_tbsize);
		fsm_printf("  m_mcs:%d",p_ul_rar_dci->s_ul_dci.m_mcs);
		fsm_printf("  RIV:%d",p_ul_rar_dci->s_ul_dci.RIV);
		fsm_printf("  m_dai:%d",p_ul_rar_dci->s_ul_dci.m_dai);
	

	
	fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACTOPHY_UL_DCI, (void *) p_ul_rar_dci, sizeof(ENBMAC_TO_PHY_ULscheduleDCI));
	fsm_mem_free(p_ul_rar_dci);
	FRET(Cal_usable_ResOfBitmap(ra_UEinfo->cqi,ra_UEinfo->subframeN));
    
}



/*
******************************
->Change Data and time:第一次 2014.5.16 第二次 2014.5.29 第三次 2014.5.31 第四次 2014.6.5 第五次2014.06.20
->Function:  About UL-schedule
->Change1:采用位段定义UL-DCI
->Change2:采用skbuff的方式，同时分开定义ICI和DCI，发送至SRIO。
->Change3:采用IOCTL的方式，重新回到之前的定义，直接生成ICI+DCI，并发送。
->Change4:在struct S_UEinfo的结构体中添加datasizeof_bsr，用来存储当前处理用户的bsr大小
->Change5:将函数Order_Ul_Sched返回值由void--->变更为int，返回当前bitmap剩余资源量
->Details:
->Special:
*******************************
*/
//BSR的处理函数，0:短bsr  1:长bsr
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

//函数能够将bsr的大小和物理层上传的数据，增加到S_UEinfo的队列中。
void Add_sueinfo_Node(PHYtoMAC_Info *temp, int m_bsr, int type_bsr)
{
	struct S_UEinfo * p_ul_UEinfo;
	
    FIN(Add_sueinfo_Node());
    SV_PTR_GET(mac_sv);
    p_ul_UEinfo=(S_UEinfo *)fsm_mem_alloc(sizeof(S_UEinfo));
    while(p_ul_UEinfo==NULL)//申请内存失败
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
	fsm_printf("###BSR_SIZE is:%d",p_ul_UEinfo->datasizeof_bsr);
	insert_ULschedQue(SV(ULschedQue_p), p_ul_UEinfo);
	//test_code Geng
	fsm_printf("\n###finsh inser node!\n");
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
	lcrbs=cal_ul_abs(bsr,PerPrb_Datasize);//根据BSR的数据量大小，计算prb的个数上绝对值

	for(a=1;a<3;a++)
    {
        if(2==subframe)
        {
            for(i=0;i<100-lcrbs;i++)
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
            if(i==100-lcrbs)
            subframe=7;
    }

        if(7==subframe)
        {
            for(i=0;i<100-lcrbs;i++)
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
            if(i==100-lcrbs)
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
			//如果需要考虑调频，那么需要在资源分配的数据域的前两个bit，设置跳频指示。
			fsm_printf("We need take of the hopping,and change the resource 'bit' allocate");
			
		}
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
    FRET(2);//1234
}
static unsigned int Do_Ul_TbSize (u16 cqi,int nprb)
{
    FIN(Do_Ul_TbSize ());
    FRET(Get_Ul_TbSize (cqi,nprb));
}
//上行调度指令:执行后返回剩余资源量大小
int Order_Ul_Sched(struct S_UEinfo *p_ul_UEinfo)
{
	//UL_ICI_DCI * p_ul_ici_dci;//LHL 20141011
	ENBMAC_TO_PHY_ULscheduleDCI *p_ul_ici_dci;//LHL 20141011
    FIN(Order_Ul_Sched());
    p_ul_ici_dci=(ENBMAC_TO_PHY_ULscheduleDCI *)fsm_mem_alloc(sizeof(ENBMAC_TO_PHY_ULscheduleDCI));

	p_ul_ici_dci->m_rnti=p_ul_UEinfo->rnti;
	p_ul_ici_dci->m_tbsize=Do_Ul_TbSize(p_ul_UEinfo->cqi,cal_ul_abs(p_ul_UEinfo->datasizeof_bsr,Get_Ul_PerPrb_Datasize(p_ul_UEinfo->cqi)));//LHL 20141011,需要和耿讨论
	p_ul_ici_dci->dci_format=0;
	
    p_ul_ici_dci->s_ul_dci.m_format		=Do_UlDci_format();
    p_ul_ici_dci->s_ul_dci.m_hopping	=Do_UlDci_hopping();
    p_ul_ici_dci->s_ul_dci.RIV			=Do_UlDci_RIV(p_ul_UEinfo->subframeN, p_ul_UEinfo->cqi, p_ul_UEinfo->datasizeof_bsr);
    p_ul_ici_dci->s_ul_dci.m_ndi		=Do_UlDci_ndi();
    p_ul_ici_dci->s_ul_dci.m_mcs		=Do_UlDci_mcs(p_ul_UEinfo->cqi);
    p_ul_ici_dci->s_ul_dci.m_tpc		=Do_UlDci_tpc();
    p_ul_ici_dci->s_ul_dci.m_cqiRequest	=Do_UlDci_cqirequest();
    p_ul_ici_dci->s_ul_dci.Cyclic_shift	=Do_UlDci_Cyclic_shift();
    p_ul_ici_dci->s_ul_dci.m_dai		=Do_UlDci_dai();
    p_ul_ici_dci->s_ul_dci.padding		=0;
	p_ul_ici_dci->s_ul_dci.emptybits	=0;
	//Test code Geng 20141027
	fsm_printf("\n##After Test Order_Ul_Sched:");
		fsm_printf("\nSome important paramters are:");
		fsm_printf("  RNTI:%u",p_ul_ici_dci->m_rnti);
		fsm_printf("  dci_format:%u",p_ul_ici_dci->dci_format);
		fsm_printf("  m_tbsize:%u",p_ul_ici_dci->m_tbsize);
		fsm_printf("  m_mcs:%u",p_ul_ici_dci->s_ul_dci.m_mcs);
		fsm_printf("  RIV:%u",p_ul_ici_dci->s_ul_dci.RIV);
		fsm_printf("  m_dai:%u",p_ul_ici_dci->s_ul_dci.m_dai);

	
	fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACTOPHY_UL_DCI, (void *) p_ul_ici_dci, sizeof(ENBMAC_TO_PHY_ULscheduleDCI));
	fsm_mem_free(p_ul_ici_dci);
	FRET(Cal_usable_ResOfBitmap(p_ul_UEinfo->cqi,p_ul_UEinfo->subframeN));
    
}

/*
******************************
->Change Data and time:第一次 2014.5.16 第二次 2014.5.29 第三次 2014.5.31
->Function:  About UL-schedule
->Change1:采用位段定义DL-DCI
->Change2:采用skbuff的方式，同时分开定义ICI和DCI，发送至SRIO。同时新增结构体result_sched_algorithm，保存静态调度的分配方案
->Change3:采用IOCTL的方式，重新回到之前的定义，直接生成ICI+DCI，并发送。
->Details:
->Special:
*******************************
*/
//下行调度算法，得到被调度的用户及其优先级，同时给出资源分配方案。
//目前最简系统，使用固定分配的方式。5个下行用户
//schedule_scheme数组为全局变量，他代表了目前的静态调度方案。
//bitmap:32bit，取前面25bit为有效位。现在全部分配了25bit，每个用户占bitmap的5个bit
void Do_sched_algorithm()
{
	int i;

	FIN(Do_Dl_Schedule_algorithm());
	SV_PTR_GET(mac_sv);

	
    if (0==SCHEDULE_MODE)
    {
        u32 bitmap[]={0xf8000000,0x07c00000,0x003e0000,0x0001f000,0x00000f80};//PRB0-19 20-39 40-59 60-79 80-99
		//
		for(i=0;i<DL_SCHEDULE_NUM;i++)
		{
		//由于特殊子帧的TBSIZE还有待商榷，所以目前全部查表nprb=20 5736
			SV(schedule_scheme[i]).tbsize=Get_Dl_TbSize(DL_CQI,GetNprb()/DL_SCHEDULE_NUM);
		//提前两个子帧
			
			if(SV(phy_to_mac_frame).subframeN!=0 && SV(phy_to_mac_frame).subframeN != 5 &&SV(phy_to_mac_frame).subframeN <=7)
				{	
					SV(schedule_scheme[i]).sfn=SV(phy_to_mac_frame).sfn;
					SV(schedule_scheme[i]).subframeN=SV(phy_to_mac_frame).subframeN+DL_TA;
				}
			else if(SV(phy_to_mac_frame).subframeN>7)
				{
					SV(schedule_scheme[i]).sfn=SV(phy_to_mac_frame).sfn+1;
					SV(schedule_scheme[i]).subframeN=SV(phy_to_mac_frame).subframeN+DL_TA-10;
				}
			else
				{
					SV(schedule_scheme[i]).sfn=SV(phy_to_mac_frame).sfn;
					SV(schedule_scheme[i]).subframeN=SV(phy_to_mac_frame).subframeN+1+DL_TA;
				}
			
			
			if(i != 2)//UE1UE2UE4UE5
				{
					SV(schedule_scheme[i]).m_bitmap=bitmap[i];
					SV(schedule_scheme[i]).m_rnti=i+61;//20141017耿灿锡改:符合物理层要求5用户rnti为61-65
					SV(schedule_scheme[i]).m_data_size=((5*4)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[i]).subframeN)/8);//1060,1530
				}
			else//UE3在PRB47-52中PBCH和PSCH信道占用了信道资源，需要将其减去
				{
				if(SV(schedule_scheme[i]).subframeN == 0)
					SV(schedule_scheme[i]).m_data_size=(((5*4)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[i]).subframeN)-PBCH_OFDM-SSCH_OFDM)/8);//1488
				else if(SV(schedule_scheme[i]).subframeN == 1 &&SV(schedule_scheme[i]).subframeN == 6)
					SV(schedule_scheme[i]).m_data_size=(((5*4)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[i]).subframeN)-PSCH_OFDM)/8);//1051
				else if(SV(schedule_scheme[i]).subframeN == 5)
					SV(schedule_scheme[i]).m_data_size=(((5*4)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[i]).subframeN)-SSCH_OFDM)/8);//1521
				else
					SV(schedule_scheme[i]).m_data_size=((5*4)*Get_Dl_PerPrb_Datasize(DL_CQI,SV(schedule_scheme[i]).subframeN)/8);//1060
				SV(schedule_scheme[i]).m_bitmap=bitmap[i];
				SV(schedule_scheme[i]).m_rnti=i+61;//20141017耿灿锡改:符合物理层要求5用户rnti为61-65
				}
			
			
		}
       
    }
    //Semi_Persistent 
    if(1==SCHEDULE_MODE)
    {
        fsm_printf("Do not consider the semi-persistent at present!\n");
    }
    // dynamic
    if(2==SCHEDULE_MODE)
    {
        fsm_printf("Do not consider the dynamic at present!\n");
    }
	FOUT;
}
//根据rnti的值，返回该rnti值对应的数据量，给令牌桶使用byte
int Do_cal_datasize(u16 rnti)
{
	int i;
	FIN(Do_cal_datasize());
	SV_PTR_GET(mac_sv);

	for(i=0;i<DL_SCHEDULE_NUM;i++)
		{
			if(SV(schedule_scheme[i]).m_rnti==rnti)
				FRET(SV(schedule_scheme[i]).m_data_size);
		}
	FRET(0);//modified by lhl 没有匹配的RNTI，返回0
}

//根据rnti的值，返回该rnti值对应的bitmap，以产生DCI
static unsigned int Do_DlDci_bitmap(u16 rnti)
{
	int i;
	u32 temp_bitmap;
	FIN(Do_DlDci_bitmap());
	SV_PTR_GET(mac_sv);

	fsm_printf("[XXX]DO DL BITMAP:%d\n",rnti);
	for(i=0;i<DL_SCHEDULE_NUM;i++)
	{
		fsm_printf("[XXX]SCHEDULE SCHEME RNTI:%d\n",SV(schedule_scheme[i]).m_rnti);
		if(SV(schedule_scheme[i]).m_rnti==rnti){
			fsm_printf("[XXX]DO DL BITMAP  m_rbBitmap:0x%.8x\n",SV(schedule_scheme[i]).m_bitmap);
			temp_bitmap=(SV(schedule_scheme[i]).m_bitmap>>7);//phsical demand high->low(prb) so in order finsh 32bit->25bit,>>7
			FRET(temp_bitmap);
		}
	}
	FRET(0);
}

static unsigned int Do_DlDci_resAlloc()
{
    FIN(Do_DlDci_resAlloc());
    FRET(0);
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
    FRET(0);//
}
static unsigned int Do_DlDci_harqProcess()
{
    FIN(Do_DlDci_harqProcess());
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

static unsigned int Do_Dl_TbSize (u16 rnti)
{

int i;
    FIN(Do_Dl_TbSize ());
	SV_PTR_GET(mac_sv);
switch(rnti)//5个用户中的第几个，0:0-19PRB 1:20-39prb,以此类推
	{
		case RNTI_A: i=0;break;
		case RNTI_B : i=1;break;
		case RNTI_C : i=2;break;
		case RNTI_D : i=3;break;
		case RNTI_E : i=4;break;
		default: fsm_printf("downlink rnti allocation sth is wrong!");break;
	}
    FRET(SV(schedule_scheme[i]).tbsize);
}

static u8  Do_DlDci_cfi()
{
	FIN(Do_DlDci_cfi ());
	FRET(1);
}

//函数功能:生成DCI，并发往物理适配层
//函数输入: 有关RLCREQ的buffer；
//由下行调度函数Order_Dl_Sched()调用。


void Order_Dl_Sched(RLC_Request *mac_buffer)
{
	
	ENBMAC_TO_PHY_DLscheduleDCI * p_dl_ici_dci;
	
    FIN(Order_Dl_Sched());

    p_dl_ici_dci=(ENBMAC_TO_PHY_DLscheduleDCI *)fsm_mem_alloc(sizeof(ENBMAC_TO_PHY_DLscheduleDCI));

	p_dl_ici_dci->s_dl_dci.m_resAlloc		=Do_DlDci_resAlloc();
	p_dl_ici_dci->s_dl_dci.m_rbBitmap		=Do_DlDci_bitmap(mac_buffer->rnti);
	p_dl_ici_dci->s_dl_dci.m_mcs			=Do_DlDci_mcs(DL_CQI);
	p_dl_ici_dci->s_dl_dci.m_ndi			=Do_DlDci_ndi();
	p_dl_ici_dci->s_dl_dci.m_rv				=Do_DlDci_rv();
	p_dl_ici_dci->s_dl_dci.m_harqProcess	=Do_DlDci_harqProcess();
	p_dl_ici_dci->s_dl_dci.m_tpc			=Do_DlDci_tpc();
	p_dl_ici_dci->s_dl_dci.m_dai			=Do_DlDci_dai();
	p_dl_ici_dci->s_dl_dci.emptybits		=0;

	p_dl_ici_dci->m_rnti=mac_buffer->rnti;
	//fsm_printf("[XXX]MAC BUF RNTI:%d\n",mac_buffer->rnti);
	p_dl_ici_dci->m_tbsize=Do_Dl_TbSize(mac_buffer->rnti);//应该要根据抗干扰要求改TBSIZE
	p_dl_ici_dci->dci_format=1;
	p_dl_ici_dci->cfi=Do_DlDci_cfi();//modified LHL 20141011
	//Test code Geng 20141027
	fsm_printf("\n##After Test Order_Dl_Sched:");
		fsm_printf("\nSome important paramters are:");
		fsm_printf("  RNTI:%u",p_dl_ici_dci->m_rnti);
		fsm_printf("  dci_format:%u",p_dl_ici_dci->dci_format);
		fsm_printf("  m_tbsize:%u",p_dl_ici_dci->m_tbsize);
		fsm_printf("  CFI:%u",p_dl_ici_dci->cfi);
		
		fsm_printf("  m_rbBitmap:0x%.8x",p_dl_ici_dci->s_dl_dci.m_rbBitmap);
		fsm_printf("  MCS:%u\n",p_dl_ici_dci->s_dl_dci.m_mcs);
	
	//fsm_do_ioctrl(STRM_TO_SRIO, IOCCMD_MACTOPHY_DL_DCI, (void *) p_dl_ici_dci, sizeof(ENBMAC_TO_PHY_DLscheduleDCI));
	fsm_mem_free(p_dl_ici_dci);
	FOUT;
}



