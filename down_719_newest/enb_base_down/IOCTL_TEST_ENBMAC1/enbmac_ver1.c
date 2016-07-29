#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include "./enbmac_ver1.h" 
#define			PRINTRLC					0x0a
//./uemac -rareq 4 LTE_MAC0  //��3��������rapid ����4 
//uemac -ulschedreq LTE_MAC0
//uemac -dlschedreq LTE_MAC0
//uemac -reset LTE_MAC0
//uemac -test LTE_MAC0
//./uemac -rlc_send_req LTE_RLC0 //��RLC����datareq��MAC�� 
//./uemac -rrc_lc_config 2 1 LTE_MAC0 //�����߼��ŵ� 


/************�ָ���***************/
//./enbmac -rar_failed LTE_MAC0,ָʾENB MAC����RAR
//./endmac -rar_send LTE_MAC0,��RAR
//./endmac -pkt_num LTE_MAC0
int main(int argc, char *argv[])
{
	int sock;
	struct ifreq ifr;
	struct kifreq kifr;
	float interval;
	sock = socket(AF_INET, SOCK_DGRAM, 0); //����һ���׽ӿڣ�������SOCK_DGRAM(TCP), Э��������0��IP
	kifr.data_ptr = NULL;
	if(argc > 2)
	{	
		if(strcmp(argv[1], "-reset") == 0)
		{	
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				send_reset(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-pkt_num") == 0)
		{	
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				get_pkt_num(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-p") == 0)
		{	
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				rlc_print(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-rar_failed") == 0)
		{
			if(argc == 3) 
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				rar_failed(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-rar_send") == 0)
		{
			if(argc == 3) 
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				rar_send(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		if(kifr.data_ptr != NULL)
			free(kifr.data_ptr);
	}
	else
		usage();
	return 1;
}


void rlc_print(struct kifreq * ifr_ptr)
{
	ifr_ptr->cmd = PRINTRLC;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}
void get_pkt_num(struct kifreq * ifr_ptr)
{
	ifr_ptr->cmd = _IOCTLtoENBMAC_PKT_NUM ;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}
void rar_failed(struct kifreq * ifr_ptr)
{
	ifr_ptr->cmd = _IOCTLtoENBMAC_RAR_Failed ;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}

void rar_send(struct kifreq * ifr_ptr)
{
	ifr_ptr->cmd = _IOCTLtoENBMAC_RAR_Send ;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}

void send_reset(struct kifreq* ifr_ptr)
{
	ifr_ptr->cmd = _RRCtoMAC_reset ;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}


void usage(void)
{
	const char* info_ptr = "./enbmac -rar_failed  LTE_MAC0 \n";
	//printf(info_ptr);
}


	
	