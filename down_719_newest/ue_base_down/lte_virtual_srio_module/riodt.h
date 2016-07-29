#ifndef RIOCDEV_H
#define RIOCDEV_H

#include "vt861.h"

#define DEV_CMD_MSGRX               0
#define DEV_CMD_MSGTX               1
#define DEV_CMD_NREAD               2
#define DEV_CMD_NWRITE              3
#define DEV_CMD_NREAD_RET           4
#define DEV_CMD_NWRITE_RET          5
#define DEV_CMD_DBELLRX             6
#define DEV_CMD_DBELLTX             7
#define DEV_CMD_ATMU_CONFIG         8 
#define DEV_CMD_MAINTREAD           9
#define DEV_CMD_MAINTWRITE          10
#define DEV_CMD_DMA_READ            11
#define DEV_CMD_DMA_WRITE           12
#define DEV_CMD_NREAD_EX            13
#define DEV_CMD_NWRITE_EX           14
#define DEV_CMD_DISCOVER            15
#define DEV_CMD_GET_DISCOVER_INFO   16
#define DEV_CMD_GET_DISCOVER_STAT   17

#define DEV_CMD_TIMER1_SEND_START   18
#define DEV_CMD_TIMER1_SEND_STOP    19

#define DEV_CMD_CLEAR_LOG			20
#define DEV_CMD_SHOW_LOG			21

#define DEV_CMD_SHOW_DBCHECK     22

#define DEV_CMD_TIMER2_SEND_START   23
#define DEV_CMD_TIMER2_SEND_STOP    24

struct rio_msg_para
{
    unsigned char port;
    unsigned int destid;
    unsigned int mbox;
    unsigned int data;
    unsigned int len;
};

struct rio_dma_para
{
    unsigned char port;
    unsigned int destid;
    unsigned long long local;
    unsigned long long dest;
    unsigned int len;
	unsigned int seconds;
	unsigned int nseconds;
	unsigned long long sendtimes;//*flag_address;
    unsigned int arg;
};

//use the struct check the new data flag.Modified date:20150320
struct new_check_para
{
	unsigned char port;
	unsigned long long local;
	unsigned int seconds;
	unsigned int nseconds;
	unsigned int arg;
};

struct rio_async_para
{
    unsigned char port;
    unsigned int result;
    unsigned int arg;
};

struct rio_dbell_para
{
    unsigned char port;
    unsigned int srcid;
    unsigned int destid;
    unsigned int data;
};

struct rio_atmu_para
{
    unsigned int no;
    unsigned int rowtar;
    unsigned int rowtear;
    unsigned int rowbar;
    unsigned int rowar;
    unsigned int rows1r;
    unsigned int rows2r;
    unsigned int rows3r;
};

struct srio_enum_stat_info{
	unsigned char  slot_found_dev_cnt[VT861_SLOT_NUM];
	unsigned char  slot_cfg_dev_num[VT861_SLOT_NUM];
	unsigned short error_pass_port_flag[VT861_SLOT_NUM];
};
struct srio_route_table{
	unsigned short destid;
	unsigned char port;
};
struct srio_enum_cnt_info{
	unsigned long init_mask;
	unsigned long route_table_cnt;
	unsigned long time_cnt_ms;
	unsigned long switch_cnts;
	unsigned long ep_cnts;
	unsigned long emp_sw_cnts;
	unsigned long err_pass_port_cnt;
	unsigned char  err_pass_slot[VT861_SLOT_NUM];
	unsigned char  err_pass_port[VT861_LTEA_SRIO_DEV_NUM];
	unsigned short destid_table[VT861_LTEA_SRIO_DEV_NUM];
	struct srio_route_table srt[VT861_SLOT_NUM][VT861_LTEA_SRIO_DEV_NUM];
};
#endif
