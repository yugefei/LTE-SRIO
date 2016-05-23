#include "../fsm/fsmdec.h"

#include <stdbool.h>
#include <linux/list.h>
#include <linux/kernel.h>
#include <stddef.h>

#ifndef _MACSCHEDULER_H
#define _MACSCHEDULER_H
#define LCG 4
typedef struct Mac_Buffer_Status_BSR_Info  //hl ���ģ�UE,������������BSR ������װ��
{
	unsigned short m_rnti;
	unsigned int m_lcgnum;//��־�ж��ٸ�LCG������Ҫ����
	unsigned int m_TotalLcgData; //�����߼��ŵ�Ҫ������ܴ�С
	unsigned int m_bufferStatus[LCG];
}__attribute__((packed))MacBufferStatus_BSR_Info;

struct Ul_SpecificParameters{
	int priority;        //INTEGER (1..16)
	enum PrioritisedBitRate{
		kBps0=0, kBps8=8, kBps16=16, kBps32=32, kBps64=64, kBps128=128,
		kBps256=256, infinity=-1//..........spare1~8δ��ʾ
	}prioritisedBitRate;
	enum BucketSizeDuration{
		bucketSizeDuration_ms50=50, bucketSizeDuration_ms100=100, bucketSizeDuration_ms150=150, bucketSizeDuration_ms300=300, 
		bucketSizeDuration_ms500=500, bucketSizeDuration_ms1000=1000//..........spare1~2δ��ʾ
	}bucketSizeDuration;
	int logicalChannelGroup;	//INTEGER (0..3) 
};

typedef struct LogicalChannelConfig//lhl ���ģ�RRC������߼��ŵ��Ľṹ
{
	bool haveUl_SpecificParameters;
	struct Ul_SpecificParameters ul_SpecificParameters;
}LogicalChannelConfig;


typedef struct MAC_LogicalChannelConfig_IoctrlMsg{
	u16 rnti;
	int logicalChannelIdentity;
	struct LogicalChannelConfig logicalChannelConfig;
}MAC_LogicalChannelConfig_IoctrlMsg;


/*****************lhlע����ɣ�������lhl�޸�********************/
#define TTI 1	//��ʾ1ms,�ں���FlushBj()��ʹ��

typedef struct RLC_Buffer_Request//lhl ����
{
	//u16 frame;   //eNB����ӳ�Ա
	//u16 subframe;
	unsigned short rnti;
	unsigned char lcid;
	unsigned int txQueueSize;
	unsigned short txQueueHeader;
	unsigned int retxQueueSize;
	unsigned short retxQueueHeader;
	unsigned short statusPduSize;
unsigned short statusPduHeader;
}__attribute__((packed))RLC_Request,RLC_Report;


typedef struct RLCBufferRequestParameters //lhl ���ģ�RLC��buffer״̬��������
{
    unsigned short rnti;
	unsigned char lcid;
	unsigned int txQueueSize;
	unsigned short txQueueHeader;
	unsigned int retxQueueSize;
	unsigned short retxQueueHeader;
	unsigned short statusPduSize;
	unsigned short statusPduHeader;
    struct list_head list;
}__attribute__((packed))RlcBufferRequest;


typedef struct Mac_Buffer_Status  //MAC�㱣����µ�RLC״̬����
{
	int lcid;
	RLC_Request *RlcRequestparams;
	struct list_head list;
}__attribute__((packed))MacBufferStatus;


typedef  struct Logical_Channel_Config_Info  //lhl ���ģ��߼��ŵ����Խṹ
{
	int lcid;
	unsigned short rnti;
	int priority;
    int prioritizedBitRateKbps;
	int bucketSizeDurationMs;
	int logicalChannelGroup;
	struct list_head list;
}__attribute__((packed))LogicalChannelConfigInfo;



typedef  struct  Logical_Channel_Bj  //lhl ���ģ��߼��ŵ���BJ�ṹ
{
	int lcid;
	unsigned short rnti;
    int lcbj;	//�߼��ŵ���BJֵ
	struct list_head list;
}__attribute__((packed))LogicalChannelBj;



#define MAX_BJ 256000/*20140512modified by lhl,256*1000������pbr*bsdֵ*/




/********���ã���ʼ��ʱ����****/
void Init_Enbmac_Scheduler(void);//UE ��������ʼ��
void * DoRefreshRLCBuffserRequest (RlcBufferRequest* params, struct list_head *enb_buffer_rlc);//����RLC����
RLC_Request* Rlc_MacRequest_copy(RlcBufferRequest *temp);//���ƽڵ�rlcBufferRequest
LogicalChannelConfigInfo* LogicalChannel_ConfigInfo_copy(MAC_LogicalChannelConfig_IoctrlMsg *temp);//�����߼��ŵ����Խڵ�
//LogicalChannelConfigInfo* LogicalChannel_ConfigInfo_copy(LogicalChannelConfigInfo *temp);//�����߼��ŵ����Խڵ�
RlcBufferRequest* Mac_RlcRequest_copy(RLC_Request *temp);//����RlcBufferRequest�ڵ�
RLC_Request* Mac_MacRequest_copy(RLC_Request *temp);//����RlcBufferRequest�ڵ�

/******************���ã�ÿ��TTL �ж�IOCTL����ʱ����****************/
void FlushBj(struct list_head *enb_logicalChannel_bj, struct list_head *enb_buffer_rlc);//ÿ��TTI�����߼��ŵ���BJ

LogicalChannelConfigInfo* LogicalChannel_ConfigInfo_Rank_Priority(struct list_head * enb_logicalChannel_config);//�����߼��ŵ����ȼ����߼��ŵ�����
MacBufferStatus* PrioritySort( struct list_head * enb_logicalChannel_config,struct list_head *enb_buffer_rlc);//�����߼��ŵ����ȼ�˳�򣬶�MacBufferStatus�������ȼ�����



RLC_Request * DoResourceAllocation(int tb_size,struct list_head *enb_buffer_rlc, struct list_head * enb_logicalChannel_config, struct list_head *enb_logicalChannel_bj,int index,int *rlc_report_num);//��Դ����
/********���ã���RRC IOCTL����ʱ���ã����߶��߼��ŵ�Ĭ������ʱ����****/
void Init_LogicalChannel_ConfigInfo(MAC_LogicalChannelConfig_IoctrlMsg *lc_info);//�����߼��ŵ����Խṹ��BJ�ṹ,RRC�߼��ŵ�����IOCTL����ʱ����

/******����msgΪGetTBsize_Allocation���ص���Դ��С�����:*num����Ҫ���͵�IOCTL��buffer���ȣ�void *��RLC �����ͷָ��**********/
/********���ã���ResourceAllocation_Algorithm���Ѿ���װ���ã��������������������ģ����ʾ����****************/
RLC_Request * ResourceAllocation_Algorithm(int msg,struct list_head *enb_buffer_rlc,struct list_head * enb_logicalChannel_config, struct list_head *enb_logicalChannel_bj,int *num,int index);//UE����Դ�����㷨������Ͱ,RlcBufferRequest MACReportToRlc
void Empty_MACBuffer_Rlc(struct list_head *enb_buffer_rlc);//���MAC���RLC����Buffer
void Free_Enbmac_Scheduler_Resource(void);//�ͷ�UE MAC SCHEDULER��Դ
void Delete_LogicalChannel_ConfigInfo(int unsigned short rnti,unsigned char lcid_delete);
/*****RLC����IOCL�����ǵ��ã�����ΪRLC���������ͷָ�룬�Լ�RLC��������ĳ��ȣ����Ϊ������ʽ*************/
RlcBufferRequest * RlcRequest_arraytolist(RLC_Request *rlc_request_array,int num,int uesernum);
void Empty_Rlcrequestnum(void);
/*******����RlcBufferRequestΪRLC report���������*num��Ҫ���͵�IOCTL��buffer���ȷ���RLC �����ͷָ��***************/
RLC_Request * RlcRequest_listtoarray( RlcBufferRequest *rlc_request,int reqnum ,int *num);
struct  list_head * Get_LogicalChannelInfo_From_Enbbuffer(struct list_head *enb_buffer_rlc);
struct  list_head * Get_LogicalChannelBj_From_Enbbuffer(struct list_head *enb_buffer_rlc);
unsigned short Getrnti_From_Enbbuffer(struct list_head *enb_buffer_rlc);//��ȡRNTI��modified by lhl 20140715 
 struct list_head * Get_LogicalChannelInfo_From_Rnti(unsigned short m_rnti);//��RNTI �� ȡ�߼��ŵ����ԣ�modified by lhl 20140715 
struct list_head * Get_LogicalChannelBj_From_Rnti(unsigned short m_rnti);//��RNTI �� ȡ�߼���BJ,modified by lhl 20140715 
 struct list_head * Get_Enbbuffer_From_Rnti(unsigned short m_rnti);
void Empty_LogicalChannelInfo(struct list_head *m_lc_info);//�ͷ��߼��ŵ��ڴ棬lhl 20140715
void Empty_LogicalChannelBj(struct list_head *m_lcbj_info);//�ͷ��߼�BJ �ڴ棬��ӦRRC�ͷ�����lhl 20140715

void ResourceAllocation_foreach_logicalchannel(RlcBufferRequest *mac_rlc_report,MacBufferStatus *temp_mac_buffer, LogicalChannelBj *temp_logicalchannel_bj,int statuslength,int retxlength,int txlength,int *res_length);
void ResourceAllocation_logicalchannel_firststatusbuffer(RlcBufferRequest *mac_rlc_report,MacBufferStatus *temp_mac_buffer, LogicalChannelBj *temp_logicalchannel_bj,int statuslength,int retxlength,int txlength,int *res_length);
void ResourceAllocation_logicalchannel_firstretxbuffer(RlcBufferRequest *mac_rlc_report,MacBufferStatus *temp_mac_buffer, LogicalChannelBj *temp_logicalchannel_bj,int retxlength,int txlength,int *res_length);
void leftresource_lessthan_retxbuffer_eachlogicalchannel(RlcBufferRequest *mac_rlc_report,RlcBufferRequest *temp_rlc_report,MacBufferStatus *temp_mac_buffer, LogicalChannelBj *temp_logicalchannel_bj,int retxlength,int txlength,int *res_length);
void leftresource_morethan_retxbuffer_eachlogicalchannel(RlcBufferRequest *mac_rlc_report,RlcBufferRequest *temp_rlc_report,MacBufferStatus *temp_mac_buffer, LogicalChannelBj *temp_logicalchannel_bj,int retxlength,int txlength,int *res_length);
#endif

