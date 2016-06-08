
/* Define fsm interface index.*/		
#define		STRM_TO_IP				0
#define		STRM_TO_RLC				1
#define		STRM_TO_MAC				1
#define 	STRM_TO_SRIO			3
#define 	STRM_TO_ETH				4
#define 	STRM_TO_RRC				5
#define 	STRM_TO_PDCP			6	
#define 	STRM_TO_IPADP 			7
#define 	STRM_TO_RLCMAC			1 	//add in 20150803
//modified define MAX_INTF		32 in file fsmcore.c


/* Define protocol number for each fsm module.*/
#define		DEV_PROTO_SRIO			0xf4f7	
#define		DEV_PROTO_MAC			0xf4f4
#define		DEV_PROTO_RLC			0xf4f6
#define		DEV_PROTO_RRC			0xf4f3
//#define		DEV_PROTO_RRC			0xf4f2
#define 	DEV_PROTO_PDCP			0xf4f1
#define 	DEV_PROTO_IPADP 		0xf4f0

#define		DEV_PROTO_RLC_MAC		0xf4f8 	//add in 20150803
#define		DEV_PROTO_IP			ETH_P_IP



