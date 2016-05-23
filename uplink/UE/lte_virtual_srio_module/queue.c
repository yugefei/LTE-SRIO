#include "queue.h"

InitQueue(LinkQueue* q)
{
	/*自旋锁初始化*/
	spin_lock_init(&q->my_lock);
	
	/*初始化一个空队列*/
	q->front = q->rear = (QueuePtr)kmalloc(sizeof(QNode), GFP_ATOMIC);
	 /*创建一个头结点，队头队尾指针指向该结点*/
	if(!q->front) 
			return;		    /*创建头结点失败*/
	q->front->next = NULL;		       /*头结点指针域置NULL*/
	q->QueueSize = 0;
	q->NextData = 0;
}


/*在队尾插入元素e:Version2*/
int Push(LinkQueue* q,ElemType e)
{
	if(q->QueueSize >= MAXSIZE)
	{
			return 0;
			printk("MAXSIZE...\n");
	}
	QueuePtr p;
	p = (QueuePtr)kmalloc(sizeof(QNode),GFP_ATOMIC);		/*创建一个队列元素结点*/
	if(!q->front) 
				return;						/*创建头结点失败*/
	p->data = e;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;
	q->QueueSize++;
	if(q->QueueSize < 50)
	{
		++q->NextData;
		if(q->NextData > 49)
			q->NextData=0;	
	}
	else
	{
		q->QueueSize = MAXSIZE;
		q->NextData = 0;
	}
	//q->NextData = q->QueueSize<100?q->QueueSize:q->QueueSize%MAXSIZE;
	return 1;
}


/*从队头弹出元素e:Version2*/
int Pop(LinkQueue* q,ElemType* e)
{
	/*如果队列q不为空，删除q的队头元素，用e返回其值*/
	QueuePtr p;
	if(q->front == q->rear) 
			return 0;			/*队列为空，返回*/
	p = q->front->next;
	*e = p->data;
	q->front->next = p->next;
	q->QueueSize--;
	if(q->rear == p) 
	{ 
		q->QueueSize = 0;
		q->rear = q->front;  /*如果队头就是队尾，则修改队尾指针*/ 	
	}
	return 1;
}

int IsQueueEmpty(LinkQueue *q)
{
	return (q->QueueSize==0)?1:0;
}

DestroyQueue(LinkQueue* q)
{
	/*自旋锁加锁*/
	spin_lock(&q->my_lock);
	while(q->front)
	{
	    q->rear = q->front->next;		/*q->rear 指向q->front的后继结点*/
	    kfree(q->front);					/*释放掉q->front*/
	    q->front = q->rear;				/*q->front后移*/
	}
	q->QueueSize = 0;
	/*自旋锁解锁*/
	spin_lock(&q->my_lock);
}
