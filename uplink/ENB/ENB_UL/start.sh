#!/bin/bash
BASE_DIR=`pwd`
LTE_SRIO_DIR=$BASE_DIR/lte_virtual_srio_module
LTE_MAC_DIR=$BASE_DIR/lte_mac_module
LTE_RLC_DIR=$BASE_DIR/lte_rlc_module
LTE_PDCP_DIR=$BASE_DIR/lte_pdcp_module
LTE_RRC_DIR=$BASE_DIR/lte_rrc_module
LTE_IPADP_DIR=$BASE_DIR/lte_ip_adp_module


#cd $LTE_MAC_DIR
insmod mac.ko

#cd $LTE_SRIO_DIR
insmod srio.ko

#cd $LTE_RLC_DIR
insmod rlc.ko

#cd $LTE_PDCP_DIR
insmod pdcp.ko

#cd $LTE_RRC_DIR
insmod rrc.ko

#cd $LTE_IPADP_DIR
insmod ipadp.ko

ifconfig LTE_SRIO0 up
sleep 1
ifconfig LTE_MAC0 up
sleep 1
ifconfig LTE_RLC0 up
sleep 1
ifconfig LTE_PDCP0 up
sleep 1
ifconfig LTE_RRC0 up
sleep 1
ifconfig LTE_IPADP0 up
sleep 1
ifconfig LTE_IPADP0 10.10.10.8

echo "~~~Modules are working.~~~"
