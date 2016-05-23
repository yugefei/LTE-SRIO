#include "../fsm/fsmdec.h"

#ifndef _RLCFSM_H
#define _RLCFSM_H

#include <linux/list.h>
#include <linux/types.h>
#include "Rlctypes.h"

#define SequenceNumber  u16

#define MAX_NUM   16
#define  MAX_CODE   50
#define FLAG 2
#define MAX_PDU_SIZE 1300

/* The types of instances in RLC layer  */
typedef enum {NONE_MODE,TM_MODE=1, UM_MODE=2, AM_MODE=3} RlcMode;
//typedef enum {TM_TX_MODE=1, TM_RX_MODE=2, UM_TX_MODE=3, UM_RX_MODE=4, AM_MODE=5} RlcMode;
typedef enum {POLL_RETX = 1, STAT_PRO = 2, AM_REORDER = 3, UM_REORDER = 4, BUFFER_REQ = 5}RlcTimerType;
/** Data Structures Used By RLC **/

typedef enum { FULL_SDU = 1, LAST_SEGMENT = 2, ANY_SEGMENT = 3} PacketStatus;


typedef struct AmSduBuffer     //AM 新数据队列
{
	FSM_PKT * pkt;
	PacketStatus pktstatus;
	u32 pos;
	struct list_head list;
} AmSduBuffer;

typedef struct AmBuffer  //已发送队列，重传队列，接受侧数据PDU队列
{
	FSM_PKT * pkt;
	PacketStatus  pktstatus;
	u32 pos;
	u32 headLen;
	long segStart[segNumMax];	//-1:无效
	long segEnd[segNumMax];		//-1:无效
	u32 segnum;
	SequenceNumber SN;
	short retxCount;      //-1:未重传，非-1重传计数；
	u32 datalen;
	struct list_head list;
} AmBuffer;

typedef struct Buffer      //状态PDU对列，TM新数据队列
{
	FSM_PKT * pkt;
	struct list_head list;
} CtrlBuffer, TmBuffer;  

typedef struct UmBuffer          //UM数据队列
{
	FSM_PKT * pkt;
	PacketStatus pktstatus;
	u32 pos;
	//	unsigned int headerlen;
	SequenceNumber SN;
	struct list_head list;
} UmBuffer;

typedef  struct pduLeft
{
	short SN5_Left;
	short SN_Left ;
	FSM_PKT *sduLeft;
}pduLeft;

/*the struct of AM instance*/
typedef struct AM_Instance
{
	u16 rnti;
	u8 rbId;
	u8 lcId;
	u16 psn;
	bool statFlag;
	/** Timers in RLC AM mode **/
	evHandle pollRetxTimer;
	long  pollRetxTimerCode;
	Time  pollRetxTimerValue;

	evHandle reorderTimer;
	long reorderTimerCode;
	Time reorderTimerValue;

	evHandle statProhTimer;
	long statProhTimerCode;
	Time statProhTimerValue;
	
	u16 currentStatVar;
	SequenceNumber SN;
	struct pduLeft pduLft;
	/**buffers in RLC AM mode  **/
	/* Transimition buffer */
	struct AmSduBuffer amSduBuffer;
	u32 amSduBufferSize;
	u32 amSduBufferNum;

	struct AmBuffer amTransmittedBuffer;
	u32 amTransmittedBufferSize;
	u32 amTransmittedBufferNum;

	struct AmBuffer amRetxBuffer;
	u32 amRetxBufferSize;
	u32 amRetxBufferNum;

	CtrlBuffer ctrlPduBuffer;
	u32 ctrlPduBufferSize;
	u32 ctrlPduBufferNum;

	struct AmBuffer amRecvBuffer;

#define AM_WINDOW_SIZE 512
	/* transimitting window   */
	struct AmBuffer *amTranWindow[AM_WINDOW_SIZE*2];
	//unsigned int amTranSize;
	/** parameters of TxWindow of AM mode  **/
	SequenceNumber vt_s;
	SequenceNumber vt_a;
	SequenceNumber vt_ms;
	/* Reception window  */
	struct AmBuffer *amRecvWindow[AM_WINDOW_SIZE*2];
	//unsigned int amRecvSize;
	long segStart[segNumMax];
	long segEnd[segNumMax];
	/** parameters of RxWindow of AM mode **/
	SequenceNumber vr_mr;
	SequenceNumber vr_h;
	SequenceNumber vr_x;
	SequenceNumber vr_ms;
	SequenceNumber vr_r;
	/**  **/
	u16 pollPDU;    /*32PDU:组装的PDU数达到该值时触发轮询*/
	u16 pollBYTE;    /*1000KB:组装的PDU数达到该值时触发轮询*/
	u16 maxRetxThreshold;  /* 4:AM模式中PDU的最大重传次数*/
	u16 pduWithoutPoll;   /*组装的未带轮询位的pdu个数*/
	u16 byteWithoutPoll;   /*组装的未带轮询位的pdu字节数*/
	SequenceNumber pollSn;   /*携带轮询位的PDU的SN*/

	struct list_head amList;

} AM_Instance;

/* the struct of the transimit side of UM instance*/
typedef struct UM_TX_Instance
{
	u16 rnti;
	u8 rbid;
	u8 lcid;
	u16 psn;
	/** Timers on the transimitting side of  RLC UM mode **/
	struct UmBuffer umSduBuffer;
	u32 umSduBufferSize;
	u32 umSduBufferNum;
	SequenceNumber SN;

	u16 snFiledLength;     // Size5/size10 :UM 模式PDU中SN域所占的bit
	u8 CurrentStatVar;

	struct list_head umTxList;

} UM_TX_Instance;

/* the struct of the receiving side of UM instance*/
typedef struct UM_RX_Instance
{
	u16 rnti;
	u8 rbId;
	u8 lcId;
	u16 psn;
	u16 snFiledLength;     // Size5/size10 :UM 模式PDU中SN域所占的bit。
	/** Timers in RLC UM mode **/
	evHandle reorderTimer;
	long  reorderTimerCode;
	Time  reorderTimerValue;

	SequenceNumber SN;
	struct pduLeft  pduLft;
	struct UmBuffer umRecvBuffer;
	/* Reception window  */
#define UM_WINDOW_SIZE5 		16
#define UM_WINDOW_SIZE10	 	512
	struct UmBuffer *umRecvWindow5[UM_WINDOW_SIZE5 * 2];
	struct UmBuffer *umRecvWindow10[UM_WINDOW_SIZE10 * 2];
	u32 umRecvSize;
	/** parameters of RxWindow of UM mode **/
	SequenceNumber vr_ur;
	SequenceNumber vr_ux;
	SequenceNumber vr_uh;

	u8 currentStatVar;

	struct list_head umRxList;

} UM_RX_Instance;

/* the struct of the transimit side of TM instance*/
typedef struct TM_TX_Instance
{
	u16 rnti;
	u8 rbId;
	u8 lcId;
	u8 pbCh;
	//u8 currentStatVar ;

	/*  */
	TmBuffer tmSduBuffer;
	u32 tmSduBufferSize;
	u32 tmSduBufferNum;

	struct list_head tmTxList;

} TM_TX_Instance;


/* the struct of the receiving side of TM instance*/
typedef struct TM_RX_Instance
{
	u16 rnti ;
	u8 rbId ;
	u8 lcId ;
	u8 pbCh;
	//u8 currentStatVar ;

	struct list_head tmRxList;

} TM_RX_Instance;

/** structures for segmnet ,resegment, and assamble  **/
typedef struct _pduhdr
{	  
	u16 R1;
	u16 FIfirst;
	u16 FIsecond;
	u16 E;
	u16 SN;		   
}pduhdr;
	
typedef struct _ampduhdr
{	  
	u16 D_C;
	u16 RF;
	u16 P;
	u16 FIfirst;
	u16 FIsecond;
	u16 E;
	u16 SN;		   
}am_pduhdr;

typedef struct um5_pduhdr
{
	u8 FIfirst;
	u8 FIsecond;
	u8 E;
	u8 SN; 	 
}um5_pduhdr;

typedef struct _pduhdrExt
{	  
	u16 E[MAX_NUM];
	u16 LI[MAX_NUM];		   
}pduhExt;

typedef struct ctrlPduPara  //组装状态PDU用
{
	u16 ctrlHdr;  //每次填2字节数据，填好后放入sk_buffer中
	u16 ctrlHdrBits;  //记录ctrlHdr 已填的位数
	//u16 nackSnBits;   //记录NACN_SN已填的位数
	u32 pduLen;  //记录已填PDU字节数
	SequenceNumber sn;  //记录接收数组中空指针所对应的SN
	u32 size;  //记录要组装的状态PDU大小
} ctrlPduPara;

/* The status virables in RLC layer */
typedef struct rlc_sv
{
	/* The type of current instance */
	RlcMode ins_mode;
	RlcTimerType timerType;
	long packetType ;  						//data packet or control packet
	u8 isBufferReq;                    		//指示是否发送缓存报告
	int allocCode[MAX_CODE];             	//保存未分配的code值
	struct  AM_Instance vAm_ins;            //AM实体链表
	struct  UM_RX_Instance vUm_rx_ins;		//UM接收侧实体链表
	struct  UM_TX_Instance vUm_tx_ins;		//UM发送侧实体链表
	struct  TM_RX_Instance vTm_rx_ins;		//TM接收侧实体链表
	struct  TM_TX_Instance vTm_tx_ins;		//TM发送侧实体链表

	evHandle bufferReqTimer;
	long  bufferReqTimerCode;
	Time  bufferReqTimerValue;
	//测试用AM 实体
	struct  AM_Instance amText;
	struct  UM_TX_Instance umText;
	long numflag;
} rlc_sv;

/*** The codes of interruption ****/
/** IOCTL command **/
/* IOCTL between RLC and  RRC */
#define		CRLC_CONFIG_REQ				0x24
#define		CRLC_STATUS_IND				0x25
#define		CRLC_DEACT_REQ				0x26
#define		CRLC_SUSPEND_REQ			0x27
#define		CRLC_RESUME_REQ				0x28
#define		CRLC_BULID_REQ				0x29
//#define		CRLC_BULID_REQ				0x01


/* IOCTRL between RLC and PDCP */
#define		PRLC_DISC_REQ				0x22
#define		PRLC_AM_DATA_CNF			0x21

/* IOCTRL between RLC and MAC */
#define		MRLC_BUFREPORT_REQ			0X0B
#define		MRLC_TRANSOP_IND			0X23

/** Event code in RLC layer **/
#define		_START_WORK					0x00

#define		SEGMENT						0x31
#define		RESEGMENT					0x32
#define		REASSAMBLE					0X33

#define		POLL						0X34
#define		CTRL_PKT_TRAN				0X35
#define		CTRL_PKT_RECV				0X36

#define         CTRL_RBID_BUILD             0X37



/** All statments in RLC FSM  **/
#define		ST_INIT			0
#define 	ST_NULL			1
#define		ST_TRAN 		2
#define		ST_SUSPEND		3

/** Macro Definition **/
#define RLC_PKT_FROM_LOWER  (fsm_ev_type()==FSM_EV_TYPE_PKT_IND)
#define RLC_PKT_FROM_UPPER  (fsm_ev_type()==FSM_EV_TYPE_PKT_REQ)
#define RLC_EV_SELF (fsm_ev_type() == FSM_EV_TYPE_SELF)
//#define RLC_AM_PKT_TO_UPPER  (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == RLC_AM_REORDER_TIMEOUT)
//#define RLC_UM_PKT_TO_UPPER  (fsm_ev_type() == FSM_EV_TYPE_SELF && fsm_ev_code() == RLC_UM_REORDER_TIMEOUT)
//#define RLC_CTRLPKT_CREAT (fsm_ev_type() == FSM_EV_TYPE_SELF  && fsm_ev_code() ==  RLC_STATPRO_TIMEOUT)
//#define RLC_POLLRETX  (fsm_ev_type() == FSM_EV_TYPE_SELF  && fsm_ev_code() == RLC_POLLRETX_TIMEOUT )
#define RLC_OPEN  (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code()== FSM_EV_CORE_OPEN)
#define RLC_CLOSE  (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code() == FSM_EV_CORE_CLOSE)
#define RLC_START_WORK  (fsm_ev_type() == FSM_EV_TYPE_SELF  && fsm_ev_code() ==  _START_WORK)
#define RLC_SUSPEND  (fsm_ev_type() == FSM_EV_TYPE_SELF &&  fsm_ev_code() == CRLC_SUSPEND_REQ)
#define RLC_RESUME  (fsm_ev_type() == FSM_EV_TYPE_SELF &&  fsm_ev_code() == CRLC_RESUME_REQ)
#define RLC_DEACT  (fsm_ev_type() == FSM_EV_TYPE_SELF &&  fsm_ev_code() == CRLC_DEACT_REQ)
#define RLC_IOCTL_ARRIVAL (fsm_ev_type() == FSM_EV_TYPE_CORE && fsm_ev_code() == FSM_EV_IOCTRL)

#define RLC_SEGMENT (fsm_ev_type() == FSM_EV_TYPE_SELF &&  fsm_ev_code() == SEGMENT)
#define RLC_RESEGMENT (fsm_ev_type() == FSM_EV_TYPE_SELF &&  fsm_ev_code() == RESEGMENT)
#define RLC_REASSAMBLE (fsm_ev_type() == FSM_EV_TYPE_SELF &&  fsm_ev_code() == REASSAMBLE)

#define RLC_POLL (fsm_ev_type() == FSM_EV_TYPE_SELF &&  fsm_ev_code() == POLL)
#define RLC_CTRL_PKT_TRAN (fsm_ev_type() == FSM_EV_TYPE_SELF &&  fsm_ev_code() == CTRL_PKT_TRAN)
#define RLC_CTRL_PKT_RECV (fsm_ev_type() == FSM_EV_TYPE_SELF &&  fsm_ev_code() == CTRL_PKT_RECV)


void rlc_main(void);
static void rlc_init_enter(void);
static void  rlc_close(void);
static void rlc_interupt(void);
static void rlc_pkt_receive_from_upper(void);
static void rlc_pkt_receive_from_mac(void);
static void rlc_AM_pkt_receive_from_mac(AM_Instance*amIns,FSM_PKT * pkt);
static void rlc_UM_pkt_receive_from_mac(UM_RX_Instance *umRxIns,FSM_PKT * pkt);
static void rlc_dispose(void);
static void rlc_ioctrl_handler(void);
static void * findInsByCode(long code, RlcTimerType * timer);


void  findInsByRbid(u8 rbid,void **up, void **down , RlcMode *mode) ;
void  findInsBylcid(u8 lcid, void **up, void**down, RlcMode *mode);
bool isInsideTranWin(struct AM_Instance *amIns, SequenceNumber SN);
bool isInsideAmRecvWin(struct AM_Instance * amIns, SequenceNumber SN);
bool isInsideUmRecvWin(struct UM_RX_Instance* umRxIns, SequenceNumber SN);
bool isOrderedUm(struct UM_RX_Instance* umRxIns, SequenceNumber SN);
u16 countSegInd(FSM_PKT *pkt);
void assamble_segment(AmBuffer *ambuf, FSM_PKT *pkt);

/***李栩龙: 分段，在分段和重组  ***/
extern FSM_PKT * rlc_UM_segment(struct UM_TX_Instance *um_tx_ins,u32 size);
extern FSM_PKT * rlc_AM_segment(struct AM_Instance *am_ins,u32 size);
extern FSM_PKT* rlc_resegment(struct AmBuffer *tbuff, u32 sizeFromMac);
extern void rlc_AM_reassemble_deliver(struct AM_Instance *amIns, struct pduLeft *pdu_left,URLC_IciMsg *icimsg);
extern void rlc_UM_reassemble_deliver(struct UM_RX_Instance *umIns, struct pduLeft *pdu_left,URLC_IciMsg *icimsg);
extern void rlc_UM5_reassemble_deliver(struct UM_RX_Instance *umIns, struct pduLeft *pdu_left,URLC_IciMsg *icimsg);

/***张义: 轮询，重传，发送状态报告 ***/
extern void rlc_ctrl_pkt_trans(struct AM_Instance *amIns);
extern void rlc_poll_retx(struct AM_Instance *amIns);
extern void rlc_retx(struct AM_Instance *amIns,struct AmBuffer *amTxedBuffer);
extern void rlc_poll(struct AM_Instance *amIns, FSM_PKT * pkt);
extern void rlc_ctrl_pkt_recv(struct AM_Instance *amIns, FSM_PKT * pkt);
extern void Assemble_Nack(struct Buffer *ctrlBf,ctrlPduPara *ctlPa);
extern void Assemble_Nack_Seg(struct Buffer *ctrlBf,ctrlPduPara *ctlPa,u16 sostart,u16 soend);

extern u16 getSO(u16 *ptr,u16 *amHdr,u32 *pduLen,FSM_PKT *pkt);
extern void getNewData(u16 *ptr,u32 *pduLen,FSM_PKT * pkt,u16 *amHdr);
extern u16 getNackSn(u32 * pduLen,u16 *amHdr,FSM_PKT * pkt,u16 * ptr);
extern void ack_handler(struct AM_Instance *amIns,SequenceNumber ackSn);
extern void so_handler(struct AM_Instance *amIns,SequenceNumber nackSn,bool *isPduFound,long SOstart,long SOend);
extern void no_so_handler(struct AM_Instance *amIns,SequenceNumber nackSn,bool *isPduFound);



#define instance_create(type) ((type*)fsm_mem_alloc(sizeof(type)))
#endif
