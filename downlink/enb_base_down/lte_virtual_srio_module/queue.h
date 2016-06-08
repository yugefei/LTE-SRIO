#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <linux/list.h>
#include <linux/spinlock.h>
#include<linux/slab.h>

typedef unsigned int ElemType;   //队列节点元素类型：存放地址偏移量
#define  MAXSIZE  100           //队列ElemType最大值&队列的最大长度:最大缓存100子帧
#define  QUEUE_MAX_NUM 10
#define  QUEUE_OFFSET     105

typedef struct QNode{			 //节点类型
	ElemType data;				 //数据域
	struct QNode *next;          //指针域
}QNode , *QueuePtr;


typedef struct{				     //队列类型
	QueuePtr front;			     //队头指针
	QueuePtr rear;			     //队尾指针
	int QueueSize;			     //队列长度：0-MAXSIZE
	int NextData;                 //下一个可用的位置：用于适配层Push操作
	spinlock_t my_lock;	     //防止并发的队列访问
}LinkQueue;


InitQueue(LinkQueue *q);
int Push(LinkQueue *q,ElemType e);
int Pop(LinkQueue *q,ElemType* e);
int IsQueueEmpty(LinkQueue *q);
int IsQueueFull(LinkQueue *q);
DestroyQueue(LinkQueue *q);

#endif //_QUEUE_H_
