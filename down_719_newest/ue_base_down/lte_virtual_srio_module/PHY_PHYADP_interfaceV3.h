
/*========以下是ENB侧下行链路Type1中的参数表或参数表头部==================*/

typedef struct ENB_DL_TYPE1_PUBLIC_C
{
	u16	PDSCHNum;
	u16 PDCCHNum;
	u16	NumOfUEForPHICH;
	u16 Zero;

	u32 PBCH_C_Offset;
	u32 PBCH_D_Offset;
	u32 PHICH_C_Offset;
	u32 PHICH_D_Offset;
	u32 PDCCH_C_Offset;
	u32 PDCCH_D_Offset;
	u32 PDSCH_C_Offset;
	u32 PDSCH_D_Offset;
}__attribute__((packed))ENB_DL_TYPE1_PUBLIC_C;

typedef struct ENB_DL_TYPE1_PBCH_C
{
	u16	NumPrbBw; //默认值为20M，值为100
	u16 PhichDurtion; //默认值为0
	u16	GPhichNg; //默认值为0
	//SFN在表头有了 这里不再给出
	//如果物理层需要我们单独给SFN也是可以的
	u16	spare; //预留16bit
}__attribute__((packed))ENB_DL_TYPE1_PBCH_C;

typedef struct ENB_DL_TYPE1_PBCH_D
{
	u32 SourcePBCH; //默认值待定
}__attribute__((packed))ENB_DL_TYPE1_PBCH_D;


typedef struct ENB_DL_TYPE1_PDSCH_C
{
	u16	RNTI; //默认值为61-65
	u16 NumCW; //默认值为1
	u16	NumPrbofUe; //默认值为20
	u16	UeCategory; //默认值为3
	u16	UeTransMod; //默认值为2
	u16	NumHarqPro; //默认值为8
	u16	RvIdx; //默认值为0
	u16	Modulation; //默认值为1
	u16	NumLayers; //默认值为2
	u16	DelayMod; //默认值为0
	u16	PA; //默认值为4
	u16	zero; //默认值为1
	u32	PDSCHTbSize; //默认值为5736/4264
	u32	BitMap; //默认值为
}__attribute__((packed))ENB_DL_TYPE1_PDSCH_C;

typedef struct ENB_DL_TYPE1_PDSCH_D
{
	u16	RNTI; //默认值为61-65
	u16 PdschData; //信源长度
}__attribute__((packed))ENB_DL_TYPE1_PDSCH_D;
//在这个后面我们会直接跟信源，长度不定

typedef struct ENB_DL_TYPE1_PDCCH_C
{
	u16	RNTI; //默认值为61-65
	u16 CommonPdcchFlag; //默认值为1
	u8	PdcchFormat; //默认值为0
	u8	DCIFormat; //默认值为2
	u16	DciBitLen; //默认值为31
}__attribute__((packed))ENB_DL_TYPE1_PDCCH_C;

typedef struct ENB_DL_TYPE1_PDCCH_D
{
	u16	RNTI; //默认值为61-65
	u16 zero;
	u64 DataSource;
}__attribute__((packed))ENB_DL_TYPE1_PDCCH_D;
//在这个后面我们会直接跟信源，长度不定

typedef struct ENB_DL_TYPE1_PHICH_C
{
	u16	RNTI; //默认值为61-65
	u16 zero;
	u32 I_lowest_index_PRB_RA; //默认值为待定
	u32 NDmrs; //默认值为待定
}__attribute__((packed))ENB_DL_TYPE1_PHICH_C;

typedef struct ENB_DL_TYPE1_PHICH_D
{
	u16	RNTI; //默认值为61-65
	u16 SourcePHICH; //默认值为0
}__attribute__((packed))ENB_DL_TYPE1_PHICH_D;

typedef struct ENBPHYADPtoPHYType1
{
	GeneralHeader12 GHead;
	ENB_DL_TYPE1_PUBLIC_C DL_TYPE1_PUBLIC_C;
}__attribute__((packed))ENBPHYADPtoPHYType1;
//之后的排列顺序为PBCH的C&D PHICH的C&D PDCCH的C&D PDSCH的C&D

/*========End of ENB侧下行链路Type1中的参数表==================*/

/*========以下是ENB侧下行链路Type3中的参数表,按序存放==================*/
typedef struct ENB_DL_TYPE3_PUBLIC_C
{
	u32 PDSCHOffset;
	u32 PDCCHOffset;
}__attribute__((packed))ENB_DL_TYPE3_PUBLIC_C;

typedef struct ENB_DL_TYPE3_PDSCH_C
{
	u16	CellID; //默认值为0
	u16 NumAntPort; //默认值为2
	u16	CFI; //默认值为1
	u16	CpType; //默认值为0
	u16	SFDirection; //默认值为2
	u16	PB; //默认值为1
}__attribute__((packed))ENB_DL_TYPE3_PDSCH_C;

typedef struct ENB_DL_TYPE3_PDCCH_C
{
	u16	SpecSubFrmCfg; //默认值为2
}__attribute__((packed))ENB_DL_TYPE3_PDCCH_C;


typedef struct ENBPHYADPtoPHYType3
{
	//这个是ENB侧下行链路Type3的总体结构
	GeneralHeader345 GHead;
	ENB_DL_TYPE3_PUBLIC_C DL_TYPE3_PUBLIC_C;
	ENB_DL_TYPE3_PDCCH_C DLType3Pdcch_C;
	ENB_DL_TYPE3_PDSCH_C DLType3Pdsch_C;
	
}__attribute__((packed))ENBPHYADPtoPHYType3;

/*========End of ENB侧下行链路Type3中的参数表==================*/


/*========以下是UE侧下行链路Type1中的参数表,按序存放==================*/
typedef struct UE_DL_TYPE1_PUBLIC_C
{
	u32 PDSCHOffset;
	u32 PDCCHOffset;
}__attribute__((packed))UE_DL_TYPE1_PUBLIC_C;

typedef struct UE_DL_TYPE1_PDSCH_C
{
	u16 PA; //默认值为4
	u16 PB; //默认值为1
	u16 RNTI; //默认值为61-65
	u16 UeCategory; //默认值为3
	u16 DelayMod; //默认值为0
	u16 padding;//默认值为0
}__attribute__((packed))UE_DL_TYPE1_PDSCH_C;

typedef struct UE_DL_TYPE1_PDCCH_C
{
	u16 PdcchNum; //默认值为1
	u16 RNTI; //默认值为61-65
}__attribute__((packed))UE_DL_TYPE1_PDCCH_C;

typedef struct UEPHYADPtoPHYType1
{
	//UE侧Type1的总体结构
	GeneralHeader12 GHead;
	UE_DL_TYPE1_PUBLIC_C DL_TYPE1_PUBLIC_C;
	UE_DL_TYPE1_PDCCH_C DL_TYPE1_PDCCH_C;  //
	UE_DL_TYPE1_PDSCH_C DL_TYPE1_PDSCH_C;
}__attribute__((packed))UEPHYADPtoPHYType1;
/*========End of UE侧下行链路Type1中的参数表==================*/


/*========以下是UE侧下行链路Type2中的参数表,按序存放==================*/
typedef struct UE_DL_TYPE2_PUBLIC_C
{
	u32 PDSCHLength;
	u32 PDCCHOffset;
}__attribute__((packed))UE_DL_TYPE2_PUBLIC_C;

typedef struct UE_DL_TYPE2_PBCH_D
{
	u32 SourcePBCH; //默认值为待定
}__attribute__((packed))UE_DL_TYPE2_PBCH_D;

typedef struct UE_DL_TYPE2_PDSCH_C
{
	u32 CRC; //默认值为随机
}__attribute__((packed))UE_DL_TYPE2_PDSCH_C;

/*
typedef struct UE_DL_TYPE2_PDSCH_D
{
	u32 SourcePDSCH;
}__attribute__((packed))UE_DL_TYPE2_PDSCH_D;
*/

typedef struct UE_DL_TYPE2_PDCCH_C
{
	u32 HARQprocessID; //默认值为0
	u32 RV; //默认值为0
	u16	NDI; //默认值为1
	u16 padding;
}__attribute__((packed))UE_DL_TYPE2_PDCCH_C;

/*
typedef struct UE_DL_TYPE2_PDCCH_D
{
	u32 DCIData;
}__attribute__((packed))UE_DL_TYPE2_PDCCH_D;
*/

typedef struct UE_DL_TYPE2_PHICH_D
{
	u32	HARQIndex; //默认值为0-1
}__attribute__((packed))UE_DL_TYPE2_PHICH_D;

typedef struct UEPHYADPtoPHYType2
{
	//UE侧Type2的总体结构
	GeneralHeader12 GHead;
	UE_DL_TYPE2_PUBLIC_C DL_TYPE2_PUBLIC_C;
}__attribute__((packed))UEPHYADPtoPHYType2;
//之后的排列顺序为PBCH的D PHICH的D PDCCH的C&D PDSCH的C&D

/*========End of UE侧下行链路Type2中的参数表==================*/

/*========以下是UE侧下行链路Type3中的参数表,按序存放==================*/
typedef struct UE_DL_TYPE3_PUBLIC_C
{
	u32 PDSCHOffset;
	u32 PDCCHOffset;
}__attribute__((packed))UE_DL_TYPE3_PUBLIC_C;

typedef struct UE_DL_TYPE3_PDSCH_C
{
	u16	DL_Status; //默认值为2
	u16 padding;//填充位0
}__attribute__((packed))UE_DL_TYPE3_PDSCH_C;

typedef struct UE_DL_TYPE3_PDCCH_C
{
	u16	SFDirection; //默认值为2
	u16	T_MODE; //默认值为3
	u16	PdcchNum; //默认值为1
	u16	RNTI; //默认值为61-65
	u16	UeCategory; //默认值为3
	u16 padding; //填充位0
	u32	MemStart; //默认值为待定
	u32	MemSize; //默认值为待定
}__attribute__((packed))UE_DL_TYPE3_PDCCH_C;

typedef struct UEPHYADPtoPHYType3
{
	//UE侧Type3的总体结构
	GeneralHeader345 GHead;
	UE_DL_TYPE3_PUBLIC_C DL_TYPE3_PUBLIC_C;
	UE_DL_TYPE3_PDCCH_C DL_TYPE3_PDCCH_C; 
	UE_DL_TYPE3_PDSCH_C DL_TYPE3_PDSCH_C;
}__attribute__((packed))UEPHYADPtoPHYType3;


/*========End of UE侧下行链路Type3中的参数表==================*/

