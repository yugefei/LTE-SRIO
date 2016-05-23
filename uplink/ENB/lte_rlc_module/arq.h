#ifndef _ARQ_H
#define _ARQ_H
#include "rlcfsm.h"

/***张义: 轮询，重传，发送状态报告 ***/
void rlc_ctrl_pkt_trans(struct AM_Instance *amIns);
void rlc_poll_retx(struct AM_Instance *amIns);
void rlc_retx(struct AM_Instance *amIns,struct AmBuffer *amTxedBuffer);
void rlc_poll(struct AM_Instance *amIns, FSM_PKT * pkt);
void rlc_ctrl_pkt_recv(struct AM_Instance *amIns, FSM_PKT * pkt);
void Assemble_Nack(struct Buffer *ctrlBf,ctrlPduPara *ctlPa);
void Assemble_Nack_Seg(struct Buffer *ctrlBf,ctrlPduPara *ctlPa,u16 sostart,u16 soend);

u16 getSO(u16 *ptr,u16 *amHdr,u32 *pduLen,FSM_PKT *pkt);
void getNewData(u16 *ptr,u32 *pduLen,FSM_PKT * pkt,u16 *amHdr);
u16 getNackSn(u32 * pduLen,u16 *amHdr,FSM_PKT * pkt,u16 * ptr);
void ack_handler(struct AM_Instance *amIns,SequenceNumber ackSn);
void so_handler(struct AM_Instance *amIns,SequenceNumber nackSn,bool *isPduFound,long SOstart,long SOend);
void no_so_handler(struct AM_Instance *amIns,SequenceNumber nackSn,bool *isPduFound);


#endif
