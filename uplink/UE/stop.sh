#!/bin/bash
ifconfig LTE_RLC0 down
#ifconfig LTE_MAC0 down
#ifconfig LTE_SRIO0 down

rmmod lte_rlc_module
#rmmod lte_mac_module
#rmmod lte_virtual_srio_module

echo "~~~Modules are removed~~~"
