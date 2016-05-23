/******************************************************************************
 ** Filename:dys_dist_mac_main.c - 
 ** Copyright: uestc.
 ** Descriptions: dist MAC
 ** v1.0, 2010/07/07, maojianbing written
 ** ----------------------------------------------------------
 ** modification history:
 ** Modified by:loulina
 ** Modified date:2014.0703
 ** Descriptions:LTE IPADP
 ** v1.0, 2014/07/03, loulina written
 ******************************************************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/netdevice.h>

#include <linux/device.h>
#include <linux/time.h>
#include <net/sock.h>
#include <linux/if_ether.h>

#include <linux/string.h>
#include <linux/mm.h>
#include <linux/syscalls.h>
#include <asm/unistd.h>
#include <asm/uaccess.h>


MODULE_DESCRIPTION("lte ipadp kernel module");
MODULE_AUTHOR("");
MODULE_LICENSE("GPL");

#include "../fsm/fsmdec.h"
#include "../lte_system.h"
#include "../debug.h"

#include "ipadp_module.h"

#define MTU 1500

/* this is used for register the special packet type that processed by DYS */
struct packet_type pk_t = {
	.type = __constant_htons(DEV_PROTO_IPADP),
    	.func = fsm_dev_recv,
};

static const struct net_device_ops ipadp_netdev_ops = {
	.ndo_open = fsm_dev_open,
	.ndo_stop = fsm_dev_stop,
	.ndo_start_xmit = fsm_dev_tx,
	.ndo_get_stats = fsm_dev_get_stats,
	.ndo_do_ioctl = fsm_dev_ioctl,
	.ndo_set_config = fsm_dev_set_config,
	.ndo_tx_timeout = fsm_dev_tx_timeout,
};
	

	


/******************************************************************************
 ** Function name:DyS_dist_mac_net_device_stc_init
 ** Descriptions:initiate the field of struct net_device for register use in dys_dist_mac_module
 ** Input: 
 ** Output: 
 ** Returns: 
 ** Created by: 
 ** Created Date:2010/07/07 
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void dev_init(struct net_device *dev)
{
   	ipadp_priv* priv;
	int fsm_id;
   	ASSERT(dev);
    	dev->tx_queue_len = 128;   			/* the queue length */   
    	dev->mtu = MTU;					/* now we do not fragmentate the packet */
   	dev->header_ops = NULL;   			/* cancle eth_header function for not building ethnet mac header */ 
    	dev->addr_len = 0;
    	dev->hard_header_len = 0;
   /*	dev->open = fsm_dev_open;
    	dev->stop = fsm_dev_stop;
    	dev->set_config = fsm_dev_set_config; 
   	dev->hard_start_xmit = fsm_dev_tx;
    	dev->do_ioctl = fsm_dev_ioctl;
    	dev->get_stats = fsm_dev_get_stats;
   	dev->tx_timeout = fsm_dev_tx_timeout; */
	
	dev->netdev_ops = &ipadp_netdev_ops;
   	dev->watchdog_timeo = 1000;  				/* the time unit is jiffy */
   	dev->flags = IFF_BROADCAST | IFF_MULTICAST | IFF_NOARP;
	//dev->features |= NETIF_F_NO_CSUM;
	priv = (ipadp_priv*)netdev_priv(dev);
   	fsm_mem_set(priv,0,sizeof(ipadp_priv));
	fsm_core_create(dev);
	priv->ipadp_sv_ptr = fsm_mem_alloc(sizeof(ipadp_sv));
	fsm_mem_set(priv->ipadp_sv_ptr, 0, sizeof(ipadp_sv));
	fsm_id = fsm_create_register("ipadpfsm",ipadp_main,priv->ipadp_sv_ptr);
	fsm_mainport_bind(fsm_id);
    return;
}
                 
                 
/******************************************************************************
 ** Function name:dys_dist_mac_net_device_init
 ** Descriptions:initiate a net_device for dist_mac_layer        
 ** Input: 
 ** Output: 
 ** Returns: 
 ** Created by: 
 ** Created Date:2010/07/07 
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int fsm_dev_create(void)
{   
   	ipadp_priv *priv;
	const char  *name = "LTE_IPADP%d";
	char dev_addr[6] = {0x00,0x11,0x1A,0x1A,0x8A,0x42};
	NETDEV *dev = NULL;
	dev = alloc_netdev(sizeof(ipadp_priv), name, dev_init);
    if (dev == NULL)   /* allocation error */
		{
		return -2;
		}
	memcpy(dev->dev_addr, &dev_addr, 6);       
   	/* ---------ADD some private data into the net_device struct */
    priv = netdev_priv(dev);
    if (priv == NULL)
    	{                
        return -2;                   
    	}
   	 /* register the net device */    
   	if (register_netdev(dev))    /* register error */
		{
        free_netdev(dev);   /* release the struct net_device */
        dev = NULL;               
        return -1;
		}
 	return 0;       
}

/******************************************************************************
 ** Function name:dys_dist_mac_exit_module
 ** Descriptions:the exit of the module
 ** Input: 
 ** Output: 
 ** Returns: 
 ** Created by: 
 ** Created Date:2010/07/07 
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void fsm_dev_destroy(void)
{
	NETDEV* dev;
	ipadp_priv* priv;
	dev = (NETDEV*)fsm_dev_get();
	fsm_core_destroy();
	priv = netdev_priv(dev);
	fsm_mem_free(priv->ipadp_sv_ptr);
    	unregister_netdev(dev);
    	free_netdev(dev);
}   

/******************************************************************************
 ** Function name:DyS_dist_mac_net_device_open
 ** Descriptions:called when we use ifconfig up
 ** Input: 
 ** Output: 
 ** Returns: 
 ** Created by: 
 ** Created Date:2010/07/07 
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int fsm_dev_open(struct net_device *dev)
{		
    /*-----------------now we need to register the special protocol_type */
	fsm_core_intf_set(STRM_TO_IP, DEV_INTF_IND, DEV_PROTO_IP, NULL);	
	fsm_core_intf_set(STRM_TO_PDCP, DEV_INTF_REQ, DEV_PROTO_IPADP, "LTE_PDCP0");
	fsm_core_intf_set(STRM_TO_MAC, DEV_INTF_REQ, DEV_PROTO_IPADP, "LTE_MAC0");
    	dev_add_pack(&pk_t); 
	netif_start_queue(dev);   
    	fsm_core_open();	 
    	return 0;    
}


/******************************************************************************
 ** Function name:DyS_dist_mac_net_device_stop
 ** Descriptions:called when we use ifconfig down
 ** Input: 
 ** Output: 
 ** Returns: 
 ** Created by: 
 ** Created Date:2010/07/07 
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int fsm_dev_stop(struct net_device *dev)
{  
         
    /*-----------------now we need to register the special protocol_type */
	fsm_core_close();
    	dev_remove_pack(&pk_t);
    	netif_stop_queue(dev);
     	return 0;    
}


/******************************************************************************
 ** Function name:DyS_dist_mac_net_device_recv
 ** Descriptions:receive the sk_buff submitted by the Dist_MAC Module and the Cent_MAC Module
 ** Input: 
 ** Output: 
 ** Returns: 
 ** Created by: 
 ** Created Date:2010/07/07 
 **-------------------------------------- ------system--------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int fsm_dev_recv(struct sk_buff *skb ,struct net_device *dev1, struct packet_type *pktype, struct net_device *dev2)
{  
    	fsm_core_pkt_drive(skb, RXTX_PKT_IND);
    	return 0;            
}


/******************************************************************************
 ** Function name:DyS_dist_mac_net_device_set_config
 ** Descriptions:
 ** Input: 
 ** Output: 
 ** Returns: 
 ** Created by: 
 ** Created Date:2010/07/07 
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int fsm_dev_set_config(struct net_device *dev, struct ifmap *p_ifmap)
{
    	return 0;
}
    
    
/******************************************************************************
 ** Function name:DyS_dist_mac_net_device_tx
 ** Descriptions:transmit sk_buff handed down by the up-layer
 ** Input: 
 ** Output: 
 ** Returns: 
 ** Created by: 
 ** Created Date:2010/07/07 
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int fsm_dev_tx(struct sk_buff *skb, struct net_device *dev)
{ 
	fsm_core_pkt_drive(skb, RXTX_PKT_REQ);	
   	return 0;    
}	


/******************************************************************************
 ** Function name:DyS_dist_mac_net_device_ioctl
 ** Descriptions:
 ** Input: 
 ** Output: 
 ** Returns: 
 ** Created by: 
 ** Created Date:2010/07/07 
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int fsm_dev_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	fsm_ioctrl_arrival(ifr,cmd);
	return 0;
}
        
        
/******************************************************************************
 ** Function name:DyS_dist_mac_net_device_get_stats
 ** Descriptions:
 ** Input: 
 ** Output: 
 ** Returns: 
 ** Created by: 
 ** Created Date:2010/07/07 
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
struct net_device_stats* fsm_dev_get_stats(struct net_device *dev)
{
    ipadp_priv* priv;
    priv = (ipadp_priv*)netdev_priv(dev);
    return &(priv->stats);            
}
    
/******************************************************************************
 ** Function name:DyS_dist_mac_net_device_tx_timeout
 ** Descriptions:tx timeout call_back function
 ** Input: 
 ** Output: 
 ** Returns: 
 ** Created by: 
 ** Created Date:2010/07/07 
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void fsm_dev_tx_timeout(struct net_device *dev)
{  
    return;   
}




module_init(fsm_dev_create);
module_exit(fsm_dev_destroy);














