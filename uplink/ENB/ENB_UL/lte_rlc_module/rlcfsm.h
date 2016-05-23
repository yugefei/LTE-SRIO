#include "../fsm/fsmdec.h"

#ifndef _RLCFSM_H
#define _RLCFSM_H

#include <linux/list.h>
#include <linux/types.h>
#include "Rlctypes.h"
//#include "arq.h"

#define SequenceNumber  u16

#define MAX_NUM   16
#define  MAX_CODE   50
#define FLAG 2

/* The types of instances in RLC layer  */
typedef enum {NONE_MODE,TM_MODE=1, UM_MODE=2, AM_MODE=3} RlcMode;
//typedef enum {TM_TX_MODE=1, TM_RX_MODE=2, UM_TX_MODE=3, UM_RX_MODE=4, AM_MODE=5} RlcMode;
typedef enum {POLL_RETX = 1, STAT_PRO = 2, AM_REORDER = 3, UM_REORDER = 4, BUFFER_REQ = 5, PKT_BUF = 6}RlcTimerType;
/** Data Structures Used By RLC **/

typedef enum { FULL_SDU = 1, LAST_SEGMENT = 2, ANY_SEGMENT = 3} PacketStatus;


typedef struct ctrlPduPara  //��װ״̬PDU��
{
	u16 ctrlHdr;  //ÿ����2�ֽ����ݣ���ú����sk_buffer��
	u16 ctrlHdrBits;  //��¼ctrlHdr �����λ��
	u16 nackSnBits;   //��¼NACN_SN�����λ��
	u32 pduLen;  //��¼����PDU�ֽ���
	SequenceNumber sn;  //��¼���������п�ָ������Ӧ��SN
	u32 size;  //��¼Ҫ��װ��״̬PDU��С
} ctrlPduPara;

typedef struct AmSduBuffer     //AM �����ݶ���
{
	FSM_PKT * pkt;
	PacketStatus  pktstatus;
	u32 pos;
	struct list_head  list;
} AmSduBuffer;

typedef struct AmBuffer  //�ѷ��Ͷ��У��ش����У����ܲ�����PDU����
{
	FSM_PKT * pkt;
	PacketStatus  pktstatus;
	u32 pos;
	u32 headLen;
	long segStart[segNumMax];   //-1:��Ч
	long segEnd[segNumMax];
	u32 segnum;
	SequenceNumber SN;
	short retxCount;      //-1:δ�ش�����-1�ش�������
	u32 datalen;
	struct list_head  list;
} AmBuffer;

typedef struct Buffer      //״̬PDU���У�TM�����ݶ���
{
	FSM_PKT * pkt;
	struct list_head  list;
} CtrlBuffer, TmBuffer;  

typedef struct UmBuffer          //UM���ݶ���
{
	FSM_PKT * pkt;
	PacketStatus  pktstatus;
	u32 pos;
	//	unsigned int headerlen;
	SequenceNumber SN;
	struct list_head  list;
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
	u16 rnti ;
	u8 rbId ;
	u8 lcId ;
	u16 psn;
	bool statFlag;
	/** Timers in RLC AM mode **/
	evHandle	 pollRetxTimer ;
	long  pollRetxTimerCode;
	Time  pollRetxTimerValue ;

	evHandle reorderTimer ;
	long  reorderTimerCode;
	Time  reorderTimerValue ;

	evHandle statProhTimer ;
	long  statProhTimerCode;
	Time  statProhTimerValue ;

	u16 currentStatVar ;
	SequenceNumber SN;
	struct pduLeft  pduLft;  //20140915��
	/**buffers in RLC AM mode  **/
	/* Transimition buffer */
	struct  AmSduBuffer amSduBuffer ;
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
	u16 pollPDU;    /*32PDU:��װ��PDU���ﵽ��ֵʱ������ѯ*/
	u16 pollBYTE;    /*1000KB:��װ��PDU���ﵽ��ֵʱ������ѯ*/
	u16 maxRetxThreshold;  /* 4:AMģʽ��PDU������ش�����*/
	u16 pduWithoutPoll;   /*��װ��δ����ѯλ��pdu����*/
	u16 byteWithoutPoll;   /*��װ��δ����ѯλ��pdu�ֽ���*/
	SequenceNumber pollSn;   /*Я����ѯλ��PDU��SN*/

	struct list_head  amList;

} AM_Instance;

/* the struct of the transimit side of UM instance*/
typedef struct UM_TX_Instance
{
	u16 rnti ;
	u8 rbid ;
	u8 lcid ;
	u16 psn;
	/** Timers on the transimitting side of  RLC UM mode **/
	struct UmBuffer umSduBuffer ;
	u32 umSduBufferSize;
	u32 umSduBufferNum;
	SequenceNumber SN;

	u16 snFiledLength;     // Size5/size10 :UM ģʽPDU��SN����ռ��bit
	u8 CurrentStatVar ;

	struct list_head  umTxList;

} UM_TX_Instance;

/* the struct of the receiving side of UM instance*/
typedef struct UM_RX_Instance
{
	u16 rnti ;
	u8 rbId ;
	u8 lcId ;
	u16 psn;
	u16 snFiledLength;     // Size5/size10 :UM ģʽPDU��SN����ռ��bit��
	/** Timers in RLC UM mode **/
	evHandle reorderTimer ;
	long  reorderTimerCode;
	Time  reorderTimerValue ;

	SequenceNumber SN;
	struct pduLeft  pduLft;  //20140915��
	struct UmBuffer umRecvBuffer ;
	/* Reception window  */
#define UM_WINDOW_SIZE5 		16
#define UM_WINDOW_SIZE10	 	512
	struct UmBuffer *umRecvWindow5[UM_WINDOW_SIZE5 * 2];
	struct UmBuffer *umRecvWindow10[UM_WINDOW_SIZE10 * 2];
	unsigned int umRecvSize;
	/** parameters of RxWindow of UM mode **/
	SequenceNumber vr_ur;
	SequenceNumber vr_ux;
	SequenceNumber vr_uh;

	u8 currentStatVar ;

	struct list_head  umRxList;

} UM_RX_Instance;

/* the struct of the transimit side of TM instance*/
typedef struct TM_TX_Instance
{
	u16 rnti ;
	u8 rbId ;
	u8 lcId ;
	u8 pbCh;
	//    u8 currentStatVar ;

	/*  */
	TmBuffer tmSduBuffer ;
	u32 tmSduBufferSize;
	u32 tmSduBufferNum;

 //   struct list_head  tmTxList;

} TM_TX_Instance;


/* the struct of the receiving side of TM instance*/
typedef struct TM_RX_Instance
{
	u16 rnti ;
	u8 rbId ;
	u8 lcId ;
	u8 pbCh;
	//   u8 currentStatVar ;
//   struct list_head  tmRxList;

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

 typedef struct um5_pduhdr  //20140915��
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

/*typedef  struct pduLeft
{
      u16 SN_Left ;
      FSM_PKT *sduLeft;
}Pdu_left;*/

typedef struct RntiManag{
	u16 rnti;
	AM_Instance amIns;
	UM_TX_Instance  umTxIns;
	UM_RX_Instance  umRxIns;
	struct  TM_RX_Instance  ccchRecv; ///�ֲ�CCCH�Ĺ���
	struct  TM_TX_Instance  ccchTran;
	struct  list_head  list;
}RntiManag;


typedef struct packetBuf
{
	FSM_PKT * pkt;
	u32 count;
	struct list_head  list;
}packetBuf;
/* The status virables in RLC layer */
typedef struct rlc_sv
{
	/* The type of current instance */
	RlcMode ins_mode;
	RlcTimerType timerType;
	long 	packetType ;  //data packet or control packet
	u8 isBufferReq;                    //ָʾ�Ƿ��ͻ��汨��
	long allocCode[MAX_CODE];             //����δ�����codeֵ
	struct pduLeft  pduLft;

	struct RntiManag rntiManag;
	struct  TM_TX_Instance  pcchIns; ///ȫ��PCCH ��BCCH�Ĺ���
	struct  TM_TX_Instance  bcchIns;

	evHandle bufferReqTimer;
	long  bufferReqTimerCode;
	Time  bufferReqTimerValue;

	evHandle pktBufTimer;
	long  pktBufTimerCode;
	Time  pktBufTimerValue;

	packetBuf pktBuf;  //����û�ж�Ӧʵ������ݰ�
	u32 pktBufNum;
	u32 pktBufSize;
	u32 count; //for test

	//������AM ʵ��
	struct  AM_Instance amText;
	struct  UM_TX_Instance umText;
} rlc_sv;

/*** The codes of interruption ****/
/** IOCTL command **/
/* IOCTL between RLC and  RRC */
#define 		CRLC_CONFIG_REQ				0x24
#define 		CRLC_STATUS_IND				0x25
#define 		CRLC_DEACT_REQ				0x26
#define 		CRLC_SUSPEND_REQ			0x27
#define 		CRLC_RESUME_REQ				0x28
#define			CRLC_BULID_REQ				0x29

/* IOCTRL between RLC and PDCP */
#define 		PRLC_DISC_REQ				0x22
#define 		PRLC_AM_DATA_CNF			0x21

/* IOCTRL between RLC and MAC */
#define 		MRLC_BUFREPORT_REQ			0X0B
#define			MRLC_TRANSOP_IND			0X23

/** Event code in RLC layer **/
#define 		_START_WORK					0x00

#define			SEGMENT						0x31
#define 		RESEGMENT					0x32
#define 		REASSAMBLE					0X33

#define 		POLL						0X34
#define 		CTRL_PKT_TRAN				0X35
#define 		CTRL_PKT_RECV				0X36


#define         CTRL_RBID_BUILD             0X37



/** All statments in RLC FSM  **/
#define		ST_INIT			0
#define 	ST_NULL			1
#define		ST_TRAN 		2
#define 	ST_SUSPEND		3

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
void rlc_AM_pkt_receive_from_mac(AM_Instance*amIns,FSM_PKT * pkt);
void rlc_UM_pkt_receive_from_mac(UM_RX_Instance *umRxIns,FSM_PKT * pkt);
static void rlc_dispose(void);
static void rlc_ioctrl_handler(void);
void rlc_AM_release(struct AM_Instance *amIns);
void rlc_UMrx_release(struct UM_RX_Instance* umRxIns);
void rlc_UMtx_release(struct UM_TX_Instance* umTxIns);
void  findInsByRbid(u16 rnti,u8 rbid,void **up, void **down , RlcMode *mode) ;
void  findInsBylcid(u16 rnti,u8 lcid, void **up, void**down, RlcMode *mode);
static void * findInsByCode(long code, RlcTimerType * timer);
RntiManag*findUeByRnti(u16 rnti);

bool isInsideTranWin(struct AM_Instance *amIns, SequenceNumber SN);
bool isInsideAmRecvWin(struct AM_Instance * amIns, SequenceNumber SN);
bool isInsideUmRecvWin(struct UM_RX_Instance* umRxIns, SequenceNumber SN);
bool isOrderedUm(struct UM_RX_Instance* umRxIns, SequenceNumber SN);
u16 countSegInd(FSM_PKT *pkt);
void assamble_segment(AmBuffer *ambuf, FSM_PKT *pkt);

/***������: �ֶΣ��ڷֶκ�����  ***/
extern FSM_PKT * rlc_UM_segment(struct UM_TX_Instance *um_tx_ins,u32 size);
extern FSM_PKT * rlc_AM_segment(struct AM_Instance *am_ins,u32 size);
extern FSM_PKT* rlc_resegment(struct AmBuffer *tbuff, u32 sizeFromMac);
extern void rlc_AM_reassemble_deliver(struct AM_Instance *amIns, struct pduLeft *pdu_left,URLC_IciMsg *icimsg);
extern void rlc_UM_reassemble_deliver(struct UM_RX_Instance *umIns, struct pduLeft *pdu_left,URLC_IciMsg *icimsg);
extern void rlc_UM5_reassemble_deliver(struct UM_RX_Instance *umIns, struct pduLeft *pdu_left,URLC_IciMsg *icimsg);


/***����: ��ѯ���ش�������״̬���� ***/
extern void rlc_ctrl_pkt_trans(struct AM_Instance *amIns);
extern void rlc_poll_retx(struct AM_Instance *amIns);
extern void rlc_poll(struct AM_Instance *amIns, FSM_PKT * pkt);
extern void rlc_ctrl_pkt_recv(struct AM_Instance *amIns, FSM_PKT * pkt);

/*void Assemble_Nack(struct Buffer *ctrlBf,ctrlPduPara *ctlPa);
void Assemble_Nack_Seg(struct Buffer *ctrlBf,ctrlPduPara *ctlPa,u16 sostart,u16 soend);
void rlc_retx(struct AM_Instance *amIns,struct AmBuffer *amTxedBuffer);
u16 getSO(u16 *ptr,u16 *amHdr,u32 *pduLen,FSM_PKT *pkt);
void getNewData(u16 *ptr,u32 *pduLen,FSM_PKT * pkt,u16 *amHdr);
u16 getNackSn(u32 * pduLen,u16 *amHdr,FSM_PKT * pkt,u16 * ptr);
void ack_handler(struct AM_Instance *amIns,SequenceNumber ackSn);
void so_handler(struct AM_Instance *amIns,SequenceNumber nackSn,bool *isPduFound,long SOstart,long SOend);
void no_so_handler(struct AM_Instance *amIns,SequenceNumber nackSn,bool *isPduFound);*/



#define instance_create(type) ((type*)fsm_mem_alloc(sizeof(type)))
#endif
