#ifndef VT861_CARRIER
#define VT861_CARRIER

#define VT861_SLOT_NUM (12)
#define VT861_LTEA_SRIO_DEV_NUM (60)

/* MCH board slot in VT861*/
#define VT861_MCH_SLOT (0x0)
/* SRIO register bit define */
#define SRIO_DEV_DISCOVERED_BIT (0x2 << 28 )
#define VT861_SRIO_EP_HOPCOUNT (0x2)


/* Lp-serial extended features registers base address,
	 both for freescale p4080 and IDT1848 SWITCH */
#define SRIO_LPS_EXT_FTR_PTR (0x100)
/* Error reporting extended features registers base address,for freescale p4080 */
#define SRIO_P4080_ER_EXT_FTR_PTR (0x600)
/* Error Managerment Extension registers base address,for IDT1848 SWITCH */
#define SRIO_IDT1848_ER_EXT_FTR_PTR (0x1000)

/* port link time-out CSR */
#define SRIO_PLTOCCSR (0x120)
/* port response time-out CSR */
#define SRIO_PRTOCCSR (0x124)
/* port general control CSR*/
#define SRIO_PGCCSR (0x13c)
/* port link maintenance request CSR */
#define SRIO_PLMREQCSR (0x40)
/* port link maintenance response CSR */
#define SRIO_PLMRESPCSR (0x44)
/* port local ackID status CSR*/
#define SRIO_PLASCSR (0x48)
/* port error and status CSR */
#define SRIO_PESCSR (0x58)
/* port control CSR */
#define SRIO_PCCSR (0x5c)
/* logical/transport layer error detect CSR */
#define SRIO_LTLEDCSR (0x8)
/* logical/transport layer error enable CSR */
#define SRIO_LTLEECSR (0xc)
/* logical/transport layer address capture CSR */
#define SRIO_LTLACCSR (0x14)
/* logical/transport layer device ID capture CSR */
#define SRIO_LTLDIDCCSR (0x18)
/* logical/transport layer control capture CSR */
#define SRIO_LTLCCCSR (0x1c)
/* port 1 error detect CSR */
#define SRIO_P1EDCSR (0x40)
/* port 1 error rate enable CSR */
#define SRIO_P1ERECSR (0x44)
/* port 1 error capture attributes CSR */
#define SRIO_P1ECACSR (0x48)
/* port 1 packet/control symbol error capture CSR0*/
#define SRIO_P1PCSECCSR0 (0x4c)
/* port 1 packet error capture CSR1 */
#define SRIO_P1PECCSR1 (0x50)
/* port 1 packet error capture CSR2 */
#define SRIO_P1PECCSR2 (0x54)
/* port 1 packet error capture CSR3 */
#define SRIO_P1PECCSR3 (0x58)
/* port 1 error rate CSR */
#define SRIO_P1ERCSR (0x68)
/* port 1 error rate threshold CSR */
#define SRIO_P1ERTCSR (0x6c)
/* logical layer configuration register */
#define SRIO_LLCR   (0x10004)
/* error/port-write interrupt status register */
#define SRIO_EPWISR (0x10010)
/* logical retry error threshold configuration register */
#define SRIO_LRETCR (0x10020)
/* physical retry error threshold configuration register */
#define SRIO_PRETCR (0x10080)

#endif
