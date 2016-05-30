#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "./srio.h" 

//sriotest -s LTE_SRIO0
//sriotest -r LTE_SRIO0
//   ./sriotest -i LTE_SRIO0 xxxxx

int main(int argc, char *argv[])
{
	int sock;
	struct ifreq ifr;
	struct kifreq kifr;
	float interval;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	kifr.data_ptr = NULL;
	if(argc > 2)
	{
		
		if(strcmp(argv[1], "-s") == 0)
		{
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				periodical_send_stop(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}	
		}
		//ygf hello world test
		else if(strcmp(argv[1], "-hello_world")==0)
		{
            if(args == 3)
            	strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
            	print_hello(&kifr);
            	ifr.ifr_ifru.ifru_data = (void*)&kifr;
            	ioctl(sock, USERIOCCMD, &ifr);

		}
		else if(strcmp(argv[1], "-r") == 0)
		{	
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				periodical_send_run(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-stop") == 0)
		{	
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				stop_timer(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-add_interval") == 0)
		{	
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				add_interval(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-print_statistics") == 0)
		{	
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				print_pkt_ue(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-minus_interval") == 0)
		{	
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				minus_interval(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-readmem") == 0)
		{	
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				read_mem(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-lostpkt") == 0)
		{	
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				lost_pkt(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-stopriodt") == 0)
		{	
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				stop_riodt(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-sendsrio") == 0)
		{	
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				send_to_srio(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-racomplete") == 0)
		{	
			if(argc == 3)
			{
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				ra_complete(&kifr);
				ifr.ifr_ifru.ifru_data = (void*)&kifr;
				ioctl(sock, USERIOCCMD, &ifr);
			}
		}
		else if(strcmp(argv[1], "-i") == 0) 
		{
			if(argc == 4)
			{
				interval = atof(argv[3]);
				if(interval < 0.00001)
				{
					printf("The minimum send interval is 10 us.\n");
					return -1;
				}
				strcpy(ifr.ifr_ifrn.ifrn_name, argv[2]);
				periodical_send_interval(&kifr, interval);
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
//ygf hello world test
void print_hello(struct kifreq* ifr_ptr)
{
	ifr_ptr->cmd = HELLO_WORLD;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}

void add_interval(struct kifreq* ifr_ptr)
{
	ifr_ptr->cmd = ADD_INTERVAL;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}
void minus_interval(struct kifreq* ifr_ptr)
{
	ifr_ptr->cmd = MINUS_INTERVAL;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}
void periodical_send_stop(struct kifreq* ifr_ptr)
{
	ifr_ptr->cmd = PSEND_STOP;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}

void read_mem(struct kifreq* ifr_ptr)
{
	ifr_ptr->cmd = READ_MEM;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}

void stop_riodt(struct kifreq* ifr_ptr)
{
	ifr_ptr->cmd = RIODT_STOP;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}

void lost_pkt(struct kifreq* ifr_ptr)
{
	ifr_ptr->cmd = LOST_PKT_COUNT;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}

void ra_complete(struct kifreq* ifr_ptr)
{
	ifr_ptr->cmd = RA_COMPLETE;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}
void stop_timer(struct kifreq* ifr_ptr)
{
	ifr_ptr->cmd = STOP_TIMER;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}

void send_to_srio(struct kifreq* ifr_ptr)
{
	ifr_ptr->cmd = SEND_TO_SRIO;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}

void periodical_send_run(struct kifreq* ifr_ptr)
{
	ifr_ptr->cmd = PSEND_RUN;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}

void periodical_send_interval(struct kifreq* ifr_ptr, float interval)
{	
	unsigned int *ptr;
	ifr_ptr->cmd = PSEND_INTERVAL;
	ifr_ptr->size = sizeof(unsigned int);
	ptr = (unsigned int*) malloc(sizeof(unsigned int));
	*ptr = (unsigned int)(interval*100000);
	ifr_ptr->data_ptr = ptr;
}
void print_pkt_ue(struct kifreq* ifr_ptr)
{
	ifr_ptr->cmd = PRINT_COUNT_STATISTICS;
	ifr_ptr->size = 0;
	ifr_ptr->data_ptr = NULL;
}
void usage(void)
{
	const char* info_ptr = "sriotest -s LTE_SRIO0   \
			  	\nsriotest -r LTE_SRIO0 \
			  	\nsriotest -i LTE_SRIO0 xxxxx (seconds) \
			  	\nsriotest -print_statistics INTF\n";
	printf("%s", info_ptr);
}
	
	
	
	
