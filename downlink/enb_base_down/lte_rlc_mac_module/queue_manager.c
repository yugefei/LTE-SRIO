/*******************************************************************
author:HuangQiong   Date:20140521 v0
description: ���ļ��ĺ�����Ҫ����ʵ���е��ȶ��еĹ���
              �����е�ʵ��ʹ������ķ�ʽ��linux�е�list��
note: ʹ�������ַ�ʽʵ��
      ��һ�ַ�ʽ�Ǳ�д��������ʽ����ֻ�����һ�ֶ��С�
	  �ڶ��ַ�ʽ��ʹ�ú궨��ķ�ʽ�����������ڲ�ͬ�Ķ��У�
	   ����Ҫ�����Ԫ�صĽṹ����һ���ԡ�
*******************************************************************/
#include <linux/if_ether.h>
#include <linux/list.h>
#include <linux/kernel.h>

#include "queue_manager.h"


/******************��һ�ַ�ʽ**����************************/

/****************************************************************************
funcName: ��ʼ�� ֱ��ʹ��list.h��ʹ�õģ���Ҫ����һ����ͷ������struct list_head *listhead
function: INIT_LIST_HEAD(struct list_head *list)
parameter: list_head�ṹ��ָ�룬������ı�ͷ
return: non
*****************************************************************************/

/****************************************************************************
funcName: insert_ULschedQue(struct list_head *listhead,struct S_UEinfo * newue)
function: ��һ���û�����Ҫ�������е��ȵģ��Ӷ���β�����뵽������
parameter: listptr��ʾָ��ö��б�ͷ��newue���Ǹ��û�����Ӧ��Ϣ
return: 0��ʾ�ɹ���ӣ������ʾ����
*****************************************************************************/
int insert_ULschedQue(struct list_head *listhead,struct S_UEinfo * newue)
{   
	int flag =0 ;
	P_ULsched_QueueEntry tmp = (P_ULsched_QueueEntry)fsm_mem_alloc(sizeof(S_ULsched_QueueEntry));
	if(tmp == NULL)
	{   
		fsm_printf("alloc memory error \n");
		flag = 1; //�ڴ������� 
	}
	tmp->info = *newue; //����UE����Ϣ
	list_add_tail(&(tmp->list_h),listhead);
	return flag;
}

/*******************************************************************
funcName: find_ULschedQue(struct list_head *listhead,u16 ue_rnti)
function: �ڶ����в���ĳ��UE������ҵ��򷵻�һ��ָ��ָ���UE�����û���ҵ��򷵻�NULL
parameter: listptr��ʾָ��ö��е�ָ�룬ue_rnti��UE��RNTI,������C_RNTI,Ҳ������T_C_RNTI
return: ��ȡ�����û�����Ϣ
*******************************************************************/
struct S_UEinfo* find_ULschedQue(struct list_head *listhead,u16 ue_rnti)
{
	P_ULsched_QueueEntry tmp = NULL;
	struct S_UEinfo* get_ue_info = NULL;
	struct list_head *pos = NULL;
	struct list_head *p = NULL;
	int flag = 0 ;
	list_for_each_safe(pos,p,listhead)//���� //���ضԿն��е��ж� ����Ҫ�����Ӳ������   
	{        
		tmp = list_entry(pos,S_ULsched_QueueEntry,list_h);//ȡÿ��Ԫ��	
		if(tmp->info.rnti == ue_rnti) 
		{
			get_ue_info	= &(tmp->info);	
			break;
		}
	}
	return get_ue_info;
}


/*******************************************************************
funcName: take_first_ULschedQue(struct list_head *listhead)
function: �Ӷ���ͷ��ȡ��һ���û��������û��Ӹö���ɾ����
parameter: listptr��ʾָ��ö��е�ָ��
return: ��ȡ�����û�����Ϣ
*******************************************************************/
struct S_UEinfo take_first_ULschedQue(struct list_head *listhead)
{
	P_ULsched_QueueEntry tmp = NULL;
	struct S_UEinfo tmp_info = {0};//��ʼ��Ϊ0
	if(list_empty_careful(listhead))//������Ϊ��
	{
		fsm_printf("The queue is empty,no element can be taken. \n");
		return tmp_info;//����Ĭ��ֵΪ0 
	}
	tmp = list_first_entry(listhead,S_ULsched_QueueEntry,list_h);//�����������ǵڶ������������������ݽṹ���е�list_head�����ı����� ��һ�����Ǳ�ͷ
	tmp_info = tmp->info;
	list_del_init(&tmp->list_h);//�ӱ���ɾ���ýڵ� 
	return tmp_info;
}

/*******************************************************************
funcName: clean_ULschedQue(struct list_head *listhead)
function: ��ն��У��ͷ��ڴ�
parameter: ��ͷ
return: 0��ʾ�ɹ���գ������ʾ����
*******************************************************************/
int clean_ULschedQue(struct list_head *listhead)
{
	P_ULsched_QueueEntry tmp = NULL;
	struct list_head *pos = NULL;
	struct list_head *p = NULL;
	int flag = 0 ;
	list_for_each_safe(pos,p,listhead)//���� //���ضԿն��е��ж� ����Ҫ�����Ӳ������   
	{        
		tmp = list_entry(pos,S_ULsched_QueueEntry,list_h);//ȡÿ��Ԫ��		
		list_del_init(&tmp->list_h);		
		if(tmp != NULL)		   
			fsm_mem_free(tmp); //��Ϊ��insertʱ������malloc�����ڴ棬���Ըô���Ҫ�ͷ��ڴ�		
		else 		
		{   
			fsm_printf("free memory error \n");
			flag = 1; //�����޸ı�־ //�˴��Ĵ���������
		}
		fsm_printf("cleaning \n");//testing code 
	}
	if(list_empty_careful(listhead) != 1)//�����в�Ϊ�գ����ǳ�����
		flag = 2;
	return flag;
}

/*******************************************************************
funcName: print_ULschedQue(struct list_head *listhead)
function: �������в���ӡ��������Ϣ
parameter: ��ͷ
return: 0��ʾ�ɹ���ӡ�������ʾ����
*******************************************************************/
int print_ULschedQue(struct list_head *listhead)
{
	P_ULsched_QueueEntry tmp = NULL;
	struct list_head *pos = NULL;
	struct list_head *p = NULL;
	list_for_each_safe(pos,p,listhead)//����    
	{        
		tmp = list_entry(pos,struct S_ULsched_QueueEntry,list_h);		
		fsm_printf("RNTI:%d,CQI:%d\n",tmp->info.rnti,tmp->info.cqi);    
	}
	fsm_printf("--------------------\n");
	return 0;
}
/***********
*���漸�������ǹ���RA_Sched_Queue�ģ�ֻ�Ǳ��������Ͳ�ͬ
************/
int insert_RAschedQue(struct list_head *listhead,struct S_RAinfo * newue)
{   
	int flag =0 ;
	P_RAsched_QueueEntry tmp = (P_RAsched_QueueEntry)fsm_mem_alloc(sizeof(S_RAsched_QueueEntry));
	if(tmp == NULL)
	{   
		fsm_printf("alloc memory error \n");
		flag = 1; //�ڴ������� 
	}
	tmp->info = *newue; //����UE����Ϣ
	list_add_tail(&(tmp->list_h),listhead);
	return flag;
}

struct S_RAinfo* find_RAschedQue(struct list_head *listhead,u16 ue_rnti)
{
	P_RAsched_QueueEntry tmp = NULL;
	struct S_RAinfo* get_ue_info = NULL;
	struct list_head *pos = NULL;
	struct list_head *p = NULL;
	int flag = 0 ;
	list_for_each_safe(pos,p,listhead)//���� //���ضԿն��е��ж� ����Ҫ�����Ӳ������   
	{        
		tmp = list_entry(pos,S_RAsched_QueueEntry,list_h);//ȡÿ��Ԫ��	
		if(tmp->info.ra_rnti == ue_rnti) 
		{
			get_ue_info	= &(tmp->info);	
			break;
		}
	}
	return get_ue_info;
}

struct S_RAinfo take_first_RAschedQue(struct list_head *listhead)
{
	P_RAsched_QueueEntry tmp = NULL;
	struct S_RAinfo tmp_info = {0};//��ʼ��Ϊ0
	if(list_empty_careful(listhead))//������Ϊ��
	{
		fsm_printf("The queue is empty,no element can be taken. \n");
		return tmp_info;//����Ĭ��ֵΪ0 
	}
	tmp = list_first_entry(listhead,S_RAsched_QueueEntry,list_h);//�����������ǵڶ������������������ݽṹ���е�list_head�����ı����� ��һ�����Ǳ�ͷ
	tmp_info = tmp->info;
	list_del_init(&tmp->list_h);//�ӱ���ɾ���ýڵ� 
	return tmp_info;
}

int clean_RAschedQue(struct list_head *listhead)
{
	P_RAsched_QueueEntry tmp = NULL;
	struct list_head *pos = NULL;
	struct list_head *p = NULL;
	int flag = 0 ;
	list_for_each_safe(pos,p,listhead)//���� //���ضԿն��е��ж� ����Ҫ�����Ӳ������   
	{        
		tmp = list_entry(pos,S_RAsched_QueueEntry,list_h);//ȡÿ��Ԫ��		
		list_del_init(&tmp->list_h);		
		if(tmp != NULL)		   
			fsm_mem_free(tmp); //��Ϊ��insertʱ������malloc�����ڴ棬���Ըô���Ҫ�ͷ��ڴ�		
		else 		
		{   
			fsm_printf("free memory error \n");
			flag = 1; //�����޸ı�־ //�˴��Ĵ���������
		}
		fsm_printf("cleaning \n");//testing code 
	}
	if(list_empty_careful(listhead) != 1)//�����в�Ϊ�գ����ǳ�����
		flag = 2;
	return flag;
}

int print_RAschedQue(struct list_head *listhead)
{
	P_RAsched_QueueEntry tmp = NULL;
	struct list_head *pos = NULL;
	struct list_head *p = NULL;
	list_for_each_safe(pos,p,listhead)//����    
	{        
		tmp = list_entry(pos,struct S_RAsched_QueueEntry,list_h);		
		fsm_printf("RA-RNTI:%d\n",tmp->info.ra_rnti);    
	}
	fsm_printf("--------------------\n");
	return 0;
}

/***************�ڶ��ַ�ʽ***�궨��********************************/
/*****************************************************************
description: ������Բ�ͬ���У�����"��β������Ԫ��","��ͷ��ȡ�ߵ�һ��Ԫ��"��
				"��ն���"��"��ӡ���������е�Ԫ��"
note: ʹ�øú궨���ǰ���ǣ����������ݽṹ��ʽһ����
	  ������ʾ���������info��lish_h��������Ա����������������
	  ���⣬�޷�����ִ�н���ı�־
typedef struct myqueue
{ 
	struct datatype info ; 
	struct list_head lish_h; 
}myqueue; 

******************************************************************/


#define insert_queue(listhead,type,info_ptr) {	type* tmp = (type*)malloc(sizeof(type));\
	tmp->info = *info_ptr;\
	list_add_tail(&(tmp->list_h),listhead);}

/*********************************************************************************
funcName: take_first_entry(listhead,type,info_ptr)
function: �Ӷ���ͷ��ȡ��һ���û��������û��Ӹö���ɾ����
parameter: listhead�Ƕ���ͷ��type�Ƕ���Ԫ�ص��������ͣ�info_ptr��ָ���Ԫ�أ����ݽṹ�������ݳ�Ա����ָ��
return: ��ȡ����Ԫ�ص����ݲ��� 
note:����Ҫд�ֺ�
���� typedef struct myqueue
    { struct datatype info ; 
	  struct list_head lish_h;} myqueue; 
 �÷�
     struct datatype myinfo;
     take_first_entry(listhead,myqueue,&myinfo)

**********************************************************************************/
#define take_first_entry(listhead,type,info_ptr) {  type* tmp = NULL;\
	tmp = list_first_entry(listhead,type,list_h);\
	list_del_init(&tmp->list_h); \
	*info_ptr=tmp->info;} 


#define clean_queue(listhead,type) { type* tmp = NULL;\
	struct list_head *pos = NULL;\
	struct list_head *p = NULL;\
	list_for_each_safe(pos,p,listhead) { \		tmp = list_entry(pos,type,list_h);\		list_del_init(&tmp->list_h);\		if(tmp != NULL)\		   free(tmp);} }


#define print_queue(listhead,type) {  type* tmp = NULL;\
	struct list_head *pos = NULL;\
	struct list_head *p = NULL;\
	list_for_each_safe(pos,p,listhead){ tmp = list_entry(pos,struct S_ULsched_QueueEntry,list_h); \		fsm_printf("RNTI:%d,CQI:%d\n",tmp->info.rnti,tmp->info.cqi);} fsm_printf("--------------------\n");}

/*******************************************************************/

