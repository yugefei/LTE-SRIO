#include "../fsm/fsmdec.h"

#include <linux/if_ether.h>
#include <linux/list.h>
#include <linux/kernel.h>

#ifndef _QUEUE_MANAGER_H
#define _QUEUE_MANAGER_H

#define UE_RA_MAXNUM 10  //һ��ʱ�̽����UE�������Ŀ
typedef struct S_UEinfo //ÿ��UE��Ӧ�Ļ�����Ϣ�����ڵ����õģ�����RNTI��CQI��
{
    u16    rnti;             //
    //u16    pgtype;           //0,1,2
    u16    sfn;              //ϵͳ֡�ţ�0��1023
    u16    subframeN;        //��֡�ţ�0����9
    u16    crc;
    u16    harqindex;
	u8    harq_result;//20141008
    u16    sr;
    u16    cqi;
    u16    pmi;
    u16    ta;	 
    u16    datasizeof_bsr;
}__attribute__((packed))S_UEinfo;





#define RA_UE_NUMBER_MAX 10
typedef struct S_RAinfo //����UE����eNBʱ���������⵽RNTI��RAPID�ϱ� �������ĸ�ʽ
{
   u16    total_num;//��ǰ��������⵽�����û���
   u16    index;//���û������û����е��±꣬��0��ʼȡֵ
    u16    ra_rnti;             //
   // u16    pgtype;           //0,1,2��0:�½��û� 1:ɾ���û� 2:�����û�������Ϣ
    u16    sfn; //             //ϵͳ֡�ţ�0��1023
    u16    subframeN;//        //��֡�ţ�0����9
    u16    crc;
    u16    harqindex;
	u8 harq_result;
    u16    sr;
    u16    cqi;//
    u16    pmi;
    u16    ta;//
    u8    rapid;//
}__attribute__((packed))S_RAinfo;
/*typedef struct S_RAinfo //����UE����eNBʱ���������⵽RNTI��RAPID�ϱ� �������ĸ�ʽ
{
   u16    total_num;//��ǰ��������⵽�����û���
   u16    index;//���û������û����е��±꣬��0��ʼȡֵ
    u16    ra_rnti;             //
   // u16    pgtype;           //0,1,2��0:�½��û� 1:ɾ���û� 2:�����û�������Ϣ
    u16    sfn; //             //ϵͳ֡�ţ�0��1023
    u16    subframeN;//        //��֡�ţ�0����9
    u16    crc;
    u16    harqindex;
	u8 harq_result;
    u16    sr;
    u16    cqi;//
    u16    pmi;
    u16    ta;//
    u16    rapid;//
}__attribute__((packed))S_RAinfo;*/

typedef struct S_ULsched_QueueEntry //�������Ԫ��
{
	struct S_UEinfo info;
    struct list_head list_h;
}S_ULsched_QueueEntry;
typedef S_ULsched_QueueEntry* P_ULsched_QueueEntry;


typedef struct S_RAsched_QueueEntry
{
	struct S_RAinfo info;
    struct list_head list_h;
}S_RAsched_QueueEntry;
typedef S_RAsched_QueueEntry* P_RAsched_QueueEntry;

//UL���ȶ��еĹ����� ����
int insert_ULschedQue(struct list_head *listhead,struct S_UEinfo * newue);//��β������һ��
struct S_UEinfo* find_ULschedQue(struct list_head *listhead,u16 ue_rnti);//����
struct S_UEinfo take_first_ULschedQue(struct list_head *listhead);//��ͷ��ȡ��һ��
int clean_ULschedQue(struct list_head *listhead);
int print_ULschedQue(struct list_head *listhead);
//RA���ȶ��еĹ����� ����
int insert_RAschedQue(struct list_head *listhead,struct S_RAinfo * newue);
struct S_RAinfo* find_RAschedQue(struct list_head *listhead,u16 ue_rnti);
struct S_RAinfo take_first_RAschedQue(struct list_head *listhead);
int clean_RAschedQue(struct list_head *listhead);
int print_RAschedQue(struct list_head *listhead);


#endif


