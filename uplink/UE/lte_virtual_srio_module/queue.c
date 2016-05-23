#include "queue.h"

InitQueue(LinkQueue* q)
{
	/*��������ʼ��*/
	spin_lock_init(&q->my_lock);
	
	/*��ʼ��һ���ն���*/
	q->front = q->rear = (QueuePtr)kmalloc(sizeof(QNode), GFP_ATOMIC);
	 /*����һ��ͷ��㣬��ͷ��βָ��ָ��ý��*/
	if(!q->front) 
			return;		    /*����ͷ���ʧ��*/
	q->front->next = NULL;		       /*ͷ���ָ������NULL*/
	q->QueueSize = 0;
	q->NextData = 0;
}


/*�ڶ�β����Ԫ��e:Version2*/
int Push(LinkQueue* q,ElemType e)
{
	if(q->QueueSize >= MAXSIZE)
	{
			return 0;
			printk("MAXSIZE...\n");
	}
	QueuePtr p;
	p = (QueuePtr)kmalloc(sizeof(QNode),GFP_ATOMIC);		/*����һ������Ԫ�ؽ��*/
	if(!q->front) 
				return;						/*����ͷ���ʧ��*/
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


/*�Ӷ�ͷ����Ԫ��e:Version2*/
int Pop(LinkQueue* q,ElemType* e)
{
	/*�������q��Ϊ�գ�ɾ��q�Ķ�ͷԪ�أ���e������ֵ*/
	QueuePtr p;
	if(q->front == q->rear) 
			return 0;			/*����Ϊ�գ�����*/
	p = q->front->next;
	*e = p->data;
	q->front->next = p->next;
	q->QueueSize--;
	if(q->rear == p) 
	{ 
		q->QueueSize = 0;
		q->rear = q->front;  /*�����ͷ���Ƕ�β�����޸Ķ�βָ��*/ 	
	}
	return 1;
}

int IsQueueEmpty(LinkQueue *q)
{
	return (q->QueueSize==0)?1:0;
}

DestroyQueue(LinkQueue* q)
{
	/*����������*/
	spin_lock(&q->my_lock);
	while(q->front)
	{
	    q->rear = q->front->next;		/*q->rear ָ��q->front�ĺ�̽��*/
	    kfree(q->front);					/*�ͷŵ�q->front*/
	    q->front = q->rear;				/*q->front����*/
	}
	q->QueueSize = 0;
	/*����������*/
	spin_lock(&q->my_lock);
}
