#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <linux/list.h>
#include <linux/spinlock.h>
#include<linux/slab.h>

typedef unsigned int ElemType;   //���нڵ�Ԫ�����ͣ���ŵ�ַƫ����
#define  MAXSIZE  100           //����ElemType���ֵ&���е���󳤶�:��󻺴�100��֡
#define  QUEUE_MAX_NUM 10
#define  QUEUE_OFFSET     105

typedef struct QNode{			 //�ڵ�����
	ElemType data;				 //������
	struct QNode *next;          //ָ����
}QNode , *QueuePtr;


typedef struct{				     //��������
	QueuePtr front;			     //��ͷָ��
	QueuePtr rear;			     //��βָ��
	int QueueSize;			     //���г��ȣ�0-MAXSIZE
	int NextData;                 //��һ�����õ�λ�ã����������Push����
	spinlock_t my_lock;	     //��ֹ�����Ķ��з���
}LinkQueue;


InitQueue(LinkQueue *q);
int Push(LinkQueue *q,ElemType e);
int Pop(LinkQueue *q,ElemType* e);
int IsQueueEmpty(LinkQueue *q);
int IsQueueFull(LinkQueue *q);
DestroyQueue(LinkQueue *q);

#endif //_QUEUE_H_
