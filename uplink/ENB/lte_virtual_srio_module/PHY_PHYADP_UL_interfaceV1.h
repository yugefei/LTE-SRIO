/*****以下是接口通用数据头部定义******/
typedef struct GeneralHeader12
{
	//GeneralHeader12 用于Type1和Type2两种接口。因为其存放区域不同，不需要单独的标志区分Type1和Type2
	u32	NewFlag;
	u16	SFN;
	u16	SubframeN;
}__attribute__((packed))GeneralHeader12;

typedef struct GeneralHeader345
{
	//GeneralHeader345 用于Type3和Type4和Type5三种接口。因为其存放区域不同，不需要单独的标志区分
	u32	NewFlag;
	union {
		u32 CmdFlag;//按位标志 配置命令参数表标志，用于Type3,按位注明对应的配置参数表是否生效
		u32 RespFlag;//按位标志 控制响应标志，用于Type4，按位对应的命令是否或响应生效
		u32 ReportFlag;//按位标志 状态上报报告标志，用于Type5，按位标志对应的状态报告是否生效
	}SetFlag;
}__attribute__((packed))GeneralHeader345;

//Type1,2,3,4,5中每个参数表的可选头部，如果需要的话
typedef struct ParTableHeader{
	u16 ParTableType;
	u16 ParTableLen;
}__attribute__((packed))ParTableHeader;

/*========以下是ENB侧上行链路Type1中的参数表或参数表头部==================*/

typedef struct ENB_UL_TYPE1_PUBLIC_C
{
	u16 ULVxxUserNum; //最小系统参数2
	u16 padding; //填充位，保持字节对齐
	u32 PUSCHOffset;
	u32 PUCCHOffset;
}__attribute__((packed))ENB_UL_TYPE1_PUBLIC_C;

typedef struct ENB_UL_TYPE1_PUSCH_C
{
	u16 RNTI;//最小系统参数61,62
	u16 UlChSel;//最小系统参数000
	u16 PGType;//最小系统参数第一次：0后面：2
	u16 NumofNP;//最小系统参数：本参数组内所有参数数量
	u16 PrbStart;//最小系统参数分别为2,50
	u16 NumPrb;//最小系统参数48
	u16 PuschHopFlag;//最小系统参数0
	u16 ULHop;//最小系统参数0
	u16 puschHopOffset;//最小系统参数0
	u16 Qm;//最小系统参数1
	u16 rvIdx;//最小系统参数0
	u16 dmrs2;//最小系统参数0
	u16 harqInfoLen;//最小系统参数0
	u16 harqOffset;//最小系统参数0
	u16 Nbundled;//最小系统参数1
	u16 riInfoLen;//最小系统参数0
	u16 riOffset;//最小系统参数0
	u16 cqiInfoLen;//最小系统参数0
	u16 cqiOffset;//最小系统参数0
	u16 betaPUSCH;//待定
	u16 ndi;//待定
	u16 CurrentTxNB;//待定
	u16 Nsb;//待定
	u16 UECategory;//最小系统参数4
	u16 TM;//待定
	u16 harqFeedbackMode;//最小系统参数1
	u16 Isrs;//待定
	u16 SRSDuration;//待定
	u16 Bsrs;//待定
	u16 Nra;//待定
	u16 Ktc;//待定
	u16 Bhop;//待定
	u16 nRRC;//待定
	u16 nSRScs;//待定
	u16 betaSRS;//待定
	u16 padding;//填充位0
	u32 tbSize;//最小系统参数7480bit
}__attribute__((packed))ENB_UL_TYPE1_PUSCH_C;

typedef struct ENB_UL_TYPE1_PUCCH_C
{
	u16 RNTI;//最小系统参数61,62
	u16 UlChSel;//最小系统参数000
	u16 PGType;//最小系统参数:第一次0后面2
	u16 NumofNP;//最小系统参数
	u16 cqiInfoLen;//待定
	u16 nPucchIndex;//待定
	u16 detaPUCCHshift;//待定
	u16 betaPUCCH;//待定
	u16 Isrs;//待定
	u16 SRSDuration;//待定
	u16 Bsrs;//待定
	u16 Nra;//待定
	u16 Ktc;//待定
	u16 Bhop;//待定
	u16 nRRC;//待定
	u16 nSRScs;//待定
	u16 betaSRS;//待定
	u16 padding;//填充位0
}__attribute__((packed))ENB_UL_TYPE1_PUCCH_C;

typedef struct ENBULPHYADPtoPHYType1
{
	GeneralHeader12 GHead;
	ENB_UL_TYPE1_PUBLIC_C UL_TYPE1_PUBLIC_C;
}__attribute__((packed))ENBULPHYADPtoPHYType1;
//后面直接跟PUCCH的C PUSCH的C（2用户）

/*========End of ENB侧上行链路Type1中的参数表==================*/

/*========以下是ENB侧上行链路Type2中的参数表或参数表头部==================*/
typedef struct ENB_UL_TYPE2_PUBLIC_C
{
	u32 PUSCHOffset;
	u32 PUCCHOffset;
}__attribute__((packed))ENB_UL_TYPE2_PUBLIC_C;

typedef struct ENB_UL_TYPE2_PUSCH_C
{
	u16 RNTI;//最小系统参数61,62
	u16 UlChSel;//最小系统参数000
	u16 NumofNP;
	u16 CRC;//最小系统参数变化
	u16 HARQbitinfo;//最小系统参数0
	u16 CQI;//最小系统参数9
	u16 RIbitinfo;//最小系统参数变化
	u16 TA;//待定
	u16 RAPID;//最小系统参数0
	u16 RARNTI;//最小系统参数0
	u16 RAmaskindex;//最小系统参数待定
	u16 padding;
}__attribute__((packed))ENB_UL_TYPE2_PUSCH_C;

typedef struct ENB_UL_TYPE2_PUCCH_C
{
	u16 RNTI;//最小系统参数61,62
	u16 UlChSel;//最小系统参数000
	u16 HARQbitinfo;//最小系统参数变化
	u16 SR;//最小系统参数变化
	u16 CQI;//最小系统参数9
	u16 TA;//最小系统参数待定
	u16 RAPID;//最小系统参数0
	u16 RARNTI;//最小系统参数0
	u16 RAmaskindex;//最小系统参数待定
	u16 padding;
}__attribute__((packed))ENB_UL_TYPE2_PUCCH_C;

typedef struct ENB_UL_TYPE2_PUSCH_D
{
	u16 RNTI;//最小系统参数61,62
	u16 UlChSel;//最小系统参数000
	u32 datalen;//译码数据的长度
}__attribute__((packed))ENB_UL_TYPE2_PUSCH_D;
//后面直接跟PUSCH译码的数据DataOfPUSCH

typedef struct ENBULPHYADPtoPHYType2
{
	GeneralHeader12 GHead;
	ENB_UL_TYPE2_PUBLIC_C UL_TYPE2_PUBLIC_C;
}__attribute__((packed))ENBULPHYADPtoPHYType2;
//后面直接跟PUCCH的C PUSCH的C&D（2用户）

/*========以上是ENB侧上行链路Type2中的参数表或参数表头部==================*/

/*========以下是ENB侧上行链路Type3中的参数表或参数表头部==================*/
typedef struct ENB_UL_TYPE3_PUBLIC_C
{
	u32 PUSCHCOffset;
}__attribute__((packed))ENB_UL_TYPE3_PUBLIC_C;

typedef struct ENB_UL_TYPE3_PUSCH_C
{
	u16 NumRbHo;//最小系统参数2
	u16 puschDeltaSS;//最小系统参数0
	u16 HoppingMode;//最小系统参数不支持
	u16 GroupHopEn;//最小系统参数0
	u16 SeqHopEn;//最小系统参数0
	u16 Dmrs1;//最小系统参数0
	u16 CpType;//最小系统参数0
	u16 cellID;//最小系统参数0
	u16 NumPrbBw;//最小系统参数20M
	u16 SFDirection;//最小系统参数2
	u16 SpecSFcfg;//最小系统参数待定
	u16 SrsSubframConfig;//最小系统参数待定
	u16 CSrs;//最小系统参数待定
	u16 SrsMaxUpPts;//最小系统参数待定
}__attribute__((packed))ENB_UL_TYPE3_PUSCH_C;

typedef struct ENBULPHYADPtoPHYType3
{	//ENB侧上行TYPE3总体参数
	GeneralHeader345 GHead;
	ENB_UL_TYPE3_PUBLIC_C UL_TYPE3_PUBLIC_C;
	ENB_UL_TYPE3_PUSCH_C UL_TYPE3_PUSCH_C;
}__attribute__((packed))ENBULPHYADPtoPHYType3;

/*========以上是ENB侧上行链路Type3中的参数表或参数表头部==================*/

/*========以下是UE侧上行链路Type1中的参数表或参数表头部==================*/

typedef struct UE_UL_TYPE1_PUBLIC_C
{
	u32 PUSCHCOffset;
	u32 PUSCHDOffset;
}__attribute__((packed))UE_UL_TYPE1_PUBLIC_C;

typedef struct UE_UL_TYPE1_PUSCH_C
{
	u16 RNTI;//最小系统参数61,62
	u16 UlStates;//最小系统参数待定
	u16 UlChSel;//最小系统参数000
	u16 PGType;//最小系统参数第一次0后面2
	u16 NumofNP;//最小系统参数
	u16 PrbStart;//最小系统参数2,50
	u16 NumPrb;//最小系统参数48
	u16 PuschHopFlag;//最小系统参数0
	u16 ULHop;//最小系统参数不支持
	u16 puschHopOffset;//最小系统参数不支持
	u16 Qm;//最小系统参数1
	u16 rvIdx;//最小系统参数0
	u16 dmrs2;//最小系统参数0
	u16 harqInfoLen;//最小系统参数0
	u16 harqOffset;//最小系统参数0
	u16 Nbundled;//最小系统参数不支持
	u16 riInfoLen;//最小系统参数0
	u16 riOffset;//最小系统参数0
	u16 cqiInfoLen;//最小系统参数0
	u16 cqiOffset;//最小系统参数0
	u16 betaPUSCH;//最小系统参数待定
	u16 ndi;//最小系统参数不支持
	u16 CurrentTxNB;//最小系统参数不支持
	u16 Nsb;//最小系统参数不支持
	u16 TA;//最小系统参数待定
	u16 Subfn;//最小系统参数变化
	u16 Isrs;//最小系统参数待定
	u16 SRSDuration;//最小系统参数待定
	u16 Bsrs;//最小系统参数待定
	u16 Nra;//最小系统参数待定
	u16 Ktc;//最小系统参数待定
	u16 Bhop;//最小系统参数待定
	u16 nRRC;//最小系统参数待定
	u16 nSRScs;//最小系统参数待定
	u16 betaSRS;//最小系统参数待定
	u16 padding;
	u32 tbSize;//最小系统参数15264
}__attribute__((packed))UE_UL_TYPE1_PUSCH_C;

typedef struct UE_UL_TYPE1_PUSCH_D
{
	u16 RNTI;//最小系统参数61,62
	u16 UlChSel;//最小系统参数000
	u16 CQI;//最小系统参数变化
	u16 RI;//最小系统参数变化
	u32 HARQ_ACK;//最小系统参数变化
}__attribute__((packed))UE_UL_TYPE1_PUSCH_D;
//后面直接跟SourcePUSCH数据

typedef struct UE_UL_TYPE1_PUCCH_C
{
	u16 RNTI;//最小系统参数61,62
	u16 UlStates;//最小系统参数待定,0或1
	u16 UlChSel;//最小系统参数000
	u16 PGType;//最小系统参数第一次0后面2
	u16 NumofNP;//最小系统参数
	u16 cqiInfoLen;//最小系统参数待定
	u16 nPucchIndex;//最小系统参数待定
	u16 deltaPUCCHshift;//最小系统参数待定
	u16 betaPUCCH;//最小系统参数待定
	u16 TA;//最小系统参数待定
	u16 Subfn;//最小系统参数变化
	u16 Isrs;//最小系统参数待定
	u16 SRSDuration;//最小系统参数待定
	u16 Bsrs;//最小系统参数待定
	u16 Nra;//最小系统参数待定
	u16 Ktc;//最小系统参数待定
	u16 Bhop;//最小系统参数待定
	u16 nRRC;//最小系统参数待定
	u16 nSRScs;//最小系统参数待定
	u16 betaSRS;//最小系统参数待定
}__attribute__((packed))UE_UL_TYPE1_PUCCH_C;

typedef struct UE_UL_TYPE1_PUCCH_D
{
	u16 RNTI;//最小系统参数61,62
	u16 UlChSel;//最小系统参数000
	u16 SR;//最小系统参数待定
	u16 HARQ;//最小系统参数待定
	u16 CQI;//最小系统参数待定
	u16 padding;
}__attribute__((packed))UE_UL_TYPE1_PUCCH_D;

typedef struct UEULPHYADPtoPHYType1
{
	GeneralHeader12 GHead;
	UE_UL_TYPE1_PUBLIC_C UL_TYPE1_PUBLIC_C;
}__attribute__((packed))UEULPHYADPtoPHYType1;
//后面直接跟PUCCH C&D PDSCH C&D

/*========End of UE侧上行链路Type1中的参数表==================*/

/*========以下是UE侧上行链路Type3中的参数表或参数表头部==================*/
typedef struct UE_UL_TYPE3_PUBLIC_C
{
	u32 PUSCH_PUCCHOffset;
}__attribute__((packed))UE_UL_TYPE3_PUBLIC_C;

typedef struct UE_UL_TYPE3_PUSCH_PUCCH_C
{
	u16 NumRbHo;//最小系统参数不支持
	u16 puschDeltaSS;//最小系统参数0
	u16 HoppingMode;//最小系统参数不支持
	u16 GroupHopEn;//最小系统参数0
	u16 SeqHopEn;//最小系统参数0
	u16 DMRS1;//最小系统参数0
	u16 CpType;//最小系统参数0
	u16 cellID;//最小系统参数0
	u16 NumPrbBw;//最小系统参数20M
	u16 SFDirection;//最小系统参数2
	u16 SpecSFcfg;//最小系统参数待定
	u16 UECategory;//最小系统参数4
	u16 TM;//最小系统参数待定
	u16 harqFeedbackMode;//最小系统参数Multiplexin
	u16 SrsSubframConfig;//最小系统参数待定
	u16 CSrs;//最小系统参数待定
	u16 SrsMaxUpPts;//最小系统参数待定
	u16 padding;
}__attribute__((packed))UE_UL_TYPE3_PUSCH_PUCCH_C;

typedef struct UEULPHYADPtoPHYType3
{	//UE侧上行TYPE3总体参数
	GeneralHeader345 GHead;
	UE_UL_TYPE3_PUBLIC_C UL_TYPE3_PUBLIC_C;
	UE_UL_TYPE3_PUSCH_PUCCH_C UL_TYPE3_PUSCH_PUCCH_C;
}__attribute__((packed))UEULPHYADPtoPHYType3;

/*========以上是UE侧上行链路Type3中的参数表或参数表头部==================*/
