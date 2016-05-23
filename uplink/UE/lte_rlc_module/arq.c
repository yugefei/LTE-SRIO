//#include "rlcfsm.h"
//#include "Rlctypes.h"
#include "arq.h"

/************************************************************************
**Function name: Assemble_Nack()
**Descriptions: Assemble the NackSn field 
**Input: struct Buffer *ctrlBf,ctrlPduPara *ctlPa
**Output: assemble the nackSn field
**Returns:
**Created by: ZhangYi
**Created Date: 2014
**---------------------------------------------------------------------
**Modified by: ZhangYi
**Modified Date: 2014/1016
************************************************************************/

//void Assemble_Nack(struct Buffer *ctrlBf,unsigned short *ctrlHdr,unsigned short *ptr,
						//unsigned short *nptr,unsigned int size,unsigned int *pduLen,unsigned short sn)
void Assemble_Nack(struct Buffer *ctrlBf,ctrlPduPara *ctlPa)

{
	//��NACK_SN
	if( ctlPa->ctrlHdrBits == 16 )
	{
		fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa->ctrlHdr,2);//��ctrlHdr�pkt������
		fsm_skb_put(ctrlBf->pkt,2);
		ctlPa->pduLen += 2;
		ctlPa->ctrlHdr = 0x0000;
		ctlPa->ctrlHdrBits = 0;
	}
	if( ctlPa->ctrlHdrBits <= 6 )
	{
		ctlPa->ctrlHdr += ctlPa->sn << ctlPa->ctrlHdrBits;
		ctlPa->ctrlHdrBits += 10;
		//ctlPa->nackSnBits = 0;
	}
	else
	{
		ctlPa->ctrlHdr += ctlPa->sn << ctlPa->ctrlHdrBits;
		//ctlPa->nackSnBits = 16 - ctlPa->ctrlHdrBits;
		//ctlPa->ctrlHdrBits = 0;

		fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa->ctrlHdr,2);//��ctrlHdr�pkt������
		fsm_skb_put(ctrlBf->pkt,2);
		ctlPa->pduLen += 2;
		ctlPa->ctrlHdr = 0x0000;

		ctlPa->ctrlHdr += ctlPa->sn >> (16 - ctlPa->ctrlHdrBits);
		ctlPa->ctrlHdrBits += ctlPa->ctrlHdrBits - 6;
		//ctlPa->nackSnBits = 0;
	}//NACK_SN����
	if( ctlPa->ctrlHdrBits == 16 )
	{
		fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa->ctrlHdr,2);//��ctrlHdr�pkt������
		fsm_skb_put(ctrlBf->pkt,2);
		ctlPa->pduLen += 2;
		ctlPa->ctrlHdr = 0x0000;
		ctlPa->ctrlHdrBits = 0;
	}
}


/************************************************************************
**Function name: Assemble_Nack_Seg()
**Descriptions: Assemble the nackSn E1 E2 and SOstart SOend fields
**Input: struct Buffer *ctrlBf,ctrlPduPara *ctlPa,u16 sostart,u16 soend
**Output: assemble the nackSn E1 E2 and SOstart SOend fields
**Returns:
**Created by: ZhangYi
**Created Date: 2014
**---------------------------------------------------------------------
**Modified by: ZhangYi
**Modified Date: 2014/1016
************************************************************************/
//void Assemble_Nack_Seg(struct Buffer *ctrlBf,unsigned short *ctrlHdr,unsigned short *ptr,
						//unsigned short *nptr,unsigned int size,unsigned int *pduLen,unsigned short sn,
						//unsigned short sostart,unsigned short soend)
void Assemble_Nack_Seg(struct Buffer *ctrlBf,ctrlPduPara *ctlPa,u16 sostart,u16 soend)

{
	//��NACK_SN
	Assemble_Nack(ctrlBf,ctlPa);
	//��E1
	if( ctlPa->ctrlHdrBits == 16 )
	{
		fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa->ctrlHdr,2);//��ctrlHdr�pkt������
		fsm_skb_put(ctrlBf->pkt,2);
		ctlPa->pduLen += 2;
		ctlPa->ctrlHdr = 0x0000;
		ctlPa->ctrlHdrBits = 0;
	}
	if(((ctlPa->ctrlHdrBits+32)%8==0&&ctlPa->pduLen+(ctlPa->ctrlHdrBits+32)/8<ctlPa->size)||\
			((ctlPa->ctrlHdrBits+32)%8!=0&&ctlPa->pduLen+(ctlPa->ctrlHdrBits+32)/8+1<ctlPa->size))
	{
		ctlPa->ctrlHdr |= 0x0001 << ctlPa->ctrlHdrBits; //��E1Ϊ1
	}
	else
	{
		ctlPa->ctrlHdr &= ~(0x0001 << ctlPa->ctrlHdrBits); //��E1Ϊ0
	}
	ctlPa->ctrlHdrBits+=1;

	//��E2
	if( ctlPa->ctrlHdrBits == 16 )
	{
		fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa->ctrlHdr,2);//��ctrlHdr�pkt������
		fsm_skb_put(ctrlBf->pkt,2);
		ctlPa->pduLen += 2;
		ctlPa->ctrlHdr = 0x0000;
		ctlPa->ctrlHdrBits = 0;
	}
	ctlPa->ctrlHdr |= 0x0001<< ctlPa->ctrlHdrBits; //��E2Ϊ1
	ctlPa->ctrlHdrBits+=1;

	//��SOstart
	if( ctlPa->ctrlHdrBits == 16 )
	{
		fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa->ctrlHdr,2);//��ctrlHdr�pkt������
		fsm_skb_put(ctrlBf->pkt,2);
		ctlPa->pduLen += 2;
		ctlPa->ctrlHdr = 0x0000;
		ctlPa->ctrlHdrBits = 0;
	}
	if( ctlPa->ctrlHdrBits <= 1 )
	{
		ctlPa->ctrlHdr += sostart << ctlPa->ctrlHdrBits;
		ctlPa->ctrlHdrBits += 15;
	}
	else
	{
		ctlPa->ctrlHdr += sostart << ctlPa->ctrlHdrBits;
		fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa->ctrlHdr,2);//��ctrlHdr�pkt������
		fsm_skb_put(ctrlBf->pkt,2);
		ctlPa->pduLen += 2;
		ctlPa->ctrlHdr = 0x0000;
		ctlPa->ctrlHdr += sostart >> (16 - ctlPa->ctrlHdrBits);
		ctlPa->ctrlHdrBits = ctlPa->ctrlHdrBits - 1;
	}

	//��SOend
	if( ctlPa->ctrlHdrBits == 16 )
	{
		fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa->ctrlHdr,2);//��ctrlHdr�pkt������
		fsm_skb_put(ctrlBf->pkt,2);
		ctlPa->pduLen += 2;
		ctlPa->ctrlHdr = 0x0000;
		ctlPa->ctrlHdrBits = 0;
	}
	if( ctlPa->ctrlHdrBits <= 1 )
	{
		ctlPa->ctrlHdr += soend << ctlPa->ctrlHdrBits;
		ctlPa->ctrlHdrBits += 15;
	}
	else
	{
		ctlPa->ctrlHdr += soend << ctlPa->ctrlHdrBits;
		fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa->ctrlHdr,2);//��ctrlHdr�pkt������
		fsm_skb_put(ctrlBf->pkt,2);
		ctlPa->pduLen += 2;
		ctlPa->ctrlHdr = 0x0000;
		ctlPa->ctrlHdr += soend >> (16 - ctlPa->ctrlHdrBits);
		ctlPa->ctrlHdrBits = ctlPa->ctrlHdrBits - 1;
	}
	if(ctlPa->ctrlHdrBits == 16 )
	{
		fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa->ctrlHdr,2);//��ctrlHdr�pkt������
		fsm_skb_put(ctrlBf->pkt,2);
		ctlPa->pduLen += 2;
		ctlPa->ctrlHdr = 0x0000;
		ctlPa->ctrlHdrBits = 0;
	}
}


/************************************************************************
**Function name: getNackSn()
**Descriptions: Get NackSn field
**Input: unsigned int * pduLen,unsigned short *amHdr,FSM_PKT * pkt,unsigned short * ptr
**Output: unsigned int * pduLen,unsigned short *amHdr,unsigned short * ptr
**Returns: the number of the nackSn field
**Created by: ZhangYi
**Created Date: 2014
**---------------------------------------------------------------------
**Modified by: ZhangYi
**Modified Date: 2014
************************************************************************/
u16 getNackSn(u32 * pduLen,u16 *amHdr,FSM_PKT * pkt,u16 * ptr)
{
	u16 nackSn = 0;
	u16 sptr = 0;
	
	if( *ptr == 0 ) //���ʣ��λ��Ϊ0���ٴ�pkt���ݲ���ȡ2�ֽ�����
	{
		getNewData(ptr,pduLen,pkt,amHdr);
	}

	if( *ptr >= 10 )
	{
		nackSn += (*amHdr&(0xffc0>>(*ptr-10)))>>(16-*ptr);  //ȡ10λNACK_SN
		//nackSn += ((*amHdr)&0xffc0) >> 6;  //ȡ10λNACK_SN
		*ptr -= 10;
	}
	else
	{
		nackSn += (*amHdr&(0xffc0<<(10-*ptr)))>>(16-*ptr);
		sptr = *ptr;
		*ptr = 0;
		getNewData(ptr,pduLen,pkt,amHdr);
		if( *ptr == 8 )
		{
			nackSn += (*amHdr)&(0xff>>(sptr-2))<<sptr;
			*ptr -= 10 - sptr;
		}
		else  //��*ptr == 16
		{
			nackSn += (*amHdr)&(0xffff>>(sptr+6))<<sptr;
			*ptr -= 10 - sptr;
		}
	}
	return nackSn;
}


/************************************************************************
**Function name: getNewData()
**Descriptions: Get new data from pkt->data to amHdr
**Input: unsigned short *ptr,unsigned int *pduLen,FSM_PKT * pkt
**Output: unsigned short *ptr,unsigned int *pduLen,unsigned short *amHdr
**Returns:
**Created by: ZhangYi
**Created Date: 2014
**---------------------------------------------------------------------
**Modified by: ZhangYi
**Modified Date: 2014
************************************************************************/
void getNewData(u16 *ptr,u32 *pduLen,FSM_PKT * pkt,u16 *amHdr)
{
	u8 mhdr = 0x00;
	
	*amHdr = 0x0000;
	if( *pduLen >= 2 )
	{
		*ptr = 16;
		fsm_mem_cpy(amHdr,pkt->data,2);
		fsm_skb_pull(pkt,2);
		*pduLen -= 2;
	}
	else if( *pduLen == 1 )
	{
		*ptr = 8;
		fsm_mem_cpy(&mhdr,pkt->data,1);
		fsm_skb_pull(pkt,1);
		*amHdr = (u32)mhdr;
		*amHdr <<= 8;
		*pduLen--;
	}
}


/************************************************************************
**Function name: getSO()
**Descriptions: Get SOStart or SOEnd field
**Input: unsigned short *ptr,unsigned short *amHdr,unsigned int *pduLen,FSM_PKT *pkt
**Output: unsigned short *ptr,unsigned short *amHdr,unsigned int *pduLen
**Returns: the number of the SOstart or SOend field
**Created by: ZhangYi
**Created Date: 2014
**---------------------------------------------------------------------
**Modified by: ZhangYi
**Modified Date: 2014
************************************************************************/
u16 getSO(u16 *ptr,u16 *amHdr,u32 *pduLen,FSM_PKT *pkt)
{
	u16 SO = 0;
	u16 soptr = 0;
	
	if( *ptr == 0 )
	getNewData(ptr,pduLen,pkt,amHdr);
	if( *ptr >= 15 )
	{
		SO += (*amHdr&(0xfffe>>(*ptr-15)))>>(16-*ptr);
		*ptr -= 15;
	}
	else
	{
		SO += (*amHdr&(0xfffe<<(15-*ptr)))>>(16-*ptr);
		soptr = *ptr;
		*ptr = 0;
		getNewData(ptr,pduLen,pkt,amHdr);
		if( *ptr == 8 )
		{
			SO += (*amHdr&(0xff>>(soptr-7)))<<soptr;
			*ptr -= 15 - soptr;
		}
		else //��*ptr == 16
		{
			SO += (*amHdr)&(0xffff>>(soptr+1))<<soptr;
			*ptr -= 15 - soptr;
		}
	}
	return SO;
}


/************************************************************************
**Function name: size_of_ctrl_pdu()
**Descriptions: Calculate the size of the ctrl pdu
**Input: struct AM_Instance *amIns
**Output: 
**Returns: the size of the ctrl pdu
**Created by: ZhangYi
**Created Date: 2014/10/15
**---------------------------------------------------------------------
**Modified by: 
**Modified Date: 
************************************************************************/
u32 size_of_ctrl_pdu(struct AM_Instance *amIns)
{
	u32 size = 0;
	int i;
	//����״̬PDU��С
	size = 15;  //ǰ�����̶����С
	if( amIns->vr_r < amIns->vr_h -1 )  //��ǰ���ն����е�PDUδȫ���ɹ�����
	{
		for( i = amIns->vr_r; i < amIns->vr_ms; i++)
		{
			//sn = i;
			if( amIns->amRecvWindow[i] == NULL )
			{
				size += 12;
			}
			else //��ʾ��PDU�Ѿ��յ����ֶַ�
			{
				if( amIns->amRecvWindow[i]->pktstatus != FULL_SDU)
				{
					if( amIns->amRecvWindow[i]->segStart[0] > 0 )
					{
						size += 42;
					}
					if( amIns->amRecvWindow[i]->pktstatus ==  LAST_SEGMENT)
					{
						size += (amIns->amRecvWindow[i]->segnum - 1)*42;
					}
					else if( amIns->amRecvWindow[i]->pktstatus ==  ANY_SEGMENT)
					{
						size += amIns->amRecvWindow[i]->segnum*42;
					}
				}
			}
		}
	}
	if( size%8 == 0 )
	{
		size /= 8;
	}
	else
	{
		size = size / 8 + 1;
	}
	return size;
}
/************************************************************************
**Function name: rlc_ctrl_pkt_trans()
**Descriptions: Assemble ctrl PDU and add to the ctrl buffer
**Input: struct AM_Instance *amIns
**Output: Assemble ctrl PDU and add to the ctrl buffer
**Returns:
**Created by: ZhangYi
**Created Date: 2014
**---------------------------------------------------------------------
**Modified by: ZhangYi
**Modified Date: 2014
************************************************************************/
void rlc_ctrl_pkt_trans(struct AM_Instance *amIns)
{
	struct Buffer *ctrlBf;
	SequenceNumber sn;  //��¼���������п�ָ������Ӧ��SN
	int i;
	int j;
	u16 soStart;
	u16 soEnd;
	//unsigned short ctrlHdr = 0;  //ÿ����2bits���ݣ���ú����sk_buffer��
	u16 mHdr = 0;      //����ֻʣ���1bitʱ����ctrlHdr������ͬ
	//unsigned short ctrlHdrBits = 0;  //��¼ctrlHdr �����λ��
	//unsigned short nackSnBits = 0; //��¼NACN_SN�����λ��
	//unsigned int pduLen = 0;  //��¼����PDU�ֽ���
	u32 size;  //��¼Ҫ��װ��״̬PDU��С
	struct ctrlPduPara ctlPa;
	
	FIN(rlc_ctrl_pkt_trans());

	fsm_printf("[RLC][rlc_ctrl_pkt_trans] entering rlc_ctrl_pkt_trans()\n");
	ctlPa.ctrlHdr = 0;
	ctlPa.ctrlHdrBits = 0;
	//ctlPa.nackSnBits = 0;
	ctlPa.pduLen = 0;
	//SV_PTR_GET(rlc_sv);
	//����״̬PDU��С
	size = size_of_ctrl_pdu(amIns);
	if( size == 0)
	{
		fsm_printf("[RLC][rlc_ctrl_pkt_trans] the ctrl buffer is empty\n");
		return;
	}
	
	ctrlBf = (struct Buffer *)fsm_mem_alloc(sizeof(struct Buffer));
	ctrlBf->pkt = fsm_pkt_create(size);
	ctlPa.ctrlHdr = 0x0000;	//��D/C��CPT��
	ctlPa.ctrlHdr += amIns->vr_ms << 4; //��ACK_SN��
	ctlPa.ctrlHdrBits = 14;
	fsm_printf("[RLC][rlc_ctrl_pkt_trans] vr_ms = %d\n",amIns->vr_ms);

	//if( amIns->vr_r == amIns->vr_h -1 )  //��ǰ���ն����е�PDU���ѳɹ�����
	if( size == 2 )  //��ǰ���ն����е�PDU���ѳɹ�����
	{
		fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa.ctrlHdr,2);
		fsm_skb_put(ctrlBf->pkt,2);
		ctlPa.pduLen += 2;
	}
	else
	{
		ctlPa.ctrlHdr |= 0x0001<<14;	//���һ���E1
		ctlPa.ctrlHdrBits += 1;
		for( i = amIns->vr_r; i < amIns->vr_ms && ctlPa.pduLen < size; i++ )
		{
			sn = i;
			if(amIns->amRecvWindow[i] == NULL)  //��ʾ����PDU��û�յ�
			{
				if( ((ctlPa.ctrlHdrBits+12)%8==0&&ctlPa.pduLen+(ctlPa.ctrlHdrBits+12)/8<=size) || \
						((ctlPa.ctrlHdrBits+12)%8!=0&&ctlPa.pduLen+(ctlPa.ctrlHdrBits+12)/8+1<=size))
				{
					ctlPa.sn = sn;
					ctlPa.size = size;
					Assemble_Nack(ctrlBf,&ctlPa);
					if( ctlPa.ctrlHdrBits == 16 )
					{
						fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa.ctrlHdr,2);//��ctrlHdr�pkt������
						fsm_skb_put(ctrlBf->pkt,2);
						ctlPa.pduLen += 2;
						ctlPa.ctrlHdr = 0x0000;
						ctlPa.ctrlHdrBits = 0;
					}
					if((ctlPa.ctrlHdrBits%8==0&&ctlPa.pduLen+ctlPa.ctrlHdrBits/8<size)||\

							(ctlPa.ctrlHdrBits%8!=0&&ctlPa.pduLen+ctlPa.ctrlHdrBits/8+1<size))
					{
						ctlPa.ctrlHdr |= 0x0001 << ctlPa.ctrlHdrBits; //��E1Ϊ1
					}
					else
					{
						ctlPa.ctrlHdr &= ~(0x0001<<ctlPa.ctrlHdrBits); //��E1Ϊ0
					}
					ctlPa.ctrlHdrBits += 1;

					if( ctlPa.ctrlHdrBits == 16 )
					{
						fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa.ctrlHdr,2);//��ctrlHdr�pkt������
						fsm_skb_put(ctrlBf->pkt,2);
						ctlPa.pduLen += 2;
						ctlPa.ctrlHdr = 0x0000;
						ctlPa.ctrlHdrBits = 0;
					}
					ctlPa.ctrlHdr &= ~(0x0001<<ctlPa.ctrlHdrBits);  //��E2Ϊ0
					ctlPa.ctrlHdrBits += 1;
				}
				else
				{
					break;
				}
			}
			else
			{
				if( amIns->amRecvWindow[i]->pktstatus != FULL_SDU)  //��ʾ���ֶַ�û���յ�
				{
					if( amIns->amRecvWindow[i]->segStart[0] > 0 )
					{
						soStart = 0;
						soEnd = amIns->amRecvWindow[i]->segStart[0];
						ctlPa.sn = sn;
						ctlPa.size = size;
						Assemble_Nack_Seg(ctrlBf,&ctlPa,soStart,soEnd);
					}
					if( amIns->amRecvWindow[i]->pktstatus == ANY_SEGMENT)  //��ʾ���һ���ֶ�û���յ�
					{
						soStart = amIns->amRecvWindow[i]->segEnd[amIns->amRecvWindow[i]->segnum-1];
						soEnd = 0x7fff;
						ctlPa.sn = sn;
						ctlPa.size = size;
						Assemble_Nack_Seg(ctrlBf,&ctlPa,soStart,soEnd);
					}
					for( j = 0; j < amIns->amRecvWindow[i]->segnum - 1; j++ )
					{
						soStart = amIns->amRecvWindow[i]->segEnd[j];
						soEnd = amIns->amRecvWindow[i]->segStart[j+1];
						ctlPa.sn = sn;
						ctlPa.size = size;
						Assemble_Nack_Seg(ctrlBf,&ctlPa,soStart,soEnd);
					}
				}
			}
		}
		if( size - ctlPa.pduLen == 1 )
		{
			mHdr = (unsigned char)(ctlPa.ctrlHdr>>8);
			fsm_mem_cpy(ctrlBf->pkt->tail,&mHdr,1);//��mHdr�pkt������
			fsm_skb_put(ctrlBf->pkt,1);
			ctlPa.pduLen += 1;
			mHdr = 0x00;
			ctlPa.ctrlHdrBits = 0;
		}
		else if( size - ctlPa.pduLen == 2 )
		{
			fsm_mem_cpy(ctrlBf->pkt->tail,&ctlPa.ctrlHdr,2);//��ctrlHdr�pkt������
			fsm_skb_put(ctrlBf->pkt,2);
			ctlPa.pduLen += 2;
			ctlPa.ctrlHdr = 0x0000;
			ctlPa.ctrlHdrBits = 0;
		}
	}
	amIns->ctrlPduBufferNum++;
	amIns->ctrlPduBufferSize += ctrlBf->pkt->len;
	fsm_printf("[RLC][rlc_ctrl_pkt_trans] ctrlPduBufferNum = %d, ctlPduSize = %d\n",amIns->ctrlPduBufferNum,amIns->ctrlPduBufferSize);
	list_add_tail(&ctrlBf->list,&amIns->ctrlPduBuffer.list);
	fsm_octets_print(ctrlBf->pkt->data,10);
	amIns->statFlag = false;
	FOUT;
}



/************************************************************************
**Function name: rlc_poll_retx()
**Descriptions: Move the PDU whose sn == vt_s - 1 to retxbuffer
**Input: struct AM_Instance *amIns
**Output: Move the PDU whose sn == vt_s - 1 to retxbuffer
**Returns:
**Created by: ZhangYi
**Created Date: 2014
**---------------------------------------------------------------------
**Modified by: ZhangYi
**Modified Date: 2014
************************************************************************/
void rlc_poll_retx(struct AM_Instance *amIns)
{
	struct AmBuffer *amTxedBuffer;
	struct AmBuffer * pos;
	//struct list_head* pos;
	struct AmBuffer *nposBf;
	//struct AmBuffer *amTxedBf;
	struct AmBuffer *amRetxBf;  //�����ش����������е�PDU
	CRLC_StatusInd_IoctrlMsg *mioctrl;
	int i;
	
	FIN(rlc_poll_retx());
	fsm_printf("[RLC][rlc_poll_retx] entering rlc_poll_retx() function\n");
	//�ѷ��Ͷ��в�Ϊ��
	if( !list_empty(&amIns->amTransmittedBuffer.list) )
	{
		fsm_printf("[RLC][rlc_poll_retx] rlc_poll_retx() anTransmittedBuffer is not empty\n");

		//for( pos = amIns->amTransmittedBuffer.list.prev; pos != &amIns->amTransmittedBuffer.list; pos = pos->prev )
		list_for_each_entry_safe(amTxedBuffer, pos, &amIns->amTransmittedBuffer.list,list)
		{
			//amTxedBuffer = list_entry(pos,struct AmBuffer,list);
			//if( amTxedBuffer->SN >= amIns->vt_a && amTxedBuffer->SN < amIns->vt_s)
			if( amTxedBuffer->SN == amIns->vt_s - 1 )
			{              
				if( amTxedBuffer->retxCount == -1 )
				{
					amTxedBuffer->retxCount = 0;
				}
				else
				{
					amTxedBuffer->retxCount++;
				}
				fsm_printf("[RLC][rlc_poll_retx] the pdu of rlc_poll_retx's SN is %d\n",amTxedBuffer->SN);
				fsm_printf("[RLC][rlc_poll_retx] the retxCount is %d, the maxThreshold is %d\n",amTxedBuffer->retxCount,amIns->maxRetxThreshold);
				//����ﵽ����ش������򱨸���߲�
				if( amTxedBuffer->retxCount == amIns->maxRetxThreshold )
				{
					fsm_printf("[RLC][rlc_poll_retx] has reach the maxRetxThreshold\n");
					mioctrl = (CRLC_StatusInd_IoctrlMsg*)fsm_mem_alloc(sizeof(CRLC_StatusInd_IoctrlMsg));
					mioctrl->eventCode = 0;
					mioctrl->rbIdentity = amIns->rbId;					
					//fsm_do_ioctrl(STRM_TO_RRC, CRLC_STATUS_IND, (void*)mioctrl, sizeof(CRLC_StatusInd_IoctrlMsg));
					fsm_mem_free(mioctrl);
					mioctrl = NULL;
					//���ش�����ɾ��PDU
					if( !list_empty(&amIns->amRetxBuffer.list) )
					{
						list_for_each_entry_safe(amRetxBf, nposBf, &amIns->amRetxBuffer.list,list)
						{
							if( amRetxBf->SN == amTxedBuffer->SN )
							{
								if( amRetxBf->pktstatus != FULL_SDU )
								{
									for( i = 0; i < amRetxBf->segnum; i++)
									{
										if( amRetxBf->segStart[i] != -1 )
										{
											amIns->amRetxBufferSize -= amRetxBf->segEnd[i] - amRetxBf->segStart[i];
										}					
									}
									amIns->amRetxBufferSize -= amRetxBf->headLen;
								}
								else
								{
									amIns->amRetxBufferSize -= amRetxBf->pkt->len;
								}
								amIns->amRetxBufferNum--;
								list_del(&amRetxBf->list);
								if(amRetxBf->pkt != NULL)
								{
									fsm_pkt_destroy( amRetxBf->pkt );
									amRetxBf->pkt = NULL;
								}
								if(amRetxBf != NULL)
								{
									fsm_mem_free(amRetxBf);
									amRetxBf = NULL;
								}						
								break;
							}
						}
					//nposBf = NULL;
					}

					//���ѷ��Ͷ���ɾ��PDU
					//pos = pos->next;
					amIns->amTransmittedBufferSize -= amTxedBuffer->pkt->len;
					amIns->amTransmittedBufferNum--;
					if(amTxedBuffer->pkt != NULL)
					{
						fsm_pkt_destroy( amTxedBuffer->pkt );
						amTxedBuffer->pkt = NULL;
					}					
					list_del(&amTxedBuffer->list);
					if(amTxedBuffer != NULL)
					{
						fsm_mem_free(amTxedBuffer);
						amTxedBuffer = NULL;
					}										
					fsm_printf("[RLC][rlc_poll_retx] retx amretxbuffersize is %d\n",amIns->amRetxBufferSize);
				}
				else
				{
					fsm_printf("[RLC][rlc_poll_retx] rlc_poll_retx pdu has not reach maxRetxThreshold\n");
					rlc_poll(amIns,amTxedBuffer->pkt);	//������ѯλ	
					rlc_retx(amIns,amTxedBuffer);
					break;
				}
			}
		}
	}
	else
	{
		fsm_printf("[RLC][rlc_poll_retx] amTransmittedBuffer is empty\n");
	}
	FOUT;
}



/************************************************************************
**Function name: rlc_retx()
**Descriptions: move the PDU which need to be retransimitted to the retx buffer,and duplicate another one to the transmitted buffer,
				if the PDU has been in the retx buffer then remove it
**Input: struct AM_Instance *amIns,struct AmBuffer *amTxedBuffer
**Output: move the PDU which need to be retransimitted to the retx buffer,and duplicate another one to the transmitted buffer,
				if the PDU has been in the retx buffer then remove it
**Returns:
**Created by: ZhangYi
**Created Date: 2014
**---------------------------------------------------------------------
**Modified by: ZhangYi
**Modified Date: 2014
************************************************************************/
void rlc_retx(struct AM_Instance *amIns,struct AmBuffer *amTxedBuffer)
{
	struct AmBuffer *amTxedBf;
	struct AmBuffer *amRetxBf;
	struct AmBuffer *nposBf;
	int i;
	
	FIN(rlc_retx());
	fsm_printf("[RLC][rlc_retx] entering rlc_retx() function\n");
	//����ش����������ж�Ӧ��PDU���Ƚ���ɾ��
	if( !list_empty(&amIns->amRetxBuffer.list) )
	{
		list_for_each_entry_safe(amRetxBf, nposBf, &amIns->amRetxBuffer.list,list)
		{
			if( amRetxBf->SN == amTxedBuffer->SN )
			{
				if( amRetxBf->pktstatus != FULL_SDU )
				{
					for( i = 0; i < amRetxBf->segnum; i++)
					{
						if( amRetxBf->segStart[i] != -1 )
						{
							amIns->amRetxBufferSize -= amRetxBf->segEnd[i] - amRetxBf->segStart[i];
						}					
					}
					amIns->amRetxBufferSize -= amRetxBf->headLen;
				}
				else
				{
					amIns->amRetxBufferSize -= amRetxBf->pkt->len;
				}
				amIns->amRetxBufferNum--;
				if(amRetxBf->pkt != NULL)
				{
					fsm_pkt_destroy( amRetxBf->pkt );
					amRetxBf->pkt = NULL;
				}				
				list_del(&amRetxBf->list);
				if(amRetxBf != NULL)
				{
					fsm_mem_free(amRetxBf);
					amRetxBf = NULL;
				}				
				break;
			}
		}
		//nposBf = NULL;
	}
	
	//�Ƶ��ش�����
	amIns->amTransmittedBufferSize -= amTxedBuffer->pkt->len;
	amIns->amTransmittedBufferNum--;
	list_del(&amTxedBuffer->list);
	list_add_tail(&amTxedBuffer->list,&amIns->amRetxBuffer.list);
	if( amTxedBuffer->pktstatus != FULL_SDU )
	{
		for( i = 0; i < amTxedBuffer->segnum; i++)
		{
			if( amTxedBuffer->segStart[i] != -1 )
			{
				amIns->amRetxBufferSize += amTxedBuffer->segEnd[i] - amTxedBuffer->segStart[i];
			}					
		}
		amIns->amRetxBufferSize += amTxedBuffer->headLen;
	}
	else
	{
		amIns->amRetxBufferSize += amTxedBuffer->pkt->len;
	}
	amIns->amRetxBufferNum++;

	//�ٸ���һ�ݵ��ѷ��Ͷ���
	amTxedBf = (struct AmBuffer *)fsm_mem_alloc(sizeof(struct AmBuffer));
	//amTxedBf->pkt = fsm_pkt_create(amTxedBuffer->pkt->len+fsm_skb_headroom(amTxedBuffer->pkt));
	amTxedBf->pkt = fsm_pkt_duplicate(amTxedBuffer->pkt);
	//fsm_mem_cpy(amTxedBf->pkt->data,amTxedBuffer->pkt->data,amTxedBuffer->pkt->len);
	//fsm_skb_put(amTxedBf->pkt,amTxedBuffer->pkt->len);
	amTxedBf->datalen = amTxedBuffer->datalen;
	amTxedBf->headLen = amTxedBuffer->headLen;
	amTxedBf->pktstatus = amTxedBuffer->pktstatus;
	amTxedBf->pos = amTxedBuffer->pos;
	amTxedBf->retxCount = amTxedBuffer->retxCount;
	amTxedBf->segnum = amTxedBuffer->segnum;
	for( i = 0;i < amTxedBuffer->segnum; i++)
	{
		amTxedBf->segStart[i] = amTxedBuffer->segStart[i];
		amTxedBf->segEnd[i] = amTxedBuffer->segEnd[i];
	}
	amTxedBf->SN = amTxedBuffer->SN;
	list_add_tail(&amTxedBf->list,&amIns->amTransmittedBuffer.list);
	amIns->amTransmittedBufferSize += amTxedBf->pkt->len;
	amIns->amTransmittedBufferNum++;
	FOUT;
}


/************************************************************************
**Function name: rlc_poll()
**Descriptions: Set polling bit to 1
**Input: struct AM_Instance *amIns, FSM_PKT * pkt
**Output: set the polling bit in the head of the PDU to 1
**Returns:
**Created by: ZhangYi
**Created Date: 2014
**---------------------------------------------------------------------
**Modified by: ZhangYi
**Modified Date: 2014
************************************************************************/
void rlc_poll(struct AM_Instance *amIns, FSM_PKT * pkt)
{
	//u16 amHdr = 0x0000; //����AM PDUͷ��
	RLC_AMPDU_fixhead * amHdr;
	
	FIN(rlc_poll());
	//SV_PTR_GET(rlc_sv);
	fsm_printf("[RLC][rlc_poll] entring rlc_poll()\n");
	//fsm_mem_cpy(&amHdr,pkt->data,2);//ȡͷ��
	amHdr = (RLC_AMPDU_fixhead *)pkt->data;
	if(amHdr->P!=1)
	{
		amHdr->P = 1;
	}
	/*if( (amHdr&0x2000)>>13 == 0 )
	{
		amHdr|=1<<13; //��pollingλ��1
	}
	fsm_mem_cpy(pkt->data,&amHdr,2);//��ͷ��*/
	amIns->pduWithoutPoll = 0;
	amIns->byteWithoutPoll = 0;
	amIns->pollSn = amIns->vt_s - 1;
	if(amIns->pollRetxTimer)
	{
		fsm_schedule_cancel(amIns->pollRetxTimer);
		amIns->pollRetxTimer = 0;
	}
	amIns->pollRetxTimer = fsm_schedule_self(amIns->pollRetxTimerValue,amIns->pollRetxTimerCode);
	fsm_printf("[RLC][rlc_poll] pollretxTimer start\n");
	//FOUT;
}




/**********************************************************************************************
**Function name: ack_handler()
**Descriptions: After reveiving a ctrl PDU, handle the corresponding PDUs according to the ackSn in the ctrl PDU
**Input: struct AM_Instance *amIns, SequenceNumber ackSn
**Output: Remove the PDUs whose sn < ackSn in the amTransmittedBuffer and amRetxBuffer
**Returns:
**Created by: ZhangYi
**Created Date: 2014
**----------------------------------------------------------------------------------
**Modified by: ZhangYi
**Modified Date: 2014/10/13
**********************************************************************************************/
void ack_handler(struct AM_Instance *amIns,SequenceNumber ackSn)   //20141013
{
	struct AmBuffer *amTxedBuffer;  //�ѷ��Ͷ��нڵ�
	//struct AmBuffer *amTxedBf;
	struct AmBuffer *amRetxBf;
	struct AmBuffer * nposBf;
	struct AmBuffer * reposBf;
	int i;
	while( amIns->vt_a < ackSn && amIns->vt_a < amIns->vt_s)
	{
		if( amIns->vt_a == amIns->pollSn )
		{
			//ֹͣ����λ�ش���ʱ��
			if(amIns->pollRetxTimer)
			{
				fsm_schedule_cancel(amIns->pollRetxTimer);
				amIns->pollRetxTimer = 0;
			}
		}
      
		//��vt_a���ѷ��Ͷ���ɾ��
		if( !list_empty(&amIns->amTransmittedBuffer.list) )
		{
			list_for_each_entry_safe(amTxedBuffer, nposBf, &amIns->amTransmittedBuffer.list,list)
			{
				if( amTxedBuffer->SN == amIns->vt_a )
				{
					amIns->amTransmittedBufferSize -= amTxedBuffer->pkt->len;
					amIns->amTransmittedBufferNum--;
					if(amTxedBuffer->pkt != NULL)
					{
						fsm_pkt_destroy( amTxedBuffer->pkt );
						amTxedBuffer->pkt = NULL;
					}				
					list_del(&amTxedBuffer->list);
					if(amTxedBuffer != NULL)
					{
						fsm_mem_free(amTxedBuffer);
						amTxedBuffer = NULL;
					}					
					break;
				}
			}
			//nposBf = NULL;
		}
		
		//��vt_a���ش�����ɾ��
		if( !list_empty(&amIns->amRetxBuffer.list) )
		{
			list_for_each_entry_safe(amRetxBf, nposBf, &amIns->amRetxBuffer.list,list)
			{
				if( amRetxBf->SN == amIns->vt_a )
				{
					for( i = 0; i <amRetxBf->segnum; i++)
					{
						amIns->amRetxBufferSize -= amRetxBf->segEnd[i] - amRetxBf->segStart[i];
					}
					amIns->amRetxBufferSize -= amRetxBf->headLen;
					amIns->amRetxBufferNum--;
					if(amRetxBf->pkt != NULL)
					{
						fsm_pkt_destroy( amRetxBf->pkt );
						amRetxBf->pkt = NULL;
					}					
					list_del(&amRetxBf->list);
					if(amRetxBf != NULL)
					{
						fsm_mem_free(amRetxBf);
						amRetxBf = NULL;
					}					
					break;
				}
			}
			//nposBf = NULL;
		}
		amIns->vt_a++;
	}
	amIns->vt_ms = amIns->vt_a + AM_WINDOW_SIZE;
}


/**********************************************************************************************
**Function name: so_handler()
**Descriptions: Handle the corresponding PDU segments according to the nackSn and SO fields
**Input: struct AM_Instance *amIns,SequenceNumber nackSn,bool *isPduFound,int SOstart,int SOend
**Output: Retx or remove the PDUs segments whose sn == nackSn
**Returns:
**Created by: ZhangYi
**Created Date: 2014
**----------------------------------------------------------------------------------
**Modified by: ZhangYi
**Modified Date: 2014/10/13
**********************************************************************************************/
void so_handler(struct AM_Instance *amIns,SequenceNumber nackSn,bool *isPduFound,long SOstart,long SOend)
{
	struct AmBuffer *amTxedBuffer;	//�ѷ��Ͷ��нڵ�
	//struct AmBuffer *amTxedBf;
	struct AmBuffer *amRetxBf;
	struct AmBuffer * nposBf;
	struct AmBuffer * reposBf;
	CRLC_StatusInd_IoctrlMsg *mioctrl;
	int i;
	
	if( !list_empty(&amIns->amTransmittedBuffer.list) )
	{
		list_for_each_entry_safe(amTxedBuffer, nposBf, &amIns->amTransmittedBuffer.list,list)
		{
			if( nackSn == amTxedBuffer->SN )
			{
				*isPduFound = true;
				for( i = 0; i < amTxedBuffer->segnum; i++ )
				{
					if(amTxedBuffer->segStart[i]==SOstart&&amTxedBuffer->segEnd[i]==SOend)
					{
						break;
					}
				}
				if( i == amTxedBuffer->segnum )
				{
					amTxedBuffer->segStart[amTxedBuffer->segnum] = SOstart;
					if( SOend == 0x7fff ) //��ʾΪ���һ���ֶ�
					{
						amTxedBuffer->segEnd[amTxedBuffer->segnum] = amTxedBuffer->pkt->len;
					}
					else
					{
						amTxedBuffer->segEnd[amTxedBuffer->segnum] = SOend;
					}
					amTxedBuffer->segnum++;
				}		  
	
				//�����ش�����retxCount
				if( amTxedBuffer->retxCount == -1 )   //��ʾ�״��ش�
				{
					amTxedBuffer->retxCount = 0;
				}
				else
				{
					amTxedBuffer->retxCount++;
				}
				//����ﵽ����ش������򱨸���߲�
				if( amTxedBuffer->retxCount == amIns->maxRetxThreshold )
				{
					mioctrl = (CRLC_StatusInd_IoctrlMsg*)fsm_mem_alloc(sizeof(CRLC_StatusInd_IoctrlMsg));
					mioctrl->eventCode = 0;
					mioctrl->rbIdentity = amIns->rbId;
					//fsm_do_ioctrl(STRM_TO_RRC, CRLC_STATUS_IND, (void*)mioctrl, sizeof(CRLC_StatusInd_IoctrlMsg));
					fsm_mem_free(mioctrl);
					mioctrl = NULL;
					//���ѷ��Ͷ���ɾ��PDU
					amIns->amTransmittedBufferSize -= amTxedBuffer->pkt->len;
					amIns->amTransmittedBufferNum--;
					fsm_pkt_destroy( amTxedBuffer->pkt );
					amTxedBuffer->pkt = NULL;
					list_del(&amTxedBuffer->list);
					fsm_mem_free(amTxedBuffer);
					amTxedBuffer = NULL;
					//���ش�����ɾ��PDU
					if( !list_empty(&amIns->amRetxBuffer.list) )
					{
						list_for_each_entry_safe(amRetxBf, reposBf, &amIns->amRetxBuffer.list,list)
						{
							if( amRetxBf->SN == nackSn)
							{
								if( amRetxBf->pktstatus != FULL_SDU )
								{
									for( i = 0; i < amRetxBf->segnum; i++)
									{
										if( amRetxBf->segStart[i] != -1 )
										{
											amIns->amRetxBufferSize -= amRetxBf->segEnd[i] - amRetxBf->segStart[i];
										}					
									}
									amIns->amRetxBufferSize -= amRetxBf->headLen;
								}
								else
								{
									amIns->amRetxBufferSize -= amRetxBf->pkt->len;
								}
								amIns->amRetxBufferNum--;
								fsm_pkt_destroy( amRetxBf->pkt );
								amRetxBf->pkt = NULL;
								list_del(&amRetxBf->list);
								fsm_mem_free(amRetxBf);
								amRetxBf= NULL;
								break;
							}
						}
					}
				}
				else
				{
					//rlc_retx(amIns,amTxedBuffer);
					fsm_printf("[RLC][rlc_ctrl_pkt_recv] run to rlc_retx()\n");
				}
				break;
			}
		}
	}
	FOUT;
}


/**********************************************************************************************
**Function name: no_so_handler()
**Descriptions: Handle the corresponding PDU segments according to the nackSn and SO fields
**Input: struct AM_Instance *amIns,SequenceNumber nackSn,bool *isPduFound,int SOstart,int SOend
**Output: Retx or remove the PDUs segments whose sn == nackSn
**Returns:
**Created by: ZhangYi
**Created Date: 2014
**----------------------------------------------------------------------------------
**Modified by: ZhangYi
**Modified Date: 2014/10/13
**********************************************************************************************/
void no_so_handler(struct AM_Instance *amIns,SequenceNumber nackSn,bool *isPduFound)
{
	struct AmBuffer *amTxedBuffer;	//�ѷ��Ͷ��нڵ�
	//struct AmBuffer *amTxedBf;
	struct AmBuffer *amRetxBf;
	struct AmBuffer * nposBf;
	struct AmBuffer * reposBf;
	CRLC_StatusInd_IoctrlMsg *mioctrl;

	if( !list_empty(&amIns->amTransmittedBuffer.list) )
	{
		list_for_each_entry_safe(amTxedBuffer, nposBf, &amIns->amTransmittedBuffer.list,list)
		{
			if( nackSn == amTxedBuffer->SN )
			{
				*isPduFound = true;
				amTxedBuffer->segStart[0] = 0;
				amTxedBuffer->segEnd[0] = amTxedBuffer->pkt->len;

				//�����ش�����retxCount
				if( amTxedBuffer->retxCount == -1 )   //��ʾ�״��ش�
				{
					amTxedBuffer->retxCount = 0;
				}
				else
				{
					amTxedBuffer->retxCount++;
				}
				//����ﵽ����ش������򱨸���߲�
				if( amTxedBuffer->retxCount == amIns->maxRetxThreshold )
				{
					mioctrl = (CRLC_StatusInd_IoctrlMsg*)fsm_mem_alloc(sizeof(CRLC_StatusInd_IoctrlMsg));
					mioctrl->eventCode = 0;
					mioctrl->rbIdentity = amIns->rbId;
					//fsm_do_ioctrl(STRM_TO_RRC, CRLC_STATUS_IND, (void*)mioctrl, sizeof(CRLC_StatusInd_IoctrlMsg));
					fsm_mem_free(mioctrl);
					mioctrl = NULL;
					//���ѷ��Ͷ���ɾ��PDU
					amIns->amTransmittedBufferSize -= amTxedBuffer->pkt->len;
					amIns->amTransmittedBufferNum--;
					fsm_pkt_destroy( amTxedBuffer->pkt );
					amTxedBuffer->pkt = NULL;
					list_del(&amTxedBuffer->list);
					fsm_mem_free(amTxedBuffer);
					amTxedBuffer = NULL;
					//���ش�����ɾ��PDU
					if( !list_empty(&amIns->amRetxBuffer.list) )
					{
						list_for_each_entry_safe(amRetxBf, reposBf, &amIns->amRetxBuffer.list,list)
						{
							if( amRetxBf->SN == nackSn)
							{
								amIns->amRetxBufferSize -= amRetxBf->pkt->len;
								amIns->amRetxBufferNum--;
								fsm_pkt_destroy( amRetxBf->pkt );
								amRetxBf->pkt = NULL;
								list_del(&amRetxBf->list);
								fsm_mem_free(amRetxBf);
								amRetxBf = NULL;
								break;
							}
						}
					}
				}
				else
				{							
					//rlc_retx(amIns,amTxedBuffer);
					fsm_printf("[RLC][no_so_handler] run to rlc_retx()\n");
				}
				break;
			}
		}
	}
	FOUT;
}
/************************************************************************
**Function name: rlc_ctrl_pkt_recv()
**Descriptions: Receive ctrl PDU
**Input: struct AM_Instance *amIns, FSM_PKT * pkt
**Output: handle the corresponding PDUs according to the ackSn and nackSn fields in the ctrl PDU
**Returns:
**Created by: ZhangYi
**Created Date: 2014
**---------------------------------------------------------------------
**Modified by: ZhangYi
**Modified Date: 2014
************************************************************************/
void rlc_ctrl_pkt_recv(struct AM_Instance *amIns, FSM_PKT * pkt)
{
	u16 amHdr;
	u32 pduLen;
	SequenceNumber ackSn;
	SequenceNumber nackSn;
	int i;
	u16 E1 = 0;
	u16 E2 = 0;
	long SOstart = 0;
	long SOend = 0;
	u16 ptr = 16;//��¼��ǰͷ���л�û��ȡ��������λ��
	bool isPduFound = false;
	
	FIN(rlc_ctrl_pkt_recv());
	fsm_printf("[RLC][rlc_ctrl_pkt_recv] entering rlc_ctrl_pkt_recv() function\n");
	//��pkt->dataȡ2�ֽ�����
	pduLen = pkt->len;
	fsm_mem_cpy(&amHdr,pkt->data,2);
	fsm_skb_pull(pkt,2);
	pduLen -= 2;
		
	ptr -= 4;  //��ȥD/C���CPT��
	ackSn = (amHdr&0x3ff0)>>4;  //ȡack_sn��
	ptr -= 10;
	ack_handler(amIns,ackSn);   //20141013

	E1 = (amHdr&0x4000)>>14;
	ptr -= 1;
	while( E1 == 1 )  //��ʾ��nack
	{
		if( ptr == 0 ) //���ʣ��λ��Ϊ0���ٴ�pkt���ݲ���ȡ2�ֽ�����
		{
			getNewData(&ptr,&pduLen,pkt,&amHdr);  //ȡ�����ݸ���amHdr
		}
		nackSn = getNackSn(&pduLen,&amHdr,pkt,&ptr);  //ȡNackSn
		if( nackSn == amIns->pollSn )
		{
			//ֹͣ����λ�ش���ʱ��
			if(amIns->pollRetxTimer)
			{
				fsm_schedule_cancel(amIns->pollRetxTimer);
				amIns->pollRetxTimer = 0;
			}
		}
		if( ptr == 0 ) //���ʣ��λ��Ϊ0���ٴ�pkt���ݲ���ȡ2�ֽ�����
		{
			getNewData(&ptr,&pduLen,pkt,&amHdr);  //ȡ�����ݸ���amHdr
		}
		E1 = (amHdr&(0x8000>>(ptr-1)))>>(16-ptr);
		ptr--;
		if( ptr == 0 ) //���ʣ��λ��Ϊ0���ٴ�pkt���ݲ���ȡ2�ֽ�����
		{
			getNewData(&ptr,&pduLen,pkt,&amHdr);  //ȡ�����ݸ���amHdr
		}
		E2 = (amHdr&(0x8000>>(ptr-1)))>>(16-ptr);
		ptr--;
		if( E2 == 1 )  //��ʾ��SOstart��SOend����AMD PDU�ֶ�
		{
			SOstart = getSO(&ptr,&amHdr,&pduLen,pkt);  //ȡSOstart
			SOend = getSO(&ptr,&amHdr,&pduLen,pkt);  //ȡSOend
			so_handler(amIns,nackSn,&isPduFound,SOstart,SOend);
		}
		else  //��ʾû��SOstart��SOend����AMD PDU
		{
			no_so_handler(amIns,nackSn,&isPduFound);
		}
		if( !isPduFound )
		{
			fsm_printf("[RLC][rlc_ctrl_pkt_recv] The corresponding PDU of the nackSn is not found\n");
		}
	}
	FOUT;
}
