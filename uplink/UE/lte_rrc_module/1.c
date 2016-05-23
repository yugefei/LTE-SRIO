
lte_rrc_module.ko:     file format elf32-i386


Disassembly of section .text:

00000000 <fsm_ev_type>:

/* ---------------------utilities for state machine-----------------------------*/

/* Return information of event.	*/
u32 fsm_ev_type()
{
       0:	55                   	push   %ebp
       1:	89 e5                	mov    %esp,%ebp
       3:	e8 fc ff ff ff       	call   4 <fsm_ev_type+0x4>
	return fsm_core.evtype;
}
       8:	a1 10 00 00 00       	mov    0x10,%eax
       d:	5d                   	pop    %ebp
       e:	c3                   	ret    
       f:	90                   	nop

00000010 <fsm_ev_code>:

u32 fsm_ev_code()
{
      10:	55                   	push   %ebp
      11:	89 e5                	mov    %esp,%ebp
      13:	e8 fc ff ff ff       	call   14 <fsm_ev_code+0x4>
	return fsm_core.code;
}
      18:	a1 14 00 00 00       	mov    0x14,%eax
      1d:	5d                   	pop    %ebp
      1e:	c3                   	ret    
      1f:	90                   	nop

00000020 <fsm_ev_src>:

int fsm_ev_src()
{
      20:	55                   	push   %ebp
      21:	89 e5                	mov    %esp,%ebp
      23:	e8 fc ff ff ff       	call   24 <fsm_ev_src+0x4>
	return fsm_core.src;
}
      28:	a1 18 00 00 00       	mov    0x18,%eax
      2d:	5d                   	pop    %ebp
      2e:	c3                   	ret    
      2f:	90                   	nop

00000030 <fsm_ev_ioctrl_cmd>:

u32 fsm_ev_ioctrl_cmd()
{
      30:	55                   	push   %ebp
      31:	89 e5                	mov    %esp,%ebp
      33:	e8 fc ff ff ff       	call   34 <fsm_ev_ioctrl_cmd+0x4>
	return fsm_core.ioctrl_cmd;
}
      38:	a1 10 01 00 00       	mov    0x110,%eax
      3d:	5d                   	pop    %ebp
      3e:	c3                   	ret    
      3f:	90                   	nop

00000040 <fsm_sv_ptr_get>:

/* FSM information get */
void* fsm_sv_ptr_get()
{
      40:	55                   	push   %ebp
      41:	89 e5                	mov    %esp,%ebp
      43:	e8 fc ff ff ff       	call   44 <fsm_sv_ptr_get+0x4>
	return fsm_core.fsm_sv_ptr;
}
      48:	a1 1c 00 00 00       	mov    0x1c,%eax
      4d:	5d                   	pop    %ebp
      4e:	c3                   	ret    
      4f:	90                   	nop

00000050 <fsm_current_state_ptr_get>:

int* fsm_current_state_ptr_get()
{
      50:	55                   	push   %ebp
      51:	89 e5                	mov    %esp,%ebp
      53:	e8 fc ff ff ff       	call   54 <fsm_current_state_ptr_get+0x4>
	return fsm_core.current_state_ptr;
}
      58:	a1 04 00 00 00       	mov    0x4,%eax
      5d:	5d                   	pop    %ebp
      5e:	c3                   	ret    
      5f:	90                   	nop

00000060 <fsm_dev_get>:

void* fsm_dev_get()
{
      60:	55                   	push   %ebp
      61:	89 e5                	mov    %esp,%ebp
      63:	e8 fc ff ff ff       	call   64 <fsm_dev_get+0x4>
	return fsm_core.dev;
}
      68:	a1 08 01 00 00       	mov    0x108,%eax
      6d:	5d                   	pop    %ebp
      6e:	c3                   	ret    
      6f:	90                   	nop

00000070 <fsm_intf_addr_get>:
	}
	*name ='\0';
}

void* fsm_intf_addr_get(int strm_id)
{
      70:	55                   	push   %ebp
      71:	89 e5                	mov    %esp,%ebp
      73:	e8 fc ff ff ff       	call   74 <fsm_intf_addr_get+0x4>
	if(INTF[strm_id].valid == DEV_INTF_REQ)
      78:	8d 50 02             	lea    0x2(%eax),%edx
      7b:	31 c0                	xor    %eax,%eax
      7d:	c1 e2 04             	shl    $0x4,%edx
      80:	83 ba 04 00 00 00 01 	cmpl   $0x1,0x4(%edx)
      87:	74 07                	je     90 <fsm_intf_addr_get+0x20>
		return INTF[strm_id].dev->dev_addr;
	else
		return NULL;
}
      89:	5d                   	pop    %ebp
      8a:	c3                   	ret    
      8b:	90                   	nop
      8c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
}

void* fsm_intf_addr_get(int strm_id)
{
	if(INTF[strm_id].valid == DEV_INTF_REQ)
		return INTF[strm_id].dev->dev_addr;
      90:	8b 82 0c 00 00 00    	mov    0xc(%edx),%eax
	else
		return NULL;
}
      96:	5d                   	pop    %ebp
}

void* fsm_intf_addr_get(int strm_id)
{
	if(INTF[strm_id].valid == DEV_INTF_REQ)
		return INTF[strm_id].dev->dev_addr;
      97:	8b 80 48 01 00 00    	mov    0x148(%eax),%eax
	else
		return NULL;
}
      9d:	c3                   	ret    
      9e:	66 90                	xchg   %ax,%ax

000000a0 <fsm_self_addr_get>:

u8* fsm_self_addr_get()
{
      a0:	55                   	push   %ebp
      a1:	89 e5                	mov    %esp,%ebp
      a3:	e8 fc ff ff ff       	call   a4 <fsm_self_addr_get+0x4>
      a8:	a1 08 01 00 00       	mov    0x108,%eax
	NETDEV* dev;
	dev = (NETDEV*)fsm_core.dev; 
	return (u8*)dev->dev_addr;
}
      ad:	5d                   	pop    %ebp
	else
		return NULL;
}

u8* fsm_self_addr_get()
{
      ae:	8b 80 48 01 00 00    	mov    0x148(%eax),%eax
	NETDEV* dev;
	dev = (NETDEV*)fsm_core.dev; 
	return (u8*)dev->dev_addr;
}
      b4:	c3                   	ret    
      b5:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
      b9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

000000c0 <fsm_data_get>:



void* fsm_data_get()
{
      c0:	55                   	push   %ebp
      c1:	89 e5                	mov    %esp,%ebp
      c3:	e8 fc ff ff ff       	call   c4 <fsm_data_get+0x4>
	void* buffer;
	buffer = fsm_core.buffer;
      c8:	a1 0c 01 00 00       	mov    0x10c,%eax
	fsm_core.buffer = NULL;
      cd:	c7 05 0c 01 00 00 00 	movl   $0x0,0x10c
      d4:	00 00 00 
	return buffer;
}
      d7:	5d                   	pop    %ebp
      d8:	c3                   	ret    
      d9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

000000e0 <fsm_pkt_get>:


/* Packet operation */

FSM_PKT* fsm_pkt_get()
{
      e0:	55                   	push   %ebp
      e1:	89 e5                	mov    %esp,%ebp
      e3:	e8 fc ff ff ff       	call   e4 <fsm_pkt_get+0x4>
	FSM_PKT* ptr;
	ptr = fsm_core.pkptr;
      e8:	a1 0c 00 00 00       	mov    0xc,%eax
	fsm_core.pkptr = NULL;
      ed:	c7 05 0c 00 00 00 00 	movl   $0x0,0xc
      f4:	00 00 00 
	return ptr;
}
      f7:	5d                   	pop    %ebp
      f8:	c3                   	ret    
      f9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00000100 <fsm_skb_reserve>:
{
	return SKB_PULL(pkptr, len);
}

void fsm_skb_reserve(FSM_PKT* pkptr , int len)
{
     100:	55                   	push   %ebp
     101:	89 e5                	mov    %esp,%ebp
     103:	e8 fc ff ff ff       	call   104 <fsm_skb_reserve+0x4>
 *	Increase the headroom of an empty &sk_buff by reducing the tail
 *	room. This is only allowed for an empty buffer.
 */
static inline void skb_reserve(struct sk_buff *skb, int len)
{
	skb->data += len;
     108:	01 90 ac 00 00 00    	add    %edx,0xac(%eax)
	skb->tail += len;
     10e:	01 90 a0 00 00 00    	add    %edx,0xa0(%eax)
	SKB_RESERVE(pkptr, len);
}
     114:	5d                   	pop    %ebp
     115:	c3                   	ret    
     116:	8d 76 00             	lea    0x0(%esi),%esi
     119:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00000120 <fsm_skb_tailroom>:

int fsm_skb_tailroom(FSM_PKT* pkptr)
{
     120:	55                   	push   %ebp
     121:	89 e5                	mov    %esp,%ebp
     123:	e8 fc ff ff ff       	call   124 <fsm_skb_tailroom+0x4>
     128:	89 c2                	mov    %eax,%edx
}


static inline int skb_is_nonlinear(const struct sk_buff *skb)
{
	return skb->data_len;
     12a:	31 c0                	xor    %eax,%eax
     12c:	8b 4a 54             	mov    0x54(%edx),%ecx
     12f:	85 c9                	test   %ecx,%ecx
     131:	75 0c                	jne    13f <fsm_skb_tailroom+0x1f>
 *
 *	Return the number of bytes of free space at the tail of an sk_buff
 */
static inline int skb_tailroom(const struct sk_buff *skb)
{
	return skb_is_nonlinear(skb) ? 0 : skb->end - skb->tail;
     133:	8b 82 a4 00 00 00    	mov    0xa4(%edx),%eax
     139:	2b 82 a0 00 00 00    	sub    0xa0(%edx),%eax
	return SKB_TAILROOM(pkptr);
}
     13f:	5d                   	pop    %ebp
     140:	c3                   	ret    
     141:	eb 0d                	jmp    150 <fsm_skb_headroom>
     143:	90                   	nop
     144:	90                   	nop
     145:	90                   	nop
     146:	90                   	nop
     147:	90                   	nop
     148:	90                   	nop
     149:	90                   	nop
     14a:	90                   	nop
     14b:	90                   	nop
     14c:	90                   	nop
     14d:	90                   	nop
     14e:	90                   	nop
     14f:	90                   	nop

00000150 <fsm_skb_headroom>:

int fsm_skb_headroom(FSM_PKT* pkptr)
{
     150:	55                   	push   %ebp
     151:	89 e5                	mov    %esp,%ebp
     153:	e8 fc ff ff ff       	call   154 <fsm_skb_headroom+0x4>
	return SKB_HEADROOM(pkptr);
}
     158:	5d                   	pop    %ebp
{
	return SKB_TAILROOM(pkptr);
}

int fsm_skb_headroom(FSM_PKT* pkptr)
{
     159:	89 c2                	mov    %eax,%edx
     15b:	8b 80 ac 00 00 00    	mov    0xac(%eax),%eax
     161:	2b 82 a8 00 00 00    	sub    0xa8(%edx),%eax
	return SKB_HEADROOM(pkptr);
}
     167:	c3                   	ret    
     168:	90                   	nop
     169:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00000170 <fsm_mainport_bind>:
		FSM[id] = NULL;
	}
}

void fsm_mainport_bind(int id)
{
     170:	55                   	push   %ebp
     171:	89 e5                	mov    %esp,%ebp
     173:	e8 fc ff ff ff       	call   174 <fsm_mainport_bind+0x4>
	fsm_core.main_port = id;
}
     178:	5d                   	pop    %ebp
	}
}

void fsm_mainport_bind(int id)
{
	fsm_core.main_port = id;
     179:	a3 ec 00 00 00       	mov    %eax,0xec
}
     17e:	c3                   	ret    
     17f:	90                   	nop

00000180 <fsm_get_name_by_id>:
	}
	return -1;
}

void fsm_get_name_by_id(int id, char* name)
{
     180:	55                   	push   %ebp
     181:	89 e5                	mov    %esp,%ebp
     183:	53                   	push   %ebx
     184:	e8 fc ff ff ff       	call   185 <fsm_get_name_by_id+0x5>
     189:	31 c9                	xor    %ecx,%ecx
     18b:	89 d3                	mov    %edx,%ebx
	int i;
	for(i=0; i< MAX_FSM; ++i)
	{
		if(FSM[i]->id == id)
     18d:	8b 14 8d f0 00 00 00 	mov    0xf0(,%ecx,4),%edx
     194:	39 82 80 00 00 00    	cmp    %eax,0x80(%edx)
     19a:	74 14                	je     1b0 <fsm_get_name_by_id+0x30>
}

void fsm_get_name_by_id(int id, char* name)
{
	int i;
	for(i=0; i< MAX_FSM; ++i)
     19c:	83 c1 01             	add    $0x1,%ecx
     19f:	83 f9 06             	cmp    $0x6,%ecx
     1a2:	75 e9                	jne    18d <fsm_get_name_by_id+0xd>
		{
			strcpy(name, FSM[i]->name);
			break;
		}
	}
	*name ='\0';
     1a4:	c6 03 00             	movb   $0x0,(%ebx)
}
     1a7:	5b                   	pop    %ebx
     1a8:	5d                   	pop    %ebp
     1a9:	c3                   	ret    
     1aa:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	int i;
	for(i=0; i< MAX_FSM; ++i)
	{
		if(FSM[i]->id == id)
		{
			strcpy(name, FSM[i]->name);
     1b0:	89 d8                	mov    %ebx,%eax
     1b2:	e8 fc ff ff ff       	call   1b3 <fsm_get_name_by_id+0x33>
			break;
		}
	}
	*name ='\0';
     1b7:	c6 03 00             	movb   $0x0,(%ebx)
}
     1ba:	5b                   	pop    %ebx
     1bb:	5d                   	pop    %ebp
     1bc:	c3                   	ret    
     1bd:	8d 76 00             	lea    0x0(%esi),%esi

000001c0 <__fsm_skb_netrx>:
{
	fsm_pkt_destroy(pkptr);
}

static void __fsm_skb_netrx(unsigned long data)
{
     1c0:	55                   	push   %ebp
     1c1:	89 e5                	mov    %esp,%ebp
     1c3:	53                   	push   %ebx
     1c4:	e8 fc ff ff ff       	call   1c5 <__fsm_skb_netrx+0x5>
     1c9:	eb 1d                	jmp    1e8 <__fsm_skb_netrx+0x28>
     1cb:	90                   	nop
     1cc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			spin_unlock_bh(&fsm_core.rx_queue_lock);
			break;
		}
		else
		{
			pkptr = skb_dequeue(fsm_core.rx_queue);
     1d0:	e8 fc ff ff ff       	call   1d1 <__fsm_skb_netrx+0x11>
     1d5:	89 c3                	mov    %eax,%ebx
			spin_unlock_bh(&fsm_core.rx_queue_lock);
     1d7:	b8 30 01 00 00       	mov    $0x130,%eax
     1dc:	e8 fc ff ff ff       	call   1dd <__fsm_skb_netrx+0x1d>
			NETIF_RX(pkptr);
     1e1:	89 d8                	mov    %ebx,%eax
     1e3:	e8 fc ff ff ff       	call   1e4 <__fsm_skb_netrx+0x24>
{
	FSM_PKT* pkptr;

	while(1)
	{
		spin_lock_bh(&fsm_core.rx_queue_lock);
     1e8:	b8 30 01 00 00       	mov    $0x130,%eax
     1ed:	e8 fc ff ff ff       	call   1ee <__fsm_skb_netrx+0x2e>
		if(skb_queue_empty(fsm_core.rx_queue))
     1f2:	a1 1c 01 00 00       	mov    0x11c,%eax
     1f7:	39 00                	cmp    %eax,(%eax)
     1f9:	75 d5                	jne    1d0 <__fsm_skb_netrx+0x10>
		{
			spin_unlock_bh(&fsm_core.rx_queue_lock);
     1fb:	b8 30 01 00 00       	mov    $0x130,%eax
     200:	e8 fc ff ff ff       	call   201 <__fsm_skb_netrx+0x41>
			NETIF_RX(pkptr);
		}
	}
	//	fsm_printf("__fsm_skb_netrx() packet receive\n");
	return;
}
     205:	5b                   	pop    %ebx
     206:	5d                   	pop    %ebp
     207:	c3                   	ret    
     208:	90                   	nop
     209:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00000210 <__fsm_skb_xmit>:

static void __fsm_skb_xmit(unsigned long data)
{
     210:	55                   	push   %ebp
     211:	89 e5                	mov    %esp,%ebp
     213:	53                   	push   %ebx
     214:	e8 fc ff ff ff       	call   215 <__fsm_skb_xmit+0x5>
     219:	eb 1d                	jmp    238 <__fsm_skb_xmit+0x28>
     21b:	90                   	nop
     21c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			spin_unlock_bh(&fsm_core.tx_queue_lock);
			break;
		}
		else
		{
			pkptr = skb_dequeue(fsm_core.tx_queue);
     220:	e8 fc ff ff ff       	call   221 <__fsm_skb_xmit+0x11>
     225:	89 c3                	mov    %eax,%ebx
			spin_unlock_bh(&fsm_core.tx_queue_lock);
     227:	b8 2c 01 00 00       	mov    $0x12c,%eax
     22c:	e8 fc ff ff ff       	call   22d <__fsm_skb_xmit+0x1d>
			//		fsm_octets_print(pkptr->data, pkptr->len);
			DEV_QUEUE_XMIT(pkptr);
     231:	89 d8                	mov    %ebx,%eax
     233:	e8 fc ff ff ff       	call   234 <__fsm_skb_xmit+0x24>
static void __fsm_skb_xmit(unsigned long data)
{
	FSM_PKT* pkptr;
	while(1)
	{
		spin_lock_bh(&fsm_core.tx_queue_lock);
     238:	b8 2c 01 00 00       	mov    $0x12c,%eax
     23d:	e8 fc ff ff ff       	call   23e <__fsm_skb_xmit+0x2e>
		if(skb_queue_empty(fsm_core.tx_queue))
     242:	a1 18 01 00 00       	mov    0x118,%eax
     247:	39 00                	cmp    %eax,(%eax)
     249:	75 d5                	jne    220 <__fsm_skb_xmit+0x10>
		{
			spin_unlock_bh(&fsm_core.tx_queue_lock);
     24b:	b8 2c 01 00 00       	mov    $0x12c,%eax
     250:	e8 fc ff ff ff       	call   251 <__fsm_skb_xmit+0x41>
			DEV_QUEUE_XMIT(pkptr);
		}
	}
	//	fsm_printf("__fsm_skb_xmit() packet send\n");
	return;
}
     255:	5b                   	pop    %ebx
     256:	5d                   	pop    %ebp
     257:	c3                   	ret    
     258:	90                   	nop
     259:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00000260 <fsm_core_intf_set>:
}

//proto is the protocol of upperlayer of the data stream 
//dev name is the destination of the data stream
void fsm_core_intf_set(int index, u32 type, u16 proto, const char* dev_name)
{
     260:	55                   	push   %ebp
     261:	89 e5                	mov    %esp,%ebp
     263:	83 ec 0c             	sub    $0xc,%esp
     266:	89 1c 24             	mov    %ebx,(%esp)
     269:	89 74 24 04          	mov    %esi,0x4(%esp)
     26d:	89 7c 24 08          	mov    %edi,0x8(%esp)
     271:	e8 fc ff ff ff       	call   272 <fsm_core_intf_set+0x12>
     276:	8b 7d 08             	mov    0x8(%ebp),%edi
	NETDEV *dev = NULL;
	switch(type)
     279:	83 fa 01             	cmp    $0x1,%edx
}

//proto is the protocol of upperlayer of the data stream 
//dev name is the destination of the data stream
void fsm_core_intf_set(int index, u32 type, u16 proto, const char* dev_name)
{
     27c:	89 c3                	mov    %eax,%ebx
     27e:	89 ce                	mov    %ecx,%esi
	NETDEV *dev = NULL;
	switch(type)
     280:	0f 84 aa 00 00 00    	je     330 <fsm_core_intf_set+0xd0>
     286:	72 38                	jb     2c0 <fsm_core_intf_set+0x60>
     288:	83 fa 02             	cmp    $0x2,%edx
     28b:	74 53                	je     2e0 <fsm_core_intf_set+0x80>
			INTF[index].proto = htons(proto);
			INTF[index].dev = dev;
			INTF[index].send = __fsm_skb_pending_xmit;
			break;
	}
	if(proto == 0 && dev_name == 0)
     28d:	85 ff                	test   %edi,%edi
     28f:	90                   	nop
     290:	75 1f                	jne    2b1 <fsm_core_intf_set+0x51>
     292:	66 85 f6             	test   %si,%si
     295:	75 1a                	jne    2b1 <fsm_core_intf_set+0x51>
	{
		INTF[index].valid = DEV_INTF_NULL;
     297:	83 c3 02             	add    $0x2,%ebx
     29a:	c1 e3 04             	shl    $0x4,%ebx
     29d:	c7 83 04 00 00 00 00 	movl   $0x0,0x4(%ebx)
     2a4:	00 00 00 
		INTF[index].send = __fsm_skb_send_null;
     2a7:	c7 83 10 00 00 00 90 	movl   $0xf90,0x10(%ebx)
     2ae:	0f 00 00 
	}
	return;
}
     2b1:	8b 1c 24             	mov    (%esp),%ebx
     2b4:	8b 74 24 04          	mov    0x4(%esp),%esi
     2b8:	8b 7c 24 08          	mov    0x8(%esp),%edi
     2bc:	89 ec                	mov    %ebp,%esp
     2be:	5d                   	pop    %ebp
     2bf:	c3                   	ret    
{
	NETDEV *dev = NULL;
	switch(type)
	{
		case DEV_INTF_NULL:
			INTF[index].valid = DEV_INTF_NULL;
     2c0:	8d 40 02             	lea    0x2(%eax),%eax
     2c3:	c1 e0 04             	shl    $0x4,%eax
     2c6:	c7 80 04 00 00 00 00 	movl   $0x0,0x4(%eax)
     2cd:	00 00 00 
			INTF[index].send = __fsm_skb_send_null;
     2d0:	c7 80 10 00 00 00 90 	movl   $0xf90,0x10(%eax)
     2d7:	0f 00 00 
			break;
     2da:	eb b1                	jmp    28d <fsm_core_intf_set+0x2d>
     2dc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
		case DEV_INTF_IND:
			if(dev_name)
     2e0:	31 c0                	xor    %eax,%eax
     2e2:	85 ff                	test   %edi,%edi
     2e4:	74 12                	je     2f8 <fsm_core_intf_set+0x98>
				dev = DEV_GET_BY_NAME(dev_name);
     2e6:	a1 08 01 00 00       	mov    0x108,%eax
     2eb:	89 fa                	mov    %edi,%edx
     2ed:	8b 80 44 02 00 00    	mov    0x244(%eax),%eax
     2f3:	e8 fc ff ff ff       	call   2f4 <fsm_core_intf_set+0x94>
			INTF[index].valid = DEV_INTF_IND;
			INTF[index].proto = htons(proto);
     2f8:	89 f1                	mov    %esi,%ecx
     2fa:	66 c1 c1 08          	rol    $0x8,%cx
			INTF[index].send = __fsm_skb_send_null;
			break;
		case DEV_INTF_IND:
			if(dev_name)
				dev = DEV_GET_BY_NAME(dev_name);
			INTF[index].valid = DEV_INTF_IND;
     2fe:	8d 53 02             	lea    0x2(%ebx),%edx
     301:	c1 e2 04             	shl    $0x4,%edx
     304:	c7 82 04 00 00 00 02 	movl   $0x2,0x4(%edx)
     30b:	00 00 00 
			INTF[index].proto = htons(proto);
			INTF[index].dev = dev;
     30e:	89 82 0c 00 00 00    	mov    %eax,0xc(%edx)
			INTF[index].send = __fsm_skb_pending_netrx;
     314:	c7 82 10 00 00 00 80 	movl   $0x480,0x10(%edx)
     31b:	04 00 00 
			break;
		case DEV_INTF_IND:
			if(dev_name)
				dev = DEV_GET_BY_NAME(dev_name);
			INTF[index].valid = DEV_INTF_IND;
			INTF[index].proto = htons(proto);
     31e:	66 89 8a 08 00 00 00 	mov    %cx,0x8(%edx)
			INTF[index].dev = dev;
			INTF[index].send = __fsm_skb_pending_netrx;
			break;
     325:	e9 63 ff ff ff       	jmp    28d <fsm_core_intf_set+0x2d>
     32a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
		case DEV_INTF_REQ:
			if(dev_name)
     330:	31 c0                	xor    %eax,%eax
     332:	85 ff                	test   %edi,%edi
     334:	74 12                	je     348 <fsm_core_intf_set+0xe8>
				dev = DEV_GET_BY_NAME(dev_name);
     336:	a1 08 01 00 00       	mov    0x108,%eax
     33b:	89 fa                	mov    %edi,%edx
     33d:	8b 80 44 02 00 00    	mov    0x244(%eax),%eax
     343:	e8 fc ff ff ff       	call   344 <fsm_core_intf_set+0xe4>
			INTF[index].valid = DEV_INTF_REQ;
			INTF[index].proto = htons(proto);
     348:	89 f1                	mov    %esi,%ecx
     34a:	66 c1 c1 08          	rol    $0x8,%cx
			INTF[index].send = __fsm_skb_pending_netrx;
			break;
		case DEV_INTF_REQ:
			if(dev_name)
				dev = DEV_GET_BY_NAME(dev_name);
			INTF[index].valid = DEV_INTF_REQ;
     34e:	8d 53 02             	lea    0x2(%ebx),%edx
     351:	c1 e2 04             	shl    $0x4,%edx
     354:	c7 82 04 00 00 00 01 	movl   $0x1,0x4(%edx)
     35b:	00 00 00 
			INTF[index].proto = htons(proto);
			INTF[index].dev = dev;
     35e:	89 82 0c 00 00 00    	mov    %eax,0xc(%edx)
			INTF[index].send = __fsm_skb_pending_xmit;
     364:	c7 82 10 00 00 00 30 	movl   $0x430,0x10(%edx)
     36b:	04 00 00 
			break;
		case DEV_INTF_REQ:
			if(dev_name)
				dev = DEV_GET_BY_NAME(dev_name);
			INTF[index].valid = DEV_INTF_REQ;
			INTF[index].proto = htons(proto);
     36e:	66 89 8a 08 00 00 00 	mov    %cx,0x8(%edx)
     375:	e9 13 ff ff ff       	jmp    28d <fsm_core_intf_set+0x2d>
     37a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00000380 <fsm_ntohl>:
{
	return NTOHS(val);
}

u32 fsm_ntohl(u32 val)
{
     380:	55                   	push   %ebp
     381:	89 e5                	mov    %esp,%ebp
     383:	e8 fc ff ff ff       	call   384 <fsm_ntohl+0x4>

static inline __attribute_const__ __u32 __arch_swab32(__u32 val)
{
#ifdef __i386__
# ifdef CONFIG_X86_BSWAP
	asm("bswap %0" : "=r" (val) : "0" (val));
     388:	0f c8                	bswap  %eax
	return NTOHL(val);
}
     38a:	5d                   	pop    %ebp
     38b:	c3                   	ret    
     38c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00000390 <fsm_ntohs>:
{
	return HTONL(val);
}

u16 fsm_ntohs(u16 val)
{
     390:	55                   	push   %ebp
     391:	89 e5                	mov    %esp,%ebp
     393:	e8 fc ff ff ff       	call   394 <fsm_ntohs+0x4>
	return NTOHS(val);
}
     398:	5d                   	pop    %ebp
{
	return HTONL(val);
}

u16 fsm_ntohs(u16 val)
{
     399:	66 c1 c0 08          	rol    $0x8,%ax
	return NTOHS(val);
}
     39d:	c3                   	ret    
     39e:	66 90                	xchg   %ax,%ax

000003a0 <fsm_htonl>:
{
	return HTONS(val);
}

u32 fsm_htonl(u32 val)
{
     3a0:	55                   	push   %ebp
     3a1:	89 e5                	mov    %esp,%ebp
     3a3:	e8 fc ff ff ff       	call   3a4 <fsm_htonl+0x4>
     3a8:	0f c8                	bswap  %eax
	return HTONL(val);
}
     3aa:	5d                   	pop    %ebp
     3ab:	c3                   	ret    
     3ac:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

000003b0 <fsm_htons>:
	return num;
}

/* Endianness */
u16 fsm_htons(u16 val)
{
     3b0:	55                   	push   %ebp
     3b1:	89 e5                	mov    %esp,%ebp
     3b3:	e8 fc ff ff ff       	call   3b4 <fsm_htons+0x4>
	return HTONS(val);
}
     3b8:	5d                   	pop    %ebp
	return num;
}

/* Endianness */
u16 fsm_htons(u16 val)
{
     3b9:	66 c1 c0 08          	rol    $0x8,%ax
	return HTONS(val);
}
     3bd:	c3                   	ret    
     3be:	66 90                	xchg   %ax,%ax

000003c0 <fsm_mem_set>:
{
	return FSM_MEM_CPY(dst_ptr,src_ptr,size);
}

void* fsm_mem_set(void* dst_ptr, const int val, size_t size)
{
     3c0:	55                   	push   %ebp
     3c1:	89 e5                	mov    %esp,%ebp
     3c3:	83 ec 08             	sub    $0x8,%esp
     3c6:	89 1c 24             	mov    %ebx,(%esp)
     3c9:	89 7c 24 04          	mov    %edi,0x4(%esp)
     3cd:	e8 fc ff ff ff       	call   3ce <fsm_mem_set+0xe>
     3d2:	89 c3                	mov    %eax,%ebx
extern void *memchr(const void *cs, int c, size_t count);

static inline void *__memset_generic(void *s, char c, size_t count)
{
	int d0, d1;
	asm volatile("rep\n\t"
     3d4:	89 c7                	mov    %eax,%edi
     3d6:	89 d0                	mov    %edx,%eax
     3d8:	f3 aa                	rep stos %al,%es:(%edi)
	return FSM_MEM_SET(dst_ptr,val,size);
}
     3da:	89 d8                	mov    %ebx,%eax
     3dc:	8b 7c 24 04          	mov    0x4(%esp),%edi
     3e0:	8b 1c 24             	mov    (%esp),%ebx
     3e3:	89 ec                	mov    %ebp,%esp
     3e5:	5d                   	pop    %ebp
     3e6:	c3                   	ret    
     3e7:	89 f6                	mov    %esi,%esi
     3e9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

000003f0 <fsm_mem_cpy>:
{
	FSM_MEM_FREE(ptr);
}

void* fsm_mem_cpy(void* dst_ptr, const void* src_ptr, size_t size)
{
     3f0:	55                   	push   %ebp
     3f1:	89 e5                	mov    %esp,%ebp
     3f3:	83 ec 0c             	sub    $0xc,%esp
     3f6:	89 1c 24             	mov    %ebx,(%esp)
     3f9:	89 74 24 04          	mov    %esi,0x4(%esp)
     3fd:	89 7c 24 08          	mov    %edi,0x8(%esp)
     401:	e8 fc ff ff ff       	call   402 <fsm_mem_cpy+0x12>
     406:	89 cb                	mov    %ecx,%ebx
extern size_t strlen(const char *s);

static __always_inline void *__memcpy(void *to, const void *from, size_t n)
{
	int d0, d1, d2;
	asm volatile("rep ; movsl\n\t"
     408:	89 c7                	mov    %eax,%edi
     40a:	c1 e9 02             	shr    $0x2,%ecx
     40d:	89 d6                	mov    %edx,%esi
     40f:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
     411:	89 d9                	mov    %ebx,%ecx
     413:	83 e1 03             	and    $0x3,%ecx
     416:	74 02                	je     41a <fsm_mem_cpy+0x2a>
     418:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
	return FSM_MEM_CPY(dst_ptr,src_ptr,size);
}
     41a:	8b 1c 24             	mov    (%esp),%ebx
     41d:	8b 74 24 04          	mov    0x4(%esp),%esi
     421:	8b 7c 24 08          	mov    0x8(%esp),%edi
     425:	89 ec                	mov    %ebp,%esp
     427:	5d                   	pop    %ebp
     428:	c3                   	ret    
     429:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00000430 <__fsm_skb_pending_xmit>:
	//	fsm_pkt_destroy(pkptr);
	return;
}

static void __fsm_skb_pending_xmit(FSM_PKT* pkptr, NETDEV* dev, u16 protocol)
{
     430:	55                   	push   %ebp
     431:	89 e5                	mov    %esp,%ebp
     433:	53                   	push   %ebx
     434:	e8 fc ff ff ff       	call   435 <__fsm_skb_pending_xmit+0x5>
	SKBUFF* skb;
	skb = (SKBUFF*)pkptr;
	skb->dev = dev;
	skb->protocol = protocol;
     439:	66 89 48 66          	mov    %cx,0x66(%eax)
	//	fsm_pkt_destroy(pkptr);
	return;
}

static void __fsm_skb_pending_xmit(FSM_PKT* pkptr, NETDEV* dev, u16 protocol)
{
     43d:	89 c3                	mov    %eax,%ebx
	SKBUFF* skb;
	skb = (SKBUFF*)pkptr;
	skb->dev = dev;
     43f:	89 50 14             	mov    %edx,0x14(%eax)
	skb->protocol = protocol;
	spin_lock(&fsm_core.tx_queue_lock);
     442:	b8 2c 01 00 00       	mov    $0x12c,%eax
     447:	e8 fc ff ff ff       	call   448 <__fsm_skb_pending_xmit+0x18>
	skb_queue_tail(fsm_core.tx_queue, pkptr);
     44c:	a1 18 01 00 00       	mov    0x118,%eax
     451:	89 da                	mov    %ebx,%edx
     453:	e8 fc ff ff ff       	call   454 <__fsm_skb_pending_xmit+0x24>
	return PVOP_CALL1(int, pv_lock_ops.spin_trylock, lock);
}

static __always_inline void __raw_spin_unlock(struct raw_spinlock *lock)
{
	PVOP_VCALL1(pv_lock_ops.spin_unlock, lock);
     458:	b8 2c 01 00 00       	mov    $0x12c,%eax
     45d:	ff 15 14 00 00 00    	call   *0x14
	spin_unlock(&fsm_core.tx_queue_lock);
	tasklet_schedule(fsm_core.tx_tsklt);
     463:	a1 20 01 00 00       	mov    0x120,%eax
 */
static inline int test_and_set_bit(int nr, volatile unsigned long *addr)
{
	int oldbit;

	asm volatile(LOCK_PREFIX "bts %2,%1\n\t"
     468:	f0 0f ba 68 04 00    	lock btsl $0x0,0x4(%eax)
     46e:	19 d2                	sbb    %edx,%edx

extern void __tasklet_schedule(struct tasklet_struct *t);

static inline void tasklet_schedule(struct tasklet_struct *t)
{
	if (!test_and_set_bit(TASKLET_STATE_SCHED, &t->state))
     470:	85 d2                	test   %edx,%edx
     472:	75 05                	jne    479 <__fsm_skb_pending_xmit+0x49>
		__tasklet_schedule(t);
     474:	e8 fc ff ff ff       	call   475 <__fsm_skb_pending_xmit+0x45>
	//	fsm_pkt_destroy(pkptr);
	return;
}
     479:	5b                   	pop    %ebx
     47a:	5d                   	pop    %ebp
     47b:	c3                   	ret    
     47c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00000480 <__fsm_skb_pending_netrx>:
	fsm_core.ioctrl_cmd = INVALIDE;
	return;
}

static void __fsm_skb_pending_netrx(FSM_PKT* pkptr, NETDEV* dev, u16 protocol)
{
     480:	55                   	push   %ebp
     481:	89 e5                	mov    %esp,%ebp
     483:	53                   	push   %ebx
     484:	e8 fc ff ff ff       	call   485 <__fsm_skb_pending_netrx+0x5>
	SKBUFF* skb;
	skb = (SKBUFF*)pkptr;
	skb->protocol = protocol;
	skb->dev = dev;
	if(skb->protocol == htons(ETH_P_IP))
     489:	66 83 f9 08          	cmp    $0x8,%cx
	fsm_core.ioctrl_cmd = INVALIDE;
	return;
}

static void __fsm_skb_pending_netrx(FSM_PKT* pkptr, NETDEV* dev, u16 protocol)
{
     48d:	89 c3                	mov    %eax,%ebx
	SKBUFF* skb;
	skb = (SKBUFF*)pkptr;
	skb->protocol = protocol;
     48f:	66 89 48 66          	mov    %cx,0x66(%eax)
	skb->dev = dev;
     493:	89 50 14             	mov    %edx,0x14(%eax)
	if(skb->protocol == htons(ETH_P_IP))
     496:	74 40                	je     4d8 <__fsm_skb_pending_netrx+0x58>
	{
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	}
	spin_lock(&fsm_core.rx_queue_lock);
     498:	b8 30 01 00 00       	mov    $0x130,%eax
     49d:	e8 fc ff ff ff       	call   49e <__fsm_skb_pending_netrx+0x1e>
	skb_queue_tail(fsm_core.rx_queue, pkptr);
     4a2:	a1 1c 01 00 00       	mov    0x11c,%eax
     4a7:	89 da                	mov    %ebx,%edx
     4a9:	e8 fc ff ff ff       	call   4aa <__fsm_skb_pending_netrx+0x2a>
     4ae:	b8 30 01 00 00       	mov    $0x130,%eax
     4b3:	ff 15 14 00 00 00    	call   *0x14
	spin_unlock(&fsm_core.rx_queue_lock);
	tasklet_schedule(fsm_core.rx_tsklt);
     4b9:	a1 24 01 00 00       	mov    0x124,%eax
     4be:	f0 0f ba 68 04 00    	lock btsl $0x0,0x4(%eax)
     4c4:	19 d2                	sbb    %edx,%edx

extern void __tasklet_schedule(struct tasklet_struct *t);

static inline void tasklet_schedule(struct tasklet_struct *t)
{
	if (!test_and_set_bit(TASKLET_STATE_SCHED, &t->state))
     4c6:	85 d2                	test   %edx,%edx
     4c8:	75 05                	jne    4cf <__fsm_skb_pending_netrx+0x4f>
		__tasklet_schedule(t);
     4ca:	e8 fc ff ff ff       	call   4cb <__fsm_skb_pending_netrx+0x4b>
	//	fsm_pkt_destroy(pkptr);
	return;
}
     4cf:	5b                   	pop    %ebx
     4d0:	5d                   	pop    %ebp
     4d1:	c3                   	ret    
     4d2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	skb = (SKBUFF*)pkptr;
	skb->protocol = protocol;
	skb->dev = dev;
	if(skb->protocol == htons(ETH_P_IP))
	{
		skb->ip_summed = CHECKSUM_UNNECESSARY;
     4d8:	0f b6 40 64          	movzbl 0x64(%eax),%eax
     4dc:	83 e0 f3             	and    $0xfffffff3,%eax
     4df:	83 c8 04             	or     $0x4,%eax
     4e2:	88 43 64             	mov    %al,0x64(%ebx)
     4e5:	eb b1                	jmp    498 <__fsm_skb_pending_netrx+0x18>
     4e7:	89 f6                	mov    %esi,%esi
     4e9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

000004f0 <fsm_get_random_bytes>:
}


/* Random bytes get*/
void fsm_get_random_bytes(void *buf, int nbytes)
{
     4f0:	55                   	push   %ebp
     4f1:	89 e5                	mov    %esp,%ebp
     4f3:	e8 fc ff ff ff       	call   4f4 <fsm_get_random_bytes+0x4>
	GET_RANDOM_BYTES(buf, nbytes);
     4f8:	e8 fc ff ff ff       	call   4f9 <fsm_get_random_bytes+0x9>
}
     4fd:	5d                   	pop    %ebp
     4fe:	c3                   	ret    
     4ff:	90                   	nop

00000500 <fsm_get_curtime>:



/* Time get */
u32 fsm_get_curtime()
{
     500:	55                   	push   %ebp
     501:	89 e5                	mov    %esp,%ebp
     503:	e8 fc ff ff ff       	call   504 <fsm_get_curtime+0x4>
	ktime_t	ktime;
	struct timeval cur_time;
	u32 ctm;
	ktime = ktime_get();
     508:	e8 fc ff ff ff       	call   509 <fsm_get_curtime+0x9>
	cur_time = ktime_to_timeval(ktime);
     50d:	e8 fc ff ff ff       	call   50e <fsm_get_curtime+0xe>
	ctm = cur_time.tv_sec * 1000000 + cur_time.tv_usec;
     512:	b9 cd cc cc cc       	mov    $0xcccccccd,%ecx
	ctm = ctm/10;
	return ctm;
}
     517:	5d                   	pop    %ebp
	ktime_t	ktime;
	struct timeval cur_time;
	u32 ctm;
	ktime = ktime_get();
	cur_time = ktime_to_timeval(ktime);
	ctm = cur_time.tv_sec * 1000000 + cur_time.tv_usec;
     518:	69 c0 40 42 0f 00    	imul   $0xf4240,%eax,%eax
     51e:	8d 14 10             	lea    (%eax,%edx,1),%edx
     521:	89 d0                	mov    %edx,%eax
     523:	f7 e1                	mul    %ecx
     525:	c1 ea 03             	shr    $0x3,%edx
	ctm = ctm/10;
	return ctm;
}
     528:	89 d0                	mov    %edx,%eax
     52a:	c3                   	ret    
     52b:	90                   	nop
     52c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00000530 <__fsm_tm_restart>:
	}
	return FSM_EXEC_FAIL;
}

static void __fsm_tm_restart()
{
     530:	55                   	push   %ebp
     531:	89 e5                	mov    %esp,%ebp
     533:	83 ec 04             	sub    $0x4,%esp
     536:	e8 fc ff ff ff       	call   537 <__fsm_tm_restart+0x7>
	__tmBlock* pB;
	pB = TMBLOCK_PTR;
	if(!(pB->evQ))
     53b:	a1 e8 00 00 00       	mov    0xe8,%eax
     540:	85 c0                	test   %eax,%eax
     542:	0f 84 80 00 00 00    	je     5c8 <__fsm_tm_restart+0x98>
	{
		pB->tm_state = FSM_TM_STOP;
		return;
	}
	if(pB->tm_state == FSM_TM_STOP)
     548:	a1 a4 00 00 00       	mov    0xa4,%eax
     54d:	85 c0                	test   %eax,%eax
     54f:	74 3f                	je     590 <__fsm_tm_restart+0x60>
	{	
		pB->timer.function = __fsm_tm_expire;
		hrtimer_start(&pB->timer, pB->evQ->expire, HRTIMER_MODE_ABS);
		pB->tm_state = FSM_TM_RUN;
	}
	else if(pB->tm_state == FSM_TM_RUN)
     551:	83 f8 01             	cmp    $0x1,%eax
     554:	74 02                	je     558 <__fsm_tm_restart+0x28>
	{	
		hrtimer_cancel(&pB->timer);
		pB->timer.function = __fsm_tm_expire;
		hrtimer_start(&pB->timer, pB->evQ->expire, HRTIMER_MODE_ABS);
	}
}
     556:	c9                   	leave  
     557:	c3                   	ret    
		hrtimer_start(&pB->timer, pB->evQ->expire, HRTIMER_MODE_ABS);
		pB->tm_state = FSM_TM_RUN;
	}
	else if(pB->tm_state == FSM_TM_RUN)
	{	
		hrtimer_cancel(&pB->timer);
     558:	b8 a8 00 00 00       	mov    $0xa8,%eax
     55d:	e8 fc ff ff ff       	call   55e <__fsm_tm_restart+0x2e>
		pB->timer.function = __fsm_tm_expire;
		hrtimer_start(&pB->timer, pB->evQ->expire, HRTIMER_MODE_ABS);
     562:	a1 e8 00 00 00       	mov    0xe8,%eax
		pB->tm_state = FSM_TM_RUN;
	}
	else if(pB->tm_state == FSM_TM_RUN)
	{	
		hrtimer_cancel(&pB->timer);
		pB->timer.function = __fsm_tm_expire;
     567:	c7 05 c4 00 00 00 f0 	movl   $0xbf0,0xc4
     56e:	0b 00 00 
		hrtimer_start(&pB->timer, pB->evQ->expire, HRTIMER_MODE_ABS);
     571:	8b 50 08             	mov    0x8(%eax),%edx
     574:	8b 48 0c             	mov    0xc(%eax),%ecx
     577:	b8 a8 00 00 00       	mov    $0xa8,%eax
     57c:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     583:	e8 fc ff ff ff       	call   584 <__fsm_tm_restart+0x54>
	}
}
     588:	c9                   	leave  
     589:	c3                   	ret    
     58a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
		return;
	}
	if(pB->tm_state == FSM_TM_STOP)
	{	
		pB->timer.function = __fsm_tm_expire;
		hrtimer_start(&pB->timer, pB->evQ->expire, HRTIMER_MODE_ABS);
     590:	a1 e8 00 00 00       	mov    0xe8,%eax
		pB->tm_state = FSM_TM_STOP;
		return;
	}
	if(pB->tm_state == FSM_TM_STOP)
	{	
		pB->timer.function = __fsm_tm_expire;
     595:	c7 05 c4 00 00 00 f0 	movl   $0xbf0,0xc4
     59c:	0b 00 00 
		hrtimer_start(&pB->timer, pB->evQ->expire, HRTIMER_MODE_ABS);
     59f:	8b 50 08             	mov    0x8(%eax),%edx
     5a2:	8b 48 0c             	mov    0xc(%eax),%ecx
     5a5:	b8 a8 00 00 00       	mov    $0xa8,%eax
     5aa:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     5b1:	e8 fc ff ff ff       	call   5b2 <__fsm_tm_restart+0x82>
		pB->tm_state = FSM_TM_RUN;
     5b6:	c7 05 a4 00 00 00 01 	movl   $0x1,0xa4
     5bd:	00 00 00 
	{	
		hrtimer_cancel(&pB->timer);
		pB->timer.function = __fsm_tm_expire;
		hrtimer_start(&pB->timer, pB->evQ->expire, HRTIMER_MODE_ABS);
	}
}
     5c0:	c9                   	leave  
     5c1:	c3                   	ret    
     5c2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
{
	__tmBlock* pB;
	pB = TMBLOCK_PTR;
	if(!(pB->evQ))
	{
		pB->tm_state = FSM_TM_STOP;
     5c8:	c7 05 a4 00 00 00 00 	movl   $0x0,0xa4
     5cf:	00 00 00 
	{	
		hrtimer_cancel(&pB->timer);
		pB->timer.function = __fsm_tm_expire;
		hrtimer_start(&pB->timer, pB->evQ->expire, HRTIMER_MODE_ABS);
	}
}
     5d2:	c9                   	leave  
     5d3:	c3                   	ret    
     5d4:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
     5da:	8d bf 00 00 00 00    	lea    0x0(%edi),%edi

000005e0 <fsm_printf>:
}


/* Print */
size_t fsm_printf(const char* fmt,...)
{
     5e0:	55                   	push   %ebp
     5e1:	89 e5                	mov    %esp,%ebp
     5e3:	83 ec 08             	sub    $0x8,%esp
     5e6:	e8 fc ff ff ff       	call   5e7 <fsm_printf+0x7>
	return FSM_MEM_CMP(dst_ptr,src_ptr,size);
}


/* Print */
size_t fsm_printf(const char* fmt,...)
     5eb:	8d 45 0c             	lea    0xc(%ebp),%eax
{
	//return;
	int print_len;
	va_list args;
	va_start(args,fmt);
	print_len = VPRINTK(fmt,args);
     5ee:	89 44 24 04          	mov    %eax,0x4(%esp)
     5f2:	8b 45 08             	mov    0x8(%ebp),%eax
     5f5:	89 04 24             	mov    %eax,(%esp)
     5f8:	e8 fc ff ff ff       	call   5f9 <fsm_printf+0x19>
	va_end(args);
	return print_len;
}
     5fd:	c9                   	leave  
     5fe:	c3                   	ret    
     5ff:	90                   	nop

00000600 <fsm_octets_print>:

size_t fsm_octets_print(void* data_ptr, size_t num)
{
     600:	55                   	push   %ebp
     601:	89 e5                	mov    %esp,%ebp
     603:	57                   	push   %edi
     604:	56                   	push   %esi
     605:	53                   	push   %ebx
     606:	83 ec 08             	sub    $0x8,%esp
     609:	e8 fc ff ff ff       	call   60a <fsm_octets_print+0xa>
     60e:	89 d7                	mov    %edx,%edi
     610:	89 c3                	mov    %eax,%ebx
	u8* ptr;
	int i;
	ptr =(u8*)data_ptr;
	fsm_printf("=====================================================\n");
     612:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     619:	e8 fc ff ff ff       	call   61a <fsm_octets_print+0x1a>
	for(i = 1; i <= num; ++ i)
     61e:	85 ff                	test   %edi,%edi
     620:	0f 84 aa 00 00 00    	je     6d0 <fsm_octets_print+0xd0>
	{
		fsm_printf("%x", (*ptr >> 4));
     626:	0f b6 03             	movzbl (%ebx),%eax
		fsm_printf("%x", (*ptr & 0x0f));
		fsm_printf(" ");
     629:	be 01 00 00 00       	mov    $0x1,%esi
	int i;
	ptr =(u8*)data_ptr;
	fsm_printf("=====================================================\n");
	for(i = 1; i <= num; ++ i)
	{
		fsm_printf("%x", (*ptr >> 4));
     62e:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     635:	c0 e8 04             	shr    $0x4,%al
     638:	0f b6 c0             	movzbl %al,%eax
     63b:	89 44 24 04          	mov    %eax,0x4(%esp)
     63f:	e8 fc ff ff ff       	call   640 <fsm_octets_print+0x40>
		fsm_printf("%x", (*ptr & 0x0f));
     644:	0f b6 03             	movzbl (%ebx),%eax
     647:	83 e0 0f             	and    $0xf,%eax
     64a:	89 44 24 04          	mov    %eax,0x4(%esp)
     64e:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     655:	e8 fc ff ff ff       	call   656 <fsm_octets_print+0x56>
		fsm_printf(" ");
     65a:	c7 04 24 03 00 00 00 	movl   $0x3,(%esp)
     661:	e8 fc ff ff ff       	call   662 <fsm_octets_print+0x62>
     666:	66 90                	xchg   %ax,%ax
{
	u8* ptr;
	int i;
	ptr =(u8*)data_ptr;
	fsm_printf("=====================================================\n");
	for(i = 1; i <= num; ++ i)
     668:	83 c6 01             	add    $0x1,%esi
     66b:	39 f7                	cmp    %esi,%edi
     66d:	72 61                	jb     6d0 <fsm_octets_print+0xd0>
	{
		fsm_printf("%x", (*ptr >> 4));
     66f:	0f b6 44 33 ff       	movzbl -0x1(%ebx,%esi,1),%eax
     674:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     67b:	c0 e8 04             	shr    $0x4,%al
     67e:	0f b6 c0             	movzbl %al,%eax
     681:	89 44 24 04          	mov    %eax,0x4(%esp)
     685:	e8 fc ff ff ff       	call   686 <fsm_octets_print+0x86>
		fsm_printf("%x", (*ptr & 0x0f));
     68a:	0f b6 44 33 ff       	movzbl -0x1(%ebx,%esi,1),%eax
     68f:	83 e0 0f             	and    $0xf,%eax
     692:	89 44 24 04          	mov    %eax,0x4(%esp)
     696:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     69d:	e8 fc ff ff ff       	call   69e <fsm_octets_print+0x9e>
		fsm_printf(" ");
     6a2:	c7 04 24 03 00 00 00 	movl   $0x3,(%esp)
     6a9:	e8 fc ff ff ff       	call   6aa <fsm_octets_print+0xaa>
		++ ptr;
		if(i >= 16 && (i % 16 == 0))
     6ae:	83 fe 0f             	cmp    $0xf,%esi
     6b1:	7e b5                	jle    668 <fsm_octets_print+0x68>
     6b3:	f7 c6 0f 00 00 00    	test   $0xf,%esi
     6b9:	75 ad                	jne    668 <fsm_octets_print+0x68>
{
	u8* ptr;
	int i;
	ptr =(u8*)data_ptr;
	fsm_printf("=====================================================\n");
	for(i = 1; i <= num; ++ i)
     6bb:	83 c6 01             	add    $0x1,%esi
		fsm_printf("%x", (*ptr & 0x0f));
		fsm_printf(" ");
		++ ptr;
		if(i >= 16 && (i % 16 == 0))
		{
			fsm_printf("\n");
     6be:	c7 04 24 05 00 00 00 	movl   $0x5,(%esp)
     6c5:	e8 fc ff ff ff       	call   6c6 <fsm_octets_print+0xc6>
{
	u8* ptr;
	int i;
	ptr =(u8*)data_ptr;
	fsm_printf("=====================================================\n");
	for(i = 1; i <= num; ++ i)
     6ca:	39 f7                	cmp    %esi,%edi
     6cc:	73 a1                	jae    66f <fsm_octets_print+0x6f>
     6ce:	66 90                	xchg   %ax,%ax
		if(i >= 16 && (i % 16 == 0))
		{
			fsm_printf("\n");
		}
	}
	fsm_printf("\n");
     6d0:	c7 04 24 05 00 00 00 	movl   $0x5,(%esp)
     6d7:	e8 fc ff ff ff       	call   6d8 <fsm_octets_print+0xd8>
	fsm_printf("=====================================================\n");
     6dc:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     6e3:	e8 fc ff ff ff       	call   6e4 <fsm_octets_print+0xe4>
	return num;
}
     6e8:	89 f8                	mov    %edi,%eax
     6ea:	83 c4 08             	add    $0x8,%esp
     6ed:	5b                   	pop    %ebx
     6ee:	5e                   	pop    %esi
     6ef:	5f                   	pop    %edi
     6f0:	5d                   	pop    %ebp
     6f1:	c3                   	ret    
     6f2:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     6f9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00000700 <fsm_mem_cmp>:
{
	return FSM_MEM_SET(dst_ptr,val,size);
}

int fsm_mem_cmp(const void* dst_ptr, const void* src_ptr, size_t size)
{
     700:	55                   	push   %ebp
     701:	89 e5                	mov    %esp,%ebp
     703:	83 ec 08             	sub    $0x8,%esp
     706:	89 34 24             	mov    %esi,(%esp)
     709:	89 7c 24 04          	mov    %edi,0x4(%esp)
     70d:	e8 fc ff ff ff       	call   70e <fsm_mem_cmp+0xe>
     712:	89 c6                	mov    %eax,%esi
     714:	89 d7                	mov    %edx,%edi
	return FSM_MEM_CMP(dst_ptr,src_ptr,size);
     716:	39 c9                	cmp    %ecx,%ecx
     718:	f3 a6                	repz cmpsb %es:(%edi),%ds:(%esi)
}
     71a:	8b 34 24             	mov    (%esp),%esi
     71d:	8b 7c 24 04          	mov    0x4(%esp),%edi
	return FSM_MEM_SET(dst_ptr,val,size);
}

int fsm_mem_cmp(const void* dst_ptr, const void* src_ptr, size_t size)
{
	return FSM_MEM_CMP(dst_ptr,src_ptr,size);
     721:	0f 97 c0             	seta   %al
     724:	0f 92 c2             	setb   %dl
     727:	28 d0                	sub    %dl,%al
}
     729:	89 ec                	mov    %ebp,%esp
	return FSM_MEM_SET(dst_ptr,val,size);
}

int fsm_mem_cmp(const void* dst_ptr, const void* src_ptr, size_t size)
{
	return FSM_MEM_CMP(dst_ptr,src_ptr,size);
     72b:	0f be c0             	movsbl %al,%eax
}
     72e:	5d                   	pop    %ebp
     72f:	c3                   	ret    

00000730 <fsm_mem_free>:
	ptr = FSM_MEM_ALLOC(size);
	return ptr;
}

void fsm_mem_free(void* ptr)
{
     730:	55                   	push   %ebp
     731:	89 e5                	mov    %esp,%ebp
     733:	e8 fc ff ff ff       	call   734 <fsm_mem_free+0x4>
	FSM_MEM_FREE(ptr);
     738:	e8 fc ff ff ff       	call   739 <fsm_mem_free+0x9>
}
     73d:	5d                   	pop    %ebp
     73e:	c3                   	ret    
     73f:	90                   	nop

00000740 <fsm_unregister_destroy>:
	}
	return -1;
}

void fsm_unregister_destroy(int id)
{
     740:	55                   	push   %ebp
     741:	89 e5                	mov    %esp,%ebp
     743:	53                   	push   %ebx
     744:	e8 fc ff ff ff       	call   745 <fsm_unregister_destroy+0x5>
	if(FSM[id]!=NULL)
     749:	8d 58 3c             	lea    0x3c(%eax),%ebx
     74c:	8b 04 9d 00 00 00 00 	mov    0x0(,%ebx,4),%eax
     753:	85 c0                	test   %eax,%eax
     755:	74 10                	je     767 <fsm_unregister_destroy+0x27>
	return ptr;
}

void fsm_mem_free(void* ptr)
{
	FSM_MEM_FREE(ptr);
     757:	e8 fc ff ff ff       	call   758 <fsm_unregister_destroy+0x18>
void fsm_unregister_destroy(int id)
{
	if(FSM[id]!=NULL)
	{
		fsm_mem_free(FSM[id]);
		FSM[id] = NULL;
     75c:	c7 04 9d 00 00 00 00 	movl   $0x0,0x0(,%ebx,4)
     763:	00 00 00 00 
	}
}
     767:	5b                   	pop    %ebx
     768:	5d                   	pop    %ebp
     769:	c3                   	ret    
     76a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00000770 <__fsm_do_ioctl>:
	}
}


static void __fsm_do_ioctl(unsigned long data)
{
     770:	55                   	push   %ebp
     771:	89 e5                	mov    %esp,%ebp
     773:	57                   	push   %edi
     774:	56                   	push   %esi
     775:	53                   	push   %ebx
     776:	e8 fc ff ff ff       	call   777 <__fsm_do_ioctl+0x7>
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
     77b:	8b 15 34 01 00 00    	mov    0x134,%edx
	struct evioctl* ev_ptr;
	while(!list_empty(&fsm_core.do_ioctl_list))
     781:	81 fa 34 01 00 00    	cmp    $0x134,%edx
     787:	74 5e                	je     7e7 <__fsm_do_ioctl+0x77>
     789:	bf 3c 01 00 00       	mov    $0x13c,%edi
     78e:	66 90                	xchg   %ax,%ax
	{
		ev_ptr = list_first_entry(&fsm_core.do_ioctl_list, struct evioctl, list_node);
		ev_ptr->dev->netdev_ops->ndo_do_ioctl(ev_ptr->dev, (struct ifreq*)&ev_ptr->ifr, IOCKERNEL);
     790:	8b 42 f0             	mov    -0x10(%edx),%eax
static void __fsm_do_ioctl(unsigned long data)
{
	struct evioctl* ev_ptr;
	while(!list_empty(&fsm_core.do_ioctl_list))
	{
		ev_ptr = list_first_entry(&fsm_core.do_ioctl_list, struct evioctl, list_node);
     793:	8d 5a f0             	lea    -0x10(%edx),%ebx
		ev_ptr->dev->netdev_ops->ndo_do_ioctl(ev_ptr->dev, (struct ifreq*)&ev_ptr->ifr, IOCKERNEL);
     796:	b9 f0 89 00 00       	mov    $0x89f0,%ecx
     79b:	83 ea 0c             	sub    $0xc,%edx
     79e:	8b b0 b4 00 00 00    	mov    0xb4(%eax),%esi
     7a4:	ff 56 2c             	call   *0x2c(%esi)
		spin_lock(&fsm_core.ioctl_list_lock);
     7a7:	b8 3c 01 00 00       	mov    $0x13c,%eax
     7ac:	e8 fc ff ff ff       	call   7ad <__fsm_do_ioctl+0x3d>
 * in an undefined state.
 */
#ifndef CONFIG_DEBUG_LIST
static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
     7b1:	8b 43 14             	mov    0x14(%ebx),%eax
     7b4:	8b 53 10             	mov    0x10(%ebx),%edx
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
     7b7:	89 42 04             	mov    %eax,0x4(%edx)
	prev->next = next;
     7ba:	89 10                	mov    %edx,(%eax)
     7bc:	89 f8                	mov    %edi,%eax
 */
#ifndef CONFIG_DEBUG_LIST
static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON1;
     7be:	c7 43 10 00 01 10 00 	movl   $0x100100,0x10(%ebx)
	entry->prev = LIST_POISON2;
     7c5:	c7 43 14 00 02 20 00 	movl   $0x200200,0x14(%ebx)
     7cc:	ff 15 14 00 00 00    	call   *0x14
	return ptr;
}

void fsm_mem_free(void* ptr)
{
	FSM_MEM_FREE(ptr);
     7d2:	89 d8                	mov    %ebx,%eax
     7d4:	e8 fc ff ff ff       	call   7d5 <__fsm_do_ioctl+0x65>
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
     7d9:	8b 15 34 01 00 00    	mov    0x134,%edx


static void __fsm_do_ioctl(unsigned long data)
{
	struct evioctl* ev_ptr;
	while(!list_empty(&fsm_core.do_ioctl_list))
     7df:	81 fa 34 01 00 00    	cmp    $0x134,%edx
     7e5:	75 a9                	jne    790 <__fsm_do_ioctl+0x20>
		list_del(&ev_ptr->list_node);
		spin_unlock(&fsm_core.ioctl_list_lock);
		//fsm_mem_free(ev_ptr->ifr.buffer);
		fsm_mem_free(ev_ptr);
	}
}
     7e7:	5b                   	pop    %ebx
     7e8:	5e                   	pop    %esi
     7e9:	5f                   	pop    %edi
     7ea:	5d                   	pop    %ebp
     7eb:	c3                   	ret    
     7ec:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

000007f0 <fsm_schedule_cancel>:
	fsm_mem_cpy(buffer, msg_ptr, size);
	return	__fsm_tm_ev_add(0, FSM_EV_TYPE_MSG, code, NULL, fsm_core.current_fsm, dst_id, buffer);
}

int fsm_schedule_cancel(evHandle eh)
{
     7f0:	55                   	push   %ebp
     7f1:	89 e5                	mov    %esp,%ebp
     7f3:	83 ec 04             	sub    $0x4,%esp
     7f6:	e8 fc ff ff ff       	call   7f7 <fsm_schedule_cancel+0x7>
static int __fsm_tm_ev_rmv(__tmEvent* pE)
{
	__tmEvent* p0;
	__tmBlock* pB;
	pB = TMBLOCK_PTR;
	if(pE->evmask != EVMASK)
     7fb:	81 78 04 d6 96 0f 04 	cmpl   $0x40f96d6,0x4(%eax)
     802:	74 0c                	je     810 <fsm_schedule_cancel+0x20>
			__fsm_tm_stop();
		}
		return FSM_EXEC_SUCC;
	}
	p0= pB->evQ;
	while(p0->pNext && (EVHANDLE(pE) != EVHANDLE(p0->pNext)))
     804:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
}

int fsm_schedule_cancel(evHandle eh)
{
	return __fsm_tm_ev_rmv((__tmEvent*)eh);
}
     809:	c9                   	leave  
     80a:	c3                   	ret    
     80b:	90                   	nop
     80c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
	__tmEvent* p0;
	__tmBlock* pB;
	pB = TMBLOCK_PTR;
	if(pE->evmask != EVMASK)
		return FSM_EXEC_FAIL;
	if(!pB->evQ)
     810:	8b 0d e8 00 00 00    	mov    0xe8,%ecx
     816:	85 c9                	test   %ecx,%ecx
     818:	74 ea                	je     804 <fsm_schedule_cancel+0x14>
		return FSM_EXEC_FAIL;

	if(EVHANDLE(pE) == EVHANDLE(pB->evQ))
     81a:	39 c8                	cmp    %ecx,%eax
     81c:	75 34                	jne    852 <fsm_schedule_cancel+0x62>
	{
		pB->evQ = pB->evQ->pNext;
     81e:	8b 10                	mov    (%eax),%edx
		if(pB->tm_state != FSM_TM_EXPIRE)
     820:	83 3d a4 00 00 00 02 	cmpl   $0x2,0xa4
	if(!pB->evQ)
		return FSM_EXEC_FAIL;

	if(EVHANDLE(pE) == EVHANDLE(pB->evQ))
	{
		pB->evQ = pB->evQ->pNext;
     827:	89 15 e8 00 00 00    	mov    %edx,0xe8
		if(pB->tm_state != FSM_TM_EXPIRE)
     82d:	74 0b                	je     83a <fsm_schedule_cancel+0x4a>
		{
			//fsm_printf("[FSMCORE]THE FIRST EVEN START!\n");

			__fsm_tm_restart();
     82f:	89 45 fc             	mov    %eax,-0x4(%ebp)
     832:	e8 f9 fc ff ff       	call   530 <__fsm_tm_restart>
     837:	8b 45 fc             	mov    -0x4(%ebp),%eax
	return ptr;
}

void fsm_mem_free(void* ptr)
{
	FSM_MEM_FREE(ptr);
     83a:	e8 fc ff ff ff       	call   83b <fsm_schedule_cancel+0x4b>
			//fsm_printf("[FSMCORE]THE FIRST EVEN START!\n");

			__fsm_tm_restart();
		}
		fsm_mem_free(pE);
		if(!pB->evQ && pB->tm_state != FSM_TM_EXPIRE)
     83f:	8b 15 e8 00 00 00    	mov    0xe8,%edx
     845:	85 d2                	test   %edx,%edx
     847:	74 20                	je     869 <fsm_schedule_cancel+0x79>
			__fsm_tm_stop();
		}
		return FSM_EXEC_SUCC;
	}
	p0= pB->evQ;
	while(p0->pNext && (EVHANDLE(pE) != EVHANDLE(p0->pNext)))
     849:	31 c0                	xor    %eax,%eax
}

int fsm_schedule_cancel(evHandle eh)
{
	return __fsm_tm_ev_rmv((__tmEvent*)eh);
}
     84b:	c9                   	leave  
     84c:	c3                   	ret    
     84d:	8d 76 00             	lea    0x0(%esi),%esi
}
static void __fsm_tm_stop()
{
	__tmBlock* pB;
	pB = TMBLOCK_PTR;
	pB->tm_state = FSM_TM_STOP;
     850:	89 d1                	mov    %edx,%ecx
			__fsm_tm_stop();
		}
		return FSM_EXEC_SUCC;
	}
	p0= pB->evQ;
	while(p0->pNext && (EVHANDLE(pE) != EVHANDLE(p0->pNext)))
     852:	8b 11                	mov    (%ecx),%edx
     854:	85 d2                	test   %edx,%edx
     856:	74 ac                	je     804 <fsm_schedule_cancel+0x14>
     858:	39 d0                	cmp    %edx,%eax
     85a:	75 f4                	jne    850 <fsm_schedule_cancel+0x60>
	if(p0->pNext)
	{
		//fsm_printf("[FSMCORE]NEXT EVEN START!\n");


		p0->pNext = pE->pNext;
     85c:	8b 10                	mov    (%eax),%edx
     85e:	89 11                	mov    %edx,(%ecx)
	return ptr;
}

void fsm_mem_free(void* ptr)
{
	FSM_MEM_FREE(ptr);
     860:	e8 fc ff ff ff       	call   861 <fsm_schedule_cancel+0x71>
     865:	31 c0                	xor    %eax,%eax
}

int fsm_schedule_cancel(evHandle eh)
{
	return __fsm_tm_ev_rmv((__tmEvent*)eh);
}
     867:	c9                   	leave  
     868:	c3                   	ret    
			//fsm_printf("[FSMCORE]THE FIRST EVEN START!\n");

			__fsm_tm_restart();
		}
		fsm_mem_free(pE);
		if(!pB->evQ && pB->tm_state != FSM_TM_EXPIRE)
     869:	83 3d a4 00 00 00 02 	cmpl   $0x2,0xa4
     870:	74 d7                	je     849 <fsm_schedule_cancel+0x59>
}
static void __fsm_tm_stop()
{
	__tmBlock* pB;
	pB = TMBLOCK_PTR;
	pB->tm_state = FSM_TM_STOP;
     872:	c7 05 a4 00 00 00 00 	movl   $0x0,0xa4
     879:	00 00 00 
     87c:	31 c0                	xor    %eax,%eax
}

int fsm_schedule_cancel(evHandle eh)
{
	return __fsm_tm_ev_rmv((__tmEvent*)eh);
}
     87e:	c9                   	leave  
     87f:	c3                   	ret    

00000880 <fsm_data_destroy>:
	fsm_core.buffer = NULL;
	return buffer;
}

void fsm_data_destroy(void* data_ptr)
{
     880:	55                   	push   %ebp
     881:	89 e5                	mov    %esp,%ebp
     883:	e8 fc ff ff ff       	call   884 <fsm_data_destroy+0x4>
	return ptr;
}

void fsm_mem_free(void* ptr)
{
	FSM_MEM_FREE(ptr);
     888:	e8 fc ff ff ff       	call   889 <fsm_data_destroy+0x9>
}

void fsm_data_destroy(void* data_ptr)
{
	fsm_mem_free(data_ptr);
}
     88d:	5d                   	pop    %ebp
     88e:	c3                   	ret    
     88f:	90                   	nop

00000890 <fsm_skb_pull>:
{
	return SKB_PUSH(pkptr, len);
}

u8* fsm_skb_pull(FSM_PKT* pkptr, int len)
{
     890:	55                   	push   %ebp
     891:	89 e5                	mov    %esp,%ebp
     893:	e8 fc ff ff ff       	call   894 <fsm_skb_pull+0x4>
	return SKB_PULL(pkptr, len);
     898:	e8 fc ff ff ff       	call   899 <fsm_skb_pull+0x9>
}
     89d:	5d                   	pop    %ebp
     89e:	c3                   	ret    
     89f:	90                   	nop

000008a0 <fsm_skb_push>:
{	
	return (u8*)SKB_PUT(pkptr, len);
}

u8* fsm_skb_push(FSM_PKT* pkptr, int len)
{
     8a0:	55                   	push   %ebp
     8a1:	89 e5                	mov    %esp,%ebp
     8a3:	e8 fc ff ff ff       	call   8a4 <fsm_skb_push+0x4>
	return SKB_PUSH(pkptr, len);
     8a8:	e8 fc ff ff ff       	call   8a9 <fsm_skb_push+0x9>
}
     8ad:	5d                   	pop    %ebp
     8ae:	c3                   	ret    
     8af:	90                   	nop

000008b0 <fsm_skb_put>:
{
	return SKB_COPY(pkptr, GFP_ATOMIC);
}

u8* fsm_skb_put(FSM_PKT* pkptr, int len)
{	
     8b0:	55                   	push   %ebp
     8b1:	89 e5                	mov    %esp,%ebp
     8b3:	e8 fc ff ff ff       	call   8b4 <fsm_skb_put+0x4>
	return (u8*)SKB_PUT(pkptr, len);
     8b8:	e8 fc ff ff ff       	call   8b9 <fsm_skb_put+0x9>
}
     8bd:	5d                   	pop    %ebp
     8be:	c3                   	ret    
     8bf:	90                   	nop

000008c0 <fsm_pkt_duplicate>:
{
	KFREE_SKB(pkptr);
}

FSM_PKT* fsm_pkt_duplicate(FSM_PKT* pkptr)
{
     8c0:	55                   	push   %ebp
     8c1:	89 e5                	mov    %esp,%ebp
     8c3:	e8 fc ff ff ff       	call   8c4 <fsm_pkt_duplicate+0x4>
	return SKB_COPY(pkptr, GFP_ATOMIC);
     8c8:	ba 20 00 00 00       	mov    $0x20,%edx
     8cd:	e8 fc ff ff ff       	call   8ce <fsm_pkt_duplicate+0xe>
}
     8d2:	5d                   	pop    %ebp
     8d3:	c3                   	ret    
     8d4:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
     8da:	8d bf 00 00 00 00    	lea    0x0(%edi),%edi

000008e0 <fsm_pkt_destroy>:
	KFREE_SKB(pkptr);
	return pkptr_new;
}

void fsm_pkt_destroy(FSM_PKT* pkptr)
{
     8e0:	55                   	push   %ebp
     8e1:	89 e5                	mov    %esp,%ebp
     8e3:	e8 fc ff ff ff       	call   8e4 <fsm_pkt_destroy+0x4>
	KFREE_SKB(pkptr);
     8e8:	e8 fc ff ff ff       	call   8e9 <fsm_pkt_destroy+0x9>
}
     8ed:	5d                   	pop    %ebp
     8ee:	c3                   	ret    
     8ef:	90                   	nop

000008f0 <__fsm_core_self_drive>:
	//	fsm_printf("__fsm_skb_xmit() packet send\n");
	return;
}

static void __fsm_core_self_drive(u32 evtype, u32 code, FSM_PKT* pkptr, int src_id, int dst_id, void* buffer, u32 ioctrl_cmd)		
{
     8f0:	55                   	push   %ebp
     8f1:	89 e5                	mov    %esp,%ebp
     8f3:	56                   	push   %esi
     8f4:	53                   	push   %ebx
     8f5:	e8 fc ff ff ff       	call   8f6 <__fsm_core_self_drive+0x6>
     8fa:	8b 5d 0c             	mov    0xc(%ebp),%ebx
	fsm_core.current_fsm = dst_id;
     8fd:	89 1d 00 00 00 00    	mov    %ebx,0x0
	fsm_core.current_state_ptr = &FSM[dst_id]->_fsm_current_block;
     903:	83 c3 3c             	add    $0x3c,%ebx
     906:	8b 34 9d 00 00 00 00 	mov    0x0(,%ebx,4),%esi
	fsm_core.evtype = evtype;
     90d:	a3 10 00 00 00       	mov    %eax,0x10
	fsm_core.code = code;
	fsm_core.pkptr = pkptr;
	fsm_core.src = src_id;
     912:	8b 45 08             	mov    0x8(%ebp),%eax
static void __fsm_core_self_drive(u32 evtype, u32 code, FSM_PKT* pkptr, int src_id, int dst_id, void* buffer, u32 ioctrl_cmd)		
{
	fsm_core.current_fsm = dst_id;
	fsm_core.current_state_ptr = &FSM[dst_id]->_fsm_current_block;
	fsm_core.evtype = evtype;
	fsm_core.code = code;
     915:	89 15 14 00 00 00    	mov    %edx,0x14
	fsm_core.pkptr = pkptr;
     91b:	89 0d 0c 00 00 00    	mov    %ecx,0xc
}

static void __fsm_core_self_drive(u32 evtype, u32 code, FSM_PKT* pkptr, int src_id, int dst_id, void* buffer, u32 ioctrl_cmd)		
{
	fsm_core.current_fsm = dst_id;
	fsm_core.current_state_ptr = &FSM[dst_id]->_fsm_current_block;
     921:	81 c6 8c 00 00 00    	add    $0x8c,%esi
     927:	89 35 04 00 00 00    	mov    %esi,0x4
	fsm_core.evtype = evtype;
	fsm_core.code = code;
	fsm_core.pkptr = pkptr;
	fsm_core.src = src_id;
     92d:	a3 18 00 00 00       	mov    %eax,0x18
	FSM_SV_PTR = FSM[dst_id]->fsm_sv_ptr;
     932:	8b 04 9d 00 00 00 00 	mov    0x0(,%ebx,4),%eax
     939:	8b 80 88 00 00 00    	mov    0x88(%eax),%eax
     93f:	a3 1c 00 00 00       	mov    %eax,0x1c
	fsm_core.buffer = buffer;
     944:	8b 45 10             	mov    0x10(%ebp),%eax
     947:	a3 0c 01 00 00       	mov    %eax,0x10c
	fsm_core.ioctrl_cmd = ioctrl_cmd;
     94c:	8b 45 14             	mov    0x14(%ebp),%eax
     94f:	a3 10 01 00 00       	mov    %eax,0x110
	fsm_core.fsm_drive = FSM[dst_id]->fsm_main;
     954:	8b 04 9d 00 00 00 00 	mov    0x0(,%ebx,4),%eax
     95b:	8b 80 84 00 00 00    	mov    0x84(%eax),%eax
     961:	a3 20 00 00 00       	mov    %eax,0x20

	//fsm_printf("[]BEFORE DRIVE!\n");

	fsm_core.fsm_drive();
     966:	ff d0                	call   *%eax

/* ------------------internal functions-------------------------------*/
static void __fsm_ev_flush()
{

	if(fsm_core.pkptr)
     968:	a1 0c 00 00 00       	mov    0xc,%eax
     96d:	85 c0                	test   %eax,%eax
     96f:	74 05                	je     976 <__fsm_core_self_drive+0x86>
	return pkptr_new;
}

void fsm_pkt_destroy(FSM_PKT* pkptr)
{
	KFREE_SKB(pkptr);
     971:	e8 fc ff ff ff       	call   972 <__fsm_core_self_drive+0x82>
	}
	//	if(fsm_core.buffer && !(fsm_ev_type()==FSM_EV_TYPE_CORE && fsm_ev_code()==FSM_EV_IOCTRL && fsm_ev_src()==USER_SPACE))
	//		{
	//		fsm_mem_free(fsm_core.buffer);
	//		}
	if(fsm_core.buffer)
     976:	a1 0c 01 00 00       	mov    0x10c,%eax
     97b:	85 c0                	test   %eax,%eax
     97d:	74 05                	je     984 <__fsm_core_self_drive+0x94>
	return ptr;
}

void fsm_mem_free(void* ptr)
{
	FSM_MEM_FREE(ptr);
     97f:	e8 fc ff ff ff       	call   980 <__fsm_core_self_drive+0x90>

	__fsm_ev_flush();

	//fsm_printf("[]AFTER FLUSH!\n");

}
     984:	5b                   	pop    %ebx
	//		}
	if(fsm_core.buffer)
	{
		fsm_data_destroy(fsm_core.buffer);
	}
	fsm_core.current_fsm = -1;
     985:	c7 05 00 00 00 00 ff 	movl   $0xffffffff,0x0
     98c:	ff ff ff 

	__fsm_ev_flush();

	//fsm_printf("[]AFTER FLUSH!\n");

}
     98f:	5e                   	pop    %esi
	if(fsm_core.buffer)
	{
		fsm_data_destroy(fsm_core.buffer);
	}
	fsm_core.current_fsm = -1;
	fsm_core.current_state_ptr = NULL;
     990:	c7 05 04 00 00 00 00 	movl   $0x0,0x4
     997:	00 00 00 
	fsm_core.pkptr = NULL;
     99a:	c7 05 0c 00 00 00 00 	movl   $0x0,0xc
     9a1:	00 00 00 
	fsm_core.evtype = INVALIDE;
     9a4:	c7 05 10 00 00 00 00 	movl   $0x0,0x10
     9ab:	00 00 00 
	fsm_core.code = INVALIDE;
     9ae:	c7 05 14 00 00 00 00 	movl   $0x0,0x14
     9b5:	00 00 00 
	fsm_core.src = INVALIDE;
     9b8:	c7 05 18 00 00 00 00 	movl   $0x0,0x18
     9bf:	00 00 00 
	FSM_SV_PTR = NULL;
     9c2:	c7 05 1c 00 00 00 00 	movl   $0x0,0x1c
     9c9:	00 00 00 
	fsm_core.fsm_drive = NULL;
     9cc:	c7 05 20 00 00 00 00 	movl   $0x0,0x20
     9d3:	00 00 00 
	fsm_core.buffer = NULL;
     9d6:	c7 05 0c 01 00 00 00 	movl   $0x0,0x10c
     9dd:	00 00 00 
	fsm_core.ioctrl_cmd = INVALIDE;
     9e0:	c7 05 10 01 00 00 00 	movl   $0x0,0x110
     9e7:	00 00 00 

	__fsm_ev_flush();

	//fsm_printf("[]AFTER FLUSH!\n");

}
     9ea:	5d                   	pop    %ebp
     9eb:	c3                   	ret    
     9ec:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

000009f0 <fsm_core_pkt_drive>:
}



int fsm_core_pkt_drive(FSM_PKT* pkptr, u32 type)
{ 
     9f0:	55                   	push   %ebp
     9f1:	89 e5                	mov    %esp,%ebp
     9f3:	53                   	push   %ebx
     9f4:	83 ec 10             	sub    $0x10,%esp
     9f7:	e8 fc ff ff ff       	call   9f8 <fsm_core_pkt_drive+0x8>
	if(type == RXTX_PKT_IND)
     9fc:	83 fa 01             	cmp    $0x1,%edx
}



int fsm_core_pkt_drive(FSM_PKT* pkptr, u32 type)
{ 
     9ff:	89 c3                	mov    %eax,%ebx
	if(type == RXTX_PKT_IND)
     a01:	74 5d                	je     a60 <fsm_core_pkt_drive+0x70>
	{
		spin_lock_bh(&fsm_core.lock);
		__fsm_core_self_drive(FSM_EV_TYPE_PKT_IND,INVALIDE,pkptr,KERNEL_MODULE,MAIN_PORT,NULL,INVALIDE);
		spin_unlock_bh(&fsm_core.lock);
	}
	if(type == RXTX_PKT_REQ)
     a03:	85 d2                	test   %edx,%edx
     a05:	74 09                	je     a10 <fsm_core_pkt_drive+0x20>
		__fsm_core_self_drive(FSM_EV_TYPE_PKT_REQ,INVALIDE,pkptr,KERNEL_MODULE,MAIN_PORT,NULL,INVALIDE);
		spin_unlock_bh(&fsm_core.lock);

	}
	return FSM_EXEC_SUCC;
}
     a07:	83 c4 10             	add    $0x10,%esp
     a0a:	31 c0                	xor    %eax,%eax
     a0c:	5b                   	pop    %ebx
     a0d:	5d                   	pop    %ebp
     a0e:	c3                   	ret    
     a0f:	90                   	nop
				if(irqs_disabled())
				{
				fsm_printf("irq is disabled!\n");
				}
				fsm_printf("send packet\n");*/
		spin_lock_bh(&fsm_core.lock);
     a10:	b8 14 01 00 00       	mov    $0x114,%eax
     a15:	e8 fc ff ff ff       	call   a16 <fsm_core_pkt_drive+0x26>
		__fsm_core_self_drive(FSM_EV_TYPE_PKT_REQ,INVALIDE,pkptr,KERNEL_MODULE,MAIN_PORT,NULL,INVALIDE);
     a1a:	a1 ec 00 00 00       	mov    0xec,%eax
     a1f:	89 d9                	mov    %ebx,%ecx
     a21:	31 d2                	xor    %edx,%edx
     a23:	89 44 24 04          	mov    %eax,0x4(%esp)
     a27:	b8 01 00 00 00       	mov    $0x1,%eax
     a2c:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
     a33:	00 
     a34:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
     a3b:	00 
     a3c:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     a43:	e8 a8 fe ff ff       	call   8f0 <__fsm_core_self_drive>
		spin_unlock_bh(&fsm_core.lock);
     a48:	b8 14 01 00 00       	mov    $0x114,%eax
     a4d:	e8 fc ff ff ff       	call   a4e <fsm_core_pkt_drive+0x5e>

	}
	return FSM_EXEC_SUCC;
}
     a52:	31 c0                	xor    %eax,%eax
     a54:	83 c4 10             	add    $0x10,%esp
     a57:	5b                   	pop    %ebx
     a58:	5d                   	pop    %ebp
     a59:	c3                   	ret    
     a5a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

int fsm_core_pkt_drive(FSM_PKT* pkptr, u32 type)
{ 
	if(type == RXTX_PKT_IND)
	{
		spin_lock_bh(&fsm_core.lock);
     a60:	b8 14 01 00 00       	mov    $0x114,%eax
     a65:	e8 fc ff ff ff       	call   a66 <fsm_core_pkt_drive+0x76>
		__fsm_core_self_drive(FSM_EV_TYPE_PKT_IND,INVALIDE,pkptr,KERNEL_MODULE,MAIN_PORT,NULL,INVALIDE);
     a6a:	a1 ec 00 00 00       	mov    0xec,%eax
     a6f:	89 d9                	mov    %ebx,%ecx
     a71:	31 d2                	xor    %edx,%edx
     a73:	89 44 24 04          	mov    %eax,0x4(%esp)
     a77:	b8 02 00 00 00       	mov    $0x2,%eax
     a7c:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
     a83:	00 
     a84:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
     a8b:	00 
     a8c:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     a93:	e8 58 fe ff ff       	call   8f0 <__fsm_core_self_drive>
		spin_unlock_bh(&fsm_core.lock);
     a98:	b8 14 01 00 00       	mov    $0x114,%eax
     a9d:	e8 fc ff ff ff       	call   a9e <fsm_core_pkt_drive+0xae>
		__fsm_core_self_drive(FSM_EV_TYPE_PKT_REQ,INVALIDE,pkptr,KERNEL_MODULE,MAIN_PORT,NULL,INVALIDE);
		spin_unlock_bh(&fsm_core.lock);

	}
	return FSM_EXEC_SUCC;
}
     aa2:	31 c0                	xor    %eax,%eax
     aa4:	83 c4 10             	add    $0x10,%esp
     aa7:	5b                   	pop    %ebx
     aa8:	5d                   	pop    %ebp
     aa9:	c3                   	ret    
     aaa:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00000ab0 <fsm_core_open>:
	return;
}


int fsm_core_open()
{
     ab0:	55                   	push   %ebp
     ab1:	89 e5                	mov    %esp,%ebp
     ab3:	83 ec 10             	sub    $0x10,%esp
     ab6:	e8 fc ff ff ff       	call   ab7 <fsm_core_open+0x7>
	if(fsm_core.state == CORE_CLOSED)
     abb:	8b 0d 08 00 00 00    	mov    0x8,%ecx
     ac1:	85 c9                	test   %ecx,%ecx
     ac3:	0f 85 1f 01 00 00    	jne    be8 <fsm_core_open+0x138>
	{
		spin_lock(&fsm_core.lock);
     ac9:	b8 14 01 00 00       	mov    $0x114,%eax
     ace:	e8 fc ff ff ff       	call   acf <fsm_core_open+0x1f>
		fsm_printf("core is opening.\n");
     ad3:	c7 04 24 07 00 00 00 	movl   $0x7,(%esp)
     ada:	e8 fc ff ff ff       	call   adb <fsm_core_open+0x2b>
		//Initialize queues
		skb_queue_head_init(fsm_core.tx_queue);
     adf:	a1 18 01 00 00       	mov    0x118,%eax
		skb_queue_head_init(fsm_core.rx_queue);
		spin_lock_init(&fsm_core.tx_queue_lock);
		spin_lock_init(&fsm_core.rx_queue_lock);
		//Initialize tasklets
		tasklet_init(fsm_core.tx_tsklt, __fsm_skb_xmit, 0);
     ae4:	31 c9                	xor    %ecx,%ecx
     ae6:	ba 10 02 00 00       	mov    $0x210,%edx
 * network layer or drivers should need annotation to consolidate the
 * main types of usage into 3 classes.
 */
static inline void skb_queue_head_init(struct sk_buff_head *list)
{
	spin_lock_init(&list->lock);
     aeb:	c7 40 0c 00 00 00 00 	movl   $0x0,0xc(%eax)
 *	the spinlock.  It can also be used for on-stack sk_buff_head
 *	objects where the spinlock is known to not be used.
 */
static inline void __skb_queue_head_init(struct sk_buff_head *list)
{
	list->prev = list->next = (struct sk_buff *)list;
     af2:	89 00                	mov    %eax,(%eax)
     af4:	89 40 04             	mov    %eax,0x4(%eax)
	list->qlen = 0;
     af7:	c7 40 08 00 00 00 00 	movl   $0x0,0x8(%eax)
	{
		spin_lock(&fsm_core.lock);
		fsm_printf("core is opening.\n");
		//Initialize queues
		skb_queue_head_init(fsm_core.tx_queue);
		skb_queue_head_init(fsm_core.rx_queue);
     afe:	a1 1c 01 00 00       	mov    0x11c,%eax
 * network layer or drivers should need annotation to consolidate the
 * main types of usage into 3 classes.
 */
static inline void skb_queue_head_init(struct sk_buff_head *list)
{
	spin_lock_init(&list->lock);
     b03:	c7 40 0c 00 00 00 00 	movl   $0x0,0xc(%eax)
 *	the spinlock.  It can also be used for on-stack sk_buff_head
 *	objects where the spinlock is known to not be used.
 */
static inline void __skb_queue_head_init(struct sk_buff_head *list)
{
	list->prev = list->next = (struct sk_buff *)list;
     b0a:	89 00                	mov    %eax,(%eax)
     b0c:	89 40 04             	mov    %eax,0x4(%eax)
	list->qlen = 0;
     b0f:	c7 40 08 00 00 00 00 	movl   $0x0,0x8(%eax)
		spin_lock_init(&fsm_core.tx_queue_lock);
		spin_lock_init(&fsm_core.rx_queue_lock);
		//Initialize tasklets
		tasklet_init(fsm_core.tx_tsklt, __fsm_skb_xmit, 0);
     b16:	a1 20 01 00 00       	mov    0x120,%eax
		spin_lock(&fsm_core.lock);
		fsm_printf("core is opening.\n");
		//Initialize queues
		skb_queue_head_init(fsm_core.tx_queue);
		skb_queue_head_init(fsm_core.rx_queue);
		spin_lock_init(&fsm_core.tx_queue_lock);
     b1b:	c7 05 2c 01 00 00 00 	movl   $0x0,0x12c
     b22:	00 00 00 
		spin_lock_init(&fsm_core.rx_queue_lock);
     b25:	c7 05 30 01 00 00 00 	movl   $0x0,0x130
     b2c:	00 00 00 
		//Initialize tasklets
		tasklet_init(fsm_core.tx_tsklt, __fsm_skb_xmit, 0);
     b2f:	e8 fc ff ff ff       	call   b30 <fsm_core_open+0x80>
		tasklet_init(fsm_core.rx_tsklt, __fsm_skb_netrx, 0);
     b34:	a1 24 01 00 00       	mov    0x124,%eax
     b39:	31 c9                	xor    %ecx,%ecx
     b3b:	ba c0 01 00 00       	mov    $0x1c0,%edx
     b40:	e8 fc ff ff ff       	call   b41 <fsm_core_open+0x91>
		spin_lock_init(&fsm_core.ioctl_list_lock);
		INIT_LIST_HEAD(&fsm_core.do_ioctl_list);
		tasklet_init(fsm_core.do_ioctl_tsklt, __fsm_do_ioctl, 0);
     b45:	a1 28 01 00 00       	mov    0x128,%eax
     b4a:	31 c9                	xor    %ecx,%ecx
     b4c:	ba 70 07 00 00       	mov    $0x770,%edx
		spin_lock_init(&fsm_core.tx_queue_lock);
		spin_lock_init(&fsm_core.rx_queue_lock);
		//Initialize tasklets
		tasklet_init(fsm_core.tx_tsklt, __fsm_skb_xmit, 0);
		tasklet_init(fsm_core.rx_tsklt, __fsm_skb_netrx, 0);
		spin_lock_init(&fsm_core.ioctl_list_lock);
     b51:	c7 05 3c 01 00 00 00 	movl   $0x0,0x13c
     b58:	00 00 00 
#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
     b5b:	c7 05 34 01 00 00 34 	movl   $0x134,0x134
     b62:	01 00 00 
	list->prev = list;
     b65:	c7 05 38 01 00 00 34 	movl   $0x134,0x138
     b6c:	01 00 00 
		INIT_LIST_HEAD(&fsm_core.do_ioctl_list);
		tasklet_init(fsm_core.do_ioctl_tsklt, __fsm_do_ioctl, 0);
     b6f:	e8 fc ff ff ff       	call   b70 <fsm_core_open+0xc0>
{
	__tmBlock* pB;
	pB = TMBLOCK_PTR;
	pB->tm_state = FSM_TM_STOP;
	pB->evQ = 0;
	hrtimer_init(&pB->timer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS); 
     b74:	31 c9                	xor    %ecx,%ecx
     b76:	ba 01 00 00 00       	mov    $0x1,%edx
     b7b:	b8 a8 00 00 00       	mov    $0xa8,%eax

static void __fsm_tm_init()
{
	__tmBlock* pB;
	pB = TMBLOCK_PTR;
	pB->tm_state = FSM_TM_STOP;
     b80:	c7 05 a4 00 00 00 00 	movl   $0x0,0xa4
     b87:	00 00 00 
	pB->evQ = 0;
     b8a:	c7 05 e8 00 00 00 00 	movl   $0x0,0xe8
     b91:	00 00 00 
	hrtimer_init(&pB->timer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS); 
     b94:	e8 fc ff ff ff       	call   b95 <fsm_core_open+0xe5>
		spin_lock_init(&fsm_core.ioctl_list_lock);
		INIT_LIST_HEAD(&fsm_core.do_ioctl_list);
		tasklet_init(fsm_core.do_ioctl_tsklt, __fsm_do_ioctl, 0);
		__fsm_tm_init();
		fsm_core.state = CORE_OPENED;
		__fsm_core_self_drive(FSM_EV_TYPE_CORE,FSM_EV_CORE_OPEN,NULL,KERNEL_MODULE,MAIN_PORT,NULL,INVALIDE);
     b99:	a1 ec 00 00 00       	mov    0xec,%eax
     b9e:	31 c9                	xor    %ecx,%ecx
     ba0:	31 d2                	xor    %edx,%edx
		tasklet_init(fsm_core.rx_tsklt, __fsm_skb_netrx, 0);
		spin_lock_init(&fsm_core.ioctl_list_lock);
		INIT_LIST_HEAD(&fsm_core.do_ioctl_list);
		tasklet_init(fsm_core.do_ioctl_tsklt, __fsm_do_ioctl, 0);
		__fsm_tm_init();
		fsm_core.state = CORE_OPENED;
     ba2:	c7 05 08 00 00 00 01 	movl   $0x1,0x8
     ba9:	00 00 00 
		__fsm_core_self_drive(FSM_EV_TYPE_CORE,FSM_EV_CORE_OPEN,NULL,KERNEL_MODULE,MAIN_PORT,NULL,INVALIDE);
     bac:	89 44 24 04          	mov    %eax,0x4(%esp)
     bb0:	b8 05 00 00 00       	mov    $0x5,%eax
     bb5:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
     bbc:	00 
     bbd:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
     bc4:	00 
     bc5:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     bcc:	e8 1f fd ff ff       	call   8f0 <__fsm_core_self_drive>
		fsm_printf("core has opened.\n");
     bd1:	c7 04 24 19 00 00 00 	movl   $0x19,(%esp)
     bd8:	e8 fc ff ff ff       	call   bd9 <fsm_core_open+0x129>
     bdd:	b8 14 01 00 00       	mov    $0x114,%eax
     be2:	ff 15 14 00 00 00    	call   *0x14
		spin_unlock(&fsm_core.lock);
	}
	return FSM_EXEC_SUCC;
}
     be8:	31 c0                	xor    %eax,%eax
     bea:	c9                   	leave  
     beb:	c3                   	ret    
     bec:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00000bf0 <__fsm_tm_expire>:
		fsm_mem_free(pE);
	}
}

static enum hrtimer_restart __fsm_tm_expire(struct hrtimer *timer)
{
     bf0:	55                   	push   %ebp
     bf1:	89 e5                	mov    %esp,%ebp
     bf3:	57                   	push   %edi
     bf4:	56                   	push   %esi
     bf5:	53                   	push   %ebx
     bf6:	83 ec 18             	sub    $0x18,%esp
     bf9:	e8 fc ff ff ff       	call   bfa <__fsm_tm_expire+0xa>
	ktime_t cur_time; 
	__tmEvent* pE;
	__tmBlock* pB;
	//fsm_printf("fsm_tm_expire\n");
	spin_lock(&fsm_core.lock);
     bfe:	b8 14 01 00 00       	mov    $0x114,%eax
     c03:	e8 fc ff ff ff       	call   c04 <__fsm_tm_expire+0x14>
	pB = TMBLOCK_PTR;
	cur_time = ktime_get();
     c08:	e8 fc ff ff ff       	call   c09 <__fsm_tm_expire+0x19>
	pB->tm_state = FSM_TM_EXPIRE;		
	while(pB->evQ && !LATE_TIME(cur_time, pB->evQ->expire))
     c0d:	8b 3d e8 00 00 00    	mov    0xe8,%edi
	__tmBlock* pB;
	//fsm_printf("fsm_tm_expire\n");
	spin_lock(&fsm_core.lock);
	pB = TMBLOCK_PTR;
	cur_time = ktime_get();
	pB->tm_state = FSM_TM_EXPIRE;		
     c13:	c7 05 a4 00 00 00 02 	movl   $0x2,0xa4
     c1a:	00 00 00 
	while(pB->evQ && !LATE_TIME(cur_time, pB->evQ->expire))
     c1d:	85 ff                	test   %edi,%edi
	__tmEvent* pE;
	__tmBlock* pB;
	//fsm_printf("fsm_tm_expire\n");
	spin_lock(&fsm_core.lock);
	pB = TMBLOCK_PTR;
	cur_time = ktime_get();
     c1f:	89 c3                	mov    %eax,%ebx
     c21:	89 d6                	mov    %edx,%esi
	pB->tm_state = FSM_TM_EXPIRE;		
	while(pB->evQ && !LATE_TIME(cur_time, pB->evQ->expire))
     c23:	74 13                	je     c38 <__fsm_tm_expire+0x48>
     c25:	8b 47 08             	mov    0x8(%edi),%eax
     c28:	8b 57 0c             	mov    0xc(%edi),%edx
     c2b:	29 d8                	sub    %ebx,%eax
     c2d:	19 f2                	sbb    %esi,%edx
     c2f:	83 fa 00             	cmp    $0x0,%edx
     c32:	7e 64                	jle    c98 <__fsm_tm_expire+0xa8>
     c34:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
     c38:	b8 14 01 00 00       	mov    $0x114,%eax
     c3d:	ff 15 14 00 00 00    	call   *0x14
		fsm_mem_free(pE);
	}
	//fsm_printf("ready to unlock\n");
	spin_unlock(&fsm_core.lock);
	//	fsm_printf("unlock_bh\n");
	if(pB->evQ)
     c43:	a1 e8 00 00 00       	mov    0xe8,%eax
     c48:	85 c0                	test   %eax,%eax
     c4a:	74 34                	je     c80 <__fsm_tm_expire+0x90>
     c4c:	8b 50 0c             	mov    0xc(%eax),%edx
     c4f:	8b 40 08             	mov    0x8(%eax),%eax
	{	
		hrtimer_set_expires(&pB->timer, pB->evQ->expire);
		pB->tm_state = FSM_TM_RUN;	
     c52:	c7 05 a4 00 00 00 01 	movl   $0x1,0xa4
     c59:	00 00 00 
#endif
};

static inline void hrtimer_set_expires(struct hrtimer *timer, ktime_t time)
{
	timer->_expires = time;
     c5c:	89 15 b8 00 00 00    	mov    %edx,0xb8
     c62:	a3 b4 00 00 00       	mov    %eax,0xb4
	timer->_softexpires = time;
     c67:	a3 bc 00 00 00       	mov    %eax,0xbc
     c6c:	b8 01 00 00 00       	mov    $0x1,%eax
     c71:	89 15 c0 00 00 00    	mov    %edx,0xc0
	{
		pB->tm_state = FSM_TM_STOP;
		return HRTIMER_NORESTART;	
	}

}
     c77:	83 c4 18             	add    $0x18,%esp
     c7a:	5b                   	pop    %ebx
     c7b:	5e                   	pop    %esi
     c7c:	5f                   	pop    %edi
     c7d:	5d                   	pop    %ebp
     c7e:	c3                   	ret    
     c7f:	90                   	nop
		pB->tm_state = FSM_TM_RUN;	
		return HRTIMER_RESTART;
	}
	else
	{
		pB->tm_state = FSM_TM_STOP;
     c80:	c7 05 a4 00 00 00 00 	movl   $0x0,0xa4
     c87:	00 00 00 
     c8a:	31 c0                	xor    %eax,%eax
		return HRTIMER_NORESTART;	
	}

}
     c8c:	83 c4 18             	add    $0x18,%esp
     c8f:	5b                   	pop    %ebx
     c90:	5e                   	pop    %esi
     c91:	5f                   	pop    %edi
     c92:	5d                   	pop    %ebp
     c93:	c3                   	ret    
     c94:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
	//fsm_printf("fsm_tm_expire\n");
	spin_lock(&fsm_core.lock);
	pB = TMBLOCK_PTR;
	cur_time = ktime_get();
	pB->tm_state = FSM_TM_EXPIRE;		
	while(pB->evQ && !LATE_TIME(cur_time, pB->evQ->expire))
     c98:	7c 05                	jl     c9f <__fsm_tm_expire+0xaf>
     c9a:	83 f8 00             	cmp    $0x0,%eax
     c9d:	77 99                	ja     c38 <__fsm_tm_expire+0x48>
     c9f:	89 5d ec             	mov    %ebx,-0x14(%ebp)
     ca2:	89 75 f0             	mov    %esi,-0x10(%ebp)
     ca5:	8d 76 00             	lea    0x0(%esi),%esi
	{
		pE = pB->evQ;
		pB->evQ = pE->pNext;
     ca8:	8b 07                	mov    (%edi),%eax
     caa:	a3 e8 00 00 00       	mov    %eax,0xe8
		__fsm_core_self_drive(pE->type,pE->code,pE->pkptr,pE->src_id,pE->dst_id,pE->buffer,INVALIDE);  
     caf:	8b 4f 1c             	mov    0x1c(%edi),%ecx
     cb2:	8b 57 14             	mov    0x14(%edi),%edx
     cb5:	8b 47 18             	mov    0x18(%edi),%eax
     cb8:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
     cbf:	00 
     cc0:	8b 5f 28             	mov    0x28(%edi),%ebx
     cc3:	89 5c 24 08          	mov    %ebx,0x8(%esp)
     cc7:	8b 5f 20             	mov    0x20(%edi),%ebx
     cca:	89 5c 24 04          	mov    %ebx,0x4(%esp)
     cce:	8b 5f 24             	mov    0x24(%edi),%ebx
     cd1:	89 1c 24             	mov    %ebx,(%esp)
     cd4:	e8 17 fc ff ff       	call   8f0 <__fsm_core_self_drive>
	return ptr;
}

void fsm_mem_free(void* ptr)
{
	FSM_MEM_FREE(ptr);
     cd9:	89 f8                	mov    %edi,%eax
     cdb:	e8 fc ff ff ff       	call   cdc <__fsm_tm_expire+0xec>
	//fsm_printf("fsm_tm_expire\n");
	spin_lock(&fsm_core.lock);
	pB = TMBLOCK_PTR;
	cur_time = ktime_get();
	pB->tm_state = FSM_TM_EXPIRE;		
	while(pB->evQ && !LATE_TIME(cur_time, pB->evQ->expire))
     ce0:	8b 3d e8 00 00 00    	mov    0xe8,%edi
     ce6:	85 ff                	test   %edi,%edi
     ce8:	0f 84 4a ff ff ff    	je     c38 <__fsm_tm_expire+0x48>
     cee:	8b 47 08             	mov    0x8(%edi),%eax
     cf1:	8b 57 0c             	mov    0xc(%edi),%edx
     cf4:	2b 45 ec             	sub    -0x14(%ebp),%eax
     cf7:	1b 55 f0             	sbb    -0x10(%ebp),%edx
     cfa:	83 fa 00             	cmp    $0x0,%edx
     cfd:	7c a9                	jl     ca8 <__fsm_tm_expire+0xb8>
     cff:	0f 8f 33 ff ff ff    	jg     c38 <__fsm_tm_expire+0x48>
     d05:	83 f8 00             	cmp    $0x0,%eax
     d08:	76 9e                	jbe    ca8 <__fsm_tm_expire+0xb8>
     d0a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
     d10:	e9 23 ff ff ff       	jmp    c38 <__fsm_tm_expire+0x48>
     d15:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
     d19:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00000d20 <fsm_core_close>:
	}
	return FSM_EXEC_SUCC;
}

int fsm_core_close()
{
     d20:	55                   	push   %ebp
     d21:	89 e5                	mov    %esp,%ebp
     d23:	57                   	push   %edi
     d24:	56                   	push   %esi
     d25:	53                   	push   %ebx
     d26:	83 ec 14             	sub    $0x14,%esp
     d29:	e8 fc ff ff ff       	call   d2a <fsm_core_close+0xa>
	struct evioctl *ev_ptr, *tmp_ptr;
	int i;
	if(fsm_core.state == CORE_CLOSED)
     d2e:	8b 1d 08 00 00 00    	mov    0x8,%ebx
     d34:	85 db                	test   %ebx,%ebx
     d36:	75 10                	jne    d48 <fsm_core_close+0x28>
		INTF[i].send = __fsm_skb_send_null;
	}
	fsm_printf("core has closed.\n");
	spin_unlock(&fsm_core.lock);
	return FSM_EXEC_SUCC;
}
     d38:	83 c4 14             	add    $0x14,%esp
     d3b:	31 c0                	xor    %eax,%eax
     d3d:	5b                   	pop    %ebx
     d3e:	5e                   	pop    %esi
     d3f:	5f                   	pop    %edi
     d40:	5d                   	pop    %ebp
     d41:	c3                   	ret    
     d42:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
{
	struct evioctl *ev_ptr, *tmp_ptr;
	int i;
	if(fsm_core.state == CORE_CLOSED)
		return FSM_EXEC_SUCC;
	spin_lock(&fsm_core.lock);
     d48:	b8 14 01 00 00       	mov    $0x114,%eax
     d4d:	e8 fc ff ff ff       	call   d4e <fsm_core_close+0x2e>
	fsm_printf("core is closing.\n");
     d52:	c7 04 24 2b 00 00 00 	movl   $0x2b,(%esp)
     d59:	e8 fc ff ff ff       	call   d5a <fsm_core_close+0x3a>
	__fsm_core_self_drive(FSM_EV_TYPE_CORE,FSM_EV_CORE_CLOSE,NULL,KERNEL_MODULE,MAIN_PORT,NULL,INVALIDE);
     d5e:	a1 ec 00 00 00       	mov    0xec,%eax
     d63:	31 c9                	xor    %ecx,%ecx
     d65:	ba 01 00 00 00       	mov    $0x1,%edx
     d6a:	89 44 24 04          	mov    %eax,0x4(%esp)
     d6e:	b8 05 00 00 00       	mov    $0x5,%eax
     d73:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
     d7a:	00 
     d7b:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
     d82:	00 
     d83:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
     d8a:	e8 61 fb ff ff       	call   8f0 <__fsm_core_self_drive>
static void __fsm_tm_flush()
{
	__tmEvent* pE;
	__tmBlock* pB;
	pB = TMBLOCK_PTR;
	while(pB->evQ)
     d8f:	a1 e8 00 00 00       	mov    0xe8,%eax
}
static void __fsm_tm_stop()
{
	__tmBlock* pB;
	pB = TMBLOCK_PTR;
	pB->tm_state = FSM_TM_STOP;
     d94:	c7 05 a4 00 00 00 00 	movl   $0x0,0xa4
     d9b:	00 00 00 
static void __fsm_tm_flush()
{
	__tmEvent* pE;
	__tmBlock* pB;
	pB = TMBLOCK_PTR;
	while(pB->evQ)
     d9e:	85 c0                	test   %eax,%eax
     da0:	74 1c                	je     dbe <fsm_core_close+0x9e>
     da2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	{
		pE = pB->evQ;
		pB->evQ = pE->pNext;
     da8:	8b 10                	mov    (%eax),%edx
     daa:	89 15 e8 00 00 00    	mov    %edx,0xe8
	return ptr;
}

void fsm_mem_free(void* ptr)
{
	FSM_MEM_FREE(ptr);
     db0:	e8 fc ff ff ff       	call   db1 <fsm_core_close+0x91>
static void __fsm_tm_flush()
{
	__tmEvent* pE;
	__tmBlock* pB;
	pB = TMBLOCK_PTR;
	while(pB->evQ)
     db5:	a1 e8 00 00 00       	mov    0xe8,%eax
     dba:	85 c0                	test   %eax,%eax
     dbc:	75 ea                	jne    da8 <fsm_core_close+0x88>
	fsm_printf("core is closing.\n");
	__fsm_core_self_drive(FSM_EV_TYPE_CORE,FSM_EV_CORE_CLOSE,NULL,KERNEL_MODULE,MAIN_PORT,NULL,INVALIDE);
	__fsm_tm_stop();
	__fsm_tm_flush();
	//Cancel tasklets
	tasklet_kill(fsm_core.tx_tsklt);
     dbe:	a1 20 01 00 00       	mov    0x120,%eax
     dc3:	e8 fc ff ff ff       	call   dc4 <fsm_core_close+0xa4>
	tasklet_kill(fsm_core.rx_tsklt);
     dc8:	a1 24 01 00 00       	mov    0x124,%eax
     dcd:	e8 fc ff ff ff       	call   dce <fsm_core_close+0xae>
	tasklet_kill(fsm_core.do_ioctl_tsklt);	
     dd2:	a1 28 01 00 00       	mov    0x128,%eax
     dd7:	e8 fc ff ff ff       	call   dd8 <fsm_core_close+0xb8>
	//Flush queues;
	while(!skb_queue_empty(fsm_core.tx_queue))
     ddc:	a1 18 01 00 00       	mov    0x118,%eax
     de1:	39 00                	cmp    %eax,(%eax)
     de3:	74 2d                	je     e12 <fsm_core_close+0xf2>
     de5:	8d 76 00             	lea    0x0(%esi),%esi
	{
		fsm_pkt_destroy(skb_dequeue(fsm_core.tx_queue));
     de8:	e8 fc ff ff ff       	call   de9 <fsm_core_close+0xc9>
	return pkptr_new;
}

void fsm_pkt_destroy(FSM_PKT* pkptr)
{
	KFREE_SKB(pkptr);
     ded:	e8 fc ff ff ff       	call   dee <fsm_core_close+0xce>
	//Cancel tasklets
	tasklet_kill(fsm_core.tx_tsklt);
	tasklet_kill(fsm_core.rx_tsklt);
	tasklet_kill(fsm_core.do_ioctl_tsklt);	
	//Flush queues;
	while(!skb_queue_empty(fsm_core.tx_queue))
     df2:	a1 18 01 00 00       	mov    0x118,%eax
     df7:	39 00                	cmp    %eax,(%eax)
     df9:	75 ed                	jne    de8 <fsm_core_close+0xc8>
	{
		fsm_pkt_destroy(skb_dequeue(fsm_core.tx_queue));
	}
	while(!skb_queue_empty(fsm_core.rx_queue))
     dfb:	a1 1c 01 00 00       	mov    0x11c,%eax
     e00:	39 00                	cmp    %eax,(%eax)
     e02:	74 17                	je     e1b <fsm_core_close+0xfb>
     e04:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
	{
		fsm_pkt_destroy(skb_dequeue(fsm_core.rx_queue));
     e08:	e8 fc ff ff ff       	call   e09 <fsm_core_close+0xe9>
	return pkptr_new;
}

void fsm_pkt_destroy(FSM_PKT* pkptr)
{
	KFREE_SKB(pkptr);
     e0d:	e8 fc ff ff ff       	call   e0e <fsm_core_close+0xee>
	//Flush queues;
	while(!skb_queue_empty(fsm_core.tx_queue))
	{
		fsm_pkt_destroy(skb_dequeue(fsm_core.tx_queue));
	}
	while(!skb_queue_empty(fsm_core.rx_queue))
     e12:	a1 1c 01 00 00       	mov    0x11c,%eax
     e17:	39 00                	cmp    %eax,(%eax)
     e19:	75 ed                	jne    e08 <fsm_core_close+0xe8>
	{
		fsm_pkt_destroy(skb_dequeue(fsm_core.rx_queue));
	}
	if(!list_empty(&fsm_core.do_ioctl_list));
	{
		list_for_each_entry_safe(ev_ptr, tmp_ptr, &fsm_core.do_ioctl_list, list_node)
     e1b:	a1 34 01 00 00       	mov    0x134,%eax
     e20:	8d 58 f0             	lea    -0x10(%eax),%ebx
     e23:	3d 34 01 00 00       	cmp    $0x134,%eax
     e28:	8b 73 10             	mov    0x10(%ebx),%esi
     e2b:	74 61                	je     e8e <fsm_core_close+0x16e>
     e2d:	83 ee 10             	sub    $0x10,%esi
     e30:	bf 3c 01 00 00       	mov    $0x13c,%edi
     e35:	eb 11                	jmp    e48 <fsm_core_close+0x128>
     e37:	90                   	nop
     e38:	81 fe 24 01 00 00    	cmp    $0x124,%esi
     e3e:	8b 46 10             	mov    0x10(%esi),%eax
     e41:	74 4b                	je     e8e <fsm_core_close+0x16e>
     e43:	89 f3                	mov    %esi,%ebx
     e45:	8d 70 f0             	lea    -0x10(%eax),%esi
		{
			spin_lock(&fsm_core.ioctl_list_lock);
     e48:	b8 3c 01 00 00       	mov    $0x13c,%eax
     e4d:	e8 fc ff ff ff       	call   e4e <fsm_core_close+0x12e>
 * in an undefined state.
 */
#ifndef CONFIG_DEBUG_LIST
static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
     e52:	8b 43 14             	mov    0x14(%ebx),%eax
     e55:	8b 53 10             	mov    0x10(%ebx),%edx
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
     e58:	89 42 04             	mov    %eax,0x4(%edx)
	prev->next = next;
     e5b:	89 10                	mov    %edx,(%eax)
     e5d:	89 f8                	mov    %edi,%eax
 */
#ifndef CONFIG_DEBUG_LIST
static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON1;
     e5f:	c7 43 10 00 01 10 00 	movl   $0x100100,0x10(%ebx)
	entry->prev = LIST_POISON2;
     e66:	c7 43 14 00 02 20 00 	movl   $0x200200,0x14(%ebx)
     e6d:	ff 15 14 00 00 00    	call   *0x14
	return ptr;
}

void fsm_mem_free(void* ptr)
{
	FSM_MEM_FREE(ptr);
     e73:	8b 43 0c             	mov    0xc(%ebx),%eax
     e76:	e8 fc ff ff ff       	call   e77 <fsm_core_close+0x157>
     e7b:	89 d8                	mov    %ebx,%eax
     e7d:	e8 fc ff ff ff       	call   e7e <fsm_core_close+0x15e>
			spin_lock(&fsm_core.ioctl_list_lock);
			list_del(&ev_ptr->list_node);
			spin_unlock(&fsm_core.ioctl_list_lock);
			fsm_mem_free(ev_ptr->ifr.buffer);
			fsm_mem_free(ev_ptr);
			if(list_empty(&fsm_core.do_ioctl_list))
     e82:	81 3d 34 01 00 00 34 	cmpl   $0x134,0x134
     e89:	01 00 00 
     e8c:	75 aa                	jne    e38 <fsm_core_close+0x118>
				break;
		}
	}	
	fsm_core.state = CORE_CLOSED;
     e8e:	c7 05 08 00 00 00 00 	movl   $0x0,0x8
     e95:	00 00 00 
     e98:	31 c0                	xor    %eax,%eax
     e9a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	for(i = 0; i < MAX_INTF; i++)
	{
		if(INTF[i].dev)
     ea0:	8b 90 2c 00 00 00    	mov    0x2c(%eax),%edx
     ea6:	85 d2                	test   %edx,%edx
     ea8:	74 07                	je     eb1 <fsm_core_close+0x191>
 *
 * Atomically decrements @v by 1.
 */
static inline void atomic_dec(atomic_t *v)
{
	asm volatile(LOCK_PREFIX "decl %0"
     eaa:	f0 ff 8a 20 02 00 00 	lock decl 0x220(%edx)
     eb1:	83 c0 10             	add    $0x10,%eax
			if(list_empty(&fsm_core.do_ioctl_list))
				break;
		}
	}	
	fsm_core.state = CORE_CLOSED;
	for(i = 0; i < MAX_INTF; i++)
     eb4:	3d 80 00 00 00       	cmp    $0x80,%eax
     eb9:	75 e5                	jne    ea0 <fsm_core_close+0x180>
     ebb:	30 c0                	xor    %al,%al
     ebd:	8d 76 00             	lea    0x0(%esi),%esi
			dev_put(INTF[i].dev);
		}	
	}
	for(i = 0; i < MAX_INTF; i++)
	{
		INTF[i].valid = 0;
     ec0:	c7 80 24 00 00 00 00 	movl   $0x0,0x24(%eax)
     ec7:	00 00 00 
		INTF[i].proto = 0;
     eca:	66 c7 80 28 00 00 00 	movw   $0x0,0x28(%eax)
     ed1:	00 00 
		INTF[i].dev	= 0;
     ed3:	c7 80 2c 00 00 00 00 	movl   $0x0,0x2c(%eax)
     eda:	00 00 00 
		INTF[i].send = __fsm_skb_send_null;
     edd:	c7 80 30 00 00 00 90 	movl   $0xf90,0x30(%eax)
     ee4:	0f 00 00 
     ee7:	83 c0 10             	add    $0x10,%eax
		if(INTF[i].dev)
		{
			dev_put(INTF[i].dev);
		}	
	}
	for(i = 0; i < MAX_INTF; i++)
     eea:	3d 80 00 00 00       	cmp    $0x80,%eax
     eef:	75 cf                	jne    ec0 <fsm_core_close+0x1a0>
		INTF[i].valid = 0;
		INTF[i].proto = 0;
		INTF[i].dev	= 0;
		INTF[i].send = __fsm_skb_send_null;
	}
	fsm_printf("core has closed.\n");
     ef1:	c7 04 24 3d 00 00 00 	movl   $0x3d,(%esp)
     ef8:	e8 fc ff ff ff       	call   ef9 <fsm_core_close+0x1d9>
     efd:	b8 14 01 00 00       	mov    $0x114,%eax
     f02:	ff 15 14 00 00 00    	call   *0x14
	spin_unlock(&fsm_core.lock);
	return FSM_EXEC_SUCC;
}
     f08:	31 c0                	xor    %eax,%eax
     f0a:	83 c4 14             	add    $0x14,%esp
     f0d:	5b                   	pop    %ebx
     f0e:	5e                   	pop    %esi
     f0f:	5f                   	pop    %edi
     f10:	5d                   	pop    %ebp
     f11:	c3                   	ret    
     f12:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     f19:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00000f20 <fsm_core_destroy>:
	return; 
}


void fsm_core_destroy()
{
     f20:	55                   	push   %ebp
     f21:	89 e5                	mov    %esp,%ebp
     f23:	53                   	push   %ebx
     f24:	e8 fc ff ff ff       	call   f25 <fsm_core_destroy+0x5>
	int i;
	if(fsm_core.state != CORE_CLOSED)
     f29:	a1 08 00 00 00       	mov    0x8,%eax
     f2e:	85 c0                	test   %eax,%eax
     f30:	75 4e                	jne    f80 <fsm_core_destroy+0x60>
		fsm_core_close();
     f32:	31 db                	xor    %ebx,%ebx
     f34:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
	for(i = 0; i < MAX_FSM; i++)
	{
		fsm_unregister_destroy(i);
     f38:	89 d8                	mov    %ebx,%eax
void fsm_core_destroy()
{
	int i;
	if(fsm_core.state != CORE_CLOSED)
		fsm_core_close();
	for(i = 0; i < MAX_FSM; i++)
     f3a:	83 c3 01             	add    $0x1,%ebx
	{
		fsm_unregister_destroy(i);
     f3d:	e8 fc ff ff ff       	call   f3e <fsm_core_destroy+0x1e>
void fsm_core_destroy()
{
	int i;
	if(fsm_core.state != CORE_CLOSED)
		fsm_core_close();
	for(i = 0; i < MAX_FSM; i++)
     f42:	83 fb 06             	cmp    $0x6,%ebx
     f45:	75 f1                	jne    f38 <fsm_core_destroy+0x18>
	return ptr;
}

void fsm_mem_free(void* ptr)
{
	FSM_MEM_FREE(ptr);
     f47:	a1 18 01 00 00       	mov    0x118,%eax
     f4c:	e8 fc ff ff ff       	call   f4d <fsm_core_destroy+0x2d>
     f51:	a1 1c 01 00 00       	mov    0x11c,%eax
     f56:	e8 fc ff ff ff       	call   f57 <fsm_core_destroy+0x37>
     f5b:	a1 20 01 00 00       	mov    0x120,%eax
     f60:	e8 fc ff ff ff       	call   f61 <fsm_core_destroy+0x41>
     f65:	a1 24 01 00 00       	mov    0x124,%eax
     f6a:	e8 fc ff ff ff       	call   f6b <fsm_core_destroy+0x4b>
     f6f:	a1 28 01 00 00       	mov    0x128,%eax
     f74:	e8 fc ff ff ff       	call   f75 <fsm_core_destroy+0x55>
	fsm_mem_free(fsm_core.rx_queue);
	fsm_mem_free(fsm_core.tx_tsklt);
	fsm_mem_free(fsm_core.rx_tsklt);
	fsm_mem_free(fsm_core.do_ioctl_tsklt);
	return;
}
     f79:	5b                   	pop    %ebx
     f7a:	5d                   	pop    %ebp
     f7b:	c3                   	ret    
     f7c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

void fsm_core_destroy()
{
	int i;
	if(fsm_core.state != CORE_CLOSED)
		fsm_core_close();
     f80:	e8 fc ff ff ff       	call   f81 <fsm_core_destroy+0x61>
     f85:	8d 76 00             	lea    0x0(%esi),%esi
     f88:	eb a8                	jmp    f32 <fsm_core_destroy+0x12>
     f8a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00000f90 <__fsm_skb_send_null>:
	//	fsm_pkt_destroy(pkptr);
	return;
}

static void __fsm_skb_send_null(FSM_PKT* pkptr, NETDEV* dev, u16 protocol)
{
     f90:	55                   	push   %ebp
     f91:	89 e5                	mov    %esp,%ebp
     f93:	e8 fc ff ff ff       	call   f94 <__fsm_skb_send_null+0x4>
	return pkptr_new;
}

void fsm_pkt_destroy(FSM_PKT* pkptr)
{
	KFREE_SKB(pkptr);
     f98:	e8 fc ff ff ff       	call   f99 <__fsm_skb_send_null+0x9>
}

static void __fsm_skb_send_null(FSM_PKT* pkptr, NETDEV* dev, u16 protocol)
{
	fsm_pkt_destroy(pkptr);
}
     f9d:	5d                   	pop    %ebp
     f9e:	c3                   	ret    
     f9f:	90                   	nop

00000fa0 <fsm_pkt_send>:
	fsm_core.pkptr = NULL;
	return ptr;
}

void fsm_pkt_send(FSM_PKT* pkptr, int oinf)
{
     fa0:	55                   	push   %ebp
     fa1:	89 e5                	mov    %esp,%ebp
     fa3:	53                   	push   %ebx
     fa4:	e8 fc ff ff ff       	call   fa5 <fsm_pkt_send+0x5>
	if(oinf < MAX_INTF && INTF[oinf].valid)
     fa9:	83 fa 07             	cmp    $0x7,%edx
     fac:	7f 32                	jg     fe0 <fsm_pkt_send+0x40>
     fae:	8d 5a 02             	lea    0x2(%edx),%ebx
     fb1:	c1 e3 04             	shl    $0x4,%ebx
     fb4:	8b 93 04 00 00 00    	mov    0x4(%ebx),%edx
     fba:	85 d2                	test   %edx,%edx
     fbc:	74 22                	je     fe0 <fsm_pkt_send+0x40>
	{
		if(INTF[oinf].valid == DEV_INTF_REQ)
     fbe:	83 fa 01             	cmp    $0x1,%edx
     fc1:	74 25                	je     fe8 <fsm_pkt_send+0x48>
		{
			INTF[oinf].send(pkptr, INTF[oinf].dev, INTF[oinf].proto);
		}
		else if(INTF[oinf].valid == DEV_INTF_IND)
     fc3:	83 fa 02             	cmp    $0x2,%edx
     fc6:	75 1d                	jne    fe5 <fsm_pkt_send+0x45>
		{
			INTF[oinf].send(pkptr, fsm_core.dev, INTF[oinf].proto);
     fc8:	0f b7 8b 08 00 00 00 	movzwl 0x8(%ebx),%ecx
     fcf:	8b 15 08 01 00 00    	mov    0x108,%edx
     fd5:	ff 93 10 00 00 00    	call   *0x10(%ebx)
     fdb:	eb 08                	jmp    fe5 <fsm_pkt_send+0x45>
     fdd:	8d 76 00             	lea    0x0(%esi),%esi
	return pkptr_new;
}

void fsm_pkt_destroy(FSM_PKT* pkptr)
{
	KFREE_SKB(pkptr);
     fe0:	e8 fc ff ff ff       	call   fe1 <fsm_pkt_send+0x41>
	}
	else
	{
		fsm_pkt_destroy(pkptr);
	}
}
     fe5:	5b                   	pop    %ebx
     fe6:	5d                   	pop    %ebp
     fe7:	c3                   	ret    
{
	if(oinf < MAX_INTF && INTF[oinf].valid)
	{
		if(INTF[oinf].valid == DEV_INTF_REQ)
		{
			INTF[oinf].send(pkptr, INTF[oinf].dev, INTF[oinf].proto);
     fe8:	0f b7 8b 08 00 00 00 	movzwl 0x8(%ebx),%ecx
     fef:	8b 93 0c 00 00 00    	mov    0xc(%ebx),%edx
     ff5:	ff 93 10 00 00 00    	call   *0x10(%ebx)
     ffb:	eb e8                	jmp    fe5 <fsm_pkt_send+0x45>
     ffd:	8d 76 00             	lea    0x0(%esi),%esi

00001000 <fsm_skb_realloc_headeroom>:
	return pkptr;
}


FSM_PKT* fsm_skb_realloc_headeroom(FSM_PKT* pkptr, unsigned int head_len)
{
    1000:	55                   	push   %ebp
    1001:	89 e5                	mov    %esp,%ebp
    1003:	83 ec 0c             	sub    $0xc,%esp
    1006:	89 1c 24             	mov    %ebx,(%esp)
    1009:	89 74 24 04          	mov    %esi,0x4(%esp)
    100d:	89 7c 24 08          	mov    %edi,0x8(%esp)
    1011:	e8 fc ff ff ff       	call   1012 <fsm_skb_realloc_headeroom+0x12>
    1016:	89 c3                	mov    %eax,%ebx
	FSM_PKT* pkptr_new;
	pkptr_new = SKB_REALLOC_HEADROOM(pkptr, head_len);
    1018:	e8 fc ff ff ff       	call   1019 <fsm_skb_realloc_headeroom+0x19>
	if (unlikely(pkptr_new == NULL))
    101d:	85 c0                	test   %eax,%eax


FSM_PKT* fsm_skb_realloc_headeroom(FSM_PKT* pkptr, unsigned int head_len)
{
	FSM_PKT* pkptr_new;
	pkptr_new = SKB_REALLOC_HEADROOM(pkptr, head_len);
    101f:	89 c6                	mov    %eax,%esi
	if (unlikely(pkptr_new == NULL))
    1021:	74 24                	je     1047 <fsm_skb_realloc_headeroom+0x47>
	{
		KFREE_SKB(pkptr);
		return NULL;
	}
	if(pkptr->sk)
    1023:	8b 7b 08             	mov    0x8(%ebx),%edi
    1026:	85 ff                	test   %edi,%edi
    1028:	74 1d                	je     1047 <fsm_skb_realloc_headeroom+0x47>
 *	destructor function and make the @skb unowned. The buffer continues
 *	to exist but is no longer charged to its former owner.
 */
static inline void skb_orphan(struct sk_buff *skb)
{
	if (skb->destructor)
    102a:	8b 50 68             	mov    0x68(%eax),%edx
    102d:	85 d2                	test   %edx,%edx
    102f:	74 02                	je     1033 <fsm_skb_realloc_headeroom+0x33>
		skb->destructor(skb);
    1031:	ff d2                	call   *%edx
 */

static inline void skb_set_owner_w(struct sk_buff *skb, struct sock *sk)
{
	skb_orphan(skb);
	skb->sk = sk;
    1033:	89 7e 08             	mov    %edi,0x8(%esi)
 *
 * Atomically adds @i to @v.
 */
static inline void atomic_add(int i, atomic_t *v)
{
	asm volatile(LOCK_PREFIX "addl %1,%0"
    1036:	8b 86 b0 00 00 00    	mov    0xb0(%esi),%eax
	skb->destructor = sock_wfree;
    103c:	c7 46 68 00 00 00 00 	movl   $0x0,0x68(%esi)
    1043:	f0 01 47 64          	lock add %eax,0x64(%edi)
	{
		SKB_SET_OWNER_W(pkptr_new, pkptr->sk); 
	}
	KFREE_SKB(pkptr);
    1047:	89 d8                	mov    %ebx,%eax
    1049:	e8 fc ff ff ff       	call   104a <fsm_skb_realloc_headeroom+0x4a>
	return pkptr_new;
}
    104e:	89 f0                	mov    %esi,%eax
    1050:	8b 1c 24             	mov    (%esp),%ebx
    1053:	8b 74 24 04          	mov    0x4(%esp),%esi
    1057:	8b 7c 24 08          	mov    0x8(%esp),%edi
    105b:	89 ec                	mov    %ebp,%esp
    105d:	5d                   	pop    %ebp
    105e:	c3                   	ret    
    105f:	90                   	nop

00001060 <fsm_pkt_create>:
		fsm_pkt_destroy(pkptr);
	}
}

FSM_PKT* fsm_pkt_create(unsigned int size)
{
    1060:	55                   	push   %ebp
    1061:	89 e5                	mov    %esp,%ebp
    1063:	53                   	push   %ebx
    1064:	e8 fc ff ff ff       	call   1065 <fsm_pkt_create+0x5>
	FSM_PKT* pkptr;
	pkptr = (FSM_PKT*) ALLOC_SKB(size);
    1069:	e8 fc ff ff ff       	call   106a <fsm_pkt_create+0xa>
	fsm_mem_set(pkptr->head, 0, pkptr->end - pkptr->head);
    106e:	31 d2                	xor    %edx,%edx
}

FSM_PKT* fsm_pkt_create(unsigned int size)
{
	FSM_PKT* pkptr;
	pkptr = (FSM_PKT*) ALLOC_SKB(size);
    1070:	89 c3                	mov    %eax,%ebx
	fsm_mem_set(pkptr->head, 0, pkptr->end - pkptr->head);
    1072:	8b 80 a8 00 00 00    	mov    0xa8(%eax),%eax
    1078:	8b 8b a4 00 00 00    	mov    0xa4(%ebx),%ecx
    107e:	29 c1                	sub    %eax,%ecx
    1080:	e8 fc ff ff ff       	call   1081 <fsm_pkt_create+0x21>
	return pkptr;
}
    1085:	89 d8                	mov    %ebx,%eax
    1087:	5b                   	pop    %ebx
    1088:	5d                   	pop    %ebp
    1089:	c3                   	ret    
    108a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00001090 <fsm_get_id_by_name>:
{
	return fsm_core.dev;
}

int fsm_get_id_by_name(const char* name)
{
    1090:	55                   	push   %ebp
    1091:	89 e5                	mov    %esp,%ebp
    1093:	56                   	push   %esi
    1094:	53                   	push   %ebx
    1095:	e8 fc ff ff ff       	call   1096 <fsm_get_id_by_name+0x6>
    109a:	31 db                	xor    %ebx,%ebx
    109c:	89 c6                	mov    %eax,%esi
	int i;
	for(i=0; i< MAX_FSM; ++i)
	{
		if(strcmp(FSM[i]->name, name) == 0)
    109e:	8b 04 9d f0 00 00 00 	mov    0xf0(,%ebx,4),%eax
    10a5:	89 f2                	mov    %esi,%edx
    10a7:	e8 fc ff ff ff       	call   10a8 <fsm_get_id_by_name+0x18>
    10ac:	85 c0                	test   %eax,%eax
    10ae:	74 18                	je     10c8 <fsm_get_id_by_name+0x38>
}

int fsm_get_id_by_name(const char* name)
{
	int i;
	for(i=0; i< MAX_FSM; ++i)
    10b0:	83 c3 01             	add    $0x1,%ebx
    10b3:	83 fb 06             	cmp    $0x6,%ebx
    10b6:	75 e6                	jne    109e <fsm_get_id_by_name+0xe>
    10b8:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
		{
			return FSM[i]->id;
		}
	}
	return -1;
}
    10bd:	5b                   	pop    %ebx
    10be:	5e                   	pop    %esi
    10bf:	5d                   	pop    %ebp
    10c0:	c3                   	ret    
    10c1:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
	int i;
	for(i=0; i< MAX_FSM; ++i)
	{
		if(strcmp(FSM[i]->name, name) == 0)
		{
			return FSM[i]->id;
    10c8:	8b 04 9d f0 00 00 00 	mov    0xf0(,%ebx,4),%eax
		}
	}
	return -1;
}
    10cf:	5b                   	pop    %ebx
    10d0:	5e                   	pop    %esi
    10d1:	5d                   	pop    %ebp
	int i;
	for(i=0; i< MAX_FSM; ++i)
	{
		if(strcmp(FSM[i]->name, name) == 0)
		{
			return FSM[i]->id;
    10d2:	8b 80 80 00 00 00    	mov    0x80(%eax),%eax
		}
	}
	return -1;
}
    10d8:	c3                   	ret    
    10d9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

000010e0 <fsm_mem_alloc>:
	return SKB_HEADROOM(pkptr);
}

/* Memory operation */
void* fsm_mem_alloc(size_t size)
{
    10e0:	55                   	push   %ebp
    10e1:	89 e5                	mov    %esp,%ebp
    10e3:	e8 fc ff ff ff       	call   10e4 <fsm_mem_alloc+0x4>
			trace_kmalloc(_THIS_IP_, ret, size, s->size, flags);

			return ret;
		}
	}
	return __kmalloc(size, flags);
    10e8:	ba 20 00 00 00       	mov    $0x20,%edx
    10ed:	e8 fc ff ff ff       	call   10ee <fsm_mem_alloc+0xe>
	void* ptr;
	ptr = FSM_MEM_ALLOC(size);
	return ptr;
}
    10f2:	5d                   	pop    %ebp
    10f3:	c3                   	ret    
    10f4:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    10fa:	8d bf 00 00 00 00    	lea    0x0(%edi),%edi

00001100 <fsm_create_register>:
	return FSM_EXEC_SUCC;
}

/* FSM operations */
int fsm_create_register(const char* name, void (*fsm_main), void* fsm_sv_ptr)
{
    1100:	55                   	push   %ebp
    1101:	89 e5                	mov    %esp,%ebp
    1103:	83 ec 14             	sub    $0x14,%esp
    1106:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    1109:	89 75 f8             	mov    %esi,-0x8(%ebp)
    110c:	89 7d fc             	mov    %edi,-0x4(%ebp)
    110f:	e8 fc ff ff ff       	call   1110 <fsm_create_register+0x10>
    1114:	31 db                	xor    %ebx,%ebx
    1116:	89 c7                	mov    %eax,%edi
	int i;
	for(i=0; i < MAX_FSM; ++i)
	{
		if(FSM[i] == NULL)
    1118:	8b 34 9d f0 00 00 00 	mov    0xf0(,%ebx,4),%esi
    111f:	85 f6                	test   %esi,%esi
    1121:	74 1d                	je     1140 <fsm_create_register+0x40>

/* FSM operations */
int fsm_create_register(const char* name, void (*fsm_main), void* fsm_sv_ptr)
{
	int i;
	for(i=0; i < MAX_FSM; ++i)
    1123:	83 c3 01             	add    $0x1,%ebx
    1126:	83 fb 06             	cmp    $0x6,%ebx
    1129:	75 ed                	jne    1118 <fsm_create_register+0x18>
    112b:	bb ff ff ff ff       	mov    $0xffffffff,%ebx
			FSM[i]->_fsm_current_block = 0;
			return i;
		}
	}
	return -1;
}
    1130:	89 d8                	mov    %ebx,%eax
    1132:	8b 75 f8             	mov    -0x8(%ebp),%esi
    1135:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    1138:	8b 7d fc             	mov    -0x4(%ebp),%edi
    113b:	89 ec                	mov    %ebp,%esp
    113d:	5d                   	pop    %ebp
    113e:	c3                   	ret    
    113f:	90                   	nop
	int i;
	for(i=0; i < MAX_FSM; ++i)
	{
		if(FSM[i] == NULL)
		{
			FSM[i] = (FSM_SPEC*)fsm_mem_alloc(sizeof(FSM_SPEC));
    1140:	b8 90 00 00 00       	mov    $0x90,%eax
    1145:	89 4d f0             	mov    %ecx,-0x10(%ebp)
    1148:	8d 73 3c             	lea    0x3c(%ebx),%esi
    114b:	89 55 ec             	mov    %edx,-0x14(%ebp)
    114e:	e8 fc ff ff ff       	call   114f <fsm_create_register+0x4f>
			FSM[i]->fsm_main = fsm_main;
    1153:	8b 55 ec             	mov    -0x14(%ebp),%edx
	int i;
	for(i=0; i < MAX_FSM; ++i)
	{
		if(FSM[i] == NULL)
		{
			FSM[i] = (FSM_SPEC*)fsm_mem_alloc(sizeof(FSM_SPEC));
    1156:	89 04 b5 00 00 00 00 	mov    %eax,0x0(,%esi,4)
			FSM[i]->fsm_main = fsm_main;
    115d:	89 90 84 00 00 00    	mov    %edx,0x84(%eax)
			FSM[i]->id = i;
    1163:	8b 04 b5 00 00 00 00 	mov    0x0(,%esi,4),%eax
			strcpy(FSM[i]->name, name);
    116a:	89 fa                	mov    %edi,%edx
	{
		if(FSM[i] == NULL)
		{
			FSM[i] = (FSM_SPEC*)fsm_mem_alloc(sizeof(FSM_SPEC));
			FSM[i]->fsm_main = fsm_main;
			FSM[i]->id = i;
    116c:	89 98 80 00 00 00    	mov    %ebx,0x80(%eax)
			strcpy(FSM[i]->name, name);
    1172:	8b 04 b5 00 00 00 00 	mov    0x0(,%esi,4),%eax
    1179:	e8 fc ff ff ff       	call   117a <fsm_create_register+0x7a>
			FSM[i]->fsm_sv_ptr = fsm_sv_ptr;
    117e:	8b 04 b5 00 00 00 00 	mov    0x0(,%esi,4),%eax
    1185:	8b 4d f0             	mov    -0x10(%ebp),%ecx
    1188:	89 88 88 00 00 00    	mov    %ecx,0x88(%eax)
			FSM[i]->_fsm_current_block = 0;
    118e:	8b 04 b5 00 00 00 00 	mov    0x0(,%esi,4),%eax
    1195:	c7 80 8c 00 00 00 00 	movl   $0x0,0x8c(%eax)
    119c:	00 00 00 
			return i;
    119f:	eb 8f                	jmp    1130 <fsm_create_register+0x30>
    11a1:	eb 0d                	jmp    11b0 <fsm_core_create>
    11a3:	90                   	nop
    11a4:	90                   	nop
    11a5:	90                   	nop
    11a6:	90                   	nop
    11a7:	90                   	nop
    11a8:	90                   	nop
    11a9:	90                   	nop
    11aa:	90                   	nop
    11ab:	90                   	nop
    11ac:	90                   	nop
    11ad:	90                   	nop
    11ae:	90                   	nop
    11af:	90                   	nop

000011b0 <fsm_core_create>:


/* FSM core operations */

void fsm_core_create(void* dev)
{
    11b0:	55                   	push   %ebp
    11b1:	89 e5                	mov    %esp,%ebp
    11b3:	e8 fc ff ff ff       	call   11b4 <fsm_core_create+0x4>
	int i;
	fsm_core.current_fsm = -1;
    11b8:	c7 05 00 00 00 00 ff 	movl   $0xffffffff,0x0
    11bf:	ff ff ff 
	fsm_core.current_state_ptr = NULL;
    11c2:	c7 05 04 00 00 00 00 	movl   $0x0,0x4
    11c9:	00 00 00 
	fsm_core.state = CORE_CLOSED;
    11cc:	c7 05 08 00 00 00 00 	movl   $0x0,0x8
    11d3:	00 00 00 
	fsm_core.pkptr = 0;
    11d6:	c7 05 0c 00 00 00 00 	movl   $0x0,0xc
    11dd:	00 00 00 
	fsm_core.evtype = 0;
    11e0:	c7 05 10 00 00 00 00 	movl   $0x0,0x10
    11e7:	00 00 00 
	fsm_core.code = 0;
	fsm_core.src = 0;
	fsm_core.dev = dev;
    11ea:	a3 08 01 00 00       	mov    %eax,0x108
	FSM_SV_PTR = NULL;
	fsm_core.fsm_drive = NULL;
	MAIN_PORT = -1;
    11ef:	31 c0                	xor    %eax,%eax
	fsm_core.current_fsm = -1;
	fsm_core.current_state_ptr = NULL;
	fsm_core.state = CORE_CLOSED;
	fsm_core.pkptr = 0;
	fsm_core.evtype = 0;
	fsm_core.code = 0;
    11f1:	c7 05 14 00 00 00 00 	movl   $0x0,0x14
    11f8:	00 00 00 
	fsm_core.src = 0;
    11fb:	c7 05 18 00 00 00 00 	movl   $0x0,0x18
    1202:	00 00 00 
	fsm_core.dev = dev;
	FSM_SV_PTR = NULL;
    1205:	c7 05 1c 00 00 00 00 	movl   $0x0,0x1c
    120c:	00 00 00 
	fsm_core.fsm_drive = NULL;
    120f:	c7 05 20 00 00 00 00 	movl   $0x0,0x20
    1216:	00 00 00 
	MAIN_PORT = -1;
    1219:	c7 05 ec 00 00 00 ff 	movl   $0xffffffff,0xec
    1220:	ff ff ff 
    1223:	90                   	nop
    1224:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
	for(i = 0; i < MAX_INTF; i++)
	{
		INTF[i].valid = 0;
    1228:	c7 80 24 00 00 00 00 	movl   $0x0,0x24(%eax)
    122f:	00 00 00 
		INTF[i].proto = 0;
    1232:	66 c7 80 28 00 00 00 	movw   $0x0,0x28(%eax)
    1239:	00 00 
		INTF[i].dev	= 0;
    123b:	c7 80 2c 00 00 00 00 	movl   $0x0,0x2c(%eax)
    1242:	00 00 00 
		INTF[i].send = __fsm_skb_send_null;
    1245:	c7 80 30 00 00 00 90 	movl   $0xf90,0x30(%eax)
    124c:	0f 00 00 
    124f:	83 c0 10             	add    $0x10,%eax
	fsm_core.src = 0;
	fsm_core.dev = dev;
	FSM_SV_PTR = NULL;
	fsm_core.fsm_drive = NULL;
	MAIN_PORT = -1;
	for(i = 0; i < MAX_INTF; i++)
    1252:	3d 80 00 00 00       	cmp    $0x80,%eax
    1257:	75 cf                	jne    1228 <fsm_core_create+0x78>
		FSM[i] = NULL;
	}
	fsm_core.buffer = NULL;
	fsm_core.ioctrl_cmd = 0;
	spin_lock_init(&fsm_core.lock);
	fsm_core.tx_queue = (struct sk_buff_head*)fsm_mem_alloc(sizeof(struct sk_buff_head));
    1259:	b0 10                	mov    $0x10,%al
		INTF[i].dev	= 0;
		INTF[i].send = __fsm_skb_send_null;
	}
	for(i = 0; i < MAX_FSM; ++i)
	{
		FSM[i] = NULL;
    125b:	c7 05 f0 00 00 00 00 	movl   $0x0,0xf0
    1262:	00 00 00 
    1265:	c7 05 f4 00 00 00 00 	movl   $0x0,0xf4
    126c:	00 00 00 
    126f:	c7 05 f8 00 00 00 00 	movl   $0x0,0xf8
    1276:	00 00 00 
    1279:	c7 05 fc 00 00 00 00 	movl   $0x0,0xfc
    1280:	00 00 00 
    1283:	c7 05 00 01 00 00 00 	movl   $0x0,0x100
    128a:	00 00 00 
    128d:	c7 05 04 01 00 00 00 	movl   $0x0,0x104
    1294:	00 00 00 
	}
	fsm_core.buffer = NULL;
    1297:	c7 05 0c 01 00 00 00 	movl   $0x0,0x10c
    129e:	00 00 00 
	fsm_core.ioctrl_cmd = 0;
    12a1:	c7 05 10 01 00 00 00 	movl   $0x0,0x110
    12a8:	00 00 00 
	spin_lock_init(&fsm_core.lock);
    12ab:	c7 05 14 01 00 00 00 	movl   $0x0,0x114
    12b2:	00 00 00 
	fsm_core.tx_queue = (struct sk_buff_head*)fsm_mem_alloc(sizeof(struct sk_buff_head));
    12b5:	e8 fc ff ff ff       	call   12b6 <fsm_core_create+0x106>
    12ba:	a3 18 01 00 00       	mov    %eax,0x118
	fsm_core.rx_queue = (struct sk_buff_head*)fsm_mem_alloc(sizeof(struct sk_buff_head));
    12bf:	b8 10 00 00 00       	mov    $0x10,%eax
    12c4:	e8 fc ff ff ff       	call   12c5 <fsm_core_create+0x115>
    12c9:	a3 1c 01 00 00       	mov    %eax,0x11c
	fsm_core.tx_tsklt = (struct tasklet_struct*)fsm_mem_alloc(sizeof(struct tasklet_struct));
    12ce:	b8 14 00 00 00       	mov    $0x14,%eax
    12d3:	e8 fc ff ff ff       	call   12d4 <fsm_core_create+0x124>
    12d8:	a3 20 01 00 00       	mov    %eax,0x120
	fsm_core.rx_tsklt = (struct tasklet_struct*)fsm_mem_alloc(sizeof(struct tasklet_struct));
    12dd:	b8 14 00 00 00       	mov    $0x14,%eax
    12e2:	e8 fc ff ff ff       	call   12e3 <fsm_core_create+0x133>
    12e7:	a3 24 01 00 00       	mov    %eax,0x124
	fsm_core.do_ioctl_tsklt = (struct tasklet_struct*)fsm_mem_alloc(sizeof(struct tasklet_struct));
    12ec:	b8 14 00 00 00       	mov    $0x14,%eax
    12f1:	e8 fc ff ff ff       	call   12f2 <fsm_core_create+0x142>
	return; 
}
    12f6:	5d                   	pop    %ebp
	spin_lock_init(&fsm_core.lock);
	fsm_core.tx_queue = (struct sk_buff_head*)fsm_mem_alloc(sizeof(struct sk_buff_head));
	fsm_core.rx_queue = (struct sk_buff_head*)fsm_mem_alloc(sizeof(struct sk_buff_head));
	fsm_core.tx_tsklt = (struct tasklet_struct*)fsm_mem_alloc(sizeof(struct tasklet_struct));
	fsm_core.rx_tsklt = (struct tasklet_struct*)fsm_mem_alloc(sizeof(struct tasklet_struct));
	fsm_core.do_ioctl_tsklt = (struct tasklet_struct*)fsm_mem_alloc(sizeof(struct tasklet_struct));
    12f7:	a3 28 01 00 00       	mov    %eax,0x128
	return; 
}
    12fc:	c3                   	ret    
    12fd:	8d 76 00             	lea    0x0(%esi),%esi

00001300 <fsm_do_ioctrl>:
  fsm_mem_free(ifr_ptr);
  return result;
  }*/

int fsm_do_ioctrl(int strm_id, u32 cmd, void* data_ptr, size_t size)
{
    1300:	55                   	push   %ebp
    1301:	89 e5                	mov    %esp,%ebp
    1303:	83 ec 14             	sub    $0x14,%esp
    1306:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    1309:	89 75 f8             	mov    %esi,-0x8(%ebp)
    130c:	89 7d fc             	mov    %edi,-0x4(%ebp)
    130f:	e8 fc ff ff ff       	call   1310 <fsm_do_ioctrl+0x10>
    1314:	8b 7d 08             	mov    0x8(%ebp),%edi
	NETDEV*	 dev;
	struct evioctl* ev_ptr;
	dev = fsm_core.__intf[strm_id].dev;
    1317:	c1 e0 04             	shl    $0x4,%eax
  fsm_mem_free(ifr_ptr);
  return result;
  }*/

int fsm_do_ioctrl(int strm_id, u32 cmd, void* data_ptr, size_t size)
{
    131a:	89 d6                	mov    %edx,%esi
	NETDEV*	 dev;
	struct evioctl* ev_ptr;
	dev = fsm_core.__intf[strm_id].dev;
    131c:	8b 90 2c 00 00 00    	mov    0x2c(%eax),%edx
	ev_ptr = (struct evioctl*)fsm_mem_alloc(sizeof(struct evioctl));
    1322:	b8 18 00 00 00       	mov    $0x18,%eax
  fsm_mem_free(ifr_ptr);
  return result;
  }*/

int fsm_do_ioctrl(int strm_id, u32 cmd, void* data_ptr, size_t size)
{
    1327:	89 4d f0             	mov    %ecx,-0x10(%ebp)
	NETDEV*	 dev;
	struct evioctl* ev_ptr;
	dev = fsm_core.__intf[strm_id].dev;
	ev_ptr = (struct evioctl*)fsm_mem_alloc(sizeof(struct evioctl));
    132a:	89 55 ec             	mov    %edx,-0x14(%ebp)
    132d:	e8 fc ff ff ff       	call   132e <fsm_do_ioctrl+0x2e>
	ev_ptr->dev =dev;
    1332:	8b 55 ec             	mov    -0x14(%ebp),%edx
	ev_ptr->ifr.cmd = cmd;
	ev_ptr->ifr.size = size;
	if(data_ptr != NULL && size > 0)
    1335:	85 ff                	test   %edi,%edi
int fsm_do_ioctrl(int strm_id, u32 cmd, void* data_ptr, size_t size)
{
	NETDEV*	 dev;
	struct evioctl* ev_ptr;
	dev = fsm_core.__intf[strm_id].dev;
	ev_ptr = (struct evioctl*)fsm_mem_alloc(sizeof(struct evioctl));
    1337:	89 c3                	mov    %eax,%ebx
	ev_ptr->dev =dev;
    1339:	89 10                	mov    %edx,(%eax)
	ev_ptr->ifr.cmd = cmd;
    133b:	89 70 04             	mov    %esi,0x4(%eax)
	ev_ptr->ifr.size = size;
    133e:	89 78 08             	mov    %edi,0x8(%eax)
	if(data_ptr != NULL && size > 0)
    1341:	75 65                	jne    13a8 <fsm_do_ioctrl+0xa8>
		ev_ptr->ifr.buffer = fsm_mem_alloc(size);
		fsm_mem_cpy(ev_ptr->ifr.buffer, data_ptr, size);
	}
	else
	{
		ev_ptr->ifr.buffer = NULL;
    1343:	c7 43 0c 00 00 00 00 	movl   $0x0,0xc(%ebx)
	}
	spin_lock(&fsm_core.ioctl_list_lock);
    134a:	b8 3c 01 00 00       	mov    $0x13c,%eax
    134f:	e8 fc ff ff ff       	call   1350 <fsm_do_ioctrl+0x50>
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
    1354:	a1 38 01 00 00       	mov    0x138,%eax
	list_add_tail(&ev_ptr->list_node, &fsm_core.do_ioctl_list);
    1359:	8d 53 10             	lea    0x10(%ebx),%edx
#ifndef CONFIG_DEBUG_LIST
static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
    135c:	89 15 38 01 00 00    	mov    %edx,0x138
	new->next = next;
    1362:	c7 43 10 34 01 00 00 	movl   $0x134,0x10(%ebx)
	new->prev = prev;
    1369:	89 43 14             	mov    %eax,0x14(%ebx)
	prev->next = new;
    136c:	89 10                	mov    %edx,(%eax)
    136e:	b8 3c 01 00 00       	mov    $0x13c,%eax
    1373:	ff 15 14 00 00 00    	call   *0x14
	spin_unlock(&fsm_core.ioctl_list_lock);
	tasklet_schedule(fsm_core.do_ioctl_tsklt);
    1379:	a1 28 01 00 00       	mov    0x128,%eax
    137e:	f0 0f ba 68 04 00    	lock btsl $0x0,0x4(%eax)
    1384:	19 d2                	sbb    %edx,%edx

extern void __tasklet_schedule(struct tasklet_struct *t);

static inline void tasklet_schedule(struct tasklet_struct *t)
{
	if (!test_and_set_bit(TASKLET_STATE_SCHED, &t->state))
    1386:	85 d2                	test   %edx,%edx
    1388:	75 05                	jne    138f <fsm_do_ioctrl+0x8f>
		__tasklet_schedule(t);
    138a:	e8 fc ff ff ff       	call   138b <fsm_do_ioctrl+0x8b>
	return 1;
}
    138f:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    1392:	b8 01 00 00 00       	mov    $0x1,%eax
    1397:	8b 75 f8             	mov    -0x8(%ebp),%esi
    139a:	8b 7d fc             	mov    -0x4(%ebp),%edi
    139d:	89 ec                	mov    %ebp,%esp
    139f:	5d                   	pop    %ebp
    13a0:	c3                   	ret    
    13a1:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
	dev = fsm_core.__intf[strm_id].dev;
	ev_ptr = (struct evioctl*)fsm_mem_alloc(sizeof(struct evioctl));
	ev_ptr->dev =dev;
	ev_ptr->ifr.cmd = cmd;
	ev_ptr->ifr.size = size;
	if(data_ptr != NULL && size > 0)
    13a8:	8b 45 f0             	mov    -0x10(%ebp),%eax
    13ab:	85 c0                	test   %eax,%eax
    13ad:	74 94                	je     1343 <fsm_do_ioctrl+0x43>
	{
		ev_ptr->ifr.buffer = fsm_mem_alloc(size);
    13af:	89 f8                	mov    %edi,%eax
    13b1:	e8 fc ff ff ff       	call   13b2 <fsm_do_ioctrl+0xb2>
		fsm_mem_cpy(ev_ptr->ifr.buffer, data_ptr, size);
    13b6:	89 f9                	mov    %edi,%ecx
	ev_ptr->dev =dev;
	ev_ptr->ifr.cmd = cmd;
	ev_ptr->ifr.size = size;
	if(data_ptr != NULL && size > 0)
	{
		ev_ptr->ifr.buffer = fsm_mem_alloc(size);
    13b8:	89 43 0c             	mov    %eax,0xc(%ebx)
		fsm_mem_cpy(ev_ptr->ifr.buffer, data_ptr, size);
    13bb:	8b 55 f0             	mov    -0x10(%ebp),%edx
    13be:	e8 fc ff ff ff       	call   13bf <fsm_do_ioctrl+0xbf>
    13c3:	eb 85                	jmp    134a <fsm_do_ioctrl+0x4a>
    13c5:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    13c9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

000013d0 <fsm_ioctrl_arrival>:
	return 1;
}


int fsm_ioctrl_arrival(struct ifreq *ifr, int cmd)
{ 
    13d0:	55                   	push   %ebp
    13d1:	89 e5                	mov    %esp,%ebp
    13d3:	83 ec 28             	sub    $0x28,%esp
    13d6:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    13d9:	89 75 f8             	mov    %esi,-0x8(%ebp)
    13dc:	89 7d fc             	mov    %edi,-0x4(%ebp)
    13df:	e8 fc ff ff ff       	call   13e0 <fsm_ioctrl_arrival+0x10>
	struct kifreq* kifr_ptr;	
	struct ifreq* uifr_ptr; 
	struct kifreq kifr;
	void* buffer = NULL;
	if(cmd == IOCKERNEL)	
    13e4:	81 fa f0 89 00 00    	cmp    $0x89f0,%edx
	return 1;
}


int fsm_ioctrl_arrival(struct ifreq *ifr, int cmd)
{ 
    13ea:	89 c3                	mov    %eax,%ebx
	struct kifreq* kifr_ptr;	
	struct ifreq* uifr_ptr; 
	struct kifreq kifr;
	void* buffer = NULL;
	if(cmd == IOCKERNEL)	
    13ec:	0f 84 b6 00 00 00    	je     14a8 <fsm_ioctrl_arrival+0xd8>
		//			}
		spin_lock(&fsm_core.lock);
		__fsm_core_self_drive(FSM_EV_TYPE_CORE,FSM_EV_IOCTRL,NULL, KERNEL_MODULE,MAIN_PORT,kifr_ptr->buffer,kifr_ptr->cmd);
		spin_unlock(&fsm_core.lock);
	}	
	else if(cmd == IOCUSER)	
    13f2:	81 fa f1 89 00 00    	cmp    $0x89f1,%edx
    13f8:	74 16                	je     1410 <fsm_ioctrl_arrival+0x40>
		}		
		copy_to_user(uifr_ptr->ifr_ifru.ifru_data, kifr_ptr, sizeof(struct kifreq));
	}

	return 1;
}
    13fa:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    13fd:	b8 01 00 00 00       	mov    $0x1,%eax
    1402:	8b 75 f8             	mov    -0x8(%ebp),%esi
    1405:	8b 7d fc             	mov    -0x4(%ebp),%edi
    1408:	89 ec                	mov    %ebp,%esp
    140a:	5d                   	pop    %ebp
    140b:	c3                   	ret    
    140c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
		spin_unlock(&fsm_core.lock);
	}	
	else if(cmd == IOCUSER)	
	{		
		uifr_ptr = ifr;		
		copy_from_user(&kifr, uifr_ptr->ifr_ifru.ifru_data, sizeof(struct kifreq)); 	
    1410:	8b 50 10             	mov    0x10(%eax),%edx
    1413:	8d 7d e8             	lea    -0x18(%ebp),%edi
    1416:	b9 0c 00 00 00       	mov    $0xc,%ecx
    141b:	89 f8                	mov    %edi,%eax
    141d:	e8 fc ff ff ff       	call   141e <fsm_ioctrl_arrival+0x4e>
		kifr_ptr = &kifr;
		//fsm_printf("IOCUER:%d\n",kifr_ptr->cmd);//140923test
		//kifr_ptr->cmd=0x0B;
		//fsm_printf("IOCUER:%d\n",kifr_ptr->cmd);//140923test
		if(kifr_ptr->buffer)		
    1422:	8b 55 f0             	mov    -0x10(%ebp),%edx
    1425:	85 d2                	test   %edx,%edx
    1427:	0f 84 c3 00 00 00    	je     14f0 <fsm_ioctrl_arrival+0x120>
		{			
			buffer = fsm_mem_alloc(kifr_ptr->size); 		
    142d:	8b 45 ec             	mov    -0x14(%ebp),%eax
    1430:	e8 fc ff ff ff       	call   1431 <fsm_ioctrl_arrival+0x61>
			copy_from_user(buffer, kifr_ptr->buffer, kifr_ptr->size);	
    1435:	8b 4d ec             	mov    -0x14(%ebp),%ecx
    1438:	8b 55 f0             	mov    -0x10(%ebp),%edx
		//fsm_printf("IOCUER:%d\n",kifr_ptr->cmd);//140923test
		//kifr_ptr->cmd=0x0B;
		//fsm_printf("IOCUER:%d\n",kifr_ptr->cmd);//140923test
		if(kifr_ptr->buffer)		
		{			
			buffer = fsm_mem_alloc(kifr_ptr->size); 		
    143b:	89 c6                	mov    %eax,%esi
			copy_from_user(buffer, kifr_ptr->buffer, kifr_ptr->size);	
    143d:	e8 fc ff ff ff       	call   143e <fsm_ioctrl_arrival+0x6e>
			spin_lock(&fsm_core.lock);
    1442:	b8 14 01 00 00       	mov    $0x114,%eax
    1447:	e8 fc ff ff ff       	call   1448 <fsm_ioctrl_arrival+0x78>
			__fsm_core_self_drive(FSM_EV_TYPE_CORE,FSM_EV_IOCTRL,NULL, USER_SPACE, MAIN_PORT,buffer,kifr_ptr->cmd);
    144c:	8b 45 e8             	mov    -0x18(%ebp),%eax
    144f:	31 c9                	xor    %ecx,%ecx
    1451:	ba 02 00 00 00       	mov    $0x2,%edx
    1456:	89 44 24 0c          	mov    %eax,0xc(%esp)
    145a:	a1 ec 00 00 00       	mov    0xec,%eax
    145f:	89 74 24 08          	mov    %esi,0x8(%esp)
    1463:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
    146a:	89 44 24 04          	mov    %eax,0x4(%esp)
    146e:	b8 05 00 00 00       	mov    $0x5,%eax
    1473:	e8 78 f4 ff ff       	call   8f0 <__fsm_core_self_drive>
    1478:	b8 14 01 00 00       	mov    $0x114,%eax
    147d:	ff 15 14 00 00 00    	call   *0x14
			spin_unlock(&fsm_core.lock);
			copy_to_user(kifr_ptr->buffer, buffer, kifr_ptr->size); 		
    1483:	8b 4d ec             	mov    -0x14(%ebp),%ecx
    1486:	89 f2                	mov    %esi,%edx
    1488:	8b 45 f0             	mov    -0x10(%ebp),%eax
    148b:	e8 fc ff ff ff       	call   148c <fsm_ioctrl_arrival+0xbc>
		{
			spin_lock(&fsm_core.lock);			
			__fsm_core_self_drive(FSM_EV_TYPE_CORE,FSM_EV_IOCTRL,NULL, USER_SPACE, MAIN_PORT,NULL,kifr_ptr->cmd);
			spin_unlock(&fsm_core.lock);		
		}		
		copy_to_user(uifr_ptr->ifr_ifru.ifru_data, kifr_ptr, sizeof(struct kifreq));
    1490:	8b 43 10             	mov    0x10(%ebx),%eax
    1493:	b9 0c 00 00 00       	mov    $0xc,%ecx
    1498:	89 fa                	mov    %edi,%edx
    149a:	e8 fc ff ff ff       	call   149b <fsm_ioctrl_arrival+0xcb>
    149f:	e9 56 ff ff ff       	jmp    13fa <fsm_ioctrl_arrival+0x2a>
    14a4:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
		//		if(kifr_ptr->buffer)
		//			{
		//			buffer = fsm_mem_alloc(kifr_ptr->size);
		//			fsm_mem_cpy(buffer, kifr_ptr->buffer, kifr_ptr->size);
		//			}
		spin_lock(&fsm_core.lock);
    14a8:	b8 14 01 00 00       	mov    $0x114,%eax
    14ad:	e8 fc ff ff ff       	call   14ae <fsm_ioctrl_arrival+0xde>
		__fsm_core_self_drive(FSM_EV_TYPE_CORE,FSM_EV_IOCTRL,NULL, KERNEL_MODULE,MAIN_PORT,kifr_ptr->buffer,kifr_ptr->cmd);
    14b2:	8b 03                	mov    (%ebx),%eax
    14b4:	31 c9                	xor    %ecx,%ecx
    14b6:	ba 02 00 00 00       	mov    $0x2,%edx
    14bb:	89 44 24 0c          	mov    %eax,0xc(%esp)
    14bf:	8b 43 08             	mov    0x8(%ebx),%eax
    14c2:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
    14c9:	89 44 24 08          	mov    %eax,0x8(%esp)
    14cd:	a1 ec 00 00 00       	mov    0xec,%eax
    14d2:	89 44 24 04          	mov    %eax,0x4(%esp)
    14d6:	b8 05 00 00 00       	mov    $0x5,%eax
    14db:	e8 10 f4 ff ff       	call   8f0 <__fsm_core_self_drive>
    14e0:	b8 14 01 00 00       	mov    $0x114,%eax
    14e5:	ff 15 14 00 00 00    	call   *0x14
    14eb:	e9 0a ff ff ff       	jmp    13fa <fsm_ioctrl_arrival+0x2a>
			copy_to_user(kifr_ptr->buffer, buffer, kifr_ptr->size); 		
			//			fsm_mem_free(buffer);		
		}		
		else		
		{
			spin_lock(&fsm_core.lock);			
    14f0:	b8 14 01 00 00       	mov    $0x114,%eax
    14f5:	e8 fc ff ff ff       	call   14f6 <fsm_ioctrl_arrival+0x126>
			__fsm_core_self_drive(FSM_EV_TYPE_CORE,FSM_EV_IOCTRL,NULL, USER_SPACE, MAIN_PORT,NULL,kifr_ptr->cmd);
    14fa:	8b 45 e8             	mov    -0x18(%ebp),%eax
    14fd:	31 c9                	xor    %ecx,%ecx
    14ff:	ba 02 00 00 00       	mov    $0x2,%edx
    1504:	89 44 24 0c          	mov    %eax,0xc(%esp)
    1508:	a1 ec 00 00 00       	mov    0xec,%eax
    150d:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
    1514:	00 
    1515:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
    151c:	89 44 24 04          	mov    %eax,0x4(%esp)
    1520:	b8 05 00 00 00       	mov    $0x5,%eax
    1525:	e8 c6 f3 ff ff       	call   8f0 <__fsm_core_self_drive>
    152a:	b8 14 01 00 00       	mov    $0x114,%eax
    152f:	ff 15 14 00 00 00    	call   *0x14
    1535:	e9 56 ff ff ff       	jmp    1490 <fsm_ioctrl_arrival+0xc0>
    153a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00001540 <T.811>:
	}
	pE->pNext = p0;
	p1->pNext = pE;	
}

static evHandle __fsm_tm_ev_add(unsigned int delay, u32 type, u32 code, FSM_PKT* pkptr, int src, int dst, void* buffer)		// delay should be in 10us base
    1540:	55                   	push   %ebp
    1541:	89 e5                	mov    %esp,%ebp
    1543:	57                   	push   %edi
    1544:	56                   	push   %esi
    1545:	53                   	push   %ebx
    1546:	83 ec 20             	sub    $0x20,%esp
    1549:	e8 fc ff ff ff       	call   154a <T.811+0xa>
    154e:	89 c6                	mov    %eax,%esi
{
	__tmEvent* pE;
	pE = (__tmEvent*)fsm_mem_alloc(sizeof(__tmEvent));
    1550:	b8 2c 00 00 00       	mov    $0x2c,%eax
    1555:	89 4d dc             	mov    %ecx,-0x24(%ebp)
	}
	pE->pNext = p0;
	p1->pNext = pE;	
}

static evHandle __fsm_tm_ev_add(unsigned int delay, u32 type, u32 code, FSM_PKT* pkptr, int src, int dst, void* buffer)		// delay should be in 10us base
    1558:	89 d7                	mov    %edx,%edi
{
	__tmEvent* pE;
	pE = (__tmEvent*)fsm_mem_alloc(sizeof(__tmEvent));
    155a:	e8 fc ff ff ff       	call   155b <T.811+0x1b>
	if(pE)
    155f:	8b 4d dc             	mov    -0x24(%ebp),%ecx
}

static evHandle __fsm_tm_ev_add(unsigned int delay, u32 type, u32 code, FSM_PKT* pkptr, int src, int dst, void* buffer)		// delay should be in 10us base
{
	__tmEvent* pE;
	pE = (__tmEvent*)fsm_mem_alloc(sizeof(__tmEvent));
    1562:	89 c3                	mov    %eax,%ebx
	if(pE)
    1564:	31 c0                	xor    %eax,%eax
    1566:	85 db                	test   %ebx,%ebx
    1568:	0f 84 b2 00 00 00    	je     1620 <T.811+0xe0>
	{
		pE->evmask = EVMASK;
    156e:	c7 43 04 d6 96 0f 04 	movl   $0x40f96d6,0x4(%ebx)
		pE->delay = delay;
		pE->pkptr = pkptr;
		pE->src_id =src;
		pE->dst_id = dst;
		pE->buffer = buffer;
		if(delay == 0)
    1575:	85 f6                	test   %esi,%esi
	__tmEvent* pE;
	pE = (__tmEvent*)fsm_mem_alloc(sizeof(__tmEvent));
	if(pE)
	{
		pE->evmask = EVMASK;
		pE->pNext = 0;
    1577:	c7 03 00 00 00 00    	movl   $0x0,(%ebx)
		pE->type = type;
    157d:	89 7b 18             	mov    %edi,0x18(%ebx)
		pE->code = code;
    1580:	89 4b 14             	mov    %ecx,0x14(%ebx)
		pE->delay = delay;
    1583:	89 73 10             	mov    %esi,0x10(%ebx)
		pE->pkptr = pkptr;
    1586:	c7 43 1c 00 00 00 00 	movl   $0x0,0x1c(%ebx)
		pE->src_id =src;
    158d:	8b 45 08             	mov    0x8(%ebp),%eax
    1590:	89 43 24             	mov    %eax,0x24(%ebx)
		pE->dst_id = dst;
    1593:	8b 45 0c             	mov    0xc(%ebp),%eax
    1596:	89 43 20             	mov    %eax,0x20(%ebx)
		pE->buffer = buffer;
    1599:	8b 45 10             	mov    0x10(%ebp),%eax
    159c:	89 43 28             	mov    %eax,0x28(%ebx)
		if(delay == 0)
    159f:	0f 84 83 00 00 00    	je     1628 <T.811+0xe8>
			pE->expire = ktime_add_us(ktime_get(), 10);
		else
			pE->expire = ktime_add_us(ktime_get(), 10 * delay);
    15a5:	e8 fc ff ff ff       	call   15a6 <T.811+0x66>
    15aa:	89 55 f0             	mov    %edx,-0x10(%ebp)
       return ktime_to_us(ktime_sub(later, earlier));
}

static inline ktime_t ktime_add_us(const ktime_t kt, const u64 usec)
{
	return ktime_add_ns(kt, usec * 1000);
    15ad:	8d 14 b6             	lea    (%esi,%esi,4),%edx
    15b0:	be e8 03 00 00       	mov    $0x3e8,%esi
    15b5:	8d 0c 12             	lea    (%edx,%edx,1),%ecx
    15b8:	89 45 ec             	mov    %eax,-0x14(%ebp)
    15bb:	89 c8                	mov    %ecx,%eax
    15bd:	8b 4d f0             	mov    -0x10(%ebp),%ecx
    15c0:	f7 e6                	mul    %esi
    15c2:	89 55 e4             	mov    %edx,-0x1c(%ebp)
    15c5:	8b 55 ec             	mov    -0x14(%ebp),%edx
    15c8:	89 45 e0             	mov    %eax,-0x20(%ebp)
    15cb:	01 55 e0             	add    %edx,-0x20(%ebp)
    15ce:	11 4d e4             	adc    %ecx,-0x1c(%ebp)
    15d1:	8b 75 e0             	mov    -0x20(%ebp),%esi
    15d4:	8b 7d e4             	mov    -0x1c(%ebp),%edi
    15d7:	89 73 08             	mov    %esi,0x8(%ebx)
    15da:	89 7b 0c             	mov    %edi,0xc(%ebx)
{
	__tmEvent* p0;
	__tmEvent* p1;
	__tmBlock* pB;
	pB = TMBLOCK_PTR;;
	if(!pB->evQ || LATE_TIME(pE->expire,pB->evQ->expire))
    15dd:	a1 e8 00 00 00       	mov    0xe8,%eax
    15e2:	85 c0                	test   %eax,%eax
    15e4:	74 22                	je     1608 <T.811+0xc8>
    15e6:	8b 70 08             	mov    0x8(%eax),%esi
    15e9:	8b 78 0c             	mov    0xc(%eax),%edi
    15ec:	8b 53 08             	mov    0x8(%ebx),%edx
    15ef:	8b 4b 0c             	mov    0xc(%ebx),%ecx
    15f2:	89 55 e0             	mov    %edx,-0x20(%ebp)
    15f5:	89 f2                	mov    %esi,%edx
    15f7:	89 4d e4             	mov    %ecx,-0x1c(%ebp)
    15fa:	89 f9                	mov    %edi,%ecx
    15fc:	2b 55 e0             	sub    -0x20(%ebp),%edx
    15ff:	1b 4d e4             	sbb    -0x1c(%ebp),%ecx
    1602:	83 f9 00             	cmp    $0x0,%ecx
    1605:	7e 36                	jle    163d <T.811+0xfd>
    1607:	90                   	nop
	{
		pE->pNext = pB->evQ;
    1608:	89 03                	mov    %eax,(%ebx)
		pB->evQ = pE;
		if(pB->tm_state != FSM_TM_EXPIRE)
    160a:	83 3d a4 00 00 00 02 	cmpl   $0x2,0xa4
	__tmBlock* pB;
	pB = TMBLOCK_PTR;;
	if(!pB->evQ || LATE_TIME(pE->expire,pB->evQ->expire))
	{
		pE->pNext = pB->evQ;
		pB->evQ = pE;
    1611:	89 1d e8 00 00 00    	mov    %ebx,0xe8
		if(pB->tm_state != FSM_TM_EXPIRE)
    1617:	74 05                	je     161e <T.811+0xde>
		{
			__fsm_tm_restart();
    1619:	e8 12 ef ff ff       	call   530 <__fsm_tm_restart>
		if(delay == 0)
			pE->expire = ktime_add_us(ktime_get(), 10);
		else
			pE->expire = ktime_add_us(ktime_get(), 10 * delay);
		__fsm_tm_ev_insert(pE);
		return EVHANDLE(pE);
    161e:	89 d8                	mov    %ebx,%eax
	}
	return 0;
}
    1620:	83 c4 20             	add    $0x20,%esp
    1623:	5b                   	pop    %ebx
    1624:	5e                   	pop    %esi
    1625:	5f                   	pop    %edi
    1626:	5d                   	pop    %ebp
    1627:	c3                   	ret    
		pE->pkptr = pkptr;
		pE->src_id =src;
		pE->dst_id = dst;
		pE->buffer = buffer;
		if(delay == 0)
			pE->expire = ktime_add_us(ktime_get(), 10);
    1628:	e8 fc ff ff ff       	call   1629 <T.811+0xe9>
    162d:	05 10 27 00 00       	add    $0x2710,%eax
    1632:	83 d2 00             	adc    $0x0,%edx
    1635:	89 43 08             	mov    %eax,0x8(%ebx)
    1638:	89 53 0c             	mov    %edx,0xc(%ebx)
    163b:	eb a0                	jmp    15dd <T.811+0x9d>
{
	__tmEvent* p0;
	__tmEvent* p1;
	__tmBlock* pB;
	pB = TMBLOCK_PTR;;
	if(!pB->evQ || LATE_TIME(pE->expire,pB->evQ->expire))
    163d:	7d 4a                	jge    1689 <T.811+0x149>
    163f:	89 5d e8             	mov    %ebx,-0x18(%ebp)
    1642:	8b 4d e0             	mov    -0x20(%ebp),%ecx
    1645:	8b 5d e4             	mov    -0x1c(%ebp),%ebx
    1648:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
    164f:	89 75 d4             	mov    %esi,-0x2c(%ebp)
    1652:	89 7d d8             	mov    %edi,-0x28(%ebp)
    1655:	8d 76 00             	lea    0x0(%esi),%esi
			__fsm_tm_restart();
		}
		return;
	}
	p0 = pB->evQ;
	while(p0 && (LATE_TIME(p0->expire,pE->expire)||ktime_equal(p0->expire, pE->expire)))
    1658:	89 ce                	mov    %ecx,%esi
    165a:	89 df                	mov    %ebx,%edi
    165c:	2b 75 d4             	sub    -0x2c(%ebp),%esi
    165f:	1b 7d d8             	sbb    -0x28(%ebp),%edi
    1662:	89 75 e0             	mov    %esi,-0x20(%ebp)
    1665:	83 ff 00             	cmp    $0x0,%edi
    1668:	89 7d e4             	mov    %edi,-0x1c(%ebp)
    166b:	7e 2b                	jle    1698 <T.811+0x158>
    166d:	8d 76 00             	lea    0x0(%esi),%esi
	{
		p1 = p0;
		p0 = p0->pNext;
    1670:	8b 10                	mov    (%eax),%edx
			__fsm_tm_restart();
		}
		return;
	}
	p0 = pB->evQ;
	while(p0 && (LATE_TIME(p0->expire,pE->expire)||ktime_equal(p0->expire, pE->expire)))
    1672:	85 d2                	test   %edx,%edx
    1674:	74 5a                	je     16d0 <T.811+0x190>
    1676:	8b 72 08             	mov    0x8(%edx),%esi
    1679:	8b 7a 0c             	mov    0xc(%edx),%edi
    167c:	89 45 ec             	mov    %eax,-0x14(%ebp)
    167f:	89 d0                	mov    %edx,%eax
    1681:	89 75 d4             	mov    %esi,-0x2c(%ebp)
    1684:	89 7d d8             	mov    %edi,-0x28(%ebp)
    1687:	eb cf                	jmp    1658 <T.811+0x118>
{
	__tmEvent* p0;
	__tmEvent* p1;
	__tmBlock* pB;
	pB = TMBLOCK_PTR;;
	if(!pB->evQ || LATE_TIME(pE->expire,pB->evQ->expire))
    1689:	83 fa 00             	cmp    $0x0,%edx
    168c:	0f 87 76 ff ff ff    	ja     1608 <T.811+0xc8>
    1692:	eb ab                	jmp    163f <T.811+0xff>
    1694:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    1698:	90                   	nop
    1699:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
			__fsm_tm_restart();
		}
		return;
	}
	p0 = pB->evQ;
	while(p0 && (LATE_TIME(p0->expire,pE->expire)||ktime_equal(p0->expire, pE->expire)))
    16a0:	7d 1e                	jge    16c0 <T.811+0x180>
    16a2:	8b 7d e8             	mov    -0x18(%ebp),%edi
    16a5:	8b 57 08             	mov    0x8(%edi),%edx
    16a8:	8b 77 0c             	mov    0xc(%edi),%esi
    16ab:	33 70 0c             	xor    0xc(%eax),%esi
    16ae:	33 50 08             	xor    0x8(%eax),%edx
    16b1:	09 d6                	or     %edx,%esi
    16b3:	74 bb                	je     1670 <T.811+0x130>
    16b5:	89 fb                	mov    %edi,%ebx
    16b7:	eb 1f                	jmp    16d8 <T.811+0x198>
    16b9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    16c0:	83 fe 00             	cmp    $0x0,%esi
    16c3:	77 ab                	ja     1670 <T.811+0x130>
    16c5:	8d 76 00             	lea    0x0(%esi),%esi
    16c8:	eb d8                	jmp    16a2 <T.811+0x162>
    16ca:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    16d0:	8b 5d e8             	mov    -0x18(%ebp),%ebx
    16d3:	89 45 ec             	mov    %eax,-0x14(%ebp)
    16d6:	31 c0                	xor    %eax,%eax
	{
		p1 = p0;
		p0 = p0->pNext;
	}
	pE->pNext = p0;
    16d8:	89 03                	mov    %eax,(%ebx)
	p1->pNext = pE;	
    16da:	8b 45 ec             	mov    -0x14(%ebp),%eax
    16dd:	89 18                	mov    %ebx,(%eax)
		if(delay == 0)
			pE->expire = ktime_add_us(ktime_get(), 10);
		else
			pE->expire = ktime_add_us(ktime_get(), 10 * delay);
		__fsm_tm_ev_insert(pE);
		return EVHANDLE(pE);
    16df:	89 d8                	mov    %ebx,%eax
    16e1:	e9 3a ff ff ff       	jmp    1620 <T.811+0xe0>
    16e6:	8d 76 00             	lea    0x0(%esi),%esi
    16e9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

000016f0 <fsm_schedule_self>:
	return NTOHL(val);
}

/*  Event scheduling operation */
evHandle fsm_schedule_self(unsigned int delay, u32 code)
{
    16f0:	55                   	push   %ebp
    16f1:	89 e5                	mov    %esp,%ebp
    16f3:	53                   	push   %ebx
    16f4:	83 ec 0c             	sub    $0xc,%esp
    16f7:	e8 fc ff ff ff       	call   16f8 <fsm_schedule_self+0x8>
	return 	__fsm_tm_ev_add(delay, FSM_EV_TYPE_SELF, code, NULL, fsm_core.current_fsm, fsm_core.current_fsm, NULL);
    16fc:	8b 1d 00 00 00 00    	mov    0x0,%ebx
    1702:	89 d1                	mov    %edx,%ecx
    1704:	ba 03 00 00 00       	mov    $0x3,%edx
    1709:	89 5c 24 04          	mov    %ebx,0x4(%esp)
    170d:	89 1c 24             	mov    %ebx,(%esp)
    1710:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
    1717:	00 
    1718:	e8 23 fe ff ff       	call   1540 <T.811>
}
    171d:	83 c4 0c             	add    $0xc,%esp
    1720:	5b                   	pop    %ebx
    1721:	5d                   	pop    %ebp
    1722:	c3                   	ret    
    1723:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    1729:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00001730 <fsm_schedule_exfsm>:

evHandle fsm_schedule_exfsm(unsigned int delay, u32 code, int dst_id)
{
    1730:	55                   	push   %ebp
    1731:	89 e5                	mov    %esp,%ebp
    1733:	83 ec 0c             	sub    $0xc,%esp
    1736:	e8 fc ff ff ff       	call   1737 <fsm_schedule_exfsm+0x7>
	return 	__fsm_tm_ev_add(delay, FSM_EV_TYPE_EXFSM, code, NULL, fsm_core.current_fsm, dst_id, NULL);
    173b:	89 4c 24 04          	mov    %ecx,0x4(%esp)
    173f:	8b 0d 00 00 00 00    	mov    0x0,%ecx
    1745:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
    174c:	00 
    174d:	89 0c 24             	mov    %ecx,(%esp)
    1750:	89 d1                	mov    %edx,%ecx
    1752:	ba 04 00 00 00       	mov    $0x4,%edx
    1757:	e8 e4 fd ff ff       	call   1540 <T.811>
}
    175c:	c9                   	leave  
    175d:	c3                   	ret    
    175e:	66 90                	xchg   %ax,%ax

00001760 <fsm_post_msg>:

evHandle fsm_post_msg(u32 code , void* msg_ptr, int dst_id, size_t size)
{
    1760:	55                   	push   %ebp
    1761:	89 e5                	mov    %esp,%ebp
    1763:	83 ec 20             	sub    $0x20,%esp
    1766:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    1769:	89 75 f8             	mov    %esi,-0x8(%ebp)
    176c:	89 7d fc             	mov    %edi,-0x4(%ebp)
    176f:	e8 fc ff ff ff       	call   1770 <fsm_post_msg+0x10>
    1774:	89 cf                	mov    %ecx,%edi
    1776:	8b 4d 08             	mov    0x8(%ebp),%ecx
    1779:	89 d6                	mov    %edx,%esi
    177b:	89 45 f0             	mov    %eax,-0x10(%ebp)
	void* buffer;
	buffer = fsm_mem_alloc(size);
    177e:	89 c8                	mov    %ecx,%eax
    1780:	89 4d ec             	mov    %ecx,-0x14(%ebp)
    1783:	e8 fc ff ff ff       	call   1784 <fsm_post_msg+0x24>
	fsm_mem_cpy(buffer, msg_ptr, size);
    1788:	8b 4d ec             	mov    -0x14(%ebp),%ecx
    178b:	89 f2                	mov    %esi,%edx
}

evHandle fsm_post_msg(u32 code , void* msg_ptr, int dst_id, size_t size)
{
	void* buffer;
	buffer = fsm_mem_alloc(size);
    178d:	89 c3                	mov    %eax,%ebx
	fsm_mem_cpy(buffer, msg_ptr, size);
    178f:	e8 fc ff ff ff       	call   1790 <fsm_post_msg+0x30>
	return	__fsm_tm_ev_add(0, FSM_EV_TYPE_MSG, code, NULL, fsm_core.current_fsm, dst_id, buffer);
    1794:	a1 00 00 00 00       	mov    0x0,%eax
    1799:	ba 06 00 00 00       	mov    $0x6,%edx
    179e:	8b 4d f0             	mov    -0x10(%ebp),%ecx
    17a1:	89 04 24             	mov    %eax,(%esp)
    17a4:	31 c0                	xor    %eax,%eax
    17a6:	89 5c 24 08          	mov    %ebx,0x8(%esp)
    17aa:	89 7c 24 04          	mov    %edi,0x4(%esp)
    17ae:	e8 8d fd ff ff       	call   1540 <T.811>
}
    17b3:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    17b6:	8b 75 f8             	mov    -0x8(%ebp),%esi
    17b9:	8b 7d fc             	mov    -0x4(%ebp),%edi
    17bc:	89 ec                	mov    %ebp,%esp
    17be:	5d                   	pop    %ebp
    17bf:	c3                   	ret    

000017c0 <checkTimer>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int checkTimer(int timerNum)
{
    17c0:	55                   	push   %ebp
    17c1:	89 e5                	mov    %esp,%ebp
    17c3:	e8 fc ff ff ff       	call   17c4 <checkTimer+0x4>
	evHandle timerHandle;
	switch(timerNum)
    17c8:	2d 2c 01 00 00       	sub    $0x12c,%eax
    17cd:	83 f8 15             	cmp    $0x15,%eax
    17d0:	76 06                	jbe    17d8 <checkTimer+0x18>
    17d2:	31 c0                	xor    %eax,%eax
			return 0;
	}

	return (timerHandle == NULL ? 0 : 1);

}
    17d4:	5d                   	pop    %ebp
    17d5:	c3                   	ret    
    17d6:	66 90                	xchg   %ax,%ax
 ** Modified Date: 
 ******************************************************************************/
int checkTimer(int timerNum)
{
	evHandle timerHandle;
	switch(timerNum)
    17d8:	ff 24 85 00 00 00 00 	jmp    *0x0(,%eax,4)
    17df:	90                   	nop
	{
		case TIMER_T300:
			timerHandle = T300;
    17e0:	a1 8c 01 00 00       	mov    0x18c,%eax
    17e5:	8d 76 00             	lea    0x0(%esi),%esi
			break;
		default:
			return 0;
	}

	return (timerHandle == NULL ? 0 : 1);
    17e8:	85 c0                	test   %eax,%eax
    17ea:	0f 95 c0             	setne  %al
    17ed:	0f b6 c0             	movzbl %al,%eax

}
    17f0:	5d                   	pop    %ebp
    17f1:	c3                   	ret    
    17f2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	{
		case TIMER_T300:
			timerHandle = T300;
			break;
		case TIMER_T301:
			timerHandle = T301;
    17f8:	a1 90 01 00 00       	mov    0x190,%eax
			break;
    17fd:	eb e9                	jmp    17e8 <checkTimer+0x28>
    17ff:	90                   	nop
		case TIMER_T302:
			timerHandle = T302;
    1800:	a1 94 01 00 00       	mov    0x194,%eax
			break;
    1805:	eb e1                	jmp    17e8 <checkTimer+0x28>
    1807:	90                   	nop
		case TIMER_T305:
			timerHandle = T305;
    1808:	a1 98 01 00 00       	mov    0x198,%eax
			break;
    180d:	eb d9                	jmp    17e8 <checkTimer+0x28>
    180f:	90                   	nop
		case TIMER_T311:
			timerHandle = T311;
    1810:	a1 9c 01 00 00       	mov    0x19c,%eax
			break;
    1815:	eb d1                	jmp    17e8 <checkTimer+0x28>
    1817:	90                   	nop
		case TIMER_T320:
			timerHandle = T320;
    1818:	a1 a0 01 00 00       	mov    0x1a0,%eax
			break;
    181d:	eb c9                	jmp    17e8 <checkTimer+0x28>
    181f:	90                   	nop
		case TIMER_T321:
			timerHandle = T321;
    1820:	a1 a4 01 00 00       	mov    0x1a4,%eax
			break;
    1825:	eb c1                	jmp    17e8 <checkTimer+0x28>
    1827:	89 f6                	mov    %esi,%esi
    1829:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00001830 <check_free_ptr>:
	//fsm_pkt_send(pkptr, STRM_TO_IP);
	FOUT;
}

void check_free_ptr(void *ptr)
{
    1830:	55                   	push   %ebp
    1831:	89 e5                	mov    %esp,%ebp
    1833:	e8 fc ff ff ff       	call   1834 <check_free_ptr+0x4>
	if(ptr == NULL)
    1838:	85 c0                	test   %eax,%eax
    183a:	74 05                	je     1841 <check_free_ptr+0x11>
		return;
	fsm_mem_free(ptr);
    183c:	e8 fc ff ff ff       	call   183d <check_free_ptr+0xd>
	ptr = NULL;
}
    1841:	5d                   	pop    %ebp
    1842:	c3                   	ret    
    1843:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    1849:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00001850 <packet_send_to_upperlayer>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void packet_send_to_upperlayer(void)
{
    1850:	55                   	push   %ebp
    1851:	89 e5                	mov    %esp,%ebp
    1853:	83 ec 04             	sub    $0x4,%esp
    1856:	e8 fc ff ff ff       	call   1857 <packet_send_to_upperlayer+0x7>
	FSM_PKT* pkptr;
	FIN(packet_send_to_upperlayer());
	pkptr = fsm_pkt_get();
    185b:	e8 fc ff ff ff       	call   185c <packet_send_to_upperlayer+0xc>
	fsm_printf("[rrc] [fsm] <-- packet_send_to_upperlayer().\n");
    1860:	c7 04 24 38 00 00 00 	movl   $0x38,(%esp)
    1867:	e8 fc ff ff ff       	call   1868 <packet_send_to_upperlayer+0x18>

	//fsm_pkt_send(pkptr, STRM_TO_IP);
	FOUT;
}
    186c:	c9                   	leave  
    186d:	c3                   	ret    
    186e:	66 90                	xchg   %ax,%ax

00001870 <packet_send_to_rlc>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void packet_send_to_rlc(char *msg, int msg_len, unsigned int message_type)
{
    1870:	55                   	push   %ebp
    1871:	89 e5                	mov    %esp,%ebp
    1873:	57                   	push   %edi
    1874:	56                   	push   %esi
    1875:	53                   	push   %ebx
    1876:	83 ec 0c             	sub    $0xc,%esp
    1879:	e8 fc ff ff ff       	call   187a <packet_send_to_rlc+0xa>
    187e:	89 cb                	mov    %ecx,%ebx
    1880:	89 d7                	mov    %edx,%edi
    1882:	89 45 ec             	mov    %eax,-0x14(%ebp)

	FIN(packet_send_to_rlc());
	SV_PTR_GET(rrc_sv);
    1885:	e8 fc ff ff ff       	call   1886 <packet_send_to_rlc+0x16>
	fsm_printf("[rrc] [fsm] <-- packet_send_to_rlc().\n");
    188a:	c7 04 24 68 00 00 00 	movl   $0x68,(%esp)
    1891:	e8 fc ff ff ff       	call   1892 <packet_send_to_rlc+0x22>

	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr = (struct lte_rrc_head* ) fsm_mem_alloc(sizeof(struct lte_rrc_head));
    1896:	b8 04 00 00 00       	mov    $0x4,%eax
    189b:	e8 fc ff ff ff       	call   189c <packet_send_to_rlc+0x2c>
    18a0:	89 45 f0             	mov    %eax,-0x10(%ebp)
	struct URLC_IciMsg* ici_ptr = (struct URLC_IciMsg* ) fsm_mem_alloc(sizeof(struct URLC_IciMsg));
    18a3:	b8 02 00 00 00       	mov    $0x2,%eax
    18a8:	e8 fc ff ff ff       	call   18a9 <packet_send_to_rlc+0x39>

	sh_ptr->message_type = message_type;
	switch(message_type)
    18ad:	83 fb 05             	cmp    $0x5,%ebx
	SV_PTR_GET(rrc_sv);
	fsm_printf("[rrc] [fsm] <-- packet_send_to_rlc().\n");

	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr = (struct lte_rrc_head* ) fsm_mem_alloc(sizeof(struct lte_rrc_head));
	struct URLC_IciMsg* ici_ptr = (struct URLC_IciMsg* ) fsm_mem_alloc(sizeof(struct URLC_IciMsg));
    18b0:	89 c6                	mov    %eax,%esi

	sh_ptr->message_type = message_type;
    18b2:	8b 45 f0             	mov    -0x10(%ebp),%eax
    18b5:	89 18                	mov    %ebx,(%eax)
	switch(message_type)
    18b7:	0f 86 9b 00 00 00    	jbe    1958 <packet_send_to_rlc+0xe8>
		case 5:    //UL_CCCH
			ici_ptr->pbCh = 0;
			ici_ptr->rbId = 0;   //srb0   
			break;
		default:
			fsm_printf("[rrc] [fsm] packet_send_to_rlc:Unrecognized message_type.\n");
    18bd:	c7 04 24 90 00 00 00 	movl   $0x90,(%esp)
    18c4:	e8 fc ff ff ff       	call   18c5 <packet_send_to_rlc+0x55>
    18c9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
			break;
	}

	pkptr = fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head) + sizeof(struct URLC_IciMsg));
    18d0:	8d 47 06             	lea    0x6(%edi),%eax
    18d3:	e8 fc ff ff ff       	call   18d4 <packet_send_to_rlc+0x64>

	//ICI space
	fsm_skb_reserve(pkptr,sizeof(struct URLC_IciMsg));
    18d8:	ba 02 00 00 00       	mov    $0x2,%edx
		default:
			fsm_printf("[rrc] [fsm] packet_send_to_rlc:Unrecognized message_type.\n");
			break;
	}

	pkptr = fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head) + sizeof(struct URLC_IciMsg));
    18dd:	89 c3                	mov    %eax,%ebx

	//ICI space
	fsm_skb_reserve(pkptr,sizeof(struct URLC_IciMsg));
    18df:	e8 fc ff ff ff       	call   18e0 <packet_send_to_rlc+0x70>
	fsm_mem_cpy(pkptr->head, ici_ptr, sizeof(struct URLC_IciMsg));
    18e4:	8b 83 a8 00 00 00    	mov    0xa8(%ebx),%eax
    18ea:	b9 02 00 00 00       	mov    $0x2,%ecx
    18ef:	89 f2                	mov    %esi,%edx
    18f1:	e8 fc ff ff ff       	call   18f2 <packet_send_to_rlc+0x82>

	//lte rrc head
	fsm_skb_put(pkptr, sizeof(struct lte_rrc_head));
    18f6:	ba 04 00 00 00       	mov    $0x4,%edx
    18fb:	89 d8                	mov    %ebx,%eax
    18fd:	e8 fc ff ff ff       	call   18fe <packet_send_to_rlc+0x8e>
	fsm_mem_cpy(pkptr->data, sh_ptr, sizeof(struct lte_rrc_head));
    1902:	8b 55 f0             	mov    -0x10(%ebp),%edx
    1905:	b9 04 00 00 00       	mov    $0x4,%ecx
    190a:	8b 83 ac 00 00 00    	mov    0xac(%ebx),%eax
    1910:	e8 fc ff ff ff       	call   1911 <packet_send_to_rlc+0xa1>

	//data
	fsm_mem_cpy(pkptr->tail, msg, msg_len);
    1915:	8b 55 ec             	mov    -0x14(%ebp),%edx
    1918:	89 f9                	mov    %edi,%ecx
    191a:	8b 83 a0 00 00 00    	mov    0xa0(%ebx),%eax
    1920:	e8 fc ff ff ff       	call   1921 <packet_send_to_rlc+0xb1>
	fsm_skb_put(pkptr, msg_len);
    1925:	89 fa                	mov    %edi,%edx
    1927:	89 d8                	mov    %ebx,%eax
    1929:	e8 fc ff ff ff       	call   192a <packet_send_to_rlc+0xba>

	fsm_mem_free(sh_ptr);
    192e:	8b 45 f0             	mov    -0x10(%ebp),%eax
    1931:	e8 fc ff ff ff       	call   1932 <packet_send_to_rlc+0xc2>
	fsm_mem_free(ici_ptr);
    1936:	89 f0                	mov    %esi,%eax
    1938:	e8 fc ff ff ff       	call   1939 <packet_send_to_rlc+0xc9>

	fsm_pkt_send(pkptr,STRM_TO_RLC);
    193d:	89 d8                	mov    %ebx,%eax
    193f:	ba 01 00 00 00       	mov    $0x1,%edx
    1944:	e8 fc ff ff ff       	call   1945 <packet_send_to_rlc+0xd5>
	FOUT;
}
    1949:	83 c4 0c             	add    $0xc,%esp
    194c:	5b                   	pop    %ebx
    194d:	5e                   	pop    %esi
    194e:	5f                   	pop    %edi
    194f:	5d                   	pop    %ebp
    1950:	c3                   	ret    
    1951:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr = (struct lte_rrc_head* ) fsm_mem_alloc(sizeof(struct lte_rrc_head));
	struct URLC_IciMsg* ici_ptr = (struct URLC_IciMsg* ) fsm_mem_alloc(sizeof(struct URLC_IciMsg));

	sh_ptr->message_type = message_type;
	switch(message_type)
    1958:	ff 24 9d 58 00 00 00 	jmp    *0x58(,%ebx,4)
    195f:	90                   	nop
			break;
		case 1: 	//BCCH
			ici_ptr->pbCh = 2;
			break;
		case 2:     //BCCH_DL_SCH
			ici_ptr->pbCh = 2;
    1960:	c6 06 02             	movb   $0x2,(%esi)
			break;
    1963:	e9 68 ff ff ff       	jmp    18d0 <packet_send_to_rlc+0x60>
		case 3:    //DL_CCCH
			ici_ptr->pbCh = 0;
			ici_ptr->rbId = 0;   //srb0   
			break;
		case 5:    //UL_CCCH
			ici_ptr->pbCh = 0;
    1968:	c6 06 00             	movb   $0x0,(%esi)
			ici_ptr->rbId = 0;   //srb0   
    196b:	c6 46 01 00          	movb   $0x0,0x1(%esi)
    196f:	90                   	nop
			break;
    1970:	e9 5b ff ff ff       	jmp    18d0 <packet_send_to_rlc+0x60>
    1975:	8d 76 00             	lea    0x0(%esi),%esi

	sh_ptr->message_type = message_type;
	switch(message_type)
	{
		case 0:      //PCCH
			ici_ptr->pbCh = 1;
    1978:	c6 06 01             	movb   $0x1,(%esi)
			break;
    197b:	e9 50 ff ff ff       	jmp    18d0 <packet_send_to_rlc+0x60>

00001980 <packet_send_to_pdcp>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void packet_send_to_pdcp(char *msg, int msg_len, unsigned int message_type)
{
    1980:	55                   	push   %ebp
    1981:	89 e5                	mov    %esp,%ebp
    1983:	57                   	push   %edi
    1984:	56                   	push   %esi
    1985:	53                   	push   %ebx
    1986:	83 ec 0c             	sub    $0xc,%esp
    1989:	e8 fc ff ff ff       	call   198a <packet_send_to_pdcp+0xa>
    198e:	89 cb                	mov    %ecx,%ebx
    1990:	89 55 f0             	mov    %edx,-0x10(%ebp)
    1993:	89 45 ec             	mov    %eax,-0x14(%ebp)

	FIN(packet_send_to_pdcp());
	SV_PTR_GET(rrc_sv);
    1996:	e8 fc ff ff ff       	call   1997 <packet_send_to_pdcp+0x17>
	fsm_printf("[rrc] [fsm] <-- packet_send_to_pdcp().\n");
    199b:	c7 04 24 cc 00 00 00 	movl   $0xcc,(%esp)
    19a2:	e8 fc ff ff ff       	call   19a3 <packet_send_to_pdcp+0x23>

	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr = (struct lte_rrc_head* ) fsm_mem_alloc(sizeof(struct lte_rrc_head));
    19a7:	b8 04 00 00 00       	mov    $0x4,%eax
    19ac:	e8 fc ff ff ff       	call   19ad <packet_send_to_pdcp+0x2d>
    19b1:	89 c7                	mov    %eax,%edi
	struct UPDCP_IciMsg* ici_ptr = (struct UPDCP_IciMsg* ) fsm_mem_alloc(sizeof(struct UPDCP_IciMsg));
    19b3:	b8 02 00 00 00       	mov    $0x2,%eax
    19b8:	e8 fc ff ff ff       	call   19b9 <packet_send_to_pdcp+0x39>

	sh_ptr->message_type = message_type;
	switch(message_type)
    19bd:	83 fb 04             	cmp    $0x4,%ebx

	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr = (struct lte_rrc_head* ) fsm_mem_alloc(sizeof(struct lte_rrc_head));
	struct UPDCP_IciMsg* ici_ptr = (struct UPDCP_IciMsg* ) fsm_mem_alloc(sizeof(struct UPDCP_IciMsg));

	sh_ptr->message_type = message_type;
    19c0:	89 1f                	mov    %ebx,(%edi)
	SV_PTR_GET(rrc_sv);
	fsm_printf("[rrc] [fsm] <-- packet_send_to_pdcp().\n");

	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr = (struct lte_rrc_head* ) fsm_mem_alloc(sizeof(struct lte_rrc_head));
	struct UPDCP_IciMsg* ici_ptr = (struct UPDCP_IciMsg* ) fsm_mem_alloc(sizeof(struct UPDCP_IciMsg));
    19c2:	89 c6                	mov    %eax,%esi

	sh_ptr->message_type = message_type;
	switch(message_type)
    19c4:	0f 84 9e 00 00 00    	je     1a68 <packet_send_to_pdcp+0xe8>
    19ca:	83 fb 06             	cmp    $0x6,%ebx
    19cd:	0f 84 95 00 00 00    	je     1a68 <packet_send_to_pdcp+0xe8>
		case 6:
			ici_ptr->pbCh = 0;
			ici_ptr->rbId = 1;       //DL_DCCH_Message(SRB1)
			break;
		default:
			fsm_printf("[rrc] [fsm] packet_send_to_pdcp:Unrecognized message_type.\n");
    19d3:	c7 04 24 f4 00 00 00 	movl   $0xf4,(%esp)
    19da:	e8 fc ff ff ff       	call   19db <packet_send_to_pdcp+0x5b>
			break;
	}

	pkptr = fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head) + sizeof(struct UPDCP_IciMsg) + 10);
    19df:	8b 45 f0             	mov    -0x10(%ebp),%eax
    19e2:	83 c0 10             	add    $0x10,%eax
    19e5:	e8 fc ff ff ff       	call   19e6 <packet_send_to_pdcp+0x66>

	//ICI space
	fsm_skb_reserve(pkptr,sizeof(struct UPDCP_IciMsg));
    19ea:	ba 02 00 00 00       	mov    $0x2,%edx
		default:
			fsm_printf("[rrc] [fsm] packet_send_to_pdcp:Unrecognized message_type.\n");
			break;
	}

	pkptr = fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head) + sizeof(struct UPDCP_IciMsg) + 10);
    19ef:	89 c3                	mov    %eax,%ebx

	//ICI space
	fsm_skb_reserve(pkptr,sizeof(struct UPDCP_IciMsg));
    19f1:	e8 fc ff ff ff       	call   19f2 <packet_send_to_pdcp+0x72>
	fsm_mem_cpy(pkptr->head, ici_ptr, sizeof(struct UPDCP_IciMsg));
    19f6:	8b 83 a8 00 00 00    	mov    0xa8(%ebx),%eax
    19fc:	b9 02 00 00 00       	mov    $0x2,%ecx
    1a01:	89 f2                	mov    %esi,%edx
    1a03:	e8 fc ff ff ff       	call   1a04 <packet_send_to_pdcp+0x84>

	//lte rrc head
	fsm_skb_put(pkptr, sizeof(struct lte_rrc_head));
    1a08:	ba 04 00 00 00       	mov    $0x4,%edx
    1a0d:	89 d8                	mov    %ebx,%eax
    1a0f:	e8 fc ff ff ff       	call   1a10 <packet_send_to_pdcp+0x90>
	fsm_mem_cpy(pkptr->data, sh_ptr, sizeof(struct lte_rrc_head));
    1a14:	8b 83 ac 00 00 00    	mov    0xac(%ebx),%eax
    1a1a:	89 fa                	mov    %edi,%edx
    1a1c:	b9 04 00 00 00       	mov    $0x4,%ecx
    1a21:	e8 fc ff ff ff       	call   1a22 <packet_send_to_pdcp+0xa2>

	//data
	fsm_mem_cpy(pkptr->tail, msg, msg_len);
    1a26:	8b 4d f0             	mov    -0x10(%ebp),%ecx
    1a29:	8b 55 ec             	mov    -0x14(%ebp),%edx
    1a2c:	8b 83 a0 00 00 00    	mov    0xa0(%ebx),%eax
    1a32:	e8 fc ff ff ff       	call   1a33 <packet_send_to_pdcp+0xb3>
	fsm_skb_put(pkptr, msg_len);
    1a37:	8b 55 f0             	mov    -0x10(%ebp),%edx
    1a3a:	89 d8                	mov    %ebx,%eax
    1a3c:	e8 fc ff ff ff       	call   1a3d <packet_send_to_pdcp+0xbd>

	fsm_mem_free(sh_ptr);
    1a41:	89 f8                	mov    %edi,%eax
    1a43:	e8 fc ff ff ff       	call   1a44 <packet_send_to_pdcp+0xc4>
	fsm_mem_free(ici_ptr);
    1a48:	89 f0                	mov    %esi,%eax
    1a4a:	e8 fc ff ff ff       	call   1a4b <packet_send_to_pdcp+0xcb>

//	fsm_pkt_send(pkptr,STRM_TO_PDCP);
	fsm_pkt_send(pkptr,STRM_TO_RLC);
    1a4f:	89 d8                	mov    %ebx,%eax
    1a51:	ba 01 00 00 00       	mov    $0x1,%edx
    1a56:	e8 fc ff ff ff       	call   1a57 <packet_send_to_pdcp+0xd7>
	FOUT;

}
    1a5b:	83 c4 0c             	add    $0xc,%esp
    1a5e:	5b                   	pop    %ebx
    1a5f:	5e                   	pop    %esi
    1a60:	5f                   	pop    %edi
    1a61:	5d                   	pop    %ebp
    1a62:	c3                   	ret    
    1a63:	90                   	nop
    1a64:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
		case 4:
			ici_ptr->pbCh = 0;
			ici_ptr->rbId = 1;       //UL_DCCH_Message(SRB1)
			break;
		case 6:
			ici_ptr->pbCh = 0;
    1a68:	c6 06 00             	movb   $0x0,(%esi)
			ici_ptr->rbId = 1;       //DL_DCCH_Message(SRB1)
    1a6b:	c6 46 01 01          	movb   $0x1,0x1(%esi)
			break;
    1a6f:	e9 6b ff ff ff       	jmp    19df <packet_send_to_pdcp+0x5f>
    1a74:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    1a7a:	8d bf 00 00 00 00    	lea    0x0(%edi),%edi

00001a80 <cancleTimer>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void cancleTimer(int timerNum)
{
    1a80:	55                   	push   %ebp
    1a81:	89 e5                	mov    %esp,%ebp
    1a83:	53                   	push   %ebx
    1a84:	83 ec 08             	sub    $0x8,%esp
    1a87:	e8 fc ff ff ff       	call   1a88 <cancleTimer+0x8>
    1a8c:	89 c3                	mov    %eax,%ebx
	FIN(cancleTimer());
	fsm_printf("[rrc] [fsm] cancleTimer(%d).\n",timerNum);
	switch(timerNum)
    1a8e:	81 eb 2c 01 00 00    	sub    $0x12c,%ebx
 ** Modified Date: 
 ******************************************************************************/
void cancleTimer(int timerNum)
{
	FIN(cancleTimer());
	fsm_printf("[rrc] [fsm] cancleTimer(%d).\n",timerNum);
    1a94:	89 44 24 04          	mov    %eax,0x4(%esp)
    1a98:	c7 04 24 4f 00 00 00 	movl   $0x4f,(%esp)
    1a9f:	e8 fc ff ff ff       	call   1aa0 <cancleTimer+0x20>
	switch(timerNum)
    1aa4:	83 fb 15             	cmp    $0x15,%ebx
    1aa7:	77 1f                	ja     1ac8 <cancleTimer+0x48>
    1aa9:	ff 24 9d 70 00 00 00 	jmp    *0x70(,%ebx,4)
			if (T320 != NULL)
				fsm_schedule_cancel(T320);
			T320 = NULL;
			FOUT;
		case TIMER_T321:
			if (T321 != NULL)
    1ab0:	a1 a4 01 00 00       	mov    0x1a4,%eax
    1ab5:	85 c0                	test   %eax,%eax
    1ab7:	74 05                	je     1abe <cancleTimer+0x3e>
				fsm_schedule_cancel(T321);
    1ab9:	e8 fc ff ff ff       	call   1aba <cancleTimer+0x3a>
			T321 = NULL;
    1abe:	c7 05 a4 01 00 00 00 	movl   $0x0,0x1a4
    1ac5:	00 00 00 
			FOUT;
		default:
			FOUT;
	}
}
    1ac8:	83 c4 08             	add    $0x8,%esp
    1acb:	5b                   	pop    %ebx
    1acc:	5d                   	pop    %ebp
    1acd:	c3                   	ret    
    1ace:	66 90                	xchg   %ax,%ax
	FIN(cancleTimer());
	fsm_printf("[rrc] [fsm] cancleTimer(%d).\n",timerNum);
	switch(timerNum)
	{
		case TIMER_T300:
			if (T300 != NULL)
    1ad0:	a1 8c 01 00 00       	mov    0x18c,%eax
    1ad5:	85 c0                	test   %eax,%eax
    1ad7:	74 05                	je     1ade <cancleTimer+0x5e>
				fsm_schedule_cancel(T300);
    1ad9:	e8 fc ff ff ff       	call   1ada <cancleTimer+0x5a>
			T300 = NULL;
    1ade:	c7 05 8c 01 00 00 00 	movl   $0x0,0x18c
    1ae5:	00 00 00 
			T321 = NULL;
			FOUT;
		default:
			FOUT;
	}
}
    1ae8:	83 c4 08             	add    $0x8,%esp
    1aeb:	5b                   	pop    %ebx
    1aec:	5d                   	pop    %ebp
    1aed:	c3                   	ret    
    1aee:	66 90                	xchg   %ax,%ax
			if (T300 != NULL)
				fsm_schedule_cancel(T300);
			T300 = NULL;
			FOUT;
		case TIMER_T301:
			if (T301 != NULL)
    1af0:	a1 90 01 00 00       	mov    0x190,%eax
    1af5:	85 c0                	test   %eax,%eax
    1af7:	74 05                	je     1afe <cancleTimer+0x7e>
				fsm_schedule_cancel(T301);
    1af9:	e8 fc ff ff ff       	call   1afa <cancleTimer+0x7a>
			T301 = NULL;
    1afe:	c7 05 90 01 00 00 00 	movl   $0x0,0x190
    1b05:	00 00 00 
			T321 = NULL;
			FOUT;
		default:
			FOUT;
	}
}
    1b08:	83 c4 08             	add    $0x8,%esp
    1b0b:	5b                   	pop    %ebx
    1b0c:	5d                   	pop    %ebp
    1b0d:	c3                   	ret    
    1b0e:	66 90                	xchg   %ax,%ax
			if (T301 != NULL)
				fsm_schedule_cancel(T301);
			T301 = NULL;
			FOUT;
		case TIMER_T302:
			if (T302 != NULL)
    1b10:	a1 94 01 00 00       	mov    0x194,%eax
    1b15:	85 c0                	test   %eax,%eax
    1b17:	74 05                	je     1b1e <cancleTimer+0x9e>
				fsm_schedule_cancel(T302);
    1b19:	e8 fc ff ff ff       	call   1b1a <cancleTimer+0x9a>
			T302 = NULL;
    1b1e:	c7 05 94 01 00 00 00 	movl   $0x0,0x194
    1b25:	00 00 00 
			T321 = NULL;
			FOUT;
		default:
			FOUT;
	}
}
    1b28:	83 c4 08             	add    $0x8,%esp
    1b2b:	5b                   	pop    %ebx
    1b2c:	5d                   	pop    %ebp
    1b2d:	c3                   	ret    
    1b2e:	66 90                	xchg   %ax,%ax
			if (T302 != NULL)
				fsm_schedule_cancel(T302);
			T302 = NULL;
			FOUT;
		case TIMER_T305:
			if (T305 != NULL)
    1b30:	a1 98 01 00 00       	mov    0x198,%eax
    1b35:	85 c0                	test   %eax,%eax
    1b37:	74 05                	je     1b3e <cancleTimer+0xbe>
				fsm_schedule_cancel(T305);
    1b39:	e8 fc ff ff ff       	call   1b3a <cancleTimer+0xba>
			T305 = NULL;
    1b3e:	c7 05 98 01 00 00 00 	movl   $0x0,0x198
    1b45:	00 00 00 
			T321 = NULL;
			FOUT;
		default:
			FOUT;
	}
}
    1b48:	83 c4 08             	add    $0x8,%esp
    1b4b:	5b                   	pop    %ebx
    1b4c:	5d                   	pop    %ebp
    1b4d:	c3                   	ret    
    1b4e:	66 90                	xchg   %ax,%ax
			if (T305 != NULL)
				fsm_schedule_cancel(T305);
			T305 = NULL;
			FOUT;
		case TIMER_T311:
			if (T311 != NULL)
    1b50:	a1 9c 01 00 00       	mov    0x19c,%eax
    1b55:	85 c0                	test   %eax,%eax
    1b57:	74 05                	je     1b5e <cancleTimer+0xde>
				fsm_schedule_cancel(T311);
    1b59:	e8 fc ff ff ff       	call   1b5a <cancleTimer+0xda>
			T311 = NULL;
    1b5e:	c7 05 9c 01 00 00 00 	movl   $0x0,0x19c
    1b65:	00 00 00 
			T321 = NULL;
			FOUT;
		default:
			FOUT;
	}
}
    1b68:	83 c4 08             	add    $0x8,%esp
    1b6b:	5b                   	pop    %ebx
    1b6c:	5d                   	pop    %ebp
    1b6d:	c3                   	ret    
    1b6e:	66 90                	xchg   %ax,%ax
			if (T311 != NULL)
				fsm_schedule_cancel(T311);
			T311 = NULL;
			FOUT;
		case TIMER_T320:
			if (T320 != NULL)
    1b70:	a1 a0 01 00 00       	mov    0x1a0,%eax
    1b75:	85 c0                	test   %eax,%eax
    1b77:	74 05                	je     1b7e <cancleTimer+0xfe>
				fsm_schedule_cancel(T320);
    1b79:	e8 fc ff ff ff       	call   1b7a <cancleTimer+0xfa>
			T320 = NULL;
    1b7e:	c7 05 a0 01 00 00 00 	movl   $0x0,0x1a0
    1b85:	00 00 00 
			T321 = NULL;
			FOUT;
		default:
			FOUT;
	}
}
    1b88:	83 c4 08             	add    $0x8,%esp
    1b8b:	5b                   	pop    %ebx
    1b8c:	5d                   	pop    %ebp
    1b8d:	c3                   	ret    
    1b8e:	66 90                	xchg   %ax,%ax

00001b90 <setTimer>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void setTimer(int timerNum, unsigned int delay)
{
    1b90:	55                   	push   %ebp
    1b91:	89 e5                	mov    %esp,%ebp
    1b93:	83 ec 14             	sub    $0x14,%esp
    1b96:	89 5d f8             	mov    %ebx,-0x8(%ebp)
    1b99:	89 75 fc             	mov    %esi,-0x4(%ebp)
    1b9c:	e8 fc ff ff ff       	call   1b9d <setTimer+0xd>
    1ba1:	89 c3                	mov    %eax,%ebx
    1ba3:	89 d6                	mov    %edx,%esi
	FIN(setTimer());
	fsm_printf("[rrc] [fsm] setTimer(%d,%u).\n",timerNum,delay);
    1ba5:	89 54 24 08          	mov    %edx,0x8(%esp)
	switch(timerNum)
    1ba9:	81 eb 2c 01 00 00    	sub    $0x12c,%ebx
 ** Modified Date: 
 ******************************************************************************/
void setTimer(int timerNum, unsigned int delay)
{
	FIN(setTimer());
	fsm_printf("[rrc] [fsm] setTimer(%d,%u).\n",timerNum,delay);
    1baf:	89 44 24 04          	mov    %eax,0x4(%esp)
    1bb3:	c7 04 24 6d 00 00 00 	movl   $0x6d,(%esp)
    1bba:	e8 fc ff ff ff       	call   1bbb <setTimer+0x2b>
	switch(timerNum)
    1bbf:	83 fb 15             	cmp    $0x15,%ebx
    1bc2:	77 24                	ja     1be8 <setTimer+0x58>
    1bc4:	ff 24 9d c8 00 00 00 	jmp    *0xc8(,%ebx,4)
    1bcb:	90                   	nop
    1bcc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			FOUT;
		case TIMER_T320:
			T320 = fsm_schedule_self(delay, CODE_TIMEOUT_T320);
			FOUT;
		case TIMER_T321:
			T321 = fsm_schedule_self(delay, CODE_TIMEOUT_T321);
    1bd0:	ba 15 00 00 00       	mov    $0x15,%edx
    1bd5:	89 f0                	mov    %esi,%eax
    1bd7:	e8 fc ff ff ff       	call   1bd8 <setTimer+0x48>
    1bdc:	a3 a4 01 00 00       	mov    %eax,0x1a4
    1be1:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
			FOUT;

		default:
			FOUT;
	}
}
    1be8:	8b 5d f8             	mov    -0x8(%ebp),%ebx
    1beb:	8b 75 fc             	mov    -0x4(%ebp),%esi
    1bee:	89 ec                	mov    %ebp,%esp
    1bf0:	5d                   	pop    %ebp
    1bf1:	c3                   	ret    
    1bf2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	FIN(setTimer());
	fsm_printf("[rrc] [fsm] setTimer(%d,%u).\n",timerNum,delay);
	switch(timerNum)
	{
		case TIMER_T300:
			T300 = fsm_schedule_self(delay, CODE_TIMEOUT_T300);
    1bf8:	89 f0                	mov    %esi,%eax
    1bfa:	ba 03 00 00 00       	mov    $0x3,%edx
    1bff:	e8 fc ff ff ff       	call   1c00 <setTimer+0x70>
    1c04:	a3 8c 01 00 00       	mov    %eax,0x18c
			FOUT;

		default:
			FOUT;
	}
}
    1c09:	8b 5d f8             	mov    -0x8(%ebp),%ebx
    1c0c:	8b 75 fc             	mov    -0x4(%ebp),%esi
    1c0f:	89 ec                	mov    %ebp,%esp
    1c11:	5d                   	pop    %ebp
    1c12:	c3                   	ret    
    1c13:	90                   	nop
    1c14:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
	{
		case TIMER_T300:
			T300 = fsm_schedule_self(delay, CODE_TIMEOUT_T300);
			FOUT;
		case TIMER_T301:
			T301 = fsm_schedule_self(delay, CODE_TIMEOUT_T301);
    1c18:	89 f0                	mov    %esi,%eax
    1c1a:	ba 0c 00 00 00       	mov    $0xc,%edx
    1c1f:	e8 fc ff ff ff       	call   1c20 <setTimer+0x90>
    1c24:	a3 90 01 00 00       	mov    %eax,0x190
			FOUT;

		default:
			FOUT;
	}
}
    1c29:	8b 5d f8             	mov    -0x8(%ebp),%ebx
    1c2c:	8b 75 fc             	mov    -0x4(%ebp),%esi
    1c2f:	89 ec                	mov    %ebp,%esp
    1c31:	5d                   	pop    %ebp
    1c32:	c3                   	ret    
    1c33:	90                   	nop
    1c34:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			FOUT;
		case TIMER_T301:
			T301 = fsm_schedule_self(delay, CODE_TIMEOUT_T301);
			FOUT;
		case TIMER_T302:
			T302 = fsm_schedule_self(delay, CODE_TIMEOUT_T302);
    1c38:	89 f0                	mov    %esi,%eax
    1c3a:	ba 12 00 00 00       	mov    $0x12,%edx
    1c3f:	e8 fc ff ff ff       	call   1c40 <setTimer+0xb0>
    1c44:	a3 94 01 00 00       	mov    %eax,0x194
			FOUT;

		default:
			FOUT;
	}
}
    1c49:	8b 5d f8             	mov    -0x8(%ebp),%ebx
    1c4c:	8b 75 fc             	mov    -0x4(%ebp),%esi
    1c4f:	89 ec                	mov    %ebp,%esp
    1c51:	5d                   	pop    %ebp
    1c52:	c3                   	ret    
    1c53:	90                   	nop
    1c54:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			FOUT;
		case TIMER_T302:
			T302 = fsm_schedule_self(delay, CODE_TIMEOUT_T302);
			FOUT;
		case TIMER_T305:
			T305 = fsm_schedule_self(delay, CODE_TIMEOUT_T305);
    1c58:	89 f0                	mov    %esi,%eax
    1c5a:	ba 13 00 00 00       	mov    $0x13,%edx
    1c5f:	e8 fc ff ff ff       	call   1c60 <setTimer+0xd0>
    1c64:	a3 98 01 00 00       	mov    %eax,0x198
			FOUT;

		default:
			FOUT;
	}
}
    1c69:	8b 5d f8             	mov    -0x8(%ebp),%ebx
    1c6c:	8b 75 fc             	mov    -0x4(%ebp),%esi
    1c6f:	89 ec                	mov    %ebp,%esp
    1c71:	5d                   	pop    %ebp
    1c72:	c3                   	ret    
    1c73:	90                   	nop
    1c74:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			FOUT;
		case TIMER_T305:
			T305 = fsm_schedule_self(delay, CODE_TIMEOUT_T305);
			FOUT;
		case TIMER_T311:
			T311 = fsm_schedule_self(delay, CODE_TIMEOUT_T311);
    1c78:	89 f0                	mov    %esi,%eax
    1c7a:	ba 0d 00 00 00       	mov    $0xd,%edx
    1c7f:	e8 fc ff ff ff       	call   1c80 <setTimer+0xf0>
    1c84:	a3 9c 01 00 00       	mov    %eax,0x19c
			FOUT;

		default:
			FOUT;
	}
}
    1c89:	8b 5d f8             	mov    -0x8(%ebp),%ebx
    1c8c:	8b 75 fc             	mov    -0x4(%ebp),%esi
    1c8f:	89 ec                	mov    %ebp,%esp
    1c91:	5d                   	pop    %ebp
    1c92:	c3                   	ret    
    1c93:	90                   	nop
    1c94:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			FOUT;
		case TIMER_T311:
			T311 = fsm_schedule_self(delay, CODE_TIMEOUT_T311);
			FOUT;
		case TIMER_T320:
			T320 = fsm_schedule_self(delay, CODE_TIMEOUT_T320);
    1c98:	89 f0                	mov    %esi,%eax
    1c9a:	ba 14 00 00 00       	mov    $0x14,%edx
    1c9f:	e8 fc ff ff ff       	call   1ca0 <setTimer+0x110>
    1ca4:	a3 a0 01 00 00       	mov    %eax,0x1a0
			FOUT;

		default:
			FOUT;
	}
}
    1ca9:	8b 5d f8             	mov    -0x8(%ebp),%ebx
    1cac:	8b 75 fc             	mov    -0x4(%ebp),%esi
    1caf:	89 ec                	mov    %ebp,%esp
    1cb1:	5d                   	pop    %ebp
    1cb2:	c3                   	ret    
    1cb3:	90                   	nop
    1cb4:	90                   	nop
    1cb5:	90                   	nop
    1cb6:	90                   	nop
    1cb7:	90                   	nop
    1cb8:	90                   	nop
    1cb9:	90                   	nop
    1cba:	90                   	nop
    1cbb:	90                   	nop
    1cbc:	90                   	nop
    1cbd:	90                   	nop
    1cbe:	90                   	nop
    1cbf:	90                   	nop

00001cc0 <test_send_msg_to_us>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void test_send_msg_to_us()
{
    1cc0:	55                   	push   %ebp
    1cc1:	89 e5                	mov    %esp,%ebp
    1cc3:	83 ec 04             	sub    $0x4,%esp
    1cc6:	e8 fc ff ff ff       	call   1cc7 <test_send_msg_to_us+0x7>
	//test send message to user space
	fsm_printf("********test send message to us.\n");
    1ccb:	c7 04 24 30 01 00 00 	movl   $0x130,(%esp)
    1cd2:	e8 fc ff ff ff       	call   1cd3 <test_send_msg_to_us+0x13>
	char *data = "a test message from rrcfsm.c";
	//send_to_user(data, strlen(data)+1);
}
    1cd7:	c9                   	leave  
    1cd8:	c3                   	ret    
    1cd9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00001ce0 <rrc_messege_handler_rlc>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
static void rrc_messege_handler_rlc(FSM_PKT* pkptr)
{
    1ce0:	55                   	push   %ebp
    1ce1:	89 e5                	mov    %esp,%ebp
    1ce3:	56                   	push   %esi
    1ce4:	53                   	push   %ebx
    1ce5:	83 ec 08             	sub    $0x8,%esp
    1ce8:	e8 fc ff ff ff       	call   1ce9 <rrc_messege_handler_rlc+0x9>
    1ced:	89 c3                	mov    %eax,%ebx
	FIN(rrc_messege_handler_rlc());
	SV_PTR_GET(rrc_sv);
    1cef:	e8 fc ff ff ff       	call   1cf0 <rrc_messege_handler_rlc+0x10>
	fsm_printf("[rrc] [fsm] rrc_messege_handler_rlc().\n");
    1cf4:	c7 04 24 54 01 00 00 	movl   $0x154,(%esp)
    1cfb:	e8 fc ff ff ff       	call   1cfc <rrc_messege_handler_rlc+0x1c>

	struct lte_rrc_head* sh_ptr;
	sh_ptr = (struct lte_rrc_head*)pkptr->data;
    1d00:	8b b3 ac 00 00 00    	mov    0xac(%ebx),%esi
	fsm_skb_pull(pkptr, sizeof(struct lte_rrc_head));
    1d06:	ba 04 00 00 00       	mov    $0x4,%edx
    1d0b:	89 d8                	mov    %ebx,%eax
    1d0d:	e8 fc ff ff ff       	call   1d0e <rrc_messege_handler_rlc+0x2e>

	fsm_printf("[rrc] [fsm] --> Msg type: %d\n", sh_ptr->message_type);
    1d12:	8b 06                	mov    (%esi),%eax
    1d14:	c7 04 24 8b 00 00 00 	movl   $0x8b,(%esp)
    1d1b:	89 44 24 04          	mov    %eax,0x4(%esp)
    1d1f:	e8 fc ff ff ff       	call   1d20 <rrc_messege_handler_rlc+0x40>
	fsm_printf("[rrc] [fsm] --> sh_ptr addr:%p\n", sh_ptr);
    1d24:	89 74 24 04          	mov    %esi,0x4(%esp)
    1d28:	c7 04 24 7c 01 00 00 	movl   $0x17c,(%esp)
    1d2f:	e8 fc ff ff ff       	call   1d30 <rrc_messege_handler_rlc+0x50>

	if(sh_ptr->message_type == 0)
    1d34:	8b 06                	mov    (%esi),%eax
    1d36:	85 c0                	test   %eax,%eax
    1d38:	74 36                	je     1d70 <rrc_messege_handler_rlc+0x90>
		paging = fsm_mem_alloc(sizeof(struct Paging));
		fsm_mem_cpy(paging, (void *)&(pcch_msg->paging), sizeof(struct Paging));
		fsm_printf("[rrc] [fsm] --> recived Paging!\n");
		fsm_schedule_self(0, CODE_RCV_PAGING);
	}
	else if(sh_ptr->message_type == 1)
    1d3a:	83 f8 01             	cmp    $0x1,%eax
    1d3d:	0f 84 fd 01 00 00    	je     1f40 <rrc_messege_handler_rlc+0x260>

		fsm_printf("[rrc] [fsm] --> recived MIB!\n");
		fsm_schedule_self(0, CODE_RCV_MIB);

	}
	else if(sh_ptr->message_type == 2)
    1d43:	83 f8 02             	cmp    $0x2,%eax
    1d46:	0f 84 e4 00 00 00    	je     1e30 <rrc_messege_handler_rlc+0x150>
			fsm_mem_cpy(sib1, (void *)&(bcch_dl_sch_msg->msg.sib1), sizeof(struct SystemInformationBlockType1));
			fsm_printf("[rrc] [fsm] --> recived SIB1!\n");
			fsm_schedule_self(0, CODE_RCV_SIB1);
		}
	}
	else if(sh_ptr->message_type == 3)
    1d4c:	83 f8 03             	cmp    $0x3,%eax
    1d4f:	90                   	nop
    1d50:	0f 84 3a 01 00 00    	je     1e90 <rrc_messege_handler_rlc+0x1b0>
			fsm_mem_cpy(rrcConnectionSetup, &(dl_ccch_msg->msg.rrcConnectionSetup), sizeof(struct RRCConnectionSetup));
			fsm_schedule_self(0, CODE_RCV_RRC_CONN_SETUP);
		}

	}
	else if(sh_ptr->message_type == 4)
    1d56:	83 f8 04             	cmp    $0x4,%eax
    1d59:	74 75                	je     1dd0 <rrc_messege_handler_rlc+0xf0>
			fsm_mem_cpy(rrcConnectionRelease, (void *)&(dl_dcch_msg->msg.rrcConnectionRelease), sizeof(struct RRCConnectionRelease));
			fsm_schedule_self(0, CODE_RCV_RRC_CONN_RELEASE);
		}

	}
	fsm_pkt_destroy(pkptr);
    1d5b:	89 d8                	mov    %ebx,%eax
    1d5d:	8d 76 00             	lea    0x0(%esi),%esi
    1d60:	e8 fc ff ff ff       	call   1d61 <rrc_messege_handler_rlc+0x81>

	FOUT;
}
    1d65:	83 c4 08             	add    $0x8,%esp
    1d68:	5b                   	pop    %ebx
    1d69:	5e                   	pop    %esi
    1d6a:	5d                   	pop    %ebp
    1d6b:	c3                   	ret    
    1d6c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

	if(sh_ptr->message_type == 0)
	{
		//PCCH_Message
		struct PCCH_Message *pcch_msg;
		fsm_printf("[rrc] [fsm] --> recive PCCH_Message.\n");
    1d70:	c7 04 24 9c 01 00 00 	movl   $0x19c,(%esp)
    1d77:	e8 fc ff ff ff       	call   1d78 <rrc_messege_handler_rlc+0x98>
		pcch_msg = (struct PCCH_Message *)pkptr->data;
		
		check_free_ptr(paging);
    1d7c:	a1 00 00 00 00       	mov    0x0,%eax
	if(sh_ptr->message_type == 0)
	{
		//PCCH_Message
		struct PCCH_Message *pcch_msg;
		fsm_printf("[rrc] [fsm] --> recive PCCH_Message.\n");
		pcch_msg = (struct PCCH_Message *)pkptr->data;
    1d81:	8b b3 ac 00 00 00    	mov    0xac(%ebx),%esi
		
		check_free_ptr(paging);
    1d87:	e8 fc ff ff ff       	call   1d88 <rrc_messege_handler_rlc+0xa8>
		paging = fsm_mem_alloc(sizeof(struct Paging));
    1d8c:	b8 d8 01 00 00       	mov    $0x1d8,%eax
    1d91:	e8 fc ff ff ff       	call   1d92 <rrc_messege_handler_rlc+0xb2>
		fsm_mem_cpy(paging, (void *)&(pcch_msg->paging), sizeof(struct Paging));
    1d96:	b9 d8 01 00 00       	mov    $0x1d8,%ecx
    1d9b:	89 f2                	mov    %esi,%edx
		struct PCCH_Message *pcch_msg;
		fsm_printf("[rrc] [fsm] --> recive PCCH_Message.\n");
		pcch_msg = (struct PCCH_Message *)pkptr->data;
		
		check_free_ptr(paging);
		paging = fsm_mem_alloc(sizeof(struct Paging));
    1d9d:	a3 00 00 00 00       	mov    %eax,0x0
		fsm_mem_cpy(paging, (void *)&(pcch_msg->paging), sizeof(struct Paging));
    1da2:	e8 fc ff ff ff       	call   1da3 <rrc_messege_handler_rlc+0xc3>
		fsm_printf("[rrc] [fsm] --> recived Paging!\n");
    1da7:	c7 04 24 c4 01 00 00 	movl   $0x1c4,(%esp)
    1dae:	e8 fc ff ff ff       	call   1daf <rrc_messege_handler_rlc+0xcf>
		fsm_schedule_self(0, CODE_RCV_PAGING);
    1db3:	ba 0e 00 00 00       	mov    $0xe,%edx
    1db8:	31 c0                	xor    %eax,%eax
    1dba:	e8 fc ff ff ff       	call   1dbb <rrc_messege_handler_rlc+0xdb>
			fsm_mem_cpy(rrcConnectionRelease, (void *)&(dl_dcch_msg->msg.rrcConnectionRelease), sizeof(struct RRCConnectionRelease));
			fsm_schedule_self(0, CODE_RCV_RRC_CONN_RELEASE);
		}

	}
	fsm_pkt_destroy(pkptr);
    1dbf:	89 d8                	mov    %ebx,%eax
    1dc1:	e8 fc ff ff ff       	call   1dc2 <rrc_messege_handler_rlc+0xe2>

	FOUT;
}
    1dc6:	83 c4 08             	add    $0x8,%esp
    1dc9:	5b                   	pop    %ebx
    1dca:	5e                   	pop    %esi
    1dcb:	5d                   	pop    %ebp
    1dcc:	c3                   	ret    
    1dcd:	8d 76 00             	lea    0x0(%esi),%esi

	}
	else if(sh_ptr->message_type == 4)
	{
		//DL_DCCH_Message
		fsm_printf("[rrc] [fsm] --> recive DL_DCCH_Message.\n");
    1dd0:	c7 04 24 40 03 00 00 	movl   $0x340,(%esp)
    1dd7:	e8 fc ff ff ff       	call   1dd8 <rrc_messege_handler_rlc+0xf8>
		struct DL_DCCH_Message *dl_dcch_msg = (struct DL_DCCH_Message *)pkptr->data;
    1ddc:	8b b3 ac 00 00 00    	mov    0xac(%ebx),%esi
		if (dl_dcch_msg->type == 1)
    1de2:	8b 06                	mov    (%esi),%eax
    1de4:	83 f8 01             	cmp    $0x1,%eax
    1de7:	0f 84 ee 01 00 00    	je     1fdb <rrc_messege_handler_rlc+0x2fb>
			check_free_ptr(rrcConnectionReconfiguration);
			rrcConnectionReconfiguration = fsm_mem_alloc(sizeof(struct RRCConnectionReconfiguration));
			fsm_mem_cpy(rrcConnectionReconfiguration, (void *)&(dl_dcch_msg->msg.rrcConnectionReconfiguration), sizeof(struct RRCConnectionReconfiguration));
			fsm_schedule_self(0, CODE_RCV_RRC_CONN_RECONF);
		}
		else if (dl_dcch_msg->type == 2)
    1ded:	83 f8 02             	cmp    $0x2,%eax
    1df0:	0f 85 65 ff ff ff    	jne    1d5b <rrc_messege_handler_rlc+0x7b>
		{
			check_free_ptr(rrcConnectionRelease);
    1df6:	a1 00 00 00 00       	mov    0x0,%eax
    1dfb:	e8 fc ff ff ff       	call   1dfc <rrc_messege_handler_rlc+0x11c>
			rrcConnectionRelease = fsm_mem_alloc(sizeof(struct RRCConnectionRelease));
    1e00:	b8 40 00 00 00       	mov    $0x40,%eax
    1e05:	e8 fc ff ff ff       	call   1e06 <rrc_messege_handler_rlc+0x126>
			fsm_mem_cpy(rrcConnectionRelease, (void *)&(dl_dcch_msg->msg.rrcConnectionRelease), sizeof(struct RRCConnectionRelease));
    1e0a:	8d 56 04             	lea    0x4(%esi),%edx
    1e0d:	b9 40 00 00 00       	mov    $0x40,%ecx
			fsm_schedule_self(0, CODE_RCV_RRC_CONN_RECONF);
		}
		else if (dl_dcch_msg->type == 2)
		{
			check_free_ptr(rrcConnectionRelease);
			rrcConnectionRelease = fsm_mem_alloc(sizeof(struct RRCConnectionRelease));
    1e12:	a3 00 00 00 00       	mov    %eax,0x0
			fsm_mem_cpy(rrcConnectionRelease, (void *)&(dl_dcch_msg->msg.rrcConnectionRelease), sizeof(struct RRCConnectionRelease));
    1e17:	e8 fc ff ff ff       	call   1e18 <rrc_messege_handler_rlc+0x138>
			fsm_schedule_self(0, CODE_RCV_RRC_CONN_RELEASE);
    1e1c:	ba 07 00 00 00       	mov    $0x7,%edx
    1e21:	31 c0                	xor    %eax,%eax
    1e23:	e8 fc ff ff ff       	call   1e24 <rrc_messege_handler_rlc+0x144>
    1e28:	e9 2e ff ff ff       	jmp    1d5b <rrc_messege_handler_rlc+0x7b>
    1e2d:	8d 76 00             	lea    0x0(%esi),%esi

	}
	else if(sh_ptr->message_type == 2)
	{
		//BCCH_DL_SCH_Message
		fsm_printf("[rrc] [fsm] --> recive BCCH_DL_SCH_Message.\n");
    1e30:	c7 04 24 14 02 00 00 	movl   $0x214,(%esp)
    1e37:	e8 fc ff ff ff       	call   1e38 <rrc_messege_handler_rlc+0x158>
		struct BCCH_DL_SCH_Message *bcch_dl_sch_msg = (struct BCCH_DL_SCH_Message *)pkptr->data;
    1e3c:	8b b3 ac 00 00 00    	mov    0xac(%ebx),%esi
		if (bcch_dl_sch_msg->type == 1)
    1e42:	83 3e 01             	cmpl   $0x1,(%esi)
    1e45:	0f 84 4d 01 00 00    	je     1f98 <rrc_messege_handler_rlc+0x2b8>
			fsm_printf("[rrc] [fsm] --> recived SI!\n");
			fsm_schedule_self(0, CODE_RCV_SI);
		}
		else
		{
			check_free_ptr(sib1);
    1e4b:	a1 00 00 00 00       	mov    0x0,%eax
    1e50:	e8 fc ff ff ff       	call   1e51 <rrc_messege_handler_rlc+0x171>
			sib1 = fsm_mem_alloc(sizeof(struct SystemInformationBlockType1));
    1e55:	b8 6c 01 00 00       	mov    $0x16c,%eax
    1e5a:	e8 fc ff ff ff       	call   1e5b <rrc_messege_handler_rlc+0x17b>
			fsm_mem_cpy(sib1, (void *)&(bcch_dl_sch_msg->msg.sib1), sizeof(struct SystemInformationBlockType1));
    1e5f:	8d 56 04             	lea    0x4(%esi),%edx
    1e62:	b9 6c 01 00 00       	mov    $0x16c,%ecx
			fsm_schedule_self(0, CODE_RCV_SI);
		}
		else
		{
			check_free_ptr(sib1);
			sib1 = fsm_mem_alloc(sizeof(struct SystemInformationBlockType1));
    1e67:	a3 00 00 00 00       	mov    %eax,0x0
			fsm_mem_cpy(sib1, (void *)&(bcch_dl_sch_msg->msg.sib1), sizeof(struct SystemInformationBlockType1));
    1e6c:	e8 fc ff ff ff       	call   1e6d <rrc_messege_handler_rlc+0x18d>
			fsm_printf("[rrc] [fsm] --> recived SIB1!\n");
    1e71:	c7 04 24 44 02 00 00 	movl   $0x244,(%esp)
    1e78:	e8 fc ff ff ff       	call   1e79 <rrc_messege_handler_rlc+0x199>
			fsm_schedule_self(0, CODE_RCV_SIB1);
    1e7d:	ba 10 00 00 00       	mov    $0x10,%edx
    1e82:	31 c0                	xor    %eax,%eax
    1e84:	e8 fc ff ff ff       	call   1e85 <rrc_messege_handler_rlc+0x1a5>
    1e89:	e9 cd fe ff ff       	jmp    1d5b <rrc_messege_handler_rlc+0x7b>
    1e8e:	66 90                	xchg   %ax,%ax
		}
	}
	else if(sh_ptr->message_type == 3)
	{
		//DL_CCCH_Message
		fsm_printf("[rrc] [fsm] --> recive DL_CCCH_Message.\n");
    1e90:	c7 04 24 64 02 00 00 	movl   $0x264,(%esp)
    1e97:	e8 fc ff ff ff       	call   1e98 <rrc_messege_handler_rlc+0x1b8>
		struct DL_CCCH_Message *dl_ccch_msg = (struct DL_CCCH_Message *)pkptr->data;
    1e9c:	8b b3 ac 00 00 00    	mov    0xac(%ebx),%esi

		fsm_printf(" 		  dl_ccch_msg->type=%d.\n",dl_ccch_msg->type);
    1ea2:	8b 06                	mov    (%esi),%eax
    1ea4:	c7 04 24 e4 00 00 00 	movl   $0xe4,(%esp)
    1eab:	89 44 24 04          	mov    %eax,0x4(%esp)
    1eaf:	e8 fc ff ff ff       	call   1eb0 <rrc_messege_handler_rlc+0x1d0>
		fsm_printf(" 		  dl_ccch_msg addr=%p.\n",dl_ccch_msg);
    1eb4:	89 74 24 04          	mov    %esi,0x4(%esp)
    1eb8:	c7 04 24 00 01 00 00 	movl   $0x100,(%esp)
    1ebf:	e8 fc ff ff ff       	call   1ec0 <rrc_messege_handler_rlc+0x1e0>

		if (dl_ccch_msg->type == 3)
    1ec4:	8b 06                	mov    (%esi),%eax
    1ec6:	83 f8 03             	cmp    $0x3,%eax
    1ec9:	0f 84 43 01 00 00    	je     2012 <rrc_messege_handler_rlc+0x332>
			check_free_ptr(rrcConnectionReject);
			rrcConnectionReject = fsm_mem_alloc(sizeof(struct RRCConnectionReject));
			fsm_mem_cpy(rrcConnectionReject, (void *)&(dl_ccch_msg->msg.rrcConnectionReject), sizeof(struct RRCConnectionReject));
			fsm_schedule_self(0, CODE_RCV_RRC_CONN_REJECT);
		}
		else if (dl_ccch_msg->type == 4)
    1ecf:	83 f8 04             	cmp    $0x4,%eax
    1ed2:	0f 85 83 fe ff ff    	jne    1d5b <rrc_messege_handler_rlc+0x7b>
		{
			check_free_ptr(rrcConnectionSetup);
    1ed8:	a1 00 00 00 00       	mov    0x0,%eax
    1edd:	e8 fc ff ff ff       	call   1ede <rrc_messege_handler_rlc+0x1fe>
			rrcConnectionSetup = fsm_mem_alloc(sizeof(struct RRCConnectionSetup));
    1ee2:	b8 f0 04 00 00       	mov    $0x4f0,%eax
    1ee7:	e8 fc ff ff ff       	call   1ee8 <rrc_messege_handler_rlc+0x208>
    1eec:	a3 00 00 00 00       	mov    %eax,0x0
			fsm_printf("[rrc] dl_ccch_msg->msg.rrcConnectionSetup.radioResourceConfigDedicated.drbToAddModList.num = %d\n",dl_ccch_msg->msg.rrcConnectionSetup.radioResourceConfigDedicated.drbToAddModList.num);
    1ef1:	8b 86 84 00 00 00    	mov    0x84(%esi),%eax
    1ef7:	c7 04 24 90 02 00 00 	movl   $0x290,(%esp)
    1efe:	89 44 24 04          	mov    %eax,0x4(%esp)
    1f02:	e8 fc ff ff ff       	call   1f03 <rrc_messege_handler_rlc+0x223>
			fsm_printf("[rrc] dl_ccch_msg->msg.rrcConnectionSetup.rrcTransactionIdentifier = %d\n",dl_ccch_msg->msg.rrcConnectionSetup.rrcTransactionIdentifier);
    1f07:	0f b6 46 04          	movzbl 0x4(%esi),%eax
    1f0b:	c7 04 24 f4 02 00 00 	movl   $0x2f4,(%esp)
    1f12:	89 44 24 04          	mov    %eax,0x4(%esp)
    1f16:	e8 fc ff ff ff       	call   1f17 <rrc_messege_handler_rlc+0x237>
			fsm_mem_cpy(rrcConnectionSetup, &(dl_ccch_msg->msg.rrcConnectionSetup), sizeof(struct RRCConnectionSetup));
    1f1b:	a1 00 00 00 00       	mov    0x0,%eax
    1f20:	8d 56 04             	lea    0x4(%esi),%edx
    1f23:	b9 f0 04 00 00       	mov    $0x4f0,%ecx
    1f28:	e8 fc ff ff ff       	call   1f29 <rrc_messege_handler_rlc+0x249>
			fsm_schedule_self(0, CODE_RCV_RRC_CONN_SETUP);
    1f2d:	ba 05 00 00 00       	mov    $0x5,%edx
    1f32:	31 c0                	xor    %eax,%eax
    1f34:	e8 fc ff ff ff       	call   1f35 <rrc_messege_handler_rlc+0x255>
    1f39:	e9 1d fe ff ff       	jmp    1d5b <rrc_messege_handler_rlc+0x7b>
    1f3e:	66 90                	xchg   %ax,%ax
	}
	else if(sh_ptr->message_type == 1)
	{
		//BCCH_BCH_Message
		struct BCCH_BCH_Message *bcch_bch_msg;
		fsm_printf("[rrc] [fsm] --> recive BCCH_BCH_Message.\n");
    1f40:	c7 04 24 e8 01 00 00 	movl   $0x1e8,(%esp)
    1f47:	e8 fc ff ff ff       	call   1f48 <rrc_messege_handler_rlc+0x268>
		bcch_bch_msg = (struct BCCH_BCH_Message *)pkptr->data;

		//struct MasterInformationBlock mib = bcch_bch_msg->mib;
		check_free_ptr(mib);
    1f4c:	a1 00 00 00 00       	mov    0x0,%eax
	else if(sh_ptr->message_type == 1)
	{
		//BCCH_BCH_Message
		struct BCCH_BCH_Message *bcch_bch_msg;
		fsm_printf("[rrc] [fsm] --> recive BCCH_BCH_Message.\n");
		bcch_bch_msg = (struct BCCH_BCH_Message *)pkptr->data;
    1f51:	8b b3 ac 00 00 00    	mov    0xac(%ebx),%esi

		//struct MasterInformationBlock mib = bcch_bch_msg->mib;
		check_free_ptr(mib);
    1f57:	e8 fc ff ff ff       	call   1f58 <rrc_messege_handler_rlc+0x278>
		mib = fsm_mem_alloc(sizeof(struct MasterInformationBlock));
    1f5c:	b8 10 00 00 00       	mov    $0x10,%eax
    1f61:	e8 fc ff ff ff       	call   1f62 <rrc_messege_handler_rlc+0x282>
		fsm_mem_cpy(mib, (void *)&(bcch_bch_msg->mib), sizeof(struct MasterInformationBlock));
    1f66:	89 f2                	mov    %esi,%edx
    1f68:	b9 10 00 00 00       	mov    $0x10,%ecx
		fsm_printf("[rrc] [fsm] --> recive BCCH_BCH_Message.\n");
		bcch_bch_msg = (struct BCCH_BCH_Message *)pkptr->data;

		//struct MasterInformationBlock mib = bcch_bch_msg->mib;
		check_free_ptr(mib);
		mib = fsm_mem_alloc(sizeof(struct MasterInformationBlock));
    1f6d:	a3 00 00 00 00       	mov    %eax,0x0
		fsm_mem_cpy(mib, (void *)&(bcch_bch_msg->mib), sizeof(struct MasterInformationBlock));
    1f72:	e8 fc ff ff ff       	call   1f73 <rrc_messege_handler_rlc+0x293>

		fsm_printf("[rrc] [fsm] --> recived MIB!\n");
    1f77:	c7 04 24 a9 00 00 00 	movl   $0xa9,(%esp)
    1f7e:	e8 fc ff ff ff       	call   1f7f <rrc_messege_handler_rlc+0x29f>
		fsm_schedule_self(0, CODE_RCV_MIB);
    1f83:	ba 0f 00 00 00       	mov    $0xf,%edx
    1f88:	31 c0                	xor    %eax,%eax
    1f8a:	e8 fc ff ff ff       	call   1f8b <rrc_messege_handler_rlc+0x2ab>
    1f8f:	e9 c7 fd ff ff       	jmp    1d5b <rrc_messege_handler_rlc+0x7b>
    1f94:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
		//BCCH_DL_SCH_Message
		fsm_printf("[rrc] [fsm] --> recive BCCH_DL_SCH_Message.\n");
		struct BCCH_DL_SCH_Message *bcch_dl_sch_msg = (struct BCCH_DL_SCH_Message *)pkptr->data;
		if (bcch_dl_sch_msg->type == 1)
		{
			check_free_ptr(si);
    1f98:	a1 00 00 00 00       	mov    0x0,%eax
    1f9d:	e8 fc ff ff ff       	call   1f9e <rrc_messege_handler_rlc+0x2be>
			si = fsm_mem_alloc(sizeof(struct SystemInformation));
    1fa2:	b8 0c 01 00 00       	mov    $0x10c,%eax
    1fa7:	e8 fc ff ff ff       	call   1fa8 <rrc_messege_handler_rlc+0x2c8>
			fsm_mem_cpy(si, (void *)&(bcch_dl_sch_msg->msg.si), sizeof(struct SystemInformation));
    1fac:	8d 56 04             	lea    0x4(%esi),%edx
    1faf:	b9 0c 01 00 00       	mov    $0x10c,%ecx
		fsm_printf("[rrc] [fsm] --> recive BCCH_DL_SCH_Message.\n");
		struct BCCH_DL_SCH_Message *bcch_dl_sch_msg = (struct BCCH_DL_SCH_Message *)pkptr->data;
		if (bcch_dl_sch_msg->type == 1)
		{
			check_free_ptr(si);
			si = fsm_mem_alloc(sizeof(struct SystemInformation));
    1fb4:	a3 00 00 00 00       	mov    %eax,0x0
			fsm_mem_cpy(si, (void *)&(bcch_dl_sch_msg->msg.si), sizeof(struct SystemInformation));
    1fb9:	e8 fc ff ff ff       	call   1fba <rrc_messege_handler_rlc+0x2da>
			fsm_printf("[rrc] [fsm] --> recived SI!\n");
    1fbe:	c7 04 24 c7 00 00 00 	movl   $0xc7,(%esp)
    1fc5:	e8 fc ff ff ff       	call   1fc6 <rrc_messege_handler_rlc+0x2e6>
			fsm_schedule_self(0, CODE_RCV_SI);
    1fca:	ba 11 00 00 00       	mov    $0x11,%edx
    1fcf:	31 c0                	xor    %eax,%eax
    1fd1:	e8 fc ff ff ff       	call   1fd2 <rrc_messege_handler_rlc+0x2f2>
    1fd6:	e9 80 fd ff ff       	jmp    1d5b <rrc_messege_handler_rlc+0x7b>
		//DL_DCCH_Message
		fsm_printf("[rrc] [fsm] --> recive DL_DCCH_Message.\n");
		struct DL_DCCH_Message *dl_dcch_msg = (struct DL_DCCH_Message *)pkptr->data;
		if (dl_dcch_msg->type == 1)
		{
			check_free_ptr(rrcConnectionReconfiguration);
    1fdb:	a1 00 00 00 00       	mov    0x0,%eax
    1fe0:	e8 fc ff ff ff       	call   1fe1 <rrc_messege_handler_rlc+0x301>
			rrcConnectionReconfiguration = fsm_mem_alloc(sizeof(struct RRCConnectionReconfiguration));
    1fe5:	b8 f0 04 00 00       	mov    $0x4f0,%eax
    1fea:	e8 fc ff ff ff       	call   1feb <rrc_messege_handler_rlc+0x30b>
			fsm_mem_cpy(rrcConnectionReconfiguration, (void *)&(dl_dcch_msg->msg.rrcConnectionReconfiguration), sizeof(struct RRCConnectionReconfiguration));
    1fef:	8d 56 04             	lea    0x4(%esi),%edx
    1ff2:	b9 f0 04 00 00       	mov    $0x4f0,%ecx
		fsm_printf("[rrc] [fsm] --> recive DL_DCCH_Message.\n");
		struct DL_DCCH_Message *dl_dcch_msg = (struct DL_DCCH_Message *)pkptr->data;
		if (dl_dcch_msg->type == 1)
		{
			check_free_ptr(rrcConnectionReconfiguration);
			rrcConnectionReconfiguration = fsm_mem_alloc(sizeof(struct RRCConnectionReconfiguration));
    1ff7:	a3 00 00 00 00       	mov    %eax,0x0
			fsm_mem_cpy(rrcConnectionReconfiguration, (void *)&(dl_dcch_msg->msg.rrcConnectionReconfiguration), sizeof(struct RRCConnectionReconfiguration));
    1ffc:	e8 fc ff ff ff       	call   1ffd <rrc_messege_handler_rlc+0x31d>
			fsm_schedule_self(0, CODE_RCV_RRC_CONN_RECONF);
    2001:	ba 06 00 00 00       	mov    $0x6,%edx
    2006:	31 c0                	xor    %eax,%eax
    2008:	e8 fc ff ff ff       	call   2009 <rrc_messege_handler_rlc+0x329>
    200d:	e9 49 fd ff ff       	jmp    1d5b <rrc_messege_handler_rlc+0x7b>
		fsm_printf(" 		  dl_ccch_msg->type=%d.\n",dl_ccch_msg->type);
		fsm_printf(" 		  dl_ccch_msg addr=%p.\n",dl_ccch_msg);

		if (dl_ccch_msg->type == 3)
		{
			check_free_ptr(rrcConnectionReject);
    2012:	a1 00 00 00 00       	mov    0x0,%eax
    2017:	e8 fc ff ff ff       	call   2018 <rrc_messege_handler_rlc+0x338>
			rrcConnectionReject = fsm_mem_alloc(sizeof(struct RRCConnectionReject));
    201c:	b8 04 00 00 00       	mov    $0x4,%eax
    2021:	e8 fc ff ff ff       	call   2022 <rrc_messege_handler_rlc+0x342>
			fsm_mem_cpy(rrcConnectionReject, (void *)&(dl_ccch_msg->msg.rrcConnectionReject), sizeof(struct RRCConnectionReject));
    2026:	8d 56 04             	lea    0x4(%esi),%edx
    2029:	b9 04 00 00 00       	mov    $0x4,%ecx
		fsm_printf(" 		  dl_ccch_msg addr=%p.\n",dl_ccch_msg);

		if (dl_ccch_msg->type == 3)
		{
			check_free_ptr(rrcConnectionReject);
			rrcConnectionReject = fsm_mem_alloc(sizeof(struct RRCConnectionReject));
    202e:	a3 00 00 00 00       	mov    %eax,0x0
			fsm_mem_cpy(rrcConnectionReject, (void *)&(dl_ccch_msg->msg.rrcConnectionReject), sizeof(struct RRCConnectionReject));
    2033:	e8 fc ff ff ff       	call   2034 <rrc_messege_handler_rlc+0x354>
			fsm_schedule_self(0, CODE_RCV_RRC_CONN_REJECT);
    2038:	ba 04 00 00 00       	mov    $0x4,%edx
    203d:	31 c0                	xor    %eax,%eax
    203f:	e8 fc ff ff ff       	call   2040 <rrc_messege_handler_rlc+0x360>
    2044:	e9 12 fd ff ff       	jmp    1d5b <rrc_messege_handler_rlc+0x7b>
    2049:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00002050 <test_si>:
{
	FSM_PKT* pkptr=gen_mib();
	rrc_messege_handler_rlc(pkptr);
}
void test_si()
{
    2050:	55                   	push   %ebp
    2051:	89 e5                	mov    %esp,%ebp
    2053:	e8 fc ff ff ff       	call   2054 <test_si+0x4>
	FSM_PKT* pkptr=gen_si();
    2058:	e8 fc ff ff ff       	call   2059 <test_si+0x9>
	rrc_messege_handler_rlc(pkptr);
    205d:	e8 7e fc ff ff       	call   1ce0 <rrc_messege_handler_rlc>
}
    2062:	5d                   	pop    %ebp
    2063:	c3                   	ret    
    2064:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    206a:	8d bf 00 00 00 00    	lea    0x0(%edi),%edi

00002070 <rrc_messege_handler_upper>:
 **-------------------------------------- --------------------
 ** Modified by: 
 ** Modified Date: 
 ******************************************************************************/
static void rrc_messege_handler_upper(FSM_PKT* pkptr)
{
    2070:	55                   	push   %ebp
    2071:	89 e5                	mov    %esp,%ebp
    2073:	53                   	push   %ebx
    2074:	83 ec 04             	sub    $0x4,%esp
    2077:	e8 fc ff ff ff       	call   2078 <rrc_messege_handler_upper+0x8>
    207c:	89 c3                	mov    %eax,%ebx
	FIN(rrc_messege_handler_upper());
	SV_PTR_GET(rrc_sv);
    207e:	e8 fc ff ff ff       	call   207f <rrc_messege_handler_upper+0xf>
	fsm_printf("[rrc] [fsm] rrc_messege_handler_upper().\n");
    2083:	c7 04 24 6c 03 00 00 	movl   $0x36c,(%esp)
    208a:	e8 fc ff ff ff       	call   208b <rrc_messege_handler_upper+0x1b>
	fsm_pkt_destroy(pkptr);
    208f:	89 d8                	mov    %ebx,%eax
    2091:	e8 fc ff ff ff       	call   2092 <rrc_messege_handler_upper+0x22>

	FOUT;
}
    2096:	83 c4 04             	add    $0x4,%esp
    2099:	5b                   	pop    %ebx
    209a:	5d                   	pop    %ebp
    209b:	c3                   	ret    
    209c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

000020a0 <test_mib>:
{
	FSM_PKT* pkptr=gen_sib1();
	rrc_messege_handler_rlc(pkptr);
}
void test_mib()
{
    20a0:	55                   	push   %ebp
    20a1:	89 e5                	mov    %esp,%ebp
    20a3:	e8 fc ff ff ff       	call   20a4 <test_mib+0x4>
	FSM_PKT* pkptr=gen_mib();
    20a8:	e8 fc ff ff ff       	call   20a9 <test_mib+0x9>
	rrc_messege_handler_rlc(pkptr);
    20ad:	e8 2e fc ff ff       	call   1ce0 <rrc_messege_handler_rlc>
}
    20b2:	5d                   	pop    %ebp
    20b3:	c3                   	ret    
    20b4:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    20ba:	8d bf 00 00 00 00    	lea    0x0(%edi),%edi

000020c0 <test_sib1>:
{
	FSM_PKT* pkptr=gen_paging();
	rrc_messege_handler_rlc(pkptr);
}
void test_sib1()
{
    20c0:	55                   	push   %ebp
    20c1:	89 e5                	mov    %esp,%ebp
    20c3:	e8 fc ff ff ff       	call   20c4 <test_sib1+0x4>
	FSM_PKT* pkptr=gen_sib1();
    20c8:	e8 fc ff ff ff       	call   20c9 <test_sib1+0x9>
	rrc_messege_handler_rlc(pkptr);
    20cd:	e8 0e fc ff ff       	call   1ce0 <rrc_messege_handler_rlc>
}
    20d2:	5d                   	pop    %ebp
    20d3:	c3                   	ret    
    20d4:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    20da:	8d bf 00 00 00 00    	lea    0x0(%edi),%edi

000020e0 <test_paging>:
	char *data = "a test message from rrcfsm.c";
	//send_to_user(data, strlen(data)+1);
}

void test_paging()
{
    20e0:	55                   	push   %ebp
    20e1:	89 e5                	mov    %esp,%ebp
    20e3:	e8 fc ff ff ff       	call   20e4 <test_paging+0x4>
	FSM_PKT* pkptr=gen_paging();
    20e8:	e8 fc ff ff ff       	call   20e9 <test_paging+0x9>
	rrc_messege_handler_rlc(pkptr);
    20ed:	e8 ee fb ff ff       	call   1ce0 <rrc_messege_handler_rlc>
}
    20f2:	5d                   	pop    %ebp
    20f3:	c3                   	ret    
    20f4:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    20fa:	8d bf 00 00 00 00    	lea    0x0(%edi),%edi

00002100 <test_send_pkt_to_rlc>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void test_send_pkt_to_rlc()
{
    2100:	55                   	push   %ebp
    2101:	89 e5                	mov    %esp,%ebp
    2103:	83 ec 10             	sub    $0x10,%esp
    2106:	e8 fc ff ff ff       	call   2107 <test_send_pkt_to_rlc+0x7>
	struct BCCH_BCH_Message bcch_bch_msg;
	bcch_bch_msg.mib = mib;
	char *msg = (char *)&bcch_bch_msg;
	int msg_len = sizeof(bcch_bch_msg);
	int message_type = 1;
	packet_send_to_rlc(msg, msg_len, message_type);
    210b:	b9 01 00 00 00       	mov    $0x1,%ecx
    2110:	ba 10 00 00 00       	mov    $0x10,%edx
    2115:	8d 45 f0             	lea    -0x10(%ebp),%eax
{
	struct MasterInformationBlock mib;
	mib.dl_Bandwidth = n25;
	mib.systemFrameNumber = (u8)120;
	struct BCCH_BCH_Message bcch_bch_msg;
	bcch_bch_msg.mib = mib;
    2118:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%ebp)
    211f:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
    2126:	c6 45 fc 78          	movb   $0x78,-0x4(%ebp)
    212a:	c7 45 f0 19 00 00 00 	movl   $0x19,-0x10(%ebp)
	char *msg = (char *)&bcch_bch_msg;
	int msg_len = sizeof(bcch_bch_msg);
	int message_type = 1;
	packet_send_to_rlc(msg, msg_len, message_type);
    2131:	e8 fc ff ff ff       	call   2132 <test_send_pkt_to_rlc+0x32>
}
    2136:	c9                   	leave  
    2137:	c3                   	ret    
    2138:	90                   	nop
    2139:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00002140 <test_recv_pkt_from_rlc>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void test_recv_pkt_from_rlc()
{
    2140:	55                   	push   %ebp
    2141:	89 e5                	mov    %esp,%ebp
    2143:	53                   	push   %ebx
    2144:	83 ec 10             	sub    $0x10,%esp
    2147:	e8 fc ff ff ff       	call   2148 <test_recv_pkt_from_rlc+0x8>
	int msg_len = sizeof(bcch_bch_msg);
	int message_type = 1;

	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr = fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));
    214c:	b8 14 00 00 00       	mov    $0x14,%eax
{
	struct MasterInformationBlock mib;
	mib.dl_Bandwidth = n25;
	mib.systemFrameNumber = (u8)120;
	struct BCCH_BCH_Message bcch_bch_msg;
	bcch_bch_msg.mib = mib;
    2151:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
    2158:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
    215f:	c6 45 f8 78          	movb   $0x78,-0x8(%ebp)
    2163:	c7 45 ec 19 00 00 00 	movl   $0x19,-0x14(%ebp)
	int msg_len = sizeof(bcch_bch_msg);
	int message_type = 1;

	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr = fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));
    216a:	e8 fc ff ff ff       	call   216b <test_recv_pkt_from_rlc+0x2b>
	fsm_skb_put(pkptr, msg_len);
    216f:	ba 10 00 00 00       	mov    $0x10,%edx
	int msg_len = sizeof(bcch_bch_msg);
	int message_type = 1;

	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr = fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));
    2174:	89 c3                	mov    %eax,%ebx
	fsm_skb_put(pkptr, msg_len);
    2176:	e8 fc ff ff ff       	call   2177 <test_recv_pkt_from_rlc+0x37>
	fsm_mem_cpy(pkptr->data, msg, msg_len);
    217b:	8b 83 ac 00 00 00    	mov    0xac(%ebx),%eax
    2181:	8d 55 ec             	lea    -0x14(%ebp),%edx
    2184:	b9 10 00 00 00       	mov    $0x10,%ecx
    2189:	e8 fc ff ff ff       	call   218a <test_recv_pkt_from_rlc+0x4a>

	if(fsm_skb_headroom(pkptr) < sizeof(struct lte_rrc_head))
    218e:	89 d8                	mov    %ebx,%eax
    2190:	e8 fc ff ff ff       	call   2191 <test_recv_pkt_from_rlc+0x51>
    2195:	83 f8 03             	cmp    $0x3,%eax
    2198:	77 12                	ja     21ac <test_recv_pkt_from_rlc+0x6c>
	{
		pkptr = fsm_skb_realloc_headeroom(pkptr,sizeof(struct lte_rrc_head));
    219a:	89 d8                	mov    %ebx,%eax
    219c:	ba 04 00 00 00       	mov    $0x4,%edx
    21a1:	e8 fc ff ff ff       	call   21a2 <test_recv_pkt_from_rlc+0x62>
		if(pkptr == NULL)
    21a6:	85 c0                	test   %eax,%eax
	fsm_skb_put(pkptr, msg_len);
	fsm_mem_cpy(pkptr->data, msg, msg_len);

	if(fsm_skb_headroom(pkptr) < sizeof(struct lte_rrc_head))
	{
		pkptr = fsm_skb_realloc_headeroom(pkptr,sizeof(struct lte_rrc_head));
    21a8:	89 c3                	mov    %eax,%ebx
		if(pkptr == NULL)
    21aa:	74 1f                	je     21cb <test_recv_pkt_from_rlc+0x8b>
			return;
	}
	fsm_skb_push(pkptr, sizeof(struct lte_rrc_head));
    21ac:	ba 04 00 00 00       	mov    $0x4,%edx
    21b1:	89 d8                	mov    %ebx,%eax
    21b3:	e8 fc ff ff ff       	call   21b4 <test_recv_pkt_from_rlc+0x74>
	sh_ptr = (struct lte_rrc_head*)pkptr->data;
	sh_ptr->message_type = message_type;
    21b8:	8b 83 ac 00 00 00    	mov    0xac(%ebx),%eax
    21be:	c7 00 01 00 00 00    	movl   $0x1,(%eax)

	rrc_messege_handler_rlc(pkptr);
    21c4:	89 d8                	mov    %ebx,%eax
    21c6:	e8 15 fb ff ff       	call   1ce0 <rrc_messege_handler_rlc>

}
    21cb:	83 c4 10             	add    $0x10,%esp
    21ce:	5b                   	pop    %ebx
    21cf:	5d                   	pop    %ebp
    21d0:	c3                   	ret    
    21d1:	eb 0d                	jmp    21e0 <test>
    21d3:	90                   	nop
    21d4:	90                   	nop
    21d5:	90                   	nop
    21d6:	90                   	nop
    21d7:	90                   	nop
    21d8:	90                   	nop
    21d9:	90                   	nop
    21da:	90                   	nop
    21db:	90                   	nop
    21dc:	90                   	nop
    21dd:	90                   	nop
    21de:	90                   	nop
    21df:	90                   	nop

000021e0 <test>:
	FSM_PKT* pkptr=gen_si();
	rrc_messege_handler_rlc(pkptr);
}

void test()
{
    21e0:	55                   	push   %ebp
    21e1:	89 e5                	mov    %esp,%ebp
    21e3:	53                   	push   %ebx
    21e4:	83 ec 1c             	sub    $0x1c,%esp
    21e7:	e8 fc ff ff ff       	call   21e8 <test+0x8>
	//receive packet test
	test_recv_pkt_from_rlc();
    21ec:	e8 fc ff ff ff       	call   21ed <test+0xd>
	if (mib != NULL)
    21f1:	a1 00 00 00 00       	mov    0x0,%eax
    21f6:	85 c0                	test   %eax,%eax
    21f8:	0f 84 a2 00 00 00    	je     22a0 <test+0xc0>
	{
		fsm_printf("bcch_bch_msg.mib.dl_Bandwidth:%d\n", mib->dl_Bandwidth);
    21fe:	8b 00                	mov    (%eax),%eax
    2200:	c7 04 24 98 03 00 00 	movl   $0x398,(%esp)
    2207:	89 44 24 04          	mov    %eax,0x4(%esp)
    220b:	e8 fc ff ff ff       	call   220c <test+0x2c>
		fsm_printf("bcch_bch_msg.mib.systemFrameNumber:%d\n", mib->systemFrameNumber);
    2210:	a1 00 00 00 00       	mov    0x0,%eax
    2215:	0f b6 40 0c          	movzbl 0xc(%eax),%eax
    2219:	c7 04 24 bc 03 00 00 	movl   $0x3bc,(%esp)
    2220:	89 44 24 04          	mov    %eax,0x4(%esp)
    2224:	e8 fc ff ff ff       	call   2225 <test+0x45>
		fsm_mem_free(mib);
    2229:	a1 00 00 00 00       	mov    0x0,%eax
    222e:	e8 fc ff ff ff       	call   222f <test+0x4f>
		mib = NULL;
    2233:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    223a:	00 00 00 
	u16 tmp_crnti = (u16)32;
	struct MasterInformationBlock tmp_mib;
	tmp_mib.dl_Bandwidth = n25;
	tmp_mib.systemFrameNumber = (u8)120;
	int data_size = sizeof(u16) + sizeof(struct MasterInformationBlock);
	char * data = (char *)fsm_mem_alloc(data_size);
    223d:	b8 12 00 00 00       	mov    $0x12,%eax
	}
	else
		fsm_printf("mib is null\n");

	//test: ioctl with crnti
	u16 tmp_crnti = (u16)32;
    2242:	66 c7 45 fa 20 00    	movw   $0x20,-0x6(%ebp)
	struct MasterInformationBlock tmp_mib;
	tmp_mib.dl_Bandwidth = n25;
    2248:	c7 45 e8 19 00 00 00 	movl   $0x19,-0x18(%ebp)
	tmp_mib.systemFrameNumber = (u8)120;
    224f:	c6 45 f4 78          	movb   $0x78,-0xc(%ebp)
	int data_size = sizeof(u16) + sizeof(struct MasterInformationBlock);
	char * data = (char *)fsm_mem_alloc(data_size);
    2253:	e8 fc ff ff ff       	call   2254 <test+0x74>
	fsm_mem_cpy(data, &tmp_crnti, sizeof(u16));
    2258:	8d 55 fa             	lea    -0x6(%ebp),%edx
    225b:	b9 02 00 00 00       	mov    $0x2,%ecx
	u16 tmp_crnti = (u16)32;
	struct MasterInformationBlock tmp_mib;
	tmp_mib.dl_Bandwidth = n25;
	tmp_mib.systemFrameNumber = (u8)120;
	int data_size = sizeof(u16) + sizeof(struct MasterInformationBlock);
	char * data = (char *)fsm_mem_alloc(data_size);
    2260:	89 c3                	mov    %eax,%ebx
	fsm_mem_cpy(data, &tmp_crnti, sizeof(u16));
    2262:	e8 fc ff ff ff       	call   2263 <test+0x83>
	fsm_mem_cpy(data+sizeof(u16), &tmp_mib, sizeof(struct MasterInformationBlock));
    2267:	8d 55 e8             	lea    -0x18(%ebp),%edx
    226a:	b9 10 00 00 00       	mov    $0x10,%ecx
    226f:	8d 43 02             	lea    0x2(%ebx),%eax
    2272:	e8 fc ff ff ff       	call   2273 <test+0x93>
	fsm_do_ioctrl(STRM_TO_MAC, IOCCMD_RRCTOMAC_BEGIN_RECV_SYSINFO, (void*)data, data_size);
    2277:	89 d9                	mov    %ebx,%ecx
    2279:	ba 01 00 00 00       	mov    $0x1,%edx
    227e:	b8 02 00 00 00       	mov    $0x2,%eax
    2283:	c7 04 24 12 00 00 00 	movl   $0x12,(%esp)
    228a:	e8 fc ff ff ff       	call   228b <test+0xab>
	fsm_mem_free(data);
    228f:	89 d8                	mov    %ebx,%eax
    2291:	e8 fc ff ff ff       	call   2292 <test+0xb2>
}
    2296:	83 c4 1c             	add    $0x1c,%esp
    2299:	5b                   	pop    %ebx
    229a:	5d                   	pop    %ebp
    229b:	c3                   	ret    
    229c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
		fsm_printf("bcch_bch_msg.mib.systemFrameNumber:%d\n", mib->systemFrameNumber);
		fsm_mem_free(mib);
		mib = NULL;
	}
	else
		fsm_printf("mib is null\n");
    22a0:	c7 04 24 1b 01 00 00 	movl   $0x11b,(%esp)
    22a7:	e8 fc ff ff ff       	call   22a8 <test+0xc8>
    22ac:	eb 8f                	jmp    223d <test+0x5d>
    22ae:	66 90                	xchg   %ax,%ax

000022b0 <rrc_close>:
 **-------------------------------------- --------------------
 ** Modified by: zhou yang 
 ** Modified Date: 2014/10/1
 ******************************************************************************/
void rrc_close(void)
{
    22b0:	55                   	push   %ebp
    22b1:	89 e5                	mov    %esp,%ebp
    22b3:	83 ec 04             	sub    $0x4,%esp
    22b6:	e8 fc ff ff ff       	call   22b7 <rrc_close+0x7>
	FIN(rrc_close());
	SV_PTR_GET(rrc_sv);
    22bb:	e8 fc ff ff ff       	call   22bc <rrc_close+0xc>
	fsm_printf("[rrc] [fsm] RRC is closing, release malloced memory!.\n");
    22c0:	c7 04 24 e4 03 00 00 	movl   $0x3e4,(%esp)
    22c7:	e8 fc ff ff ff       	call   22c8 <rrc_close+0x18>


	if(paging != NULL)
    22cc:	a1 00 00 00 00       	mov    0x0,%eax
    22d1:	85 c0                	test   %eax,%eax
    22d3:	74 0f                	je     22e4 <rrc_close+0x34>
	{
		fsm_mem_free(paging);
    22d5:	e8 fc ff ff ff       	call   22d6 <rrc_close+0x26>
		paging=NULL;
    22da:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    22e1:	00 00 00 
	}
	if(mib != NULL)
    22e4:	a1 00 00 00 00       	mov    0x0,%eax
    22e9:	85 c0                	test   %eax,%eax
    22eb:	74 0f                	je     22fc <rrc_close+0x4c>
	{
		fsm_mem_free(mib);
    22ed:	e8 fc ff ff ff       	call   22ee <rrc_close+0x3e>
		mib=NULL;
    22f2:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    22f9:	00 00 00 
	}
	if(si != NULL)
    22fc:	a1 00 00 00 00       	mov    0x0,%eax
    2301:	85 c0                	test   %eax,%eax
    2303:	74 0f                	je     2314 <rrc_close+0x64>
	{
		fsm_mem_free(si);
    2305:	e8 fc ff ff ff       	call   2306 <rrc_close+0x56>
		si=NULL;
    230a:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    2311:	00 00 00 
	}
	if(sib1 != NULL)
    2314:	a1 00 00 00 00       	mov    0x0,%eax
    2319:	85 c0                	test   %eax,%eax
    231b:	74 0f                	je     232c <rrc_close+0x7c>
	{
		fsm_mem_free(sib1);
    231d:	e8 fc ff ff ff       	call   231e <rrc_close+0x6e>
		sib1=NULL;
    2322:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    2329:	00 00 00 
	}
	if(rrcConnectionReject != NULL)
    232c:	a1 00 00 00 00       	mov    0x0,%eax
    2331:	85 c0                	test   %eax,%eax
    2333:	74 0f                	je     2344 <rrc_close+0x94>
	{
		fsm_mem_free(rrcConnectionReject);
    2335:	e8 fc ff ff ff       	call   2336 <rrc_close+0x86>
		rrcConnectionReject=NULL;
    233a:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    2341:	00 00 00 
	}
	if(rrcConnectionSetup != NULL)
    2344:	a1 00 00 00 00       	mov    0x0,%eax
    2349:	85 c0                	test   %eax,%eax
    234b:	74 0f                	je     235c <rrc_close+0xac>
	{
		fsm_mem_free(rrcConnectionSetup);
    234d:	e8 fc ff ff ff       	call   234e <rrc_close+0x9e>
		rrcConnectionSetup=NULL;
    2352:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    2359:	00 00 00 
	}
	if(rrcConnectionReconfiguration != NULL)
    235c:	a1 00 00 00 00       	mov    0x0,%eax
    2361:	85 c0                	test   %eax,%eax
    2363:	74 0f                	je     2374 <rrc_close+0xc4>
	{
		fsm_mem_free(rrcConnectionReconfiguration);
    2365:	e8 fc ff ff ff       	call   2366 <rrc_close+0xb6>
		rrcConnectionReconfiguration=NULL;
    236a:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    2371:	00 00 00 
	}
	if(rrcConnectionRelease != NULL)
    2374:	a1 00 00 00 00       	mov    0x0,%eax
    2379:	85 c0                	test   %eax,%eax
    237b:	74 0f                	je     238c <rrc_close+0xdc>
	{
		fsm_mem_free(rrcConnectionRelease);
    237d:	e8 fc ff ff ff       	call   237e <rrc_close+0xce>
		rrcConnectionRelease=NULL;
    2382:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    2389:	00 00 00 
	}

	if(ueCellReselectionPriorityList!=NULL)
    238c:	a1 00 00 00 00       	mov    0x0,%eax
    2391:	85 c0                	test   %eax,%eax
    2393:	74 0f                	je     23a4 <rrc_close+0xf4>
	{
		fsm_mem_free(ueCellReselectionPriorityList);
    2395:	e8 fc ff ff ff       	call   2396 <rrc_close+0xe6>
			ueCellReselectionPriorityList=NULL;
    239a:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    23a1:	00 00 00 
	{
		fsm_mem_free(ueFreqPriorityList);
		ueFreqPriorityList=NULL;
	}
*/
	stop_timer();
    23a4:	e8 fc ff ff ff       	call   23a5 <rrc_close+0xf5>
	release_radio_resource();
    23a9:	e8 fc ff ff ff       	call   23aa <rrc_close+0xfa>
	FOUT;
}
    23ae:	c9                   	leave  
    23af:	c3                   	ret    

000023b0 <rrc_ioctl_handler>:
 **-------------------------------------- --------------------
 ** Modified by: Liu yingtao
 ** Modified Date: 
 ******************************************************************************/
static void rrc_ioctl_handler(void)
{
    23b0:	55                   	push   %ebp
    23b1:	89 e5                	mov    %esp,%ebp
    23b3:	83 ec 04             	sub    $0x4,%esp
    23b6:	e8 fc ff ff ff       	call   23b7 <rrc_ioctl_handler+0x7>
	FIN(rrc_ioctl_handler());
	SV_PTR_GET(rrc_sv);
    23bb:	e8 fc ff ff ff       	call   23bc <rrc_ioctl_handler+0xc>
	fsm_printf("[rrc] [fsm] in rrc_ioctl_handler().\n");
    23c0:	c7 04 24 1c 04 00 00 	movl   $0x41c,(%esp)
    23c7:	e8 fc ff ff ff       	call   23c8 <rrc_ioctl_handler+0x18>

	switch(fsm_ev_ioctrl_cmd())
    23cc:	e8 fc ff ff ff       	call   23cd <rrc_ioctl_handler+0x1d>
    23d1:	83 f8 24             	cmp    $0x24,%eax
    23d4:	76 12                	jbe    23e8 <rrc_ioctl_handler+0x38>
		case IOCCMD_MACTORRC_REPORT_CRNTI:
			//fsm_schedule_self(0, );
			FOUT;

		default:
			fsm_printf("[rrc] [fsm] Unrecognized I/O control command.\n");
    23d6:	c7 04 24 44 04 00 00 	movl   $0x444,(%esp)
    23dd:	e8 fc ff ff ff       	call   23de <rrc_ioctl_handler+0x2e>
			FOUT;
	}

}
    23e2:	c9                   	leave  
    23e3:	c3                   	ret    
    23e4:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
{
	FIN(rrc_ioctl_handler());
	SV_PTR_GET(rrc_sv);
	fsm_printf("[rrc] [fsm] in rrc_ioctl_handler().\n");

	switch(fsm_ev_ioctrl_cmd())
    23e8:	ff 24 85 20 01 00 00 	jmp    *0x120(,%eax,4)
    23ef:	90                   	nop
		case IOCCMD_USTORRC_RRC_CONN_REQ:
			fsm_schedule_self(0, CODE_CONN_REQ_FROM_NAS);
			FOUT;

		case IOCCMD_USTORRC_RRC_CONN_RELEASE:
			fsm_schedule_self(0, CODE_RCV_RRC_CONN_RELEASE);
    23f0:	ba 07 00 00 00       	mov    $0x7,%edx
    23f5:	31 c0                	xor    %eax,%eax
    23f7:	90                   	nop
    23f8:	e8 fc ff ff ff       	call   23f9 <rrc_ioctl_handler+0x49>
		default:
			fsm_printf("[rrc] [fsm] Unrecognized I/O control command.\n");
			FOUT;
	}

}
    23fd:	c9                   	leave  
    23fe:	66 90                	xchg   %ax,%ax
    2400:	c3                   	ret    
    2401:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
		case IOCCMD_USTORRC_CELL_ACCESS:
			fsm_schedule_self(0, CODE_BEGIN_RECV_SYSINFO);
			FOUT;

		case IOCCMD_USTORRC_RRC_CONN_REQ:
			fsm_schedule_self(0, CODE_CONN_REQ_FROM_NAS);
    2408:	ba 02 00 00 00       	mov    $0x2,%edx
    240d:	31 c0                	xor    %eax,%eax
    240f:	e8 fc ff ff ff       	call   2410 <rrc_ioctl_handler+0x60>
		default:
			fsm_printf("[rrc] [fsm] Unrecognized I/O control command.\n");
			FOUT;
	}

}
    2414:	c9                   	leave  
    2415:	c3                   	ret    
    2416:	66 90                	xchg   %ax,%ax
	fsm_printf("[rrc] [fsm] in rrc_ioctl_handler().\n");

	switch(fsm_ev_ioctrl_cmd())
	{
		case IOCCMD_USTORRC_CELL_ACCESS:
			fsm_schedule_self(0, CODE_BEGIN_RECV_SYSINFO);
    2418:	31 d2                	xor    %edx,%edx
    241a:	31 c0                	xor    %eax,%eax
    241c:	e8 fc ff ff ff       	call   241d <rrc_ioctl_handler+0x6d>
		default:
			fsm_printf("[rrc] [fsm] Unrecognized I/O control command.\n");
			FOUT;
	}

}
    2421:	c9                   	leave  
    2422:	c3                   	ret    
    2423:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    2429:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00002430 <other_events_handler>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
static void other_events_handler()
{
    2430:	55                   	push   %ebp
    2431:	89 e5                	mov    %esp,%ebp
    2433:	57                   	push   %edi
    2434:	56                   	push   %esi
    2435:	53                   	push   %ebx
    2436:	81 ec 28 02 00 00    	sub    $0x228,%esp
    243c:	e8 fc ff ff ff       	call   243d <other_events_handler+0xd>
	FIN(other_events_handler());

	SV_PTR_GET(rrc_sv);
    2441:	e8 fc ff ff ff       	call   2442 <other_events_handler+0x12>
	fsm_printf("[rrc] [fsm] other_events_handler().\n");
    2446:	c7 04 24 74 04 00 00 	movl   $0x474,(%esp)
    244d:	e8 fc ff ff ff       	call   244e <other_events_handler+0x1e>

	int *state=fsm_current_state_ptr_get();
    2452:	e8 fc ff ff ff       	call   2453 <other_events_handler+0x23>
    2457:	89 c3                	mov    %eax,%ebx
	if (Evt_RCV_PAGING && (*state ==7|| *state ==11))
    2459:	e8 fc ff ff ff       	call   245a <other_events_handler+0x2a>
    245e:	83 f8 03             	cmp    $0x3,%eax
    2461:	74 7d                	je     24e0 <other_events_handler+0xb0>

		fsm_printf("[rrc] [fsm] handle paging successfully.\n");

	}

	else if(Evt_RCV_MIB && (*state ==5||*state ==7|| *state ==11) )
    2463:	e8 fc ff ff ff       	call   2464 <other_events_handler+0x34>
    2468:	83 f8 03             	cmp    $0x3,%eax
    246b:	0f 84 cf 00 00 00    	je     2540 <other_events_handler+0x110>
		{
			fsm_printf("[rrc] [fsm] receive all system information and current fsm state is ST_IDLE_WAIT_SYSINFO, transit to ST_IDLE_NORMALLY.\n");
			fsm_schedule_self(0, CODE_END_RECV_SYSINFO);
		}
	}
	else if(Evt_RCV_SIB1 && (*state ==5||*state ==7|| *state ==11))
    2471:	e8 fc ff ff ff       	call   2472 <other_events_handler+0x42>
    2476:	83 f8 03             	cmp    $0x3,%eax
    2479:	0f 84 49 01 00 00    	je     25c8 <other_events_handler+0x198>
    247f:	90                   	nop
		{
			fsm_printf("[rrc] [fsm] receive all system information and current fsm state is ST_IDLE_WAIT_SYSINFO, transit to ST_IDLE_NORMALLY.\n");
			fsm_schedule_self(0, CODE_END_RECV_SYSINFO);
		}
	}
	else if(Evt_RCV_SI && (*state ==5||*state ==7|| *state ==11))
    2480:	e8 fc ff ff ff       	call   2481 <other_events_handler+0x51>
    2485:	83 f8 03             	cmp    $0x3,%eax
    2488:	0f 84 a2 01 00 00    	je     2630 <other_events_handler+0x200>
    248e:	66 90                	xchg   %ax,%ax
		}

		fsm_printf("[rrc] [fsm] handle SI successfully.\n");
	}

	else if(Evt_TimeOut_T302)
    2490:	e8 fc ff ff ff       	call   2491 <other_events_handler+0x61>
    2495:	83 f8 03             	cmp    $0x3,%eax
    2498:	0f 84 ea 01 00 00    	je     2688 <other_events_handler+0x258>
    249e:	66 90                	xchg   %ax,%ax
	{
		//fix me: T302 timeout
	}
	else if(Evt_TimeOut_T305)
    24a0:	e8 fc ff ff ff       	call   24a1 <other_events_handler+0x71>
    24a5:	83 f8 03             	cmp    $0x3,%eax
    24a8:	0f 84 f8 01 00 00    	je     26a6 <other_events_handler+0x276>
    24ae:	66 90                	xchg   %ax,%ax
	{
		//fix me: T305 timeout
	}
	else if(Evt_TimeOut_T320)
    24b0:	e8 fc ff ff ff       	call   24b1 <other_events_handler+0x81>
    24b5:	83 f8 03             	cmp    $0x3,%eax
    24b8:	0f 84 08 02 00 00    	je     26c6 <other_events_handler+0x296>
    24be:	66 90                	xchg   %ax,%ax
	{
		//fix me: T320 timeout
	}
	else if(Evt_TimeOut_T321)
    24c0:	e8 fc ff ff ff       	call   24c1 <other_events_handler+0x91>
    24c5:	83 f8 03             	cmp    $0x3,%eax
    24c8:	0f 84 18 02 00 00    	je     26e6 <other_events_handler+0x2b6>
	{
		//fix me: T321 timeout
	}
	FOUT;
}
    24ce:	81 c4 28 02 00 00    	add    $0x228,%esp
    24d4:	5b                   	pop    %ebx
    24d5:	5e                   	pop    %esi
    24d6:	5f                   	pop    %edi
    24d7:	5d                   	pop    %ebp
    24d8:	c3                   	ret    
    24d9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

	SV_PTR_GET(rrc_sv);
	fsm_printf("[rrc] [fsm] other_events_handler().\n");

	int *state=fsm_current_state_ptr_get();
	if (Evt_RCV_PAGING && (*state ==7|| *state ==11))
    24e0:	e8 fc ff ff ff       	call   24e1 <other_events_handler+0xb1>
    24e5:	83 f8 0e             	cmp    $0xe,%eax
    24e8:	0f 85 75 ff ff ff    	jne    2463 <other_events_handler+0x33>
    24ee:	8b 03                	mov    (%ebx),%eax
    24f0:	83 f8 0b             	cmp    $0xb,%eax
    24f3:	74 09                	je     24fe <other_events_handler+0xce>
    24f5:	83 f8 07             	cmp    $0x7,%eax
    24f8:	0f 85 65 ff ff ff    	jne    2463 <other_events_handler+0x33>
	{
		fsm_printf("[rrc] [fsm] start to handle paging.\n");
    24fe:	c7 04 24 9c 04 00 00 	movl   $0x49c,(%esp)
    2505:	e8 fc ff ff ff       	call   2506 <other_events_handler+0xd6>
		if(*state ==7 && paging->havePagingRecord==true)
    250a:	83 3b 07             	cmpl   $0x7,(%ebx)
    250d:	0f 84 4a 02 00 00    	je     275d <other_events_handler+0x32d>
		{
			CheckPagingRecord(paging->pagingRecordList,ue_Identity);
    2513:	a1 00 00 00 00       	mov    0x0,%eax
		}

		if (paging->systemInfoModification==true)
    2518:	80 b8 d4 01 00 00 00 	cmpb   $0x0,0x1d4(%eax)
    251f:	74 11                	je     2532 <other_events_handler+0x102>
		{
			fsm_printf("[rrc] [fsm] paging.systemInfoModification==true, renew the system information from enb.\n");
    2521:	c7 04 24 c4 04 00 00 	movl   $0x4c4,(%esp)
    2528:	e8 fc ff ff ff       	call   2529 <other_events_handler+0xf9>
			Begin_recv_sysinfo();
    252d:	e8 fc ff ff ff       	call   252e <other_events_handler+0xfe>
		}

		fsm_printf("[rrc] [fsm] handle paging successfully.\n");
    2532:	c7 04 24 20 05 00 00 	movl   $0x520,(%esp)
    2539:	e8 fc ff ff ff       	call   253a <other_events_handler+0x10a>

	SV_PTR_GET(rrc_sv);
	fsm_printf("[rrc] [fsm] other_events_handler().\n");

	int *state=fsm_current_state_ptr_get();
	if (Evt_RCV_PAGING && (*state ==7|| *state ==11))
    253e:	eb 8e                	jmp    24ce <other_events_handler+0x9e>

		fsm_printf("[rrc] [fsm] handle paging successfully.\n");

	}

	else if(Evt_RCV_MIB && (*state ==5||*state ==7|| *state ==11) )
    2540:	e8 fc ff ff ff       	call   2541 <other_events_handler+0x111>
    2545:	83 f8 0f             	cmp    $0xf,%eax
    2548:	0f 85 23 ff ff ff    	jne    2471 <other_events_handler+0x41>
    254e:	8b 03                	mov    (%ebx),%eax
    2550:	83 f8 07             	cmp    $0x7,%eax
    2553:	74 11                	je     2566 <other_events_handler+0x136>
    2555:	83 f8 05             	cmp    $0x5,%eax
    2558:	74 0c                	je     2566 <other_events_handler+0x136>
    255a:	83 f8 0b             	cmp    $0xb,%eax
    255d:	8d 76 00             	lea    0x0(%esi),%esi
    2560:	0f 85 0b ff ff ff    	jne    2471 <other_events_handler+0x41>
	{
		m_receivedmib=true;
		DoReceiveMIB(mib);
    2566:	a1 00 00 00 00       	mov    0x0,%eax

	}

	else if(Evt_RCV_MIB && (*state ==5||*state ==7|| *state ==11) )
	{
		m_receivedmib=true;
    256b:	c6 05 00 00 00 00 01 	movb   $0x1,0x0
		DoReceiveMIB(mib);
    2572:	e8 fc ff ff ff       	call   2573 <other_events_handler+0x143>

		if(*state==5 && m_receivedmib==true && m_receivedsib1==true && m_receivedSib2==true)
    2577:	83 3b 05             	cmpl   $0x5,(%ebx)
    257a:	0f 85 4e ff ff ff    	jne    24ce <other_events_handler+0x9e>
		m_receivedsib1=true;
		fsm_printf("[rrc] [fsm] start to handle SIB1 .\n");
		SendCellAccessRelatedInfotoUS(sib1->cellAccessRelatedInfo);
		fsm_printf("[rrc] [fsm] handle SIB1 successfully.\n");

		if(*state==5 && m_receivedmib==true && m_receivedsib1==true && m_receivedSib2==true)
    2580:	80 3d 00 00 00 00 00 	cmpb   $0x0,0x0
    2587:	0f 84 41 ff ff ff    	je     24ce <other_events_handler+0x9e>
    258d:	80 3d 00 00 00 00 00 	cmpb   $0x0,0x0
    2594:	0f 84 34 ff ff ff    	je     24ce <other_events_handler+0x9e>
    259a:	80 3d 00 00 00 00 00 	cmpb   $0x0,0x0
    25a1:	0f 84 27 ff ff ff    	je     24ce <other_events_handler+0x9e>
		{
			fsm_printf("[rrc] [fsm] receive all system information and current fsm state is ST_IDLE_WAIT_SYSINFO, transit to ST_IDLE_NORMALLY.\n");
    25a7:	c7 04 24 4c 05 00 00 	movl   $0x54c,(%esp)
    25ae:	e8 fc ff ff ff       	call   25af <other_events_handler+0x17f>
			fsm_schedule_self(0, CODE_END_RECV_SYSINFO);
    25b3:	ba 01 00 00 00       	mov    $0x1,%edx
    25b8:	31 c0                	xor    %eax,%eax
    25ba:	e8 fc ff ff ff       	call   25bb <other_events_handler+0x18b>
    25bf:	e9 0a ff ff ff       	jmp    24ce <other_events_handler+0x9e>
    25c4:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
		{
			fsm_printf("[rrc] [fsm] receive all system information and current fsm state is ST_IDLE_WAIT_SYSINFO, transit to ST_IDLE_NORMALLY.\n");
			fsm_schedule_self(0, CODE_END_RECV_SYSINFO);
		}
	}
	else if(Evt_RCV_SIB1 && (*state ==5||*state ==7|| *state ==11))
    25c8:	e8 fc ff ff ff       	call   25c9 <other_events_handler+0x199>
    25cd:	83 f8 10             	cmp    $0x10,%eax
    25d0:	0f 85 a9 fe ff ff    	jne    247f <other_events_handler+0x4f>
    25d6:	8b 03                	mov    (%ebx),%eax
    25d8:	83 f8 07             	cmp    $0x7,%eax
    25db:	74 0e                	je     25eb <other_events_handler+0x1bb>
    25dd:	83 f8 05             	cmp    $0x5,%eax
    25e0:	74 09                	je     25eb <other_events_handler+0x1bb>
    25e2:	83 f8 0b             	cmp    $0xb,%eax
    25e5:	0f 85 94 fe ff ff    	jne    247f <other_events_handler+0x4f>
	{
		m_receivedsib1=true;
    25eb:	c6 05 00 00 00 00 01 	movb   $0x1,0x0
		fsm_printf("[rrc] [fsm] start to handle SIB1 .\n");
    25f2:	c7 04 24 c4 05 00 00 	movl   $0x5c4,(%esp)
    25f9:	e8 fc ff ff ff       	call   25fa <other_events_handler+0x1ca>
		SendCellAccessRelatedInfotoUS(sib1->cellAccessRelatedInfo);
    25fe:	8b 35 00 00 00 00    	mov    0x0,%esi
    2604:	b9 30 00 00 00       	mov    $0x30,%ecx
    2609:	89 e7                	mov    %esp,%edi
    260b:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    260d:	e8 fc ff ff ff       	call   260e <other_events_handler+0x1de>
		fsm_printf("[rrc] [fsm] handle SIB1 successfully.\n");
    2612:	c7 04 24 e8 05 00 00 	movl   $0x5e8,(%esp)
    2619:	e8 fc ff ff ff       	call   261a <other_events_handler+0x1ea>

		if(*state==5 && m_receivedmib==true && m_receivedsib1==true && m_receivedSib2==true)
    261e:	83 3b 05             	cmpl   $0x5,(%ebx)
    2621:	0f 85 a7 fe ff ff    	jne    24ce <other_events_handler+0x9e>
    2627:	e9 54 ff ff ff       	jmp    2580 <other_events_handler+0x150>
    262c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
		{
			fsm_printf("[rrc] [fsm] receive all system information and current fsm state is ST_IDLE_WAIT_SYSINFO, transit to ST_IDLE_NORMALLY.\n");
			fsm_schedule_self(0, CODE_END_RECV_SYSINFO);
		}
	}
	else if(Evt_RCV_SI && (*state ==5||*state ==7|| *state ==11))
    2630:	e8 fc ff ff ff       	call   2631 <other_events_handler+0x201>
    2635:	83 f8 11             	cmp    $0x11,%eax
    2638:	0f 85 50 fe ff ff    	jne    248e <other_events_handler+0x5e>
    263e:	8b 03                	mov    (%ebx),%eax
    2640:	83 f8 07             	cmp    $0x7,%eax
    2643:	74 11                	je     2656 <other_events_handler+0x226>
    2645:	83 f8 05             	cmp    $0x5,%eax
    2648:	74 0c                	je     2656 <other_events_handler+0x226>
    264a:	83 f8 0b             	cmp    $0xb,%eax
    264d:	8d 76 00             	lea    0x0(%esi),%esi
    2650:	0f 85 38 fe ff ff    	jne    248e <other_events_handler+0x5e>
	{
		fsm_printf("[rrc] [fsm] start to handle SI .\n");
    2656:	c7 04 24 10 06 00 00 	movl   $0x610,(%esp)
    265d:	e8 fc ff ff ff       	call   265e <other_events_handler+0x22e>
		if(si->haveSib2==true)
    2662:	8b 35 00 00 00 00    	mov    0x0,%esi
    2668:	80 3e 00             	cmpb   $0x0,(%esi)
    266b:	0f 85 87 00 00 00    	jne    26f8 <other_events_handler+0x2c8>
				fsm_printf("[rrc] [fsm] receive all system information and current fsm state is ST_IDLE_WAIT_SYSINFO, transit to ST_IDLE_NORMALLY.\n");
				fsm_schedule_self(0, CODE_END_RECV_SYSINFO);
			}
		}

		fsm_printf("[rrc] [fsm] handle SI successfully.\n");
    2671:	c7 04 24 34 06 00 00 	movl   $0x634,(%esp)
    2678:	e8 fc ff ff ff       	call   2679 <other_events_handler+0x249>
		{
			fsm_printf("[rrc] [fsm] receive all system information and current fsm state is ST_IDLE_WAIT_SYSINFO, transit to ST_IDLE_NORMALLY.\n");
			fsm_schedule_self(0, CODE_END_RECV_SYSINFO);
		}
	}
	else if(Evt_RCV_SI && (*state ==5||*state ==7|| *state ==11))
    267d:	e9 4c fe ff ff       	jmp    24ce <other_events_handler+0x9e>
    2682:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
		}

		fsm_printf("[rrc] [fsm] handle SI successfully.\n");
	}

	else if(Evt_TimeOut_T302)
    2688:	e8 fc ff ff ff       	call   2689 <other_events_handler+0x259>
    268d:	83 f8 12             	cmp    $0x12,%eax
    2690:	0f 84 38 fe ff ff    	je     24ce <other_events_handler+0x9e>
	{
		//fix me: T302 timeout
	}
	else if(Evt_TimeOut_T305)
    2696:	e8 fc ff ff ff       	call   2697 <other_events_handler+0x267>
    269b:	83 f8 03             	cmp    $0x3,%eax
    269e:	66 90                	xchg   %ax,%ax
    26a0:	0f 85 08 fe ff ff    	jne    24ae <other_events_handler+0x7e>
    26a6:	e8 fc ff ff ff       	call   26a7 <other_events_handler+0x277>
    26ab:	83 f8 13             	cmp    $0x13,%eax
    26ae:	66 90                	xchg   %ax,%ax
    26b0:	0f 84 18 fe ff ff    	je     24ce <other_events_handler+0x9e>
	{
		//fix me: T305 timeout
	}
	else if(Evt_TimeOut_T320)
    26b6:	e8 fc ff ff ff       	call   26b7 <other_events_handler+0x287>
    26bb:	83 f8 03             	cmp    $0x3,%eax
    26be:	66 90                	xchg   %ax,%ax
    26c0:	0f 85 f8 fd ff ff    	jne    24be <other_events_handler+0x8e>
    26c6:	e8 fc ff ff ff       	call   26c7 <other_events_handler+0x297>
    26cb:	83 f8 14             	cmp    $0x14,%eax
    26ce:	66 90                	xchg   %ax,%ax
    26d0:	0f 84 f8 fd ff ff    	je     24ce <other_events_handler+0x9e>
	{
		//fix me: T320 timeout
	}
	else if(Evt_TimeOut_T321)
    26d6:	e8 fc ff ff ff       	call   26d7 <other_events_handler+0x2a7>
    26db:	83 f8 03             	cmp    $0x3,%eax
    26de:	66 90                	xchg   %ax,%ax
    26e0:	0f 85 e8 fd ff ff    	jne    24ce <other_events_handler+0x9e>
    26e6:	e8 fc ff ff ff       	call   26e7 <other_events_handler+0x2b7>
	{
		//fix me: T321 timeout
	}
	FOUT;
}
    26eb:	81 c4 28 02 00 00    	add    $0x228,%esp
    26f1:	5b                   	pop    %ebx
    26f2:	5e                   	pop    %esi
    26f3:	5f                   	pop    %edi
    26f4:	5d                   	pop    %ebp
    26f5:	c3                   	ret    
    26f6:	66 90                	xchg   %ax,%ax
	else if(Evt_RCV_SI && (*state ==5||*state ==7|| *state ==11))
	{
		fsm_printf("[rrc] [fsm] start to handle SI .\n");
		if(si->haveSib2==true)
		{
			m_receivedSib2=true;
    26f8:	c6 05 00 00 00 00 01 	movb   $0x1,0x0
			if(si->sib2.haveMBSFN_SubframeConfigList==true)
			{
			}

			ApplyRadioResourceConfigCommon(si->sib2.radioResourceConfigCommon);
    26ff:	83 c6 24             	add    $0x24,%esi
    2702:	89 e7                	mov    %esp,%edi
    2704:	b9 2f 00 00 00       	mov    $0x2f,%ecx
    2709:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    270b:	e8 fc ff ff ff       	call   270c <other_events_handler+0x2dc>

			if(*state==5 && m_receivedmib==true && m_receivedsib1==true && m_receivedSib2==true)
    2710:	83 3b 05             	cmpl   $0x5,(%ebx)
    2713:	0f 85 58 ff ff ff    	jne    2671 <other_events_handler+0x241>
    2719:	80 3d 00 00 00 00 00 	cmpb   $0x0,0x0
    2720:	0f 84 4b ff ff ff    	je     2671 <other_events_handler+0x241>
    2726:	80 3d 00 00 00 00 00 	cmpb   $0x0,0x0
    272d:	0f 84 3e ff ff ff    	je     2671 <other_events_handler+0x241>
    2733:	80 3d 00 00 00 00 00 	cmpb   $0x0,0x0
    273a:	0f 84 31 ff ff ff    	je     2671 <other_events_handler+0x241>
			{
				fsm_printf("[rrc] [fsm] receive all system information and current fsm state is ST_IDLE_WAIT_SYSINFO, transit to ST_IDLE_NORMALLY.\n");
    2740:	c7 04 24 4c 05 00 00 	movl   $0x54c,(%esp)
    2747:	e8 fc ff ff ff       	call   2748 <other_events_handler+0x318>
				fsm_schedule_self(0, CODE_END_RECV_SYSINFO);
    274c:	ba 01 00 00 00       	mov    $0x1,%edx
    2751:	31 c0                	xor    %eax,%eax
    2753:	e8 fc ff ff ff       	call   2754 <other_events_handler+0x324>
    2758:	e9 14 ff ff ff       	jmp    2671 <other_events_handler+0x241>

	int *state=fsm_current_state_ptr_get();
	if (Evt_RCV_PAGING && (*state ==7|| *state ==11))
	{
		fsm_printf("[rrc] [fsm] start to handle paging.\n");
		if(*state ==7 && paging->havePagingRecord==true)
    275d:	a1 00 00 00 00       	mov    0x0,%eax
    2762:	80 38 00             	cmpb   $0x0,(%eax)
    2765:	0f 84 ad fd ff ff    	je     2518 <other_events_handler+0xe8>
		{
			CheckPagingRecord(paging->pagingRecordList,ue_Identity);
    276b:	8d bc 24 d0 01 00 00 	lea    0x1d0(%esp),%edi
    2772:	be 00 00 00 00       	mov    $0x0,%esi
    2777:	b9 16 00 00 00       	mov    $0x16,%ecx
    277c:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    277e:	8d 70 04             	lea    0x4(%eax),%esi
    2781:	89 e7                	mov    %esp,%edi
    2783:	b1 74                	mov    $0x74,%cl
    2785:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    2787:	e8 fc ff ff ff       	call   2788 <other_events_handler+0x358>
    278c:	e9 82 fd ff ff       	jmp    2513 <other_events_handler+0xe3>
    2791:	eb 0d                	jmp    27a0 <transit_to_idle_connecting>
    2793:	90                   	nop
    2794:	90                   	nop
    2795:	90                   	nop
    2796:	90                   	nop
    2797:	90                   	nop
    2798:	90                   	nop
    2799:	90                   	nop
    279a:	90                   	nop
    279b:	90                   	nop
    279c:	90                   	nop
    279d:	90                   	nop
    279e:	90                   	nop
    279f:	90                   	nop

000027a0 <transit_to_idle_connecting>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
static void transit_to_idle_connecting(void)
{
    27a0:	55                   	push   %ebp
    27a1:	89 e5                	mov    %esp,%ebp
    27a3:	57                   	push   %edi
    27a4:	56                   	push   %esi
    27a5:	53                   	push   %ebx
    27a6:	81 ec 4c 02 00 00    	sub    $0x24c,%esp
    27ac:	e8 fc ff ff ff       	call   27ad <transit_to_idle_connecting+0xd>

	FIN(transit_to_idle_connecting());
	fsm_printf("[rrc] [fsm] transit_to_idle_connecting().\n");
    27b1:	c7 04 24 5c 06 00 00 	movl   $0x65c,(%esp)

	struct RadioResourceConfigDedicated *radioResourceConfigdefault;
	radioResourceConfigdefault = gen_Defaultradioresource ();          
	struct PhysicalConfigDedicated physicalConfigdefault;
	physicalConfigdefault = radioResourceConfigdefault->physicalConfigDedicated ; 
    27b8:	8d bd 88 fe ff ff    	lea    -0x178(%ebp),%edi
 ******************************************************************************/
static void transit_to_idle_connecting(void)
{

	FIN(transit_to_idle_connecting());
	fsm_printf("[rrc] [fsm] transit_to_idle_connecting().\n");
    27be:	e8 fc ff ff ff       	call   27bf <transit_to_idle_connecting+0x1f>

	struct RadioResourceConfigDedicated *radioResourceConfigdefault;
	radioResourceConfigdefault = gen_Defaultradioresource ();          
    27c3:	e8 fc ff ff ff       	call   27c4 <transit_to_idle_connecting+0x24>
	struct PhysicalConfigDedicated physicalConfigdefault;
	physicalConfigdefault = radioResourceConfigdefault->physicalConfigDedicated ; 
    27c8:	b9 36 00 00 00       	mov    $0x36,%ecx
    27cd:	8d b0 14 04 00 00    	lea    0x414(%eax),%esi

	FIN(transit_to_idle_connecting());
	fsm_printf("[rrc] [fsm] transit_to_idle_connecting().\n");

	struct RadioResourceConfigDedicated *radioResourceConfigdefault;
	radioResourceConfigdefault = gen_Defaultradioresource ();          
    27d3:	89 c3                	mov    %eax,%ebx
	struct PhysicalConfigDedicated physicalConfigdefault;
	physicalConfigdefault = radioResourceConfigdefault->physicalConfigDedicated ; 
    27d5:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
	struct SPS_Config sps_Configdefault;
	sps_Configdefault = radioResourceConfigdefault->sps_Config;     
    27d7:	8d 7d b0             	lea    -0x50(%ebp),%edi
    27da:	8d b0 cc 03 00 00    	lea    0x3cc(%eax),%esi
    27e0:	b1 11                	mov    $0x11,%cl
    27e2:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
	struct MAC_MainConfig mac_MainConfigdefault;
	mac_MainConfigdefault = radioResourceConfigdefault->mac_MainConfig;    
    27e4:	8d bd 60 ff ff ff    	lea    -0xa0(%ebp),%edi
    27ea:	8d b0 78 03 00 00    	lea    0x378(%eax),%esi
    27f0:	b1 14                	mov    $0x14,%cl
    27f2:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
	struct SystemInformationBlockType2 *TimeAlignmentTimerCommontest;
	TimeAlignmentTimerCommontest = gen_sysInfoTimer();
	struct UL_CCCH_Message *ulccchRRCrequestmsg;
	ulccchRRCrequestmsg = gen_ul_ccchmsg_send_rrcquest();                 

	set_default_physical_channel(physicalConfigdefault);
    27f4:	8d b5 88 fe ff ff    	lea    -0x178(%ebp),%esi
	sps_Configdefault = radioResourceConfigdefault->sps_Config;     
	struct MAC_MainConfig mac_MainConfigdefault;
	mac_MainConfigdefault = radioResourceConfigdefault->mac_MainConfig;    

	struct SystemInformationBlockType2 *TimeAlignmentTimerCommontest;
	TimeAlignmentTimerCommontest = gen_sysInfoTimer();
    27fa:	e8 fc ff ff ff       	call   27fb <transit_to_idle_connecting+0x5b>
    27ff:	89 85 80 fe ff ff    	mov    %eax,-0x180(%ebp)
	struct UL_CCCH_Message *ulccchRRCrequestmsg;
	ulccchRRCrequestmsg = gen_ul_ccchmsg_send_rrcquest();                 
    2805:	e8 fc ff ff ff       	call   2806 <transit_to_idle_connecting+0x66>

	set_default_physical_channel(physicalConfigdefault);
    280a:	b9 36 00 00 00       	mov    $0x36,%ecx
	mac_MainConfigdefault = radioResourceConfigdefault->mac_MainConfig;    

	struct SystemInformationBlockType2 *TimeAlignmentTimerCommontest;
	TimeAlignmentTimerCommontest = gen_sysInfoTimer();
	struct UL_CCCH_Message *ulccchRRCrequestmsg;
	ulccchRRCrequestmsg = gen_ul_ccchmsg_send_rrcquest();                 
    280f:	89 85 84 fe ff ff    	mov    %eax,-0x17c(%ebp)

	set_default_physical_channel(physicalConfigdefault);
    2815:	89 e7                	mov    %esp,%edi
    2817:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
	set_default_semi_persistent (sps_Configdefault);
    2819:	8d 75 b0             	lea    -0x50(%ebp),%esi
	struct SystemInformationBlockType2 *TimeAlignmentTimerCommontest;
	TimeAlignmentTimerCommontest = gen_sysInfoTimer();
	struct UL_CCCH_Message *ulccchRRCrequestmsg;
	ulccchRRCrequestmsg = gen_ul_ccchmsg_send_rrcquest();                 

	set_default_physical_channel(physicalConfigdefault);
    281c:	e8 fc ff ff ff       	call   281d <transit_to_idle_connecting+0x7d>
	set_default_semi_persistent (sps_Configdefault);
    2821:	b9 11 00 00 00       	mov    $0x11,%ecx
    2826:	89 e7                	mov    %esp,%edi
    2828:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)

	fsm_printf("[rrc] [fsm] CCCH_Config we use the initial one ,so I do nothing here,if there may causes some problems,please contact me 3 Q .\n");

	set_default_MAC(mac_MainConfigdefault);
    282a:	8d b5 60 ff ff ff    	lea    -0xa0(%ebp),%esi
	TimeAlignmentTimerCommontest = gen_sysInfoTimer();
	struct UL_CCCH_Message *ulccchRRCrequestmsg;
	ulccchRRCrequestmsg = gen_ul_ccchmsg_send_rrcquest();                 

	set_default_physical_channel(physicalConfigdefault);
	set_default_semi_persistent (sps_Configdefault);
    2830:	e8 fc ff ff ff       	call   2831 <transit_to_idle_connecting+0x91>

	fsm_printf("[rrc] [fsm] CCCH_Config we use the initial one ,so I do nothing here,if there may causes some problems,please contact me 3 Q .\n");
    2835:	c7 04 24 88 06 00 00 	movl   $0x688,(%esp)
    283c:	e8 fc ff ff ff       	call   283d <transit_to_idle_connecting+0x9d>

	set_default_MAC(mac_MainConfigdefault);
    2841:	b9 14 00 00 00       	mov    $0x14,%ecx
    2846:	89 e7                	mov    %esp,%edi
    2848:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    284a:	e8 fc ff ff ff       	call   284b <transit_to_idle_connecting+0xab>
	set_timeAlignmentTimerCommon (TimeAlignmentTimerCommontest);
    284f:	8b 85 80 fe ff ff    	mov    -0x180(%ebp),%eax
    2855:	e8 fc ff ff ff       	call   2856 <transit_to_idle_connecting+0xb6>

	setTimer(TIMER_T300, 2000000); 
    285a:	ba 80 84 1e 00       	mov    $0x1e8480,%edx
    285f:	b8 2c 01 00 00       	mov    $0x12c,%eax
    2864:	e8 fc ff ff ff       	call   2865 <transit_to_idle_connecting+0xc5>
	fsm_printf("[rrc] [fsm] Time_T300 is starting, the duration is 2000ms.\n");
    2869:	c7 04 24 08 07 00 00 	movl   $0x708,(%esp)
    2870:	e8 fc ff ff ff       	call   2871 <transit_to_idle_connecting+0xd1>

	send_RRCConnectionRequest(ulccchRRCrequestmsg);
    2875:	8b 85 84 fe ff ff    	mov    -0x17c(%ebp),%eax
    287b:	e8 fc ff ff ff       	call   287c <transit_to_idle_connecting+0xdc>

	fsm_mem_free(radioResourceConfigdefault);
    2880:	89 d8                	mov    %ebx,%eax
    2882:	e8 fc ff ff ff       	call   2883 <transit_to_idle_connecting+0xe3>
	radioResourceConfigdefault = NULL;
	fsm_mem_free(TimeAlignmentTimerCommontest);
    2887:	8b 85 80 fe ff ff    	mov    -0x180(%ebp),%eax
    288d:	e8 fc ff ff ff       	call   288e <transit_to_idle_connecting+0xee>
	TimeAlignmentTimerCommontest = NULL;
	fsm_mem_free(ulccchRRCrequestmsg);
    2892:	8b 85 84 fe ff ff    	mov    -0x17c(%ebp),%eax
    2898:	e8 fc ff ff ff       	call   2899 <transit_to_idle_connecting+0xf9>
	ulccchRRCrequestmsg = NULL;

	FOUT;
}
    289d:	81 c4 4c 02 00 00    	add    $0x24c,%esp
    28a3:	5b                   	pop    %ebx
    28a4:	5e                   	pop    %esi
    28a5:	5f                   	pop    %edi
    28a6:	5d                   	pop    %ebp
    28a7:	c3                   	ret    
    28a8:	90                   	nop
    28a9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

000028b0 <rcv_rrc_conn_setup>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
static void rcv_rrc_conn_setup(void)
{
    28b0:	55                   	push   %ebp
    28b1:	89 e5                	mov    %esp,%ebp
    28b3:	81 ec b8 03 00 00    	sub    $0x3b8,%esp
    28b9:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    28bc:	89 75 f8             	mov    %esi,-0x8(%ebp)
    28bf:	89 7d fc             	mov    %edi,-0x4(%ebp)
    28c2:	e8 fc ff ff ff       	call   28c3 <rcv_rrc_conn_setup+0x13>
	FIN(rcv_rrc_conn_setup());

	fsm_printf("[rrc] [fsm] rcv_rrc_conn_setup().\n");
    28c7:	c7 04 24 44 07 00 00 	movl   $0x744,(%esp)
    28ce:	e8 fc ff ff ff       	call   28cf <rcv_rrc_conn_setup+0x1f>

	if(rrcConnectionSetup != NULL)
    28d3:	a1 00 00 00 00       	mov    0x0,%eax
    28d8:	85 c0                	test   %eax,%eax
    28da:	0f 84 d0 00 00 00    	je     29b0 <rcv_rrc_conn_setup+0x100>
	{
		struct SrbToAddModList srbToAddModList_setup;
		struct DrbToAddModList drbToAddModList_setup;
		struct UL_DCCH_Message *Ul_Dcch_rrccompletemsg;

		srbToAddModList_setup = rrcConnectionSetup->radioResourceConfigDedicated.srbToAddModList; 
    28e0:	8d 70 08             	lea    0x8(%eax),%esi
    28e3:	b9 1d 00 00 00       	mov    $0x1d,%ecx
    28e8:	8d 7d 80             	lea    -0x80(%ebp),%edi
    28eb:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
		drbToAddModList_setup = rrcConnectionSetup->radioResourceConfigDedicated.drbToAddModList;
    28ed:	8d b0 80 00 00 00    	lea    0x80(%eax),%esi
    28f3:	8d bd bc fc ff ff    	lea    -0x344(%ebp),%edi
	{
		struct SrbToAddModList srbToAddModList_setup;
		struct DrbToAddModList drbToAddModList_setup;
		struct UL_DCCH_Message *Ul_Dcch_rrccompletemsg;

		srbToAddModList_setup = rrcConnectionSetup->radioResourceConfigDedicated.srbToAddModList; 
    28f9:	8b 5d 80             	mov    -0x80(%ebp),%ebx
		drbToAddModList_setup = rrcConnectionSetup->radioResourceConfigDedicated.drbToAddModList;
    28fc:	b1 b1                	mov    $0xb1,%cl
    28fe:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
		fsm_printf("[rrc] drbToAddModList.num = %d\n", drbToAddModList_setup.num);
		fsm_printf("[rrc] srbToAddModList.num = %d\n", srbToAddModList_setup.num);
		ApplySrbToAdd(srbToAddModList_setup);
    2900:	8d 75 80             	lea    -0x80(%ebp),%esi
		struct DrbToAddModList drbToAddModList_setup;
		struct UL_DCCH_Message *Ul_Dcch_rrccompletemsg;

		srbToAddModList_setup = rrcConnectionSetup->radioResourceConfigDedicated.srbToAddModList; 
		drbToAddModList_setup = rrcConnectionSetup->radioResourceConfigDedicated.drbToAddModList;
		fsm_printf("[rrc] drbToAddModList.num = %d\n", drbToAddModList_setup.num);
    2903:	c7 04 24 68 07 00 00 	movl   $0x768,(%esp)
    290a:	8b 85 bc fc ff ff    	mov    -0x344(%ebp),%eax
    2910:	89 44 24 04          	mov    %eax,0x4(%esp)
    2914:	e8 fc ff ff ff       	call   2915 <rcv_rrc_conn_setup+0x65>
		fsm_printf("[rrc] srbToAddModList.num = %d\n", srbToAddModList_setup.num);
    2919:	89 5c 24 04          	mov    %ebx,0x4(%esp)
    291d:	c7 04 24 88 07 00 00 	movl   $0x788,(%esp)
    2924:	e8 fc ff ff ff       	call   2925 <rcv_rrc_conn_setup+0x75>
		ApplySrbToAdd(srbToAddModList_setup);
    2929:	b9 1d 00 00 00       	mov    $0x1d,%ecx
    292e:	89 5d 80             	mov    %ebx,-0x80(%ebp)
    2931:	89 e7                	mov    %esp,%edi
    2933:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    2935:	e8 fc ff ff ff       	call   2936 <rcv_rrc_conn_setup+0x86>
	//	ApplyDrbToAdd(drbToAddModList_setup);

		set_MAC_mainconfig(rrcConnectionSetup);
    293a:	a1 00 00 00 00       	mov    0x0,%eax
    293f:	e8 fc ff ff ff       	call   2940 <rcv_rrc_conn_setup+0x90>
		set_semi_persistent(rrcConnectionSetup);
    2944:	a1 00 00 00 00       	mov    0x0,%eax
    2949:	e8 fc ff ff ff       	call   294a <rcv_rrc_conn_setup+0x9a>
		set_physicalConfigDedicated(rrcConnectionSetup);
    294e:	a1 00 00 00 00       	mov    0x0,%eax
    2953:	e8 fc ff ff ff       	call   2954 <rcv_rrc_conn_setup+0xa4>

		cancleTimer(TIMER_T302); 
    2958:	b8 2e 01 00 00       	mov    $0x12e,%eax
    295d:	e8 fc ff ff ff       	call   295e <rcv_rrc_conn_setup+0xae>
		cancleTimer(TIMER_T305);
    2962:	b8 31 01 00 00       	mov    $0x131,%eax
    2967:	e8 fc ff ff ff       	call   2968 <rcv_rrc_conn_setup+0xb8>

		Ul_Dcch_rrccompletemsg = gen_ul_dcch_rrccomplete(); 
    296c:	e8 fc ff ff ff       	call   296d <rcv_rrc_conn_setup+0xbd>
    2971:	89 c3                	mov    %eax,%ebx
		send_RRCConnectionSetupComplete(Ul_Dcch_rrccompletemsg);
    2973:	e8 fc ff ff ff       	call   2974 <rcv_rrc_conn_setup+0xc4>

		fsm_mem_free(Ul_Dcch_rrccompletemsg);
    2978:	89 d8                	mov    %ebx,%eax
    297a:	e8 fc ff ff ff       	call   297b <rcv_rrc_conn_setup+0xcb>
		Ul_Dcch_rrccompletemsg = NULL;
		cancleTimer(TIMER_T300); 
    297f:	b8 2c 01 00 00       	mov    $0x12c,%eax
    2984:	e8 fc ff ff ff       	call   2985 <rcv_rrc_conn_setup+0xd5>

		fsm_mem_free(rrcConnectionSetup);
    2989:	a1 00 00 00 00       	mov    0x0,%eax
    298e:	e8 fc ff ff ff       	call   298f <rcv_rrc_conn_setup+0xdf>
		rrcConnectionSetup = NULL;
    2993:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    299a:	00 00 00 
		fsm_printf("[rrc] [fsm] rrcConnectionSetup is NULL\n");
	}

	FOUT;

}
    299d:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    29a0:	8b 75 f8             	mov    -0x8(%ebp),%esi
    29a3:	8b 7d fc             	mov    -0x4(%ebp),%edi
    29a6:	89 ec                	mov    %ebp,%esp
    29a8:	5d                   	pop    %ebp
    29a9:	c3                   	ret    
    29aa:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
		fsm_mem_free(rrcConnectionSetup);
		rrcConnectionSetup = NULL;
	}
	else
	{
		fsm_printf("[rrc] [fsm] rrcConnectionSetup is NULL\n");
    29b0:	c7 04 24 a8 07 00 00 	movl   $0x7a8,(%esp)
    29b7:	e8 fc ff ff ff       	call   29b8 <rcv_rrc_conn_setup+0x108>
    29bc:	eb df                	jmp    299d <rcv_rrc_conn_setup+0xed>
    29be:	66 90                	xchg   %ax,%ax

000029c0 <rrc_main>:
struct CellReselectionPriority *ueCellReselectionPriorityList = NULL; //zhouyang 2014/10/1



void rrc_main(void)
{
    29c0:	55                   	push   %ebp
    29c1:	89 e5                	mov    %esp,%ebp
    29c3:	83 ec 18             	sub    $0x18,%esp
    29c6:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    29c9:	89 75 f8             	mov    %esi,-0x8(%ebp)
    29cc:	89 7d fc             	mov    %edi,-0x4(%ebp)
    29cf:	e8 fc ff ff ff       	call   29d0 <rrc_main+0x10>
	FSM_ENTER(rrc_main);
    29d4:	e8 fc ff ff ff       	call   29d5 <rrc_main+0x15>
	FSM_BLOCK_SWITCH
    29d9:	83 38 0f             	cmpl   $0xf,(%eax)



void rrc_main(void)
{
	FSM_ENTER(rrc_main);
    29dc:	89 c3                	mov    %eax,%ebx
	FSM_BLOCK_SWITCH
    29de:	76 18                	jbe    29f8 <rrc_main+0x38>
				FSM_CASE_TRANSIT(3, ST_IDLE_NORMALLY, t311_timeout(), "ST_CONNECTED_REESTABLISH -> ST_IDLE_NORMALLY")
				FSM_CASE_DEFAULT(ST_CONNECTED_REESTABLISH, st_connect_reest_default(), "ST_CONNECTED_REESTABLISH -> ST_CONNECTED_REESTABLISH")   //transit to idle state by default.
			}
		}
	}
	FSM_EXIT(0)
    29e0:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
    29e6:	66 90                	xchg   %ax,%ax
}
    29e8:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    29eb:	8b 75 f8             	mov    -0x8(%ebp),%esi
    29ee:	8b 7d fc             	mov    -0x4(%ebp),%edi
    29f1:	89 ec                	mov    %ebp,%esp
    29f3:	5d                   	pop    %ebp
    29f4:	c3                   	ret    
    29f5:	8d 76 00             	lea    0x0(%esi),%esi


void rrc_main(void)
{
	FSM_ENTER(rrc_main);
	FSM_BLOCK_SWITCH
    29f8:	8b 00                	mov    (%eax),%eax
    29fa:	ff 24 85 b4 01 00 00 	jmp    *0x1b4(,%eax,4)
    2a01:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
	{
		FSM_STATE_FORCED(ST_INIT, "ST_INIT", st_init_enter(), st_init_exit())
    2a08:	c7 05 5c 00 00 00 28 	movl   $0x128,0x5c
    2a0f:	01 00 00 
 ******************************************************************************/

static void st_init_enter(void)
{
	FIN(st_init_enter());
	if(RRC_OPEN)
    2a12:	e8 fc ff ff ff       	call   2a13 <rrc_main+0x53>
    2a17:	83 f8 05             	cmp    $0x5,%eax
    2a1a:	0f 84 c5 0a 00 00    	je     34e5 <rrc_main+0xb25>
void rrc_main(void)
{
	FSM_ENTER(rrc_main);
	FSM_BLOCK_SWITCH
	{
		FSM_STATE_FORCED(ST_INIT, "ST_INIT", st_init_enter(), st_init_exit())
    2a20:	c7 03 01 00 00 00    	movl   $0x1,(%ebx)
    2a26:	c7 05 5c 00 00 00 28 	movl   $0x128,0x5c
    2a2d:	01 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_init_exit(void)
{
	FIN(st_init_exit());
	fsm_printf("[rrc] [fsm] st_init_exit().\n");
    2a30:	c7 04 24 66 01 00 00 	movl   $0x166,(%esp)
    2a37:	e8 fc ff ff ff       	call   2a38 <rrc_main+0x78>
	FSM_ENTER(rrc_main);
	FSM_BLOCK_SWITCH
	{
		FSM_STATE_FORCED(ST_INIT, "ST_INIT", st_init_enter(), st_init_exit())
		{
			FSM_TRANSIT_FORCE(ST_IDLE_CELL_SEL, , "default", "", "ST_INIT -> ST_IDLE_CELL_SEL");
    2a3c:	c7 03 02 00 00 00    	movl   $0x2,(%ebx)
		}
		FSM_STATE_UNFORCED(ST_IDLE_CELL_SEL, "ST_IDLE_CELL_SEL", st_cell_sel_enter(), st_cell_sel_exit())
    2a42:	c7 05 5c 00 00 00 9f 	movl   $0x19f,0x5c
    2a49:	01 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_cell_sel_enter(void)
{
	FIN(st_cell_sel_enter());
	fsm_printf("[rrc] [fsm] rrc_cell_sel_enter().\n");
    2a4c:	c7 04 24 d0 07 00 00 	movl   $0x7d0,(%esp)
    2a53:	e8 fc ff ff ff       	call   2a54 <rrc_main+0x94>


	static int flag_st_cell_sel = 0;
	if(flag_st_cell_sel == 0)
    2a58:	8b 15 dc 01 00 00    	mov    0x1dc,%edx
    2a5e:	85 d2                	test   %edx,%edx
    2a60:	0f 84 02 01 00 00    	je     2b68 <rrc_main+0x1a8>
	{
		FSM_STATE_FORCED(ST_INIT, "ST_INIT", st_init_enter(), st_init_exit())
		{
			FSM_TRANSIT_FORCE(ST_IDLE_CELL_SEL, , "default", "", "ST_INIT -> ST_IDLE_CELL_SEL");
		}
		FSM_STATE_UNFORCED(ST_IDLE_CELL_SEL, "ST_IDLE_CELL_SEL", st_cell_sel_enter(), st_cell_sel_exit())
    2a66:	c7 03 03 00 00 00    	movl   $0x3,(%ebx)
    2a6c:	e9 77 ff ff ff       	jmp    29e8 <rrc_main+0x28>
    2a71:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
			{
				FSM_CASE_TRANSIT(0, ST_IDLE_CONNECTING, transit_to_idle_connecting(), "ST_IDLE_NORMALLY -> ST_IDLE_CONNECTING")
				FSM_CASE_DEFAULT(ST_IDLE_NORMALLY, st_idle_normal_default(), "ST_IDLE_NORMALLY -> ST_IDLE_NORMALLY")   //transit to idle state by default.
			}
		}
		FSM_STATE_UNFORCED(ST_IDLE_CONNECTING, "ST_IDLE_CONNECTING", st_idle_connecting_enter(),st_idle_connecting_exit())
    2a78:	c7 05 5c 00 00 00 d6 	movl   $0x1d6,0x5c
    2a7f:	01 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_idle_connecting_exit(void)
{
	FIN(st_idle_connecting_exit());
	fsm_printf("[rrc] [fsm] st_idle_connecting_exit().\n");
    2a82:	c7 04 24 98 0a 00 00 	movl   $0xa98,(%esp)
    2a89:	e8 fc ff ff ff       	call   2a8a <rrc_main+0xca>

	if(RRC_CLOSE)
    2a8e:	e8 fc ff ff ff       	call   2a8f <rrc_main+0xcf>
    2a93:	83 f8 05             	cmp    $0x5,%eax
    2a96:	0f 84 ee 09 00 00    	je     348a <rrc_main+0xaca>
    2a9c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			}
		}
		FSM_STATE_UNFORCED(ST_IDLE_CONNECTING, "ST_IDLE_CONNECTING", st_idle_connecting_enter(),st_idle_connecting_exit())
		{
			FSM_COND_TEST_IN("ST_IDLE_CONNECTING")
			FSM_TEST_COND(Evt_TimeOut_T300)
    2aa0:	e8 fc ff ff ff       	call   2aa1 <rrc_main+0xe1>
    2aa5:	83 f8 03             	cmp    $0x3,%eax
    2aa8:	0f 84 c2 09 00 00    	je     3470 <rrc_main+0xab0>
    2aae:	bf ff ff ff ff       	mov    $0xffffffff,%edi
    2ab3:	31 f6                	xor    %esi,%esi
			FSM_TEST_COND(Evt_RcvRRCConnReject)
    2ab5:	e8 fc ff ff ff       	call   2ab6 <rrc_main+0xf6>
    2aba:	83 f8 03             	cmp    $0x3,%eax
    2abd:	0f 84 92 09 00 00    	je     3455 <rrc_main+0xa95>
			FSM_TEST_COND(Evt_RcvRRCConnSetup)
    2ac3:	e8 fc ff ff ff       	call   2ac4 <rrc_main+0x104>
    2ac8:	83 f8 03             	cmp    $0x3,%eax
    2acb:	0f 84 69 09 00 00    	je     343a <rrc_main+0xa7a>
			FSM_COND_TEST_OUT("ST_IDLE_CONNECTING")
    2ad1:	83 fe 01             	cmp    $0x1,%esi
    2ad4:	0f 8f f6 01 00 00    	jg     2cd0 <rrc_main+0x310>
    2ada:	85 f6                	test   %esi,%esi
    2adc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    2ae0:	0f 84 06 02 00 00    	je     2cec <rrc_main+0x32c>
			FSM_TRANSIT_SWITCH
    2ae6:	83 ff 01             	cmp    $0x1,%edi
    2ae9:	0f 84 0b 07 00 00    	je     31fa <rrc_main+0x83a>
    2aef:	83 ff 02             	cmp    $0x2,%edi
    2af2:	0f 84 e8 06 00 00    	je     31e0 <rrc_main+0x820>
    2af8:	85 ff                	test   %edi,%edi
    2afa:	0f 85 ec 01 00 00    	jne    2cec <rrc_main+0x32c>
			{
				FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, t300_timeout(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
    2b00:	c7 05 5c 00 00 00 c0 	movl   $0xac0,0x5c
    2b07:	0a 00 00 
	struct SrbToAddModList srbToAddModList_setup;
	struct DrbToAddModList drbToAddModList_setup;
	int srbIndex;
	int drbIndex;

	fsm_printf("[rrc] [fsm] t300_timeout().\n");
    2b0a:	c7 04 24 0e 02 00 00 	movl   $0x20e,(%esp)
    2b11:	e8 fc ff ff ff       	call   2b12 <rrc_main+0x152>

	fsm_do_ioctrl(STRM_TO_MAC,  IOCCMD_RRCTOMAC_RESET  , NULL, 0);
    2b16:	31 c9                	xor    %ecx,%ecx
    2b18:	ba 03 00 00 00       	mov    $0x3,%edx
    2b1d:	b8 02 00 00 00       	mov    $0x2,%eax
    2b22:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
    2b29:	e8 fc ff ff ff       	call   2b2a <rrc_main+0x16a>
	}

	fsm_mem_free(DL_ccch_rrcsetupmsg);
	DL_ccch_rrcsetupmsg = NULL;
	*/
	cancleTimer(TIMER_T300);
    2b2e:	b8 2c 01 00 00       	mov    $0x12c,%eax
    2b33:	e8 fc ff ff ff       	call   2b34 <rrc_main+0x174>
			FSM_TEST_COND(Evt_RcvRRCConnReject)
			FSM_TEST_COND(Evt_RcvRRCConnSetup)
			FSM_COND_TEST_OUT("ST_IDLE_CONNECTING")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, t300_timeout(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
    2b38:	c7 03 06 00 00 00    	movl   $0x6,(%ebx)
    2b3e:	66 90                	xchg   %ax,%ax
				{
					FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, transit_to_idle(), "ST_IDLE_WAIT_SYSINFO -> ST_IDLE_NORMALLY")
					FSM_CASE_DEFAULT(ST_IDLE_WAIT_SYSINFO, st_wait_sysInfo_default(), "ST_IDLE_WAIT_SYSINFO -> ST_IDLE_WAIT_SYSINFO")   //transit to idle state by default.
				}
		}
		FSM_STATE_UNFORCED(ST_IDLE_NORMALLY, "ST_IDLE_NORMALLY", st_idle_normal_enter(),st_idle_normal_exit())
    2b40:	c7 05 5c 00 00 00 c5 	movl   $0x1c5,0x5c
    2b47:	01 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_idle_normal_enter(void)
{
	FIN(st_idle_normal_enter());
	fsm_printf("[rrc] [fsm] st_idle_normal_enter().\n");
    2b4a:	c7 04 24 a8 09 00 00 	movl   $0x9a8,(%esp)
    2b51:	e8 fc ff ff ff       	call   2b52 <rrc_main+0x192>
				{
					FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, transit_to_idle(), "ST_IDLE_WAIT_SYSINFO -> ST_IDLE_NORMALLY")
					FSM_CASE_DEFAULT(ST_IDLE_WAIT_SYSINFO, st_wait_sysInfo_default(), "ST_IDLE_WAIT_SYSINFO -> ST_IDLE_WAIT_SYSINFO")   //transit to idle state by default.
				}
		}
		FSM_STATE_UNFORCED(ST_IDLE_NORMALLY, "ST_IDLE_NORMALLY", st_idle_normal_enter(),st_idle_normal_exit())
    2b56:	c7 03 07 00 00 00    	movl   $0x7,(%ebx)
    2b5c:	e9 87 fe ff ff       	jmp    29e8 <rrc_main+0x28>
    2b61:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi


	static int flag_st_cell_sel = 0;
	if(flag_st_cell_sel == 0)
	{
		fsm_schedule_self(0, CODE_BEGIN_RECV_SYSINFO); //test
    2b68:	31 d2                	xor    %edx,%edx
    2b6a:	31 c0                	xor    %eax,%eax
    2b6c:	e8 fc ff ff ff       	call   2b6d <rrc_main+0x1ad>
		flag_st_cell_sel++;
    2b71:	83 05 dc 01 00 00 01 	addl   $0x1,0x1dc
    2b78:	e9 e9 fe ff ff       	jmp    2a66 <rrc_main+0xa6>
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_NORMALLY, "ST_CONNECTED_NORMALLY", st_connect_normal_enter(),st_connect_normal_exit())
		{
			FSM_COND_TEST_IN("ST_CONNECTED_NORMALLY")
			FSM_TEST_COND(Evt_RcvRRCConnReconfig)
			FSM_TEST_COND(Evt_RcvRRCConnRelease)
    2b7d:	e8 fc ff ff ff       	call   2b7e <rrc_main+0x1be>
    2b82:	83 f8 07             	cmp    $0x7,%eax
    2b85:	0f 85 28 04 00 00    	jne    2fb3 <rrc_main+0x5f3>
			FSM_COND_TEST_OUT("ST_CONNECTED_NORMALLY")
    2b8b:	83 fe 01             	cmp    $0x1,%esi
    2b8e:	66 90                	xchg   %ax,%ax
    2b90:	0f 85 c3 07 00 00    	jne    3359 <rrc_main+0x999>
    2b96:	c7 44 24 08 e9 01 00 	movl   $0x1e9,0x8(%esp)
    2b9d:	00 
    2b9e:	c7 44 24 04 2b 02 00 	movl   $0x22b,0x4(%esp)
    2ba5:	00 
    2ba6:	c7 04 24 fd 01 00 00 	movl   $0x1fd,(%esp)
    2bad:	e8 fc ff ff ff       	call   2bae <rrc_main+0x1ee>
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_CONNECTED_RECONF, rcv_rrc_conn_reconf(), "ST_CONNECTED_NORMALLY -> ST_CONNECTED_RECONF")
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_release(), "ST_CONNECTED_NORMALLY -> ST_IDLE_NORMALLY")
				FSM_CASE_DEFAULT(ST_CONNECTED_NORMALLY, st_connect_normal_default(), "ST_CONNECTED_NORMALLY -> ST_CONNECTED_NORMALLY")   //transit to idle state by default.
    2bb2:	c7 05 5c 00 00 00 ec 	movl   $0xcec,0x5c
    2bb9:	0c 00 00 
 ******************************************************************************/

static void st_connect_normal_default(void)
{
	FIN(st_connect_normal_default());
	fsm_printf("[rrc] [fsm] st_connect_normal_default().\n");
    2bbc:	c7 04 24 1c 0d 00 00 	movl   $0xd1c,(%esp)
    2bc3:	e8 fc ff ff ff       	call   2bc4 <rrc_main+0x204>

	if(EVT_IOCTL_ARRIVAL)
    2bc8:	e8 fc ff ff ff       	call   2bc9 <rrc_main+0x209>
    2bcd:	83 f8 05             	cmp    $0x5,%eax
    2bd0:	0f 84 ea 09 00 00    	je     35c0 <rrc_main+0xc00>
	{
		rrc_ioctl_handler();
	}
	else if(EVT_RRC_PK_FROM_LOWER)
    2bd6:	e8 fc ff ff ff       	call   2bd7 <rrc_main+0x217>
    2bdb:	83 f8 02             	cmp    $0x2,%eax
    2bde:	66 90                	xchg   %ax,%ax
    2be0:	0f 84 74 0a 00 00    	je     365a <rrc_main+0xc9a>
	{
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_rlc(pkptr);
	}
	else if(EVT_RRC_PK_FROM_UPPER)
    2be6:	e8 fc ff ff ff       	call   2be7 <rrc_main+0x227>
    2beb:	83 f8 01             	cmp    $0x1,%eax
    2bee:	66 90                	xchg   %ax,%ax
    2bf0:	0f 84 7f 0a 00 00    	je     3675 <rrc_main+0xcb5>
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_upper(pkptr);
	}
	else
	{
		other_events_handler();
    2bf6:	e8 35 f8 ff ff       	call   2430 <other_events_handler>
			FSM_TEST_COND(Evt_ReconfigSuccess)
			FSM_TEST_COND(Evt_ReconfigFail)
			FSM_COND_TEST_OUT("ST_CONNECTED_RECONF")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_CONNECTED_NORMALLY, reconfig_success(), "ST_CONNECTED_RECONF -> ST_CONNECTED_NORMALLY")
    2bfb:	c7 03 0a 00 00 00    	movl   $0xa,(%ebx)
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_reject(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(2, ST_CONNECTED_NORMALLY, rcv_rrc_conn_setup(), "ST_IDLE_CONNECTING -> ST_CONNECTED_NORMALLY")
				FSM_CASE_DEFAULT(ST_IDLE_CONNECTING, st_idle_connecting_default(), "ST_IDLE_CONNECTING -> ST_IDLE_CONNECTING")   //transit to idle state by default.
			}
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_NORMALLY, "ST_CONNECTED_NORMALLY", st_connect_normal_enter(),st_connect_normal_exit())
    2c01:	c7 05 5c 00 00 00 2b 	movl   $0x22b,0x5c
    2c08:	02 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_connect_normal_enter(void)
{
	FIN(st_connect_normal_enter());
	fsm_printf("[rrc] [fsm] st_connect_normal_enter().\n");
    2c0b:	c7 04 24 90 0b 00 00 	movl   $0xb90,(%esp)
    2c12:	e8 fc ff ff ff       	call   2c13 <rrc_main+0x253>
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_reject(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(2, ST_CONNECTED_NORMALLY, rcv_rrc_conn_setup(), "ST_IDLE_CONNECTING -> ST_CONNECTED_NORMALLY")
				FSM_CASE_DEFAULT(ST_IDLE_CONNECTING, st_idle_connecting_default(), "ST_IDLE_CONNECTING -> ST_IDLE_CONNECTING")   //transit to idle state by default.
			}
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_NORMALLY, "ST_CONNECTED_NORMALLY", st_connect_normal_enter(),st_connect_normal_exit())
    2c17:	c7 03 0b 00 00 00    	movl   $0xb,(%ebx)
    2c1d:	e9 c6 fd ff ff       	jmp    29e8 <rrc_main+0x28>
    2c22:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
				{
					FSM_CASE_TRANSIT(0, ST_IDLE_WAIT_SYSINFO, start_recv_sysInfo(), "ST_IDLE_CELL_SEL -> ST_IDLE_WAIT_SYSINFO")
					FSM_CASE_DEFAULT(ST_IDLE_CELL_SEL, st_cell_sel_default(), "ST_IDLE_CELL_SEL -> ST_IDLE_CELL_SEL")
				}
		}
		FSM_STATE_UNFORCED(ST_IDLE_WAIT_SYSINFO, "ST_IDLE_WAIT_SYSINFO", st_wait_sysInfo_enter(),st_wait_sysInfo_exit())
    2c28:	c7 05 5c 00 00 00 b0 	movl   $0x1b0,0x5c
    2c2f:	01 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_wait_sysInfo_exit(void)
{
	FIN(st_wait_sysInfo_exit());
	fsm_printf("[rrc] [fsm] st_wait_sysInfo_exit().\n");
    2c32:	c7 04 24 dc 08 00 00 	movl   $0x8dc,(%esp)
    2c39:	e8 fc ff ff ff       	call   2c3a <rrc_main+0x27a>

	if(RRC_CLOSE)
    2c3e:	e8 fc ff ff ff       	call   2c3f <rrc_main+0x27f>
    2c43:	83 f8 05             	cmp    $0x5,%eax
    2c46:	0f 84 00 06 00 00    	je     324c <rrc_main+0x88c>
    2c4c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
				}
		}
		FSM_STATE_UNFORCED(ST_IDLE_WAIT_SYSINFO, "ST_IDLE_WAIT_SYSINFO", st_wait_sysInfo_enter(),st_wait_sysInfo_exit())
		{
			FSM_COND_TEST_IN("ST_IDLE_WAIT_SYSINFO")
				FSM_TEST_COND(EVT_END_RECV_SYSINFO)
    2c50:	e8 fc ff ff ff       	call   2c51 <rrc_main+0x291>
    2c55:	83 f8 03             	cmp    $0x3,%eax
    2c58:	0f 84 b4 06 00 00    	je     3312 <rrc_main+0x952>
				FSM_COND_TEST_OUT("ST_IDLE_WAIT_SYSINFO")
				FSM_TRANSIT_SWITCH
				{
					FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, transit_to_idle(), "ST_IDLE_WAIT_SYSINFO -> ST_IDLE_NORMALLY")
					FSM_CASE_DEFAULT(ST_IDLE_WAIT_SYSINFO, st_wait_sysInfo_default(), "ST_IDLE_WAIT_SYSINFO -> ST_IDLE_WAIT_SYSINFO")   //transit to idle state by default.
    2c5e:	c7 05 5c 00 00 00 04 	movl   $0x904,0x5c
    2c65:	09 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_wait_sysInfo_default(void)
{
	FIN(st_wait_sysInfo_default());
	fsm_printf("[rrc] [fsm] st_wait_sysInfo_default().\n");
    2c68:	c7 04 24 34 09 00 00 	movl   $0x934,(%esp)
    2c6f:	e8 fc ff ff ff       	call   2c70 <rrc_main+0x2b0>

	if(EVT_IOCTL_ARRIVAL)
    2c74:	e8 fc ff ff ff       	call   2c75 <rrc_main+0x2b5>
    2c79:	83 f8 05             	cmp    $0x5,%eax
    2c7c:	0f 84 f3 04 00 00    	je     3175 <rrc_main+0x7b5>
	{
		rrc_ioctl_handler();
	}
	else if(EVT_RRC_PK_FROM_LOWER)
    2c82:	e8 fc ff ff ff       	call   2c83 <rrc_main+0x2c3>
    2c87:	83 f8 02             	cmp    $0x2,%eax
    2c8a:	0f 84 df 08 00 00    	je     356f <rrc_main+0xbaf>
	{
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_rlc(pkptr);
	}
	else if(EVT_RRC_PK_FROM_UPPER)
    2c90:	e8 fc ff ff ff       	call   2c91 <rrc_main+0x2d1>
    2c95:	83 f8 01             	cmp    $0x1,%eax
    2c98:	0f 84 3c 09 00 00    	je     35da <rrc_main+0xc1a>
    2c9e:	66 90                	xchg   %ax,%ax
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_upper(pkptr);
	}
	else
	{
		other_events_handler();
    2ca0:	e8 8b f7 ff ff       	call   2430 <other_events_handler>
				FSM_TEST_COND(EVT_END_RECV_SYSINFO)
				FSM_COND_TEST_OUT("ST_IDLE_WAIT_SYSINFO")
				FSM_TRANSIT_SWITCH
				{
					FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, transit_to_idle(), "ST_IDLE_WAIT_SYSINFO -> ST_IDLE_NORMALLY")
					FSM_CASE_DEFAULT(ST_IDLE_WAIT_SYSINFO, st_wait_sysInfo_default(), "ST_IDLE_WAIT_SYSINFO -> ST_IDLE_WAIT_SYSINFO")   //transit to idle state by default.
    2ca5:	c7 03 04 00 00 00    	movl   $0x4,(%ebx)
				{
					FSM_CASE_TRANSIT(0, ST_IDLE_WAIT_SYSINFO, start_recv_sysInfo(), "ST_IDLE_CELL_SEL -> ST_IDLE_WAIT_SYSINFO")
					FSM_CASE_DEFAULT(ST_IDLE_CELL_SEL, st_cell_sel_default(), "ST_IDLE_CELL_SEL -> ST_IDLE_CELL_SEL")
				}
		}
		FSM_STATE_UNFORCED(ST_IDLE_WAIT_SYSINFO, "ST_IDLE_WAIT_SYSINFO", st_wait_sysInfo_enter(),st_wait_sysInfo_exit())
    2cab:	c7 05 5c 00 00 00 b0 	movl   $0x1b0,0x5c
    2cb2:	01 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_wait_sysInfo_enter(void)
{
	FIN(st_wait_sysInfo_enter());
	fsm_printf("[rrc] [fsm] st_wait_sysInfo_enter().\n");
    2cb5:	c7 04 24 b4 08 00 00 	movl   $0x8b4,(%esp)
    2cbc:	e8 fc ff ff ff       	call   2cbd <rrc_main+0x2fd>
				{
					FSM_CASE_TRANSIT(0, ST_IDLE_WAIT_SYSINFO, start_recv_sysInfo(), "ST_IDLE_CELL_SEL -> ST_IDLE_WAIT_SYSINFO")
					FSM_CASE_DEFAULT(ST_IDLE_CELL_SEL, st_cell_sel_default(), "ST_IDLE_CELL_SEL -> ST_IDLE_CELL_SEL")
				}
		}
		FSM_STATE_UNFORCED(ST_IDLE_WAIT_SYSINFO, "ST_IDLE_WAIT_SYSINFO", st_wait_sysInfo_enter(),st_wait_sysInfo_exit())
    2cc1:	c7 03 05 00 00 00    	movl   $0x5,(%ebx)
    2cc7:	e9 1c fd ff ff       	jmp    29e8 <rrc_main+0x28>
    2ccc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
		{
			FSM_COND_TEST_IN("ST_IDLE_CONNECTING")
			FSM_TEST_COND(Evt_TimeOut_T300)
			FSM_TEST_COND(Evt_RcvRRCConnReject)
			FSM_TEST_COND(Evt_RcvRRCConnSetup)
			FSM_COND_TEST_OUT("ST_IDLE_CONNECTING")
    2cd0:	c7 44 24 08 e9 01 00 	movl   $0x1e9,0x8(%esp)
    2cd7:	00 
    2cd8:	c7 44 24 04 d6 01 00 	movl   $0x1d6,0x4(%esp)
    2cdf:	00 
    2ce0:	c7 04 24 fd 01 00 00 	movl   $0x1fd,(%esp)
    2ce7:	e8 fc ff ff ff       	call   2ce8 <rrc_main+0x328>
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, t300_timeout(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_reject(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(2, ST_CONNECTED_NORMALLY, rcv_rrc_conn_setup(), "ST_IDLE_CONNECTING -> ST_CONNECTED_NORMALLY")
				FSM_CASE_DEFAULT(ST_IDLE_CONNECTING, st_idle_connecting_default(), "ST_IDLE_CONNECTING -> ST_IDLE_CONNECTING")   //transit to idle state by default.
    2cec:	c7 05 5c 00 00 00 38 	movl   $0xb38,0x5c
    2cf3:	0b 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_idle_connecting_default(void)
{
	FIN(st_idle_connecting_default());
	fsm_printf("[rrc] [fsm] st_idle_connecting_default().\n");
    2cf6:	c7 04 24 64 0b 00 00 	movl   $0xb64,(%esp)
    2cfd:	e8 fc ff ff ff       	call   2cfe <rrc_main+0x33e>

	if(EVT_IOCTL_ARRIVAL)
    2d02:	e8 fc ff ff ff       	call   2d03 <rrc_main+0x343>
    2d07:	83 f8 05             	cmp    $0x5,%eax
    2d0a:	0f 84 15 09 00 00    	je     3625 <rrc_main+0xc65>
	{
		rrc_ioctl_handler();
	}
	else if(EVT_RRC_PK_FROM_LOWER)
    2d10:	e8 fc ff ff ff       	call   2d11 <rrc_main+0x351>
    2d15:	83 f8 02             	cmp    $0x2,%eax
    2d18:	0f 84 98 09 00 00    	je     36b6 <rrc_main+0xcf6>
    2d1e:	66 90                	xchg   %ax,%ax
	{
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_rlc(pkptr);
	}
	else if(EVT_RRC_PK_FROM_UPPER)
    2d20:	e8 fc ff ff ff       	call   2d21 <rrc_main+0x361>
    2d25:	83 f8 01             	cmp    $0x1,%eax
    2d28:	0f 84 9c 09 00 00    	je     36ca <rrc_main+0xd0a>
    2d2e:	66 90                	xchg   %ax,%ax
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_upper(pkptr);
	}
	else
	{
		other_events_handler();
    2d30:	e8 fb f6 ff ff       	call   2430 <other_events_handler>
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, t300_timeout(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_reject(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(2, ST_CONNECTED_NORMALLY, rcv_rrc_conn_setup(), "ST_IDLE_CONNECTING -> ST_CONNECTED_NORMALLY")
				FSM_CASE_DEFAULT(ST_IDLE_CONNECTING, st_idle_connecting_default(), "ST_IDLE_CONNECTING -> ST_IDLE_CONNECTING")   //transit to idle state by default.
    2d35:	c7 03 08 00 00 00    	movl   $0x8,(%ebx)
    2d3b:	90                   	nop
    2d3c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			{
				FSM_CASE_TRANSIT(0, ST_IDLE_CONNECTING, transit_to_idle_connecting(), "ST_IDLE_NORMALLY -> ST_IDLE_CONNECTING")
				FSM_CASE_DEFAULT(ST_IDLE_NORMALLY, st_idle_normal_default(), "ST_IDLE_NORMALLY -> ST_IDLE_NORMALLY")   //transit to idle state by default.
			}
		}
		FSM_STATE_UNFORCED(ST_IDLE_CONNECTING, "ST_IDLE_CONNECTING", st_idle_connecting_enter(),st_idle_connecting_exit())
    2d40:	c7 05 5c 00 00 00 d6 	movl   $0x1d6,0x5c
    2d47:	01 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_idle_connecting_enter(void)
{
	FIN(st_idle_connecting_enter());
	fsm_printf("[rrc] [fsm] st_idle_connecting_enter().\n");
    2d4a:	c7 04 24 6c 0a 00 00 	movl   $0xa6c,(%esp)
    2d51:	e8 fc ff ff ff       	call   2d52 <rrc_main+0x392>
			{
				FSM_CASE_TRANSIT(0, ST_IDLE_CONNECTING, transit_to_idle_connecting(), "ST_IDLE_NORMALLY -> ST_IDLE_CONNECTING")
				FSM_CASE_DEFAULT(ST_IDLE_NORMALLY, st_idle_normal_default(), "ST_IDLE_NORMALLY -> ST_IDLE_NORMALLY")   //transit to idle state by default.
			}
		}
		FSM_STATE_UNFORCED(ST_IDLE_CONNECTING, "ST_IDLE_CONNECTING", st_idle_connecting_enter(),st_idle_connecting_exit())
    2d56:	c7 03 09 00 00 00    	movl   $0x9,(%ebx)
    2d5c:	e9 87 fc ff ff       	jmp    29e8 <rrc_main+0x28>
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_RECONF, "ST_CONNECTED_RECONF", st_connect_reconf_enter(),st_connect_reconf_exit())
		{
			FSM_COND_TEST_IN("ST_CONNECTED_RECONF")
			FSM_TEST_COND(Evt_ReconfigSuccess)
			FSM_TEST_COND(Evt_ReconfigFail)
    2d61:	e8 fc ff ff ff       	call   2d62 <rrc_main+0x3a2>
    2d66:	83 f8 09             	cmp    $0x9,%eax
    2d69:	0f 85 94 01 00 00    	jne    2f03 <rrc_main+0x543>
			FSM_COND_TEST_OUT("ST_CONNECTED_RECONF")
    2d6f:	83 fe 01             	cmp    $0x1,%esi
    2d72:	0f 85 23 01 00 00    	jne    2e9b <rrc_main+0x4db>
    2d78:	c7 44 24 08 e9 01 00 	movl   $0x1e9,0x8(%esp)
    2d7f:	00 
    2d80:	c7 44 24 04 41 02 00 	movl   $0x241,0x4(%esp)
    2d87:	00 
    2d88:	c7 04 24 fd 01 00 00 	movl   $0x1fd,(%esp)
    2d8f:	e8 fc ff ff ff       	call   2d90 <rrc_main+0x3d0>
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_CONNECTED_NORMALLY, reconfig_success(), "ST_CONNECTED_RECONF -> ST_CONNECTED_NORMALLY")
				FSM_CASE_TRANSIT(1, ST_CONNECTED_REESTABLISH, reconfig_fail(), "ST_CONNECTED_RECONF -> ST_CONNECTED_REESTABLISH")
				FSM_CASE_DEFAULT(ST_CONNECTED_RECONF, st_connect_reconf_default(), "ST_CONNECTED_RECONF -> ST_CONNECTED_RECONF")   //transit to idle state by default.
    2d94:	c7 05 5c 00 00 00 3c 	movl   $0xe3c,0x5c
    2d9b:	0e 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_connect_reconf_default(void)
{
	FIN(st_connect_reconf_default());
	fsm_printf("[rrc] [fsm] st_connect_reconf_default().\n");
    2d9e:	c7 04 24 68 0e 00 00 	movl   $0xe68,(%esp)
    2da5:	e8 fc ff ff ff       	call   2da6 <rrc_main+0x3e6>

	if(EVT_IOCTL_ARRIVAL)
    2daa:	e8 fc ff ff ff       	call   2dab <rrc_main+0x3eb>
    2daf:	83 f8 05             	cmp    $0x5,%eax
    2db2:	0f 84 e2 07 00 00    	je     359a <rrc_main+0xbda>
	{
		rrc_ioctl_handler();
	}
	else if(EVT_RRC_PK_FROM_LOWER)
    2db8:	e8 fc ff ff ff       	call   2db9 <rrc_main+0x3f9>
    2dbd:	83 f8 02             	cmp    $0x2,%eax
    2dc0:	0f 84 7f 08 00 00    	je     3645 <rrc_main+0xc85>
	{
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_rlc(pkptr);
	}
	else if(EVT_RRC_PK_FROM_UPPER)
    2dc6:	e8 fc ff ff ff       	call   2dc7 <rrc_main+0x407>
    2dcb:	83 f8 01             	cmp    $0x1,%eax
    2dce:	66 90                	xchg   %ax,%ax
    2dd0:	0f 84 b4 08 00 00    	je     368a <rrc_main+0xcca>
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_upper(pkptr);
	}
	else
	{
		other_events_handler();
    2dd6:	e8 55 f6 ff ff       	call   2430 <other_events_handler>
			FSM_COND_TEST_OUT("ST_CONNECTED_RECONF")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_CONNECTED_NORMALLY, reconfig_success(), "ST_CONNECTED_RECONF -> ST_CONNECTED_NORMALLY")
				FSM_CASE_TRANSIT(1, ST_CONNECTED_REESTABLISH, reconfig_fail(), "ST_CONNECTED_RECONF -> ST_CONNECTED_REESTABLISH")
				FSM_CASE_DEFAULT(ST_CONNECTED_RECONF, st_connect_reconf_default(), "ST_CONNECTED_RECONF -> ST_CONNECTED_RECONF")   //transit to idle state by default.
    2ddb:	c7 03 0c 00 00 00    	movl   $0xc,(%ebx)
				FSM_CASE_TRANSIT(0, ST_CONNECTED_RECONF, rcv_rrc_conn_reconf(), "ST_CONNECTED_NORMALLY -> ST_CONNECTED_RECONF")
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_release(), "ST_CONNECTED_NORMALLY -> ST_IDLE_NORMALLY")
				FSM_CASE_DEFAULT(ST_CONNECTED_NORMALLY, st_connect_normal_default(), "ST_CONNECTED_NORMALLY -> ST_CONNECTED_NORMALLY")   //transit to idle state by default.
			}
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_RECONF, "ST_CONNECTED_RECONF", st_connect_reconf_enter(),st_connect_reconf_exit())
    2de1:	c7 05 5c 00 00 00 41 	movl   $0x241,0x5c
    2de8:	02 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_connect_reconf_enter(void)
{
	FIN(st_connect_reconf_enter());
	fsm_printf("[rrc] [fsm] st_connect_reconf_enter().\n");
    2deb:	c7 04 24 48 0d 00 00 	movl   $0xd48,(%esp)
    2df2:	e8 fc ff ff ff       	call   2df3 <rrc_main+0x433>


	static int flag_st_connect_reconf = 0;
	if(flag_st_connect_reconf == 0)
    2df7:	a1 e0 01 00 00       	mov    0x1e0,%eax
    2dfc:	85 c0                	test   %eax,%eax
    2dfe:	75 16                	jne    2e16 <rrc_main+0x456>
	{
		fsm_schedule_self(100, CODE_RECONF_SUCCESS); //test reconfig success
    2e00:	ba 08 00 00 00       	mov    $0x8,%edx
    2e05:	b8 64 00 00 00       	mov    $0x64,%eax
    2e0a:	e8 fc ff ff ff       	call   2e0b <rrc_main+0x44b>
		flag_st_connect_reconf++;
    2e0f:	83 05 e0 01 00 00 01 	addl   $0x1,0x1e0
				FSM_CASE_TRANSIT(0, ST_CONNECTED_RECONF, rcv_rrc_conn_reconf(), "ST_CONNECTED_NORMALLY -> ST_CONNECTED_RECONF")
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_release(), "ST_CONNECTED_NORMALLY -> ST_IDLE_NORMALLY")
				FSM_CASE_DEFAULT(ST_CONNECTED_NORMALLY, st_connect_normal_default(), "ST_CONNECTED_NORMALLY -> ST_CONNECTED_NORMALLY")   //transit to idle state by default.
			}
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_RECONF, "ST_CONNECTED_RECONF", st_connect_reconf_enter(),st_connect_reconf_exit())
    2e16:	c7 03 0d 00 00 00    	movl   $0xd,(%ebx)
    2e1c:	e9 c7 fb ff ff       	jmp    29e8 <rrc_main+0x28>
    2e21:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
				FSM_CASE_TRANSIT(0, ST_CONNECTED_NORMALLY, reconfig_success(), "ST_CONNECTED_RECONF -> ST_CONNECTED_NORMALLY")
				FSM_CASE_TRANSIT(1, ST_CONNECTED_REESTABLISH, reconfig_fail(), "ST_CONNECTED_RECONF -> ST_CONNECTED_REESTABLISH")
				FSM_CASE_DEFAULT(ST_CONNECTED_RECONF, st_connect_reconf_default(), "ST_CONNECTED_RECONF -> ST_CONNECTED_RECONF")   //transit to idle state by default.
			}
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_REESTABLISH, "ST_CONNECTED_REESTABLISH", st_connect_reest_enter(),st_connect_reest_exit())
    2e28:	c7 05 5c 00 00 00 55 	movl   $0x255,0x5c
    2e2f:	02 00 00 
		{
			FSM_COND_TEST_IN("ST_CONNECTED_REESTABLISH")
			FSM_TEST_COND(Evt_RcvRRCConnReestablish)
    2e32:	e8 fc ff ff ff       	call   2e33 <rrc_main+0x473>
    2e37:	83 f8 03             	cmp    $0x3,%eax
    2e3a:	0f 84 db 05 00 00    	je     341b <rrc_main+0xa5b>
    2e40:	bf ff ff ff ff       	mov    $0xffffffff,%edi
    2e45:	31 f6                	xor    %esi,%esi
			FSM_TEST_COND(Evt_RcvRRCConnReestablishReject)
    2e47:	e8 fc ff ff ff       	call   2e48 <rrc_main+0x488>
    2e4c:	83 f8 03             	cmp    $0x3,%eax
    2e4f:	0f 84 a5 05 00 00    	je     33fa <rrc_main+0xa3a>
			FSM_TEST_COND(Evt_TimeOut_T301)
    2e55:	e8 fc ff ff ff       	call   2e56 <rrc_main+0x496>
    2e5a:	83 f8 03             	cmp    $0x3,%eax
    2e5d:	8d 76 00             	lea    0x0(%esi),%esi
    2e60:	0f 84 df 06 00 00    	je     3545 <rrc_main+0xb85>
			FSM_TEST_COND(Evt_TimeOut_T311)
    2e66:	e8 fc ff ff ff       	call   2e67 <rrc_main+0x4a7>
    2e6b:	83 f8 03             	cmp    $0x3,%eax
    2e6e:	66 90                	xchg   %ax,%ax
    2e70:	0f 84 b0 06 00 00    	je     3526 <rrc_main+0xb66>
			FSM_COND_TEST_OUT("ST_CONNECTED_REESTABLISH")
    2e76:	83 fe 01             	cmp    $0x1,%esi
    2e79:	0f 8e b1 02 00 00    	jle    3130 <rrc_main+0x770>
    2e7f:	c7 44 24 08 e9 01 00 	movl   $0x1e9,0x8(%esp)
    2e86:	00 
    2e87:	c7 44 24 04 55 02 00 	movl   $0x255,0x4(%esp)
    2e8e:	00 
    2e8f:	c7 04 24 fd 01 00 00 	movl   $0x1fd,(%esp)
    2e96:	e8 fc ff ff ff       	call   2e97 <rrc_main+0x4d7>
			{
				FSM_CASE_TRANSIT(0, ST_CONNECTED_NORMALLY, rcv_rrc_conn_reestablishment(), "ST_CONNECTED_REESTABLISH -> ST_CONNECTED_NORMALLY")
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_reestablish_reject(), "ST_CONNECTED_REESTABLISH -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(2, ST_IDLE_NORMALLY, t301_timeout(), "ST_CONNECTED_REESTABLISH -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(3, ST_IDLE_NORMALLY, t311_timeout(), "ST_CONNECTED_REESTABLISH -> ST_IDLE_NORMALLY")
				FSM_CASE_DEFAULT(ST_CONNECTED_REESTABLISH, st_connect_reest_default(), "ST_CONNECTED_REESTABLISH -> ST_CONNECTED_REESTABLISH")   //transit to idle state by default.
    2e9b:	c7 03 0e 00 00 00    	movl   $0xe,(%ebx)
				FSM_CASE_TRANSIT(0, ST_CONNECTED_NORMALLY, reconfig_success(), "ST_CONNECTED_RECONF -> ST_CONNECTED_NORMALLY")
				FSM_CASE_TRANSIT(1, ST_CONNECTED_REESTABLISH, reconfig_fail(), "ST_CONNECTED_RECONF -> ST_CONNECTED_REESTABLISH")
				FSM_CASE_DEFAULT(ST_CONNECTED_RECONF, st_connect_reconf_default(), "ST_CONNECTED_RECONF -> ST_CONNECTED_RECONF")   //transit to idle state by default.
			}
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_REESTABLISH, "ST_CONNECTED_REESTABLISH", st_connect_reest_enter(),st_connect_reest_exit())
    2ea1:	c7 05 5c 00 00 00 55 	movl   $0x255,0x5c
    2ea8:	02 00 00 
    2eab:	c7 03 0f 00 00 00    	movl   $0xf,(%ebx)
    2eb1:	e9 32 fb ff ff       	jmp    29e8 <rrc_main+0x28>
    2eb6:	66 90                	xchg   %ax,%ax
				FSM_CASE_TRANSIT(0, ST_CONNECTED_RECONF, rcv_rrc_conn_reconf(), "ST_CONNECTED_NORMALLY -> ST_CONNECTED_RECONF")
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_release(), "ST_CONNECTED_NORMALLY -> ST_IDLE_NORMALLY")
				FSM_CASE_DEFAULT(ST_CONNECTED_NORMALLY, st_connect_normal_default(), "ST_CONNECTED_NORMALLY -> ST_CONNECTED_NORMALLY")   //transit to idle state by default.
			}
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_RECONF, "ST_CONNECTED_RECONF", st_connect_reconf_enter(),st_connect_reconf_exit())
    2eb8:	c7 05 5c 00 00 00 41 	movl   $0x241,0x5c
    2ebf:	02 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_connect_reconf_exit(void)
{
	FIN(st_connect_reconf_exit());
	fsm_printf("[rrc] [fsm] st_connect_reconf_exit().\n");
    2ec2:	c7 04 24 70 0d 00 00 	movl   $0xd70,(%esp)
    2ec9:	e8 fc ff ff ff       	call   2eca <rrc_main+0x50a>

	if(RRC_CLOSE)
    2ece:	e8 fc ff ff ff       	call   2ecf <rrc_main+0x50f>
    2ed3:	83 f8 05             	cmp    $0x5,%eax
    2ed6:	0f 84 e6 05 00 00    	je     34c2 <rrc_main+0xb02>
    2edc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			}
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_RECONF, "ST_CONNECTED_RECONF", st_connect_reconf_enter(),st_connect_reconf_exit())
		{
			FSM_COND_TEST_IN("ST_CONNECTED_RECONF")
			FSM_TEST_COND(Evt_ReconfigSuccess)
    2ee0:	e8 fc ff ff ff       	call   2ee1 <rrc_main+0x521>
    2ee5:	83 f8 03             	cmp    $0x3,%eax
    2ee8:	0f 84 b7 05 00 00    	je     34a5 <rrc_main+0xae5>
    2eee:	bf ff ff ff ff       	mov    $0xffffffff,%edi
    2ef3:	31 f6                	xor    %esi,%esi
			FSM_TEST_COND(Evt_ReconfigFail)
    2ef5:	e8 fc ff ff ff       	call   2ef6 <rrc_main+0x536>
    2efa:	83 f8 03             	cmp    $0x3,%eax
    2efd:	0f 84 5e fe ff ff    	je     2d61 <rrc_main+0x3a1>
			FSM_COND_TEST_OUT("ST_CONNECTED_RECONF")
    2f03:	85 f6                	test   %esi,%esi
    2f05:	0f 84 89 fe ff ff    	je     2d94 <rrc_main+0x3d4>
			FSM_TRANSIT_SWITCH
    2f0b:	85 ff                	test   %edi,%edi
    2f0d:	8d 76 00             	lea    0x0(%esi),%esi
    2f10:	0f 85 7e fe ff ff    	jne    2d94 <rrc_main+0x3d4>
			{
				FSM_CASE_TRANSIT(0, ST_CONNECTED_NORMALLY, reconfig_success(), "ST_CONNECTED_RECONF -> ST_CONNECTED_NORMALLY")
    2f16:	c7 05 5c 00 00 00 98 	movl   $0xd98,0x5c
    2f1d:	0d 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void reconfig_success(void)
{
	FIN(reconfig_success());
	fsm_printf("[rrc] [fsm] reconfig_success().\n");
    2f20:	c7 04 24 c8 0d 00 00 	movl   $0xdc8,(%esp)
    2f27:	e8 fc ff ff ff       	call   2f28 <rrc_main+0x568>
	struct RRCConnectionReconfigurationComplete msg2;
	msg2.rrcTransactionIdentifier = rrcConnectionReconfiguration->rrcTransactionIdentifier;
	DoSendRrcConnectionReconfigurationCompleted (msg2);
    2f2c:	a1 00 00 00 00       	mov    0x0,%eax
    2f31:	0f b6 00             	movzbl (%eax),%eax
    2f34:	e8 fc ff ff ff       	call   2f35 <rrc_main+0x575>

	if(rrcConnectionReconfiguration != NULL)
    2f39:	a1 00 00 00 00       	mov    0x0,%eax
    2f3e:	85 c0                	test   %eax,%eax
    2f40:	74 0f                	je     2f51 <rrc_main+0x591>
	{
		fsm_mem_free(rrcConnectionReconfiguration);
    2f42:	e8 fc ff ff ff       	call   2f43 <rrc_main+0x583>
		rrcConnectionReconfiguration=NULL;
    2f47:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    2f4e:	00 00 00 
	}

	fsm_printf("[rrc] [fsm] reconfig success.\n");//test
    2f51:	c7 04 24 ec 0d 00 00 	movl   $0xdec,(%esp)
    2f58:	e8 fc ff ff ff       	call   2f59 <rrc_main+0x599>
    2f5d:	e9 99 fc ff ff       	jmp    2bfb <rrc_main+0x23b>
    2f62:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_reject(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(2, ST_CONNECTED_NORMALLY, rcv_rrc_conn_setup(), "ST_IDLE_CONNECTING -> ST_CONNECTED_NORMALLY")
				FSM_CASE_DEFAULT(ST_IDLE_CONNECTING, st_idle_connecting_default(), "ST_IDLE_CONNECTING -> ST_IDLE_CONNECTING")   //transit to idle state by default.
			}
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_NORMALLY, "ST_CONNECTED_NORMALLY", st_connect_normal_enter(),st_connect_normal_exit())
    2f68:	c7 05 5c 00 00 00 2b 	movl   $0x22b,0x5c
    2f6f:	02 00 00 
	FOUT;
}
static void st_connect_normal_exit(void)
{
	FIN(st_connect_normal_exit());
	fsm_printf("[rrc] [fsm] st_connect_normal_exit().\n");
    2f72:	c7 04 24 b8 0b 00 00 	movl   $0xbb8,(%esp)
    2f79:	e8 fc ff ff ff       	call   2f7a <rrc_main+0x5ba>

	if(RRC_CLOSE)
    2f7e:	e8 fc ff ff ff       	call   2f7f <rrc_main+0x5bf>
    2f83:	83 f8 05             	cmp    $0x5,%eax
    2f86:	0f 84 52 04 00 00    	je     33de <rrc_main+0xa1e>
    2f8c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			}
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_NORMALLY, "ST_CONNECTED_NORMALLY", st_connect_normal_enter(),st_connect_normal_exit())
		{
			FSM_COND_TEST_IN("ST_CONNECTED_NORMALLY")
			FSM_TEST_COND(Evt_RcvRRCConnReconfig)
    2f90:	e8 fc ff ff ff       	call   2f91 <rrc_main+0x5d1>
    2f95:	83 f8 03             	cmp    $0x3,%eax
    2f98:	0f 84 26 04 00 00    	je     33c4 <rrc_main+0xa04>
    2f9e:	bf ff ff ff ff       	mov    $0xffffffff,%edi
    2fa3:	31 f6                	xor    %esi,%esi
			FSM_TEST_COND(Evt_RcvRRCConnRelease)
    2fa5:	e8 fc ff ff ff       	call   2fa6 <rrc_main+0x5e6>
    2faa:	83 f8 03             	cmp    $0x3,%eax
    2fad:	0f 84 ca fb ff ff    	je     2b7d <rrc_main+0x1bd>
			FSM_COND_TEST_OUT("ST_CONNECTED_NORMALLY")
    2fb3:	85 f6                	test   %esi,%esi
    2fb5:	0f 84 f7 fb ff ff    	je     2bb2 <rrc_main+0x1f2>
			FSM_TRANSIT_SWITCH
    2fbb:	85 ff                	test   %edi,%edi
    2fbd:	8d 76 00             	lea    0x0(%esi),%esi
    2fc0:	0f 85 ec fb ff ff    	jne    2bb2 <rrc_main+0x1f2>
			{
				FSM_CASE_TRANSIT(0, ST_CONNECTED_RECONF, rcv_rrc_conn_reconf(), "ST_CONNECTED_NORMALLY -> ST_CONNECTED_RECONF")
    2fc6:	c7 05 5c 00 00 00 e0 	movl   $0xbe0,0x5c
    2fcd:	0b 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void rcv_rrc_conn_reconf(void)
{
	FIN(rcv_rrc_conn_reconf());
	fsm_printf("[rrc] [fsm] rcv_rrc_conn_reconf().\n");
    2fd0:	c7 04 24 10 0c 00 00 	movl   $0xc10,(%esp)
    2fd7:	e8 fc ff ff ff       	call   2fd8 <rrc_main+0x618>

	fsm_printf("[rrc] [fsm] DoRecvRrcConnectionReconfiguration().\n");
    2fdc:	c7 04 24 34 0c 00 00 	movl   $0xc34,(%esp)
    2fe3:	e8 fc ff ff ff       	call   2fe4 <rrc_main+0x624>

	//used for test
//	rrcConnectionReconfiguration = SetRrcConnReconfigmessage();
//	fsm_printf("[rrc] [fsm] rrcConnectionReconfiguration->rrcTransactionIdentifier=%d\n",rrcConnectionReconfiguration->rrcTransactionIdentifier);
	if(rrcConnectionReconfiguration == NULL)
    2fe8:	a1 00 00 00 00       	mov    0x0,%eax
    2fed:	85 c0                	test   %eax,%eax
    2fef:	0f 84 b0 06 00 00    	je     36a5 <rrc_main+0xce5>
	{
		fsm_printf("[rrc] invalid rrcConnectionReconfiguration.\n");
		FOUT;
	}
	DoRecvRrcConnectionReconfiguration(rrcConnectionReconfiguration);
    2ff5:	e8 fc ff ff ff       	call   2ff6 <rrc_main+0x636>

	fsm_mem_free(rrcConnectionReconfiguration);
    2ffa:	a1 00 00 00 00       	mov    0x0,%eax
    2fff:	e8 fc ff ff ff       	call   3000 <rrc_main+0x640>
	rrcConnectionReconfiguration = NULL;
    3004:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    300b:	00 00 00 
    300e:	e9 c8 fd ff ff       	jmp    2ddb <rrc_main+0x41b>
    3013:	90                   	nop
    3014:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
				{
					FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, transit_to_idle(), "ST_IDLE_WAIT_SYSINFO -> ST_IDLE_NORMALLY")
					FSM_CASE_DEFAULT(ST_IDLE_WAIT_SYSINFO, st_wait_sysInfo_default(), "ST_IDLE_WAIT_SYSINFO -> ST_IDLE_WAIT_SYSINFO")   //transit to idle state by default.
				}
		}
		FSM_STATE_UNFORCED(ST_IDLE_NORMALLY, "ST_IDLE_NORMALLY", st_idle_normal_enter(),st_idle_normal_exit())
    3018:	c7 05 5c 00 00 00 c5 	movl   $0x1c5,0x5c
    301f:	01 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_idle_normal_exit(void)
{
	FIN(st_idle_normal_exit());
	fsm_printf("[rrc] [fsm] st_idle_normal_exit().\n");
    3022:	c7 04 24 d0 09 00 00 	movl   $0x9d0,(%esp)
    3029:	e8 fc ff ff ff       	call   302a <rrc_main+0x66a>


	if(RRC_CLOSE)
    302e:	e8 fc ff ff ff       	call   302f <rrc_main+0x66f>
    3033:	83 f8 05             	cmp    $0x5,%eax
    3036:	0f 84 4e 02 00 00    	je     328a <rrc_main+0x8ca>
    303c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
				}
		}
		FSM_STATE_UNFORCED(ST_IDLE_NORMALLY, "ST_IDLE_NORMALLY", st_idle_normal_enter(),st_idle_normal_exit())
		{
			FSM_COND_TEST_IN("ST_IDLE_NORMALLY")
			FSM_TEST_COND(Evt_RcvConnReqNAS)
    3040:	e8 fc ff ff ff       	call   3041 <rrc_main+0x681>
    3045:	83 f8 03             	cmp    $0x3,%eax
    3048:	0f 84 9c 02 00 00    	je     32ea <rrc_main+0x92a>
			FSM_COND_TEST_OUT("ST_IDLE_NORMALLY")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_IDLE_CONNECTING, transit_to_idle_connecting(), "ST_IDLE_NORMALLY -> ST_IDLE_CONNECTING")
				FSM_CASE_DEFAULT(ST_IDLE_NORMALLY, st_idle_normal_default(), "ST_IDLE_NORMALLY -> ST_IDLE_NORMALLY")   //transit to idle state by default.
    304e:	c7 05 5c 00 00 00 f4 	movl   $0x9f4,0x5c
    3055:	09 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_idle_normal_default(void)
{
	FIN(st_idle_normal_default());
	fsm_printf("[rrc] [fsm] st_idle_normal_default().\n");
    3058:	c7 04 24 1c 0a 00 00 	movl   $0xa1c,(%esp)
    305f:	e8 fc ff ff ff       	call   3060 <rrc_main+0x6a0>

	if(EVT_IOCTL_ARRIVAL)
    3064:	e8 fc ff ff ff       	call   3065 <rrc_main+0x6a5>
    3069:	83 f8 05             	cmp    $0x5,%eax
    306c:	0f 84 4e 01 00 00    	je     31c0 <rrc_main+0x800>
	{
		rrc_ioctl_handler();
	}
	else if(EVT_RRC_PK_FROM_LOWER)
    3072:	e8 fc ff ff ff       	call   3073 <rrc_main+0x6b3>
    3077:	83 f8 02             	cmp    $0x2,%eax
    307a:	0f 84 e0 04 00 00    	je     3560 <rrc_main+0xba0>
	{
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_rlc(pkptr);
	}
	else if(EVT_RRC_PK_FROM_UPPER)
    3080:	e8 fc ff ff ff       	call   3081 <rrc_main+0x6c1>
    3085:	83 f8 01             	cmp    $0x1,%eax
    3088:	0f 84 7c 05 00 00    	je     360a <rrc_main+0xc4a>
    308e:	66 90                	xchg   %ax,%ax
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_upper(pkptr);
	}
	else
	{
		other_events_handler();
    3090:	e8 9b f3 ff ff       	call   2430 <other_events_handler>
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_CONNECTED_NORMALLY, rcv_rrc_conn_reestablishment(), "ST_CONNECTED_REESTABLISH -> ST_CONNECTED_NORMALLY")
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_reestablish_reject(), "ST_CONNECTED_REESTABLISH -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(2, ST_IDLE_NORMALLY, t301_timeout(), "ST_CONNECTED_REESTABLISH -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(3, ST_IDLE_NORMALLY, t311_timeout(), "ST_CONNECTED_REESTABLISH -> ST_IDLE_NORMALLY")
    3095:	c7 03 06 00 00 00    	movl   $0x6,(%ebx)
    309b:	e9 a0 fa ff ff       	jmp    2b40 <rrc_main+0x180>
	{
		FSM_STATE_FORCED(ST_INIT, "ST_INIT", st_init_enter(), st_init_exit())
		{
			FSM_TRANSIT_FORCE(ST_IDLE_CELL_SEL, , "default", "", "ST_INIT -> ST_IDLE_CELL_SEL");
		}
		FSM_STATE_UNFORCED(ST_IDLE_CELL_SEL, "ST_IDLE_CELL_SEL", st_cell_sel_enter(), st_cell_sel_exit())
    30a0:	c7 05 5c 00 00 00 9f 	movl   $0x19f,0x5c
    30a7:	01 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_cell_sel_exit(void)
{
	FIN(st_cell_sel_exit());
	fsm_printf("[rrc] [fsm] st_cell_sel_exit().\n");
    30aa:	c7 04 24 f4 07 00 00 	movl   $0x7f4,(%esp)
    30b1:	e8 fc ff ff ff       	call   30b2 <rrc_main+0x6f2>

	//test_send_msg_to_us();

	if(RRC_CLOSE)
    30b6:	e8 fc ff ff ff       	call   30b7 <rrc_main+0x6f7>
    30bb:	83 f8 05             	cmp    $0x5,%eax
    30be:	0f 84 a6 01 00 00    	je     326a <rrc_main+0x8aa>
			FSM_TRANSIT_FORCE(ST_IDLE_CELL_SEL, , "default", "", "ST_INIT -> ST_IDLE_CELL_SEL");
		}
		FSM_STATE_UNFORCED(ST_IDLE_CELL_SEL, "ST_IDLE_CELL_SEL", st_cell_sel_enter(), st_cell_sel_exit())
		{
			FSM_COND_TEST_IN("ST_IDLE_CELL_SEL")
				FSM_TEST_COND(EVT_BEGIN_RECV_SYSINFO)
    30c4:	e8 fc ff ff ff       	call   30c5 <rrc_main+0x705>
    30c9:	83 f8 03             	cmp    $0x3,%eax
    30cc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    30d0:	0f 84 d4 01 00 00    	je     32aa <rrc_main+0x8ea>
				FSM_COND_TEST_OUT("ST_IDLE_CELL_SEL")
				FSM_TRANSIT_SWITCH
				{
					FSM_CASE_TRANSIT(0, ST_IDLE_WAIT_SYSINFO, start_recv_sysInfo(), "ST_IDLE_CELL_SEL -> ST_IDLE_WAIT_SYSINFO")
					FSM_CASE_DEFAULT(ST_IDLE_CELL_SEL, st_cell_sel_default(), "ST_IDLE_CELL_SEL -> ST_IDLE_CELL_SEL")
    30d6:	c7 05 5c 00 00 00 18 	movl   $0x818,0x5c
    30dd:	08 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void st_cell_sel_default(void)
{
	FIN(st_cell_sel_default());
	fsm_printf("[rrc] [fsm] st_cell_sel_default().\n");
    30e0:	c7 04 24 40 08 00 00 	movl   $0x840,(%esp)
    30e7:	e8 fc ff ff ff       	call   30e8 <rrc_main+0x728>

	if(EVT_IOCTL_ARRIVAL)
    30ec:	e8 fc ff ff ff       	call   30ed <rrc_main+0x72d>
    30f1:	83 f8 05             	cmp    $0x5,%eax
    30f4:	0f 84 9e 00 00 00    	je     3198 <rrc_main+0x7d8>
    30fa:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	{
		rrc_ioctl_handler();
	}
	else if(EVT_RRC_PK_FROM_LOWER)
    3100:	e8 fc ff ff ff       	call   3101 <rrc_main+0x741>
    3105:	83 f8 02             	cmp    $0x2,%eax
    3108:	0f 84 77 04 00 00    	je     3585 <rrc_main+0xbc5>
    310e:	66 90                	xchg   %ax,%ax
	{
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_rlc(pkptr);
	}
	else if(EVT_RRC_PK_FROM_UPPER)
    3110:	e8 fc ff ff ff       	call   3111 <rrc_main+0x751>
    3115:	83 f8 01             	cmp    $0x1,%eax
    3118:	0f 84 d7 04 00 00    	je     35f5 <rrc_main+0xc35>
    311e:	66 90                	xchg   %ax,%ax
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_upper(pkptr);
	}
	else
	{
		other_events_handler();
    3120:	e8 0b f3 ff ff       	call   2430 <other_events_handler>
    3125:	e9 12 f9 ff ff       	jmp    2a3c <rrc_main+0x7c>
    312a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
			FSM_COND_TEST_IN("ST_CONNECTED_REESTABLISH")
			FSM_TEST_COND(Evt_RcvRRCConnReestablish)
			FSM_TEST_COND(Evt_RcvRRCConnReestablishReject)
			FSM_TEST_COND(Evt_TimeOut_T301)
			FSM_TEST_COND(Evt_TimeOut_T311)
			FSM_COND_TEST_OUT("ST_CONNECTED_REESTABLISH")
    3130:	85 f6                	test   %esi,%esi
    3132:	0f 84 63 fd ff ff    	je     2e9b <rrc_main+0x4db>
			FSM_TRANSIT_SWITCH
    3138:	83 ff 01             	cmp    $0x1,%edi
    313b:	90                   	nop
    313c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    3140:	0f 84 4f ff ff ff    	je     3095 <rrc_main+0x6d5>
    3146:	66 90                	xchg   %ax,%ax
    3148:	0f 8e 97 05 00 00    	jle    36e5 <rrc_main+0xd25>
    314e:	83 ff 02             	cmp    $0x2,%edi
    3151:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    3158:	0f 84 37 ff ff ff    	je     3095 <rrc_main+0x6d5>
    315e:	83 ff 03             	cmp    $0x3,%edi
    3161:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    3168:	0f 85 2d fd ff ff    	jne    2e9b <rrc_main+0x4db>
    316e:	66 90                	xchg   %ax,%ax
    3170:	e9 20 ff ff ff       	jmp    3095 <rrc_main+0x6d5>
    3175:	8d 76 00             	lea    0x0(%esi),%esi
static void st_wait_sysInfo_default(void)
{
	FIN(st_wait_sysInfo_default());
	fsm_printf("[rrc] [fsm] st_wait_sysInfo_default().\n");

	if(EVT_IOCTL_ARRIVAL)
    3178:	e8 fc ff ff ff       	call   3179 <rrc_main+0x7b9>
    317d:	83 f8 02             	cmp    $0x2,%eax
    3180:	0f 85 fc fa ff ff    	jne    2c82 <rrc_main+0x2c2>
	{
		rrc_ioctl_handler();
    3186:	e8 25 f2 ff ff       	call   23b0 <rrc_ioctl_handler>
    318b:	90                   	nop
    318c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    3190:	e9 10 fb ff ff       	jmp    2ca5 <rrc_main+0x2e5>
    3195:	8d 76 00             	lea    0x0(%esi),%esi
    3198:	90                   	nop
    3199:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
static void st_cell_sel_default(void)
{
	FIN(st_cell_sel_default());
	fsm_printf("[rrc] [fsm] st_cell_sel_default().\n");

	if(EVT_IOCTL_ARRIVAL)
    31a0:	e8 fc ff ff ff       	call   31a1 <rrc_main+0x7e1>
    31a5:	83 f8 02             	cmp    $0x2,%eax
    31a8:	0f 85 4c ff ff ff    	jne    30fa <rrc_main+0x73a>
    31ae:	66 90                	xchg   %ax,%ax
	{
		rrc_ioctl_handler();
    31b0:	e8 fb f1 ff ff       	call   23b0 <rrc_ioctl_handler>
    31b5:	e9 82 f8 ff ff       	jmp    2a3c <rrc_main+0x7c>
    31ba:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
static void st_idle_normal_default(void)
{
	FIN(st_idle_normal_default());
	fsm_printf("[rrc] [fsm] st_idle_normal_default().\n");

	if(EVT_IOCTL_ARRIVAL)
    31c0:	e8 fc ff ff ff       	call   31c1 <rrc_main+0x801>
    31c5:	83 f8 02             	cmp    $0x2,%eax
    31c8:	0f 85 a4 fe ff ff    	jne    3072 <rrc_main+0x6b2>
    31ce:	66 90                	xchg   %ax,%ax
	{
		rrc_ioctl_handler();
    31d0:	e8 db f1 ff ff       	call   23b0 <rrc_ioctl_handler>
    31d5:	e9 bb fe ff ff       	jmp    3095 <rrc_main+0x6d5>
    31da:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
			FSM_COND_TEST_OUT("ST_IDLE_CONNECTING")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, t300_timeout(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_reject(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(2, ST_CONNECTED_NORMALLY, rcv_rrc_conn_setup(), "ST_IDLE_CONNECTING -> ST_CONNECTED_NORMALLY")
    31e0:	c7 05 5c 00 00 00 0c 	movl   $0xb0c,0x5c
    31e7:	0b 00 00 
    31ea:	e8 c1 f6 ff ff       	call   28b0 <rcv_rrc_conn_setup>
    31ef:	c7 03 0a 00 00 00    	movl   $0xa,(%ebx)
    31f5:	e9 07 fa ff ff       	jmp    2c01 <rrc_main+0x241>
			FSM_TEST_COND(Evt_RcvRRCConnSetup)
			FSM_COND_TEST_OUT("ST_IDLE_CONNECTING")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, t300_timeout(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_reject(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
    31fa:	c7 05 5c 00 00 00 c0 	movl   $0xac0,0x5c
    3201:	0a 00 00 
 ******************************************************************************/
static void rcv_rrc_conn_reject(void)
{
	FIN(rcv_rrc_conn_reject());

	fsm_printf("[rrc] [fsm] rcv_rrc_conn_reject().\n");
    3204:	c7 04 24 e8 0a 00 00 	movl   $0xae8,(%esp)
    320b:	e8 fc ff ff ff       	call   320c <rrc_main+0x84c>
	cancleTimer(TIMER_T300);
    3210:	b8 2c 01 00 00       	mov    $0x12c,%eax
    3215:	e8 fc ff ff ff       	call   3216 <rrc_main+0x856>
	fsm_do_ioctrl(STRM_TO_MAC,  IOCCMD_RRCTOMAC_RESET  , NULL, 0);
    321a:	31 c9                	xor    %ecx,%ecx
    321c:	ba 03 00 00 00       	mov    $0x3,%edx
    3221:	b8 02 00 00 00       	mov    $0x2,%eax
    3226:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
    322d:	e8 fc ff ff ff       	call   322e <rrc_main+0x86e>
	setTimer(TIMER_T302, 2000);
    3232:	ba d0 07 00 00       	mov    $0x7d0,%edx
    3237:	b8 2e 01 00 00       	mov    $0x12e,%eax
    323c:	e8 fc ff ff ff       	call   323d <rrc_main+0x87d>
			FSM_TEST_COND(Evt_RcvRRCConnSetup)
			FSM_COND_TEST_OUT("ST_IDLE_CONNECTING")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, t300_timeout(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_reject(), "ST_IDLE_CONNECTING -> ST_IDLE_NORMALLY")
    3241:	c7 03 06 00 00 00    	movl   $0x6,(%ebx)
    3247:	e9 f4 f8 ff ff       	jmp    2b40 <rrc_main+0x180>
static void st_wait_sysInfo_exit(void)
{
	FIN(st_wait_sysInfo_exit());
	fsm_printf("[rrc] [fsm] st_wait_sysInfo_exit().\n");

	if(RRC_CLOSE)
    324c:	e8 fc ff ff ff       	call   324d <rrc_main+0x88d>
    3251:	83 f8 01             	cmp    $0x1,%eax
    3254:	0f 85 f2 f9 ff ff    	jne    2c4c <rrc_main+0x28c>
    325a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	{
		rrc_close();
    3260:	e8 fc ff ff ff       	call   3261 <rrc_main+0x8a1>
    3265:	e9 e2 f9 ff ff       	jmp    2c4c <rrc_main+0x28c>
    326a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	FIN(st_cell_sel_exit());
	fsm_printf("[rrc] [fsm] st_cell_sel_exit().\n");

	//test_send_msg_to_us();

	if(RRC_CLOSE)
    3270:	e8 fc ff ff ff       	call   3271 <rrc_main+0x8b1>
    3275:	83 f8 01             	cmp    $0x1,%eax
    3278:	0f 85 46 fe ff ff    	jne    30c4 <rrc_main+0x704>
    327e:	66 90                	xchg   %ax,%ax
	{
		rrc_close();
    3280:	e8 fc ff ff ff       	call   3281 <rrc_main+0x8c1>
    3285:	e9 3a fe ff ff       	jmp    30c4 <rrc_main+0x704>
    328a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
{
	FIN(st_idle_normal_exit());
	fsm_printf("[rrc] [fsm] st_idle_normal_exit().\n");


	if(RRC_CLOSE)
    3290:	e8 fc ff ff ff       	call   3291 <rrc_main+0x8d1>
    3295:	83 f8 01             	cmp    $0x1,%eax
    3298:	0f 85 9e fd ff ff    	jne    303c <rrc_main+0x67c>
    329e:	66 90                	xchg   %ax,%ax
	{
		rrc_close();
    32a0:	e8 fc ff ff ff       	call   32a1 <rrc_main+0x8e1>
    32a5:	e9 92 fd ff ff       	jmp    303c <rrc_main+0x67c>
    32aa:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
			FSM_TRANSIT_FORCE(ST_IDLE_CELL_SEL, , "default", "", "ST_INIT -> ST_IDLE_CELL_SEL");
		}
		FSM_STATE_UNFORCED(ST_IDLE_CELL_SEL, "ST_IDLE_CELL_SEL", st_cell_sel_enter(), st_cell_sel_exit())
		{
			FSM_COND_TEST_IN("ST_IDLE_CELL_SEL")
				FSM_TEST_COND(EVT_BEGIN_RECV_SYSINFO)
    32b0:	e8 fc ff ff ff       	call   32b1 <rrc_main+0x8f1>
    32b5:	85 c0                	test   %eax,%eax
    32b7:	0f 85 19 fe ff ff    	jne    30d6 <rrc_main+0x716>
				FSM_COND_TEST_OUT("ST_IDLE_CELL_SEL")
				FSM_TRANSIT_SWITCH
				{
					FSM_CASE_TRANSIT(0, ST_IDLE_WAIT_SYSINFO, start_recv_sysInfo(), "ST_IDLE_CELL_SEL -> ST_IDLE_WAIT_SYSINFO")
    32bd:	c7 05 5c 00 00 00 64 	movl   $0x864,0x5c
    32c4:	08 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void start_recv_sysInfo(void)
{
	FIN(start_recv_sysInfo());
	fsm_printf("[rrc] [fsm] start_recv_sysInfo().\n");
    32c7:	c7 04 24 90 08 00 00 	movl   $0x890,(%esp)
    32ce:	e8 fc ff ff ff       	call   32cf <rrc_main+0x90f>
	//Begin_recv_sysinfo();
	fsm_schedule_self(0, CODE_END_RECV_SYSINFO);
    32d3:	ba 01 00 00 00       	mov    $0x1,%edx
    32d8:	31 c0                	xor    %eax,%eax
    32da:	e8 fc ff ff ff       	call   32db <rrc_main+0x91b>
			FSM_COND_TEST_IN("ST_IDLE_CELL_SEL")
				FSM_TEST_COND(EVT_BEGIN_RECV_SYSINFO)
				FSM_COND_TEST_OUT("ST_IDLE_CELL_SEL")
				FSM_TRANSIT_SWITCH
				{
					FSM_CASE_TRANSIT(0, ST_IDLE_WAIT_SYSINFO, start_recv_sysInfo(), "ST_IDLE_CELL_SEL -> ST_IDLE_WAIT_SYSINFO")
    32df:	c7 03 04 00 00 00    	movl   $0x4,(%ebx)
    32e5:	e9 c1 f9 ff ff       	jmp    2cab <rrc_main+0x2eb>
				}
		}
		FSM_STATE_UNFORCED(ST_IDLE_NORMALLY, "ST_IDLE_NORMALLY", st_idle_normal_enter(),st_idle_normal_exit())
		{
			FSM_COND_TEST_IN("ST_IDLE_NORMALLY")
			FSM_TEST_COND(Evt_RcvConnReqNAS)
    32ea:	e8 fc ff ff ff       	call   32eb <rrc_main+0x92b>
    32ef:	83 f8 02             	cmp    $0x2,%eax
    32f2:	0f 85 56 fd ff ff    	jne    304e <rrc_main+0x68e>
			FSM_COND_TEST_OUT("ST_IDLE_NORMALLY")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_IDLE_CONNECTING, transit_to_idle_connecting(), "ST_IDLE_NORMALLY -> ST_IDLE_CONNECTING")
    32f8:	c7 05 5c 00 00 00 44 	movl   $0xa44,0x5c
    32ff:	0a 00 00 
    3302:	e8 99 f4 ff ff       	call   27a0 <transit_to_idle_connecting>
    3307:	c7 03 08 00 00 00    	movl   $0x8,(%ebx)
    330d:	e9 2e fa ff ff       	jmp    2d40 <rrc_main+0x380>
				}
		}
		FSM_STATE_UNFORCED(ST_IDLE_WAIT_SYSINFO, "ST_IDLE_WAIT_SYSINFO", st_wait_sysInfo_enter(),st_wait_sysInfo_exit())
		{
			FSM_COND_TEST_IN("ST_IDLE_WAIT_SYSINFO")
				FSM_TEST_COND(EVT_END_RECV_SYSINFO)
    3312:	e8 fc ff ff ff       	call   3313 <rrc_main+0x953>
    3317:	83 f8 01             	cmp    $0x1,%eax
    331a:	0f 85 3e f9 ff ff    	jne    2c5e <rrc_main+0x29e>
				FSM_COND_TEST_OUT("ST_IDLE_WAIT_SYSINFO")
				FSM_TRANSIT_SWITCH
				{
					FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, transit_to_idle(), "ST_IDLE_WAIT_SYSINFO -> ST_IDLE_NORMALLY")
    3320:	c7 05 5c 00 00 00 5c 	movl   $0x95c,0x5c
    3327:	09 00 00 
 ** Modified Date: 
 ******************************************************************************/
static void transit_to_idle(void)
{
	FIN(transit_to_idle());
	fsm_printf("[rrc] [fsm] transit_to_idle().\n");
    332a:	c7 04 24 88 09 00 00 	movl   $0x988,(%esp)
    3331:	e8 fc ff ff ff       	call   3332 <rrc_main+0x972>
	fsm_do_ioctrl(STRM_TO_MAC, TEST_RECV_PADING, NULL, 0);
    3336:	31 c9                	xor    %ecx,%ecx
    3338:	ba 45 00 00 00       	mov    $0x45,%edx
    333d:	b8 02 00 00 00       	mov    $0x2,%eax
    3342:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
    3349:	e8 fc ff ff ff       	call   334a <rrc_main+0x98a>
			FSM_COND_TEST_IN("ST_IDLE_WAIT_SYSINFO")
				FSM_TEST_COND(EVT_END_RECV_SYSINFO)
				FSM_COND_TEST_OUT("ST_IDLE_WAIT_SYSINFO")
				FSM_TRANSIT_SWITCH
				{
					FSM_CASE_TRANSIT(0, ST_IDLE_NORMALLY, transit_to_idle(), "ST_IDLE_WAIT_SYSINFO -> ST_IDLE_NORMALLY")
    334e:	c7 03 06 00 00 00    	movl   $0x6,(%ebx)
    3354:	e9 e7 f7 ff ff       	jmp    2b40 <rrc_main+0x180>
			FSM_TEST_COND(Evt_RcvRRCConnRelease)
			FSM_COND_TEST_OUT("ST_CONNECTED_NORMALLY")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_CONNECTED_RECONF, rcv_rrc_conn_reconf(), "ST_CONNECTED_NORMALLY -> ST_CONNECTED_RECONF")
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_release(), "ST_CONNECTED_NORMALLY -> ST_IDLE_NORMALLY")
    3359:	c7 05 5c 00 00 00 98 	movl   $0xc98,0x5c
    3360:	0c 00 00 
 ** Modified Date: 2014/10/1
 ******************************************************************************/
static void rcv_rrc_conn_release(void)
{
	FIN(rcv_rrc_conn_release());
	fsm_printf("[rrc] [fsm] rcv_rrc_conn_release().\n");
    3363:	c7 04 24 c4 0c 00 00 	movl   $0xcc4,(%esp)
    336a:	e8 fc ff ff ff       	call   336b <rrc_main+0x9ab>
	//generator rrcConnectionRelease info testing
//	rrcConnectionRelease = gen_release();

	//if have cell_reselection_priority_info then stored cell_reselection_priority_info
	cell_reselection_priority_info(rrcConnectionRelease);
    336f:	a1 00 00 00 00       	mov    0x0,%eax
    3374:	e8 fc ff ff ff       	call   3375 <rrc_main+0x9b5>
	//set the cell_reselection_priority_info valid time
	set_t320(rrcConnectionRelease);
    3379:	a1 00 00 00 00       	mov    0x0,%eax
    337e:	e8 fc ff ff ff       	call   337f <rrc_main+0x9bf>
	//reset MAC
	fsm_do_ioctrl(STRM_TO_MAC,  IOCCMD_RRCTOMAC_RESET  , NULL, 0);
    3383:	31 c9                	xor    %ecx,%ecx
    3385:	ba 03 00 00 00       	mov    $0x3,%edx
    338a:	b8 02 00 00 00       	mov    $0x2,%eax
    338f:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
    3396:	e8 fc ff ff ff       	call   3397 <rrc_main+0x9d7>
	//stop all timer except t320 
	stop_timer();
    339b:	e8 fc ff ff ff       	call   339c <rrc_main+0x9dc>
	//release all radio resource
	release_radio_resource();
    33a0:	e8 fc ff ff ff       	call   33a1 <rrc_main+0x9e1>
	//fix me:report release cause information to up
	//report_to_userspace();
	fsm_mem_free(rrcConnectionRelease);
    33a5:	a1 00 00 00 00       	mov    0x0,%eax
    33aa:	e8 fc ff ff ff       	call   33ab <rrc_main+0x9eb>
	rrcConnectionRelease=NULL;
    33af:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    33b6:	00 00 00 
			FSM_TEST_COND(Evt_RcvRRCConnRelease)
			FSM_COND_TEST_OUT("ST_CONNECTED_NORMALLY")
			FSM_TRANSIT_SWITCH
			{
				FSM_CASE_TRANSIT(0, ST_CONNECTED_RECONF, rcv_rrc_conn_reconf(), "ST_CONNECTED_NORMALLY -> ST_CONNECTED_RECONF")
				FSM_CASE_TRANSIT(1, ST_IDLE_NORMALLY, rcv_rrc_conn_release(), "ST_CONNECTED_NORMALLY -> ST_IDLE_NORMALLY")
    33b9:	c7 03 06 00 00 00    	movl   $0x6,(%ebx)
    33bf:	e9 7c f7 ff ff       	jmp    2b40 <rrc_main+0x180>
			}
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_NORMALLY, "ST_CONNECTED_NORMALLY", st_connect_normal_enter(),st_connect_normal_exit())
		{
			FSM_COND_TEST_IN("ST_CONNECTED_NORMALLY")
			FSM_TEST_COND(Evt_RcvRRCConnReconfig)
    33c4:	e8 fc ff ff ff       	call   33c5 <rrc_main+0xa05>
    33c9:	31 ff                	xor    %edi,%edi
    33cb:	be 01 00 00 00       	mov    $0x1,%esi
    33d0:	83 f8 06             	cmp    $0x6,%eax
    33d3:	0f 85 c5 fb ff ff    	jne    2f9e <rrc_main+0x5de>
    33d9:	e9 c7 fb ff ff       	jmp    2fa5 <rrc_main+0x5e5>
    33de:	66 90                	xchg   %ax,%ax
static void st_connect_normal_exit(void)
{
	FIN(st_connect_normal_exit());
	fsm_printf("[rrc] [fsm] st_connect_normal_exit().\n");

	if(RRC_CLOSE)
    33e0:	e8 fc ff ff ff       	call   33e1 <rrc_main+0xa21>
    33e5:	83 f8 01             	cmp    $0x1,%eax
    33e8:	0f 85 9e fb ff ff    	jne    2f8c <rrc_main+0x5cc>
    33ee:	66 90                	xchg   %ax,%ax
	{
		rrc_close();
    33f0:	e8 fc ff ff ff       	call   33f1 <rrc_main+0xa31>
    33f5:	e9 92 fb ff ff       	jmp    2f8c <rrc_main+0x5cc>
    33fa:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_REESTABLISH, "ST_CONNECTED_REESTABLISH", st_connect_reest_enter(),st_connect_reest_exit())
		{
			FSM_COND_TEST_IN("ST_CONNECTED_REESTABLISH")
			FSM_TEST_COND(Evt_RcvRRCConnReestablish)
			FSM_TEST_COND(Evt_RcvRRCConnReestablishReject)
    3400:	e8 fc ff ff ff       	call   3401 <rrc_main+0xa41>
    3405:	83 f8 0b             	cmp    $0xb,%eax
    3408:	0f 85 47 fa ff ff    	jne    2e55 <rrc_main+0x495>
    340e:	83 c6 01             	add    $0x1,%esi
    3411:	bf 01 00 00 00       	mov    $0x1,%edi
    3416:	e9 3a fa ff ff       	jmp    2e55 <rrc_main+0x495>
    341b:	90                   	nop
    341c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			}
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_REESTABLISH, "ST_CONNECTED_REESTABLISH", st_connect_reest_enter(),st_connect_reest_exit())
		{
			FSM_COND_TEST_IN("ST_CONNECTED_REESTABLISH")
			FSM_TEST_COND(Evt_RcvRRCConnReestablish)
    3420:	e8 fc ff ff ff       	call   3421 <rrc_main+0xa61>
    3425:	31 ff                	xor    %edi,%edi
    3427:	be 01 00 00 00       	mov    $0x1,%esi
    342c:	83 f8 0a             	cmp    $0xa,%eax
    342f:	0f 85 0b fa ff ff    	jne    2e40 <rrc_main+0x480>
    3435:	e9 0d fa ff ff       	jmp    2e47 <rrc_main+0x487>
		FSM_STATE_UNFORCED(ST_IDLE_CONNECTING, "ST_IDLE_CONNECTING", st_idle_connecting_enter(),st_idle_connecting_exit())
		{
			FSM_COND_TEST_IN("ST_IDLE_CONNECTING")
			FSM_TEST_COND(Evt_TimeOut_T300)
			FSM_TEST_COND(Evt_RcvRRCConnReject)
			FSM_TEST_COND(Evt_RcvRRCConnSetup)
    343a:	e8 fc ff ff ff       	call   343b <rrc_main+0xa7b>
    343f:	83 f8 05             	cmp    $0x5,%eax
    3442:	0f 85 89 f6 ff ff    	jne    2ad1 <rrc_main+0x111>
    3448:	83 c6 01             	add    $0x1,%esi
    344b:	bf 02 00 00 00       	mov    $0x2,%edi
    3450:	e9 7c f6 ff ff       	jmp    2ad1 <rrc_main+0x111>
		}
		FSM_STATE_UNFORCED(ST_IDLE_CONNECTING, "ST_IDLE_CONNECTING", st_idle_connecting_enter(),st_idle_connecting_exit())
		{
			FSM_COND_TEST_IN("ST_IDLE_CONNECTING")
			FSM_TEST_COND(Evt_TimeOut_T300)
			FSM_TEST_COND(Evt_RcvRRCConnReject)
    3455:	e8 fc ff ff ff       	call   3456 <rrc_main+0xa96>
    345a:	83 f8 04             	cmp    $0x4,%eax
    345d:	0f 85 60 f6 ff ff    	jne    2ac3 <rrc_main+0x103>
    3463:	83 c6 01             	add    $0x1,%esi
    3466:	bf 01 00 00 00       	mov    $0x1,%edi
    346b:	e9 53 f6 ff ff       	jmp    2ac3 <rrc_main+0x103>
			}
		}
		FSM_STATE_UNFORCED(ST_IDLE_CONNECTING, "ST_IDLE_CONNECTING", st_idle_connecting_enter(),st_idle_connecting_exit())
		{
			FSM_COND_TEST_IN("ST_IDLE_CONNECTING")
			FSM_TEST_COND(Evt_TimeOut_T300)
    3470:	e8 fc ff ff ff       	call   3471 <rrc_main+0xab1>
    3475:	31 ff                	xor    %edi,%edi
    3477:	be 01 00 00 00       	mov    $0x1,%esi
    347c:	83 f8 03             	cmp    $0x3,%eax
    347f:	0f 85 29 f6 ff ff    	jne    2aae <rrc_main+0xee>
    3485:	e9 2b f6 ff ff       	jmp    2ab5 <rrc_main+0xf5>
static void st_idle_connecting_exit(void)
{
	FIN(st_idle_connecting_exit());
	fsm_printf("[rrc] [fsm] st_idle_connecting_exit().\n");

	if(RRC_CLOSE)
    348a:	e8 fc ff ff ff       	call   348b <rrc_main+0xacb>
    348f:	83 f8 01             	cmp    $0x1,%eax
    3492:	0f 85 04 f6 ff ff    	jne    2a9c <rrc_main+0xdc>
	{
		rrc_close();
    3498:	e8 fc ff ff ff       	call   3499 <rrc_main+0xad9>
    349d:	8d 76 00             	lea    0x0(%esi),%esi
    34a0:	e9 f7 f5 ff ff       	jmp    2a9c <rrc_main+0xdc>
    34a5:	8d 76 00             	lea    0x0(%esi),%esi
			}
		}
		FSM_STATE_UNFORCED(ST_CONNECTED_RECONF, "ST_CONNECTED_RECONF", st_connect_reconf_enter(),st_connect_reconf_exit())
		{
			FSM_COND_TEST_IN("ST_CONNECTED_RECONF")
			FSM_TEST_COND(Evt_ReconfigSuccess)
    34a8:	e8 fc ff ff ff       	call   34a9 <rrc_main+0xae9>
    34ad:	31 ff                	xor    %edi,%edi
    34af:	be 01 00 00 00       	mov    $0x1,%esi
    34b4:	83 f8 08             	cmp    $0x8,%eax
    34b7:	0f 85 31 fa ff ff    	jne    2eee <rrc_main+0x52e>
    34bd:	e9 33 fa ff ff       	jmp    2ef5 <rrc_main+0x535>
static void st_connect_reconf_exit(void)
{
	FIN(st_connect_reconf_exit());
	fsm_printf("[rrc] [fsm] st_connect_reconf_exit().\n");

	if(RRC_CLOSE)
    34c2:	e8 fc ff ff ff       	call   34c3 <rrc_main+0xb03>
    34c7:	83 f8 01             	cmp    $0x1,%eax
    34ca:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    34d0:	0f 85 06 fa ff ff    	jne    2edc <rrc_main+0x51c>
	{
		rrc_close();
    34d6:	e8 fc ff ff ff       	call   34d7 <rrc_main+0xb17>
    34db:	90                   	nop
    34dc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    34e0:	e9 f7 f9 ff ff       	jmp    2edc <rrc_main+0x51c>
    34e5:	8d 76 00             	lea    0x0(%esi),%esi
 ******************************************************************************/

static void st_init_enter(void)
{
	FIN(st_init_enter());
	if(RRC_OPEN)
    34e8:	e8 fc ff ff ff       	call   34e9 <rrc_main+0xb29>
    34ed:	85 c0                	test   %eax,%eax
    34ef:	90                   	nop
    34f0:	0f 85 2a f5 ff ff    	jne    2a20 <rrc_main+0x60>
	{
		fsm_printf("[rrc] [fsm] st_init_enter().\n");
    34f6:	c7 04 24 30 01 00 00 	movl   $0x130,(%esp)
    34fd:	e8 fc ff ff ff       	call   34fe <rrc_main+0xb3e>
		fsm_printf("Setup message size: %d\n", sizeof(struct RRCConnectionSetup));
    3502:	c7 44 24 04 f0 04 00 	movl   $0x4f0,0x4(%esp)
    3509:	00 
    350a:	c7 04 24 4e 01 00 00 	movl   $0x14e,(%esp)
    3511:	e8 fc ff ff ff       	call   3512 <rrc_main+0xb52>
		//SV init
		SV_PTR_GET(rrc_sv);
    3516:	e8 fc ff ff ff       	call   3517 <rrc_main+0xb57>
		SV(hello_count) = 0;
    351b:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
    3521:	e9 fa f4 ff ff       	jmp    2a20 <rrc_main+0x60>
		{
			FSM_COND_TEST_IN("ST_CONNECTED_REESTABLISH")
			FSM_TEST_COND(Evt_RcvRRCConnReestablish)
			FSM_TEST_COND(Evt_RcvRRCConnReestablishReject)
			FSM_TEST_COND(Evt_TimeOut_T301)
			FSM_TEST_COND(Evt_TimeOut_T311)
    3526:	e8 fc ff ff ff       	call   3527 <rrc_main+0xb67>
    352b:	83 f8 0d             	cmp    $0xd,%eax
    352e:	66 90                	xchg   %ax,%ax
    3530:	0f 85 40 f9 ff ff    	jne    2e76 <rrc_main+0x4b6>
    3536:	83 c6 01             	add    $0x1,%esi
    3539:	bf 03 00 00 00       	mov    $0x3,%edi
    353e:	66 90                	xchg   %ax,%ax
    3540:	e9 31 f9 ff ff       	jmp    2e76 <rrc_main+0x4b6>
		FSM_STATE_UNFORCED(ST_CONNECTED_REESTABLISH, "ST_CONNECTED_REESTABLISH", st_connect_reest_enter(),st_connect_reest_exit())
		{
			FSM_COND_TEST_IN("ST_CONNECTED_REESTABLISH")
			FSM_TEST_COND(Evt_RcvRRCConnReestablish)
			FSM_TEST_COND(Evt_RcvRRCConnReestablishReject)
			FSM_TEST_COND(Evt_TimeOut_T301)
    3545:	e8 fc ff ff ff       	call   3546 <rrc_main+0xb86>
    354a:	83 f8 0c             	cmp    $0xc,%eax
    354d:	0f 85 13 f9 ff ff    	jne    2e66 <rrc_main+0x4a6>
    3553:	83 c6 01             	add    $0x1,%esi
    3556:	bf 02 00 00 00       	mov    $0x2,%edi
    355b:	e9 06 f9 ff ff       	jmp    2e66 <rrc_main+0x4a6>
	{
		rrc_ioctl_handler();
	}
	else if(EVT_RRC_PK_FROM_LOWER)
	{
		FSM_PKT* pkptr = fsm_pkt_get();
    3560:	e8 fc ff ff ff       	call   3561 <rrc_main+0xba1>
		rrc_messege_handler_rlc(pkptr);
    3565:	e8 76 e7 ff ff       	call   1ce0 <rrc_messege_handler_rlc>
    356a:	e9 26 fb ff ff       	jmp    3095 <rrc_main+0x6d5>
    356f:	90                   	nop
	{
		rrc_ioctl_handler();
	}
	else if(EVT_RRC_PK_FROM_LOWER)
	{
		FSM_PKT* pkptr = fsm_pkt_get();
    3570:	e8 fc ff ff ff       	call   3571 <rrc_main+0xbb1>
    3575:	8d 76 00             	lea    0x0(%esi),%esi
		rrc_messege_handler_rlc(pkptr);
    3578:	e8 63 e7 ff ff       	call   1ce0 <rrc_messege_handler_rlc>
    357d:	8d 76 00             	lea    0x0(%esi),%esi
    3580:	e9 20 f7 ff ff       	jmp    2ca5 <rrc_main+0x2e5>
    3585:	8d 76 00             	lea    0x0(%esi),%esi
	{
		rrc_ioctl_handler();
	}
	else if(EVT_RRC_PK_FROM_LOWER)
	{
		FSM_PKT* pkptr = fsm_pkt_get();
    3588:	e8 fc ff ff ff       	call   3589 <rrc_main+0xbc9>
    358d:	8d 76 00             	lea    0x0(%esi),%esi
		rrc_messege_handler_rlc(pkptr);
    3590:	e8 4b e7 ff ff       	call   1ce0 <rrc_messege_handler_rlc>
    3595:	e9 a2 f4 ff ff       	jmp    2a3c <rrc_main+0x7c>
    359a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
static void st_connect_reconf_default(void)
{
	FIN(st_connect_reconf_default());
	fsm_printf("[rrc] [fsm] st_connect_reconf_default().\n");

	if(EVT_IOCTL_ARRIVAL)
    35a0:	e8 fc ff ff ff       	call   35a1 <rrc_main+0xbe1>
    35a5:	83 f8 02             	cmp    $0x2,%eax
    35a8:	0f 85 0a f8 ff ff    	jne    2db8 <rrc_main+0x3f8>
    35ae:	66 90                	xchg   %ax,%ax
	{
		rrc_ioctl_handler();
    35b0:	e8 fb ed ff ff       	call   23b0 <rrc_ioctl_handler>
    35b5:	e9 21 f8 ff ff       	jmp    2ddb <rrc_main+0x41b>
    35ba:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
static void st_connect_normal_default(void)
{
	FIN(st_connect_normal_default());
	fsm_printf("[rrc] [fsm] st_connect_normal_default().\n");

	if(EVT_IOCTL_ARRIVAL)
    35c0:	e8 fc ff ff ff       	call   35c1 <rrc_main+0xc01>
    35c5:	83 f8 02             	cmp    $0x2,%eax
    35c8:	0f 85 08 f6 ff ff    	jne    2bd6 <rrc_main+0x216>
    35ce:	66 90                	xchg   %ax,%ax
	{
		rrc_ioctl_handler();
    35d0:	e8 db ed ff ff       	call   23b0 <rrc_ioctl_handler>
    35d5:	e9 21 f6 ff ff       	jmp    2bfb <rrc_main+0x23b>
    35da:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_rlc(pkptr);
	}
	else if(EVT_RRC_PK_FROM_UPPER)
	{
		FSM_PKT* pkptr = fsm_pkt_get();
    35e0:	e8 fc ff ff ff       	call   35e1 <rrc_main+0xc21>
    35e5:	8d 76 00             	lea    0x0(%esi),%esi
		rrc_messege_handler_upper(pkptr);
    35e8:	e8 83 ea ff ff       	call   2070 <rrc_messege_handler_upper>
    35ed:	8d 76 00             	lea    0x0(%esi),%esi
    35f0:	e9 b0 f6 ff ff       	jmp    2ca5 <rrc_main+0x2e5>
    35f5:	8d 76 00             	lea    0x0(%esi),%esi
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_rlc(pkptr);
	}
	else if(EVT_RRC_PK_FROM_UPPER)
	{
		FSM_PKT* pkptr = fsm_pkt_get();
    35f8:	e8 fc ff ff ff       	call   35f9 <rrc_main+0xc39>
    35fd:	8d 76 00             	lea    0x0(%esi),%esi
		rrc_messege_handler_upper(pkptr);
    3600:	e8 6b ea ff ff       	call   2070 <rrc_messege_handler_upper>
    3605:	e9 32 f4 ff ff       	jmp    2a3c <rrc_main+0x7c>
    360a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_rlc(pkptr);
	}
	else if(EVT_RRC_PK_FROM_UPPER)
	{
		FSM_PKT* pkptr = fsm_pkt_get();
    3610:	e8 fc ff ff ff       	call   3611 <rrc_main+0xc51>
    3615:	8d 76 00             	lea    0x0(%esi),%esi
		rrc_messege_handler_upper(pkptr);
    3618:	e8 53 ea ff ff       	call   2070 <rrc_messege_handler_upper>
    361d:	8d 76 00             	lea    0x0(%esi),%esi
    3620:	e9 70 fa ff ff       	jmp    3095 <rrc_main+0x6d5>
    3625:	8d 76 00             	lea    0x0(%esi),%esi
static void st_idle_connecting_default(void)
{
	FIN(st_idle_connecting_default());
	fsm_printf("[rrc] [fsm] st_idle_connecting_default().\n");

	if(EVT_IOCTL_ARRIVAL)
    3628:	e8 fc ff ff ff       	call   3629 <rrc_main+0xc69>
    362d:	83 f8 02             	cmp    $0x2,%eax
    3630:	0f 85 da f6 ff ff    	jne    2d10 <rrc_main+0x350>
	{
		rrc_ioctl_handler();
    3636:	e8 75 ed ff ff       	call   23b0 <rrc_ioctl_handler>
    363b:	90                   	nop
    363c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    3640:	e9 f0 f6 ff ff       	jmp    2d35 <rrc_main+0x375>
    3645:	8d 76 00             	lea    0x0(%esi),%esi
	{
		rrc_ioctl_handler();
	}
	else if(EVT_RRC_PK_FROM_LOWER)
	{
		FSM_PKT* pkptr = fsm_pkt_get();
    3648:	e8 fc ff ff ff       	call   3649 <rrc_main+0xc89>
    364d:	8d 76 00             	lea    0x0(%esi),%esi
		rrc_messege_handler_rlc(pkptr);
    3650:	e8 8b e6 ff ff       	call   1ce0 <rrc_messege_handler_rlc>
    3655:	e9 81 f7 ff ff       	jmp    2ddb <rrc_main+0x41b>
    365a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	{
		rrc_ioctl_handler();
	}
	else if(EVT_RRC_PK_FROM_LOWER)
	{
		FSM_PKT* pkptr = fsm_pkt_get();
    3660:	e8 fc ff ff ff       	call   3661 <rrc_main+0xca1>
    3665:	8d 76 00             	lea    0x0(%esi),%esi
		rrc_messege_handler_rlc(pkptr);
    3668:	e8 73 e6 ff ff       	call   1ce0 <rrc_messege_handler_rlc>
    366d:	8d 76 00             	lea    0x0(%esi),%esi
    3670:	e9 86 f5 ff ff       	jmp    2bfb <rrc_main+0x23b>
    3675:	8d 76 00             	lea    0x0(%esi),%esi
	}
	else if(EVT_RRC_PK_FROM_UPPER)
	{
		FSM_PKT* pkptr = fsm_pkt_get();
    3678:	e8 fc ff ff ff       	call   3679 <rrc_main+0xcb9>
    367d:	8d 76 00             	lea    0x0(%esi),%esi
		rrc_messege_handler_upper(pkptr);
    3680:	e8 eb e9 ff ff       	call   2070 <rrc_messege_handler_upper>
    3685:	e9 71 f5 ff ff       	jmp    2bfb <rrc_main+0x23b>
    368a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
		FSM_PKT* pkptr = fsm_pkt_get();
		rrc_messege_handler_rlc(pkptr);
	}
	else if(EVT_RRC_PK_FROM_UPPER)
	{
		FSM_PKT* pkptr = fsm_pkt_get();
    3690:	e8 fc ff ff ff       	call   3691 <rrc_main+0xcd1>
    3695:	8d 76 00             	lea    0x0(%esi),%esi
		rrc_messege_handler_upper(pkptr);
    3698:	e8 d3 e9 ff ff       	call   2070 <rrc_messege_handler_upper>
    369d:	8d 76 00             	lea    0x0(%esi),%esi
    36a0:	e9 36 f7 ff ff       	jmp    2ddb <rrc_main+0x41b>
	//used for test
//	rrcConnectionReconfiguration = SetRrcConnReconfigmessage();
//	fsm_printf("[rrc] [fsm] rrcConnectionReconfiguration->rrcTransactionIdentifier=%d\n",rrcConnectionReconfiguration->rrcTransactionIdentifier);
	if(rrcConnectionReconfiguration == NULL)
	{
		fsm_printf("[rrc] invalid rrcConnectionReconfiguration.\n");
    36a5:	c7 04 24 68 0c 00 00 	movl   $0xc68,(%esp)
    36ac:	e8 fc ff ff ff       	call   36ad <rrc_main+0xced>
    36b1:	e9 25 f7 ff ff       	jmp    2ddb <rrc_main+0x41b>
	{
		rrc_ioctl_handler();
	}
	else if(EVT_RRC_PK_FROM_LOWER)
	{
		FSM_PKT* pkptr = fsm_pkt_get();
    36b6:	e8 fc ff ff ff       	call   36b7 <rrc_main+0xcf7>
    36bb:	90                   	nop
    36bc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
		rrc_messege_handler_rlc(pkptr);
    36c0:	e8 1b e6 ff ff       	call   1ce0 <rrc_messege_handler_rlc>
    36c5:	e9 6b f6 ff ff       	jmp    2d35 <rrc_main+0x375>
    36ca:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	}
	else if(EVT_RRC_PK_FROM_UPPER)
	{
		FSM_PKT* pkptr = fsm_pkt_get();
    36d0:	e8 fc ff ff ff       	call   36d1 <rrc_main+0xd11>
    36d5:	8d 76 00             	lea    0x0(%esi),%esi
		rrc_messege_handler_upper(pkptr);
    36d8:	e8 93 e9 ff ff       	call   2070 <rrc_messege_handler_upper>
    36dd:	8d 76 00             	lea    0x0(%esi),%esi
    36e0:	e9 50 f6 ff ff       	jmp    2d35 <rrc_main+0x375>
			FSM_TEST_COND(Evt_RcvRRCConnReestablish)
			FSM_TEST_COND(Evt_RcvRRCConnReestablishReject)
			FSM_TEST_COND(Evt_TimeOut_T301)
			FSM_TEST_COND(Evt_TimeOut_T311)
			FSM_COND_TEST_OUT("ST_CONNECTED_REESTABLISH")
			FSM_TRANSIT_SWITCH
    36e5:	85 ff                	test   %edi,%edi
    36e7:	0f 84 0e f5 ff ff    	je     2bfb <rrc_main+0x23b>
    36ed:	8d 76 00             	lea    0x0(%esi),%esi
    36f0:	e9 a6 f7 ff ff       	jmp    2e9b <rrc_main+0x4db>
    36f5:	90                   	nop
    36f6:	90                   	nop
    36f7:	90                   	nop
    36f8:	90                   	nop
    36f9:	90                   	nop
    36fa:	90                   	nop
    36fb:	90                   	nop
    36fc:	90                   	nop
    36fd:	90                   	nop
    36fe:	90                   	nop
    36ff:	90                   	nop

00003700 <send_to_user>:
/*---------------------------------- netlinlk -----------------------------------------*/
#define NETLINK_TEST 21
//u32 pid;    //process of user space
//static struct sock *netlinkfd = NULL;

void send_to_user(char *info, int size_info){
    3700:	55                   	push   %ebp
    3701:	89 e5                	mov    %esp,%ebp
    3703:	e8 fc ff ff ff       	call   3704 <send_to_user+0x4>
	//     //发送数据
	// retval = netlink_unicast(netlinkfd, skb, pid, MSG_DONTWAIT);
	//fsm_printf("[kernel space] netlink_unicast return: %d\n", retval);


}
    3708:	5d                   	pop    %ebp
    3709:	c3                   	ret    
    370a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00003710 <rcv_msg_from_us>:

void rcv_msg_from_us(struct sk_buff *__skb){
    3710:	55                   	push   %ebp
    3711:	89 e5                	mov    %esp,%ebp
    3713:	e8 fc ff ff ff       	call   3714 <rcv_msg_from_us+0x4>
	//         send_to_user(data, strlen(data)+1);
	//     }
	// }else{
	//     //fsm_printf("[kernel space] data receive from user are:%s\n",(char *)NLMSG_DATA(nlmsg_hdr(__skb)));
	// }
}
    3718:	5d                   	pop    %ebp
    3719:	c3                   	ret    
    371a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00003720 <__fsm_dev_set_config>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int __fsm_dev_set_config(struct net_device *dev, struct ifmap *p_ifmap)
{
    3720:	55                   	push   %ebp
    3721:	89 e5                	mov    %esp,%ebp
    3723:	e8 fc ff ff ff       	call   3724 <__fsm_dev_set_config+0x4>
	return 0;
}
    3728:	31 c0                	xor    %eax,%eax
    372a:	5d                   	pop    %ebp
    372b:	c3                   	ret    
    372c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00003730 <__fsm_dev_get_stats>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
struct net_device_stats* __fsm_dev_get_stats(struct net_device *dev)
{
    3730:	55                   	push   %ebp
    3731:	89 e5                	mov    %esp,%ebp
    3733:	e8 fc ff ff ff       	call   3734 <__fsm_dev_get_stats+0x4>
	fsm_priv* priv;
	priv = (fsm_priv*)netdev_priv(dev);
	return &(priv->stats);            
}
    3738:	5d                   	pop    %ebp
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
struct net_device_stats* __fsm_dev_get_stats(struct net_device *dev)
{
    3739:	05 a0 03 00 00       	add    $0x3a0,%eax
	fsm_priv* priv;
	priv = (fsm_priv*)netdev_priv(dev);
	return &(priv->stats);            
}
    373e:	c3                   	ret    
    373f:	90                   	nop

00003740 <__fsm_dev_tx_timeout>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void __fsm_dev_tx_timeout(struct net_device *dev)
{  
    3740:	55                   	push   %ebp
    3741:	89 e5                	mov    %esp,%ebp
    3743:	e8 fc ff ff ff       	call   3744 <__fsm_dev_tx_timeout+0x4>
	return;   
}
    3748:	5d                   	pop    %ebp
    3749:	c3                   	ret    
    374a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00003750 <__fsm_dev_ioctl>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int __fsm_dev_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
    3750:	55                   	push   %ebp
    3751:	89 e5                	mov    %esp,%ebp
    3753:	e8 fc ff ff ff       	call   3754 <__fsm_dev_ioctl+0x4>
    3758:	89 d0                	mov    %edx,%eax
    375a:	89 ca                	mov    %ecx,%edx
	fsm_ioctrl_arrival(ifr,cmd);
    375c:	e8 fc ff ff ff       	call   375d <__fsm_dev_ioctl+0xd>
	return 0;
}
    3761:	31 c0                	xor    %eax,%eax
    3763:	5d                   	pop    %ebp
    3764:	c3                   	ret    
    3765:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    3769:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00003770 <__fsm_dev_tx>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int __fsm_dev_tx(struct sk_buff *skb, struct net_device *dev)
{ 
    3770:	55                   	push   %ebp
    3771:	89 e5                	mov    %esp,%ebp
    3773:	e8 fc ff ff ff       	call   3774 <__fsm_dev_tx+0x4>
	fsm_core_pkt_drive(skb, RXTX_PKT_REQ);	
    3778:	31 d2                	xor    %edx,%edx
    377a:	e8 fc ff ff ff       	call   377b <__fsm_dev_tx+0xb>
	return 0;    
}	
    377f:	31 c0                	xor    %eax,%eax
    3781:	5d                   	pop    %ebp
    3782:	c3                   	ret    
    3783:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    3789:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00003790 <__fsm_dev_recv>:
 **-------------------------------------- ------system--------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int __fsm_dev_recv(struct sk_buff *skb ,struct net_device *dev1, struct packet_type *pktype, struct net_device *dev2)
{  
    3790:	55                   	push   %ebp
    3791:	89 e5                	mov    %esp,%ebp
    3793:	e8 fc ff ff ff       	call   3794 <__fsm_dev_recv+0x4>
	fsm_core_pkt_drive(skb, RXTX_PKT_IND);
    3798:	ba 01 00 00 00       	mov    $0x1,%edx
    379d:	e8 fc ff ff ff       	call   379e <__fsm_dev_recv+0xe>
	return 0;            
}
    37a2:	31 c0                	xor    %eax,%eax
    37a4:	5d                   	pop    %ebp
    37a5:	c3                   	ret    
    37a6:	8d 76 00             	lea    0x0(%esi),%esi
    37a9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

000037b0 <__fsm_dev_stop>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int __fsm_dev_stop(struct net_device *dev)
{  
    37b0:	55                   	push   %ebp
    37b1:	89 e5                	mov    %esp,%ebp
    37b3:	53                   	push   %ebx
    37b4:	e8 fc ff ff ff       	call   37b5 <__fsm_dev_stop+0x5>
    37b9:	89 c3                	mov    %eax,%ebx

	/*-----------------now we need to register the special protocol_type */
	fsm_core_close();
    37bb:	e8 fc ff ff ff       	call   37bc <__fsm_dev_stop+0xc>
	dev_remove_pack(&pk_t);
    37c0:	b8 00 00 00 00       	mov    $0x0,%eax
    37c5:	e8 fc ff ff ff       	call   37c6 <__fsm_dev_stop+0x16>
static __always_inline void
set_bit(unsigned int nr, volatile unsigned long *addr)
{
	if (IS_IMMEDIATE(nr)) {
		asm volatile(LOCK_PREFIX "orb %1,%0"
			: CONST_MASK_ADDR(nr, addr)
    37ca:	8b 83 c0 01 00 00    	mov    0x1c0(%ebx),%eax
 */
static __always_inline void
set_bit(unsigned int nr, volatile unsigned long *addr)
{
	if (IS_IMMEDIATE(nr)) {
		asm volatile(LOCK_PREFIX "orb %1,%0"
    37d0:	f0 80 48 08 01       	lock orb $0x1,0x8(%eax)
	netif_stop_queue(dev);
	return 0;    
}
    37d5:	31 c0                	xor    %eax,%eax
    37d7:	5b                   	pop    %ebx
    37d8:	5d                   	pop    %ebp
    37d9:	c3                   	ret    
    37da:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

000037e0 <__fsm_dev_open>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int __fsm_dev_open(struct net_device *dev)
{
    37e0:	55                   	push   %ebp
    37e1:	89 e5                	mov    %esp,%ebp
    37e3:	53                   	push   %ebx
    37e4:	83 ec 04             	sub    $0x4,%esp
    37e7:	e8 fc ff ff ff       	call   37e8 <__fsm_dev_open+0x8>
	/*-----------------now we need to register the special protocol_type */	
	//mdelay(3000);

	//	fsm_core_intf_set(STRM_TO_IP, DEV_INTF_IND, DEV_PROTO_IP, NULL);	
	fsm_core_intf_set(STRM_TO_PDCP, DEV_INTF_REQ, DEV_PROTO_RRC, "LTE_PDCP0");
    37ec:	b9 f8 f4 00 00       	mov    $0xf4f8,%ecx
    37f1:	ba 01 00 00 00       	mov    $0x1,%edx
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int __fsm_dev_open(struct net_device *dev)
{
    37f6:	89 c3                	mov    %eax,%ebx
	/*-----------------now we need to register the special protocol_type */	
	//mdelay(3000);

	//	fsm_core_intf_set(STRM_TO_IP, DEV_INTF_IND, DEV_PROTO_IP, NULL);	
	fsm_core_intf_set(STRM_TO_PDCP, DEV_INTF_REQ, DEV_PROTO_RRC, "LTE_PDCP0");
    37f8:	b8 06 00 00 00       	mov    $0x6,%eax
    37fd:	c7 04 24 77 02 00 00 	movl   $0x277,(%esp)
    3804:	e8 fc ff ff ff       	call   3805 <__fsm_dev_open+0x25>
	fsm_core_intf_set(STRM_TO_RLC, DEV_INTF_REQ, DEV_PROTO_RRC, "LTE_RLC0");
    3809:	b9 f8 f4 00 00       	mov    $0xf4f8,%ecx
    380e:	ba 01 00 00 00       	mov    $0x1,%edx
    3813:	b8 01 00 00 00       	mov    $0x1,%eax
    3818:	c7 04 24 81 02 00 00 	movl   $0x281,(%esp)
    381f:	e8 fc ff ff ff       	call   3820 <__fsm_dev_open+0x40>
	fsm_core_intf_set(STRM_TO_MAC, DEV_INTF_REQ, DEV_PROTO_RRC, "LTE_MAC0");
    3824:	b9 f8 f4 00 00       	mov    $0xf4f8,%ecx
    3829:	ba 01 00 00 00       	mov    $0x1,%edx
    382e:	b8 02 00 00 00       	mov    $0x2,%eax
    3833:	c7 04 24 8a 02 00 00 	movl   $0x28a,(%esp)
    383a:	e8 fc ff ff ff       	call   383b <__fsm_dev_open+0x5b>

	dev_add_pack(&pk_t); 
    383f:	b8 00 00 00 00       	mov    $0x0,%eax
    3844:	e8 fc ff ff ff       	call   3845 <__fsm_dev_open+0x65>
static __always_inline void
clear_bit(int nr, volatile unsigned long *addr)
{
	if (IS_IMMEDIATE(nr)) {
		asm volatile(LOCK_PREFIX "andb %1,%0"
			: CONST_MASK_ADDR(nr, addr)
    3849:	8b 83 c0 01 00 00    	mov    0x1c0(%ebx),%eax
 */
static __always_inline void
clear_bit(int nr, volatile unsigned long *addr)
{
	if (IS_IMMEDIATE(nr)) {
		asm volatile(LOCK_PREFIX "andb %1,%0"
    384f:	f0 80 60 08 fe       	lock andb $0xfe,0x8(%eax)
	netif_start_queue(dev);  
	fsm_core_open();	 
    3854:	e8 fc ff ff ff       	call   3855 <__fsm_dev_open+0x75>
	return 0;    
}
    3859:	31 c0                	xor    %eax,%eax
    385b:	83 c4 04             	add    $0x4,%esp
    385e:	5b                   	pop    %ebx
    385f:	5d                   	pop    %ebp
    3860:	c3                   	ret    
    3861:	eb 0d                	jmp    3870 <__fsm_dev_destroy>
    3863:	90                   	nop
    3864:	90                   	nop
    3865:	90                   	nop
    3866:	90                   	nop
    3867:	90                   	nop
    3868:	90                   	nop
    3869:	90                   	nop
    386a:	90                   	nop
    386b:	90                   	nop
    386c:	90                   	nop
    386d:	90                   	nop
    386e:	90                   	nop
    386f:	90                   	nop

00003870 <__fsm_dev_destroy>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void __fsm_dev_destroy(void)
{
    3870:	55                   	push   %ebp
    3871:	89 e5                	mov    %esp,%ebp
    3873:	53                   	push   %ebx
    3874:	e8 fc ff ff ff       	call   3875 <__fsm_dev_destroy+0x5>
	//	//	sock_release(netlinkfd->sk_socket);
	//	}

	NETDEV* dev;
	fsm_priv* priv;
	dev = (NETDEV*)fsm_dev_get();
    3879:	e8 fc ff ff ff       	call   387a <__fsm_dev_destroy+0xa>
    387e:	89 c3                	mov    %eax,%ebx
	fsm_core_destroy();
    3880:	e8 fc ff ff ff       	call   3881 <__fsm_dev_destroy+0x11>
	priv = netdev_priv(dev);
	fsm_mem_free(priv->sv_ptr);
    3885:	8b 83 fc 03 00 00    	mov    0x3fc(%ebx),%eax
    388b:	e8 fc ff ff ff       	call   388c <__fsm_dev_destroy+0x1c>
	unregister_netdev(dev);
    3890:	89 d8                	mov    %ebx,%eax
    3892:	e8 fc ff ff ff       	call   3893 <__fsm_dev_destroy+0x23>
	free_netdev(dev);
    3897:	89 d8                	mov    %ebx,%eax
    3899:	e8 fc ff ff ff       	call   389a <__fsm_dev_destroy+0x2a>
}   
    389e:	5b                   	pop    %ebx
    389f:	5d                   	pop    %ebp
    38a0:	c3                   	ret    
    38a1:	eb 0d                	jmp    38b0 <__fsm_dev_create>
    38a3:	90                   	nop
    38a4:	90                   	nop
    38a5:	90                   	nop
    38a6:	90                   	nop
    38a7:	90                   	nop
    38a8:	90                   	nop
    38a9:	90                   	nop
    38aa:	90                   	nop
    38ab:	90                   	nop
    38ac:	90                   	nop
    38ad:	90                   	nop
    38ae:	90                   	nop
    38af:	90                   	nop

000038b0 <__fsm_dev_create>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
int __fsm_dev_create(void)
{   
    38b0:	55                   	push   %ebp
    38b1:	89 e5                	mov    %esp,%ebp
    38b3:	53                   	push   %ebx
    38b4:	83 ec 0c             	sub    $0xc,%esp
    38b7:	e8 fc ff ff ff       	call   38b8 <__fsm_dev_create+0x8>

	fsm_priv *priv;
	const char  *name = "LTE_RRC%d";
	char dev_addr[6] = RRC_ADDR;
	NETDEV *dev = NULL;
	dev = alloc_netdev(sizeof(fsm_priv), name, dev_init);
    38bc:	b9 00 00 00 00       	mov    $0x0,%ecx
    38c1:	ba 93 02 00 00       	mov    $0x293,%edx
    38c6:	b8 60 00 00 00       	mov    $0x60,%eax
{   
	//printk(KERN_EMERG"rrc device creating.\n");

	fsm_priv *priv;
	const char  *name = "LTE_RRC%d";
	char dev_addr[6] = RRC_ADDR;
    38cb:	c6 45 f6 00          	movb   $0x0,-0xa(%ebp)
    38cf:	c6 45 f7 11          	movb   $0x11,-0x9(%ebp)
    38d3:	c6 45 f8 1a          	movb   $0x1a,-0x8(%ebp)
    38d7:	c6 45 f9 1a          	movb   $0x1a,-0x7(%ebp)
    38db:	c6 45 fa 8a          	movb   $0x8a,-0x6(%ebp)
    38df:	c6 45 fb 42          	movb   $0x42,-0x5(%ebp)
	NETDEV *dev = NULL;
	dev = alloc_netdev(sizeof(fsm_priv), name, dev_init);
    38e3:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
    38ea:	e8 fc ff ff ff       	call   38eb <__fsm_dev_create+0x3b>
	if (dev == NULL)   /* allocation error */
    38ef:	85 c0                	test   %eax,%eax

	fsm_priv *priv;
	const char  *name = "LTE_RRC%d";
	char dev_addr[6] = RRC_ADDR;
	NETDEV *dev = NULL;
	dev = alloc_netdev(sizeof(fsm_priv), name, dev_init);
    38f1:	89 c3                	mov    %eax,%ebx
	if (dev == NULL)   /* allocation error */
    38f3:	75 0b                	jne    3900 <__fsm_dev_create+0x50>
	/* register the net device */    
	if (register_netdev(dev))    /* register error */
	{
		free_netdev(dev);   /* release the struct net_device */
		dev = NULL;               
		return -1;
    38f5:	b8 fe ff ff ff       	mov    $0xfffffffe,%eax
	//        printk(KERN_ERR "can not create a netlink socket\n");
	//        return -1;
	//    }

	return 0;       
}
    38fa:	83 c4 0c             	add    $0xc,%esp
    38fd:	5b                   	pop    %ebx
    38fe:	5d                   	pop    %ebp
    38ff:	c3                   	ret    
	case 5:
		*(int *)to = *(int *)from;
		*((char *)to + 4) = *((char *)from + 4);
		return to;
	case 6:
		*(int *)to = *(int *)from;
    3900:	8b 55 f6             	mov    -0xa(%ebp),%edx
	}

	memcpy(dev->dev_addr, &dev_addr, 6);       
	/* ---------ADD some private data into the net_device struct */
	priv = netdev_priv(dev);
	if (priv == NULL)
    3903:	81 fb 60 fc ff ff    	cmp    $0xfffffc60,%ebx
	if (dev == NULL)   /* allocation error */
	{
		return -2;
	}

	memcpy(dev->dev_addr, &dev_addr, 6);       
    3909:	8b 80 48 01 00 00    	mov    0x148(%eax),%eax
    390f:	89 10                	mov    %edx,(%eax)
		*((short *)to + 2) = *((short *)from + 2);
    3911:	0f b7 55 fa          	movzwl -0x6(%ebp),%edx
    3915:	66 89 50 04          	mov    %dx,0x4(%eax)
	/* ---------ADD some private data into the net_device struct */
	priv = netdev_priv(dev);
	if (priv == NULL)
    3919:	74 da                	je     38f5 <__fsm_dev_create+0x45>
	{                
		return -2;                   
	}

	/* register the net device */    
	if (register_netdev(dev))    /* register error */
    391b:	89 d8                	mov    %ebx,%eax
    391d:	e8 fc ff ff ff       	call   391e <__fsm_dev_create+0x6e>
    3922:	85 c0                	test   %eax,%eax
    3924:	74 d4                	je     38fa <__fsm_dev_create+0x4a>
	{
		free_netdev(dev);   /* release the struct net_device */
    3926:	89 d8                	mov    %ebx,%eax
    3928:	e8 fc ff ff ff       	call   3929 <__fsm_dev_create+0x79>
    392d:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
		dev = NULL;               
		return -1;
    3932:	eb c6                	jmp    38fa <__fsm_dev_create+0x4a>
    3934:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    393a:	8d bf 00 00 00 00    	lea    0x0(%edi),%edi

00003940 <dev_init>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void dev_init(struct net_device *dev)
{
    3940:	55                   	push   %ebp
    3941:	89 e5                	mov    %esp,%ebp
    3943:	56                   	push   %esi
    3944:	53                   	push   %ebx
    3945:	83 ec 08             	sub    $0x8,%esp
    3948:	e8 fc ff ff ff       	call   3949 <dev_init+0x9>
	fsm_priv* priv;
	int fsm_id;
	ASSERT(dev);
    394d:	85 c0                	test   %eax,%eax
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void dev_init(struct net_device *dev)
{
    394f:	89 c3                	mov    %eax,%ebx
	fsm_priv* priv;
	int fsm_id;
	ASSERT(dev);
    3951:	0f 84 9e 00 00 00    	je     39f5 <dev_init+0xb5>
	dev->netdev_ops = &fsm_netdev_ops;
	dev->watchdog_timeo = 1000;  				/* the time unit is jiffy */
	dev->flags = IFF_BROADCAST | IFF_MULTICAST | IFF_NOARP;
	//dev->features |= NETIF_F_NO_CSUM;

	priv = (fsm_priv*)netdev_priv(dev);
    3957:	8d b0 a0 03 00 00    	lea    0x3a0(%eax),%esi
	fsm_mem_set(priv,0,sizeof(fsm_priv));
    395d:	b9 60 00 00 00       	mov    $0x60,%ecx
    3962:	31 d2                	xor    %edx,%edx
void dev_init(struct net_device *dev)
{
	fsm_priv* priv;
	int fsm_id;
	ASSERT(dev);
	dev->tx_queue_len = 128;   	/* the queue length */   
    3964:	c7 80 d0 01 00 00 80 	movl   $0x80,0x1d0(%eax)
    396b:	00 00 00 
	dev->mtu = MTU;		/* now we do not fragmentate the packet */
    396e:	c7 80 cc 00 00 00 ff 	movl   $0xffff,0xcc(%eax)
    3975:	ff 00 00 
	dev->header_ops = NULL;   	/* cancle eth_header function for not building ethnet mac header */ 
    3978:	c7 80 bc 00 00 00 00 	movl   $0x0,0xbc(%eax)
    397f:	00 00 00 
	dev->addr_len = 0;
    3982:	c6 80 fc 00 00 00 00 	movb   $0x0,0xfc(%eax)
	dev->hard_header_len = 0;
    3989:	66 c7 80 d2 00 00 00 	movw   $0x0,0xd2(%eax)
    3990:	00 00 
	dev->netdev_ops = &fsm_netdev_ops;
    3992:	c7 80 b4 00 00 00 00 	movl   $0x200,0xb4(%eax)
    3999:	02 00 00 
	dev->watchdog_timeo = 1000;  				/* the time unit is jiffy */
    399c:	c7 80 dc 01 00 00 e8 	movl   $0x3e8,0x1dc(%eax)
    39a3:	03 00 00 
	dev->flags = IFF_BROADCAST | IFF_MULTICAST | IFF_NOARP;
    39a6:	c7 80 c0 00 00 00 82 	movl   $0x1082,0xc0(%eax)
    39ad:	10 00 00 
	//dev->features |= NETIF_F_NO_CSUM;

	priv = (fsm_priv*)netdev_priv(dev);
	fsm_mem_set(priv,0,sizeof(fsm_priv));
    39b0:	89 f0                	mov    %esi,%eax
    39b2:	e8 fc ff ff ff       	call   39b3 <dev_init+0x73>
	fsm_core_create(dev);
    39b7:	89 d8                	mov    %ebx,%eax
    39b9:	e8 fc ff ff ff       	call   39ba <dev_init+0x7a>

	priv->sv_ptr = fsm_mem_alloc(sizeof(SV_TYPE_NAME));
    39be:	b8 04 00 00 00       	mov    $0x4,%eax
    39c3:	e8 fc ff ff ff       	call   39c4 <dev_init+0x84>
	fsm_mem_set(priv->sv_ptr, 0, sizeof(SV_TYPE_NAME));
    39c8:	b9 04 00 00 00       	mov    $0x4,%ecx
    39cd:	31 d2                	xor    %edx,%edx

	priv = (fsm_priv*)netdev_priv(dev);
	fsm_mem_set(priv,0,sizeof(fsm_priv));
	fsm_core_create(dev);

	priv->sv_ptr = fsm_mem_alloc(sizeof(SV_TYPE_NAME));
    39cf:	89 46 5c             	mov    %eax,0x5c(%esi)
	fsm_mem_set(priv->sv_ptr, 0, sizeof(SV_TYPE_NAME));
    39d2:	e8 fc ff ff ff       	call   39d3 <dev_init+0x93>
	/*-----------------------------------FSM creation---------------------------*/
	fsm_id = fsm_create_register("lte_rrc_fsm", rrc_main, priv->sv_ptr);
    39d7:	8b 4e 5c             	mov    0x5c(%esi),%ecx
    39da:	ba 00 00 00 00       	mov    $0x0,%edx
    39df:	b8 9d 02 00 00       	mov    $0x29d,%eax
    39e4:	e8 fc ff ff ff       	call   39e5 <dev_init+0xa5>
	fsm_mainport_bind(fsm_id);
    39e9:	e8 fc ff ff ff       	call   39ea <dev_init+0xaa>
	/*--------------------------------------------------------------------------*/

	return;
}
    39ee:	83 c4 08             	add    $0x8,%esp
    39f1:	5b                   	pop    %ebx
    39f2:	5e                   	pop    %esi
    39f3:	5d                   	pop    %ebp
    39f4:	c3                   	ret    
 ******************************************************************************/
void dev_init(struct net_device *dev)
{
	fsm_priv* priv;
	int fsm_id;
	ASSERT(dev);
    39f5:	c7 44 24 04 64 02 00 	movl   $0x264,0x4(%esp)
    39fc:	00 
    39fd:	c7 04 24 30 0f 00 00 	movl   $0xf30,(%esp)
    3a04:	e8 fc ff ff ff       	call   3a05 <dev_init+0xc5>
    3a09:	e8 fc ff ff ff       	call   3a0a <dev_init+0xca>
    3a0e:	eb de                	jmp    39ee <dev_init+0xae>

00003a10 <send_RRCConnectionSetupComplete>:
**-----------------------------------
**Modified by: Xu Shangfei
**Modified date:2014.10.9
****************************************************************/
void send_RRCConnectionSetupComplete(struct UL_DCCH_Message *ul_dcchmsg)
{
    3a10:	55                   	push   %ebp
    3a11:	89 e5                	mov    %esp,%ebp
    3a13:	83 ec 04             	sub    $0x4,%esp
    3a16:	e8 fc ff ff ff       	call   3a17 <send_RRCConnectionSetupComplete+0x7>
	FIN(send_RRCConnectionSetupComplete());
	char *msg = (char*)&(*ul_dcchmsg);
	u32 msg_len = sizeof(ul_dcchmsg);
	u32 message_type = 6;
	packet_send_to_pdcp(msg, msg_len, message_type);
    3a1b:	b9 06 00 00 00       	mov    $0x6,%ecx
    3a20:	ba 04 00 00 00       	mov    $0x4,%edx
    3a25:	e8 fc ff ff ff       	call   3a26 <send_RRCConnectionSetupComplete+0x16>
	fsm_printf("[rrc] [conn_establish] send_RRCConnectionSetupComplete process is done successfully.========\n");
    3a2a:	c7 04 24 58 0f 00 00 	movl   $0xf58,(%esp)
    3a31:	e8 fc ff ff ff       	call   3a32 <send_RRCConnectionSetupComplete+0x22>
	FOUT;
}
    3a36:	c9                   	leave  
    3a37:	c3                   	ret    
    3a38:	90                   	nop
    3a39:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00003a40 <set_physicalConfigDedicated>:
**Modified by: Xu Shangfei
**Modified date:2014.10.9
****************************************************************/
void  set_physicalConfigDedicated(struct RRCConnectionSetup *rrcConnectionSetupmPHYmsg)

{
    3a40:	55                   	push   %ebp
    3a41:	89 e5                	mov    %esp,%ebp
    3a43:	83 ec 04             	sub    $0x4,%esp
    3a46:	e8 fc ff ff ff       	call   3a47 <set_physicalConfigDedicated+0x7>
	FIN(set_physicalConfigDedicated())
		if(rrcConnectionSetupmPHYmsg->radioResourceConfigDedicated.havePhysicalConfigDedicated)
    3a4b:	80 b8 14 04 00 00 00 	cmpb   $0x0,0x414(%eax)
    3a52:	75 04                	jne    3a58 <set_physicalConfigDedicated+0x18>
		    //fix me :PHY IOCTL is wating
			//fsm_do_ioctrl(STRM_TO_PHY, IOCCMD_RRCTOPHY_CONFIG_CHANNEL , (void*)&(rrcConnectionSetupmPHYmsg->radioResourceConfigDedicated.physicalConfigDedicated), sizeof(struct PhysicalConfigDedicated ));
			fsm_printf("[rrc] [conn_establish] set_physicalConfigDedicated process is done successfully.BUT the TOCTL is waiting to send==========\n");
		}
	FOUT;
}
    3a54:	c9                   	leave  
    3a55:	c3                   	ret    
    3a56:	66 90                	xchg   %ax,%ax
	FIN(set_physicalConfigDedicated())
		if(rrcConnectionSetupmPHYmsg->radioResourceConfigDedicated.havePhysicalConfigDedicated)
		{
		    //fix me :PHY IOCTL is wating
			//fsm_do_ioctrl(STRM_TO_PHY, IOCCMD_RRCTOPHY_CONFIG_CHANNEL , (void*)&(rrcConnectionSetupmPHYmsg->radioResourceConfigDedicated.physicalConfigDedicated), sizeof(struct PhysicalConfigDedicated ));
			fsm_printf("[rrc] [conn_establish] set_physicalConfigDedicated process is done successfully.BUT the TOCTL is waiting to send==========\n");
    3a58:	c7 04 24 b8 0f 00 00 	movl   $0xfb8,(%esp)
    3a5f:	e8 fc ff ff ff       	call   3a60 <set_physicalConfigDedicated+0x20>
		}
	FOUT;
}
    3a64:	c9                   	leave  
    3a65:	c3                   	ret    
    3a66:	8d 76 00             	lea    0x0(%esi),%esi
    3a69:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00003a70 <set_default_physical_channel>:
**-----------------------------------
**Modified by: Xu Shangfei
**Modified date:2014.10.9
****************************************************************/
void set_default_physical_channel(struct PhysicalConfigDedicated phydefaultmsg)
{
    3a70:	55                   	push   %ebp
    3a71:	89 e5                	mov    %esp,%ebp
    3a73:	83 ec 04             	sub    $0x4,%esp
    3a76:	e8 fc ff ff ff       	call   3a77 <set_default_physical_channel+0x7>
	FIN(set_default_physical_channel());
	// fsm_do_ioctrl(STRM_TO_PHY, IOCCMD_RRCTOPHY_CONFIG_CHANNEL, (void*)(&phydefaultmsg), sizeof(struct PhysicalConfigDedicated));
	fsm_printf("[rrc] [conn_establish] IOCLT of physical layer undefined. Waitting for the follow-up supplement!========\n");
    3a7b:	c7 04 24 34 10 00 00 	movl   $0x1034,(%esp)
    3a82:	e8 fc ff ff ff       	call   3a83 <set_default_physical_channel+0x13>
	FOUT;

}
    3a87:	c9                   	leave  
    3a88:	c3                   	ret    
    3a89:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00003a90 <set_semi_persistent>:
**-----------------------------------
**Modified by: Xu Shangfei
**Modified date:2014.10.9
****************************************************************/
void set_semi_persistent(struct RRCConnectionSetup *rrcConnectionSetupmSPSmsg)
{
    3a90:	55                   	push   %ebp
    3a91:	89 e5                	mov    %esp,%ebp
    3a93:	83 ec 04             	sub    $0x4,%esp
    3a96:	e8 fc ff ff ff       	call   3a97 <set_semi_persistent+0x7>
	FIN(set_semi_persistent());
	if(rrcConnectionSetupmSPSmsg->radioResourceConfigDedicated.haveSPS_Config)
    3a9b:	80 b8 cc 03 00 00 00 	cmpb   $0x0,0x3cc(%eax)
    3aa2:	75 04                	jne    3aa8 <set_semi_persistent+0x18>
		fsm_do_ioctrl(STRM_TO_MAC, IOCCMD_RRCTOMAC_CONFIG_SPS , (void*)&(rrcConnectionSetupmSPSmsg->radioResourceConfigDedicated.sps_Config), sizeof(struct SPS_Config));
		fsm_printf("[rrc] [conn_establish] set_semi-persistent process is done successfully.========\n");
	}
	FOUT;

}
    3aa4:	c9                   	leave  
    3aa5:	c3                   	ret    
    3aa6:	66 90                	xchg   %ax,%ax
{
	FIN(set_semi_persistent());
	if(rrcConnectionSetupmSPSmsg->radioResourceConfigDedicated.haveSPS_Config)
	{
		//ues IOCTL to send SPS_config
		fsm_do_ioctrl(STRM_TO_MAC, IOCCMD_RRCTOMAC_CONFIG_SPS , (void*)&(rrcConnectionSetupmSPSmsg->radioResourceConfigDedicated.sps_Config), sizeof(struct SPS_Config));
    3aa8:	8d 88 d0 03 00 00    	lea    0x3d0(%eax),%ecx
    3aae:	ba 10 00 00 00       	mov    $0x10,%edx
    3ab3:	c7 04 24 44 00 00 00 	movl   $0x44,(%esp)
    3aba:	b8 02 00 00 00       	mov    $0x2,%eax
    3abf:	e8 fc ff ff ff       	call   3ac0 <set_semi_persistent+0x30>
		fsm_printf("[rrc] [conn_establish] set_semi-persistent process is done successfully.========\n");
    3ac4:	c7 04 24 a0 10 00 00 	movl   $0x10a0,(%esp)
    3acb:	e8 fc ff ff ff       	call   3acc <set_semi_persistent+0x3c>
	}
	FOUT;

}
    3ad0:	c9                   	leave  
    3ad1:	c3                   	ret    
    3ad2:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    3ad9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00003ae0 <set_MAC_mainconfig>:
**-----------------------------------
**Modified by: Xu Shangfei
**Modified date:2014.10.9
****************************************************************/
void set_MAC_mainconfig(struct RRCConnectionSetup *rrcConnectionSetupmMACmsg)
{
    3ae0:	55                   	push   %ebp
    3ae1:	89 e5                	mov    %esp,%ebp
    3ae3:	83 ec 04             	sub    $0x4,%esp
    3ae6:	e8 fc ff ff ff       	call   3ae7 <set_MAC_mainconfig+0x7>
	FIN(set_MAC_mainconfig());
	if(rrcConnectionSetupmMACmsg->radioResourceConfigDedicated.haveMAC_MainConfig)
    3aeb:	80 b8 78 03 00 00 00 	cmpb   $0x0,0x378(%eax)
    3af2:	75 04                	jne    3af8 <set_MAC_mainconfig+0x18>
		//ues IOCTLsend message betwween layers
		fsm_do_ioctrl(STRM_TO_MAC, IOCCMD_RRCTOMAC_CONFIG_MAC_MAIN , (void*)&(rrcConnectionSetupmMACmsg->radioResourceConfigDedicated.mac_MainConfig), sizeof(struct MAC_MainConfig));
		fsm_printf("[rrc] [conn_establish] set_MAC-mainconfig process is done successfully.==========\n");
	}
	FOUT;
}
    3af4:	c9                   	leave  
    3af5:	c3                   	ret    
    3af6:	66 90                	xchg   %ax,%ax
{
	FIN(set_MAC_mainconfig());
	if(rrcConnectionSetupmMACmsg->radioResourceConfigDedicated.haveMAC_MainConfig)
	{
		//ues IOCTLsend message betwween layers
		fsm_do_ioctrl(STRM_TO_MAC, IOCCMD_RRCTOMAC_CONFIG_MAC_MAIN , (void*)&(rrcConnectionSetupmMACmsg->radioResourceConfigDedicated.mac_MainConfig), sizeof(struct MAC_MainConfig));
    3af8:	8d 88 7c 03 00 00    	lea    0x37c(%eax),%ecx
    3afe:	ba 09 00 00 00       	mov    $0x9,%edx
    3b03:	c7 04 24 50 00 00 00 	movl   $0x50,(%esp)
    3b0a:	b8 02 00 00 00       	mov    $0x2,%eax
    3b0f:	e8 fc ff ff ff       	call   3b10 <set_MAC_mainconfig+0x30>
		fsm_printf("[rrc] [conn_establish] set_MAC-mainconfig process is done successfully.==========\n");
    3b14:	c7 04 24 f4 10 00 00 	movl   $0x10f4,(%esp)
    3b1b:	e8 fc ff ff ff       	call   3b1c <set_MAC_mainconfig+0x3c>
	}
	FOUT;
}
    3b20:	c9                   	leave  
    3b21:	c3                   	ret    
    3b22:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    3b29:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00003b30 <set_timeAlignmentTimerCommon>:
**-----------------------------------
**Modified by: Xu Shangfei
**Modified date:2014.10.9
****************************************************************/
void set_timeAlignmentTimerCommon (struct SystemInformationBlockType2 *sys2infoAlignmenttimer)
{
    3b30:	55                   	push   %ebp
    3b31:	89 e5                	mov    %esp,%ebp
    3b33:	83 ec 04             	sub    $0x4,%esp
    3b36:	e8 fc ff ff ff       	call   3b37 <set_timeAlignmentTimerCommon+0x7>
	FIN(set_timeAlignmentTimerCommon());
	fsm_do_ioctrl(STRM_TO_MAC, IOCCMD_RRCTOMAC_CONFIG_TAT , (void*)&(sys2infoAlignmenttimer->timeAlignmentTimerCommon), sizeof(struct TimeAlignmentTimer));
    3b3b:	ba 05 00 00 00       	mov    $0x5,%edx
    3b40:	8d 88 04 01 00 00    	lea    0x104(%eax),%ecx
    3b46:	b8 02 00 00 00       	mov    $0x2,%eax
    3b4b:	c7 04 24 04 00 00 00 	movl   $0x4,(%esp)
    3b52:	e8 fc ff ff ff       	call   3b53 <set_timeAlignmentTimerCommon+0x23>

	fsm_printf("[rrc] [conn_establish] set_timeAlignmentTimerCommon process is done successfully.============\n");
    3b57:	c7 04 24 48 11 00 00 	movl   $0x1148,(%esp)
    3b5e:	e8 fc ff ff ff       	call   3b5f <set_timeAlignmentTimerCommon+0x2f>
	FOUT;

}
    3b63:	c9                   	leave  
    3b64:	c3                   	ret    
    3b65:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    3b69:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00003b70 <set_default_MAC>:
**-----------------------------------
**Modified by: Xu Shangfei
**Modified date:2014.10.9
****************************************************************/
void set_default_MAC(struct MAC_MainConfig macdefaultmsg)
{
    3b70:	55                   	push   %ebp
    3b71:	89 e5                	mov    %esp,%ebp
    3b73:	83 ec 04             	sub    $0x4,%esp
    3b76:	e8 fc ff ff ff       	call   3b77 <set_default_MAC+0x7>
	FIN(set_default_MAC());
	fsm_do_ioctrl(STRM_TO_MAC, IOCCMD_RRCTOMAC_CONFIG_MAC_MAIN , (void*)(&macdefaultmsg), sizeof(struct MAC_MainConfig));
    3b7b:	ba 09 00 00 00       	mov    $0x9,%edx
    3b80:	b8 02 00 00 00       	mov    $0x2,%eax
    3b85:	8d 4d 08             	lea    0x8(%ebp),%ecx
    3b88:	c7 04 24 50 00 00 00 	movl   $0x50,(%esp)
    3b8f:	e8 fc ff ff ff       	call   3b90 <set_default_MAC+0x20>
	fsm_printf("[rrc] [conn_establish] set_default_MAC_MainConfig process is done successfully.============\n");
    3b94:	c7 04 24 a8 11 00 00 	movl   $0x11a8,(%esp)
    3b9b:	e8 fc ff ff ff       	call   3b9c <set_default_MAC+0x2c>
	FOUT;
}
    3ba0:	c9                   	leave  
    3ba1:	c3                   	ret    
    3ba2:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    3ba9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00003bb0 <set_default_semi_persistent>:
**-----------------------------------
**Modified by: Xu Shangfei
**Modified date:2014.10.9
****************************************************************/
void set_default_semi_persistent (struct SPS_Config spsdefaultmsg)
{
    3bb0:	55                   	push   %ebp
    3bb1:	89 e5                	mov    %esp,%ebp
    3bb3:	83 ec 04             	sub    $0x4,%esp
    3bb6:	e8 fc ff ff ff       	call   3bb7 <set_default_semi_persistent+0x7>
	FIN(setDefaultspsconfig());
	fsm_do_ioctrl(STRM_TO_MAC, IOCCMD_RRCTOMAC_CONFIG_SPS , (void*)(&spsdefaultmsg), sizeof(struct SPS_Config));
    3bbb:	ba 10 00 00 00       	mov    $0x10,%edx
    3bc0:	b8 02 00 00 00       	mov    $0x2,%eax
    3bc5:	8d 4d 08             	lea    0x8(%ebp),%ecx
    3bc8:	c7 04 24 44 00 00 00 	movl   $0x44,(%esp)
    3bcf:	e8 fc ff ff ff       	call   3bd0 <set_default_semi_persistent+0x20>

	fsm_printf("[rrc] [conn_establish] set_default_semi_persistent process is done successfully.=========\n");
    3bd4:	c7 04 24 08 12 00 00 	movl   $0x1208,(%esp)
    3bdb:	e8 fc ff ff ff       	call   3bdc <set_default_semi_persistent+0x2c>
	FOUT;
}
    3be0:	c9                   	leave  
    3be1:	c3                   	ret    
    3be2:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    3be9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00003bf0 <send_RRCConnectionRequest>:
**-----------------------------------
**Modified by: Xu Shangfei
**Modified date:2014.10.9
****************************************************************/
void send_RRCConnectionRequest(struct UL_CCCH_Message *ulccchRRCremsg)
{
    3bf0:	55                   	push   %ebp
    3bf1:	89 e5                	mov    %esp,%ebp
    3bf3:	53                   	push   %ebx
    3bf4:	83 ec 08             	sub    $0x8,%esp
    3bf7:	e8 fc ff ff ff       	call   3bf8 <send_RRCConnectionRequest+0x8>
	FIN(send_RRCConnectionRequest());

	char *msg = (char *)(&(*ulccchRRCremsg));
	u32 msg_len = sizeof(struct UL_CCCH_Message);
	u32 message_type = 5;
	packet_send_to_rlc(msg, msg_len, message_type);
    3bfc:	b9 05 00 00 00       	mov    $0x5,%ecx
    3c01:	ba 0e 00 00 00       	mov    $0xe,%edx
**-----------------------------------
**Modified by: Xu Shangfei
**Modified date:2014.10.9
****************************************************************/
void send_RRCConnectionRequest(struct UL_CCCH_Message *ulccchRRCremsg)
{
    3c06:	89 c3                	mov    %eax,%ebx
	FIN(send_RRCConnectionRequest());

	char *msg = (char *)(&(*ulccchRRCremsg));
	u32 msg_len = sizeof(struct UL_CCCH_Message);
	u32 message_type = 5;
	packet_send_to_rlc(msg, msg_len, message_type);
    3c08:	e8 fc ff ff ff       	call   3c09 <send_RRCConnectionRequest+0x19>
	fsm_printf("[rrc] [conn_establish] message RRCConnectionRequest sends successfully.\n");
    3c0d:	c7 04 24 64 12 00 00 	movl   $0x1264,(%esp)
    3c14:	e8 fc ff ff ff       	call   3c15 <send_RRCConnectionRequest+0x25>
	fsm_printf("[rrc] [conn_establish] test request type=%d\n",ulccchRRCremsg->msg.rrcConnectionRequest.type );
    3c19:	0f b6 43 04          	movzbl 0x4(%ebx),%eax
    3c1d:	c7 04 24 b0 12 00 00 	movl   $0x12b0,(%esp)
    3c24:	89 44 24 04          	mov    %eax,0x4(%esp)
    3c28:	e8 fc ff ff ff       	call   3c29 <send_RRCConnectionRequest+0x39>
	fsm_printf("[rrc] [conn_establish] test request mmec=%d\n",ulccchRRCremsg->msg.rrcConnectionRequest.ue_Identity.s_TMSI.mmec);
    3c2d:	0f b6 43 05          	movzbl 0x5(%ebx),%eax
    3c31:	c7 04 24 e0 12 00 00 	movl   $0x12e0,(%esp)
    3c38:	89 44 24 04          	mov    %eax,0x4(%esp)
    3c3c:	e8 fc ff ff ff       	call   3c3d <send_RRCConnectionRequest+0x4d>
//	fsm_mem_cpy(data_to_send, data, strlen(data));
//	send_to_user(data_to_send, strlen(data_to_send));

	FOUT;

}
    3c41:	83 c4 08             	add    $0x8,%esp
    3c44:	5b                   	pop    %ebx
    3c45:	5d                   	pop    %ebp
    3c46:	c3                   	ret    
    3c47:	89 f6                	mov    %esi,%esi
    3c49:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00003c50 <gen_ul_dcch_rrccomplete>:
**-----------------------------------
**Modified by: Xu Shangfei
**Modified date:2014.10.9
****************************************************************/
struct UL_DCCH_Message *gen_ul_dcch_rrccomplete(void)
{
    3c50:	55                   	push   %ebp
    3c51:	89 e5                	mov    %esp,%ebp
    3c53:	57                   	push   %edi
    3c54:	53                   	push   %ebx
    3c55:	83 ec 28             	sub    $0x28,%esp
    3c58:	e8 fc ff ff ff       	call   3c59 <gen_ul_dcch_rrccomplete+0x9>
	struct RRCConnectionSetupComplete rrcconnectionsetup_complete1={
		.rrcTransactionIdentifier = 1,
		.selectedPLMN_Identity = 1,    //INTEGER (1..6),
		.registeredMME = registeredmme1,
		//struct DedicatedInfoNAS dedicatedInfoNAS;       //协议里有,暂时不用
	};
    3c5d:	31 c0                	xor    %eax,%eax
    3c5f:	b9 09 00 00 00       	mov    $0x9,%ecx
    3c64:	8d 7d d4             	lea    -0x2c(%ebp),%edi
    3c67:	f3 ab                	rep stos %eax,%es:(%edi)

	struct UL_DCCH_Message *ul_dcchmsg1 = fsm_mem_alloc(sizeof(struct UL_DCCH_Message));
    3c69:	b0 28                	mov    $0x28,%al
	struct RRCConnectionSetupComplete rrcconnectionsetup_complete1={
		.rrcTransactionIdentifier = 1,
		.selectedPLMN_Identity = 1,    //INTEGER (1..6),
		.registeredMME = registeredmme1,
		//struct DedicatedInfoNAS dedicatedInfoNAS;       //协议里有,暂时不用
	};
    3c6b:	c6 45 d4 01          	movb   $0x1,-0x2c(%ebp)
    3c6f:	c7 45 d8 01 00 00 00 	movl   $0x1,-0x28(%ebp)
    3c76:	c6 45 f6 01          	movb   $0x1,-0xa(%ebp)
    3c7a:	66 c7 45 f4 01 00    	movw   $0x1,-0xc(%ebp)
    3c80:	c7 45 e8 02 00 00 00 	movl   $0x2,-0x18(%ebp)
    3c87:	c7 45 dc 02 00 00 00 	movl   $0x2,-0x24(%ebp)

	struct UL_DCCH_Message *ul_dcchmsg1 = fsm_mem_alloc(sizeof(struct UL_DCCH_Message));
    3c8e:	e8 fc ff ff ff       	call   3c8f <gen_ul_dcch_rrccomplete+0x3f>
	ul_dcchmsg1->type = 4;
	fsm_mem_cpy(&(ul_dcchmsg1->msg.rrcConnectionSetupComplete), &rrcconnectionsetup_complete1, sizeof(struct RRCConnectionSetupComplete));
    3c93:	8d 55 d4             	lea    -0x2c(%ebp),%edx
    3c96:	b9 24 00 00 00       	mov    $0x24,%ecx
		.selectedPLMN_Identity = 1,    //INTEGER (1..6),
		.registeredMME = registeredmme1,
		//struct DedicatedInfoNAS dedicatedInfoNAS;       //协议里有,暂时不用
	};

	struct UL_DCCH_Message *ul_dcchmsg1 = fsm_mem_alloc(sizeof(struct UL_DCCH_Message));
    3c9b:	89 c3                	mov    %eax,%ebx
	ul_dcchmsg1->type = 4;
    3c9d:	c7 00 04 00 00 00    	movl   $0x4,(%eax)
	fsm_mem_cpy(&(ul_dcchmsg1->msg.rrcConnectionSetupComplete), &rrcconnectionsetup_complete1, sizeof(struct RRCConnectionSetupComplete));
    3ca3:	8d 40 04             	lea    0x4(%eax),%eax
    3ca6:	e8 fc ff ff ff       	call   3ca7 <gen_ul_dcch_rrccomplete+0x57>
	//ul_dcchmsg1->msg.rrcConnectionSetupComplete = rrcconnectionsetup_complete1;
	fsm_printf("[rrc] [conn_establish] <-- gen rrcsetupcompletemsg message !========\n");
    3cab:	c7 04 24 10 13 00 00 	movl   $0x1310,(%esp)
    3cb2:	e8 fc ff ff ff       	call   3cb3 <gen_ul_dcch_rrccomplete+0x63>
	return ul_dcchmsg1;
}
    3cb7:	89 d8                	mov    %ebx,%eax
    3cb9:	83 c4 28             	add    $0x28,%esp
    3cbc:	5b                   	pop    %ebx
    3cbd:	5f                   	pop    %edi
    3cbe:	5d                   	pop    %ebp
    3cbf:	c3                   	ret    

00003cc0 <gen_dl_ccch_send_rrcsetup>:
**Modified by: Xu Shangfei
**Modified date:2014.10.9
****************************************************************/
struct DL_CCCH_Message *gen_dl_ccch_send_rrcsetup(void)

{
    3cc0:	55                   	push   %ebp
    3cc1:	89 e5                	mov    %esp,%ebp
    3cc3:	81 ec 80 10 00 00    	sub    $0x1080,%esp
    3cc9:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    3ccc:	89 75 f8             	mov    %esi,-0x8(%ebp)
    3ccf:	89 7d fc             	mov    %edi,-0x4(%ebp)
    3cd2:	e8 fc ff ff ff       	call   3cd3 <gen_dl_ccch_send_rrcsetup+0x13>
		.dl_AM_RLC =  dl_am_rlc1,
	};
	struct RlcConfig rlcconfig1={                                       //RLC configuration of SRB and DRB
		.type = 1,
		.rlcConfigType.am = rlc_config_am1,
	};
    3cd7:	31 c0                	xor    %eax,%eax
    3cd9:	8d 95 74 ff ff ff    	lea    -0x8c(%ebp),%edx
    3cdf:	c7 04 02 00 00 00 00 	movl   $0x0,(%edx,%eax,1)
    3ce6:	83 c0 04             	add    $0x4,%eax
    3ce9:	83 f8 1c             	cmp    $0x1c,%eax
    3cec:	72 f1                	jb     3cdf <gen_dl_ccch_send_rrcsetup+0x1f>
		.srbIdentity = 1,       //INTEGER (1..2)
		.haveRlcConfig = true,
		.rlcConfig =  rlcconfig1,    //rlcConfig==null means use default config
		.haveLogicalChannelConfig = true,
		.logicalChannelConfig = logicalchannelconfig1,   //nullmeans use default config
	};
    3cee:	31 c0                	xor    %eax,%eax
    3cf0:	b9 0e 00 00 00       	mov    $0xe,%ecx
    3cf5:	8d bd 80 fe ff ff    	lea    -0x180(%ebp),%edi
    3cfb:	f3 ab                	rep stos %eax,%es:(%edi)
		.srbIdentity = 2,       //INTEGER (1..2)
		.haveRlcConfig = true,
		.rlcConfig =  rlcconfig1,    //rlcConfig==nullmeans use default config
		.haveLogicalChannelConfig = true,
		.logicalChannelConfig = logicalchannelconfig1,   //nullmeans use default config
	};
    3cfd:	8d bd 48 fe ff ff    	lea    -0x1b8(%ebp),%edi
	/**srb-ToAddModList**/
	struct SrbToAddModList srb_toaddmodlist1={
		.num = 2,     //number of SrbToAddMod in SrbToAddModList
		.srbList[0] = srbtoaddmod1,
		.srbList[1] = srbtoaddmod2,
	};
    3d03:	c6 85 84 fe ff ff 01 	movb   $0x1,-0x17c(%ebp)
    3d0a:	8d b5 00 fd ff ff    	lea    -0x300(%ebp),%esi
		.dl_AM_RLC =  dl_am_rlc1,
	};
	struct RlcConfig rlcconfig1={                                       //RLC configuration of SRB and DRB
		.type = 1,
		.rlcConfigType.am = rlc_config_am1,
	};
    3d10:	c7 45 8c 14 00 00 00 	movl   $0x14,-0x74(%ebp)
	/**srb-ToAddModList**/
	struct SrbToAddModList srb_toaddmodlist1={
		.num = 2,     //number of SrbToAddMod in SrbToAddModList
		.srbList[0] = srbtoaddmod1,
		.srbList[1] = srbtoaddmod2,
	};
    3d17:	8b 95 84 fe ff ff    	mov    -0x17c(%ebp),%edx
		.dl_AM_RLC =  dl_am_rlc1,
	};
	struct RlcConfig rlcconfig1={                                       //RLC configuration of SRB and DRB
		.type = 1,
		.rlcConfigType.am = rlc_config_am1,
	};
    3d1d:	c7 45 88 14 00 00 00 	movl   $0x14,-0x78(%ebp)
    3d24:	c7 45 84 02 00 00 00 	movl   $0x2,-0x7c(%ebp)
		.srbIdentity = 2,       //INTEGER (1..2)
		.haveRlcConfig = true,
		.rlcConfig =  rlcconfig1,    //rlcConfig==nullmeans use default config
		.haveLogicalChannelConfig = true,
		.logicalChannelConfig = logicalchannelconfig1,   //nullmeans use default config
	};
    3d2b:	b1 0e                	mov    $0xe,%cl
    3d2d:	f3 ab                	rep stos %eax,%es:(%edi)
		.haveRlcConfig = true,
		.rlcConfig = rlcconfig1,
		.logicalChannelIdentity = 7,//INTEGER (3..10)
		.haveLogicalChannelConfig = true,
		.logicalChannelConfig = logicalchannelconfig1,
	};
    3d2f:	8d bd 08 fe ff ff    	lea    -0x1f8(%ebp),%edi
	/**srb-ToAddModList**/
	struct SrbToAddModList srb_toaddmodlist1={
		.num = 2,     //number of SrbToAddMod in SrbToAddModList
		.srbList[0] = srbtoaddmod1,
		.srbList[1] = srbtoaddmod2,
	};
    3d35:	89 95 08 fd ff ff    	mov    %edx,-0x2f8(%ebp)
		.dl_AM_RLC =  dl_am_rlc1,
	};
	struct RlcConfig rlcconfig1={                                       //RLC configuration of SRB and DRB
		.type = 1,
		.rlcConfigType.am = rlc_config_am1,
	};
    3d3b:	c7 45 80 e8 03 00 00 	movl   $0x3e8,-0x80(%ebp)
    3d42:	c7 85 7c ff ff ff 08 	movl   $0x8,-0x84(%ebp)
    3d49:	00 00 00 
    3d4c:	c7 85 78 ff ff ff 78 	movl   $0x78,-0x88(%ebp)
    3d53:	00 00 00 
		.srbIdentity = 1,       //INTEGER (1..2)
		.haveRlcConfig = true,
		.rlcConfig =  rlcconfig1,    //rlcConfig==null means use default config
		.haveLogicalChannelConfig = true,
		.logicalChannelConfig = logicalchannelconfig1,   //nullmeans use default config
	};
    3d56:	c7 85 88 fe ff ff 01 	movl   $0x1,-0x178(%ebp)
    3d5d:	00 00 00 
    3d60:	c7 85 8c fe ff ff 78 	movl   $0x78,-0x174(%ebp)
    3d67:	00 00 00 
		.haveRlcConfig = true,
		.rlcConfig = rlcconfig1,
		.logicalChannelIdentity = 7,//INTEGER (3..10)
		.haveLogicalChannelConfig = true,
		.logicalChannelConfig = logicalchannelconfig1,
	};
    3d6a:	b1 10                	mov    $0x10,%cl
		.srbIdentity = 1,       //INTEGER (1..2)
		.haveRlcConfig = true,
		.rlcConfig =  rlcconfig1,    //rlcConfig==null means use default config
		.haveLogicalChannelConfig = true,
		.logicalChannelConfig = logicalchannelconfig1,   //nullmeans use default config
	};
    3d6c:	c7 85 90 fe ff ff 08 	movl   $0x8,-0x170(%ebp)
    3d73:	00 00 00 
    3d76:	c7 85 94 fe ff ff e8 	movl   $0x3e8,-0x16c(%ebp)
    3d7d:	03 00 00 
    3d80:	c7 85 98 fe ff ff 02 	movl   $0x2,-0x168(%ebp)
    3d87:	00 00 00 
    3d8a:	c7 85 9c fe ff ff 14 	movl   $0x14,-0x164(%ebp)
    3d91:	00 00 00 
    3d94:	c7 85 a0 fe ff ff 14 	movl   $0x14,-0x160(%ebp)
    3d9b:	00 00 00 
		.srbIdentity = 2,       //INTEGER (1..2)
		.haveRlcConfig = true,
		.rlcConfig =  rlcconfig1,    //rlcConfig==nullmeans use default config
		.haveLogicalChannelConfig = true,
		.logicalChannelConfig = logicalchannelconfig1,   //nullmeans use default config
	};
    3d9e:	c7 85 50 fe ff ff 01 	movl   $0x1,-0x1b0(%ebp)
    3da5:	00 00 00 
    3da8:	c7 85 54 fe ff ff 78 	movl   $0x78,-0x1ac(%ebp)
    3daf:	00 00 00 
    3db2:	c7 85 58 fe ff ff 08 	movl   $0x8,-0x1a8(%ebp)
    3db9:	00 00 00 
    3dbc:	c7 85 5c fe ff ff e8 	movl   $0x3e8,-0x1a4(%ebp)
    3dc3:	03 00 00 
    3dc6:	c7 85 60 fe ff ff 02 	movl   $0x2,-0x1a0(%ebp)
    3dcd:	00 00 00 
    3dd0:	c7 85 64 fe ff ff 14 	movl   $0x14,-0x19c(%ebp)
    3dd7:	00 00 00 
    3dda:	c7 85 68 fe ff ff 14 	movl   $0x14,-0x198(%ebp)
    3de1:	00 00 00 
	/**srb-ToAddModList**/
	struct SrbToAddModList srb_toaddmodlist1={
		.num = 2,     //number of SrbToAddMod in SrbToAddModList
		.srbList[0] = srbtoaddmod1,
		.srbList[1] = srbtoaddmod2,
	};
    3de4:	c7 85 80 fe ff ff 01 	movl   $0x1,-0x180(%ebp)
    3deb:	00 00 00 
    3dee:	c6 85 a4 fe ff ff 01 	movb   $0x1,-0x15c(%ebp)
    3df5:	c6 85 a5 fe ff ff 01 	movb   $0x1,-0x15b(%ebp)
    3dfc:	c7 85 a6 fe ff ff 01 	movl   $0x1,-0x15a(%ebp)
    3e03:	00 00 00 
    3e06:	c7 85 aa fe ff ff 20 	movl   $0x20,-0x156(%ebp)
    3e0d:	00 00 00 
    3e10:	c7 85 ae fe ff ff 64 	movl   $0x64,-0x152(%ebp)
    3e17:	00 00 00 
    3e1a:	c7 85 b2 fe ff ff 01 	movl   $0x1,-0x14e(%ebp)
    3e21:	00 00 00 
    3e24:	c7 85 04 fd ff ff 01 	movl   $0x1,-0x2fc(%ebp)
    3e2b:	00 00 00 
    3e2e:	c7 85 0c fd ff ff 01 	movl   $0x1,-0x2f4(%ebp)
    3e35:	00 00 00 
    3e38:	8b 95 a4 fe ff ff    	mov    -0x15c(%ebp),%edx
    3e3e:	c6 85 4c fe ff ff 01 	movb   $0x1,-0x1b4(%ebp)
    3e45:	c7 85 10 fd ff ff 78 	movl   $0x78,-0x2f0(%ebp)
    3e4c:	00 00 00 
    3e4f:	c7 85 14 fd ff ff 08 	movl   $0x8,-0x2ec(%ebp)
    3e56:	00 00 00 
    3e59:	89 95 28 fd ff ff    	mov    %edx,-0x2d8(%ebp)
    3e5f:	8b 95 a8 fe ff ff    	mov    -0x158(%ebp),%edx
    3e65:	c7 85 18 fd ff ff e8 	movl   $0x3e8,-0x2e8(%ebp)
    3e6c:	03 00 00 
    3e6f:	c7 85 1c fd ff ff 02 	movl   $0x2,-0x2e4(%ebp)
    3e76:	00 00 00 
    3e79:	c7 85 20 fd ff ff 14 	movl   $0x14,-0x2e0(%ebp)
    3e80:	00 00 00 
    3e83:	89 95 2c fd ff ff    	mov    %edx,-0x2d4(%ebp)
    3e89:	8b 95 ac fe ff ff    	mov    -0x154(%ebp),%edx
    3e8f:	c7 85 24 fd ff ff 14 	movl   $0x14,-0x2dc(%ebp)
    3e96:	00 00 00 
    3e99:	c7 85 48 fe ff ff 02 	movl   $0x2,-0x1b8(%ebp)
    3ea0:	00 00 00 
    3ea3:	c6 85 6c fe ff ff 01 	movb   $0x1,-0x194(%ebp)
    3eaa:	89 95 30 fd ff ff    	mov    %edx,-0x2d0(%ebp)
    3eb0:	8b 95 b0 fe ff ff    	mov    -0x150(%ebp),%edx
    3eb6:	c6 85 6d fe ff ff 01 	movb   $0x1,-0x193(%ebp)
    3ebd:	c7 85 6e fe ff ff 01 	movl   $0x1,-0x192(%ebp)
    3ec4:	00 00 00 
    3ec7:	c7 85 72 fe ff ff 20 	movl   $0x20,-0x18e(%ebp)
    3ece:	00 00 00 
    3ed1:	89 95 34 fd ff ff    	mov    %edx,-0x2cc(%ebp)
    3ed7:	8b 95 b4 fe ff ff    	mov    -0x14c(%ebp),%edx
    3edd:	c7 85 76 fe ff ff 64 	movl   $0x64,-0x18a(%ebp)
    3ee4:	00 00 00 
    3ee7:	c7 85 7a fe ff ff 01 	movl   $0x1,-0x186(%ebp)
    3eee:	00 00 00 
    3ef1:	c7 85 3c fd ff ff 02 	movl   $0x2,-0x2c4(%ebp)
    3ef8:	00 00 00 
    3efb:	89 95 38 fd ff ff    	mov    %edx,-0x2c8(%ebp)
    3f01:	8b 95 4c fe ff ff    	mov    -0x1b4(%ebp),%edx
    3f07:	c7 85 44 fd ff ff 01 	movl   $0x1,-0x2bc(%ebp)
    3f0e:	00 00 00 
    3f11:	c7 85 48 fd ff ff 78 	movl   $0x78,-0x2b8(%ebp)
    3f18:	00 00 00 
    3f1b:	c7 85 4c fd ff ff 08 	movl   $0x8,-0x2b4(%ebp)
    3f22:	00 00 00 
    3f25:	89 95 40 fd ff ff    	mov    %edx,-0x2c0(%ebp)
    3f2b:	c7 85 50 fd ff ff e8 	movl   $0x3e8,-0x2b0(%ebp)
    3f32:	03 00 00 
    3f35:	c7 85 54 fd ff ff 02 	movl   $0x2,-0x2ac(%ebp)
    3f3c:	00 00 00 
    3f3f:	c7 85 58 fd ff ff 14 	movl   $0x14,-0x2a8(%ebp)
    3f46:	00 00 00 
    3f49:	c7 85 5c fd ff ff 14 	movl   $0x14,-0x2a4(%ebp)
    3f50:	00 00 00 
    3f53:	8b 95 6c fe ff ff    	mov    -0x194(%ebp),%edx
		.haveRlcConfig = true,
		.rlcConfig = rlcconfig1,
		.logicalChannelIdentity = 7,//INTEGER (3..10)
		.haveLogicalChannelConfig = true,
		.logicalChannelConfig = logicalchannelconfig1,
	};
    3f59:	f3 ab                	rep stos %eax,%es:(%edi)
	/**DrbToAddModList**/
	struct DrbToAddModList drb_toaddmodlist1={
		.num = 1,
		.drbList[0] = drb_toaddmod1,
	};
    3f5b:	c6 85 10 fe ff ff 01 	movb   $0x1,-0x1f0(%ebp)
		.haveRlcConfig = true,
		.rlcConfig = rlcconfig1,
		.logicalChannelIdentity = 7,//INTEGER (3..10)
		.haveLogicalChannelConfig = true,
		.logicalChannelConfig = logicalchannelconfig1,
	};
    3f62:	c7 85 74 ff ff ff 01 	movl   $0x1,-0x8c(%ebp)
    3f69:	00 00 00 
	/**srb-ToAddModList**/
	struct SrbToAddModList srb_toaddmodlist1={
		.num = 2,     //number of SrbToAddMod in SrbToAddModList
		.srbList[0] = srbtoaddmod1,
		.srbList[1] = srbtoaddmod2,
	};
    3f6c:	89 95 60 fd ff ff    	mov    %edx,-0x2a0(%ebp)
    3f72:	8b 95 70 fe ff ff    	mov    -0x190(%ebp),%edx
		.haveRlcConfig = true,
		.rlcConfig = rlcconfig1,
		.logicalChannelIdentity = 7,//INTEGER (3..10)
		.haveLogicalChannelConfig = true,
		.logicalChannelConfig = logicalchannelconfig1,
	};
    3f78:	c7 85 14 fe ff ff 01 	movl   $0x1,-0x1ec(%ebp)
    3f7f:	00 00 00 
    3f82:	c7 85 18 fe ff ff 78 	movl   $0x78,-0x1e8(%ebp)
    3f89:	00 00 00 
	/**DrbToAddModList**/
	struct DrbToAddModList drb_toaddmodlist1={
		.num = 1,
		.drbList[0] = drb_toaddmod1,
	};
    3f8c:	b1 b1                	mov    $0xb1,%cl
	/**srb-ToAddModList**/
	struct SrbToAddModList srb_toaddmodlist1={
		.num = 2,     //number of SrbToAddMod in SrbToAddModList
		.srbList[0] = srbtoaddmod1,
		.srbList[1] = srbtoaddmod2,
	};
    3f8e:	89 95 64 fd ff ff    	mov    %edx,-0x29c(%ebp)
    3f94:	8b 95 74 fe ff ff    	mov    -0x18c(%ebp),%edx
		.haveRlcConfig = true,
		.rlcConfig = rlcconfig1,
		.logicalChannelIdentity = 7,//INTEGER (3..10)
		.haveLogicalChannelConfig = true,
		.logicalChannelConfig = logicalchannelconfig1,
	};
    3f9a:	c7 85 1c fe ff ff 08 	movl   $0x8,-0x1e4(%ebp)
    3fa1:	00 00 00 
    3fa4:	c7 85 20 fe ff ff e8 	movl   $0x3e8,-0x1e0(%ebp)
    3fab:	03 00 00 
    3fae:	c7 85 24 fe ff ff 02 	movl   $0x2,-0x1dc(%ebp)
    3fb5:	00 00 00 
	/**srb-ToAddModList**/
	struct SrbToAddModList srb_toaddmodlist1={
		.num = 2,     //number of SrbToAddMod in SrbToAddModList
		.srbList[0] = srbtoaddmod1,
		.srbList[1] = srbtoaddmod2,
	};
    3fb8:	89 95 68 fd ff ff    	mov    %edx,-0x298(%ebp)
    3fbe:	8b 95 78 fe ff ff    	mov    -0x188(%ebp),%edx
		.haveRlcConfig = true,
		.rlcConfig = rlcconfig1,
		.logicalChannelIdentity = 7,//INTEGER (3..10)
		.haveLogicalChannelConfig = true,
		.logicalChannelConfig = logicalchannelconfig1,
	};
    3fc4:	c7 85 28 fe ff ff 14 	movl   $0x14,-0x1d8(%ebp)
    3fcb:	00 00 00 
    3fce:	c7 85 2c fe ff ff 14 	movl   $0x14,-0x1d4(%ebp)
    3fd5:	00 00 00 
	/**DrbToAddModList**/
	struct DrbToAddModList drb_toaddmodlist1={
		.num = 1,
		.drbList[0] = drb_toaddmod1,
	};
    3fd8:	c7 85 08 fe ff ff 01 	movl   $0x1,-0x1f8(%ebp)
    3fdf:	00 00 00 
	/**srb-ToAddModList**/
	struct SrbToAddModList srb_toaddmodlist1={
		.num = 2,     //number of SrbToAddMod in SrbToAddModList
		.srbList[0] = srbtoaddmod1,
		.srbList[1] = srbtoaddmod2,
	};
    3fe2:	89 95 6c fd ff ff    	mov    %edx,-0x294(%ebp)
    3fe8:	8b 95 7c fe ff ff    	mov    -0x184(%ebp),%edx
	};
	/**DrbToAddModList**/
	struct DrbToAddModList drb_toaddmodlist1={
		.num = 1,
		.drbList[0] = drb_toaddmod1,
	};
    3fee:	c7 85 0c fe ff ff 07 	movl   $0x7,-0x1f4(%ebp)
    3ff5:	00 00 00 
    3ff8:	c7 85 30 fe ff ff 07 	movl   $0x7,-0x1d0(%ebp)
    3fff:	00 00 00 
    4002:	c6 85 34 fe ff ff 01 	movb   $0x1,-0x1cc(%ebp)
	/**srb-ToAddModList**/
	struct SrbToAddModList srb_toaddmodlist1={
		.num = 2,     //number of SrbToAddMod in SrbToAddModList
		.srbList[0] = srbtoaddmod1,
		.srbList[1] = srbtoaddmod2,
	};
    4009:	89 95 70 fd ff ff    	mov    %edx,-0x290(%ebp)
	};
	/**DrbToAddModList**/
	struct DrbToAddModList drb_toaddmodlist1={
		.num = 1,
		.drbList[0] = drb_toaddmod1,
	};
    400f:	8d 95 64 f9 ff ff    	lea    -0x69c(%ebp),%edx
    4015:	89 d7                	mov    %edx,%edi
    4017:	f3 ab                	rep stos %eax,%es:(%edi)
    4019:	8b 85 10 fe ff ff    	mov    -0x1f0(%ebp),%eax
		.drx_RetransmissionTimer = drx_RetransmissionTimer_psf8,
		.type = 3,    //1:sf10......
		.longDRX_CycleStartOffset.sf32 = 30,
		.haveShortDRX = true,
		.shortDRX = shortdrx1,
	};
    401f:	8d 8d 1c ff ff ff    	lea    -0xe4(%ebp),%ecx
	};
	/**DrbToAddModList**/
	struct DrbToAddModList drb_toaddmodlist1={
		.num = 1,
		.drbList[0] = drb_toaddmod1,
	};
    4025:	c6 85 35 fe ff ff 01 	movb   $0x1,-0x1cb(%ebp)
    402c:	c7 85 36 fe ff ff 01 	movl   $0x1,-0x1ca(%ebp)
    4033:	00 00 00 
    4036:	c7 85 3a fe ff ff 20 	movl   $0x20,-0x1c6(%ebp)
    403d:	00 00 00 
    4040:	c7 85 3e fe ff ff 64 	movl   $0x64,-0x1c2(%ebp)
    4047:	00 00 00 
    404a:	c7 85 42 fe ff ff 01 	movl   $0x1,-0x1be(%ebp)
    4051:	00 00 00 
    4054:	c7 85 68 f9 ff ff 01 	movl   $0x1,-0x698(%ebp)
    405b:	00 00 00 
    405e:	c7 85 6c f9 ff ff 07 	movl   $0x7,-0x694(%ebp)
    4065:	00 00 00 
    4068:	89 85 70 f9 ff ff    	mov    %eax,-0x690(%ebp)
    406e:	8b 85 34 fe ff ff    	mov    -0x1cc(%ebp),%eax
    4074:	c7 85 74 f9 ff ff 01 	movl   $0x1,-0x68c(%ebp)
    407b:	00 00 00 
    407e:	c7 85 78 f9 ff ff 78 	movl   $0x78,-0x688(%ebp)
    4085:	00 00 00 
    4088:	c7 85 7c f9 ff ff 08 	movl   $0x8,-0x684(%ebp)
    408f:	00 00 00 
    4092:	89 85 94 f9 ff ff    	mov    %eax,-0x66c(%ebp)
    4098:	8b 85 38 fe ff ff    	mov    -0x1c8(%ebp),%eax
    409e:	c7 85 80 f9 ff ff e8 	movl   $0x3e8,-0x680(%ebp)
    40a5:	03 00 00 
    40a8:	c7 85 84 f9 ff ff 02 	movl   $0x2,-0x67c(%ebp)
    40af:	00 00 00 
    40b2:	c7 85 88 f9 ff ff 14 	movl   $0x14,-0x678(%ebp)
    40b9:	00 00 00 
    40bc:	89 85 98 f9 ff ff    	mov    %eax,-0x668(%ebp)
    40c2:	8b 85 3c fe ff ff    	mov    -0x1c4(%ebp),%eax
    40c8:	c7 85 8c f9 ff ff 14 	movl   $0x14,-0x674(%ebp)
    40cf:	00 00 00 
    40d2:	c7 85 90 f9 ff ff 07 	movl   $0x7,-0x670(%ebp)
    40d9:	00 00 00 
    40dc:	89 85 9c f9 ff ff    	mov    %eax,-0x664(%ebp)
    40e2:	8b 85 40 fe ff ff    	mov    -0x1c0(%ebp),%eax
    40e8:	89 85 a0 f9 ff ff    	mov    %eax,-0x660(%ebp)
    40ee:	8b 85 44 fe ff ff    	mov    -0x1bc(%ebp),%eax
    40f4:	89 85 a4 f9 ff ff    	mov    %eax,-0x65c(%ebp)
		.drx_RetransmissionTimer = drx_RetransmissionTimer_psf8,
		.type = 3,    //1:sf10......
		.longDRX_CycleStartOffset.sf32 = 30,
		.haveShortDRX = true,
		.shortDRX = shortdrx1,
	};
    40fa:	31 c0                	xor    %eax,%eax
    40fc:	c7 04 01 00 00 00 00 	movl   $0x0,(%ecx,%eax,1)
    4103:	83 c0 04             	add    $0x4,%eax
    4106:	83 f8 20             	cmp    $0x20,%eax
    4109:	72 f1                	jb     40fc <gen_dl_ccch_send_rrcsetup+0x43c>
		.haveDRX_Config = true,
		.drx_Config = drx_config1,
		.timeAlignmentTimerDedicated = time_alignmenttimer1,
		.type = 2,   //1:release, 2:setup
		.phr_Config.setup = phr_configsetup1,
	};
    410b:	8d 85 74 fd ff ff    	lea    -0x28c(%ebp),%eax
    4111:	b9 14 00 00 00       	mov    $0x14,%ecx
    4116:	89 85 84 ef ff ff    	mov    %eax,-0x107c(%ebp)
    411c:	8b bd 84 ef ff ff    	mov    -0x107c(%ebp),%edi
    4122:	31 c0                	xor    %eax,%eax
		.shortDRX = shortdrx1,
	};
	struct DRX_Config drx_config1={
        .type = 2,    //1:release, 2:setup
		.choice.setup = drx_config_setup1,
	};
    4124:	c6 85 30 ff ff ff 01 	movb   $0x1,-0xd0(%ebp)
    412b:	8b 9d 30 ff ff ff    	mov    -0xd0(%ebp),%ebx
		.drx_RetransmissionTimer = drx_RetransmissionTimer_psf8,
		.type = 3,    //1:sf10......
		.longDRX_CycleStartOffset.sf32 = 30,
		.haveShortDRX = true,
		.shortDRX = shortdrx1,
	};
    4131:	c7 85 2c ff ff ff 1e 	movl   $0x1e,-0xd4(%ebp)
    4138:	00 00 00 
	struct DRX_Config drx_config1={
        .type = 2,    //1:release, 2:setup
		.choice.setup = drx_config_setup1,
	};
    413b:	c7 85 1c ff ff ff 3c 	movl   $0x3c,-0xe4(%ebp)
    4142:	00 00 00 
		.haveDRX_Config = true,
		.drx_Config = drx_config1,
		.timeAlignmentTimerDedicated = time_alignmenttimer1,
		.type = 2,   //1:release, 2:setup
		.phr_Config.setup = phr_configsetup1,
	};
    4145:	f3 ab                	rep stos %eax,%es:(%edi)
		.n1_PUCCH_AN_PersistentList = n1_pucch_an_persistentlist1,
	};
	struct SPS_ConfigDL sps_configdl1={
		.type = 2,    //1:release, 2:setup
		.choice.setup = sps_configdl_setup1,
	};
    4147:	8d 8d 58 ff ff ff    	lea    -0xa8(%ebp),%ecx
		.shortDRX = shortdrx1,
	};
	struct DRX_Config drx_config1={
        .type = 2,    //1:release, 2:setup
		.choice.setup = drx_config_setup1,
	};
    414d:	c7 85 20 ff ff ff 64 	movl   $0x64,-0xe0(%ebp)
    4154:	00 00 00 
    4157:	c7 85 24 ff ff ff 08 	movl   $0x8,-0xdc(%ebp)
    415e:	00 00 00 
    4161:	c7 85 28 ff ff ff 03 	movl   $0x3,-0xd8(%ebp)
    4168:	00 00 00 
    416b:	c7 85 34 ff ff ff 40 	movl   $0x40,-0xcc(%ebp)
    4172:	00 00 00 
    4175:	c7 85 38 ff ff ff 04 	movl   $0x4,-0xc8(%ebp)
    417c:	00 00 00 
    417f:	c7 85 bc fe ff ff 3c 	movl   $0x3c,-0x144(%ebp)
    4186:	00 00 00 
    4189:	c7 85 c0 fe ff ff 64 	movl   $0x64,-0x140(%ebp)
    4190:	00 00 00 
    4193:	c7 85 c4 fe ff ff 08 	movl   $0x8,-0x13c(%ebp)
    419a:	00 00 00 
    419d:	c7 85 c8 fe ff ff 03 	movl   $0x3,-0x138(%ebp)
    41a4:	00 00 00 
    41a7:	c7 85 cc fe ff ff 1e 	movl   $0x1e,-0x134(%ebp)
    41ae:	00 00 00 
    41b1:	89 9d d0 fe ff ff    	mov    %ebx,-0x130(%ebp)
    41b7:	c7 85 d4 fe ff ff 40 	movl   $0x40,-0x12c(%ebp)
    41be:	00 00 00 
    41c1:	c7 85 d8 fe ff ff 04 	movl   $0x4,-0x128(%ebp)
    41c8:	00 00 00 
		.haveDRX_Config = true,
		.drx_Config = drx_config1,
		.timeAlignmentTimerDedicated = time_alignmenttimer1,
		.type = 2,   //1:release, 2:setup
		.phr_Config.setup = phr_configsetup1,
	};
    41cb:	c7 85 b8 fe ff ff 02 	movl   $0x2,-0x148(%ebp)
    41d2:	00 00 00 
    41d5:	c7 85 8c fd ff ff 02 	movl   $0x2,-0x274(%ebp)
    41dc:	00 00 00 
    41df:	c7 85 90 fd ff ff 3c 	movl   $0x3c,-0x270(%ebp)
    41e6:	00 00 00 
    41e9:	c7 85 94 fd ff ff 64 	movl   $0x64,-0x26c(%ebp)
    41f0:	00 00 00 
    41f3:	c7 85 98 fd ff ff 08 	movl   $0x8,-0x268(%ebp)
    41fa:	00 00 00 
    41fd:	c7 85 9c fd ff ff 03 	movl   $0x3,-0x264(%ebp)
    4204:	00 00 00 
    4207:	c7 85 a0 fd ff ff 1e 	movl   $0x1e,-0x260(%ebp)
    420e:	00 00 00 
    4211:	89 9d a4 fd ff ff    	mov    %ebx,-0x25c(%ebp)
    4217:	c7 85 a8 fd ff ff 40 	movl   $0x40,-0x258(%ebp)
    421e:	00 00 00 
    4221:	c7 85 ac fd ff ff 04 	movl   $0x4,-0x254(%ebp)
    4228:	00 00 00 
    422b:	c7 85 c0 fd ff ff 01 	movl   $0x1,-0x240(%ebp)
    4232:	00 00 00 
    4235:	c7 85 bc fd ff ff 64 	movl   $0x64,-0x244(%ebp)
    423c:	00 00 00 
    423f:	c7 85 b8 fd ff ff 64 	movl   $0x64,-0x248(%ebp)
    4246:	00 00 00 
		.n1_PUCCH_AN_PersistentList = n1_pucch_an_persistentlist1,
	};
	struct SPS_ConfigDL sps_configdl1={
		.type = 2,    //1:release, 2:setup
		.choice.setup = sps_configdl_setup1,
	};
    4249:	c7 04 01 00 00 00 00 	movl   $0x0,(%ecx,%eax,1)
    4250:	83 c0 04             	add    $0x4,%eax
    4253:	83 f8 1c             	cmp    $0x1c,%eax
    4256:	72 f1                	jb     4249 <gen_dl_ccch_send_rrcsetup+0x589>
    4258:	c7 85 70 ff ff ff 04 	movl   $0x4,-0x90(%ebp)
    425f:	00 00 00 
		.twoIntervalsConfig = true,
	};
	struct SPS_ConfigUL sps_configul1={
		.type = 2,   //1:release, 2:setup
		.choice.setup = sps_config_setup1,
	};
    4262:	8d 8d 3c ff ff ff    	lea    -0xc4(%ebp),%ecx
    4268:	31 c0                	xor    %eax,%eax
		.n1_PUCCH_AN_PersistentList = n1_pucch_an_persistentlist1,
	};
	struct SPS_ConfigDL sps_configdl1={
		.type = 2,    //1:release, 2:setup
		.choice.setup = sps_configdl_setup1,
	};
    426a:	c7 85 6c ff ff ff 03 	movl   $0x3,-0x94(%ebp)
    4271:	00 00 00 
    4274:	c7 85 68 ff ff ff 02 	movl   $0x2,-0x98(%ebp)
    427b:	00 00 00 
    427e:	c7 85 64 ff ff ff 01 	movl   $0x1,-0x9c(%ebp)
    4285:	00 00 00 
    4288:	c7 85 60 ff ff ff 04 	movl   $0x4,-0xa0(%ebp)
    428f:	00 00 00 
    4292:	c7 85 5c ff ff ff 28 	movl   $0x28,-0xa4(%ebp)
    4299:	00 00 00 
		.twoIntervalsConfig = true,
	};
	struct SPS_ConfigUL sps_configul1={
		.type = 2,   //1:release, 2:setup
		.choice.setup = sps_config_setup1,
	};
    429c:	c7 04 01 00 00 00 00 	movl   $0x0,(%ecx,%eax,1)
    42a3:	83 c0 04             	add    $0x4,%eax
    42a6:	83 f8 1c             	cmp    $0x1c,%eax
    42a9:	72 f1                	jb     429c <gen_dl_ccch_send_rrcsetup+0x5dc>
		.semiPersistSchedC_RNTI = c_rnti1,
		.haveSPS_ConfigDL = true,
		.sps_ConfigDL = sps_configdl1,
		.haveSPS_ConfigUL = true,
		.sps_ConfigUL = sps_configul1,
	};
    42ab:	8d bd c4 fd ff ff    	lea    -0x23c(%ebp),%edi
    42b1:	31 c0                	xor    %eax,%eax
    42b3:	b9 11 00 00 00       	mov    $0x11,%ecx
    42b8:	89 bd 80 ef ff ff    	mov    %edi,-0x1080(%ebp)
    42be:	f3 ab                	rep stos %eax,%es:(%edi)
    42c0:	8b 85 5c ff ff ff    	mov    -0xa4(%ebp),%eax
	struct CQI_ReportConfig cqi_reportconfig1={                                    //descripe CQI_ReportConfig
		.cqi_ReportModeAperiodic = rm20,
		.nomPDSCH_RS_EPRE_Offset = 2, //INTEGER (-1..6)
		.haveCQI_ReportPeriodic = true,
		.cqi_ReportPeriodic = cqi_reportperodic1,
	};
    42c6:	8d 8d fc fe ff ff    	lea    -0x104(%ebp),%ecx
		.twoIntervalsConfig = true,
	};
	struct SPS_ConfigUL sps_configul1={
		.type = 2,   //1:release, 2:setup
		.choice.setup = sps_config_setup1,
	};
    42cc:	c6 85 48 ff ff ff 01 	movb   $0x1,-0xb8(%ebp)
    42d3:	c6 85 54 ff ff ff 01 	movb   $0x1,-0xac(%ebp)
    42da:	c7 85 50 ff ff ff 01 	movl   $0x1,-0xb0(%ebp)
    42e1:	00 00 00 
		.semiPersistSchedC_RNTI = c_rnti1,
		.haveSPS_ConfigDL = true,
		.sps_ConfigDL = sps_configdl1,
		.haveSPS_ConfigUL = true,
		.sps_ConfigUL = sps_configul1,
	};
    42e4:	89 85 d0 fd ff ff    	mov    %eax,-0x230(%ebp)
    42ea:	8b 85 60 ff ff ff    	mov    -0xa0(%ebp),%eax
		.twoIntervalsConfig = true,
	};
	struct SPS_ConfigUL sps_configul1={
		.type = 2,   //1:release, 2:setup
		.choice.setup = sps_config_setup1,
	};
    42f0:	c7 85 4c ff ff ff 01 	movl   $0x1,-0xb4(%ebp)
    42f7:	00 00 00 
    42fa:	c7 85 44 ff ff ff 02 	movl   $0x2,-0xbc(%ebp)
    4301:	00 00 00 
    4304:	c7 85 40 ff ff ff 3c 	movl   $0x3c,-0xc0(%ebp)
    430b:	00 00 00 
		.semiPersistSchedC_RNTI = c_rnti1,
		.haveSPS_ConfigDL = true,
		.sps_ConfigDL = sps_configdl1,
		.haveSPS_ConfigUL = true,
		.sps_ConfigUL = sps_configul1,
	};
    430e:	89 85 d4 fd ff ff    	mov    %eax,-0x22c(%ebp)
    4314:	8b 85 64 ff ff ff    	mov    -0x9c(%ebp),%eax
    431a:	c7 85 58 ff ff ff 02 	movl   $0x2,-0xa8(%ebp)
    4321:	00 00 00 
    4324:	c7 85 cc fd ff ff 02 	movl   $0x2,-0x234(%ebp)
    432b:	00 00 00 
    432e:	c7 85 3c ff ff ff 02 	movl   $0x2,-0xc4(%ebp)
    4335:	00 00 00 
    4338:	89 85 d8 fd ff ff    	mov    %eax,-0x228(%ebp)
    433e:	8b 85 68 ff ff ff    	mov    -0x98(%ebp),%eax
    4344:	c7 85 ec fd ff ff 02 	movl   $0x2,-0x214(%ebp)
    434b:	00 00 00 
    434e:	c7 85 f0 fd ff ff 3c 	movl   $0x3c,-0x210(%ebp)
    4355:	00 00 00 
    4358:	c7 85 f4 fd ff ff 02 	movl   $0x2,-0x20c(%ebp)
    435f:	00 00 00 
    4362:	89 85 dc fd ff ff    	mov    %eax,-0x224(%ebp)
    4368:	8b 85 6c ff ff ff    	mov    -0x94(%ebp),%eax
    436e:	c7 85 fc fd ff ff 01 	movl   $0x1,-0x204(%ebp)
    4375:	00 00 00 
    4378:	c7 85 00 fe ff ff 01 	movl   $0x1,-0x200(%ebp)
    437f:	00 00 00 
	};

	struct PUCCH_ConfigDedicated pucch_configdedicate1={                         //descripe PUCCH_ConfigDedicated
		.type = 2,   //1:release, 2:setup, 3:tddAckNackFeedbackMode
		.ackNackRepetition.setup = acknacrepetition_setup1,
	};
    4382:	c7 45 f0 04 00 00 00 	movl   $0x4,-0x10(%ebp)
		.semiPersistSchedC_RNTI = c_rnti1,
		.haveSPS_ConfigDL = true,
		.sps_ConfigDL = sps_configdl1,
		.haveSPS_ConfigUL = true,
		.sps_ConfigUL = sps_configul1,
	};
    4389:	89 85 e0 fd ff ff    	mov    %eax,-0x220(%ebp)
    438f:	8b 85 70 ff ff ff    	mov    -0x90(%ebp),%eax
    4395:	89 85 e4 fd ff ff    	mov    %eax,-0x21c(%ebp)
    439b:	8b 85 48 ff ff ff    	mov    -0xb8(%ebp),%eax
    43a1:	89 85 f8 fd ff ff    	mov    %eax,-0x208(%ebp)
    43a7:	8b 85 54 ff ff ff    	mov    -0xac(%ebp),%eax
    43ad:	89 85 04 fe ff ff    	mov    %eax,-0x1fc(%ebp)
	struct CQI_ReportConfig cqi_reportconfig1={                                    //descripe CQI_ReportConfig
		.cqi_ReportModeAperiodic = rm20,
		.nomPDSCH_RS_EPRE_Offset = 2, //INTEGER (-1..6)
		.haveCQI_ReportPeriodic = true,
		.cqi_ReportPeriodic = cqi_reportperodic1,
	};
    43b3:	31 c0                	xor    %eax,%eax
	};

	struct PUCCH_ConfigDedicated pucch_configdedicate1={                         //descripe PUCCH_ConfigDedicated
		.type = 2,   //1:release, 2:setup, 3:tddAckNackFeedbackMode
		.ackNackRepetition.setup = acknacrepetition_setup1,
	};
    43b5:	c7 45 ec 02 00 00 00 	movl   $0x2,-0x14(%ebp)
		.indexOfFormat3A = 2,       //INTEGER (1..31)
	};
	struct TPC_PDCCH_Config tpc_pdcch_config1={
		.type = 2,    //1:release, 2:setup
		.choice.setup = tpc_pdcch_config_setup1,
	};
    43bc:	c7 45 e4 02 00 00 00 	movl   $0x2,-0x1c(%ebp)
    43c3:	c7 45 e0 02 00 00 00 	movl   $0x2,-0x20(%ebp)
	struct CQI_ReportPeriodic_setup cqi_reportperioid1={
		.cqi_PUCCH_ResourceIndex = 100,//INTEGER (0.. 1185)
		.cqi_pmi_ConfigIndex = 100,    //INTEGER (0..1023)
		.type = 3,    //1:widebandCQI......
		.cqi_FormatIndicatorPeriodic.ri_ConfigIndex = 100,
	};
    43ca:	c7 45 d8 64 00 00 00 	movl   $0x64,-0x28(%ebp)
	struct CQI_ReportPeriodic cqi_reportperodic1={
		.type = 2,   //1:release, 2:setup, 3:ri_ConfigIndex, 4:simultaneousAckNackAndCQI
		.choice.setup = cqi_reportperioid1,
	};
    43d1:	c7 45 cc 64 00 00 00 	movl   $0x64,-0x34(%ebp)
    43d8:	c7 45 d0 64 00 00 00 	movl   $0x64,-0x30(%ebp)
    43df:	c7 45 d4 03 00 00 00 	movl   $0x3,-0x2c(%ebp)
    43e6:	c7 45 ac 64 00 00 00 	movl   $0x64,-0x54(%ebp)
    43ed:	c7 45 b0 64 00 00 00 	movl   $0x64,-0x50(%ebp)
    43f4:	c7 45 b4 03 00 00 00 	movl   $0x3,-0x4c(%ebp)
    43fb:	c7 45 b8 64 00 00 00 	movl   $0x64,-0x48(%ebp)
	struct CQI_ReportConfig cqi_reportconfig1={                                    //descripe CQI_ReportConfig
		.cqi_ReportModeAperiodic = rm20,
		.nomPDSCH_RS_EPRE_Offset = 2, //INTEGER (-1..6)
		.haveCQI_ReportPeriodic = true,
		.cqi_ReportPeriodic = cqi_reportperodic1,
	};
    4402:	c7 04 01 00 00 00 00 	movl   $0x0,(%ecx,%eax,1)
    4409:	83 c0 04             	add    $0x4,%eax
    440c:	83 f8 20             	cmp    $0x20,%eax
    440f:	72 f1                	jb     4402 <gen_dl_ccch_send_rrcsetup+0x742>
    4411:	8b 45 ac             	mov    -0x54(%ebp),%eax
		.cyclicShift = cs1,
	};
	struct SoundingRS_UL_ConfigDedicated soundrs_ul_configdedicated1={              //descripe SoundingRS_UL_ConfigDedicated
		.type = 2,    //1:release, 2:setup
		.choice.setup = soundrs_ul_configdedicate_setup1,
	};
    4414:	8d 8d dc fe ff ff    	lea    -0x124(%ebp),%ecx
	struct CQI_ReportConfig cqi_reportconfig1={                                    //descripe CQI_ReportConfig
		.cqi_ReportModeAperiodic = rm20,
		.nomPDSCH_RS_EPRE_Offset = 2, //INTEGER (-1..6)
		.haveCQI_ReportPeriodic = true,
		.cqi_ReportPeriodic = cqi_reportperodic1,
	};
    441a:	c7 45 a8 02 00 00 00 	movl   $0x2,-0x58(%ebp)
    4421:	c7 85 08 ff ff ff 02 	movl   $0x2,-0xf8(%ebp)
    4428:	00 00 00 
    442b:	89 85 0c ff ff ff    	mov    %eax,-0xf4(%ebp)
    4431:	8b 45 b0             	mov    -0x50(%ebp),%eax
    4434:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%ebp)
    443a:	8b 45 b4             	mov    -0x4c(%ebp),%eax
    443d:	89 85 14 ff ff ff    	mov    %eax,-0xec(%ebp)
    4443:	8b 45 b8             	mov    -0x48(%ebp),%eax
    4446:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%ebp)
		.cyclicShift = cs1,
	};
	struct SoundingRS_UL_ConfigDedicated soundrs_ul_configdedicated1={              //descripe SoundingRS_UL_ConfigDedicated
		.type = 2,    //1:release, 2:setup
		.choice.setup = soundrs_ul_configdedicate_setup1,
	};
    444c:	31 c0                	xor    %eax,%eax
    444e:	c7 04 01 00 00 00 00 	movl   $0x0,(%ecx,%eax,1)
    4455:	83 c0 04             	add    $0x4,%eax
    4458:	83 f8 20             	cmp    $0x20,%eax
    445b:	72 f1                	jb     444e <gen_dl_ccch_send_rrcsetup+0x78e>
    445d:	c7 85 f8 fe ff ff 01 	movl   $0x1,-0x108(%ebp)
    4464:	00 00 00 
		.transmissionMode = tm3,
		.type_codebookSubsetRestriction = 2,    //1:n2TxAntenna_tm3......
		.codebookSubsetRestriction.n4TxAntenna_tm3 = 2,
		.type_ue_TransmitAntennaSelection = 2,
		.ue_TransmitAntennaSelection.setup = openLoop,
	};
    4467:	8d 4d 90             	lea    -0x70(%ebp),%ecx
    446a:	31 c0                	xor    %eax,%eax
		.cyclicShift = cs1,
	};
	struct SoundingRS_UL_ConfigDedicated soundrs_ul_configdedicated1={              //descripe SoundingRS_UL_ConfigDedicated
		.type = 2,    //1:release, 2:setup
		.choice.setup = soundrs_ul_configdedicate_setup1,
	};
    446c:	c7 85 f4 fe ff ff 01 	movl   $0x1,-0x10c(%ebp)
    4473:	00 00 00 
    4476:	c7 85 f0 fe ff ff 02 	movl   $0x2,-0x110(%ebp)
    447d:	00 00 00 
    4480:	c6 85 ec fe ff ff 01 	movb   $0x1,-0x114(%ebp)
    4487:	c7 85 e8 fe ff ff 02 	movl   $0x2,-0x118(%ebp)
    448e:	00 00 00 
    4491:	c7 85 e4 fe ff ff 00 	movl   $0x0,-0x11c(%ebp)
    4498:	00 00 00 
    449b:	c7 85 e0 fe ff ff 00 	movl   $0x0,-0x120(%ebp)
    44a2:	00 00 00 
		.dsr_TransMax  = dsr_TransMax_n4,
	};
	struct SchedulingRequestConfig schedulingrequestconfig1={                       //descripe  SchedulingRequestConfig
		.type = 2,    //1:release, 2:setup
		.choice.setup = schedulingrequestconfig_setup1,
	};
    44a5:	c7 45 c8 04 00 00 00 	movl   $0x4,-0x38(%ebp)
    44ac:	c7 45 c4 64 00 00 00 	movl   $0x64,-0x3c(%ebp)
    44b3:	c7 45 c0 64 00 00 00 	movl   $0x64,-0x40(%ebp)
		.transmissionMode = tm3,
		.type_codebookSubsetRestriction = 2,    //1:n2TxAntenna_tm3......
		.codebookSubsetRestriction.n4TxAntenna_tm3 = 2,
		.type_ue_TransmitAntennaSelection = 2,
		.ue_TransmitAntennaSelection.setup = openLoop,
	};
    44ba:	c7 04 01 00 00 00 00 	movl   $0x0,(%ecx,%eax,1)
    44c1:	83 c0 04             	add    $0x4,%eax
    44c4:	83 f8 18             	cmp    $0x18,%eax
    44c7:	72 f1                	jb     44ba <gen_dl_ccch_send_rrcsetup+0x7fa>
		.soundingRS_UL_ConfigDedicated = soundrs_ul_configdedicated1,
		.haveAntennaInformationDedicated = true,
		.antennaInfo = antennainformationdedicated1,
		.haveSchedulingRequestConfig = true,
		.schedulingRequestConfig = schedulingrequestconfig1,
	};
    44c9:	31 db                	xor    %ebx,%ebx
    44cb:	b9 36 00 00 00       	mov    $0x36,%ecx
    44d0:	89 d8                	mov    %ebx,%eax
    44d2:	8d bd 28 fc ff ff    	lea    -0x3d8(%ebp),%edi
    44d8:	f3 ab                	rep stos %eax,%es:(%edi)
    44da:	8b 45 ec             	mov    -0x14(%ebp),%eax
		.mac_MainConfig = mac_mainconfig1,
		.haveSPS_Config = true,
		.sps_Config = sps_config1,
		.havePhysicalConfigDedicated = true,
		.physicalConfigDedicated = physicalconfigdedicateed1,
	};
    44dd:	8d bd 78 f4 ff ff    	lea    -0xb88(%ebp),%edi
		.soundingRS_UL_ConfigDedicated = soundrs_ul_configdedicated1,
		.haveAntennaInformationDedicated = true,
		.antennaInfo = antennainformationdedicated1,
		.haveSchedulingRequestConfig = true,
		.schedulingRequestConfig = schedulingrequestconfig1,
	};
    44e3:	c6 85 04 ff ff ff 01 	movb   $0x1,-0xfc(%ebp)
    44ea:	8b 4d e0             	mov    -0x20(%ebp),%ecx
		.transmissionMode = tm3,
		.type_codebookSubsetRestriction = 2,    //1:n2TxAntenna_tm3......
		.codebookSubsetRestriction.n4TxAntenna_tm3 = 2,
		.type_ue_TransmitAntennaSelection = 2,
		.ue_TransmitAntennaSelection.setup = openLoop,
	};
    44ed:	c6 45 98 02          	movb   $0x2,-0x68(%ebp)
    44f1:	c7 45 a4 01 00 00 00 	movl   $0x1,-0x5c(%ebp)
		.soundingRS_UL_ConfigDedicated = soundrs_ul_configdedicated1,
		.haveAntennaInformationDedicated = true,
		.antennaInfo = antennainformationdedicated1,
		.haveSchedulingRequestConfig = true,
		.schedulingRequestConfig = schedulingrequestconfig1,
	};
    44f8:	89 85 38 fc ff ff    	mov    %eax,-0x3c8(%ebp)
    44fe:	8b 45 f0             	mov    -0x10(%ebp),%eax
    4501:	89 8d 74 fc ff ff    	mov    %ecx,-0x38c(%ebp)
    4507:	89 8d 80 fc ff ff    	mov    %ecx,-0x380(%ebp)
		.mac_MainConfig = mac_mainconfig1,
		.haveSPS_Config = true,
		.sps_Config = sps_config1,
		.havePhysicalConfigDedicated = true,
		.physicalConfigDedicated = physicalconfigdedicateed1,
	};
    450d:	b9 3b 01 00 00       	mov    $0x13b,%ecx
		.soundingRS_UL_ConfigDedicated = soundrs_ul_configdedicated1,
		.haveAntennaInformationDedicated = true,
		.antennaInfo = antennainformationdedicated1,
		.haveSchedulingRequestConfig = true,
		.schedulingRequestConfig = schedulingrequestconfig1,
	};
    4512:	c7 45 e8 02 00 00 00 	movl   $0x2,-0x18(%ebp)
    4519:	89 85 3c fc ff ff    	mov    %eax,-0x3c4(%ebp)
    451f:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    4522:	c7 85 34 fc ff ff 02 	movl   $0x2,-0x3cc(%ebp)
    4529:	00 00 00 
    452c:	c7 85 70 fc ff ff 02 	movl   $0x2,-0x390(%ebp)
    4533:	00 00 00 
    4536:	c7 45 dc 02 00 00 00 	movl   $0x2,-0x24(%ebp)
    453d:	89 85 78 fc ff ff    	mov    %eax,-0x388(%ebp)
    4543:	89 85 84 fc ff ff    	mov    %eax,-0x37c(%ebp)
    4549:	8b 85 04 ff ff ff    	mov    -0xfc(%ebp),%eax
    454f:	c7 85 7c fc ff ff 02 	movl   $0x2,-0x384(%ebp)
    4556:	00 00 00 
    4559:	c7 85 fc fe ff ff 14 	movl   $0x14,-0x104(%ebp)
    4560:	00 00 00 
    4563:	c7 85 00 ff ff ff 02 	movl   $0x2,-0x100(%ebp)
    456a:	00 00 00 
    456d:	89 85 94 fc ff ff    	mov    %eax,-0x36c(%ebp)
    4573:	8b 85 08 ff ff ff    	mov    -0xf8(%ebp),%eax
    4579:	c7 85 8c fc ff ff 14 	movl   $0x14,-0x374(%ebp)
    4580:	00 00 00 
    4583:	c7 85 90 fc ff ff 02 	movl   $0x2,-0x370(%ebp)
    458a:	00 00 00 
    458d:	89 85 98 fc ff ff    	mov    %eax,-0x368(%ebp)
    4593:	8b 85 0c ff ff ff    	mov    -0xf4(%ebp),%eax
    4599:	89 85 9c fc ff ff    	mov    %eax,-0x364(%ebp)
    459f:	8b 85 10 ff ff ff    	mov    -0xf0(%ebp),%eax
    45a5:	89 85 a0 fc ff ff    	mov    %eax,-0x360(%ebp)
    45ab:	8b 85 14 ff ff ff    	mov    -0xec(%ebp),%eax
    45b1:	89 85 a4 fc ff ff    	mov    %eax,-0x35c(%ebp)
    45b7:	8b 85 18 ff ff ff    	mov    -0xe8(%ebp),%eax
    45bd:	89 85 a8 fc ff ff    	mov    %eax,-0x358(%ebp)
    45c3:	8b 85 e0 fe ff ff    	mov    -0x120(%ebp),%eax
    45c9:	c7 85 dc fe ff ff 02 	movl   $0x2,-0x124(%ebp)
    45d0:	00 00 00 
    45d3:	c7 85 b0 fc ff ff 02 	movl   $0x2,-0x350(%ebp)
    45da:	00 00 00 
    45dd:	c7 45 90 03 00 00 00 	movl   $0x3,-0x70(%ebp)
    45e4:	89 85 b4 fc ff ff    	mov    %eax,-0x34c(%ebp)
    45ea:	8b 85 e4 fe ff ff    	mov    -0x11c(%ebp),%eax
    45f0:	c7 45 94 02 00 00 00 	movl   $0x2,-0x6c(%ebp)
    45f7:	c7 45 a0 02 00 00 00 	movl   $0x2,-0x60(%ebp)
    45fe:	c7 85 d4 fc ff ff 03 	movl   $0x3,-0x32c(%ebp)
    4605:	00 00 00 
    4608:	89 85 b8 fc ff ff    	mov    %eax,-0x348(%ebp)
    460e:	8b 85 e8 fe ff ff    	mov    -0x118(%ebp),%eax
    4614:	c7 85 d8 fc ff ff 02 	movl   $0x2,-0x328(%ebp)
    461b:	00 00 00 
    461e:	c7 85 e4 fc ff ff 02 	movl   $0x2,-0x31c(%ebp)
    4625:	00 00 00 
    4628:	c7 85 e8 fc ff ff 01 	movl   $0x1,-0x318(%ebp)
    462f:	00 00 00 
    4632:	89 85 bc fc ff ff    	mov    %eax,-0x344(%ebp)
    4638:	8b 85 ec fe ff ff    	mov    -0x114(%ebp),%eax
    463e:	c7 45 bc 02 00 00 00 	movl   $0x2,-0x44(%ebp)
    4645:	c7 85 f0 fc ff ff 02 	movl   $0x2,-0x310(%ebp)
    464c:	00 00 00 
    464f:	89 85 c0 fc ff ff    	mov    %eax,-0x340(%ebp)
    4655:	8b 85 f0 fe ff ff    	mov    -0x110(%ebp),%eax
    465b:	89 85 c4 fc ff ff    	mov    %eax,-0x33c(%ebp)
    4661:	8b 85 f4 fe ff ff    	mov    -0x10c(%ebp),%eax
    4667:	89 85 c8 fc ff ff    	mov    %eax,-0x338(%ebp)
    466d:	8b 85 f8 fe ff ff    	mov    -0x108(%ebp),%eax
    4673:	89 85 cc fc ff ff    	mov    %eax,-0x334(%ebp)
    4679:	8b 45 98             	mov    -0x68(%ebp),%eax
    467c:	89 85 dc fc ff ff    	mov    %eax,-0x324(%ebp)
    4682:	8b 45 9c             	mov    -0x64(%ebp),%eax
    4685:	89 85 e0 fc ff ff    	mov    %eax,-0x320(%ebp)
    468b:	8b 45 c0             	mov    -0x40(%ebp),%eax
    468e:	89 85 f4 fc ff ff    	mov    %eax,-0x30c(%ebp)
    4694:	8b 45 c4             	mov    -0x3c(%ebp),%eax
    4697:	89 85 f8 fc ff ff    	mov    %eax,-0x308(%ebp)
    469d:	8b 45 c8             	mov    -0x38(%ebp),%eax
    46a0:	89 85 fc fc ff ff    	mov    %eax,-0x304(%ebp)
		.mac_MainConfig = mac_mainconfig1,
		.haveSPS_Config = true,
		.sps_Config = sps_config1,
		.havePhysicalConfigDedicated = true,
		.physicalConfigDedicated = physicalconfigdedicateed1,
	};
    46a6:	89 d8                	mov    %ebx,%eax
    46a8:	f3 ab                	rep stos %eax,%es:(%edi)
    46aa:	8d bd 7c f4 ff ff    	lea    -0xb84(%ebp),%edi
    46b0:	c7 85 00 fd ff ff 02 	movl   $0x2,-0x300(%ebp)
    46b7:	00 00 00 
    46ba:	8d 85 f0 f7 ff ff    	lea    -0x810(%ebp),%eax
    46c0:	c7 85 64 f9 ff ff 01 	movl   $0x1,-0x69c(%ebp)
    46c7:	00 00 00 
    46ca:	c6 85 74 fd ff ff 01 	movb   $0x1,-0x28c(%ebp)
    46d1:	c7 85 78 fd ff ff 02 	movl   $0x2,-0x288(%ebp)
    46d8:	00 00 00 
    46db:	c7 85 7c fd ff ff 28 	movl   $0x28,-0x284(%ebp)
    46e2:	00 00 00 
    46e5:	b1 1d                	mov    $0x1d,%cl
    46e7:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    46e9:	89 d6                	mov    %edx,%esi
    46eb:	8d bd f4 f4 ff ff    	lea    -0xb0c(%ebp),%edi
    46f1:	c7 85 80 fd ff ff 80 	movl   $0x280,-0x280(%ebp)
    46f8:	02 00 00 
    46fb:	c6 85 84 fd ff ff 01 	movb   $0x1,-0x27c(%ebp)
    4702:	c6 85 88 fd ff ff 01 	movb   $0x1,-0x278(%ebp)
    4709:	c7 85 b0 fd ff ff 80 	movl   $0x780,-0x250(%ebp)
    4710:	07 00 00 
    4713:	b1 b1                	mov    $0xb1,%cl
    4715:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    4717:	8b b5 84 ef ff ff    	mov    -0x107c(%ebp),%esi
    471d:	89 c7                	mov    %eax,%edi
    471f:	c7 85 b4 fd ff ff 02 	movl   $0x2,-0x24c(%ebp)
    4726:	00 00 00 

	struct RRCConnectionSetup rrcConnectionSetupmsg1 ={
		.rrcTransactionIdentifier = 2,	//pay attention 随意赋值的
		.radioResourceConfigDedicated = set_radioresourcemsg,
	};
    4729:	89 d8                	mov    %ebx,%eax
		.mac_MainConfig = mac_mainconfig1,
		.haveSPS_Config = true,
		.sps_Config = sps_config1,
		.havePhysicalConfigDedicated = true,
		.physicalConfigDedicated = physicalconfigdedicateed1,
	};
    472b:	c6 85 c4 fd ff ff 01 	movb   $0x1,-0x23c(%ebp)
    4732:	66 c7 85 c6 fd ff ff 	movw   $0x4,-0x23a(%ebp)
    4739:	04 00 
    473b:	c6 85 c8 fd ff ff 01 	movb   $0x1,-0x238(%ebp)
    4742:	c6 85 e8 fd ff ff 01 	movb   $0x1,-0x218(%ebp)
    4749:	b1 14                	mov    $0x14,%cl
    474b:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    474d:	8b b5 80 ef ff ff    	mov    -0x1080(%ebp),%esi
    4753:	8d bd 44 f8 ff ff    	lea    -0x7bc(%ebp),%edi
    4759:	c6 85 28 fc ff ff 01 	movb   $0x1,-0x3d8(%ebp)
    4760:	c7 85 2c fc ff ff 01 	movl   $0x1,-0x3d4(%ebp)
    4767:	00 00 00 
    476a:	c6 85 30 fc ff ff 01 	movb   $0x1,-0x3d0(%ebp)
    4771:	c6 85 40 fc ff ff 01 	movb   $0x1,-0x3c0(%ebp)
    4778:	c7 85 44 fc ff ff 02 	movl   $0x2,-0x3bc(%ebp)
    477f:	00 00 00 
    4782:	b1 11                	mov    $0x11,%cl
    4784:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    4786:	8d bd 8c f8 ff ff    	lea    -0x774(%ebp),%edi
    478c:	c7 85 48 fc ff ff 02 	movl   $0x2,-0x3b8(%ebp)
    4793:	00 00 00 
    4796:	8d b5 28 fc ff ff    	lea    -0x3d8(%ebp),%esi
    479c:	c7 85 4c fc ff ff 02 	movl   $0x2,-0x3b4(%ebp)
    47a3:	00 00 00 
    47a6:	c6 85 50 fc ff ff 01 	movb   $0x1,-0x3b0(%ebp)
    47ad:	c7 85 54 fc ff ff 02 	movl   $0x2,-0x3ac(%ebp)
    47b4:	00 00 00 
    47b7:	c7 85 58 fc ff ff 01 	movl   $0x1,-0x3a8(%ebp)
    47be:	00 00 00 
    47c1:	c6 85 5c fc ff ff 01 	movb   $0x1,-0x3a4(%ebp)
    47c8:	b1 36                	mov    $0x36,%cl
    47ca:	c7 85 60 fc ff ff 02 	movl   $0x2,-0x3a0(%ebp)
    47d1:	00 00 00 
    47d4:	c7 85 64 fc ff ff 02 	movl   $0x2,-0x39c(%ebp)
    47db:	00 00 00 
    47de:	c7 85 68 fc ff ff 06 	movl   $0x6,-0x398(%ebp)
    47e5:	00 00 00 
    47e8:	c6 85 6c fc ff ff 01 	movb   $0x1,-0x394(%ebp)
    47ef:	c6 85 88 fc ff ff 01 	movb   $0x1,-0x378(%ebp)
    47f6:	c6 85 ac fc ff ff 01 	movb   $0x1,-0x354(%ebp)
    47fd:	c6 85 d0 fc ff ff 01 	movb   $0x1,-0x330(%ebp)
    4804:	c6 85 ec fc ff ff 01 	movb   $0x1,-0x314(%ebp)
    480b:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)

	struct RRCConnectionSetup rrcConnectionSetupmsg1 ={
		.rrcTransactionIdentifier = 2,	//pay attention 随意赋值的
		.radioResourceConfigDedicated = set_radioresourcemsg,
	};
    480d:	8d bd 88 ef ff ff    	lea    -0x1078(%ebp),%edi
    4813:	c6 85 78 f4 ff ff 01 	movb   $0x1,-0xb88(%ebp)
    481a:	8d b5 78 f4 ff ff    	lea    -0xb88(%ebp),%esi
    4820:	c6 85 f0 f4 ff ff 01 	movb   $0x1,-0xb10(%ebp)
    4827:	c6 85 b8 f7 ff ff 01 	movb   $0x1,-0x848(%ebp)
    482e:	c7 85 bc f7 ff ff 01 	movl   $0x1,-0x844(%ebp)
    4835:	00 00 00 
    4838:	c7 85 c0 f7 ff ff 04 	movl   $0x4,-0x840(%ebp)
    483f:	00 00 00 
    4842:	66 b9 3c 01          	mov    $0x13c,%cx
    4846:	f3 ab                	rep stos %eax,%es:(%edi)
    4848:	8d bd 8c ef ff ff    	lea    -0x1074(%ebp),%edi


	struct DL_CCCH_Message *dl_ccch_rrcsetup = fsm_mem_alloc(sizeof(struct DL_CCCH_Message));
    484e:	66 b8 f4 04          	mov    $0x4f4,%ax
	};

	struct RRCConnectionSetup rrcConnectionSetupmsg1 ={
		.rrcTransactionIdentifier = 2,	//pay attention 随意赋值的
		.radioResourceConfigDedicated = set_radioresourcemsg,
	};
    4852:	c7 85 c4 f7 ff ff 00 	movl   $0x0,-0x83c(%ebp)
    4859:	00 00 00 
    485c:	c7 85 c8 f7 ff ff 00 	movl   $0x0,-0x838(%ebp)
    4863:	00 00 00 
    4866:	c7 85 cc f7 ff ff 00 	movl   $0x0,-0x834(%ebp)
    486d:	00 00 00 
    4870:	c7 85 d0 f7 ff ff 00 	movl   $0x0,-0x830(%ebp)
    4877:	00 00 00 
    487a:	c7 85 d4 f7 ff ff 00 	movl   $0x0,-0x82c(%ebp)
    4881:	00 00 00 
    4884:	c7 85 d8 f7 ff ff 00 	movl   $0x0,-0x828(%ebp)
    488b:	00 00 00 
    488e:	66 b9 3b 01          	mov    $0x13b,%cx
    4892:	c7 85 dc f7 ff ff 00 	movl   $0x0,-0x824(%ebp)
    4899:	00 00 00 
    489c:	c7 85 e0 f7 ff ff 00 	movl   $0x0,-0x820(%ebp)
    48a3:	00 00 00 
    48a6:	c7 85 e4 f7 ff ff 00 	movl   $0x0,-0x81c(%ebp)
    48ad:	00 00 00 
    48b0:	c7 85 e8 f7 ff ff 00 	movl   $0x0,-0x818(%ebp)
    48b7:	00 00 00 
    48ba:	c6 85 ec f7 ff ff 01 	movb   $0x1,-0x814(%ebp)
    48c1:	c6 85 40 f8 ff ff 01 	movb   $0x1,-0x7c0(%ebp)
    48c8:	c6 85 88 f8 ff ff 01 	movb   $0x1,-0x778(%ebp)
    48cf:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    48d1:	c6 85 88 ef ff ff 02 	movb   $0x2,-0x1078(%ebp)


	struct DL_CCCH_Message *dl_ccch_rrcsetup = fsm_mem_alloc(sizeof(struct DL_CCCH_Message));
    48d8:	e8 fc ff ff ff       	call   48d9 <gen_dl_ccch_send_rrcsetup+0xc19>
	dl_ccch_rrcsetup->type = 4;
	fsm_mem_cpy(&(dl_ccch_rrcsetup->msg.rrcConnectionSetup), &rrcConnectionSetupmsg1, sizeof(struct RRCConnectionSetup));
    48dd:	8d 95 88 ef ff ff    	lea    -0x1078(%ebp),%edx
    48e3:	b9 f0 04 00 00       	mov    $0x4f0,%ecx
		.rrcTransactionIdentifier = 2,	//pay attention 随意赋值的
		.radioResourceConfigDedicated = set_radioresourcemsg,
	};


	struct DL_CCCH_Message *dl_ccch_rrcsetup = fsm_mem_alloc(sizeof(struct DL_CCCH_Message));
    48e8:	89 c3                	mov    %eax,%ebx
	dl_ccch_rrcsetup->type = 4;
    48ea:	c7 00 04 00 00 00    	movl   $0x4,(%eax)
	fsm_mem_cpy(&(dl_ccch_rrcsetup->msg.rrcConnectionSetup), &rrcConnectionSetupmsg1, sizeof(struct RRCConnectionSetup));
    48f0:	8d 40 04             	lea    0x4(%eax),%eax
    48f3:	e8 fc ff ff ff       	call   48f4 <gen_dl_ccch_send_rrcsetup+0xc34>
	//dl_ccch_rrcsetup->msg.rrcConnectionSetup = rrcConnectionSetupmsg1;
	return dl_ccch_rrcsetup;
}
    48f8:	89 d8                	mov    %ebx,%eax
    48fa:	8b 75 f8             	mov    -0x8(%ebp),%esi
    48fd:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    4900:	8b 7d fc             	mov    -0x4(%ebp),%edi
    4903:	89 ec                	mov    %ebp,%esp
    4905:	5d                   	pop    %ebp
    4906:	c3                   	ret    
    4907:	89 f6                	mov    %esi,%esi
    4909:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00004910 <gen_ul_ccchmsg_send_rrcquest>:
**Modified by: Xu Shangfei
**Modified date:2014.10.9
****************************************************************/

struct UL_CCCH_Message *gen_ul_ccchmsg_send_rrcquest(void)
{
    4910:	55                   	push   %ebp
    4911:	89 e5                	mov    %esp,%ebp
    4913:	53                   	push   %ebx
    4914:	83 ec 14             	sub    $0x14,%esp
    4917:	e8 fc ff ff ff       	call   4918 <gen_ul_ccchmsg_send_rrcquest+0x8>
		.type = 1,   //type=1:s_TMSI,  type=2:randomValue
		.ue_Identity.s_TMSI = s_tmsi,
		.establishmentCause = mt_Access,
	};

	struct UL_CCCH_Message *send_ulccchmsgRRCreq =  (struct UL_CCCH_Message *)fsm_mem_alloc(sizeof(struct UL_CCCH_Message));
    491c:	b8 0e 00 00 00       	mov    $0xe,%eax
	};
	struct RRCConnectionRequest setrrcrequestmsg={
		.type = 1,   //type=1:s_TMSI,  type=2:randomValue
		.ue_Identity.s_TMSI = s_tmsi,
		.establishmentCause = mt_Access,
	};
    4921:	c6 45 f2 01          	movb   $0x1,-0xe(%ebp)
    4925:	c7 45 f4 40 e2 01 00 	movl   $0x1e240,-0xc(%ebp)
    492c:	c6 45 f3 0b          	movb   $0xb,-0xd(%ebp)
    4930:	c7 45 f8 02 00 00 00 	movl   $0x2,-0x8(%ebp)

	struct UL_CCCH_Message *send_ulccchmsgRRCreq =  (struct UL_CCCH_Message *)fsm_mem_alloc(sizeof(struct UL_CCCH_Message));
    4937:	e8 fc ff ff ff       	call   4938 <gen_ul_ccchmsg_send_rrcquest+0x28>
	send_ulccchmsgRRCreq->type = 2;
	//send_ulccchmsgRRCreq->msg.rrcConnectionRequest = setrrcrequestmsg;
	fsm_mem_cpy(&(send_ulccchmsgRRCreq->msg.rrcConnectionRequest), &setrrcrequestmsg, sizeof(struct RRCConnectionRequest));
    493c:	8d 55 f2             	lea    -0xe(%ebp),%edx
    493f:	b9 0a 00 00 00       	mov    $0xa,%ecx
		.type = 1,   //type=1:s_TMSI,  type=2:randomValue
		.ue_Identity.s_TMSI = s_tmsi,
		.establishmentCause = mt_Access,
	};

	struct UL_CCCH_Message *send_ulccchmsgRRCreq =  (struct UL_CCCH_Message *)fsm_mem_alloc(sizeof(struct UL_CCCH_Message));
    4944:	89 c3                	mov    %eax,%ebx
	send_ulccchmsgRRCreq->type = 2;
    4946:	c7 00 02 00 00 00    	movl   $0x2,(%eax)
	//send_ulccchmsgRRCreq->msg.rrcConnectionRequest = setrrcrequestmsg;
	fsm_mem_cpy(&(send_ulccchmsgRRCreq->msg.rrcConnectionRequest), &setrrcrequestmsg, sizeof(struct RRCConnectionRequest));
    494c:	8d 40 04             	lea    0x4(%eax),%eax
    494f:	e8 fc ff ff ff       	call   4950 <gen_ul_ccchmsg_send_rrcquest+0x40>
	fsm_printf("[rrc] [conn_establish] <-- send setrrcrequestmsg!\n");
    4954:	c7 04 24 58 13 00 00 	movl   $0x1358,(%esp)
    495b:	e8 fc ff ff ff       	call   495c <gen_ul_ccchmsg_send_rrcquest+0x4c>
	fsm_printf("[rrc] [conn_establish] ullccchmsg type=%d \n", send_ulccchmsgRRCreq->type);
    4960:	8b 03                	mov    (%ebx),%eax
    4962:	c7 04 24 8c 13 00 00 	movl   $0x138c,(%esp)
    4969:	89 44 24 04          	mov    %eax,0x4(%esp)
    496d:	e8 fc ff ff ff       	call   496e <gen_ul_ccchmsg_send_rrcquest+0x5e>

	return send_ulccchmsgRRCreq;

}
    4972:	89 d8                	mov    %ebx,%eax
    4974:	83 c4 14             	add    $0x14,%esp
    4977:	5b                   	pop    %ebx
    4978:	5d                   	pop    %ebp
    4979:	c3                   	ret    
    497a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00004980 <gen_sysInfoTimer>:
**Modified by: Xu Shangfei
**Modified date:2014.10.9
*********************************************************************/

struct SystemInformationBlockType2 *gen_sysInfoTimer(void)
{
    4980:	55                   	push   %ebp
    4981:	89 e5                	mov    %esp,%ebp
    4983:	53                   	push   %ebx
    4984:	83 ec 04             	sub    $0x4,%esp
    4987:	e8 fc ff ff ff       	call   4988 <gen_sysInfoTimer+0x8>
	struct TimeAlignmentTimer timeAligment={
		.timeAlignmentTimertype = timeAlignmentTimertype_sf10240 * 100,
	};
	struct SystemInformationBlockType2 *sys2infotimer1 = fsm_mem_alloc(sizeof(struct SystemInformationBlockType2));
    498c:	b8 08 01 00 00       	mov    $0x108,%eax

struct SystemInformationBlockType2 *gen_sysInfoTimer(void)
{
	struct TimeAlignmentTimer timeAligment={
		.timeAlignmentTimertype = timeAlignmentTimertype_sf10240 * 100,
	};
    4991:	c7 45 f8 00 a0 0f 00 	movl   $0xfa000,-0x8(%ebp)
	struct SystemInformationBlockType2 *sys2infotimer1 = fsm_mem_alloc(sizeof(struct SystemInformationBlockType2));
    4998:	e8 fc ff ff ff       	call   4999 <gen_sysInfoTimer+0x19>
	fsm_mem_cpy(&(sys2infotimer1->timeAlignmentTimerCommon), &timeAligment, sizeof(struct TimeAlignmentTimer));
    499d:	8d 55 f8             	lea    -0x8(%ebp),%edx
    49a0:	b9 04 00 00 00       	mov    $0x4,%ecx
struct SystemInformationBlockType2 *gen_sysInfoTimer(void)
{
	struct TimeAlignmentTimer timeAligment={
		.timeAlignmentTimertype = timeAlignmentTimertype_sf10240 * 100,
	};
	struct SystemInformationBlockType2 *sys2infotimer1 = fsm_mem_alloc(sizeof(struct SystemInformationBlockType2));
    49a5:	89 c3                	mov    %eax,%ebx
	fsm_mem_cpy(&(sys2infotimer1->timeAlignmentTimerCommon), &timeAligment, sizeof(struct TimeAlignmentTimer));
    49a7:	8d 80 04 01 00 00    	lea    0x104(%eax),%eax
    49ad:	e8 fc ff ff ff       	call   49ae <gen_sysInfoTimer+0x2e>
	//sys2infotimer1->timeAlignmentTimerCommon = timeAligment;
	//fsm_printf("	set	setsysInfoTimer message   !\n");
	return sys2infotimer1;
}
    49b2:	89 d8                	mov    %ebx,%eax
    49b4:	83 c4 04             	add    $0x4,%esp
    49b7:	5b                   	pop    %ebx
    49b8:	5d                   	pop    %ebp
    49b9:	c3                   	ret    
    49ba:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

000049c0 <gen_Defaultradioresource>:
**-----------------------------------
**Modified by: Xu Shangfei
**Modified date:
****************************************************************/
struct RadioResourceConfigDedicated *gen_Defaultradioresource (void)
{
    49c0:	55                   	push   %ebp
    49c1:	89 e5                	mov    %esp,%ebp
    49c3:	81 ec 74 02 00 00    	sub    $0x274,%esp
    49c9:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    49cc:	89 75 f8             	mov    %esi,-0x8(%ebp)
    49cf:	89 7d fc             	mov    %edi,-0x4(%ebp)
    49d2:	e8 fc ff ff ff       	call   49d3 <gen_Defaultradioresource+0x13>
	struct CQI_ReportConfig Cqi_ReConfig={                                  //描述 CQI报告配置
		.cqi_ReportModeAperiodic = rm12,
		.nomPDSCH_RS_EPRE_Offset = 0,//INTEGER (-1..6)
		.haveCQI_ReportPeriodic = true,
		.cqi_ReportPeriodic = Cqi_Periodic,
	};
    49d7:	31 c0                	xor    %eax,%eax
	};

	struct PUCCH_ConfigDedicated Pucch_ConfigDe={                           //描述UE专用的PUCCH配置
		.type = 3,    //1:release, 2:setup, 3:tddAckNackFeedbackMode
		.ackNackRepetition.tddAckNackFeedbackMode = bundling,
	};
    49d9:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
	struct CQI_ReportConfig Cqi_ReConfig={                                  //描述 CQI报告配置
		.cqi_ReportModeAperiodic = rm12,
		.nomPDSCH_RS_EPRE_Offset = 0,//INTEGER (-1..6)
		.haveCQI_ReportPeriodic = true,
		.cqi_ReportPeriodic = Cqi_Periodic,
	};
    49e0:	8d 95 3c ff ff ff    	lea    -0xc4(%ebp),%edx
	};

	struct PUCCH_ConfigDedicated Pucch_ConfigDe={                           //描述UE专用的PUCCH配置
		.type = 3,    //1:release, 2:setup, 3:tddAckNackFeedbackMode
		.ackNackRepetition.tddAckNackFeedbackMode = bundling,
	};
    49e6:	c7 45 ec 05 00 00 00 	movl   $0x5,-0x14(%ebp)
	};

	struct TPC_PDCCH_Config TPC_pucch={                                     //描述RNTI，以及 PUCCH和PUSCH 功率控制的序号
		.type = 1,    //1:release, 2:setup
		.choice.release = 1,
	};
    49ed:	c7 45 e4 00 00 00 00 	movl   $0x0,-0x1c(%ebp)
    49f4:	c7 45 e0 01 00 00 00 	movl   $0x1,-0x20(%ebp)

	struct TPC_PDCCH_Config TPC_pusch={                                     //描述RNTI，以及 PUCCH和PUSCH 功率控制的序号
		.type = 1,    //1:release, 2:setup
		.choice.release = 1,
	};
    49fb:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%ebp)
    4a02:	c7 45 d4 01 00 00 00 	movl   $0x1,-0x2c(%ebp)

	struct CQI_ReportPeriodic Cqi_Periodic={
		.type = 1,    //1:release, 2:setup, 3:ri_ConfigIndex, 4:simultaneousAckNackAndCQI
		.choice.release = 1,
	};
    4a09:	c7 45 b4 00 00 00 00 	movl   $0x0,-0x4c(%ebp)
    4a10:	c7 45 b8 00 00 00 00 	movl   $0x0,-0x48(%ebp)
    4a17:	c7 45 bc 00 00 00 00 	movl   $0x0,-0x44(%ebp)
    4a1e:	c7 45 b0 01 00 00 00 	movl   $0x1,-0x50(%ebp)
	struct CQI_ReportConfig Cqi_ReConfig={                                  //描述 CQI报告配置
		.cqi_ReportModeAperiodic = rm12,
		.nomPDSCH_RS_EPRE_Offset = 0,//INTEGER (-1..6)
		.haveCQI_ReportPeriodic = true,
		.cqi_ReportPeriodic = Cqi_Periodic,
	};
    4a25:	c7 04 02 00 00 00 00 	movl   $0x0,(%edx,%eax,1)
    4a2c:	83 c0 04             	add    $0x4,%eax
    4a2f:	83 f8 20             	cmp    $0x20,%eax
    4a32:	72 f1                	jb     4a25 <gen_Defaultradioresource+0x65>
    4a34:	8b 45 b0             	mov    -0x50(%ebp),%eax

	struct SoundingRS_UL_ConfigDedicated SRS_UL_CDe={                       //描述上行探测RS配置
		.type = 1,   //1:release, 2:setup
		.choice.release = 1,
	};
    4a37:	8d 95 1c ff ff ff    	lea    -0xe4(%ebp),%edx
	struct CQI_ReportConfig Cqi_ReConfig={                                  //描述 CQI报告配置
		.cqi_ReportModeAperiodic = rm12,
		.nomPDSCH_RS_EPRE_Offset = 0,//INTEGER (-1..6)
		.haveCQI_ReportPeriodic = true,
		.cqi_ReportPeriodic = Cqi_Periodic,
	};
    4a3d:	c7 45 ac 01 00 00 00 	movl   $0x1,-0x54(%ebp)
    4a44:	c7 85 48 ff ff ff 01 	movl   $0x1,-0xb8(%ebp)
    4a4b:	00 00 00 
    4a4e:	89 85 4c ff ff ff    	mov    %eax,-0xb4(%ebp)
    4a54:	8b 45 b4             	mov    -0x4c(%ebp),%eax
    4a57:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%ebp)
    4a5d:	8b 45 b8             	mov    -0x48(%ebp),%eax
    4a60:	89 85 54 ff ff ff    	mov    %eax,-0xac(%ebp)
    4a66:	8b 45 bc             	mov    -0x44(%ebp),%eax
    4a69:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%ebp)

	struct SoundingRS_UL_ConfigDedicated SRS_UL_CDe={                       //描述上行探测RS配置
		.type = 1,   //1:release, 2:setup
		.choice.release = 1,
	};
    4a6f:	31 c0                	xor    %eax,%eax
    4a71:	c7 04 02 00 00 00 00 	movl   $0x0,(%edx,%eax,1)
    4a78:	83 c0 04             	add    $0x4,%eax
    4a7b:	83 f8 20             	cmp    $0x20,%eax
    4a7e:	72 f1                	jb     4a71 <gen_Defaultradioresource+0xb1>
    4a80:	c7 85 20 ff ff ff 01 	movl   $0x1,-0xe0(%ebp)
    4a87:	00 00 00 
		.transmissionMode=tm1,
        .type_codebookSubsetRestriction = 1,    //1:n2TxAntenna_tm3......
		.codebookSubsetRestriction= {0},
		.type_ue_TransmitAntennaSelection = 1,
		.ue_TransmitAntennaSelection.release = 1,
	};
    4a8a:	8d 55 94             	lea    -0x6c(%ebp),%edx
    4a8d:	31 c0                	xor    %eax,%eax
    4a8f:	c7 04 02 00 00 00 00 	movl   $0x0,(%edx,%eax,1)
    4a96:	83 c0 04             	add    $0x4,%eax
    4a99:	83 f8 18             	cmp    $0x18,%eax
    4a9c:	72 f1                	jb     4a8f <gen_Defaultradioresource+0xcf>
		.soundingRS_UL_ConfigDedicated = SRS_UL_CDe,
		.haveAntennaInformationDedicated = true,
		.antennaInfo = AnteInfoDe,
		.haveSchedulingRequestConfig = true,
		.schedulingRequestConfig = ScheduReConfig,
	};
    4a9e:	8d b5 8c fd ff ff    	lea    -0x274(%ebp),%esi
    4aa4:	31 c0                	xor    %eax,%eax
    4aa6:	b9 36 00 00 00       	mov    $0x36,%ecx
    4aab:	89 f7                	mov    %esi,%edi
    4aad:	f3 ab                	rep stos %eax,%es:(%edi)
    4aaf:	8b 45 ec             	mov    -0x14(%ebp),%eax

	struct SPS_ConfigDL sps_dl={
		.type = 1,   //1:release, 2:setup
		.choice.release = 1,
	};
    4ab2:	8d 95 78 ff ff ff    	lea    -0x88(%ebp),%edx
		.transmissionMode=tm1,
        .type_codebookSubsetRestriction = 1,    //1:n2TxAntenna_tm3......
		.codebookSubsetRestriction= {0},
		.type_ue_TransmitAntennaSelection = 1,
		.ue_TransmitAntennaSelection.release = 1,
	};
    4ab8:	c7 45 a8 01 00 00 00 	movl   $0x1,-0x58(%ebp)

	struct SchedulingRequestConfig ScheduReConfig={                         //描述调度请求相关的参数
		.type = 1,   //1:release, 2:setup
		.choice.release = 1,
	};
    4abf:	c7 45 c8 00 00 00 00 	movl   $0x0,-0x38(%ebp)
    4ac6:	c7 45 cc 00 00 00 00 	movl   $0x0,-0x34(%ebp)
		.soundingRS_UL_ConfigDedicated = SRS_UL_CDe,
		.haveAntennaInformationDedicated = true,
		.antennaInfo = AnteInfoDe,
		.haveSchedulingRequestConfig = true,
		.schedulingRequestConfig = ScheduReConfig,
	};
    4acd:	89 85 9c fd ff ff    	mov    %eax,-0x264(%ebp)
    4ad3:	8b 45 f0             	mov    -0x10(%ebp),%eax
	};

	struct SchedulingRequestConfig ScheduReConfig={                         //描述调度请求相关的参数
		.type = 1,   //1:release, 2:setup
		.choice.release = 1,
	};
    4ad6:	c7 45 c4 01 00 00 00 	movl   $0x1,-0x3c(%ebp)
		.soundingRS_UL_ConfigDedicated = SRS_UL_CDe,
		.haveAntennaInformationDedicated = true,
		.antennaInfo = AnteInfoDe,
		.haveSchedulingRequestConfig = true,
		.schedulingRequestConfig = ScheduReConfig,
	};
    4add:	c6 85 8c fd ff ff 01 	movb   $0x1,-0x274(%ebp)
    4ae4:	c6 85 94 fd ff ff 01 	movb   $0x1,-0x26c(%ebp)
    4aeb:	89 85 a0 fd ff ff    	mov    %eax,-0x260(%ebp)
    4af1:	8b 45 e0             	mov    -0x20(%ebp),%eax
    4af4:	c7 45 e8 03 00 00 00 	movl   $0x3,-0x18(%ebp)
    4afb:	c7 85 98 fd ff ff 03 	movl   $0x3,-0x268(%ebp)
    4b02:	00 00 00 
    4b05:	c6 85 a4 fd ff ff 01 	movb   $0x1,-0x25c(%ebp)
    4b0c:	89 85 d8 fd ff ff    	mov    %eax,-0x228(%ebp)
    4b12:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    4b15:	c7 85 b0 fd ff ff 0f 	movl   $0xf,-0x250(%ebp)
    4b1c:	00 00 00 
    4b1f:	c7 85 ac fd ff ff 0c 	movl   $0xc,-0x254(%ebp)
    4b26:	00 00 00 
    4b29:	c7 85 a8 fd ff ff 0a 	movl   $0xa,-0x258(%ebp)
    4b30:	00 00 00 
    4b33:	89 85 dc fd ff ff    	mov    %eax,-0x224(%ebp)
    4b39:	8b 45 d4             	mov    -0x2c(%ebp),%eax
    4b3c:	c6 85 b4 fd ff ff 01 	movb   $0x1,-0x24c(%ebp)
    4b43:	c7 85 cc fd ff ff 04 	movl   $0x4,-0x234(%ebp)
    4b4a:	00 00 00 
    4b4d:	c7 85 c8 fd ff ff 07 	movl   $0x7,-0x238(%ebp)
    4b54:	00 00 00 
    4b57:	89 85 e4 fd ff ff    	mov    %eax,-0x21c(%ebp)
    4b5d:	8b 45 d8             	mov    -0x28(%ebp),%eax
    4b60:	c6 85 d0 fd ff ff 01 	movb   $0x1,-0x230(%ebp)
    4b67:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%ebp)
    4b6e:	c7 85 d4 fd ff ff 01 	movl   $0x1,-0x22c(%ebp)
    4b75:	00 00 00 
    4b78:	89 85 e8 fd ff ff    	mov    %eax,-0x218(%ebp)
    4b7e:	c7 45 d0 01 00 00 00 	movl   $0x1,-0x30(%ebp)
    4b85:	c7 85 e0 fd ff ff 01 	movl   $0x1,-0x220(%ebp)
    4b8c:	00 00 00 
    4b8f:	c6 85 ec fd ff ff 01 	movb   $0x1,-0x214(%ebp)
    4b96:	8b 85 40 ff ff ff    	mov    -0xc0(%ebp),%eax
    4b9c:	c6 85 44 ff ff ff 01 	movb   $0x1,-0xbc(%ebp)
    4ba3:	c7 85 3c ff ff ff 0c 	movl   $0xc,-0xc4(%ebp)
    4baa:	00 00 00 
    4bad:	c7 85 f0 fd ff ff 0c 	movl   $0xc,-0x210(%ebp)
    4bb4:	00 00 00 
    4bb7:	89 85 f4 fd ff ff    	mov    %eax,-0x20c(%ebp)
    4bbd:	8b 85 44 ff ff ff    	mov    -0xbc(%ebp),%eax
    4bc3:	c6 85 10 fe ff ff 01 	movb   $0x1,-0x1f0(%ebp)
    4bca:	c7 85 1c ff ff ff 01 	movl   $0x1,-0xe4(%ebp)
    4bd1:	00 00 00 
    4bd4:	c7 85 14 fe ff ff 01 	movl   $0x1,-0x1ec(%ebp)
    4bdb:	00 00 00 
    4bde:	89 85 f8 fd ff ff    	mov    %eax,-0x208(%ebp)
    4be4:	8b 85 48 ff ff ff    	mov    -0xb8(%ebp),%eax
    4bea:	89 85 fc fd ff ff    	mov    %eax,-0x204(%ebp)
    4bf0:	8b 85 4c ff ff ff    	mov    -0xb4(%ebp),%eax
    4bf6:	89 85 00 fe ff ff    	mov    %eax,-0x200(%ebp)
    4bfc:	8b 85 50 ff ff ff    	mov    -0xb0(%ebp),%eax
    4c02:	89 85 04 fe ff ff    	mov    %eax,-0x1fc(%ebp)
    4c08:	8b 85 54 ff ff ff    	mov    -0xac(%ebp),%eax
    4c0e:	89 85 08 fe ff ff    	mov    %eax,-0x1f8(%ebp)
    4c14:	8b 85 58 ff ff ff    	mov    -0xa8(%ebp),%eax
    4c1a:	89 85 0c fe ff ff    	mov    %eax,-0x1f4(%ebp)
    4c20:	8b 85 20 ff ff ff    	mov    -0xe0(%ebp),%eax
    4c26:	89 85 18 fe ff ff    	mov    %eax,-0x1e8(%ebp)
    4c2c:	8b 85 24 ff ff ff    	mov    -0xdc(%ebp),%eax
    4c32:	89 85 1c fe ff ff    	mov    %eax,-0x1e4(%ebp)
    4c38:	8b 85 28 ff ff ff    	mov    -0xd8(%ebp),%eax
    4c3e:	89 85 20 fe ff ff    	mov    %eax,-0x1e0(%ebp)
    4c44:	8b 85 2c ff ff ff    	mov    -0xd4(%ebp),%eax
    4c4a:	89 85 24 fe ff ff    	mov    %eax,-0x1dc(%ebp)
    4c50:	8b 85 30 ff ff ff    	mov    -0xd0(%ebp),%eax
    4c56:	89 85 28 fe ff ff    	mov    %eax,-0x1d8(%ebp)
    4c5c:	8b 85 34 ff ff ff    	mov    -0xcc(%ebp),%eax
    4c62:	89 85 2c fe ff ff    	mov    %eax,-0x1d4(%ebp)
    4c68:	8b 85 38 ff ff ff    	mov    -0xc8(%ebp),%eax
    4c6e:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%ebp)
    4c74:	8b 45 9c             	mov    -0x64(%ebp),%eax
    4c77:	c6 85 34 fe ff ff 01 	movb   $0x1,-0x1cc(%ebp)
    4c7e:	c7 45 94 01 00 00 00 	movl   $0x1,-0x6c(%ebp)
    4c85:	c7 45 98 01 00 00 00 	movl   $0x1,-0x68(%ebp)
    4c8c:	89 85 40 fe ff ff    	mov    %eax,-0x1c0(%ebp)
    4c92:	8b 45 a0             	mov    -0x60(%ebp),%eax
    4c95:	c7 45 a4 01 00 00 00 	movl   $0x1,-0x5c(%ebp)
    4c9c:	c7 85 38 fe ff ff 01 	movl   $0x1,-0x1c8(%ebp)
    4ca3:	00 00 00 
    4ca6:	c7 85 3c fe ff ff 01 	movl   $0x1,-0x1c4(%ebp)
    4cad:	00 00 00 
    4cb0:	89 85 44 fe ff ff    	mov    %eax,-0x1bc(%ebp)

	struct SPS_ConfigDL sps_dl={
		.type = 1,   //1:release, 2:setup
		.choice.release = 1,
	};
    4cb6:	31 c0                	xor    %eax,%eax
		.soundingRS_UL_ConfigDedicated = SRS_UL_CDe,
		.haveAntennaInformationDedicated = true,
		.antennaInfo = AnteInfoDe,
		.haveSchedulingRequestConfig = true,
		.schedulingRequestConfig = ScheduReConfig,
	};
    4cb8:	c7 85 48 fe ff ff 01 	movl   $0x1,-0x1b8(%ebp)
    4cbf:	00 00 00 
    4cc2:	c7 85 4c fe ff ff 01 	movl   $0x1,-0x1b4(%ebp)
    4cc9:	00 00 00 
    4ccc:	c6 85 50 fe ff ff 01 	movb   $0x1,-0x1b0(%ebp)
    4cd3:	c7 45 c0 01 00 00 00 	movl   $0x1,-0x40(%ebp)
    4cda:	c7 85 54 fe ff ff 01 	movl   $0x1,-0x1ac(%ebp)
    4ce1:	00 00 00 
    4ce4:	c7 85 58 fe ff ff 01 	movl   $0x1,-0x1a8(%ebp)
    4ceb:	00 00 00 

	struct SPS_ConfigDL sps_dl={
		.type = 1,   //1:release, 2:setup
		.choice.release = 1,
	};
    4cee:	c7 04 02 00 00 00 00 	movl   $0x0,(%edx,%eax,1)
    4cf5:	83 c0 04             	add    $0x4,%eax
    4cf8:	83 f8 1c             	cmp    $0x1c,%eax
    4cfb:	72 f1                	jb     4cee <gen_Defaultradioresource+0x32e>
    4cfd:	c7 85 7c ff ff ff 01 	movl   $0x1,-0x84(%ebp)
    4d04:	00 00 00 
	struct SPS_ConfigUL sps_ul={
		.type = 1,    //1:release, 2:setup
		.choice.release = 1,
	};
    4d07:	8d 95 5c ff ff ff    	lea    -0xa4(%ebp),%edx
    4d0d:	31 c0                	xor    %eax,%eax
    4d0f:	c7 04 02 00 00 00 00 	movl   $0x0,(%edx,%eax,1)
    4d16:	83 c0 04             	add    $0x4,%eax
    4d19:	83 f8 1c             	cmp    $0x1c,%eax
    4d1c:	72 f1                	jb     4d0f <gen_Defaultradioresource+0x34f>
	struct SPS_Config set_spsconfig={
		.haveSPS_ConfigDL = true,
		.sps_ConfigDL = sps_dl,
		.haveSPS_ConfigUL = true,
		.sps_ConfigUL = sps_ul,
	};
    4d1e:	8d 95 b4 fe ff ff    	lea    -0x14c(%ebp),%edx
    4d24:	31 c0                	xor    %eax,%eax
    4d26:	89 d7                	mov    %edx,%edi
    4d28:	8b 95 7c ff ff ff    	mov    -0x84(%ebp),%edx
    4d2e:	b9 11 00 00 00       	mov    $0x11,%ecx
    4d33:	f3 ab                	rep stos %eax,%es:(%edi)
		.choice.release = 1,
	};
	struct SPS_ConfigUL sps_ul={
		.type = 1,    //1:release, 2:setup
		.choice.release = 1,
	};
    4d35:	c7 85 60 ff ff ff 01 	movl   $0x1,-0xa0(%ebp)
    4d3c:	00 00 00 
	struct SPS_Config set_spsconfig={
		.haveSPS_ConfigDL = true,
		.sps_ConfigDL = sps_dl,
		.haveSPS_ConfigUL = true,
		.sps_ConfigUL = sps_ul,
	};
    4d3f:	c6 85 b8 fe ff ff 01 	movb   $0x1,-0x148(%ebp)
    4d46:	89 95 c0 fe ff ff    	mov    %edx,-0x140(%ebp)
    4d4c:	8b 55 80             	mov    -0x80(%ebp),%edx
    4d4f:	c7 85 78 ff ff ff 01 	movl   $0x1,-0x88(%ebp)
    4d56:	00 00 00 
    4d59:	c7 85 bc fe ff ff 01 	movl   $0x1,-0x144(%ebp)
    4d60:	00 00 00 
	};

	struct DRX_Config drxconfig={
		.type = 1,    //1:release, 2:setup
		.choice.release = 1,
	};
    4d63:	b1 09                	mov    $0x9,%cl
	struct SPS_Config set_spsconfig={
		.haveSPS_ConfigDL = true,
		.sps_ConfigDL = sps_dl,
		.haveSPS_ConfigUL = true,
		.sps_ConfigUL = sps_ul,
	};
    4d65:	89 95 c4 fe ff ff    	mov    %edx,-0x13c(%ebp)
    4d6b:	8b 55 84             	mov    -0x7c(%ebp),%edx
    4d6e:	c6 85 d8 fe ff ff 01 	movb   $0x1,-0x128(%ebp)
    4d75:	c7 85 5c ff ff ff 01 	movl   $0x1,-0xa4(%ebp)
    4d7c:	00 00 00 
    4d7f:	c7 85 dc fe ff ff 01 	movl   $0x1,-0x124(%ebp)
    4d86:	00 00 00 
    4d89:	89 95 c8 fe ff ff    	mov    %edx,-0x138(%ebp)
    4d8f:	8b 55 88             	mov    -0x78(%ebp),%edx
    4d92:	c7 85 e0 fe ff ff 01 	movl   $0x1,-0x120(%ebp)
    4d99:	00 00 00 
    4d9c:	89 95 cc fe ff ff    	mov    %edx,-0x134(%ebp)
    4da2:	8b 55 8c             	mov    -0x74(%ebp),%edx
    4da5:	89 95 d0 fe ff ff    	mov    %edx,-0x130(%ebp)
    4dab:	8b 55 90             	mov    -0x70(%ebp),%edx
    4dae:	89 95 d4 fe ff ff    	mov    %edx,-0x12c(%ebp)
    4db4:	8b 95 64 ff ff ff    	mov    -0x9c(%ebp),%edx
    4dba:	89 95 e4 fe ff ff    	mov    %edx,-0x11c(%ebp)
    4dc0:	8b 95 68 ff ff ff    	mov    -0x98(%ebp),%edx
    4dc6:	89 95 e8 fe ff ff    	mov    %edx,-0x118(%ebp)
    4dcc:	8b 95 6c ff ff ff    	mov    -0x94(%ebp),%edx
    4dd2:	89 95 ec fe ff ff    	mov    %edx,-0x114(%ebp)
    4dd8:	8b 95 70 ff ff ff    	mov    -0x90(%ebp),%edx
    4dde:	89 95 f0 fe ff ff    	mov    %edx,-0x110(%ebp)
    4de4:	8b 95 74 ff ff ff    	mov    -0x8c(%ebp),%edx
    4dea:	89 95 f4 fe ff ff    	mov    %edx,-0x10c(%ebp)
	};

	struct DRX_Config drxconfig={
		.type = 1,    //1:release, 2:setup
		.choice.release = 1,
	};
    4df0:	8d 95 f8 fe ff ff    	lea    -0x108(%ebp),%edx
    4df6:	89 d7                	mov    %edx,%edi
    4df8:	f3 ab                	rep stos %eax,%es:(%edi)
		.ul_SCH_Config = ul_sch_config,
		.haveDRX_Config = true,
		.drx_Config = drxconfig,
		.type = 1,    //1:release, 2:setup
		.phr_Config.release = 1,
	};
    4dfa:	8d 95 64 fe ff ff    	lea    -0x19c(%ebp),%edx
    4e00:	89 d7                	mov    %edx,%edi
	};

	struct DRX_Config drxconfig={
		.type = 1,    //1:release, 2:setup
		.choice.release = 1,
	};
    4e02:	c7 85 fc fe ff ff 01 	movl   $0x1,-0x104(%ebp)
    4e09:	00 00 00 
		.ul_SCH_Config = ul_sch_config,
		.haveDRX_Config = true,
		.drx_Config = drxconfig,
		.type = 1,    //1:release, 2:setup
		.phr_Config.release = 1,
	};
    4e0c:	b1 14                	mov    $0x14,%cl
    4e0e:	f3 ab                	rep stos %eax,%es:(%edi)
	//set default radioresource
	struct RadioResourceConfigDedicated *defaultRadioresource1 = fsm_mem_alloc(sizeof(struct RadioResourceConfigDedicated));
    4e10:	66 b8 ec 04          	mov    $0x4ec,%ax
		.ul_SCH_Config = ul_sch_config,
		.haveDRX_Config = true,
		.drx_Config = drxconfig,
		.type = 1,    //1:release, 2:setup
		.phr_Config.release = 1,
	};
    4e14:	c6 85 64 fe ff ff 01 	movb   $0x1,-0x19c(%ebp)
    4e1b:	c7 85 70 fe ff ff 00 	movl   $0xa00,-0x190(%ebp)
    4e22:	0a 00 00 
    4e25:	c7 85 6c fe ff ff ff 	movl   $0xffffffff,-0x194(%ebp)
    4e2c:	ff ff ff 
    4e2f:	c7 85 68 fe ff ff 05 	movl   $0x5,-0x198(%ebp)
    4e36:	00 00 00 
    4e39:	c6 85 78 fe ff ff 01 	movb   $0x1,-0x188(%ebp)
    4e40:	c7 85 f8 fe ff ff 01 	movl   $0x1,-0x108(%ebp)
    4e47:	00 00 00 
    4e4a:	c7 85 7c fe ff ff 01 	movl   $0x1,-0x184(%ebp)
    4e51:	00 00 00 
    4e54:	c7 85 80 fe ff ff 01 	movl   $0x1,-0x180(%ebp)
    4e5b:	00 00 00 
    4e5e:	c7 85 84 fe ff ff 00 	movl   $0x0,-0x17c(%ebp)
    4e65:	00 00 00 
    4e68:	c7 85 88 fe ff ff 00 	movl   $0x0,-0x178(%ebp)
    4e6f:	00 00 00 
    4e72:	c7 85 8c fe ff ff 00 	movl   $0x0,-0x174(%ebp)
    4e79:	00 00 00 
    4e7c:	c7 85 90 fe ff ff 00 	movl   $0x0,-0x170(%ebp)
    4e83:	00 00 00 
    4e86:	c7 85 94 fe ff ff 00 	movl   $0x0,-0x16c(%ebp)
    4e8d:	00 00 00 
    4e90:	c7 85 98 fe ff ff 00 	movl   $0x0,-0x168(%ebp)
    4e97:	00 00 00 
    4e9a:	c7 85 9c fe ff ff 00 	movl   $0x0,-0x164(%ebp)
    4ea1:	00 00 00 
    4ea4:	c7 85 a4 fe ff ff 01 	movl   $0x1,-0x15c(%ebp)
    4eab:	00 00 00 
    4eae:	c7 85 a8 fe ff ff 01 	movl   $0x1,-0x158(%ebp)
    4eb5:	00 00 00 
	//set default radioresource
	struct RadioResourceConfigDedicated *defaultRadioresource1 = fsm_mem_alloc(sizeof(struct RadioResourceConfigDedicated));
    4eb8:	e8 fc ff ff ff       	call   4eb9 <gen_Defaultradioresource+0x4f9>
	defaultRadioresource1->haveDrbToAddModList = false;
	//defaultRadioresource1->drbToAddModList = {0};
	defaultRadioresource1->haveDrbToReleaseList = false;
	//defaultRadioresource1->drbToReleaseList = {0};
	defaultRadioresource1->haveMAC_MainConfig = true;
	fsm_mem_cpy(&(defaultRadioresource1->mac_MainConfig), &set_macmainconfig, sizeof(struct MAC_MainConfig));
    4ebd:	8d 95 64 fe ff ff    	lea    -0x19c(%ebp),%edx
    4ec3:	b9 50 00 00 00       	mov    $0x50,%ecx
		.drx_Config = drxconfig,
		.type = 1,    //1:release, 2:setup
		.phr_Config.release = 1,
	};
	//set default radioresource
	struct RadioResourceConfigDedicated *defaultRadioresource1 = fsm_mem_alloc(sizeof(struct RadioResourceConfigDedicated));
    4ec8:	89 c3                	mov    %eax,%ebx
	defaultRadioresource1->haveSrbToAddModList = false;
    4eca:	c6 00 00             	movb   $0x0,(%eax)
	//defaultRadioresource1->srbToAddModList = {0};
	defaultRadioresource1->haveDrbToAddModList = false;
    4ecd:	c6 40 78 00          	movb   $0x0,0x78(%eax)
	//defaultRadioresource1->drbToAddModList = {0};
	defaultRadioresource1->haveDrbToReleaseList = false;
    4ed1:	c6 80 40 03 00 00 00 	movb   $0x0,0x340(%eax)
	//defaultRadioresource1->drbToReleaseList = {0};
	defaultRadioresource1->haveMAC_MainConfig = true;
    4ed8:	c6 80 74 03 00 00 01 	movb   $0x1,0x374(%eax)
	fsm_mem_cpy(&(defaultRadioresource1->mac_MainConfig), &set_macmainconfig, sizeof(struct MAC_MainConfig));
    4edf:	8d 80 78 03 00 00    	lea    0x378(%eax),%eax
    4ee5:	e8 fc ff ff ff       	call   4ee6 <gen_Defaultradioresource+0x526>
	//defaultRadioresource1->mac_MainConfig = set_macmainconfig;       //mac_MainConfig==null means use default config
	defaultRadioresource1->haveSPS_Config = true;
	fsm_mem_cpy(&(defaultRadioresource1->sps_Config), &set_spsconfig, sizeof(struct SPS_Config));
    4eea:	8d 95 b4 fe ff ff    	lea    -0x14c(%ebp),%edx
    4ef0:	b9 44 00 00 00       	mov    $0x44,%ecx
	defaultRadioresource1->haveDrbToReleaseList = false;
	//defaultRadioresource1->drbToReleaseList = {0};
	defaultRadioresource1->haveMAC_MainConfig = true;
	fsm_mem_cpy(&(defaultRadioresource1->mac_MainConfig), &set_macmainconfig, sizeof(struct MAC_MainConfig));
	//defaultRadioresource1->mac_MainConfig = set_macmainconfig;       //mac_MainConfig==null means use default config
	defaultRadioresource1->haveSPS_Config = true;
    4ef5:	c6 83 c8 03 00 00 01 	movb   $0x1,0x3c8(%ebx)
	fsm_mem_cpy(&(defaultRadioresource1->sps_Config), &set_spsconfig, sizeof(struct SPS_Config));
    4efc:	8d 83 cc 03 00 00    	lea    0x3cc(%ebx),%eax
    4f02:	e8 fc ff ff ff       	call   4f03 <gen_Defaultradioresource+0x543>
	//defaultRadioresource1->sps_Config = set_spsconfig;
	defaultRadioresource1->havePhysicalConfigDedicated = true;
	fsm_mem_cpy(&(defaultRadioresource1->physicalConfigDedicated), &set_phyconfigdedicated, sizeof(struct SPS_Config));
    4f07:	8d 83 14 04 00 00    	lea    0x414(%ebx),%eax
    4f0d:	89 f2                	mov    %esi,%edx
	fsm_mem_cpy(&(defaultRadioresource1->mac_MainConfig), &set_macmainconfig, sizeof(struct MAC_MainConfig));
	//defaultRadioresource1->mac_MainConfig = set_macmainconfig;       //mac_MainConfig==null means use default config
	defaultRadioresource1->haveSPS_Config = true;
	fsm_mem_cpy(&(defaultRadioresource1->sps_Config), &set_spsconfig, sizeof(struct SPS_Config));
	//defaultRadioresource1->sps_Config = set_spsconfig;
	defaultRadioresource1->havePhysicalConfigDedicated = true;
    4f0f:	c6 83 10 04 00 00 01 	movb   $0x1,0x410(%ebx)
	fsm_mem_cpy(&(defaultRadioresource1->physicalConfigDedicated), &set_phyconfigdedicated, sizeof(struct SPS_Config));
    4f16:	b9 44 00 00 00       	mov    $0x44,%ecx
    4f1b:	e8 fc ff ff ff       	call   4f1c <gen_Defaultradioresource+0x55c>
	//defaultRadioresource1->physicalConfigDedicated = set_phyconfigdedicated;
	return defaultRadioresource1;
}
    4f20:	89 d8                	mov    %ebx,%eax
    4f22:	8b 75 f8             	mov    -0x8(%ebp),%esi
    4f25:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    4f28:	8b 7d fc             	mov    -0x4(%ebp),%edi
    4f2b:	89 ec                	mov    %ebp,%esp
    4f2d:	5d                   	pop    %ebp
    4f2e:	c3                   	ret    
    4f2f:	90                   	nop

00004f30 <DoSendRrcConnectionReconfigurationCompleted>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void DoSendRrcConnectionReconfigurationCompleted(struct RRCConnectionReconfigurationComplete reconfigcompletemsg)
{
    4f30:	55                   	push   %ebp
    4f31:	89 e5                	mov    %esp,%ebp
    4f33:	53                   	push   %ebx
    4f34:	83 ec 04             	sub    $0x4,%esp
    4f37:	e8 fc ff ff ff       	call   4f38 <DoSendRrcConnectionReconfigurationCompleted+0x8>
    4f3c:	89 c3                	mov    %eax,%ebx
	FIN(DoSendRrcConnectionReconfigurationCompleted());
	struct UL_DCCH_Message *ul_DCCH_Message;
	int message_type;

	ul_DCCH_Message = (struct UL_DCCH_Message *) fsm_mem_alloc(sizeof(struct UL_DCCH_Message));
    4f3e:	b8 28 00 00 00       	mov    $0x28,%eax
    4f43:	e8 fc ff ff ff       	call   4f44 <DoSendRrcConnectionReconfigurationCompleted+0x14>
	ul_DCCH_Message->type = 2;
	ul_DCCH_Message->msg.rrcConnectionReconfigurationComplete = reconfigcompletemsg;

	message_type = 6;
	packet_send_to_pdcp(ul_DCCH_Message, sizeof(struct UL_DCCH_Message), message_type);
    4f48:	b9 06 00 00 00       	mov    $0x6,%ecx
    4f4d:	ba 28 00 00 00       	mov    $0x28,%edx
	struct UL_DCCH_Message *ul_DCCH_Message;
	int message_type;

	ul_DCCH_Message = (struct UL_DCCH_Message *) fsm_mem_alloc(sizeof(struct UL_DCCH_Message));
	ul_DCCH_Message->type = 2;
	ul_DCCH_Message->msg.rrcConnectionReconfigurationComplete = reconfigcompletemsg;
    4f52:	88 58 04             	mov    %bl,0x4(%eax)
	FIN(DoSendRrcConnectionReconfigurationCompleted());
	struct UL_DCCH_Message *ul_DCCH_Message;
	int message_type;

	ul_DCCH_Message = (struct UL_DCCH_Message *) fsm_mem_alloc(sizeof(struct UL_DCCH_Message));
	ul_DCCH_Message->type = 2;
    4f55:	c7 00 02 00 00 00    	movl   $0x2,(%eax)
	ul_DCCH_Message->msg.rrcConnectionReconfigurationComplete = reconfigcompletemsg;

	message_type = 6;
	packet_send_to_pdcp(ul_DCCH_Message, sizeof(struct UL_DCCH_Message), message_type);
    4f5b:	e8 fc ff ff ff       	call   4f5c <DoSendRrcConnectionReconfigurationCompleted+0x2c>
//	fsm_mem_free(ul_DCCH_Message);
	fsm_printf("[rrc] [fsm] UE Reconfig finished!\n");
    4f60:	c7 04 24 b8 13 00 00 	movl   $0x13b8,(%esp)
    4f67:	e8 fc ff ff ff       	call   4f68 <DoSendRrcConnectionReconfigurationCompleted+0x38>
	FOUT;
}
    4f6c:	83 c4 04             	add    $0x4,%esp
    4f6f:	5b                   	pop    %ebx
    4f70:	5d                   	pop    %ebp
    4f71:	c3                   	ret    
    4f72:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    4f79:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00004f80 <SetRrcConnReconfigmessage>:
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
//set rrc conn reconfig message for test
struct RRCConnectionReconfiguration *SetRrcConnReconfigmessage(void)
{		
    4f80:	55                   	push   %ebp
    4f81:	89 e5                	mov    %esp,%ebp
    4f83:	81 ec 00 09 00 00    	sub    $0x900,%esp
    4f89:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    4f8c:	89 75 f8             	mov    %esi,-0x8(%ebp)
    4f8f:	89 7d fc             	mov    %edi,-0x4(%ebp)
    4f92:	e8 fc ff ff ff       	call   4f93 <SetRrcConnReconfigmessage+0x13>
	struct RlcConfig rlcConfig={
		.type=1,
		.rlcConfigType={0},
	};
    4f97:	31 c0                	xor    %eax,%eax
    4f99:	8d 55 d8             	lea    -0x28(%ebp),%edx
    4f9c:	c7 04 02 00 00 00 00 	movl   $0x0,(%edx,%eax,1)
    4fa3:	83 c0 04             	add    $0x4,%eax
    4fa6:	83 f8 1c             	cmp    $0x1c,%eax
    4fa9:	72 f1                	jb     4f9c <SetRrcConnReconfigmessage+0x1c>
		.srbIdentity=1,
		.haveRlcConfig=1,
		.rlcConfig=rlcConfig,
		.haveLogicalChannelConfig=1,
		.logicalChannelConfig=lcc,
	};
    4fab:	31 c0                	xor    %eax,%eax
    4fad:	b9 0e 00 00 00       	mov    $0xe,%ecx
    4fb2:	8b 55 dc             	mov    -0x24(%ebp),%edx
    4fb5:	8d 7d a0             	lea    -0x60(%ebp),%edi
    4fb8:	8b 5d e0             	mov    -0x20(%ebp),%ebx
    4fbb:	f3 ab                	rep stos %eax,%es:(%edi)
    4fbd:	8b 4d e8             	mov    -0x18(%ebp),%ecx
		.srbIdentity=2,
		.haveRlcConfig=1,
		.rlcConfig=rlcConfig,
		.haveLogicalChannelConfig=1,
		.logicalChannelConfig=lcc,
	};
    4fc0:	8d bd 68 ff ff ff    	lea    -0x98(%ebp),%edi
		.srbIdentity=1,
		.haveRlcConfig=1,
		.rlcConfig=rlcConfig,
		.haveLogicalChannelConfig=1,
		.logicalChannelConfig=lcc,
	};
    4fc6:	8b 75 e4             	mov    -0x1c(%ebp),%esi
    4fc9:	89 55 ac             	mov    %edx,-0x54(%ebp)
    4fcc:	89 5d b0             	mov    %ebx,-0x50(%ebp)
    4fcf:	89 4d b8             	mov    %ecx,-0x48(%ebp)
    4fd2:	8b 4d ec             	mov    -0x14(%ebp),%ecx
    4fd5:	89 75 b4             	mov    %esi,-0x4c(%ebp)
    4fd8:	c7 45 a8 01 00 00 00 	movl   $0x1,-0x58(%ebp)
		.drb_Identity=4,
		.haveRlcConfig=1,
		.rlcConfig=rlcConfig,
		.haveLogicalChannelConfig=1,
		.logicalChannelConfig=lcc,
	};
    4fdf:	c7 45 d8 01 00 00 00 	movl   $0x1,-0x28(%ebp)
		.srbIdentity=1,
		.haveRlcConfig=1,
		.rlcConfig=rlcConfig,
		.haveLogicalChannelConfig=1,
		.logicalChannelConfig=lcc,
	};
    4fe6:	89 4d bc             	mov    %ecx,-0x44(%ebp)
    4fe9:	8b 4d f0             	mov    -0x10(%ebp),%ecx
    4fec:	89 4d c0             	mov    %ecx,-0x40(%ebp)
		.srbIdentity=2,
		.haveRlcConfig=1,
		.rlcConfig=rlcConfig,
		.haveLogicalChannelConfig=1,
		.logicalChannelConfig=lcc,
	};
    4fef:	b9 0e 00 00 00       	mov    $0xe,%ecx
    4ff4:	f3 ab                	rep stos %eax,%es:(%edi)
    4ff6:	8b 4d e8             	mov    -0x18(%ebp),%ecx
		.drb_Identity=4,
		.haveRlcConfig=1,
		.rlcConfig=rlcConfig,
		.haveLogicalChannelConfig=1,
		.logicalChannelConfig=lcc,
	};
    4ff9:	8d bd 28 ff ff ff    	lea    -0xd8(%ebp),%edi
		.srbIdentity=2,
		.haveRlcConfig=1,
		.rlcConfig=rlcConfig,
		.haveLogicalChannelConfig=1,
		.logicalChannelConfig=lcc,
	};
    4fff:	89 95 74 ff ff ff    	mov    %edx,-0x8c(%ebp)
    5005:	89 9d 78 ff ff ff    	mov    %ebx,-0x88(%ebp)
    500b:	89 b5 7c ff ff ff    	mov    %esi,-0x84(%ebp)
    5011:	89 4d 80             	mov    %ecx,-0x80(%ebp)
    5014:	8b 4d ec             	mov    -0x14(%ebp),%ecx
    5017:	c7 85 70 ff ff ff 01 	movl   $0x1,-0x90(%ebp)
    501e:	00 00 00 
    5021:	89 4d 84             	mov    %ecx,-0x7c(%ebp)
    5024:	8b 4d f0             	mov    -0x10(%ebp),%ecx
    5027:	89 4d 88             	mov    %ecx,-0x78(%ebp)
		.drb_Identity=4,
		.haveRlcConfig=1,
		.rlcConfig=rlcConfig,
		.haveLogicalChannelConfig=1,
		.logicalChannelConfig=lcc,
	};
    502a:	b9 10 00 00 00       	mov    $0x10,%ecx
    502f:	f3 ab                	rep stos %eax,%es:(%edi)
    5031:	8b 4d e8             	mov    -0x18(%ebp),%ecx
		.srbList[1]=srb_to_add_mod2,
	};
	struct DrbToAddModList drb_to_addmod_list={
		.num = 1,
		.drbList[0]=drb_to_add_mod,
	};
    5034:	8d bd f0 fb ff ff    	lea    -0x410(%ebp),%edi
		.drb_Identity=4,
		.haveRlcConfig=1,
		.rlcConfig=rlcConfig,
		.haveLogicalChannelConfig=1,
		.logicalChannelConfig=lcc,
	};
    503a:	89 95 38 ff ff ff    	mov    %edx,-0xc8(%ebp)
    5040:	89 9d 3c ff ff ff    	mov    %ebx,-0xc4(%ebp)
    5046:	89 b5 40 ff ff ff    	mov    %esi,-0xc0(%ebp)
    504c:	89 8d 44 ff ff ff    	mov    %ecx,-0xbc(%ebp)
    5052:	8b 4d ec             	mov    -0x14(%ebp),%ecx
    5055:	c7 85 34 ff ff ff 01 	movl   $0x1,-0xcc(%ebp)
    505c:	00 00 00 
    505f:	89 8d 48 ff ff ff    	mov    %ecx,-0xb8(%ebp)
    5065:	8b 4d f0             	mov    -0x10(%ebp),%ecx

	struct SrbToAddModList srb_to_addmod_list={
		.num=2,
		.srbList[0]=srb_to_add_mod1,
		.srbList[1]=srb_to_add_mod2,
	};
    5068:	c6 45 a4 01          	movb   $0x1,-0x5c(%ebp)
    506c:	c6 45 c4 01          	movb   $0x1,-0x3c(%ebp)
    5070:	c6 45 c5 01          	movb   $0x1,-0x3b(%ebp)
		.drb_Identity=4,
		.haveRlcConfig=1,
		.rlcConfig=rlcConfig,
		.haveLogicalChannelConfig=1,
		.logicalChannelConfig=lcc,
	};
    5074:	89 8d 4c ff ff ff    	mov    %ecx,-0xb4(%ebp)

	struct SrbToAddModList srb_to_addmod_list={
		.num=2,
		.srbList[0]=srb_to_add_mod1,
		.srbList[1]=srb_to_add_mod2,
	};
    507a:	8b 4d a4             	mov    -0x5c(%ebp),%ecx
    507d:	89 95 c4 fe ff ff    	mov    %edx,-0x13c(%ebp)
    5083:	89 9d c8 fe ff ff    	mov    %ebx,-0x138(%ebp)
    5089:	89 b5 cc fe ff ff    	mov    %esi,-0x134(%ebp)
    508f:	89 8d bc fe ff ff    	mov    %ecx,-0x144(%ebp)
    5095:	8b 4d e8             	mov    -0x18(%ebp),%ecx
    5098:	c7 45 a0 01 00 00 00 	movl   $0x1,-0x60(%ebp)
    509f:	c7 85 b8 fe ff ff 01 	movl   $0x1,-0x148(%ebp)
    50a6:	00 00 00 
    50a9:	c7 85 c0 fe ff ff 01 	movl   $0x1,-0x140(%ebp)
    50b0:	00 00 00 
    50b3:	89 8d d0 fe ff ff    	mov    %ecx,-0x130(%ebp)
    50b9:	8b 4d ec             	mov    -0x14(%ebp),%ecx
    50bc:	c7 85 68 ff ff ff 02 	movl   $0x2,-0x98(%ebp)
    50c3:	00 00 00 
    50c6:	c6 85 6c ff ff ff 01 	movb   $0x1,-0x94(%ebp)
    50cd:	c6 45 8c 01          	movb   $0x1,-0x74(%ebp)
    50d1:	89 8d d4 fe ff ff    	mov    %ecx,-0x12c(%ebp)
    50d7:	8b 4d f0             	mov    -0x10(%ebp),%ecx
    50da:	c6 45 8d 01          	movb   $0x1,-0x73(%ebp)
    50de:	89 8d d8 fe ff ff    	mov    %ecx,-0x128(%ebp)
    50e4:	8b 4d c4             	mov    -0x3c(%ebp),%ecx
    50e7:	89 8d dc fe ff ff    	mov    %ecx,-0x124(%ebp)
    50ed:	8b 4d c8             	mov    -0x38(%ebp),%ecx
    50f0:	89 8d e0 fe ff ff    	mov    %ecx,-0x120(%ebp)
    50f6:	8b 4d cc             	mov    -0x34(%ebp),%ecx
    50f9:	89 8d e4 fe ff ff    	mov    %ecx,-0x11c(%ebp)
    50ff:	8b 4d d0             	mov    -0x30(%ebp),%ecx
    5102:	89 8d e8 fe ff ff    	mov    %ecx,-0x118(%ebp)
    5108:	8b 4d d4             	mov    -0x2c(%ebp),%ecx
    510b:	89 8d ec fe ff ff    	mov    %ecx,-0x114(%ebp)
    5111:	c7 85 f0 fe ff ff 02 	movl   $0x2,-0x110(%ebp)
    5118:	00 00 00 
    511b:	8b 8d 6c ff ff ff    	mov    -0x94(%ebp),%ecx
	struct DrbToAddModList drb_to_addmod_list={
		.num = 1,
		.drbList[0]=drb_to_add_mod,
	};
    5121:	c6 85 30 ff ff ff 01 	movb   $0x1,-0xd0(%ebp)

	struct SrbToAddModList srb_to_addmod_list={
		.num=2,
		.srbList[0]=srb_to_add_mod1,
		.srbList[1]=srb_to_add_mod2,
	};
    5128:	89 95 fc fe ff ff    	mov    %edx,-0x104(%ebp)
    512e:	89 9d 00 ff ff ff    	mov    %ebx,-0x100(%ebp)
    5134:	89 8d f4 fe ff ff    	mov    %ecx,-0x10c(%ebp)
    513a:	8b 4d e8             	mov    -0x18(%ebp),%ecx
    513d:	89 b5 04 ff ff ff    	mov    %esi,-0xfc(%ebp)
    5143:	c7 85 f8 fe ff ff 01 	movl   $0x1,-0x108(%ebp)
    514a:	00 00 00 
	struct DrbToAddModList drb_to_addmod_list={
		.num = 1,
		.drbList[0]=drb_to_add_mod,
	};
    514d:	c7 85 2c ff ff ff 04 	movl   $0x4,-0xd4(%ebp)
    5154:	00 00 00 

	struct SrbToAddModList srb_to_addmod_list={
		.num=2,
		.srbList[0]=srb_to_add_mod1,
		.srbList[1]=srb_to_add_mod2,
	};
    5157:	89 8d 08 ff ff ff    	mov    %ecx,-0xf8(%ebp)
    515d:	8b 4d ec             	mov    -0x14(%ebp),%ecx
	struct DrbToAddModList drb_to_addmod_list={
		.num = 1,
		.drbList[0]=drb_to_add_mod,
	};
    5160:	c6 85 54 ff ff ff 01 	movb   $0x1,-0xac(%ebp)
    5167:	c6 85 55 ff ff ff 01 	movb   $0x1,-0xab(%ebp)

	struct SrbToAddModList srb_to_addmod_list={
		.num=2,
		.srbList[0]=srb_to_add_mod1,
		.srbList[1]=srb_to_add_mod2,
	};
    516e:	89 8d 0c ff ff ff    	mov    %ecx,-0xf4(%ebp)
    5174:	8b 4d f0             	mov    -0x10(%ebp),%ecx
    5177:	89 8d 10 ff ff ff    	mov    %ecx,-0xf0(%ebp)
    517d:	8b 4d 8c             	mov    -0x74(%ebp),%ecx
    5180:	89 8d 14 ff ff ff    	mov    %ecx,-0xec(%ebp)
    5186:	8b 4d 90             	mov    -0x70(%ebp),%ecx
    5189:	89 8d 18 ff ff ff    	mov    %ecx,-0xe8(%ebp)
    518f:	8b 4d 94             	mov    -0x6c(%ebp),%ecx
    5192:	89 8d 1c ff ff ff    	mov    %ecx,-0xe4(%ebp)
    5198:	8b 4d 98             	mov    -0x68(%ebp),%ecx
    519b:	89 8d 20 ff ff ff    	mov    %ecx,-0xe0(%ebp)
    51a1:	8b 4d 9c             	mov    -0x64(%ebp),%ecx
    51a4:	89 8d 24 ff ff ff    	mov    %ecx,-0xdc(%ebp)
	struct DrbToAddModList drb_to_addmod_list={
		.num = 1,
		.drbList[0]=drb_to_add_mod,
	};
    51aa:	b9 b1 00 00 00       	mov    $0xb1,%ecx
    51af:	f3 ab                	rep stos %eax,%es:(%edi)
    51b1:	8b 8d 30 ff ff ff    	mov    -0xd0(%ebp),%ecx
		.haveDrbToReleaseList=1,
		.srbToAddModList=srb_to_addmod_list,
		.drbToAddModList=drb_to_addmod_list,
		.drbToReleaseList=drb_to_release_list,

	};
    51b7:	8d bd 04 f7 ff ff    	lea    -0x8fc(%ebp),%edi
		.srbList[1]=srb_to_add_mod2,
	};
	struct DrbToAddModList drb_to_addmod_list={
		.num = 1,
		.drbList[0]=drb_to_add_mod,
	};
    51bd:	89 95 04 fc ff ff    	mov    %edx,-0x3fc(%ebp)
    51c3:	c7 85 f4 fb ff ff 00 	movl   $0x0,-0x40c(%ebp)
    51ca:	00 00 00 
    51cd:	c7 85 f8 fb ff ff 04 	movl   $0x4,-0x408(%ebp)
    51d4:	00 00 00 
    51d7:	89 8d fc fb ff ff    	mov    %ecx,-0x404(%ebp)
    51dd:	c7 85 00 fc ff ff 01 	movl   $0x1,-0x400(%ebp)
    51e4:	00 00 00 
    51e7:	89 9d 08 fc ff ff    	mov    %ebx,-0x3f8(%ebp)
    51ed:	8b 55 e8             	mov    -0x18(%ebp),%edx
    51f0:	8b 4d ec             	mov    -0x14(%ebp),%ecx
    51f3:	89 b5 0c fc ff ff    	mov    %esi,-0x3f4(%ebp)
		.haveDrbToReleaseList=1,
		.srbToAddModList=srb_to_addmod_list,
		.drbToAddModList=drb_to_addmod_list,
		.drbToReleaseList=drb_to_release_list,

	};
    51f9:	8d b5 b4 fe ff ff    	lea    -0x14c(%ebp),%esi
    51ff:	c7 85 b4 fe ff ff 02 	movl   $0x2,-0x14c(%ebp)
    5206:	00 00 00 
		.srbList[1]=srb_to_add_mod2,
	};
	struct DrbToAddModList drb_to_addmod_list={
		.num = 1,
		.drbList[0]=drb_to_add_mod,
	};
    5209:	89 95 10 fc ff ff    	mov    %edx,-0x3f0(%ebp)
    520f:	8b 55 f0             	mov    -0x10(%ebp),%edx
    5212:	89 8d 14 fc ff ff    	mov    %ecx,-0x3ec(%ebp)
		.haveDrbToReleaseList=1,
		.srbToAddModList=srb_to_addmod_list,
		.drbToAddModList=drb_to_addmod_list,
		.drbToReleaseList=drb_to_release_list,

	};
    5218:	b9 3b 01 00 00       	mov    $0x13b,%ecx
    521d:	f3 ab                	rep stos %eax,%es:(%edi)
    521f:	8d bd 08 f7 ff ff    	lea    -0x8f8(%ebp),%edi

	struct RRCConnectionReconfiguration *rrcConfig = fsm_mem_alloc(sizeof(struct RRCConnectionReconfiguration));
    5225:	66 b8 f0 04          	mov    $0x4f0,%ax
		.haveDrbToReleaseList=1,
		.srbToAddModList=srb_to_addmod_list,
		.drbToAddModList=drb_to_addmod_list,
		.drbToReleaseList=drb_to_release_list,

	};
    5229:	c7 85 f0 fb ff ff 01 	movl   $0x1,-0x410(%ebp)
    5230:	00 00 00 
		.srbList[1]=srb_to_add_mod2,
	};
	struct DrbToAddModList drb_to_addmod_list={
		.num = 1,
		.drbList[0]=drb_to_add_mod,
	};
    5233:	89 95 18 fc ff ff    	mov    %edx,-0x3e8(%ebp)
    5239:	8b 95 50 ff ff ff    	mov    -0xb0(%ebp),%edx
    523f:	89 95 1c fc ff ff    	mov    %edx,-0x3e4(%ebp)
    5245:	8b 95 54 ff ff ff    	mov    -0xac(%ebp),%edx
		.haveDrbToReleaseList=1,
		.srbToAddModList=srb_to_addmod_list,
		.drbToAddModList=drb_to_addmod_list,
		.drbToReleaseList=drb_to_release_list,

	};
    524b:	b1 1d                	mov    $0x1d,%cl
    524d:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    524f:	8d bd 80 f7 ff ff    	lea    -0x880(%ebp),%edi
    5255:	8d b5 f0 fb ff ff    	lea    -0x410(%ebp),%esi
		.srbList[1]=srb_to_add_mod2,
	};
	struct DrbToAddModList drb_to_addmod_list={
		.num = 1,
		.drbList[0]=drb_to_add_mod,
	};
    525b:	89 95 20 fc ff ff    	mov    %edx,-0x3e0(%ebp)
    5261:	8b 95 58 ff ff ff    	mov    -0xa8(%ebp),%edx
		.haveDrbToReleaseList=1,
		.srbToAddModList=srb_to_addmod_list,
		.drbToAddModList=drb_to_addmod_list,
		.drbToReleaseList=drb_to_release_list,

	};
    5267:	b1 b1                	mov    $0xb1,%cl
		.srbList[1]=srb_to_add_mod2,
	};
	struct DrbToAddModList drb_to_addmod_list={
		.num = 1,
		.drbList[0]=drb_to_add_mod,
	};
    5269:	89 95 24 fc ff ff    	mov    %edx,-0x3dc(%ebp)
    526f:	8b 95 5c ff ff ff    	mov    -0xa4(%ebp),%edx
    5275:	89 95 28 fc ff ff    	mov    %edx,-0x3d8(%ebp)
    527b:	8b 95 60 ff ff ff    	mov    -0xa0(%ebp),%edx
    5281:	89 95 2c fc ff ff    	mov    %edx,-0x3d4(%ebp)
    5287:	8b 95 64 ff ff ff    	mov    -0x9c(%ebp),%edx
    528d:	89 95 30 fc ff ff    	mov    %edx,-0x3d0(%ebp)
		.haveDrbToReleaseList=1,
		.srbToAddModList=srb_to_addmod_list,
		.drbToAddModList=drb_to_addmod_list,
		.drbToReleaseList=drb_to_release_list,

	};
    5293:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)

	struct RRCConnectionReconfiguration *rrcConfig = fsm_mem_alloc(sizeof(struct RRCConnectionReconfiguration));
	rrcConfig->haveRadioResourceConfigDedicated = true;
	rrcConfig->rrcTransactionIdentifier = 1;
	rrcConfig->radioResourceConfigDedicated=rrcd;
    5295:	8d b5 04 f7 ff ff    	lea    -0x8fc(%ebp),%esi
		.drbToAddModList=drb_to_addmod_list,
		.drbToReleaseList=drb_to_release_list,

	};

	struct RRCConnectionReconfiguration *rrcConfig = fsm_mem_alloc(sizeof(struct RRCConnectionReconfiguration));
    529b:	e8 fc ff ff ff       	call   529c <SetRrcConnReconfigmessage+0x31c>
	rrcConfig->haveRadioResourceConfigDedicated = true;
	rrcConfig->rrcTransactionIdentifier = 1;
	rrcConfig->radioResourceConfigDedicated=rrcd;
    52a0:	b9 3b 01 00 00       	mov    $0x13b,%ecx
		.drbToReleaseList=drb_to_release_list,

	};

	struct RRCConnectionReconfiguration *rrcConfig = fsm_mem_alloc(sizeof(struct RRCConnectionReconfiguration));
	rrcConfig->haveRadioResourceConfigDedicated = true;
    52a5:	c6 40 01 01          	movb   $0x1,0x1(%eax)
	rrcConfig->rrcTransactionIdentifier = 1;
	rrcConfig->radioResourceConfigDedicated=rrcd;
    52a9:	8d 78 04             	lea    0x4(%eax),%edi
		.drbToAddModList=drb_to_addmod_list,
		.drbToReleaseList=drb_to_release_list,

	};

	struct RRCConnectionReconfiguration *rrcConfig = fsm_mem_alloc(sizeof(struct RRCConnectionReconfiguration));
    52ac:	89 c3                	mov    %eax,%ebx
	rrcConfig->haveRadioResourceConfigDedicated = true;
	rrcConfig->rrcTransactionIdentifier = 1;
    52ae:	c6 00 01             	movb   $0x1,(%eax)
	rrcConfig->radioResourceConfigDedicated=rrcd;
    52b1:	c6 85 04 f7 ff ff 01 	movb   $0x1,-0x8fc(%ebp)
    52b8:	c6 85 7c f7 ff ff 01 	movb   $0x1,-0x884(%ebp)
    52bf:	c6 85 44 fa ff ff 01 	movb   $0x1,-0x5bc(%ebp)
    52c6:	c7 85 48 fa ff ff 01 	movl   $0x1,-0x5b8(%ebp)
    52cd:	00 00 00 
    52d0:	c7 85 4c fa ff ff 04 	movl   $0x4,-0x5b4(%ebp)
    52d7:	00 00 00 
    52da:	c7 85 50 fa ff ff 00 	movl   $0x0,-0x5b0(%ebp)
    52e1:	00 00 00 
    52e4:	c7 85 54 fa ff ff 00 	movl   $0x0,-0x5ac(%ebp)
    52eb:	00 00 00 
    52ee:	c7 85 58 fa ff ff 00 	movl   $0x0,-0x5a8(%ebp)
    52f5:	00 00 00 
    52f8:	c7 85 5c fa ff ff 00 	movl   $0x0,-0x5a4(%ebp)
    52ff:	00 00 00 
    5302:	c7 85 60 fa ff ff 00 	movl   $0x0,-0x5a0(%ebp)
    5309:	00 00 00 
    530c:	c7 85 64 fa ff ff 00 	movl   $0x0,-0x59c(%ebp)
    5313:	00 00 00 
    5316:	c7 85 68 fa ff ff 00 	movl   $0x0,-0x598(%ebp)
    531d:	00 00 00 
    5320:	c7 85 6c fa ff ff 00 	movl   $0x0,-0x594(%ebp)
    5327:	00 00 00 
    532a:	c7 85 70 fa ff ff 00 	movl   $0x0,-0x590(%ebp)
    5331:	00 00 00 
    5334:	c7 85 74 fa ff ff 00 	movl   $0x0,-0x58c(%ebp)
    533b:	00 00 00 
    533e:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)

	fsm_printf("[rrc] [conn_reconfig] UE is seting RRCConnectionReconfiguration message !\n");
    5340:	c7 04 24 dc 13 00 00 	movl   $0x13dc,(%esp)
    5347:	e8 fc ff ff ff       	call   5348 <SetRrcConnReconfigmessage+0x3c8>
	return rrcConfig;


}
    534c:	89 d8                	mov    %ebx,%eax
    534e:	8b 75 f8             	mov    -0x8(%ebp),%esi
    5351:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    5354:	8b 7d fc             	mov    -0x4(%ebp),%edi
    5357:	89 ec                	mov    %ebp,%esp
    5359:	5d                   	pop    %ebp
    535a:	c3                   	ret    
    535b:	90                   	nop
    535c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00005360 <AddModDrb>:
 **-----------------------------------------------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
static void AddModDrb(struct DrbToAddMod drb,int add_or_mod)
{
    5360:	55                   	push   %ebp
    5361:	89 e5                	mov    %esp,%ebp
    5363:	57                   	push   %edi
    5364:	56                   	push   %esi
    5365:	53                   	push   %ebx
    5366:	81 ec 58 01 00 00    	sub    $0x158,%esp
    536c:	e8 fc ff ff ff       	call   536d <AddModDrb+0xd>
	FIN(AddModSrb());
	struct CRLC_ConfigReq_IoctrlMsg crlc_configreq_ioctlmsg;
	struct MAC_LogicalChannelConfig_IoctrlMsg mac_lcc_ioctlmsg;
	int ioccmdToRLC;

	ioccmdToRLC=(add_or_mod==0? IOCCMD_RRCTORLC_BUILD:IOCCMD_RRCTORLC_RECONFIG);
    5371:	8b 45 48             	mov    0x48(%ebp),%eax
 **-----------------------------------------------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
static void AddModDrb(struct DrbToAddMod drb,int add_or_mod)
{
    5374:	8b 5d 0c             	mov    0xc(%ebp),%ebx
    5377:	0f b6 7d 10          	movzbl 0x10(%ebp),%edi
    537b:	0f b6 75 34          	movzbl 0x34(%ebp),%esi
	FIN(AddModSrb());
	struct CRLC_ConfigReq_IoctrlMsg crlc_configreq_ioctlmsg;
	struct MAC_LogicalChannelConfig_IoctrlMsg mac_lcc_ioctlmsg;
	int ioccmdToRLC;

	ioccmdToRLC=(add_or_mod==0? IOCCMD_RRCTORLC_BUILD:IOCCMD_RRCTORLC_RECONFIG);
    537f:	85 c0                	test   %eax,%eax
    5381:	0f 85 d9 00 00 00    	jne    5460 <AddModDrb+0x100>
    5387:	8b 55 1c             	mov    0x1c(%ebp),%edx
    538a:	8b 45 08             	mov    0x8(%ebp),%eax
    538d:	8b 4d 18             	mov    0x18(%ebp),%ecx
    5390:	89 9d 7c ff ff ff    	mov    %ebx,-0x84(%ebp)
    5396:	89 95 a4 fe ff ff    	mov    %edx,-0x15c(%ebp)
    539c:	89 55 8c             	mov    %edx,-0x74(%ebp)
    539f:	8b 55 20             	mov    0x20(%ebp),%edx
    53a2:	89 85 78 ff ff ff    	mov    %eax,-0x88(%ebp)
    53a8:	8b 45 10             	mov    0x10(%ebp),%eax
    53ab:	89 4d 88             	mov    %ecx,-0x78(%ebp)
    53ae:	89 95 b4 fe ff ff    	mov    %edx,-0x14c(%ebp)
    53b4:	89 55 90             	mov    %edx,-0x70(%ebp)
    53b7:	8b 55 24             	mov    0x24(%ebp),%edx
    53ba:	89 45 80             	mov    %eax,-0x80(%ebp)
    53bd:	8b 45 14             	mov    0x14(%ebp),%eax
    53c0:	89 95 b0 fe ff ff    	mov    %edx,-0x150(%ebp)
    53c6:	89 55 94             	mov    %edx,-0x6c(%ebp)
    53c9:	8b 55 28             	mov    0x28(%ebp),%edx
	FIN(ExtractDrbInfo());
	crlc_configreq_ioctlmsg->rbIdentity=drb.drb_Identity;
	crlc_configreq_ioctlmsg->lcIdentity=drb.logicalChannelIdentity;
	crlc_configreq_ioctlmsg->Mode=drb.rlcConfig.type;

	switch(drb.rlcConfig.type)
    53cc:	83 f8 02             	cmp    $0x2,%eax
	FIN(AddModSrb());
	struct CRLC_ConfigReq_IoctrlMsg crlc_configreq_ioctlmsg;
	struct MAC_LogicalChannelConfig_IoctrlMsg mac_lcc_ioctlmsg;
	int ioccmdToRLC;

	ioccmdToRLC=(add_or_mod==0? IOCCMD_RRCTORLC_BUILD:IOCCMD_RRCTORLC_RECONFIG);
    53cf:	89 45 84             	mov    %eax,-0x7c(%ebp)
    53d2:	89 95 ac fe ff ff    	mov    %edx,-0x154(%ebp)
    53d8:	89 55 98             	mov    %edx,-0x68(%ebp)
    53db:	8b 55 2c             	mov    0x2c(%ebp),%edx
    53de:	89 95 a8 fe ff ff    	mov    %edx,-0x158(%ebp)
    53e4:	89 55 9c             	mov    %edx,-0x64(%ebp)
    53e7:	8b 55 30             	mov    0x30(%ebp),%edx
    53ea:	89 55 a0             	mov    %edx,-0x60(%ebp)
    53ed:	8b 55 34             	mov    0x34(%ebp),%edx
    53f0:	89 55 a4             	mov    %edx,-0x5c(%ebp)
    53f3:	8b 55 38             	mov    0x38(%ebp),%edx
    53f6:	89 55 a8             	mov    %edx,-0x58(%ebp)
    53f9:	8b 55 3c             	mov    0x3c(%ebp),%edx
    53fc:	89 55 ac             	mov    %edx,-0x54(%ebp)
    53ff:	8b 55 40             	mov    0x40(%ebp),%edx
    5402:	89 55 b0             	mov    %edx,-0x50(%ebp)
    5405:	8b 55 44             	mov    0x44(%ebp),%edx
 ** Modified Date: 
 ******************************************************************************/
static void ExtractDrbRlcInfo(struct DrbToAddMod drb,struct CRLC_ConfigReq_IoctrlMsg *crlc_configreq_ioctlmsg)
{
	FIN(ExtractDrbInfo());
	crlc_configreq_ioctlmsg->rbIdentity=drb.drb_Identity;
    5408:	88 5d b8             	mov    %bl,-0x48(%ebp)
	crlc_configreq_ioctlmsg->lcIdentity=drb.logicalChannelIdentity;
	crlc_configreq_ioctlmsg->Mode=drb.rlcConfig.type;
    540b:	66 89 45 ba          	mov    %ax,-0x46(%ebp)
	FIN(AddModSrb());
	struct CRLC_ConfigReq_IoctrlMsg crlc_configreq_ioctlmsg;
	struct MAC_LogicalChannelConfig_IoctrlMsg mac_lcc_ioctlmsg;
	int ioccmdToRLC;

	ioccmdToRLC=(add_or_mod==0? IOCCMD_RRCTORLC_BUILD:IOCCMD_RRCTORLC_RECONFIG);
    540f:	89 55 b4             	mov    %edx,-0x4c(%ebp)
 ******************************************************************************/
static void ExtractDrbRlcInfo(struct DrbToAddMod drb,struct CRLC_ConfigReq_IoctrlMsg *crlc_configreq_ioctlmsg)
{
	FIN(ExtractDrbInfo());
	crlc_configreq_ioctlmsg->rbIdentity=drb.drb_Identity;
	crlc_configreq_ioctlmsg->lcIdentity=drb.logicalChannelIdentity;
    5412:	0f b6 55 30          	movzbl 0x30(%ebp),%edx
    5416:	88 55 b9             	mov    %dl,-0x47(%ebp)
	crlc_configreq_ioctlmsg->Mode=drb.rlcConfig.type;

	switch(drb.rlcConfig.type)
    5419:	0f 84 89 03 00 00    	je     57a8 <AddModDrb+0x448>
    541f:	0f 86 7b 02 00 00    	jbe    56a0 <AddModDrb+0x340>
    5425:	83 f8 03             	cmp    $0x3,%eax
    5428:	0f 84 0a 04 00 00    	je     5838 <AddModDrb+0x4d8>
    542e:	83 f8 04             	cmp    $0x4,%eax
    5431:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    5438:	0f 85 6b 02 00 00    	jne    56a9 <AddModDrb+0x349>
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength;
			crlc_configreq_ioctlmsg->Mode = 3;
			break;
		case 4:
			//um down link
			crlc_configreq_ioctlmsg->umDwParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.sn_FieldLength;
    543e:	0f b7 95 a4 fe ff ff 	movzwl -0x15c(%ebp),%edx
			crlc_configreq_ioctlmsg->umDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.t_Reordering;
    5445:	8b 85 b4 fe ff ff    	mov    -0x14c(%ebp),%eax
			crlc_configreq_ioctlmsg->Mode = 4;
    544b:	66 c7 45 ba 04 00    	movw   $0x4,-0x46(%ebp)
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength;
			crlc_configreq_ioctlmsg->Mode = 3;
			break;
		case 4:
			//um down link
			crlc_configreq_ioctlmsg->umDwParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.sn_FieldLength;
    5451:	66 89 55 bc          	mov    %dx,-0x44(%ebp)
			crlc_configreq_ioctlmsg->umDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.t_Reordering;
    5455:	89 45 c0             	mov    %eax,-0x40(%ebp)
    5458:	e9 4c 02 00 00       	jmp    56a9 <AddModDrb+0x349>
    545d:	8d 76 00             	lea    0x0(%esi),%esi
	}
	else{
		//fix me:if have pdcpconfig,reconfig PDCP entity

		//send ioctl msg for rlc to reconfigure srb
		if(drb.haveRlcConfig){
    5460:	89 fa                	mov    %edi,%edx
    5462:	84 d2                	test   %dl,%dl
    5464:	0f 84 2f 01 00 00    	je     5599 <AddModDrb+0x239>
		ExtractDrbRlcInfo(drb,&crlc_configreq_ioctlmsg);
		fsm_do_ioctrl(STRM_TO_RLC,IOCCMD_RRCTORLC_BUILD,(void*)&crlc_configreq_ioctlmsg,sizeof(crlc_configreq_ioctlmsg));
		//send ioctl msg for mac to establish DCCH	
		ExtractDrbMacInfo(drb,&mac_lcc_ioctlmsg);
		fsm_printf("[rrc] [AddModDrb] add a drb, drbid = %d\n", drb.drb_Identity);
		fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_CONFIG_LCC,(void*)&mac_lcc_ioctlmsg,sizeof(mac_lcc_ioctlmsg));
    546a:	89 f2                	mov    %esi,%edx
    546c:	8b 45 08             	mov    0x8(%ebp),%eax
    546f:	88 55 34             	mov    %dl,0x34(%ebp)
    5472:	8b 55 1c             	mov    0x1c(%ebp),%edx
    5475:	c6 45 10 01          	movb   $0x1,0x10(%ebp)
    5479:	8b 4d 18             	mov    0x18(%ebp),%ecx
    547c:	89 5d 0c             	mov    %ebx,0xc(%ebp)
    547f:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%ebp)
    5485:	8b 45 10             	mov    0x10(%ebp),%eax
    5488:	89 95 a4 fe ff ff    	mov    %edx,-0x15c(%ebp)
    548e:	89 95 0c ff ff ff    	mov    %edx,-0xf4(%ebp)
    5494:	8b 55 20             	mov    0x20(%ebp),%edx
    5497:	89 9d fc fe ff ff    	mov    %ebx,-0x104(%ebp)
    549d:	89 85 00 ff ff ff    	mov    %eax,-0x100(%ebp)
    54a3:	8b 45 14             	mov    0x14(%ebp),%eax
    54a6:	89 8d 08 ff ff ff    	mov    %ecx,-0xf8(%ebp)
    54ac:	89 95 b4 fe ff ff    	mov    %edx,-0x14c(%ebp)
    54b2:	89 95 10 ff ff ff    	mov    %edx,-0xf0(%ebp)
    54b8:	8b 55 24             	mov    0x24(%ebp),%edx
    54bb:	89 85 04 ff ff ff    	mov    %eax,-0xfc(%ebp)
	FIN(ExtractDrbInfo());
	crlc_configreq_ioctlmsg->rbIdentity=drb.drb_Identity;
	crlc_configreq_ioctlmsg->lcIdentity=drb.logicalChannelIdentity;
	crlc_configreq_ioctlmsg->Mode=drb.rlcConfig.type;

	switch(drb.rlcConfig.type)
    54c1:	83 f8 02             	cmp    $0x2,%eax
		ExtractDrbRlcInfo(drb,&crlc_configreq_ioctlmsg);
		fsm_do_ioctrl(STRM_TO_RLC,IOCCMD_RRCTORLC_BUILD,(void*)&crlc_configreq_ioctlmsg,sizeof(crlc_configreq_ioctlmsg));
		//send ioctl msg for mac to establish DCCH	
		ExtractDrbMacInfo(drb,&mac_lcc_ioctlmsg);
		fsm_printf("[rrc] [AddModDrb] add a drb, drbid = %d\n", drb.drb_Identity);
		fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_CONFIG_LCC,(void*)&mac_lcc_ioctlmsg,sizeof(mac_lcc_ioctlmsg));
    54c4:	89 95 b0 fe ff ff    	mov    %edx,-0x150(%ebp)
    54ca:	89 95 14 ff ff ff    	mov    %edx,-0xec(%ebp)
    54d0:	8b 55 28             	mov    0x28(%ebp),%edx
    54d3:	89 95 ac fe ff ff    	mov    %edx,-0x154(%ebp)
    54d9:	89 95 18 ff ff ff    	mov    %edx,-0xe8(%ebp)
    54df:	8b 55 2c             	mov    0x2c(%ebp),%edx
    54e2:	89 95 a8 fe ff ff    	mov    %edx,-0x158(%ebp)
    54e8:	89 95 1c ff ff ff    	mov    %edx,-0xe4(%ebp)
    54ee:	8b 55 30             	mov    0x30(%ebp),%edx
    54f1:	89 95 20 ff ff ff    	mov    %edx,-0xe0(%ebp)
    54f7:	8b 55 34             	mov    0x34(%ebp),%edx
    54fa:	89 95 24 ff ff ff    	mov    %edx,-0xdc(%ebp)
    5500:	8b 55 38             	mov    0x38(%ebp),%edx
    5503:	89 95 28 ff ff ff    	mov    %edx,-0xd8(%ebp)
    5509:	8b 55 3c             	mov    0x3c(%ebp),%edx
    550c:	89 95 2c ff ff ff    	mov    %edx,-0xd4(%ebp)
    5512:	8b 55 40             	mov    0x40(%ebp),%edx
 ** Modified Date: 
 ******************************************************************************/
static void ExtractDrbRlcInfo(struct DrbToAddMod drb,struct CRLC_ConfigReq_IoctrlMsg *crlc_configreq_ioctlmsg)
{
	FIN(ExtractDrbInfo());
	crlc_configreq_ioctlmsg->rbIdentity=drb.drb_Identity;
    5515:	88 5d b8             	mov    %bl,-0x48(%ebp)
	crlc_configreq_ioctlmsg->lcIdentity=drb.logicalChannelIdentity;
	crlc_configreq_ioctlmsg->Mode=drb.rlcConfig.type;
    5518:	66 89 45 ba          	mov    %ax,-0x46(%ebp)
		ExtractDrbRlcInfo(drb,&crlc_configreq_ioctlmsg);
		fsm_do_ioctrl(STRM_TO_RLC,IOCCMD_RRCTORLC_BUILD,(void*)&crlc_configreq_ioctlmsg,sizeof(crlc_configreq_ioctlmsg));
		//send ioctl msg for mac to establish DCCH	
		ExtractDrbMacInfo(drb,&mac_lcc_ioctlmsg);
		fsm_printf("[rrc] [AddModDrb] add a drb, drbid = %d\n", drb.drb_Identity);
		fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_CONFIG_LCC,(void*)&mac_lcc_ioctlmsg,sizeof(mac_lcc_ioctlmsg));
    551c:	89 95 30 ff ff ff    	mov    %edx,-0xd0(%ebp)
    5522:	8b 55 44             	mov    0x44(%ebp),%edx
    5525:	89 95 34 ff ff ff    	mov    %edx,-0xcc(%ebp)
 ******************************************************************************/
static void ExtractDrbRlcInfo(struct DrbToAddMod drb,struct CRLC_ConfigReq_IoctrlMsg *crlc_configreq_ioctlmsg)
{
	FIN(ExtractDrbInfo());
	crlc_configreq_ioctlmsg->rbIdentity=drb.drb_Identity;
	crlc_configreq_ioctlmsg->lcIdentity=drb.logicalChannelIdentity;
    552b:	0f b6 55 30          	movzbl 0x30(%ebp),%edx
    552f:	88 55 b9             	mov    %dl,-0x47(%ebp)
	crlc_configreq_ioctlmsg->Mode=drb.rlcConfig.type;

	switch(drb.rlcConfig.type)
    5532:	0f 84 d8 02 00 00    	je     5810 <AddModDrb+0x4b0>
    5538:	0f 87 92 02 00 00    	ja     57d0 <AddModDrb+0x470>
    553e:	83 f8 01             	cmp    $0x1,%eax
    5541:	75 3d                	jne    5580 <AddModDrb+0x220>
	{
		case 1:
			//AM down link
			crlc_configreq_ioctlmsg->amDwParas.timerStatusProhibit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_StatusProhibit;
    5543:	8b 85 a8 fe ff ff    	mov    -0x158(%ebp),%eax
			crlc_configreq_ioctlmsg->amDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_Reordering;
    5549:	8b 95 ac fe ff ff    	mov    -0x154(%ebp),%edx

			//AM up link
			crlc_configreq_ioctlmsg->amUpParas.timerPollRetransmit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.t_PollRetransmit;
    554f:	89 4d d0             	mov    %ecx,-0x30(%ebp)
			crlc_configreq_ioctlmsg->amUpParas.PollPDU=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollPDU;
			crlc_configreq_ioctlmsg->amUpParas.PollBYTE=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollByte;
			crlc_configreq_ioctlmsg->amUpParas.maxRetxThreshold=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.maxRetxThreshold;
			crlc_configreq_ioctlmsg->Mode = 1;
    5552:	66 c7 45 ba 01 00    	movw   $0x1,-0x46(%ebp)

	switch(drb.rlcConfig.type)
	{
		case 1:
			//AM down link
			crlc_configreq_ioctlmsg->amDwParas.timerStatusProhibit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_StatusProhibit;
    5558:	89 45 c8             	mov    %eax,-0x38(%ebp)
			crlc_configreq_ioctlmsg->amDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_Reordering;

			//AM up link
			crlc_configreq_ioctlmsg->amUpParas.timerPollRetransmit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.t_PollRetransmit;
			crlc_configreq_ioctlmsg->amUpParas.PollPDU=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollPDU;
    555b:	0f b7 85 a4 fe ff ff 	movzwl -0x15c(%ebp),%eax
	switch(drb.rlcConfig.type)
	{
		case 1:
			//AM down link
			crlc_configreq_ioctlmsg->amDwParas.timerStatusProhibit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_StatusProhibit;
			crlc_configreq_ioctlmsg->amDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_Reordering;
    5562:	89 55 cc             	mov    %edx,-0x34(%ebp)

			//AM up link
			crlc_configreq_ioctlmsg->amUpParas.timerPollRetransmit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.t_PollRetransmit;
			crlc_configreq_ioctlmsg->amUpParas.PollPDU=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollPDU;
			crlc_configreq_ioctlmsg->amUpParas.PollBYTE=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollByte;
    5565:	0f b7 95 b4 fe ff ff 	movzwl -0x14c(%ebp),%edx
			crlc_configreq_ioctlmsg->amDwParas.timerStatusProhibit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_StatusProhibit;
			crlc_configreq_ioctlmsg->amDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_Reordering;

			//AM up link
			crlc_configreq_ioctlmsg->amUpParas.timerPollRetransmit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.t_PollRetransmit;
			crlc_configreq_ioctlmsg->amUpParas.PollPDU=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollPDU;
    556c:	66 89 45 d4          	mov    %ax,-0x2c(%ebp)
			crlc_configreq_ioctlmsg->amUpParas.PollBYTE=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollByte;
			crlc_configreq_ioctlmsg->amUpParas.maxRetxThreshold=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.maxRetxThreshold;
    5570:	0f b7 85 b0 fe ff ff 	movzwl -0x150(%ebp),%eax
			crlc_configreq_ioctlmsg->amDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_Reordering;

			//AM up link
			crlc_configreq_ioctlmsg->amUpParas.timerPollRetransmit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.t_PollRetransmit;
			crlc_configreq_ioctlmsg->amUpParas.PollPDU=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollPDU;
			crlc_configreq_ioctlmsg->amUpParas.PollBYTE=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollByte;
    5577:	66 89 55 d6          	mov    %dx,-0x2a(%ebp)
			crlc_configreq_ioctlmsg->amUpParas.maxRetxThreshold=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.maxRetxThreshold;
    557b:	66 89 45 d8          	mov    %ax,-0x28(%ebp)
    557f:	90                   	nop
		//fix me:if have pdcpconfig,reconfig PDCP entity

		//send ioctl msg for rlc to reconfigure srb
		if(drb.haveRlcConfig){
			ExtractDrbRlcInfo(drb,&crlc_configreq_ioctlmsg);
			fsm_do_ioctrl(STRM_TO_RLC,IOCCMD_RRCTORLC_RECONFIG,(void*)&crlc_configreq_ioctlmsg,sizeof(crlc_configreq_ioctlmsg));
    5580:	8d 4d b8             	lea    -0x48(%ebp),%ecx
    5583:	ba 02 00 00 00       	mov    $0x2,%edx
    5588:	b8 01 00 00 00       	mov    $0x1,%eax
    558d:	c7 04 24 24 00 00 00 	movl   $0x24,(%esp)
    5594:	e8 fc ff ff ff       	call   5595 <AddModDrb+0x235>
		}
		//send ioctl msg for mac to reconfigure DCCH
		if(drb.haveLogicalChannelConfig){
    5599:	89 f2                	mov    %esi,%edx
    559b:	84 d2                	test   %dl,%dl
    559d:	75 11                	jne    55b0 <AddModDrb+0x250>
			ExtractDrbMacInfo(drb,&mac_lcc_ioctlmsg);
			fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_CONFIG_LCC,(void*)&mac_lcc_ioctlmsg,sizeof(mac_lcc_ioctlmsg));
		}
	}
	FOUT;
}
    559f:	81 c4 58 01 00 00    	add    $0x158,%esp
    55a5:	5b                   	pop    %ebx
    55a6:	5e                   	pop    %esi
    55a7:	5f                   	pop    %edi
    55a8:	5d                   	pop    %ebp
    55a9:	c3                   	ret    
    55aa:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
		if(drb.haveRlcConfig){
			ExtractDrbRlcInfo(drb,&crlc_configreq_ioctlmsg);
			fsm_do_ioctrl(STRM_TO_RLC,IOCCMD_RRCTORLC_RECONFIG,(void*)&crlc_configreq_ioctlmsg,sizeof(crlc_configreq_ioctlmsg));
		}
		//send ioctl msg for mac to reconfigure DCCH
		if(drb.haveLogicalChannelConfig){
    55b0:	89 f8                	mov    %edi,%eax
    55b2:	88 45 10             	mov    %al,0x10(%ebp)
    55b5:	8b 45 08             	mov    0x8(%ebp),%eax
    55b8:	c6 45 34 01          	movb   $0x1,0x34(%ebp)
    55bc:	89 5d 0c             	mov    %ebx,0xc(%ebp)
    55bf:	89 9d bc fe ff ff    	mov    %ebx,-0x144(%ebp)
    55c5:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%ebp)
    55cb:	8b 45 10             	mov    0x10(%ebp),%eax
    55ce:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%ebp)
    55d4:	8b 45 14             	mov    0x14(%ebp),%eax
    55d7:	89 85 c4 fe ff ff    	mov    %eax,-0x13c(%ebp)
    55dd:	8b 45 18             	mov    0x18(%ebp),%eax
    55e0:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%ebp)
    55e6:	8b 45 1c             	mov    0x1c(%ebp),%eax
    55e9:	89 85 cc fe ff ff    	mov    %eax,-0x134(%ebp)
    55ef:	8b 45 20             	mov    0x20(%ebp),%eax
    55f2:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%ebp)
    55f8:	8b 45 24             	mov    0x24(%ebp),%eax
    55fb:	89 85 d4 fe ff ff    	mov    %eax,-0x12c(%ebp)
    5601:	8b 45 28             	mov    0x28(%ebp),%eax
    5604:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%ebp)
    560a:	8b 45 2c             	mov    0x2c(%ebp),%eax
    560d:	89 85 dc fe ff ff    	mov    %eax,-0x124(%ebp)
    5613:	8b 45 30             	mov    0x30(%ebp),%eax
    5616:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%ebp)
    561c:	8b 45 34             	mov    0x34(%ebp),%eax
    561f:	89 85 e4 fe ff ff    	mov    %eax,-0x11c(%ebp)
    5625:	8b 45 38             	mov    0x38(%ebp),%eax
    5628:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%ebp)
    562e:	8b 45 3c             	mov    0x3c(%ebp),%eax
    5631:	89 85 ec fe ff ff    	mov    %eax,-0x114(%ebp)
    5637:	8b 45 40             	mov    0x40(%ebp),%eax
    563a:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%ebp)
    5640:	8b 45 44             	mov    0x44(%ebp),%eax
    5643:	89 85 f4 fe ff ff    	mov    %eax,-0x10c(%ebp)
 ** Modified Date: 
 ******************************************************************************/
static void ExtractDrbMacInfo(struct DrbToAddMod drb,struct MAC_LogicalChannelConfig_IoctrlMsg *mac_lcc_ioctlmsg)
{
	FIN(ExtractDrbMacInfo());
	mac_lcc_ioctlmsg->logicalChannelConfig=drb.logicalChannelConfig;
    5649:	8b 85 f2 fe ff ff    	mov    -0x10e(%ebp),%eax
	mac_lcc_ioctlmsg->logicalChannelIdentity=drb.drb_Identity; //INTEGER(1,2)
    564f:	89 5d df             	mov    %ebx,-0x21(%ebp)
 ** Modified Date: 
 ******************************************************************************/
static void ExtractDrbMacInfo(struct DrbToAddMod drb,struct MAC_LogicalChannelConfig_IoctrlMsg *mac_lcc_ioctlmsg)
{
	FIN(ExtractDrbMacInfo());
	mac_lcc_ioctlmsg->logicalChannelConfig=drb.logicalChannelConfig;
    5652:	89 45 f0             	mov    %eax,-0x10(%ebp)
    5655:	8b 85 ee fe ff ff    	mov    -0x112(%ebp),%eax
    565b:	89 45 ec             	mov    %eax,-0x14(%ebp)
    565e:	8b 85 ea fe ff ff    	mov    -0x116(%ebp),%eax
    5664:	89 45 e8             	mov    %eax,-0x18(%ebp)
    5667:	8b 85 e6 fe ff ff    	mov    -0x11a(%ebp),%eax
    566d:	89 45 e4             	mov    %eax,-0x1c(%ebp)
    5670:	0f b6 85 e5 fe ff ff 	movzbl -0x11b(%ebp),%eax
    5677:	88 45 e3             	mov    %al,-0x1d(%ebp)
			fsm_do_ioctrl(STRM_TO_RLC,IOCCMD_RRCTORLC_RECONFIG,(void*)&crlc_configreq_ioctlmsg,sizeof(crlc_configreq_ioctlmsg));
		}
		//send ioctl msg for mac to reconfigure DCCH
		if(drb.haveLogicalChannelConfig){
			ExtractDrbMacInfo(drb,&mac_lcc_ioctlmsg);
			fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_CONFIG_LCC,(void*)&mac_lcc_ioctlmsg,sizeof(mac_lcc_ioctlmsg));
    567a:	8d 4d df             	lea    -0x21(%ebp),%ecx
    567d:	ba 11 00 00 00       	mov    $0x11,%edx
    5682:	b8 02 00 00 00       	mov    $0x2,%eax
    5687:	c7 04 24 15 00 00 00 	movl   $0x15,(%esp)
    568e:	e8 fc ff ff ff       	call   568f <AddModDrb+0x32f>
		}
	}
	FOUT;
}
    5693:	81 c4 58 01 00 00    	add    $0x158,%esp
    5699:	5b                   	pop    %ebx
    569a:	5e                   	pop    %esi
    569b:	5f                   	pop    %edi
    569c:	5d                   	pop    %ebp
    569d:	c3                   	ret    
    569e:	66 90                	xchg   %ax,%ax
	FIN(ExtractDrbInfo());
	crlc_configreq_ioctlmsg->rbIdentity=drb.drb_Identity;
	crlc_configreq_ioctlmsg->lcIdentity=drb.logicalChannelIdentity;
	crlc_configreq_ioctlmsg->Mode=drb.rlcConfig.type;

	switch(drb.rlcConfig.type)
    56a0:	83 f8 01             	cmp    $0x1,%eax
    56a3:	0f 84 9f 01 00 00    	je     5848 <AddModDrb+0x4e8>
	if(ioccmdToRLC==IOCCMD_RRCTORLC_BUILD){
		//fix me:establish PDCP entity

		//send ioctl msg for rlc to establish srb
		ExtractDrbRlcInfo(drb,&crlc_configreq_ioctlmsg);
		fsm_do_ioctrl(STRM_TO_RLC,IOCCMD_RRCTORLC_BUILD,(void*)&crlc_configreq_ioctlmsg,sizeof(crlc_configreq_ioctlmsg));
    56a9:	8d 4d b8             	lea    -0x48(%ebp),%ecx
    56ac:	ba 29 00 00 00       	mov    $0x29,%edx
    56b1:	b8 01 00 00 00       	mov    $0x1,%eax
    56b6:	c7 04 24 24 00 00 00 	movl   $0x24,(%esp)
    56bd:	e8 fc ff ff ff       	call   56be <AddModDrb+0x35e>
    56c2:	89 f0                	mov    %esi,%eax
    56c4:	89 fa                	mov    %edi,%edx
    56c6:	88 45 34             	mov    %al,0x34(%ebp)
    56c9:	8b 45 08             	mov    0x8(%ebp),%eax
    56cc:	88 55 10             	mov    %dl,0x10(%ebp)
    56cf:	89 5d 0c             	mov    %ebx,0xc(%ebp)
    56d2:	89 9d 3c ff ff ff    	mov    %ebx,-0xc4(%ebp)
    56d8:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%ebp)
    56de:	8b 45 10             	mov    0x10(%ebp),%eax
    56e1:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%ebp)
    56e7:	8b 45 14             	mov    0x14(%ebp),%eax
    56ea:	89 85 44 ff ff ff    	mov    %eax,-0xbc(%ebp)
    56f0:	8b 45 18             	mov    0x18(%ebp),%eax
    56f3:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%ebp)
    56f9:	8b 45 1c             	mov    0x1c(%ebp),%eax
    56fc:	89 85 4c ff ff ff    	mov    %eax,-0xb4(%ebp)
    5702:	8b 45 20             	mov    0x20(%ebp),%eax
    5705:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%ebp)
    570b:	8b 45 24             	mov    0x24(%ebp),%eax
    570e:	89 85 54 ff ff ff    	mov    %eax,-0xac(%ebp)
    5714:	8b 45 28             	mov    0x28(%ebp),%eax
    5717:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%ebp)
    571d:	8b 45 2c             	mov    0x2c(%ebp),%eax
    5720:	89 85 5c ff ff ff    	mov    %eax,-0xa4(%ebp)
    5726:	8b 45 30             	mov    0x30(%ebp),%eax
    5729:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%ebp)
    572f:	8b 45 34             	mov    0x34(%ebp),%eax
    5732:	89 85 64 ff ff ff    	mov    %eax,-0x9c(%ebp)
    5738:	8b 45 38             	mov    0x38(%ebp),%eax
    573b:	89 85 68 ff ff ff    	mov    %eax,-0x98(%ebp)
    5741:	8b 45 3c             	mov    0x3c(%ebp),%eax
    5744:	89 85 6c ff ff ff    	mov    %eax,-0x94(%ebp)
    574a:	8b 45 40             	mov    0x40(%ebp),%eax
    574d:	89 85 70 ff ff ff    	mov    %eax,-0x90(%ebp)
    5753:	8b 45 44             	mov    0x44(%ebp),%eax
    5756:	89 85 74 ff ff ff    	mov    %eax,-0x8c(%ebp)
 ** Modified Date: 
 ******************************************************************************/
static void ExtractDrbMacInfo(struct DrbToAddMod drb,struct MAC_LogicalChannelConfig_IoctrlMsg *mac_lcc_ioctlmsg)
{
	FIN(ExtractDrbMacInfo());
	mac_lcc_ioctlmsg->logicalChannelConfig=drb.logicalChannelConfig;
    575c:	8b 85 72 ff ff ff    	mov    -0x8e(%ebp),%eax
	mac_lcc_ioctlmsg->logicalChannelIdentity=drb.drb_Identity; //INTEGER(1,2)
    5762:	89 5d df             	mov    %ebx,-0x21(%ebp)
 ** Modified Date: 
 ******************************************************************************/
static void ExtractDrbMacInfo(struct DrbToAddMod drb,struct MAC_LogicalChannelConfig_IoctrlMsg *mac_lcc_ioctlmsg)
{
	FIN(ExtractDrbMacInfo());
	mac_lcc_ioctlmsg->logicalChannelConfig=drb.logicalChannelConfig;
    5765:	89 45 f0             	mov    %eax,-0x10(%ebp)
    5768:	8b 85 6e ff ff ff    	mov    -0x92(%ebp),%eax
    576e:	89 45 ec             	mov    %eax,-0x14(%ebp)
    5771:	8b 85 6a ff ff ff    	mov    -0x96(%ebp),%eax
    5777:	89 45 e8             	mov    %eax,-0x18(%ebp)
    577a:	8b 85 66 ff ff ff    	mov    -0x9a(%ebp),%eax
    5780:	89 45 e4             	mov    %eax,-0x1c(%ebp)
    5783:	0f b6 85 65 ff ff ff 	movzbl -0x9b(%ebp),%eax
    578a:	88 45 e3             	mov    %al,-0x1d(%ebp)
		//send ioctl msg for rlc to establish srb
		ExtractDrbRlcInfo(drb,&crlc_configreq_ioctlmsg);
		fsm_do_ioctrl(STRM_TO_RLC,IOCCMD_RRCTORLC_BUILD,(void*)&crlc_configreq_ioctlmsg,sizeof(crlc_configreq_ioctlmsg));
		//send ioctl msg for mac to establish DCCH	
		ExtractDrbMacInfo(drb,&mac_lcc_ioctlmsg);
		fsm_printf("[rrc] [AddModDrb] add a drb, drbid = %d\n", drb.drb_Identity);
    578d:	89 5c 24 04          	mov    %ebx,0x4(%esp)
    5791:	c7 04 24 28 14 00 00 	movl   $0x1428,(%esp)
    5798:	e8 fc ff ff ff       	call   5799 <AddModDrb+0x439>
    579d:	e9 d8 fe ff ff       	jmp    567a <AddModDrb+0x31a>
    57a2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
			crlc_configreq_ioctlmsg->amUpParas.maxRetxThreshold=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.maxRetxThreshold;
			crlc_configreq_ioctlmsg->Mode = 1;
			break;
		case 2:
			//um down link
			crlc_configreq_ioctlmsg->umDwParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.sn_FieldLength;
    57a8:	0f b7 95 a4 fe ff ff 	movzwl -0x15c(%ebp),%edx
			crlc_configreq_ioctlmsg->umDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.t_Reordering;
    57af:	8b 85 b4 fe ff ff    	mov    -0x14c(%ebp),%eax

			//um up link
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength;
    57b5:	66 89 4d c4          	mov    %cx,-0x3c(%ebp)
			crlc_configreq_ioctlmsg->Mode = 2;
    57b9:	66 c7 45 ba 02 00    	movw   $0x2,-0x46(%ebp)
			crlc_configreq_ioctlmsg->amUpParas.maxRetxThreshold=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.maxRetxThreshold;
			crlc_configreq_ioctlmsg->Mode = 1;
			break;
		case 2:
			//um down link
			crlc_configreq_ioctlmsg->umDwParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.sn_FieldLength;
    57bf:	66 89 55 bc          	mov    %dx,-0x44(%ebp)
			crlc_configreq_ioctlmsg->umDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.t_Reordering;
    57c3:	89 45 c0             	mov    %eax,-0x40(%ebp)
    57c6:	e9 de fe ff ff       	jmp    56a9 <AddModDrb+0x349>
    57cb:	90                   	nop
    57cc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
	FIN(ExtractDrbInfo());
	crlc_configreq_ioctlmsg->rbIdentity=drb.drb_Identity;
	crlc_configreq_ioctlmsg->lcIdentity=drb.logicalChannelIdentity;
	crlc_configreq_ioctlmsg->Mode=drb.rlcConfig.type;

	switch(drb.rlcConfig.type)
    57d0:	83 f8 03             	cmp    $0x3,%eax
    57d3:	74 2b                	je     5800 <AddModDrb+0x4a0>
    57d5:	83 f8 04             	cmp    $0x4,%eax
    57d8:	0f 85 a2 fd ff ff    	jne    5580 <AddModDrb+0x220>
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength;
			crlc_configreq_ioctlmsg->Mode = 3;
			break;
		case 4:
			//um down link
			crlc_configreq_ioctlmsg->umDwParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.sn_FieldLength;
    57de:	0f b7 95 a4 fe ff ff 	movzwl -0x15c(%ebp),%edx
			crlc_configreq_ioctlmsg->umDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.t_Reordering;
    57e5:	8b 85 b4 fe ff ff    	mov    -0x14c(%ebp),%eax
			crlc_configreq_ioctlmsg->Mode = 4;
    57eb:	66 c7 45 ba 04 00    	movw   $0x4,-0x46(%ebp)
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength;
			crlc_configreq_ioctlmsg->Mode = 3;
			break;
		case 4:
			//um down link
			crlc_configreq_ioctlmsg->umDwParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.sn_FieldLength;
    57f1:	66 89 55 bc          	mov    %dx,-0x44(%ebp)
			crlc_configreq_ioctlmsg->umDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.t_Reordering;
    57f5:	89 45 c0             	mov    %eax,-0x40(%ebp)
    57f8:	e9 83 fd ff ff       	jmp    5580 <AddModDrb+0x220>
    57fd:	8d 76 00             	lea    0x0(%esi),%esi
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength;
			crlc_configreq_ioctlmsg->Mode = 2;
			break;
		case 3:
			//um up link
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength;
    5800:	66 89 4d c4          	mov    %cx,-0x3c(%ebp)
			crlc_configreq_ioctlmsg->Mode = 3;
    5804:	66 c7 45 ba 03 00    	movw   $0x3,-0x46(%ebp)
    580a:	e9 71 fd ff ff       	jmp    5580 <AddModDrb+0x220>
    580f:	90                   	nop
			crlc_configreq_ioctlmsg->amUpParas.maxRetxThreshold=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.maxRetxThreshold;
			crlc_configreq_ioctlmsg->Mode = 1;
			break;
		case 2:
			//um down link
			crlc_configreq_ioctlmsg->umDwParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.sn_FieldLength;
    5810:	0f b7 95 a4 fe ff ff 	movzwl -0x15c(%ebp),%edx
			crlc_configreq_ioctlmsg->umDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.t_Reordering;
    5817:	8b 85 b4 fe ff ff    	mov    -0x14c(%ebp),%eax

			//um up link
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength;
    581d:	66 89 4d c4          	mov    %cx,-0x3c(%ebp)
			crlc_configreq_ioctlmsg->Mode = 2;
    5821:	66 c7 45 ba 02 00    	movw   $0x2,-0x46(%ebp)
			crlc_configreq_ioctlmsg->amUpParas.maxRetxThreshold=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.maxRetxThreshold;
			crlc_configreq_ioctlmsg->Mode = 1;
			break;
		case 2:
			//um down link
			crlc_configreq_ioctlmsg->umDwParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.sn_FieldLength;
    5827:	66 89 55 bc          	mov    %dx,-0x44(%ebp)
			crlc_configreq_ioctlmsg->umDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.t_Reordering;
    582b:	89 45 c0             	mov    %eax,-0x40(%ebp)
    582e:	e9 4d fd ff ff       	jmp    5580 <AddModDrb+0x220>
    5833:	90                   	nop
    5834:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength;
			crlc_configreq_ioctlmsg->Mode = 2;
			break;
		case 3:
			//um up link
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=*(unsigned int*)&drb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength;
    5838:	66 89 4d c4          	mov    %cx,-0x3c(%ebp)
			crlc_configreq_ioctlmsg->Mode = 3;
    583c:	66 c7 45 ba 03 00    	movw   $0x3,-0x46(%ebp)
    5842:	e9 62 fe ff ff       	jmp    56a9 <AddModDrb+0x349>
    5847:	90                   	nop

	switch(drb.rlcConfig.type)
	{
		case 1:
			//AM down link
			crlc_configreq_ioctlmsg->amDwParas.timerStatusProhibit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_StatusProhibit;
    5848:	8b 85 a8 fe ff ff    	mov    -0x158(%ebp),%eax
			crlc_configreq_ioctlmsg->amDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_Reordering;
    584e:	8b 95 ac fe ff ff    	mov    -0x154(%ebp),%edx

			//AM up link
			crlc_configreq_ioctlmsg->amUpParas.timerPollRetransmit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.t_PollRetransmit;
    5854:	89 4d d0             	mov    %ecx,-0x30(%ebp)
			crlc_configreq_ioctlmsg->amUpParas.PollPDU=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollPDU;
			crlc_configreq_ioctlmsg->amUpParas.PollBYTE=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollByte;
			crlc_configreq_ioctlmsg->amUpParas.maxRetxThreshold=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.maxRetxThreshold;
			crlc_configreq_ioctlmsg->Mode = 1;
    5857:	66 c7 45 ba 01 00    	movw   $0x1,-0x46(%ebp)

	switch(drb.rlcConfig.type)
	{
		case 1:
			//AM down link
			crlc_configreq_ioctlmsg->amDwParas.timerStatusProhibit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_StatusProhibit;
    585d:	89 45 c8             	mov    %eax,-0x38(%ebp)
			crlc_configreq_ioctlmsg->amDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_Reordering;

			//AM up link
			crlc_configreq_ioctlmsg->amUpParas.timerPollRetransmit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.t_PollRetransmit;
			crlc_configreq_ioctlmsg->amUpParas.PollPDU=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollPDU;
    5860:	0f b7 85 a4 fe ff ff 	movzwl -0x15c(%ebp),%eax
	switch(drb.rlcConfig.type)
	{
		case 1:
			//AM down link
			crlc_configreq_ioctlmsg->amDwParas.timerStatusProhibit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_StatusProhibit;
			crlc_configreq_ioctlmsg->amDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_Reordering;
    5867:	89 55 cc             	mov    %edx,-0x34(%ebp)

			//AM up link
			crlc_configreq_ioctlmsg->amUpParas.timerPollRetransmit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.t_PollRetransmit;
			crlc_configreq_ioctlmsg->amUpParas.PollPDU=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollPDU;
			crlc_configreq_ioctlmsg->amUpParas.PollBYTE=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollByte;
    586a:	0f b7 95 b4 fe ff ff 	movzwl -0x14c(%ebp),%edx
			crlc_configreq_ioctlmsg->amDwParas.timerStatusProhibit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_StatusProhibit;
			crlc_configreq_ioctlmsg->amDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_Reordering;

			//AM up link
			crlc_configreq_ioctlmsg->amUpParas.timerPollRetransmit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.t_PollRetransmit;
			crlc_configreq_ioctlmsg->amUpParas.PollPDU=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollPDU;
    5871:	66 89 45 d4          	mov    %ax,-0x2c(%ebp)
			crlc_configreq_ioctlmsg->amUpParas.PollBYTE=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollByte;
			crlc_configreq_ioctlmsg->amUpParas.maxRetxThreshold=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.maxRetxThreshold;
    5875:	0f b7 85 b0 fe ff ff 	movzwl -0x150(%ebp),%eax
			crlc_configreq_ioctlmsg->amDwParas.timerReordering=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_Reordering;

			//AM up link
			crlc_configreq_ioctlmsg->amUpParas.timerPollRetransmit=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.t_PollRetransmit;
			crlc_configreq_ioctlmsg->amUpParas.PollPDU=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollPDU;
			crlc_configreq_ioctlmsg->amUpParas.PollBYTE=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollByte;
    587c:	66 89 55 d6          	mov    %dx,-0x2a(%ebp)
			crlc_configreq_ioctlmsg->amUpParas.maxRetxThreshold=*(unsigned int*)&drb.rlcConfig.rlcConfigType.am.ul_AM_RLC.maxRetxThreshold;
    5880:	66 89 45 d8          	mov    %ax,-0x28(%ebp)
    5884:	e9 20 fe ff ff       	jmp    56a9 <AddModDrb+0x349>
    5889:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00005890 <ApplyDrbToAdd>:
 **-----------------------------------------------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
extern void ApplyDrbToAdd(struct DrbToAddModList drb)
{
    5890:	55                   	push   %ebp
    5891:	89 e5                	mov    %esp,%ebp
    5893:	57                   	push   %edi
    5894:	56                   	push   %esi
    5895:	53                   	push   %ebx
    5896:	81 ec cc 00 00 00    	sub    $0xcc,%esp
    589c:	e8 fc ff ff ff       	call   589d <ApplyDrbToAdd+0xd>
    58a1:	8b 45 08             	mov    0x8(%ebp),%eax
	FIN(ApplyDrbToAdd());
	struct LteDataRadioBearerInfo *localDrbConfig;
	struct DrbToAddMod eachDrb;
	int drbIndex;

	fsm_printf("[rrc] [ApplyDrbToAdd] DrbToAddModList.num = %d\n", drb.num);
    58a4:	c7 04 24 54 14 00 00 	movl   $0x1454,(%esp)
 **-----------------------------------------------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
extern void ApplyDrbToAdd(struct DrbToAddModList drb)
{
    58ab:	89 85 70 ff ff ff    	mov    %eax,-0x90(%ebp)
	FIN(ApplyDrbToAdd());
	struct LteDataRadioBearerInfo *localDrbConfig;
	struct DrbToAddMod eachDrb;
	int drbIndex;

	fsm_printf("[rrc] [ApplyDrbToAdd] DrbToAddModList.num = %d\n", drb.num);
    58b1:	89 44 24 04          	mov    %eax,0x4(%esp)
    58b5:	e8 fc ff ff ff       	call   58b6 <ApplyDrbToAdd+0x26>
	for(drbIndex=0; drbIndex<drb.num; drbIndex++)
    58ba:	8b 95 70 ff ff ff    	mov    -0x90(%ebp),%edx
    58c0:	85 d2                	test   %edx,%edx
    58c2:	0f 84 d8 02 00 00    	je     5ba0 <ApplyDrbToAdd+0x310>
    58c8:	8d 5d 0c             	lea    0xc(%ebp),%ebx
    58cb:	c7 45 ac 00 00 00 00 	movl   $0x0,-0x54(%ebp)
    58d2:	e9 1c 01 00 00       	jmp    59f3 <ApplyDrbToAdd+0x163>
    58d7:	90                   	nop
			fsm_printf("[rrc] [conn_reconfig] add a drb ,drbid=%d\n",ueDrbConfig[eachDrb.drb_Identity]->drbIdentity);//test
		}
		else
		{
			//reconfig the drb
			AddModDrb(eachDrb,1);
    58d8:	0f b6 45 90          	movzbl -0x70(%ebp),%eax
    58dc:	c7 44 24 40 01 00 00 	movl   $0x1,0x40(%esp)
    58e3:	00 
    58e4:	89 0c 24             	mov    %ecx,(%esp)
    58e7:	89 74 24 04          	mov    %esi,0x4(%esp)
    58eb:	88 45 e1             	mov    %al,-0x1f(%ebp)
    58ee:	8b 45 a0             	mov    -0x60(%ebp),%eax
    58f1:	89 54 24 08          	mov    %edx,0x8(%esp)
    58f5:	89 75 b8             	mov    %esi,-0x48(%ebp)
    58f8:	89 45 e2             	mov    %eax,-0x1e(%ebp)
    58fb:	8b 45 a4             	mov    -0x5c(%ebp),%eax
    58fe:	89 45 e6             	mov    %eax,-0x1a(%ebp)
    5901:	8b 45 a8             	mov    -0x58(%ebp),%eax
    5904:	89 45 ea             	mov    %eax,-0x16(%ebp)
    5907:	8b 45 b0             	mov    -0x50(%ebp),%eax
    590a:	89 45 ee             	mov    %eax,-0x12(%ebp)
    590d:	8b 85 6c ff ff ff    	mov    -0x94(%ebp),%eax
    5913:	89 44 24 0c          	mov    %eax,0xc(%esp)
    5917:	8b 45 8c             	mov    -0x74(%ebp),%eax
    591a:	89 44 24 10          	mov    %eax,0x10(%esp)
    591e:	8b 45 88             	mov    -0x78(%ebp),%eax
    5921:	89 44 24 14          	mov    %eax,0x14(%esp)
    5925:	8b 45 84             	mov    -0x7c(%ebp),%eax
    5928:	89 44 24 18          	mov    %eax,0x18(%esp)
    592c:	8b 45 80             	mov    -0x80(%ebp),%eax
    592f:	89 44 24 1c          	mov    %eax,0x1c(%esp)
    5933:	8b 85 7c ff ff ff    	mov    -0x84(%ebp),%eax
    5939:	89 44 24 20          	mov    %eax,0x20(%esp)
    593d:	8b 85 78 ff ff ff    	mov    -0x88(%ebp),%eax
    5943:	89 44 24 24          	mov    %eax,0x24(%esp)
    5947:	8b 85 74 ff ff ff    	mov    -0x8c(%ebp),%eax
    594d:	89 44 24 28          	mov    %eax,0x28(%esp)
    5951:	8b 45 e0             	mov    -0x20(%ebp),%eax
    5954:	89 44 24 2c          	mov    %eax,0x2c(%esp)
    5958:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    595b:	89 44 24 30          	mov    %eax,0x30(%esp)
    595f:	8b 45 e8             	mov    -0x18(%ebp),%eax
    5962:	89 44 24 34          	mov    %eax,0x34(%esp)
    5966:	8b 45 ec             	mov    -0x14(%ebp),%eax
    5969:	89 44 24 38          	mov    %eax,0x38(%esp)
    596d:	8b 45 f0             	mov    -0x10(%ebp),%eax
    5970:	89 44 24 3c          	mov    %eax,0x3c(%esp)
    5974:	e8 e7 f9 ff ff       	call   5360 <AddModDrb>

			//back up older config for recover the DRB hanged up
			localDrbConfig->rlcConfig=eachDrb.rlcConfig;
    5979:	8b 45 c0             	mov    -0x40(%ebp),%eax
    597c:	89 47 04             	mov    %eax,0x4(%edi)
    597f:	8b 45 c4             	mov    -0x3c(%ebp),%eax
    5982:	89 47 08             	mov    %eax,0x8(%edi)
    5985:	8b 45 c8             	mov    -0x38(%ebp),%eax
    5988:	89 47 0c             	mov    %eax,0xc(%edi)
    598b:	8b 45 cc             	mov    -0x34(%ebp),%eax
    598e:	89 47 10             	mov    %eax,0x10(%edi)
    5991:	8b 45 d0             	mov    -0x30(%ebp),%eax
    5994:	89 47 14             	mov    %eax,0x14(%edi)
    5997:	8b 45 d4             	mov    -0x2c(%ebp),%eax
    599a:	89 47 18             	mov    %eax,0x18(%edi)
    599d:	8b 45 d8             	mov    -0x28(%ebp),%eax
    59a0:	89 47 1c             	mov    %eax,0x1c(%edi)
			localDrbConfig->logicalChannelConfig=eachDrb.logicalChannelConfig;
    59a3:	8b 45 b0             	mov    -0x50(%ebp),%eax
    59a6:	89 47 2e             	mov    %eax,0x2e(%edi)
    59a9:	8b 45 a8             	mov    -0x58(%ebp),%eax
    59ac:	89 47 2a             	mov    %eax,0x2a(%edi)
    59af:	8b 45 a4             	mov    -0x5c(%ebp),%eax
    59b2:	89 47 26             	mov    %eax,0x26(%edi)
    59b5:	8b 45 a0             	mov    -0x60(%ebp),%eax
    59b8:	89 47 22             	mov    %eax,0x22(%edi)
    59bb:	0f b6 45 90          	movzbl -0x70(%ebp),%eax
    59bf:	88 47 21             	mov    %al,0x21(%edi)
			fsm_printf("[rrc] [conn_reconfig] reconfig a drb ,drbid=%d\n",ueDrbConfig[eachDrb.drb_Identity]->drbIdentity);//test
    59c2:	8b 04 b5 00 00 00 00 	mov    0x0(,%esi,4),%eax
    59c9:	0f b6 40 01          	movzbl 0x1(%eax),%eax
    59cd:	c7 04 24 b0 14 00 00 	movl   $0x14b0,(%esp)
    59d4:	89 44 24 04          	mov    %eax,0x4(%esp)
    59d8:	e8 fc ff ff ff       	call   59d9 <ApplyDrbToAdd+0x149>
	struct LteDataRadioBearerInfo *localDrbConfig;
	struct DrbToAddMod eachDrb;
	int drbIndex;

	fsm_printf("[rrc] [ApplyDrbToAdd] DrbToAddModList.num = %d\n", drb.num);
	for(drbIndex=0; drbIndex<drb.num; drbIndex++)
    59dd:	83 45 ac 01          	addl   $0x1,-0x54(%ebp)
    59e1:	83 c3 40             	add    $0x40,%ebx
    59e4:	8b 7d ac             	mov    -0x54(%ebp),%edi
    59e7:	39 bd 70 ff ff ff    	cmp    %edi,-0x90(%ebp)
    59ed:	0f 86 ad 01 00 00    	jbe    5ba0 <ApplyDrbToAdd+0x310>
	{
		eachDrb=drb.drbList[drbIndex];	
    59f3:	8b 0b                	mov    (%ebx),%ecx
    59f5:	89 4d b4             	mov    %ecx,-0x4c(%ebp)
    59f8:	8b 73 04             	mov    0x4(%ebx),%esi
    59fb:	89 75 b8             	mov    %esi,-0x48(%ebp)
    59fe:	8b 53 08             	mov    0x8(%ebx),%edx
    5a01:	89 55 bc             	mov    %edx,-0x44(%ebp)
    5a04:	8b 7b 0c             	mov    0xc(%ebx),%edi
    5a07:	89 bd 6c ff ff ff    	mov    %edi,-0x94(%ebp)
    5a0d:	89 7d c0             	mov    %edi,-0x40(%ebp)
    5a10:	8b 43 10             	mov    0x10(%ebx),%eax
    5a13:	89 45 8c             	mov    %eax,-0x74(%ebp)
    5a16:	89 45 c4             	mov    %eax,-0x3c(%ebp)
    5a19:	8b 7b 14             	mov    0x14(%ebx),%edi
    5a1c:	89 7d 88             	mov    %edi,-0x78(%ebp)
    5a1f:	89 7d c8             	mov    %edi,-0x38(%ebp)
    5a22:	8b 43 18             	mov    0x18(%ebx),%eax
    5a25:	89 45 84             	mov    %eax,-0x7c(%ebp)
    5a28:	89 45 cc             	mov    %eax,-0x34(%ebp)
    5a2b:	8b 7b 1c             	mov    0x1c(%ebx),%edi
    5a2e:	89 7d 80             	mov    %edi,-0x80(%ebp)
    5a31:	89 7d d0             	mov    %edi,-0x30(%ebp)
    5a34:	8b 43 20             	mov    0x20(%ebx),%eax
    5a37:	89 85 7c ff ff ff    	mov    %eax,-0x84(%ebp)
    5a3d:	89 45 d4             	mov    %eax,-0x2c(%ebp)
    5a40:	8b 7b 24             	mov    0x24(%ebx),%edi
    5a43:	89 bd 78 ff ff ff    	mov    %edi,-0x88(%ebp)
    5a49:	89 7d d8             	mov    %edi,-0x28(%ebp)
    5a4c:	8b 43 28             	mov    0x28(%ebx),%eax
    5a4f:	89 85 74 ff ff ff    	mov    %eax,-0x8c(%ebp)
    5a55:	89 45 dc             	mov    %eax,-0x24(%ebp)
    5a58:	8b 7b 2c             	mov    0x2c(%ebx),%edi
    5a5b:	89 7d e0             	mov    %edi,-0x20(%ebp)
    5a5e:	8b 43 30             	mov    0x30(%ebx),%eax
    5a61:	89 45 e4             	mov    %eax,-0x1c(%ebp)
    5a64:	8b 43 34             	mov    0x34(%ebx),%eax
    5a67:	89 45 e8             	mov    %eax,-0x18(%ebp)
    5a6a:	8b 43 38             	mov    0x38(%ebx),%eax
    5a6d:	89 45 ec             	mov    %eax,-0x14(%ebp)
    5a70:	8b 43 3c             	mov    0x3c(%ebx),%eax
    5a73:	89 45 f0             	mov    %eax,-0x10(%ebp)
    5a76:	89 f8                	mov    %edi,%eax
    5a78:	8b 7d e2             	mov    -0x1e(%ebp),%edi
    5a7b:	66 c1 e8 08          	shr    $0x8,%ax
    5a7f:	88 45 90             	mov    %al,-0x70(%ebp)
    5a82:	8b 45 e6             	mov    -0x1a(%ebp),%eax
    5a85:	89 7d a0             	mov    %edi,-0x60(%ebp)
    5a88:	8b 7d ea             	mov    -0x16(%ebp),%edi
    5a8b:	89 45 a4             	mov    %eax,-0x5c(%ebp)
    5a8e:	8b 45 ee             	mov    -0x12(%ebp),%eax
    5a91:	89 7d a8             	mov    %edi,-0x58(%ebp)
		localDrbConfig=ueDrbConfig[eachDrb.drb_Identity];
    5a94:	8b 3c b5 00 00 00 00 	mov    0x0(,%esi,4),%edi
	int drbIndex;

	fsm_printf("[rrc] [ApplyDrbToAdd] DrbToAddModList.num = %d\n", drb.num);
	for(drbIndex=0; drbIndex<drb.num; drbIndex++)
	{
		eachDrb=drb.drbList[drbIndex];	
    5a9b:	89 45 b0             	mov    %eax,-0x50(%ebp)
		localDrbConfig=ueDrbConfig[eachDrb.drb_Identity];
		if(localDrbConfig==NULL){
    5a9e:	85 ff                	test   %edi,%edi
    5aa0:	0f 85 32 fe ff ff    	jne    58d8 <ApplyDrbToAdd+0x48>
			localDrbConfig=fsm_mem_alloc(sizeof(struct LteDataRadioBearerInfo));
    5aa6:	b8 34 00 00 00       	mov    $0x34,%eax
    5aab:	e8 fc ff ff ff       	call   5aac <ApplyDrbToAdd+0x21c>
			//build the drb
			AddModDrb(eachDrb,0);
    5ab0:	89 75 b8             	mov    %esi,-0x48(%ebp)
	for(drbIndex=0; drbIndex<drb.num; drbIndex++)
	{
		eachDrb=drb.drbList[drbIndex];	
		localDrbConfig=ueDrbConfig[eachDrb.drb_Identity];
		if(localDrbConfig==NULL){
			localDrbConfig=fsm_mem_alloc(sizeof(struct LteDataRadioBearerInfo));
    5ab3:	89 c7                	mov    %eax,%edi
			//build the drb
			AddModDrb(eachDrb,0);
    5ab5:	0f b6 45 90          	movzbl -0x70(%ebp),%eax
    5ab9:	89 74 24 04          	mov    %esi,0x4(%esp)
    5abd:	c7 44 24 40 00 00 00 	movl   $0x0,0x40(%esp)
    5ac4:	00 
    5ac5:	88 45 e1             	mov    %al,-0x1f(%ebp)
    5ac8:	8b 45 a0             	mov    -0x60(%ebp),%eax
    5acb:	89 45 e2             	mov    %eax,-0x1e(%ebp)
    5ace:	8b 45 a4             	mov    -0x5c(%ebp),%eax
    5ad1:	89 45 e6             	mov    %eax,-0x1a(%ebp)
    5ad4:	8b 45 a8             	mov    -0x58(%ebp),%eax
    5ad7:	89 45 ea             	mov    %eax,-0x16(%ebp)
    5ada:	8b 45 b0             	mov    -0x50(%ebp),%eax
    5add:	89 45 ee             	mov    %eax,-0x12(%ebp)
    5ae0:	8b 45 b4             	mov    -0x4c(%ebp),%eax
    5ae3:	89 04 24             	mov    %eax,(%esp)
    5ae6:	8b 45 bc             	mov    -0x44(%ebp),%eax
    5ae9:	89 44 24 08          	mov    %eax,0x8(%esp)
    5aed:	8b 45 c0             	mov    -0x40(%ebp),%eax
    5af0:	89 44 24 0c          	mov    %eax,0xc(%esp)
    5af4:	8b 45 c4             	mov    -0x3c(%ebp),%eax
    5af7:	89 44 24 10          	mov    %eax,0x10(%esp)
    5afb:	8b 45 c8             	mov    -0x38(%ebp),%eax
    5afe:	89 44 24 14          	mov    %eax,0x14(%esp)
    5b02:	8b 45 cc             	mov    -0x34(%ebp),%eax
    5b05:	89 44 24 18          	mov    %eax,0x18(%esp)
    5b09:	8b 45 d0             	mov    -0x30(%ebp),%eax
    5b0c:	89 44 24 1c          	mov    %eax,0x1c(%esp)
    5b10:	8b 45 d4             	mov    -0x2c(%ebp),%eax
    5b13:	89 44 24 20          	mov    %eax,0x20(%esp)
    5b17:	8b 45 d8             	mov    -0x28(%ebp),%eax
    5b1a:	89 44 24 24          	mov    %eax,0x24(%esp)
    5b1e:	8b 45 dc             	mov    -0x24(%ebp),%eax
    5b21:	89 44 24 28          	mov    %eax,0x28(%esp)
    5b25:	8b 45 e0             	mov    -0x20(%ebp),%eax
    5b28:	89 44 24 2c          	mov    %eax,0x2c(%esp)
    5b2c:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    5b2f:	89 44 24 30          	mov    %eax,0x30(%esp)
    5b33:	8b 45 e8             	mov    -0x18(%ebp),%eax
    5b36:	89 44 24 34          	mov    %eax,0x34(%esp)
    5b3a:	8b 45 ec             	mov    -0x14(%ebp),%eax
    5b3d:	89 44 24 38          	mov    %eax,0x38(%esp)
    5b41:	8b 45 f0             	mov    -0x10(%ebp),%eax
    5b44:	89 44 24 3c          	mov    %eax,0x3c(%esp)
    5b48:	e8 13 f8 ff ff       	call   5360 <AddModDrb>

			//drb status managment
			localDrbConfig->drbStatus=1;
			localDrbConfig->drbIdentity=eachDrb.drb_Identity;
    5b4d:	89 f0                	mov    %esi,%eax
    5b4f:	88 47 01             	mov    %al,0x1(%edi)
			localDrbConfig=fsm_mem_alloc(sizeof(struct LteDataRadioBearerInfo));
			//build the drb
			AddModDrb(eachDrb,0);

			//drb status managment
			localDrbConfig->drbStatus=1;
    5b52:	c6 07 01             	movb   $0x1,(%edi)
			localDrbConfig->drbIdentity=eachDrb.drb_Identity;
			localDrbConfig->lcid=eachDrb.logicalChannelIdentity;
    5b55:	8b 45 dc             	mov    -0x24(%ebp),%eax
    5b58:	88 47 20             	mov    %al,0x20(%edi)

			//back up older config for recover the DRB hanged up
			/*localDrbConfig->rlcConfig=eachDrb.rlcConfig;*/

			localDrbConfig->logicalChannelConfig=eachDrb.logicalChannelConfig;
    5b5b:	8b 45 b0             	mov    -0x50(%ebp),%eax
    5b5e:	89 47 2e             	mov    %eax,0x2e(%edi)
    5b61:	8b 45 a8             	mov    -0x58(%ebp),%eax
    5b64:	89 47 2a             	mov    %eax,0x2a(%edi)
    5b67:	8b 45 a4             	mov    -0x5c(%ebp),%eax
    5b6a:	89 47 26             	mov    %eax,0x26(%edi)
    5b6d:	8b 45 a0             	mov    -0x60(%ebp),%eax
    5b70:	89 47 22             	mov    %eax,0x22(%edi)
    5b73:	0f b6 45 90          	movzbl -0x70(%ebp),%eax
    5b77:	88 47 21             	mov    %al,0x21(%edi)
			ueDrbConfig[eachDrb.drb_Identity]=localDrbConfig;
    5b7a:	89 3c b5 00 00 00 00 	mov    %edi,0x0(,%esi,4)
			fsm_printf("[rrc] [conn_reconfig] add a drb ,drbid=%d\n",ueDrbConfig[eachDrb.drb_Identity]->drbIdentity);//test
    5b81:	0f b6 47 01          	movzbl 0x1(%edi),%eax
    5b85:	c7 04 24 84 14 00 00 	movl   $0x1484,(%esp)
    5b8c:	89 44 24 04          	mov    %eax,0x4(%esp)
    5b90:	e8 fc ff ff ff       	call   5b91 <ApplyDrbToAdd+0x301>
    5b95:	e9 43 fe ff ff       	jmp    59dd <ApplyDrbToAdd+0x14d>
    5b9a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
			localDrbConfig->logicalChannelConfig=eachDrb.logicalChannelConfig;
			fsm_printf("[rrc] [conn_reconfig] reconfig a drb ,drbid=%d\n",ueDrbConfig[eachDrb.drb_Identity]->drbIdentity);//test
		}
	}
	FOUT;	
}
    5ba0:	81 c4 cc 00 00 00    	add    $0xcc,%esp
    5ba6:	5b                   	pop    %ebx
    5ba7:	5e                   	pop    %esi
    5ba8:	5f                   	pop    %edi
    5ba9:	5d                   	pop    %ebp
    5baa:	c3                   	ret    
    5bab:	90                   	nop
    5bac:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00005bb0 <ApplyDrbToRelease>:
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
//release the drb
void ApplyDrbToRelease(struct DrbToReleaseList drb)
{
    5bb0:	55                   	push   %ebp
    5bb1:	89 e5                	mov    %esp,%ebp
    5bb3:	57                   	push   %edi
    5bb4:	56                   	push   %esi
    5bb5:	53                   	push   %ebx
    5bb6:	83 ec 10             	sub    $0x10,%esp
    5bb9:	e8 fc ff ff ff       	call   5bba <ApplyDrbToRelease+0xa>
    5bbe:	8b 7d 08             	mov    0x8(%ebp),%edi
	FIN(ApplyDrbToRelease());
	int drbIndex;
	for(drbIndex=0; drbIndex<drb.num;drbIndex++){
    5bc1:	85 ff                	test   %edi,%edi
    5bc3:	0f 84 83 00 00 00    	je     5c4c <ApplyDrbToRelease+0x9c>
    5bc9:	8d 5d 0c             	lea    0xc(%ebp),%ebx
    5bcc:	31 f6                	xor    %esi,%esi
    5bce:	66 90                	xchg   %ax,%ax
		DRB_Identity drbid=drb.drbToRelease[drbIndex];
    5bd0:	8b 03                	mov    (%ebx),%eax
		int logicalChannelIdentity= drbid;//DRB0-->lcid=3,DRB1-->lcid=4,.....
		if(ueDrbConfig[drbid]!=NULL){
    5bd2:	8b 0c 85 00 00 00 00 	mov    0x0(,%eax,4),%ecx
void ApplyDrbToRelease(struct DrbToReleaseList drb)
{
	FIN(ApplyDrbToRelease());
	int drbIndex;
	for(drbIndex=0; drbIndex<drb.num;drbIndex++){
		DRB_Identity drbid=drb.drbToRelease[drbIndex];
    5bd9:	89 45 f0             	mov    %eax,-0x10(%ebp)
		int logicalChannelIdentity= drbid;//DRB0-->lcid=3,DRB1-->lcid=4,.....
    5bdc:	89 45 ec             	mov    %eax,-0x14(%ebp)
		if(ueDrbConfig[drbid]!=NULL){
    5bdf:	85 c9                	test   %ecx,%ecx
    5be1:	74 5f                	je     5c42 <ApplyDrbToRelease+0x92>
			//fix me:release pdcp

			//release rlc entity
			fsm_do_ioctrl(STRM_TO_RLC,IOCCMD_RRCTORLC_RELEASE,(void*)&drbid,sizeof(DRB_Identity));
    5be3:	8d 4d f0             	lea    -0x10(%ebp),%ecx
    5be6:	ba 26 00 00 00       	mov    $0x26,%edx
    5beb:	b8 01 00 00 00       	mov    $0x1,%eax
    5bf0:	c7 04 24 04 00 00 00 	movl   $0x4,(%esp)
    5bf7:	e8 fc ff ff ff       	call   5bf8 <ApplyDrbToRelease+0x48>

			//fix me:release DTCH
			fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_RELEASE_LCC,(void*)&logicalChannelIdentity,sizeof(logicalChannelIdentity));
    5bfc:	8d 4d ec             	lea    -0x14(%ebp),%ecx
    5bff:	ba 12 00 00 00       	mov    $0x12,%edx
    5c04:	b8 02 00 00 00       	mov    $0x2,%eax
    5c09:	c7 04 24 04 00 00 00 	movl   $0x4,(%esp)
    5c10:	e8 fc ff ff ff       	call   5c11 <ApplyDrbToRelease+0x61>

			//release memory and pointer
			fsm_mem_free(ueDrbConfig[drbid]);
    5c15:	8b 45 f0             	mov    -0x10(%ebp),%eax
    5c18:	8b 04 85 00 00 00 00 	mov    0x0(,%eax,4),%eax
    5c1f:	e8 fc ff ff ff       	call   5c20 <ApplyDrbToRelease+0x70>
			ueDrbConfig[drbid]=NULL;
    5c24:	8b 45 f0             	mov    -0x10(%ebp),%eax
    5c27:	c7 04 85 00 00 00 00 	movl   $0x0,0x0(,%eax,4)
    5c2e:	00 00 00 00 
			fsm_printf("[rrc] [conn_reconfig] drb.drbToRelease=DRB%d\n",drbid);//test
    5c32:	89 44 24 04          	mov    %eax,0x4(%esp)
    5c36:	c7 04 24 e0 14 00 00 	movl   $0x14e0,(%esp)
    5c3d:	e8 fc ff ff ff       	call   5c3e <ApplyDrbToRelease+0x8e>
//release the drb
void ApplyDrbToRelease(struct DrbToReleaseList drb)
{
	FIN(ApplyDrbToRelease());
	int drbIndex;
	for(drbIndex=0; drbIndex<drb.num;drbIndex++){
    5c42:	83 c6 01             	add    $0x1,%esi
    5c45:	83 c3 04             	add    $0x4,%ebx
    5c48:	39 f7                	cmp    %esi,%edi
    5c4a:	77 84                	ja     5bd0 <ApplyDrbToRelease+0x20>
			ueDrbConfig[drbid]=NULL;
			fsm_printf("[rrc] [conn_reconfig] drb.drbToRelease=DRB%d\n",drbid);//test
		}
	}
	FOUT;
}
    5c4c:	83 c4 10             	add    $0x10,%esp
    5c4f:	5b                   	pop    %ebx
    5c50:	5e                   	pop    %esi
    5c51:	5f                   	pop    %edi
    5c52:	5d                   	pop    %ebp
    5c53:	c3                   	ret    
    5c54:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    5c5a:	8d bf 00 00 00 00    	lea    0x0(%edi),%edi

00005c60 <ApplySrbToRelease>:
 **-----------------------------------------------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void ApplySrbToRelease(void)
{
    5c60:	55                   	push   %ebp
    5c61:	89 e5                	mov    %esp,%ebp
    5c63:	57                   	push   %edi
    5c64:	56                   	push   %esi
    5c65:	53                   	push   %ebx
    5c66:	83 ec 10             	sub    $0x10,%esp
    5c69:	e8 fc ff ff ff       	call   5c6a <ApplySrbToRelease+0xa>
    5c6e:	31 db                	xor    %ebx,%ebx
		logicalChannelIdentity= srbid;
		if(ueSrbConfig[srbIndex]!=NULL){
			//fix me:release pdcp

			//release rlc entity
			fsm_do_ioctrl(STRM_TO_RLC,IOCCMD_RRCTORLC_RELEASE,(void*)&srbid,sizeof(int));
    5c70:	8d 75 f0             	lea    -0x10(%ebp),%esi

			//fix me:release DTCH
			fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_RELEASE_LCC,(void*)&logicalChannelIdentity,sizeof(logicalChannelIdentity));
    5c73:	8d 7d ec             	lea    -0x14(%ebp),%edi
	int srbIndex;
	int srbid;
	int logicalChannelIdentity;
	for(srbIndex=0;srbIndex<2;srbIndex++)
	{
		srbid = srbIndex+1;
    5c76:	83 c3 01             	add    $0x1,%ebx
		logicalChannelIdentity= srbid;
		if(ueSrbConfig[srbIndex]!=NULL){
    5c79:	8b 04 9d fc ff ff ff 	mov    -0x4(,%ebx,4),%eax
	int srbIndex;
	int srbid;
	int logicalChannelIdentity;
	for(srbIndex=0;srbIndex<2;srbIndex++)
	{
		srbid = srbIndex+1;
    5c80:	89 5d f0             	mov    %ebx,-0x10(%ebp)
		logicalChannelIdentity= srbid;
    5c83:	89 5d ec             	mov    %ebx,-0x14(%ebp)
		if(ueSrbConfig[srbIndex]!=NULL){
    5c86:	85 c0                	test   %eax,%eax
    5c88:	74 5a                	je     5ce4 <ApplySrbToRelease+0x84>
			//fix me:release pdcp

			//release rlc entity
			fsm_do_ioctrl(STRM_TO_RLC,IOCCMD_RRCTORLC_RELEASE,(void*)&srbid,sizeof(int));
    5c8a:	89 f1                	mov    %esi,%ecx
    5c8c:	ba 26 00 00 00       	mov    $0x26,%edx
    5c91:	b8 01 00 00 00       	mov    $0x1,%eax
    5c96:	c7 04 24 04 00 00 00 	movl   $0x4,(%esp)
    5c9d:	e8 fc ff ff ff       	call   5c9e <ApplySrbToRelease+0x3e>

			//fix me:release DTCH
			fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_RELEASE_LCC,(void*)&logicalChannelIdentity,sizeof(logicalChannelIdentity));
    5ca2:	89 f9                	mov    %edi,%ecx
    5ca4:	ba 12 00 00 00       	mov    $0x12,%edx
    5ca9:	b8 02 00 00 00       	mov    $0x2,%eax
    5cae:	c7 04 24 04 00 00 00 	movl   $0x4,(%esp)
    5cb5:	e8 fc ff ff ff       	call   5cb6 <ApplySrbToRelease+0x56>

			//release memory and pointer
			fsm_mem_free(ueSrbConfig[srbIndex]);
    5cba:	8b 04 9d fc ff ff ff 	mov    -0x4(,%ebx,4),%eax
    5cc1:	e8 fc ff ff ff       	call   5cc2 <ApplySrbToRelease+0x62>
			ueSrbConfig[srbIndex]=NULL;
			fsm_printf("[rrc] [conn_reconfig] srb.srbToRelease=SRB%d\n",srbid);//test
    5cc6:	8b 45 f0             	mov    -0x10(%ebp),%eax
			//fix me:release DTCH
			fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_RELEASE_LCC,(void*)&logicalChannelIdentity,sizeof(logicalChannelIdentity));

			//release memory and pointer
			fsm_mem_free(ueSrbConfig[srbIndex]);
			ueSrbConfig[srbIndex]=NULL;
    5cc9:	c7 04 9d fc ff ff ff 	movl   $0x0,-0x4(,%ebx,4)
    5cd0:	00 00 00 00 
			fsm_printf("[rrc] [conn_reconfig] srb.srbToRelease=SRB%d\n",srbid);//test
    5cd4:	89 44 24 04          	mov    %eax,0x4(%esp)
    5cd8:	c7 04 24 10 15 00 00 	movl   $0x1510,(%esp)
    5cdf:	e8 fc ff ff ff       	call   5ce0 <ApplySrbToRelease+0x80>
{
	FIN(ApplySrbToAdd());
	int srbIndex;
	int srbid;
	int logicalChannelIdentity;
	for(srbIndex=0;srbIndex<2;srbIndex++)
    5ce4:	83 fb 02             	cmp    $0x2,%ebx
    5ce7:	75 8d                	jne    5c76 <ApplySrbToRelease+0x16>
			fsm_mem_free(ueSrbConfig[srbIndex]);
			ueSrbConfig[srbIndex]=NULL;
			fsm_printf("[rrc] [conn_reconfig] srb.srbToRelease=SRB%d\n",srbid);//test
		}
	}
	fsm_printf("[rrc] [conn_reconfig] ApplySrbToRelease() is done!.\n");//test
    5ce9:	c7 04 24 40 15 00 00 	movl   $0x1540,(%esp)
    5cf0:	e8 fc ff ff ff       	call   5cf1 <ApplySrbToRelease+0x91>
	FOUT;			
}
    5cf5:	83 c4 10             	add    $0x10,%esp
    5cf8:	5b                   	pop    %ebx
    5cf9:	5e                   	pop    %esi
    5cfa:	5f                   	pop    %edi
    5cfb:	5d                   	pop    %ebp
    5cfc:	c3                   	ret    
    5cfd:	8d 76 00             	lea    0x0(%esi),%esi

00005d00 <AddModSrb>:
 **-----------------------------------------------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
static void AddModSrb(struct SrbToAddMod srb,int add_or_mod)
{
    5d00:	55                   	push   %ebp
    5d01:	89 e5                	mov    %esp,%ebp
    5d03:	57                   	push   %edi
    5d04:	56                   	push   %esi
    5d05:	53                   	push   %ebx
    5d06:	83 ec 50             	sub    $0x50,%esp
    5d09:	e8 fc ff ff ff       	call   5d0a <AddModSrb+0xa>
	FIN(AddModSrb());
	int ioccmdToRLC;
	struct CRLC_ConfigReq_IoctrlMsg *crlc_configreq_ioctlmsg;
	struct MAC_LogicalChannelConfig_IoctrlMsg *mac_lcc_ioctlmsg;
	crlc_configreq_ioctlmsg = (struct CRLC_ConfigReq_IoctrlMsg *)fsm_mem_alloc(sizeof(struct CRLC_ConfigReq_IoctrlMsg));
    5d0e:	b8 24 00 00 00       	mov    $0x24,%eax
    5d13:	e8 fc ff ff ff       	call   5d14 <AddModSrb+0x14>
    5d18:	89 c3                	mov    %eax,%ebx
	mac_lcc_ioctlmsg = (struct MAC_LogicalChannelConfig_IoctrlMsg *) fsm_mem_alloc(sizeof(struct MAC_LogicalChannelConfig_IoctrlMsg));
    5d1a:	b8 15 00 00 00       	mov    $0x15,%eax
    5d1f:	e8 fc ff ff ff       	call   5d20 <AddModSrb+0x20>
    5d24:	8b 55 0c             	mov    0xc(%ebp),%edx
    5d27:	8b 7d 10             	mov    0x10(%ebp),%edi
    5d2a:	89 55 c0             	mov    %edx,-0x40(%ebp)
    5d2d:	8b 55 14             	mov    0x14(%ebp),%edx
    5d30:	89 7d c4             	mov    %edi,-0x3c(%ebp)
    5d33:	89 c6                	mov    %eax,%esi
    5d35:	8b 45 08             	mov    0x8(%ebp),%eax
    5d38:	89 55 c8             	mov    %edx,-0x38(%ebp)
    5d3b:	8b 55 18             	mov    0x18(%ebp),%edx
    5d3e:	89 45 bc             	mov    %eax,-0x44(%ebp)
    5d41:	89 55 cc             	mov    %edx,-0x34(%ebp)
    5d44:	8b 55 1c             	mov    0x1c(%ebp),%edx
    5d47:	89 55 d0             	mov    %edx,-0x30(%ebp)
    5d4a:	8b 55 20             	mov    0x20(%ebp),%edx
    5d4d:	89 55 d4             	mov    %edx,-0x2c(%ebp)
    5d50:	8b 55 24             	mov    0x24(%ebp),%edx
    5d53:	89 55 d8             	mov    %edx,-0x28(%ebp)
    5d56:	8b 55 28             	mov    0x28(%ebp),%edx
    5d59:	89 55 dc             	mov    %edx,-0x24(%ebp)
    5d5c:	8b 55 2c             	mov    0x2c(%ebp),%edx
    5d5f:	89 55 e0             	mov    %edx,-0x20(%ebp)
    5d62:	8b 55 30             	mov    0x30(%ebp),%edx
    5d65:	89 55 e4             	mov    %edx,-0x1c(%ebp)
    5d68:	8b 55 34             	mov    0x34(%ebp),%edx
    5d6b:	89 55 e8             	mov    %edx,-0x18(%ebp)
    5d6e:	8b 55 38             	mov    0x38(%ebp),%edx
    5d71:	89 55 ec             	mov    %edx,-0x14(%ebp)
    5d74:	8b 55 3c             	mov    0x3c(%ebp),%edx
    5d77:	89 55 f0             	mov    %edx,-0x10(%ebp)
    5d7a:	8b 55 ea             	mov    -0x16(%ebp),%edx
    5d7d:	8b 4d ee             	mov    -0x12(%ebp),%ecx
    5d80:	89 55 ac             	mov    %edx,-0x54(%ebp)
    5d83:	8b 55 e6             	mov    -0x1a(%ebp),%edx
    5d86:	89 55 b0             	mov    %edx,-0x50(%ebp)
    5d89:	8b 55 e2             	mov    -0x1e(%ebp),%edx
    5d8c:	89 55 b4             	mov    %edx,-0x4c(%ebp)
    5d8f:	0f b6 55 e1          	movzbl -0x1f(%ebp),%edx
    5d93:	88 55 bb             	mov    %dl,-0x45(%ebp)
 ** Modified Date: 
 ******************************************************************************/
static void ExtractSrbInfo(struct SrbToAddMod srb,struct CRLC_ConfigReq_IoctrlMsg *crlc_configreq_ioctlmsg, struct MAC_LogicalChannelConfig_IoctrlMsg *mac_lcc_ioctlmsg)
{
	FIN(ExtractSrbInfo());
	crlc_configreq_ioctlmsg->rbIdentity=srb.srbIdentity;
    5d96:	88 03                	mov    %al,(%ebx)
	crlc_configreq_ioctlmsg->lcIdentity=srb.srbIdentity;
    5d98:	88 43 01             	mov    %al,0x1(%ebx)
	//	fsm_mem_cpy(&(crlc_configreq_ioctlmsg->Mode),&(srb.rlcConfig.type), sizeof(int));
	crlc_configreq_ioctlmsg->Mode=srb.rlcConfig.type;
    5d9b:	66 89 7b 02          	mov    %di,0x2(%ebx)

	mac_lcc_ioctlmsg->logicalChannelConfig=srb.logicalChannelConfig;
    5d9f:	89 4e 11             	mov    %ecx,0x11(%esi)
    5da2:	8b 55 ac             	mov    -0x54(%ebp),%edx
    5da5:	89 56 0d             	mov    %edx,0xd(%esi)
    5da8:	8b 55 b0             	mov    -0x50(%ebp),%edx
    5dab:	89 56 09             	mov    %edx,0x9(%esi)
    5dae:	8b 55 b4             	mov    -0x4c(%ebp),%edx
    5db1:	89 56 05             	mov    %edx,0x5(%esi)
    5db4:	0f b6 55 bb          	movzbl -0x45(%ebp),%edx
	mac_lcc_ioctlmsg->logicalChannelIdentity=srb.srbIdentity; //INTEGER(1,2)
    5db8:	89 06                	mov    %eax,(%esi)
	crlc_configreq_ioctlmsg->rbIdentity=srb.srbIdentity;
	crlc_configreq_ioctlmsg->lcIdentity=srb.srbIdentity;
	//	fsm_mem_cpy(&(crlc_configreq_ioctlmsg->Mode),&(srb.rlcConfig.type), sizeof(int));
	crlc_configreq_ioctlmsg->Mode=srb.rlcConfig.type;

	mac_lcc_ioctlmsg->logicalChannelConfig=srb.logicalChannelConfig;
    5dba:	88 56 04             	mov    %dl,0x4(%esi)
	mac_lcc_ioctlmsg->logicalChannelIdentity=srb.srbIdentity; //INTEGER(1,2)

	fsm_printf("[rrc] [conn_reconfig] RlcConfig Type: %d\n",srb.rlcConfig.type);
    5dbd:	89 7c 24 04          	mov    %edi,0x4(%esp)
    5dc1:	c7 04 24 78 15 00 00 	movl   $0x1578,(%esp)
    5dc8:	e8 fc ff ff ff       	call   5dc9 <AddModSrb+0xc9>
	switch(srb.rlcConfig.type)
    5dcd:	83 ff 02             	cmp    $0x2,%edi
    5dd0:	0f 84 fa 00 00 00    	je     5ed0 <AddModSrb+0x1d0>
    5dd6:	0f 87 c4 00 00 00    	ja     5ea0 <AddModSrb+0x1a0>
    5ddc:	83 ff 01             	cmp    $0x1,%edi
    5ddf:	90                   	nop
    5de0:	75 2e                	jne    5e10 <AddModSrb+0x110>
	{
		case 1:
			//AM down link
			crlc_configreq_ioctlmsg->amDwParas.timerStatusProhibit=(unsigned int)(srb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_StatusProhibit.t_StatusProhibit);
    5de2:	8b 45 dc             	mov    -0x24(%ebp),%eax
    5de5:	89 43 10             	mov    %eax,0x10(%ebx)
			crlc_configreq_ioctlmsg->amDwParas.timerReordering=(unsigned int)(srb.rlcConfig.rlcConfigType.am.dl_AM_RLC.t_Reordering.t_Reordering);
    5de8:	8b 45 d8             	mov    -0x28(%ebp),%eax
    5deb:	89 43 14             	mov    %eax,0x14(%ebx)

			//AM up link
			crlc_configreq_ioctlmsg->amUpParas.timerPollRetransmit=(unsigned int)(srb.rlcConfig.rlcConfigType.am.ul_AM_RLC.t_PollRetransmit.t_PollRetransmittype);
    5dee:	8b 45 c8             	mov    -0x38(%ebp),%eax
    5df1:	89 43 18             	mov    %eax,0x18(%ebx)
			crlc_configreq_ioctlmsg->amUpParas.PollPDU=(unsigned int)(srb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollPDU.pollPDUtype);
    5df4:	8b 45 cc             	mov    -0x34(%ebp),%eax
    5df7:	66 89 43 1c          	mov    %ax,0x1c(%ebx)
			crlc_configreq_ioctlmsg->amUpParas.PollBYTE=(unsigned int)(srb.rlcConfig.rlcConfigType.am.ul_AM_RLC.pollByte.pollByte);
    5dfb:	8b 45 d0             	mov    -0x30(%ebp),%eax
    5dfe:	66 89 43 1e          	mov    %ax,0x1e(%ebx)
			crlc_configreq_ioctlmsg->amUpParas.maxRetxThreshold=(unsigned int)(srb.rlcConfig.rlcConfigType.am.ul_AM_RLC.maxRetxThreshold);
    5e02:	8b 45 d4             	mov    -0x2c(%ebp),%eax
    5e05:	66 89 43 20          	mov    %ax,0x20(%ebx)
    5e09:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
	struct MAC_LogicalChannelConfig_IoctrlMsg *mac_lcc_ioctlmsg;
	crlc_configreq_ioctlmsg = (struct CRLC_ConfigReq_IoctrlMsg *)fsm_mem_alloc(sizeof(struct CRLC_ConfigReq_IoctrlMsg));
	mac_lcc_ioctlmsg = (struct MAC_LogicalChannelConfig_IoctrlMsg *) fsm_mem_alloc(sizeof(struct MAC_LogicalChannelConfig_IoctrlMsg));

	ExtractSrbInfo(srb,crlc_configreq_ioctlmsg,mac_lcc_ioctlmsg);
	fsm_printf("[rrc] [conn_reconfig] IN AddModSrb: crlc_configreq_ioctlmsg->Mode: %d\n",crlc_configreq_ioctlmsg->Mode);
    5e10:	0f b7 43 02          	movzwl 0x2(%ebx),%eax
    5e14:	c7 04 24 a4 15 00 00 	movl   $0x15a4,(%esp)
    5e1b:	89 44 24 04          	mov    %eax,0x4(%esp)
    5e1f:	e8 fc ff ff ff       	call   5e20 <AddModSrb+0x120>

	if (crlc_configreq_ioctlmsg != NULL)
    5e24:	85 db                	test   %ebx,%ebx
    5e26:	74 28                	je     5e50 <AddModSrb+0x150>
	{
		fsm_printf("[rrc] [conn_reconfig] crlc_configreq_ioctlmsg->lcIdentity= %d\n",crlc_configreq_ioctlmsg->lcIdentity);
    5e28:	0f b6 43 01          	movzbl 0x1(%ebx),%eax
    5e2c:	c7 04 24 ec 15 00 00 	movl   $0x15ec,(%esp)
    5e33:	89 44 24 04          	mov    %eax,0x4(%esp)
    5e37:	e8 fc ff ff ff       	call   5e38 <AddModSrb+0x138>
		fsm_printf("[rrc] [conn_reconfig] sizeof(struct CRLC_ConfigReq_IoctrlMsg= %d\n)",sizeof(struct CRLC_ConfigReq_IoctrlMsg));
    5e3c:	c7 44 24 04 24 00 00 	movl   $0x24,0x4(%esp)
    5e43:	00 
    5e44:	c7 04 24 2c 16 00 00 	movl   $0x162c,(%esp)
    5e4b:	e8 fc ff ff ff       	call   5e4c <AddModSrb+0x14c>
	}

	ioccmdToRLC=(add_or_mod==0? IOCCMD_RRCTORLC_BUILD:IOCCMD_RRCTORLC_RECONFIG);
    5e50:	83 7d 40 01          	cmpl   $0x1,0x40(%ebp)
	//fix me:establish PDCP entity

	//send ioctl msg for rlc to establish/reconfigure srb
	//send ioctl msg for mac to establish/reconfigure DCCH

	fsm_do_ioctrl(STRM_TO_RLC,ioccmdToRLC,(void*)crlc_configreq_ioctlmsg,sizeof(struct CRLC_ConfigReq_IoctrlMsg));
    5e54:	89 d9                	mov    %ebx,%ecx
    5e56:	b8 01 00 00 00       	mov    $0x1,%eax
    5e5b:	c7 04 24 24 00 00 00 	movl   $0x24,(%esp)
	{
		fsm_printf("[rrc] [conn_reconfig] crlc_configreq_ioctlmsg->lcIdentity= %d\n",crlc_configreq_ioctlmsg->lcIdentity);
		fsm_printf("[rrc] [conn_reconfig] sizeof(struct CRLC_ConfigReq_IoctrlMsg= %d\n)",sizeof(struct CRLC_ConfigReq_IoctrlMsg));
	}

	ioccmdToRLC=(add_or_mod==0? IOCCMD_RRCTORLC_BUILD:IOCCMD_RRCTORLC_RECONFIG);
    5e62:	19 d2                	sbb    %edx,%edx
    5e64:	83 e2 27             	and    $0x27,%edx
    5e67:	83 c2 02             	add    $0x2,%edx
	//fix me:establish PDCP entity

	//send ioctl msg for rlc to establish/reconfigure srb
	//send ioctl msg for mac to establish/reconfigure DCCH

	fsm_do_ioctrl(STRM_TO_RLC,ioccmdToRLC,(void*)crlc_configreq_ioctlmsg,sizeof(struct CRLC_ConfigReq_IoctrlMsg));
    5e6a:	e8 fc ff ff ff       	call   5e6b <AddModSrb+0x16b>
	fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_CONFIG_LCC,(void*)mac_lcc_ioctlmsg,sizeof(struct MAC_LogicalChannelConfig_IoctrlMsg));
    5e6f:	89 f1                	mov    %esi,%ecx
    5e71:	ba 11 00 00 00       	mov    $0x11,%edx
    5e76:	b8 02 00 00 00       	mov    $0x2,%eax
    5e7b:	c7 04 24 15 00 00 00 	movl   $0x15,(%esp)
    5e82:	e8 fc ff ff ff       	call   5e83 <AddModSrb+0x183>

	fsm_mem_free(crlc_configreq_ioctlmsg);
    5e87:	89 d8                	mov    %ebx,%eax
    5e89:	e8 fc ff ff ff       	call   5e8a <AddModSrb+0x18a>
	fsm_mem_free(mac_lcc_ioctlmsg);
    5e8e:	89 f0                	mov    %esi,%eax
    5e90:	e8 fc ff ff ff       	call   5e91 <AddModSrb+0x191>

	FOUT;
}
    5e95:	83 c4 50             	add    $0x50,%esp
    5e98:	5b                   	pop    %ebx
    5e99:	5e                   	pop    %esi
    5e9a:	5f                   	pop    %edi
    5e9b:	5d                   	pop    %ebp
    5e9c:	c3                   	ret    
    5e9d:	8d 76 00             	lea    0x0(%esi),%esi

	mac_lcc_ioctlmsg->logicalChannelConfig=srb.logicalChannelConfig;
	mac_lcc_ioctlmsg->logicalChannelIdentity=srb.srbIdentity; //INTEGER(1,2)

	fsm_printf("[rrc] [conn_reconfig] RlcConfig Type: %d\n",srb.rlcConfig.type);
	switch(srb.rlcConfig.type)
    5ea0:	83 ff 03             	cmp    $0x3,%edi
    5ea3:	74 1b                	je     5ec0 <AddModSrb+0x1c0>
    5ea5:	83 ff 04             	cmp    $0x4,%edi
    5ea8:	0f 85 62 ff ff ff    	jne    5e10 <AddModSrb+0x110>
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=(unsigned int)srb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength.sn_FieldLength;
			//		crlc_configreq_ioctlmsg->Mode = 3;
			break;
		case 4:
			//um down link
			crlc_configreq_ioctlmsg->umDwParas.snFiledLength=(unsigned int)srb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.sn_FieldLength.sn_FieldLength;
    5eae:	8b 45 cc             	mov    -0x34(%ebp),%eax
    5eb1:	66 89 43 04          	mov    %ax,0x4(%ebx)
			crlc_configreq_ioctlmsg->umDwParas.timerReordering=(unsigned int)srb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.t_Reordering.t_Reordering;
    5eb5:	8b 45 d0             	mov    -0x30(%ebp),%eax
    5eb8:	89 43 08             	mov    %eax,0x8(%ebx)
    5ebb:	e9 50 ff ff ff       	jmp    5e10 <AddModSrb+0x110>
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=(unsigned int)srb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength.sn_FieldLength;
			//		crlc_configreq_ioctlmsg->Mode = 2;
			break;
		case 3:
			//um up link
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=(unsigned int)srb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength.sn_FieldLength;
    5ec0:	8b 45 c8             	mov    -0x38(%ebp),%eax
    5ec3:	66 89 43 0c          	mov    %ax,0xc(%ebx)
    5ec7:	e9 44 ff ff ff       	jmp    5e10 <AddModSrb+0x110>
    5ecc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

			//		crlc_configreq_ioctlmsg->Mode = 1;
			break;
		case 2:
			//um down link
			crlc_configreq_ioctlmsg->umDwParas.snFiledLength=(unsigned int)srb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.sn_FieldLength.sn_FieldLength;
    5ed0:	8b 45 cc             	mov    -0x34(%ebp),%eax
    5ed3:	66 89 43 04          	mov    %ax,0x4(%ebx)
			crlc_configreq_ioctlmsg->umDwParas.timerReordering=(unsigned int)srb.rlcConfig.rlcConfigType.um_Bi_Directional.dl_UM_RLC.t_Reordering.t_Reordering;
    5ed7:	8b 45 d0             	mov    -0x30(%ebp),%eax
    5eda:	89 43 08             	mov    %eax,0x8(%ebx)

			//um up link
			crlc_configreq_ioctlmsg->umUpParas.snFiledLength=(unsigned int)srb.rlcConfig.rlcConfigType.um_Bi_Directional.ul_UM_RLC.sn_FieldLength.sn_FieldLength;
    5edd:	8b 45 c8             	mov    -0x38(%ebp),%eax
    5ee0:	66 89 43 0c          	mov    %ax,0xc(%ebx)
    5ee4:	e9 27 ff ff ff       	jmp    5e10 <AddModSrb+0x110>
    5ee9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00005ef0 <ApplySrbToAdd>:
 **-----------------------------------------------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void ApplySrbToAdd(struct SrbToAddModList  srb)
{
    5ef0:	55                   	push   %ebp
    5ef1:	89 e5                	mov    %esp,%ebp
    5ef3:	57                   	push   %edi
    5ef4:	56                   	push   %esi
    5ef5:	53                   	push   %ebx
    5ef6:	81 ec b8 00 00 00    	sub    $0xb8,%esp
    5efc:	e8 fc ff ff ff       	call   5efd <ApplySrbToAdd+0xd>
	FIN(ApplySrbToAdd());
	int srbIndex;
	struct SrbToAddMod eachSrb;
	struct LteSignalingRadioBearerInfo *localSrbConfig=NULL;
	for(srbIndex = 0; srbIndex < srb.num; srbIndex ++)		
    5f01:	8b 55 08             	mov    0x8(%ebp),%edx
    5f04:	85 d2                	test   %edx,%edx
    5f06:	0f 84 e0 01 00 00    	je     60ec <ApplySrbToAdd+0x1fc>
    5f0c:	8d 5d 0c             	lea    0xc(%ebp),%ebx
    5f0f:	31 f6                	xor    %esi,%esi
	{
		fsm_printf("[rrc] srbIndex = %d, srbId = %d.\n", srbIndex, srb.srbList[srbIndex].srbIdentity);
    5f11:	8b 03                	mov    (%ebx),%eax
    5f13:	89 74 24 04          	mov    %esi,0x4(%esp)
    5f17:	c7 04 24 70 16 00 00 	movl   $0x1670,(%esp)
    5f1e:	89 44 24 08          	mov    %eax,0x8(%esp)
    5f22:	e8 fc ff ff ff       	call   5f23 <ApplySrbToAdd+0x33>
		fsm_printf("[rrc] srbIdentity @ %p.\n", &(srb.srbList[srbIndex].srbIdentity));
    5f27:	6b c6 38             	imul   $0x38,%esi,%eax
    5f2a:	8d 44 05 0c          	lea    0xc(%ebp,%eax,1),%eax
    5f2e:	89 44 24 04          	mov    %eax,0x4(%esp)
    5f32:	c7 04 24 a9 02 00 00 	movl   $0x2a9,(%esp)
    5f39:	e8 fc ff ff ff       	call   5f3a <ApplySrbToAdd+0x4a>
		eachSrb = srb.srbList[srbIndex];
    5f3e:	8b 3b                	mov    (%ebx),%edi
    5f40:	89 7d bc             	mov    %edi,-0x44(%ebp)
    5f43:	8b 4b 04             	mov    0x4(%ebx),%ecx
    5f46:	89 4d c0             	mov    %ecx,-0x40(%ebp)
    5f49:	8b 43 08             	mov    0x8(%ebx),%eax
    5f4c:	89 85 78 ff ff ff    	mov    %eax,-0x88(%ebp)
    5f52:	89 45 c4             	mov    %eax,-0x3c(%ebp)
    5f55:	8b 53 0c             	mov    0xc(%ebx),%edx
    5f58:	89 55 94             	mov    %edx,-0x6c(%ebp)
    5f5b:	89 55 c8             	mov    %edx,-0x38(%ebp)
    5f5e:	8b 43 10             	mov    0x10(%ebx),%eax
    5f61:	89 45 90             	mov    %eax,-0x70(%ebp)
    5f64:	89 45 cc             	mov    %eax,-0x34(%ebp)
    5f67:	8b 53 14             	mov    0x14(%ebx),%edx
    5f6a:	89 55 8c             	mov    %edx,-0x74(%ebp)
    5f6d:	89 55 d0             	mov    %edx,-0x30(%ebp)
    5f70:	8b 43 18             	mov    0x18(%ebx),%eax
    5f73:	89 45 88             	mov    %eax,-0x78(%ebp)
    5f76:	89 45 d4             	mov    %eax,-0x2c(%ebp)
    5f79:	8b 53 1c             	mov    0x1c(%ebx),%edx
    5f7c:	89 55 84             	mov    %edx,-0x7c(%ebp)
    5f7f:	89 55 d8             	mov    %edx,-0x28(%ebp)
    5f82:	8b 43 20             	mov    0x20(%ebx),%eax
    5f85:	89 45 80             	mov    %eax,-0x80(%ebp)
    5f88:	89 45 dc             	mov    %eax,-0x24(%ebp)
    5f8b:	8b 53 24             	mov    0x24(%ebx),%edx
    5f8e:	89 55 e0             	mov    %edx,-0x20(%ebp)
    5f91:	8b 43 28             	mov    0x28(%ebx),%eax
    5f94:	66 c1 ea 08          	shr    $0x8,%dx
    5f98:	89 45 e4             	mov    %eax,-0x1c(%ebp)
    5f9b:	8b 43 2c             	mov    0x2c(%ebx),%eax
    5f9e:	89 45 e8             	mov    %eax,-0x18(%ebp)
    5fa1:	8b 43 30             	mov    0x30(%ebx),%eax
    5fa4:	89 45 ec             	mov    %eax,-0x14(%ebp)
    5fa7:	8b 43 34             	mov    0x34(%ebx),%eax
    5faa:	89 45 f0             	mov    %eax,-0x10(%ebp)
    5fad:	8b 45 e6             	mov    -0x1a(%ebp),%eax
    5fb0:	88 55 9c             	mov    %dl,-0x64(%ebp)
    5fb3:	8b 55 e2             	mov    -0x1e(%ebp),%edx
    5fb6:	89 45 b0             	mov    %eax,-0x50(%ebp)
    5fb9:	8b 45 ee             	mov    -0x12(%ebp),%eax
    5fbc:	89 55 ac             	mov    %edx,-0x54(%ebp)
    5fbf:	8b 55 ea             	mov    -0x16(%ebp),%edx
    5fc2:	89 45 b8             	mov    %eax,-0x48(%ebp)
    5fc5:	89 55 b4             	mov    %edx,-0x4c(%ebp)
		localSrbConfig=ueSrbConfig[eachSrb.srbIdentity-1];
    5fc8:	8d 57 ff             	lea    -0x1(%edi),%edx
    5fcb:	8b 04 95 00 00 00 00 	mov    0x0(,%edx,4),%eax
    5fd2:	89 55 98             	mov    %edx,-0x68(%ebp)
		if(localSrbConfig == NULL)
    5fd5:	85 c0                	test   %eax,%eax
    5fd7:	0f 84 2b 01 00 00    	je     6108 <ApplySrbToAdd+0x218>
			fsm_printf("[rrc] [conn_reconfig] add a srb ,srbid=%d\n",ueSrbConfig[eachSrb.srbIdentity-1]->srbIdentity);//test
		}
		else
		{
			//reconfig the srb
			AddModSrb(eachSrb,1);
    5fdd:	0f b6 55 9c          	movzbl -0x64(%ebp),%edx
    5fe1:	c7 44 24 38 01 00 00 	movl   $0x1,0x38(%esp)
    5fe8:	00 
    5fe9:	89 3c 24             	mov    %edi,(%esp)
    5fec:	89 4c 24 04          	mov    %ecx,0x4(%esp)
    5ff0:	88 55 e1             	mov    %dl,-0x1f(%ebp)
    5ff3:	8b 55 ac             	mov    -0x54(%ebp),%edx
    5ff6:	89 7d bc             	mov    %edi,-0x44(%ebp)
    5ff9:	89 55 e2             	mov    %edx,-0x1e(%ebp)
    5ffc:	8b 55 b0             	mov    -0x50(%ebp),%edx
    5fff:	89 55 e6             	mov    %edx,-0x1a(%ebp)
    6002:	8b 55 b4             	mov    -0x4c(%ebp),%edx
    6005:	89 55 ea             	mov    %edx,-0x16(%ebp)
    6008:	8b 55 b8             	mov    -0x48(%ebp),%edx
    600b:	89 55 ee             	mov    %edx,-0x12(%ebp)
    600e:	8b 95 78 ff ff ff    	mov    -0x88(%ebp),%edx
    6014:	89 54 24 08          	mov    %edx,0x8(%esp)
    6018:	8b 55 94             	mov    -0x6c(%ebp),%edx
    601b:	89 54 24 0c          	mov    %edx,0xc(%esp)
    601f:	8b 55 90             	mov    -0x70(%ebp),%edx
    6022:	89 54 24 10          	mov    %edx,0x10(%esp)
    6026:	8b 55 8c             	mov    -0x74(%ebp),%edx
    6029:	89 54 24 14          	mov    %edx,0x14(%esp)
    602d:	8b 55 88             	mov    -0x78(%ebp),%edx
    6030:	89 54 24 18          	mov    %edx,0x18(%esp)
    6034:	8b 55 84             	mov    -0x7c(%ebp),%edx
    6037:	89 54 24 1c          	mov    %edx,0x1c(%esp)
    603b:	8b 55 80             	mov    -0x80(%ebp),%edx
    603e:	89 54 24 20          	mov    %edx,0x20(%esp)
    6042:	8b 55 e0             	mov    -0x20(%ebp),%edx
    6045:	89 54 24 24          	mov    %edx,0x24(%esp)
    6049:	8b 55 e4             	mov    -0x1c(%ebp),%edx
    604c:	89 54 24 28          	mov    %edx,0x28(%esp)
    6050:	8b 55 e8             	mov    -0x18(%ebp),%edx
    6053:	89 54 24 2c          	mov    %edx,0x2c(%esp)
    6057:	8b 55 ec             	mov    -0x14(%ebp),%edx
    605a:	89 85 7c ff ff ff    	mov    %eax,-0x84(%ebp)
    6060:	89 54 24 30          	mov    %edx,0x30(%esp)
    6064:	8b 55 f0             	mov    -0x10(%ebp),%edx
    6067:	89 54 24 34          	mov    %edx,0x34(%esp)
    606b:	e8 90 fc ff ff       	call   5d00 <AddModSrb>

			//back up older config for recover the SRB hanged up
			localSrbConfig->rlcConfig=eachSrb.rlcConfig;
    6070:	8b 55 c4             	mov    -0x3c(%ebp),%edx
    6073:	8b 85 7c ff ff ff    	mov    -0x84(%ebp),%eax
    6079:	89 50 04             	mov    %edx,0x4(%eax)
    607c:	8b 55 c8             	mov    -0x38(%ebp),%edx
    607f:	89 50 08             	mov    %edx,0x8(%eax)
    6082:	8b 55 cc             	mov    -0x34(%ebp),%edx
    6085:	89 50 0c             	mov    %edx,0xc(%eax)
    6088:	8b 55 d0             	mov    -0x30(%ebp),%edx
    608b:	89 50 10             	mov    %edx,0x10(%eax)
    608e:	8b 55 d4             	mov    -0x2c(%ebp),%edx
    6091:	89 50 14             	mov    %edx,0x14(%eax)
    6094:	8b 55 d8             	mov    -0x28(%ebp),%edx
    6097:	89 50 18             	mov    %edx,0x18(%eax)
    609a:	8b 55 dc             	mov    -0x24(%ebp),%edx
    609d:	89 50 1c             	mov    %edx,0x1c(%eax)
			localSrbConfig->logicalChannelConfig=eachSrb.logicalChannelConfig;
    60a0:	8b 55 b8             	mov    -0x48(%ebp),%edx
    60a3:	89 50 2e             	mov    %edx,0x2e(%eax)
    60a6:	8b 55 b4             	mov    -0x4c(%ebp),%edx
    60a9:	89 50 2a             	mov    %edx,0x2a(%eax)
    60ac:	8b 55 b0             	mov    -0x50(%ebp),%edx
    60af:	89 50 26             	mov    %edx,0x26(%eax)
    60b2:	8b 55 ac             	mov    -0x54(%ebp),%edx
    60b5:	89 50 22             	mov    %edx,0x22(%eax)
    60b8:	0f b6 55 9c          	movzbl -0x64(%ebp),%edx
    60bc:	88 50 21             	mov    %dl,0x21(%eax)
			fsm_printf("[rrc] [conn_reconfig] reconfig a srb ,srbid=%d\n",ueSrbConfig[eachSrb.srbIdentity-1]->srbIdentity);//test
    60bf:	8b 55 98             	mov    -0x68(%ebp),%edx
    60c2:	8b 04 95 00 00 00 00 	mov    0x0(,%edx,4),%eax
    60c9:	0f b6 40 01          	movzbl 0x1(%eax),%eax
    60cd:	c7 04 24 c0 16 00 00 	movl   $0x16c0,(%esp)
    60d4:	89 44 24 04          	mov    %eax,0x4(%esp)
    60d8:	e8 fc ff ff ff       	call   60d9 <ApplySrbToAdd+0x1e9>
{
	FIN(ApplySrbToAdd());
	int srbIndex;
	struct SrbToAddMod eachSrb;
	struct LteSignalingRadioBearerInfo *localSrbConfig=NULL;
	for(srbIndex = 0; srbIndex < srb.num; srbIndex ++)		
    60dd:	83 c6 01             	add    $0x1,%esi
    60e0:	83 c3 38             	add    $0x38,%ebx
    60e3:	39 75 08             	cmp    %esi,0x8(%ebp)
    60e6:	0f 87 25 fe ff ff    	ja     5f11 <ApplySrbToAdd+0x21>
			localSrbConfig->rlcConfig=eachSrb.rlcConfig;
			localSrbConfig->logicalChannelConfig=eachSrb.logicalChannelConfig;
			fsm_printf("[rrc] [conn_reconfig] reconfig a srb ,srbid=%d\n",ueSrbConfig[eachSrb.srbIdentity-1]->srbIdentity);//test
		}
	}
	fsm_printf("[rrc] [conn_reconfig] ApplySrbToAdd() is done!.\n");//test
    60ec:	c7 04 24 f0 16 00 00 	movl   $0x16f0,(%esp)
    60f3:	e8 fc ff ff ff       	call   60f4 <ApplySrbToAdd+0x204>
	FOUT;
}
    60f8:	81 c4 b8 00 00 00    	add    $0xb8,%esp
    60fe:	5b                   	pop    %ebx
    60ff:	5e                   	pop    %esi
    6100:	5f                   	pop    %edi
    6101:	5d                   	pop    %ebp
    6102:	c3                   	ret    
    6103:	90                   	nop
    6104:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
		fsm_printf("[rrc] srbIdentity @ %p.\n", &(srb.srbList[srbIndex].srbIdentity));
		eachSrb = srb.srbList[srbIndex];
		localSrbConfig=ueSrbConfig[eachSrb.srbIdentity-1];
		if(localSrbConfig == NULL)
		{
			localSrbConfig=fsm_mem_alloc(sizeof(struct LteSignalingRadioBearerInfo));
    6108:	b0 34                	mov    $0x34,%al
    610a:	e8 fc ff ff ff       	call   610b <ApplySrbToAdd+0x21b>
			//build the srb
			AddModSrb(eachSrb,0);
    610f:	0f b6 55 9c          	movzbl -0x64(%ebp),%edx
    6113:	89 7d bc             	mov    %edi,-0x44(%ebp)
    6116:	88 55 e1             	mov    %dl,-0x1f(%ebp)
    6119:	8b 55 ac             	mov    -0x54(%ebp),%edx
    611c:	89 3c 24             	mov    %edi,(%esp)
    611f:	c7 44 24 38 00 00 00 	movl   $0x0,0x38(%esp)
    6126:	00 
    6127:	89 55 e2             	mov    %edx,-0x1e(%ebp)
    612a:	8b 55 b0             	mov    -0x50(%ebp),%edx
    612d:	89 55 e6             	mov    %edx,-0x1a(%ebp)
    6130:	8b 55 b4             	mov    -0x4c(%ebp),%edx
    6133:	89 55 ea             	mov    %edx,-0x16(%ebp)
    6136:	8b 55 b8             	mov    -0x48(%ebp),%edx
    6139:	89 55 ee             	mov    %edx,-0x12(%ebp)
    613c:	8b 55 c0             	mov    -0x40(%ebp),%edx
    613f:	89 54 24 04          	mov    %edx,0x4(%esp)
    6143:	8b 55 c4             	mov    -0x3c(%ebp),%edx
    6146:	89 54 24 08          	mov    %edx,0x8(%esp)
    614a:	8b 55 c8             	mov    -0x38(%ebp),%edx
    614d:	89 54 24 0c          	mov    %edx,0xc(%esp)
    6151:	8b 55 cc             	mov    -0x34(%ebp),%edx
    6154:	89 54 24 10          	mov    %edx,0x10(%esp)
    6158:	8b 55 d0             	mov    -0x30(%ebp),%edx
    615b:	89 54 24 14          	mov    %edx,0x14(%esp)
    615f:	8b 55 d4             	mov    -0x2c(%ebp),%edx
    6162:	89 54 24 18          	mov    %edx,0x18(%esp)
    6166:	8b 55 d8             	mov    -0x28(%ebp),%edx
    6169:	89 54 24 1c          	mov    %edx,0x1c(%esp)
    616d:	8b 55 dc             	mov    -0x24(%ebp),%edx
    6170:	89 54 24 20          	mov    %edx,0x20(%esp)
    6174:	8b 55 e0             	mov    -0x20(%ebp),%edx
    6177:	89 54 24 24          	mov    %edx,0x24(%esp)
    617b:	8b 55 e4             	mov    -0x1c(%ebp),%edx
    617e:	89 54 24 28          	mov    %edx,0x28(%esp)
    6182:	8b 55 e8             	mov    -0x18(%ebp),%edx
    6185:	89 54 24 2c          	mov    %edx,0x2c(%esp)
    6189:	8b 55 ec             	mov    -0x14(%ebp),%edx
    618c:	89 85 7c ff ff ff    	mov    %eax,-0x84(%ebp)
    6192:	89 54 24 30          	mov    %edx,0x30(%esp)
    6196:	8b 55 f0             	mov    -0x10(%ebp),%edx
    6199:	89 54 24 34          	mov    %edx,0x34(%esp)
    619d:	e8 5e fb ff ff       	call   5d00 <AddModSrb>

			//fix me:srb status managment
			localSrbConfig->srbStatus=1;//0,hang up
    61a2:	8b 85 7c ff ff ff    	mov    -0x84(%ebp),%eax
			localSrbConfig->srbIdentity=eachSrb.srbIdentity;
    61a8:	89 fa                	mov    %edi,%edx
			localSrbConfig=fsm_mem_alloc(sizeof(struct LteSignalingRadioBearerInfo));
			//build the srb
			AddModSrb(eachSrb,0);

			//fix me:srb status managment
			localSrbConfig->srbStatus=1;//0,hang up
    61aa:	c6 00 01             	movb   $0x1,(%eax)
			localSrbConfig->srbIdentity=eachSrb.srbIdentity;
    61ad:	88 50 01             	mov    %dl,0x1(%eax)
			localSrbConfig->lcid=(u8)eachSrb.srbIdentity;
    61b0:	88 50 20             	mov    %dl,0x20(%eax)

			//back up older config for recover the SRB hanged up
			localSrbConfig->rlcConfig=eachSrb.rlcConfig;
    61b3:	8b 55 c4             	mov    -0x3c(%ebp),%edx
    61b6:	89 50 04             	mov    %edx,0x4(%eax)
    61b9:	8b 55 c8             	mov    -0x38(%ebp),%edx
    61bc:	89 50 08             	mov    %edx,0x8(%eax)
    61bf:	8b 55 cc             	mov    -0x34(%ebp),%edx
    61c2:	89 50 0c             	mov    %edx,0xc(%eax)
    61c5:	8b 55 d0             	mov    -0x30(%ebp),%edx
    61c8:	89 50 10             	mov    %edx,0x10(%eax)
    61cb:	8b 55 d4             	mov    -0x2c(%ebp),%edx
    61ce:	89 50 14             	mov    %edx,0x14(%eax)
    61d1:	8b 55 d8             	mov    -0x28(%ebp),%edx
    61d4:	89 50 18             	mov    %edx,0x18(%eax)
    61d7:	8b 55 dc             	mov    -0x24(%ebp),%edx
    61da:	89 50 1c             	mov    %edx,0x1c(%eax)
			localSrbConfig->logicalChannelConfig=eachSrb.logicalChannelConfig;
    61dd:	8b 55 b8             	mov    -0x48(%ebp),%edx
    61e0:	89 50 2e             	mov    %edx,0x2e(%eax)
    61e3:	8b 55 b4             	mov    -0x4c(%ebp),%edx
    61e6:	89 50 2a             	mov    %edx,0x2a(%eax)
    61e9:	8b 55 b0             	mov    -0x50(%ebp),%edx
    61ec:	89 50 26             	mov    %edx,0x26(%eax)
    61ef:	8b 55 ac             	mov    -0x54(%ebp),%edx
    61f2:	89 50 22             	mov    %edx,0x22(%eax)
    61f5:	0f b6 55 9c          	movzbl -0x64(%ebp),%edx
    61f9:	88 50 21             	mov    %dl,0x21(%eax)
			ueSrbConfig[eachSrb.srbIdentity-1]=localSrbConfig;
    61fc:	8b 55 98             	mov    -0x68(%ebp),%edx
    61ff:	89 04 95 00 00 00 00 	mov    %eax,0x0(,%edx,4)
			fsm_printf("[rrc] [conn_reconfig] add a srb ,srbid=%d\n",ueSrbConfig[eachSrb.srbIdentity-1]->srbIdentity);//test
    6206:	0f b6 40 01          	movzbl 0x1(%eax),%eax
    620a:	c7 04 24 94 16 00 00 	movl   $0x1694,(%esp)
    6211:	89 44 24 04          	mov    %eax,0x4(%esp)
    6215:	e8 fc ff ff ff       	call   6216 <ApplySrbToAdd+0x326>
    621a:	e9 be fe ff ff       	jmp    60dd <ApplySrbToAdd+0x1ed>
    621f:	90                   	nop

00006220 <ApplyRadioResourceConfigDedicated>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
static void ApplyRadioResourceConfigDedicated (struct RadioResourceConfigDedicated rrcd) 
{ 	
    6220:	55                   	push   %ebp
    6221:	89 e5                	mov    %esp,%ebp
    6223:	81 ec 6c 03 00 00    	sub    $0x36c,%esp
    6229:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    622c:	89 75 f8             	mov    %esi,-0x8(%ebp)
    622f:	89 7d fc             	mov    %edi,-0x4(%ebp)
    6232:	e8 fc ff ff ff       	call   6233 <ApplyRadioResourceConfigDedicated+0x13>
    6237:	0f b6 85 7c 03 00 00 	movzbl 0x37c(%ebp),%eax
	FIN(ApplyRadioResourceConfigDedicated()); 	
	if(rrcd.haveSrbToAddModList) { 	
    623e:	80 7d 08 00          	cmpb   $0x0,0x8(%ebp)
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
static void ApplyRadioResourceConfigDedicated (struct RadioResourceConfigDedicated rrcd) 
{ 	
    6242:	0f b6 9d 80 00 00 00 	movzbl 0x80(%ebp),%ebx
    6249:	0f b6 95 48 03 00 00 	movzbl 0x348(%ebp),%edx
    6250:	88 85 5e ff ff ff    	mov    %al,-0xa2(%ebp)
    6256:	0f b6 85 d0 03 00 00 	movzbl 0x3d0(%ebp),%eax
    625d:	88 85 5f ff ff ff    	mov    %al,-0xa1(%ebp)
	FIN(ApplyRadioResourceConfigDedicated()); 	
	if(rrcd.haveSrbToAddModList) { 	
    6263:	0f 85 67 01 00 00    	jne    63d0 <ApplyRadioResourceConfigDedicated+0x1b0>
		fsm_printf("[rrc] [conn_reconfig] ApplySrbToAdd!\n");//test	 		
		ApplySrbToAdd(rrcd.srbToAddModList); 	
	} 	
	if(rrcd.haveDrbToAddModList) { 		
    6269:	84 db                	test   %bl,%bl
    626b:	0f 85 27 01 00 00    	jne    6398 <ApplyRadioResourceConfigDedicated+0x178>
		fsm_printf("[rrc] [conn_reconfig] ApplyDrbToAdd!\n");//test	
		ApplyDrbToAdd(rrcd.drbToAddModList); 	
	} 	
	if(rrcd.haveDrbToReleaseList) { 		
    6271:	84 d2                	test   %dl,%dl
    6273:	0f 85 8f 00 00 00    	jne    6308 <ApplyRadioResourceConfigDedicated+0xe8>
		fsm_printf("[rrc] [conn_reconfig] ApplyDrbToRelease!\n");	//test
		ApplyDrbToRelease(rrcd.drbToReleaseList); 
		//fsm_printf("		ApplySrbToRelease!\n");//test	
		//ApplySrbToRelease();//test	
	} 	
	if(rrcd.haveMAC_MainConfig) { 		
    6279:	80 bd 5e ff ff ff 00 	cmpb   $0x0,-0xa2(%ebp)
    6280:	75 4e                	jne    62d0 <ApplyRadioResourceConfigDedicated+0xb0>
		ApplyMacMainConfig(rrcd.mac_MainConfig); 	
	} 	
	if(rrcd.haveSPS_Config) { 		
    6282:	80 bd 5f ff ff ff 00 	cmpb   $0x0,-0xa1(%ebp)
    6289:	74 29                	je     62b4 <ApplyRadioResourceConfigDedicated+0x94>
    628b:	8d 7d b0             	lea    -0x50(%ebp),%edi
    628e:	b9 11 00 00 00       	mov    $0x11,%ecx
    6293:	8d b5 d4 03 00 00    	lea    0x3d4(%ebp),%esi
 ** Modified Date: 
 ******************************************************************************/
static void ApplySpsConfig(struct SPS_Config sps)
{
	FIN(ApplySpsConfig());
	fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_CONFIG_SPS,(void*)&sps,sizeof(sps));
    6299:	ba 10 00 00 00       	mov    $0x10,%edx
		//ApplySrbToRelease();//test	
	} 	
	if(rrcd.haveMAC_MainConfig) { 		
		ApplyMacMainConfig(rrcd.mac_MainConfig); 	
	} 	
	if(rrcd.haveSPS_Config) { 		
    629e:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 ** Modified Date: 
 ******************************************************************************/
static void ApplySpsConfig(struct SPS_Config sps)
{
	FIN(ApplySpsConfig());
	fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_CONFIG_SPS,(void*)&sps,sizeof(sps));
    62a0:	b8 02 00 00 00       	mov    $0x2,%eax
    62a5:	8d 4d b0             	lea    -0x50(%ebp),%ecx
    62a8:	c7 04 24 44 00 00 00 	movl   $0x44,(%esp)
    62af:	e8 fc ff ff ff       	call   62b0 <ApplyRadioResourceConfigDedicated+0x90>
	} 
	if(rrcd.havePhysicalConfigDedicated) { 		
		ApplyPhysicalConfigDedicated(rrcd.physicalConfigDedicated); 	
	} 	

	fsm_printf("[rrc] [conn_reconfig] UE is doing RadioResourceConfigDedicated Reconfig !\n");
    62b4:	c7 04 24 a0 17 00 00 	movl   $0x17a0,(%esp)
    62bb:	e8 fc ff ff ff       	call   62bc <ApplyRadioResourceConfigDedicated+0x9c>
	FOUT;
} 
    62c0:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    62c3:	8b 75 f8             	mov    -0x8(%ebp),%esi
    62c6:	8b 7d fc             	mov    -0x4(%ebp),%edi
    62c9:	89 ec                	mov    %ebp,%esp
    62cb:	5d                   	pop    %ebp
    62cc:	c3                   	ret    
    62cd:	8d 76 00             	lea    0x0(%esi),%esi
		fsm_printf("[rrc] [conn_reconfig] ApplyDrbToRelease!\n");	//test
		ApplyDrbToRelease(rrcd.drbToReleaseList); 
		//fsm_printf("		ApplySrbToRelease!\n");//test	
		//ApplySrbToRelease();//test	
	} 	
	if(rrcd.haveMAC_MainConfig) { 		
    62d0:	8d bd 60 ff ff ff    	lea    -0xa0(%ebp),%edi
    62d6:	b9 14 00 00 00       	mov    $0x14,%ecx
    62db:	8d b5 80 03 00 00    	lea    0x380(%ebp),%esi
 ** Modified Date: 
 ******************************************************************************/
static void ApplyMacMainConfig(struct MAC_MainConfig mac)
{
	FIN(ApplyMacMainConfig());
	fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_CONFIG_MAC_MAIN,(void*)&mac,sizeof(mac));
    62e1:	ba 09 00 00 00       	mov    $0x9,%edx
		fsm_printf("[rrc] [conn_reconfig] ApplyDrbToRelease!\n");	//test
		ApplyDrbToRelease(rrcd.drbToReleaseList); 
		//fsm_printf("		ApplySrbToRelease!\n");//test	
		//ApplySrbToRelease();//test	
	} 	
	if(rrcd.haveMAC_MainConfig) { 		
    62e6:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 ** Modified Date: 
 ******************************************************************************/
static void ApplyMacMainConfig(struct MAC_MainConfig mac)
{
	FIN(ApplyMacMainConfig());
	fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_CONFIG_MAC_MAIN,(void*)&mac,sizeof(mac));
    62e8:	b8 02 00 00 00       	mov    $0x2,%eax
    62ed:	8d 8d 60 ff ff ff    	lea    -0xa0(%ebp),%ecx
    62f3:	c7 04 24 50 00 00 00 	movl   $0x50,(%esp)
    62fa:	e8 fc ff ff ff       	call   62fb <ApplyRadioResourceConfigDedicated+0xdb>
    62ff:	eb 81                	jmp    6282 <ApplyRadioResourceConfigDedicated+0x62>
    6301:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
	if(rrcd.haveDrbToAddModList) { 		
		fsm_printf("[rrc] [conn_reconfig] ApplyDrbToAdd!\n");//test	
		ApplyDrbToAdd(rrcd.drbToAddModList); 	
	} 	
	if(rrcd.haveDrbToReleaseList) { 		
		fsm_printf("[rrc] [conn_reconfig] ApplyDrbToRelease!\n");	//test
    6308:	c7 04 24 74 17 00 00 	movl   $0x1774,(%esp)
    630f:	e8 fc ff ff ff       	call   6310 <ApplyRadioResourceConfigDedicated+0xf0>
		ApplyDrbToRelease(rrcd.drbToReleaseList); 
    6314:	8b 85 4c 03 00 00    	mov    0x34c(%ebp),%eax
    631a:	89 04 24             	mov    %eax,(%esp)
    631d:	8b 85 50 03 00 00    	mov    0x350(%ebp),%eax
    6323:	89 44 24 04          	mov    %eax,0x4(%esp)
    6327:	8b 85 54 03 00 00    	mov    0x354(%ebp),%eax
    632d:	89 44 24 08          	mov    %eax,0x8(%esp)
    6331:	8b 85 58 03 00 00    	mov    0x358(%ebp),%eax
    6337:	89 44 24 0c          	mov    %eax,0xc(%esp)
    633b:	8b 85 5c 03 00 00    	mov    0x35c(%ebp),%eax
    6341:	89 44 24 10          	mov    %eax,0x10(%esp)
    6345:	8b 85 60 03 00 00    	mov    0x360(%ebp),%eax
    634b:	89 44 24 14          	mov    %eax,0x14(%esp)
    634f:	8b 85 64 03 00 00    	mov    0x364(%ebp),%eax
    6355:	89 44 24 18          	mov    %eax,0x18(%esp)
    6359:	8b 85 68 03 00 00    	mov    0x368(%ebp),%eax
    635f:	89 44 24 1c          	mov    %eax,0x1c(%esp)
    6363:	8b 85 6c 03 00 00    	mov    0x36c(%ebp),%eax
    6369:	89 44 24 20          	mov    %eax,0x20(%esp)
    636d:	8b 85 70 03 00 00    	mov    0x370(%ebp),%eax
    6373:	89 44 24 24          	mov    %eax,0x24(%esp)
    6377:	8b 85 74 03 00 00    	mov    0x374(%ebp),%eax
    637d:	89 44 24 28          	mov    %eax,0x28(%esp)
    6381:	8b 85 78 03 00 00    	mov    0x378(%ebp),%eax
    6387:	89 44 24 2c          	mov    %eax,0x2c(%esp)
    638b:	e8 fc ff ff ff       	call   638c <ApplyRadioResourceConfigDedicated+0x16c>
    6390:	e9 e4 fe ff ff       	jmp    6279 <ApplyRadioResourceConfigDedicated+0x59>
    6395:	8d 76 00             	lea    0x0(%esi),%esi
	if(rrcd.haveSrbToAddModList) { 	
		fsm_printf("[rrc] [conn_reconfig] ApplySrbToAdd!\n");//test	 		
		ApplySrbToAdd(rrcd.srbToAddModList); 	
	} 	
	if(rrcd.haveDrbToAddModList) { 		
		fsm_printf("[rrc] [conn_reconfig] ApplyDrbToAdd!\n");//test	
    6398:	88 95 58 ff ff ff    	mov    %dl,-0xa8(%ebp)
		ApplyDrbToAdd(rrcd.drbToAddModList); 	
    639e:	8d b5 84 00 00 00    	lea    0x84(%ebp),%esi
	if(rrcd.haveSrbToAddModList) { 	
		fsm_printf("[rrc] [conn_reconfig] ApplySrbToAdd!\n");//test	 		
		ApplySrbToAdd(rrcd.srbToAddModList); 	
	} 	
	if(rrcd.haveDrbToAddModList) { 		
		fsm_printf("[rrc] [conn_reconfig] ApplyDrbToAdd!\n");//test	
    63a4:	c7 04 24 4c 17 00 00 	movl   $0x174c,(%esp)
    63ab:	e8 fc ff ff ff       	call   63ac <ApplyRadioResourceConfigDedicated+0x18c>
		ApplyDrbToAdd(rrcd.drbToAddModList); 	
    63b0:	b9 b1 00 00 00       	mov    $0xb1,%ecx
    63b5:	89 e7                	mov    %esp,%edi
    63b7:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    63b9:	e8 fc ff ff ff       	call   63ba <ApplyRadioResourceConfigDedicated+0x19a>
    63be:	0f b6 95 58 ff ff ff 	movzbl -0xa8(%ebp),%edx
    63c5:	e9 a7 fe ff ff       	jmp    6271 <ApplyRadioResourceConfigDedicated+0x51>
    63ca:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 ******************************************************************************/
static void ApplyRadioResourceConfigDedicated (struct RadioResourceConfigDedicated rrcd) 
{ 	
	FIN(ApplyRadioResourceConfigDedicated()); 	
	if(rrcd.haveSrbToAddModList) { 	
		fsm_printf("[rrc] [conn_reconfig] ApplySrbToAdd!\n");//test	 		
    63d0:	88 95 58 ff ff ff    	mov    %dl,-0xa8(%ebp)
		ApplySrbToAdd(rrcd.srbToAddModList); 	
    63d6:	8d 75 0c             	lea    0xc(%ebp),%esi
 ******************************************************************************/
static void ApplyRadioResourceConfigDedicated (struct RadioResourceConfigDedicated rrcd) 
{ 	
	FIN(ApplyRadioResourceConfigDedicated()); 	
	if(rrcd.haveSrbToAddModList) { 	
		fsm_printf("[rrc] [conn_reconfig] ApplySrbToAdd!\n");//test	 		
    63d9:	c7 04 24 24 17 00 00 	movl   $0x1724,(%esp)
    63e0:	e8 fc ff ff ff       	call   63e1 <ApplyRadioResourceConfigDedicated+0x1c1>
		ApplySrbToAdd(rrcd.srbToAddModList); 	
    63e5:	b9 1d 00 00 00       	mov    $0x1d,%ecx
    63ea:	89 e7                	mov    %esp,%edi
    63ec:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    63ee:	e8 fc ff ff ff       	call   63ef <ApplyRadioResourceConfigDedicated+0x1cf>
    63f3:	0f b6 95 58 ff ff ff 	movzbl -0xa8(%ebp),%edx
    63fa:	e9 6a fe ff ff       	jmp    6269 <ApplyRadioResourceConfigDedicated+0x49>
    63ff:	90                   	nop

00006400 <DoRecvRrcConnectionReconfiguration>:
 **-------------------------------------- --------------------
 ** Modified by:
 ** Modified Date: 
 ******************************************************************************/
void DoRecvRrcConnectionReconfiguration (struct RRCConnectionReconfiguration *msg)
{
    6400:	55                   	push   %ebp
    6401:	89 e5                	mov    %esp,%ebp
    6403:	81 ec f4 04 00 00    	sub    $0x4f4,%esp
    6409:	89 75 f8             	mov    %esi,-0x8(%ebp)
    640c:	89 7d fc             	mov    %edi,-0x4(%ebp)
    640f:	e8 fc ff ff ff       	call   6410 <DoRecvRrcConnectionReconfiguration+0x10>
	FIN(DoRecvRrcConnectionReconfiguration()); 		
	if (msg->haveRadioResourceConfigDedicated){ 			
    6414:	80 78 01 00          	cmpb   $0x0,0x1(%eax)
    6418:	74 11                	je     642b <DoRecvRrcConnectionReconfiguration+0x2b>
		ApplyRadioResourceConfigDedicated (msg->radioResourceConfigDedicated); 		
    641a:	8d 70 04             	lea    0x4(%eax),%esi
    641d:	b9 3b 01 00 00       	mov    $0x13b,%ecx
    6422:	89 e7                	mov    %esp,%edi
    6424:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    6426:	e8 f5 fd ff ff       	call   6220 <ApplyRadioResourceConfigDedicated>
	} 		 	

	FOUT; 
} 
    642b:	8b 75 f8             	mov    -0x8(%ebp),%esi
    642e:	8b 7d fc             	mov    -0x4(%ebp),%edi
    6431:	89 ec                	mov    %ebp,%esp
    6433:	5d                   	pop    %ebp
    6434:	c3                   	ret    
    6435:	90                   	nop
    6436:	90                   	nop
    6437:	90                   	nop
    6438:	90                   	nop
    6439:	90                   	nop
    643a:	90                   	nop
    643b:	90                   	nop
    643c:	90                   	nop
    643d:	90                   	nop
    643e:	90                   	nop
    643f:	90                   	nop

00006440 <gen_release>:
**Descriptions:modified format
**--------------------------------------------------------------------------------------------------

*************************************************************************************************************************************************/
struct RRCConnectionRelease *  gen_release()
{
    6440:	55                   	push   %ebp
    6441:	89 e5                	mov    %esp,%ebp
    6443:	e8 fc ff ff ff       	call   6444 <gen_release+0x4>
	struct RRCConnectionRelease * rrcConnectionRelease ;
	rrcConnectionRelease=(struct RRCConnectionRelease *)fsm_mem_alloc(sizeof(struct RRCConnectionRelease ));
    6448:	b8 40 00 00 00       	mov    $0x40,%eax
    644d:	e8 fc ff ff ff       	call   644e <gen_release+0xe>
	rrcConnectionRelease->rrcTransactionIdentifier=1;
    6452:	c6 00 01             	movb   $0x1,(%eax)
	rrcConnectionRelease->haveIdleModeMobilityControlInfo=true;
    6455:	c6 40 08 01          	movb   $0x1,0x8(%eax)
	rrcConnectionRelease->releaseCause=other;
    6459:	c7 40 04 01 00 00 00 	movl   $0x1,0x4(%eax)
	rrcConnectionRelease->idleModeMobilityControlInfo.have_t320=true;
    6460:	c6 40 38 01          	movb   $0x1,0x38(%eax)
	rrcConnectionRelease->idleModeMobilityControlInfo.t320_Value=min5;
    6464:	c7 40 3c 05 00 00 00 	movl   $0x5,0x3c(%eax)
	rrcConnectionRelease->idleModeMobilityControlInfo.haveCellReselectionPriorityInfo=false;
    646b:	c6 40 0c 00          	movb   $0x0,0xc(%eax)
	return rrcConnectionRelease;
}
    646f:	5d                   	pop    %ebp
    6470:	c3                   	ret    
    6471:	eb 0d                	jmp    6480 <t320_timeout>
    6473:	90                   	nop
    6474:	90                   	nop
    6475:	90                   	nop
    6476:	90                   	nop
    6477:	90                   	nop
    6478:	90                   	nop
    6479:	90                   	nop
    647a:	90                   	nop
    647b:	90                   	nop
    647c:	90                   	nop
    647d:	90                   	nop
    647e:	90                   	nop
    647f:	90                   	nop

00006480 <t320_timeout>:
**Descriptions:modified format
**--------------------------------------------------------------------------------------------------

*************************************************************************************************************************************************/
extern void t320_timeout(struct CellReselectionPriority *ueCellReselectionPriorityList)
{
    6480:	55                   	push   %ebp
    6481:	89 e5                	mov    %esp,%ebp
    6483:	53                   	push   %ebx
    6484:	83 ec 04             	sub    $0x4,%esp
    6487:	e8 fc ff ff ff       	call   6488 <t320_timeout+0x8>
    648c:	89 c3                	mov    %eax,%ebx
	FIN(t320_timeout());
	fsm_printf("[rrc] [conn_release] t320_timeout().\n");
    648e:	c7 04 24 ec 17 00 00 	movl   $0x17ec,(%esp)
    6495:	e8 fc ff ff ff       	call   6496 <t320_timeout+0x16>
    
	if(ueCellReselectionPriorityList!=NULL)
    649a:	85 db                	test   %ebx,%ebx
    649c:	74 07                	je     64a5 <t320_timeout+0x25>
	{
		fsm_mem_free(ueCellReselectionPriorityList);
    649e:	89 d8                	mov    %ebx,%eax
    64a0:	e8 fc ff ff ff       	call   64a1 <t320_timeout+0x21>
		ueCellReselectionPriorityList=NULL;
	}
    FOUT;
}
    64a5:	83 c4 04             	add    $0x4,%esp
    64a8:	5b                   	pop    %ebx
    64a9:	5d                   	pop    %ebp
    64aa:	c3                   	ret    
    64ab:	90                   	nop
    64ac:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

000064b0 <cell_reselection_priority_info>:
**Modified by:zhou yang
**Modified Date:2014/09/30
**Descriptions:modified format
**************************************************************************************************************************************************/
void cell_reselection_priority_info(struct RRCConnectionRelease *rrcConnectionRelease)
{
    64b0:	55                   	push   %ebp
    64b1:	89 e5                	mov    %esp,%ebp
    64b3:	83 ec 10             	sub    $0x10,%esp
    64b6:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    64b9:	89 75 f8             	mov    %esi,-0x8(%ebp)
    64bc:	89 7d fc             	mov    %edi,-0x4(%ebp)
    64bf:	e8 fc ff ff ff       	call   64c0 <cell_reselection_priority_info+0x10>
    64c4:	89 c3                	mov    %eax,%ebx
	FIN(cell_reselection_priority_info());
	fsm_printf("[rrc] [conn_release] cell_reselection_priority_info().\n");
    64c6:	c7 04 24 14 18 00 00 	movl   $0x1814,(%esp)
    64cd:	e8 fc ff ff ff       	call   64ce <cell_reselection_priority_info+0x1e>
	
	if(rrcConnectionRelease->haveIdleModeMobilityControlInfo)
    64d2:	80 7b 08 00          	cmpb   $0x0,0x8(%ebx)
    64d6:	74 1e                	je     64f6 <cell_reselection_priority_info+0x46>
	{
		
		//release old ueCellReselectionPriorityList 
		if(ueCellReselectionPriorityList!=NULL)
    64d8:	a1 00 00 00 00       	mov    0x0,%eax
    64dd:	85 c0                	test   %eax,%eax
    64df:	74 0f                	je     64f0 <cell_reselection_priority_info+0x40>
		{
			fsm_mem_free(ueCellReselectionPriorityList);
    64e1:	e8 fc ff ff ff       	call   64e2 <cell_reselection_priority_info+0x32>
			ueCellReselectionPriorityList=NULL;
    64e6:	c7 05 00 00 00 00 00 	movl   $0x0,0x0
    64ed:	00 00 00 
		}
		if(rrcConnectionRelease->idleModeMobilityControlInfo.haveCellReselectionPriorityInfo)
    64f0:	80 7b 0c 00          	cmpb   $0x0,0xc(%ebx)
    64f4:	75 12                	jne    6508 <cell_reselection_priority_info+0x58>
			}
		}
    }

    FOUT;
}
    64f6:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    64f9:	8b 75 f8             	mov    -0x8(%ebp),%esi
    64fc:	8b 7d fc             	mov    -0x4(%ebp),%edi
    64ff:	89 ec                	mov    %ebp,%esp
    6501:	5d                   	pop    %ebp
    6502:	c3                   	ret    
    6503:	90                   	nop
    6504:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
			ueCellReselectionPriorityList=NULL;
		}
		if(rrcConnectionRelease->idleModeMobilityControlInfo.haveCellReselectionPriorityInfo)
		{
			//if t320 overtime ;then free ueCellReselectionPriorityList
			ueCellReselectionPriorityList = (struct  CellReselectionPriority  *)fsm_mem_alloc(sizeof(struct CellReselectionPriority )*MAX_CELL_RESELECTION_SIZE);
    6508:	b8 28 00 00 00       	mov    $0x28,%eax
    650d:	e8 fc ff ff ff       	call   650e <cell_reselection_priority_info+0x5e>
			if(ueCellReselectionPriorityList==NULL)
			{
				fsm_printf("[rrc] [conn_release] cell_reselection_priority_info() apply memory failure \n");
				return ;
    6512:	31 d2                	xor    %edx,%edx
		}
		if(rrcConnectionRelease->idleModeMobilityControlInfo.haveCellReselectionPriorityInfo)
		{
			//if t320 overtime ;then free ueCellReselectionPriorityList
			ueCellReselectionPriorityList = (struct  CellReselectionPriority  *)fsm_mem_alloc(sizeof(struct CellReselectionPriority )*MAX_CELL_RESELECTION_SIZE);
			if(ueCellReselectionPriorityList==NULL)
    6514:	85 c0                	test   %eax,%eax
			ueCellReselectionPriorityList=NULL;
		}
		if(rrcConnectionRelease->idleModeMobilityControlInfo.haveCellReselectionPriorityInfo)
		{
			//if t320 overtime ;then free ueCellReselectionPriorityList
			ueCellReselectionPriorityList = (struct  CellReselectionPriority  *)fsm_mem_alloc(sizeof(struct CellReselectionPriority )*MAX_CELL_RESELECTION_SIZE);
    6516:	a3 00 00 00 00       	mov    %eax,0x0
			if(ueCellReselectionPriorityList==NULL)
    651b:	74 1e                	je     653b <cell_reselection_priority_info+0x8b>
				return ;
			}
			int i=0;
			for(i=0; i<MAX_CELL_RESELECTION_SIZE; i++)
			{
				ueCellReselectionPriorityList[i]=rrcConnectionRelease->idleModeMobilityControlInfo.cellReselectionPriorityList[i];
    651d:	8b 74 13 10          	mov    0x10(%ebx,%edx,1),%esi
    6521:	8b 7c 13 14          	mov    0x14(%ebx,%edx,1),%edi
    6525:	89 34 10             	mov    %esi,(%eax,%edx,1)
    6528:	89 7c 10 04          	mov    %edi,0x4(%eax,%edx,1)
    652c:	83 c2 08             	add    $0x8,%edx
			{
				fsm_printf("[rrc] [conn_release] cell_reselection_priority_info() apply memory failure \n");
				return ;
			}
			int i=0;
			for(i=0; i<MAX_CELL_RESELECTION_SIZE; i++)
    652f:	83 fa 28             	cmp    $0x28,%edx
    6532:	74 c2                	je     64f6 <cell_reselection_priority_info+0x46>
    6534:	a1 00 00 00 00       	mov    0x0,%eax
    6539:	eb e2                	jmp    651d <cell_reselection_priority_info+0x6d>
		{
			//if t320 overtime ;then free ueCellReselectionPriorityList
			ueCellReselectionPriorityList = (struct  CellReselectionPriority  *)fsm_mem_alloc(sizeof(struct CellReselectionPriority )*MAX_CELL_RESELECTION_SIZE);
			if(ueCellReselectionPriorityList==NULL)
			{
				fsm_printf("[rrc] [conn_release] cell_reselection_priority_info() apply memory failure \n");
    653b:	c7 04 24 4c 18 00 00 	movl   $0x184c,(%esp)
    6542:	e8 fc ff ff ff       	call   6543 <cell_reselection_priority_info+0x93>
				return ;
    6547:	eb ad                	jmp    64f6 <cell_reselection_priority_info+0x46>
    6549:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00006550 <release_radio_resource>:
**Descriptions:modified format
**--------------------------------------------------------------------------------------------------

*************************************************************************************************************************************************/
void release_radio_resource(void)
{
    6550:	55                   	push   %ebp
    6551:	89 e5                	mov    %esp,%ebp
    6553:	83 ec 60             	sub    $0x60,%esp
    6556:	e8 fc ff ff ff       	call   6557 <release_radio_resource+0x7>
	FIN(release_radio_resource());
	int i;
	int numIndex=0;
	struct DrbToReleaseList drb;
	
	fsm_printf("[rrc] [conn_release] release_radio_resource().\n");
    655b:	c7 04 24 9c 18 00 00 	movl   $0x189c,(%esp)
    6562:	e8 fc ff ff ff       	call   6563 <release_radio_resource+0x13>
    6567:	31 c9                	xor    %ecx,%ecx
    6569:	31 c0                	xor    %eax,%eax
    656b:	90                   	nop
    656c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
	for(i=0; i<maxDRB; i++)
	{
		if(ueDrbConfig[i]!=NULL)
    6570:	8b 14 85 00 00 00 00 	mov    0x0(,%eax,4),%edx
    6577:	85 d2                	test   %edx,%edx
    6579:	74 0b                	je     6586 <release_radio_resource+0x36>
		{          	
			drb.drbToRelease[numIndex]=ueDrbConfig[i]->drbIdentity;
    657b:	0f b6 52 01          	movzbl 0x1(%edx),%edx
    657f:	89 54 8d d4          	mov    %edx,-0x2c(%ebp,%ecx,4)
			numIndex++;
    6583:	83 c1 01             	add    $0x1,%ecx
	int i;
	int numIndex=0;
	struct DrbToReleaseList drb;
	
	fsm_printf("[rrc] [conn_release] release_radio_resource().\n");
	for(i=0; i<maxDRB; i++)
    6586:	83 c0 01             	add    $0x1,%eax
    6589:	83 f8 0b             	cmp    $0xb,%eax
    658c:	75 e2                	jne    6570 <release_radio_resource+0x20>
		{          	
			drb.drbToRelease[numIndex]=ueDrbConfig[i]->drbIdentity;
			numIndex++;
		}       
	}
	drb.num=numIndex;
    658e:	89 4d d0             	mov    %ecx,-0x30(%ebp)
	ApplySrbToRelease();//release SRB
    6591:	e8 fc ff ff ff       	call   6592 <release_radio_resource+0x42>
	ApplyDrbToRelease(drb) ;//release DRB
    6596:	8b 45 d0             	mov    -0x30(%ebp),%eax
    6599:	89 04 24             	mov    %eax,(%esp)
    659c:	8b 45 d4             	mov    -0x2c(%ebp),%eax
    659f:	89 44 24 04          	mov    %eax,0x4(%esp)
    65a3:	8b 45 d8             	mov    -0x28(%ebp),%eax
    65a6:	89 44 24 08          	mov    %eax,0x8(%esp)
    65aa:	8b 45 dc             	mov    -0x24(%ebp),%eax
    65ad:	89 44 24 0c          	mov    %eax,0xc(%esp)
    65b1:	8b 45 e0             	mov    -0x20(%ebp),%eax
    65b4:	89 44 24 10          	mov    %eax,0x10(%esp)
    65b8:	8b 45 e4             	mov    -0x1c(%ebp),%eax
    65bb:	89 44 24 14          	mov    %eax,0x14(%esp)
    65bf:	8b 45 e8             	mov    -0x18(%ebp),%eax
    65c2:	89 44 24 18          	mov    %eax,0x18(%esp)
    65c6:	8b 45 ec             	mov    -0x14(%ebp),%eax
    65c9:	89 44 24 1c          	mov    %eax,0x1c(%esp)
    65cd:	8b 45 f0             	mov    -0x10(%ebp),%eax
    65d0:	89 44 24 20          	mov    %eax,0x20(%esp)
    65d4:	8b 45 f4             	mov    -0xc(%ebp),%eax
    65d7:	89 44 24 24          	mov    %eax,0x24(%esp)
    65db:	8b 45 f8             	mov    -0x8(%ebp),%eax
    65de:	89 44 24 28          	mov    %eax,0x28(%esp)
    65e2:	8b 45 fc             	mov    -0x4(%ebp),%eax
    65e5:	89 44 24 2c          	mov    %eax,0x2c(%esp)
    65e9:	e8 fc ff ff ff       	call   65ea <release_radio_resource+0x9a>
	FOUT;
}
    65ee:	c9                   	leave  
    65ef:	c3                   	ret    

000065f0 <stop_timer>:
**Descriptions:modified format
**--------------------------------------------------------------------------------------------------

*************************************************************************************************************************************************/
void stop_timer(void)
{
    65f0:	55                   	push   %ebp
    65f1:	89 e5                	mov    %esp,%ebp
    65f3:	83 ec 04             	sub    $0x4,%esp
    65f6:	e8 fc ff ff ff       	call   65f7 <stop_timer+0x7>
	FIN(stop_timer());
	fsm_printf("[rrc] [conn_release] stop_timer().\n");
    65fb:	c7 04 24 cc 18 00 00 	movl   $0x18cc,(%esp)
    6602:	e8 fc ff ff ff       	call   6603 <stop_timer+0x13>
	cancleTimer(0);
    6607:	31 c0                	xor    %eax,%eax
    6609:	e8 fc ff ff ff       	call   660a <stop_timer+0x1a>
	cancleTimer(1);
    660e:	b8 01 00 00 00       	mov    $0x1,%eax
    6613:	e8 fc ff ff ff       	call   6614 <stop_timer+0x24>
	cancleTimer(2);
    6618:	b8 02 00 00 00       	mov    $0x2,%eax
    661d:	e8 fc ff ff ff       	call   661e <stop_timer+0x2e>
	cancleTimer(5);
    6622:	b8 05 00 00 00       	mov    $0x5,%eax
    6627:	e8 fc ff ff ff       	call   6628 <stop_timer+0x38>
	cancleTimer(11);
    662c:	b8 0b 00 00 00       	mov    $0xb,%eax
    6631:	e8 fc ff ff ff       	call   6632 <stop_timer+0x42>
	cancleTimer(21);
    6636:	b8 15 00 00 00       	mov    $0x15,%eax
    663b:	e8 fc ff ff ff       	call   663c <stop_timer+0x4c>
	FOUT;
}
    6640:	c9                   	leave  
    6641:	c3                   	ret    
    6642:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    6649:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00006650 <set_t320>:
**Modified by: zhou yang
**Modified Date: 2014/09/30
**Descriptions:modified format
*************************************************************************************************************************************************/
void set_t320(struct RRCConnectionRelease * rrcConnectionRelease)
{
    6650:	55                   	push   %ebp
    6651:	89 e5                	mov    %esp,%ebp
    6653:	53                   	push   %ebx
    6654:	83 ec 04             	sub    $0x4,%esp
    6657:	e8 fc ff ff ff       	call   6658 <set_t320+0x8>
    665c:	89 c3                	mov    %eax,%ebx
	FIN(set_t320());
	fsm_printf("[rrc] [conn_release] set_t320().\n");
    665e:	c7 04 24 f0 18 00 00 	movl   $0x18f0,(%esp)
    6665:	e8 fc ff ff ff       	call   6666 <set_t320+0x16>
	if(rrcConnectionRelease->idleModeMobilityControlInfo.have_t320)
    666a:	80 7b 38 00          	cmpb   $0x0,0x38(%ebx)
    666e:	74 11                	je     6681 <set_t320+0x31>
	{
		unsigned int delay;
		delay=rrcConnectionRelease->idleModeMobilityControlInfo.t320_Value;
		setTimer(20,delay*60*1000*1000*100);
    6670:	69 53 3c 00 bc a0 65 	imul   $0x65a0bc00,0x3c(%ebx),%edx
    6677:	b8 14 00 00 00       	mov    $0x14,%eax
    667c:	e8 fc ff ff ff       	call   667d <set_t320+0x2d>
	}
	FOUT;
}
    6681:	83 c4 04             	add    $0x4,%esp
    6684:	5b                   	pop    %ebx
    6685:	5d                   	pop    %ebp
    6686:	c3                   	ret    
    6687:	90                   	nop
    6688:	90                   	nop
    6689:	90                   	nop
    668a:	90                   	nop
    668b:	90                   	nop
    668c:	90                   	nop
    668d:	90                   	nop
    668e:	90                   	nop
    668f:	90                   	nop

00006690 <ApplyPhich_Config>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void ApplyPhich_Config(struct PHICH_Config phich_c)
{
    6690:	55                   	push   %ebp
    6691:	89 e5                	mov    %esp,%ebp
    6693:	e8 fc ff ff ff       	call   6694 <ApplyPhich_Config+0x4>

	//Sent to the PHY(NULL)
	
}
    6698:	5d                   	pop    %ebp
    6699:	c3                   	ret    
    669a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

000066a0 <ApplyBCCH_Config>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void ApplyBCCH_Config(struct BCCH_Config bc)
{
    66a0:	55                   	push   %ebp
    66a1:	89 e5                	mov    %esp,%ebp
    66a3:	e8 fc ff ff ff       	call   66a4 <ApplyBCCH_Config+0x4>
	FIN(ApplyBCCH_Config());
	//fsm_do_ioctrl(STRM_TO_MAC, IOCCMD_RRCTOMAC_CONFIG_BCCH, (void*)&bc, sizeof(struct BCCH_Config));
	FOUT;
}
    66a8:	5d                   	pop    %ebp
    66a9:	c3                   	ret    
    66aa:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

000066b0 <ApplyPCCH_Config>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void ApplyPCCH_Config(struct PCCH_Config pc)
{
    66b0:	55                   	push   %ebp
    66b1:	89 e5                	mov    %esp,%ebp
    66b3:	e8 fc ff ff ff       	call   66b4 <ApplyPCCH_Config+0x4>
	FIN(ApplyPCCH_Config());
	//fsm_do_ioctrl(STRM_TO_MAC, IOCCMD_RRCTOMAC_CONFIG_PCCH, (void*)&pc, sizeof(struct PCCH_Config));
	FOUT;
}
    66b8:	5d                   	pop    %ebp
    66b9:	c3                   	ret    
    66ba:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

000066c0 <ApplyPRACH_ConfigSIB>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void ApplyPRACH_ConfigSIB(struct PRACH_ConfigSIB prach_c)
{
    66c0:	55                   	push   %ebp
    66c1:	89 e5                	mov    %esp,%ebp
    66c3:	e8 fc ff ff ff       	call   66c4 <ApplyPRACH_ConfigSIB+0x4>
	//fix me:Sent to the PHY(waited)

}
    66c8:	5d                   	pop    %ebp
    66c9:	c3                   	ret    
    66ca:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

000066d0 <ApplyPDSCH_ConfigCommon>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void ApplyPDSCH_ConfigCommon(struct PDSCH_ConfigCommon pdsch_c)
{
    66d0:	55                   	push   %ebp
    66d1:	89 e5                	mov    %esp,%ebp
    66d3:	e8 fc ff ff ff       	call   66d4 <ApplyPDSCH_ConfigCommon+0x4>
	////fix me:Sent to the PHY(waited)

}
    66d8:	5d                   	pop    %ebp
    66d9:	c3                   	ret    
    66da:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

000066e0 <ApplyPUSCH_ConfigCommon>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void ApplyPUSCH_ConfigCommon(struct PUSCH_ConfigCommon pusch_c)
{
    66e0:	55                   	push   %ebp
    66e1:	89 e5                	mov    %esp,%ebp
    66e3:	e8 fc ff ff ff       	call   66e4 <ApplyPUSCH_ConfigCommon+0x4>
	////fix me:Sent to the PHY(waited)

}
    66e8:	5d                   	pop    %ebp
    66e9:	c3                   	ret    
    66ea:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

000066f0 <ApplySoundingRS_UL_ConfigCommon>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void ApplySoundingRS_UL_ConfigCommon(struct SoundingRS_UL_ConfigCommon sc)
{
    66f0:	55                   	push   %ebp
    66f1:	89 e5                	mov    %esp,%ebp
    66f3:	e8 fc ff ff ff       	call   66f4 <ApplySoundingRS_UL_ConfigCommon+0x4>
	////fix me:Sent to the PHY(waited)

}
    66f8:	5d                   	pop    %ebp
    66f9:	c3                   	ret    
    66fa:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00006700 <ApplyUplinkPowerControlCommon>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void ApplyUplinkPowerControlCommon(struct UplinkPowerControlCommon uc)
{
    6700:	55                   	push   %ebp
    6701:	89 e5                	mov    %esp,%ebp
    6703:	e8 fc ff ff ff       	call   6704 <ApplyUplinkPowerControlCommon+0x4>
	////fix me:Sent to the PHY(waited)

}
    6708:	5d                   	pop    %ebp
    6709:	c3                   	ret    
    670a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00006710 <ApplyUL_CyclicPrefixLength>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void ApplyUL_CyclicPrefixLength(struct UL_CyclicPrefixLength ul_c)
{
    6710:	55                   	push   %ebp
    6711:	89 e5                	mov    %esp,%ebp
    6713:	e8 fc ff ff ff       	call   6714 <ApplyUL_CyclicPrefixLength+0x4>
	////fix me:Sent to the PHY(waited)

}
    6718:	5d                   	pop    %ebp
    6719:	c3                   	ret    
    671a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00006720 <gen_sib1>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
FSM_PKT* gen_sib1()
{
    6720:	55                   	push   %ebp
    6721:	89 e5                	mov    %esp,%ebp
    6723:	81 ec e8 02 00 00    	sub    $0x2e8,%esp
    6729:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    672c:	89 75 f8             	mov    %esi,-0x8(%ebp)
    672f:	89 7d fc             	mov    %edi,-0x4(%ebp)
    6732:	e8 fc ff ff ff       	call   6733 <gen_sib1+0x13>
	struct SystemInformationBlockType1 sib1;
	sib1.cellAccessRelatedInfo.cellIdentity=(u32)15;
	sib1.cellAccessRelatedInfo.trackingAreaCode=(u16)12;
	struct BCCH_DL_SCH_Message bcch_dl_sch_message;
	bcch_dl_sch_message.type=2;
	bcch_dl_sch_message.msg.sib1=sib1;
    6737:	b9 5b 00 00 00       	mov    $0x5b,%ecx
	
	
	//Generate packets
	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr= fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));  
    673c:	b8 74 01 00 00       	mov    $0x174,%eax
	struct SystemInformationBlockType1 sib1;
	sib1.cellAccessRelatedInfo.cellIdentity=(u32)15;
	sib1.cellAccessRelatedInfo.trackingAreaCode=(u16)12;
	struct BCCH_DL_SCH_Message bcch_dl_sch_message;
	bcch_dl_sch_message.type=2;
	bcch_dl_sch_message.msg.sib1=sib1;
    6741:	c7 85 34 ff ff ff 0f 	movl   $0xf,-0xcc(%ebp)
    6748:	00 00 00 
    674b:	8d bd 1c fd ff ff    	lea    -0x2e4(%ebp),%edi
    6751:	66 c7 85 30 ff ff ff 	movw   $0xc,-0xd0(%ebp)
    6758:	0c 00 
    675a:	8d b5 88 fe ff ff    	lea    -0x178(%ebp),%esi
    6760:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
{
	struct SystemInformationBlockType1 sib1;
	sib1.cellAccessRelatedInfo.cellIdentity=(u32)15;
	sib1.cellAccessRelatedInfo.trackingAreaCode=(u16)12;
	struct BCCH_DL_SCH_Message bcch_dl_sch_message;
	bcch_dl_sch_message.type=2;
    6762:	c7 85 18 fd ff ff 02 	movl   $0x2,-0x2e8(%ebp)
    6769:	00 00 00 
	
	
	//Generate packets
	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr= fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));  
    676c:	e8 fc ff ff ff       	call   676d <gen_sib1+0x4d>
	fsm_skb_put(pkptr, msg_len);
    6771:	ba 70 01 00 00       	mov    $0x170,%edx
	
	
	//Generate packets
	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr= fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));  
    6776:	89 c3                	mov    %eax,%ebx
	fsm_skb_put(pkptr, msg_len);
    6778:	e8 fc ff ff ff       	call   6779 <gen_sib1+0x59>
	fsm_mem_cpy(pkptr->data, msg, msg_len);
    677d:	8b 83 ac 00 00 00    	mov    0xac(%ebx),%eax
    6783:	8d 95 18 fd ff ff    	lea    -0x2e8(%ebp),%edx
    6789:	b9 70 01 00 00       	mov    $0x170,%ecx
    678e:	e8 fc ff ff ff       	call   678f <gen_sib1+0x6f>
	
	//Filling head
	if(fsm_skb_headroom(pkptr) < sizeof(struct lte_rrc_head)){
    6793:	89 d8                	mov    %ebx,%eax
    6795:	e8 fc ff ff ff       	call   6796 <gen_sib1+0x76>
    679a:	83 f8 03             	cmp    $0x3,%eax
    679d:	77 12                	ja     67b1 <gen_sib1+0x91>
		pkptr= fsm_skb_realloc_headeroom(pkptr,sizeof(struct lte_rrc_head));
    679f:	89 d8                	mov    %ebx,%eax
    67a1:	ba 04 00 00 00       	mov    $0x4,%edx
    67a6:	e8 fc ff ff ff       	call   67a7 <gen_sib1+0x87>
		if(pkptr== NULL)
    67ab:	85 c0                	test   %eax,%eax
	fsm_skb_put(pkptr, msg_len);
	fsm_mem_cpy(pkptr->data, msg, msg_len);
	
	//Filling head
	if(fsm_skb_headroom(pkptr) < sizeof(struct lte_rrc_head)){
		pkptr= fsm_skb_realloc_headeroom(pkptr,sizeof(struct lte_rrc_head));
    67ad:	89 c3                	mov    %eax,%ebx
		if(pkptr== NULL)
    67af:	74 27                	je     67d8 <gen_sib1+0xb8>
			return;
	}
	fsm_skb_push(pkptr, sizeof(struct lte_rrc_head));
    67b1:	ba 04 00 00 00       	mov    $0x4,%edx
    67b6:	89 d8                	mov    %ebx,%eax
    67b8:	e8 fc ff ff ff       	call   67b9 <gen_sib1+0x99>
	sh_ptr= (struct lte_rrc_head*)pkptr->data;
	sh_ptr->message_type = 2;
    67bd:	8b 83 ac 00 00 00    	mov    0xac(%ebx),%eax
    67c3:	c7 00 02 00 00 00    	movl   $0x2,(%eax)
	return pkptr;
}
    67c9:	89 d8                	mov    %ebx,%eax
    67cb:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    67ce:	8b 75 f8             	mov    -0x8(%ebp),%esi
    67d1:	8b 7d fc             	mov    -0x4(%ebp),%edi
    67d4:	89 ec                	mov    %ebp,%esp
    67d6:	5d                   	pop    %ebp
    67d7:	c3                   	ret    
    67d8:	eb f1                	jmp    67cb <gen_sib1+0xab>
    67da:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

000067e0 <gen_mib>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
FSM_PKT* gen_mib()
{
    67e0:	55                   	push   %ebp
    67e1:	89 e5                	mov    %esp,%ebp
    67e3:	53                   	push   %ebx
    67e4:	83 ec 10             	sub    $0x10,%esp
    67e7:	e8 fc ff ff ff       	call   67e8 <gen_mib+0x8>
	int message_type = 1;

	//Generate packets
	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr = fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));  
    67ec:	b8 14 00 00 00       	mov    $0x14,%eax
	struct MasterInformationBlock mib;
	mib.dl_Bandwidth = n25;
	//mib.phich_Config
	mib.systemFrameNumber = (u8)120;
	struct BCCH_BCH_Message bcch_bch_msg;
	bcch_bch_msg.mib = mib;
    67f1:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
    67f8:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
    67ff:	c6 45 f8 78          	movb   $0x78,-0x8(%ebp)
    6803:	c7 45 ec 19 00 00 00 	movl   $0x19,-0x14(%ebp)
	int message_type = 1;

	//Generate packets
	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr = fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));  
    680a:	e8 fc ff ff ff       	call   680b <gen_mib+0x2b>
	fsm_skb_put(pkptr, msg_len);
    680f:	ba 10 00 00 00       	mov    $0x10,%edx
	int message_type = 1;

	//Generate packets
	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr = fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));  
    6814:	89 c3                	mov    %eax,%ebx
	fsm_skb_put(pkptr, msg_len);
    6816:	e8 fc ff ff ff       	call   6817 <gen_mib+0x37>
	fsm_mem_cpy(pkptr->data, msg, msg_len);
    681b:	8b 83 ac 00 00 00    	mov    0xac(%ebx),%eax
    6821:	8d 55 ec             	lea    -0x14(%ebp),%edx
    6824:	b9 10 00 00 00       	mov    $0x10,%ecx
    6829:	e8 fc ff ff ff       	call   682a <gen_mib+0x4a>

	//Filling head
	if(fsm_skb_headroom(pkptr) < sizeof(struct lte_rrc_head)){
    682e:	89 d8                	mov    %ebx,%eax
    6830:	e8 fc ff ff ff       	call   6831 <gen_mib+0x51>
    6835:	83 f8 03             	cmp    $0x3,%eax
    6838:	77 12                	ja     684c <gen_mib+0x6c>
		pkptr = fsm_skb_realloc_headeroom(pkptr,sizeof(struct lte_rrc_head));
    683a:	89 d8                	mov    %ebx,%eax
    683c:	ba 04 00 00 00       	mov    $0x4,%edx
    6841:	e8 fc ff ff ff       	call   6842 <gen_mib+0x62>
		if(pkptr == NULL)
    6846:	85 c0                	test   %eax,%eax
	fsm_skb_put(pkptr, msg_len);
	fsm_mem_cpy(pkptr->data, msg, msg_len);

	//Filling head
	if(fsm_skb_headroom(pkptr) < sizeof(struct lte_rrc_head)){
		pkptr = fsm_skb_realloc_headeroom(pkptr,sizeof(struct lte_rrc_head));
    6848:	89 c3                	mov    %eax,%ebx
		if(pkptr == NULL)
    684a:	74 24                	je     6870 <gen_mib+0x90>
			return;
	}
	fsm_skb_push(pkptr, sizeof(struct lte_rrc_head));
    684c:	89 d8                	mov    %ebx,%eax
    684e:	ba 04 00 00 00       	mov    $0x4,%edx
    6853:	e8 fc ff ff ff       	call   6854 <gen_mib+0x74>
	sh_ptr = (struct lte_rrc_head*)pkptr->data;
	sh_ptr->message_type = message_type;
    6858:	8b 83 ac 00 00 00    	mov    0xac(%ebx),%eax
    685e:	c7 00 01 00 00 00    	movl   $0x1,(%eax)
	return pkptr;
}
    6864:	89 d8                	mov    %ebx,%eax
    6866:	83 c4 10             	add    $0x10,%esp
    6869:	5b                   	pop    %ebx
    686a:	5d                   	pop    %ebp
    686b:	c3                   	ret    
    686c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    6870:	83 c4 10             	add    $0x10,%esp
    6873:	5b                   	pop    %ebx
    6874:	5d                   	pop    %ebp
    6875:	c3                   	ret    
    6876:	8d 76 00             	lea    0x0(%esi),%esi
    6879:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00006880 <gen_si>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
FSM_PKT* gen_si()
{
    6880:	55                   	push   %ebp
    6881:	89 e5                	mov    %esp,%ebp
    6883:	57                   	push   %edi
    6884:	56                   	push   %esi
    6885:	53                   	push   %ebx
    6886:	81 ec 7c 02 00 00    	sub    $0x27c,%esp
    688c:	e8 fc ff ff ff       	call   688d <gen_si+0xd>
	si.sib2.radioResourceConfigCommon.bcch_Config.modificationPeriodCoeff=modificationPeriodCoeff_n4;
	si.sib2.radioResourceConfigCommon.pcch_Config.defaultPagingCycle=rf64;
	si.sib2.radioResourceConfigCommon.pcch_Config.nB=twoT;
	struct BCCH_DL_SCH_Message bcch_dl_sch_message;
	bcch_dl_sch_message.type=1;
	bcch_dl_sch_message.msg.si=si;
    6891:	b9 43 00 00 00       	mov    $0x43,%ecx
	int message_type = 2;
	
	//Generate packets
	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr= fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));  
    6896:	b8 74 01 00 00       	mov    $0x174,%eax
	si.sib2.radioResourceConfigCommon.bcch_Config.modificationPeriodCoeff=modificationPeriodCoeff_n4;
	si.sib2.radioResourceConfigCommon.pcch_Config.defaultPagingCycle=rf64;
	si.sib2.radioResourceConfigCommon.pcch_Config.nB=twoT;
	struct BCCH_DL_SCH_Message bcch_dl_sch_message;
	bcch_dl_sch_message.type=1;
	bcch_dl_sch_message.msg.si=si;
    689b:	c6 85 e8 fe ff ff 01 	movb   $0x1,-0x118(%ebp)
    68a2:	8d bd 7c fd ff ff    	lea    -0x284(%ebp),%edi
    68a8:	c6 45 ec 01          	movb   $0x1,-0x14(%ebp)
    68ac:	8d b5 e8 fe ff ff    	lea    -0x118(%ebp),%esi
    68b2:	c7 85 0c ff ff ff 20 	movl   $0x20,-0xf4(%ebp)
    68b9:	00 00 00 
    68bc:	c6 85 10 ff ff ff 01 	movb   $0x1,-0xf0(%ebp)
    68c3:	c7 85 14 ff ff ff 08 	movl   $0x8,-0xec(%ebp)
    68ca:	00 00 00 
    68cd:	c7 85 18 ff ff ff 90 	movl   $0x90,-0xe8(%ebp)
    68d4:	00 00 00 
    68d7:	c7 85 1c ff ff ff 0c 	movl   $0xc,-0xe4(%ebp)
    68de:	00 00 00 
    68e1:	c7 85 20 ff ff ff 04 	movl   $0x4,-0xe0(%ebp)
    68e8:	00 00 00 
    68eb:	c7 85 24 ff ff ff 92 	movl   $0xffffff92,-0xdc(%ebp)
    68f2:	ff ff ff 
    68f5:	c7 85 28 ff ff ff 04 	movl   $0x4,-0xd8(%ebp)
    68fc:	00 00 00 
    68ff:	c7 85 34 ff ff ff 04 	movl   $0x4,-0xcc(%ebp)
    6906:	00 00 00 
    6909:	c7 85 38 ff ff ff 04 	movl   $0x4,-0xc8(%ebp)
    6910:	00 00 00 
    6913:	c7 85 3c ff ff ff 40 	movl   $0x40,-0xc4(%ebp)
    691a:	00 00 00 
    691d:	c7 85 40 ff ff ff 01 	movl   $0x1,-0xc0(%ebp)
    6924:	00 00 00 
    6927:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
	si.sib2.radioResourceConfigCommon.rachConfigCommon.maxHARQ_Msg3Tx=4;
	si.sib2.radioResourceConfigCommon.bcch_Config.modificationPeriodCoeff=modificationPeriodCoeff_n4;
	si.sib2.radioResourceConfigCommon.pcch_Config.defaultPagingCycle=rf64;
	si.sib2.radioResourceConfigCommon.pcch_Config.nB=twoT;
	struct BCCH_DL_SCH_Message bcch_dl_sch_message;
	bcch_dl_sch_message.type=1;
    6929:	c7 85 78 fd ff ff 01 	movl   $0x1,-0x288(%ebp)
    6930:	00 00 00 
	int message_type = 2;
	
	//Generate packets
	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr= fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));  
    6933:	e8 fc ff ff ff       	call   6934 <gen_si+0xb4>
	fsm_skb_put(pkptr, msg_len);
    6938:	ba 70 01 00 00       	mov    $0x170,%edx
	int message_type = 2;
	
	//Generate packets
	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr= fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));  
    693d:	89 c3                	mov    %eax,%ebx
	fsm_skb_put(pkptr, msg_len);
    693f:	e8 fc ff ff ff       	call   6940 <gen_si+0xc0>
	fsm_mem_cpy(pkptr->data, msg, msg_len);
    6944:	8b 83 ac 00 00 00    	mov    0xac(%ebx),%eax
    694a:	8d 95 78 fd ff ff    	lea    -0x288(%ebp),%edx
    6950:	b9 70 01 00 00       	mov    $0x170,%ecx
    6955:	e8 fc ff ff ff       	call   6956 <gen_si+0xd6>
	//Filling head
	if(fsm_skb_headroom(pkptr) < sizeof(struct lte_rrc_head)){
    695a:	89 d8                	mov    %ebx,%eax
    695c:	e8 fc ff ff ff       	call   695d <gen_si+0xdd>
    6961:	83 f8 03             	cmp    $0x3,%eax
    6964:	77 12                	ja     6978 <gen_si+0xf8>
		pkptr= fsm_skb_realloc_headeroom(pkptr,sizeof(struct lte_rrc_head));
    6966:	89 d8                	mov    %ebx,%eax
    6968:	ba 04 00 00 00       	mov    $0x4,%edx
    696d:	e8 fc ff ff ff       	call   696e <gen_si+0xee>
		if(pkptr== NULL)
    6972:	85 c0                	test   %eax,%eax
	pkptr= fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));  
	fsm_skb_put(pkptr, msg_len);
	fsm_mem_cpy(pkptr->data, msg, msg_len);
	//Filling head
	if(fsm_skb_headroom(pkptr) < sizeof(struct lte_rrc_head)){
		pkptr= fsm_skb_realloc_headeroom(pkptr,sizeof(struct lte_rrc_head));
    6974:	89 c3                	mov    %eax,%ebx
		if(pkptr== NULL)
    6976:	74 28                	je     69a0 <gen_si+0x120>
			return;
	}
	fsm_skb_push(pkptr, sizeof(struct lte_rrc_head));
    6978:	89 d8                	mov    %ebx,%eax
    697a:	ba 04 00 00 00       	mov    $0x4,%edx
    697f:	e8 fc ff ff ff       	call   6980 <gen_si+0x100>
	sh_ptr= (struct lte_rrc_head*)pkptr->data;
	sh_ptr->message_type = message_type;
    6984:	8b 83 ac 00 00 00    	mov    0xac(%ebx),%eax
    698a:	c7 00 02 00 00 00    	movl   $0x2,(%eax)
	return pkptr;
}
    6990:	89 d8                	mov    %ebx,%eax
    6992:	81 c4 7c 02 00 00    	add    $0x27c,%esp
    6998:	5b                   	pop    %ebx
    6999:	5e                   	pop    %esi
    699a:	5f                   	pop    %edi
    699b:	5d                   	pop    %ebp
    699c:	c3                   	ret    
    699d:	8d 76 00             	lea    0x0(%esi),%esi
    69a0:	81 c4 7c 02 00 00    	add    $0x27c,%esp
    69a6:	5b                   	pop    %ebx
    69a7:	5e                   	pop    %esi
    69a8:	5f                   	pop    %edi
    69a9:	5d                   	pop    %ebp
    69aa:	c3                   	ret    
    69ab:	90                   	nop
    69ac:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

000069b0 <gen_paging>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
FSM_PKT* gen_paging()
{
    69b0:	55                   	push   %ebp
    69b1:	89 e5                	mov    %esp,%ebp
    69b3:	57                   	push   %edi
    69b4:	56                   	push   %esi
    69b5:	53                   	push   %ebx
    69b6:	81 ec b0 03 00 00    	sub    $0x3b0,%esp
    69bc:	e8 fc ff ff ff       	call   69bd <gen_paging+0xd>
	paging.pagingRecordList.pagingRecord[2].ue_Identity.type=1;
	paging.pagingRecordList.pagingRecord[2].ue_Identity.choice.s_TMSI.mmec=12;
	paging.pagingRecordList.pagingRecord[2].ue_Identity.choice.s_TMSI.m_TMSI=123457;
	paging.pagingRecordList.pagingRecord[2].cn_Domain=0;
	struct PCCH_Message pcch_msg;
	pcch_msg.paging=paging;
    69c1:	b9 76 00 00 00       	mov    $0x76,%ecx
	int message_type = 0;
	
	//Generate packets
	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr = fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));  
    69c6:	b8 dc 01 00 00       	mov    $0x1dc,%eax
	paging.havePagingRecord=true;
	paging.systemInfoModification=true;
	paging.havePagingRecord=true;
	paging.pagingRecordList.num=3;
	paging.pagingRecordList.pagingRecord[0].ue_Identity.type=1;
	paging.pagingRecordList.pagingRecord[0].ue_Identity.choice.s_TMSI.mmec=11;
    69cb:	c6 85 28 fe ff ff 0b 	movb   $0xb,-0x1d8(%ebp)
	paging.pagingRecordList.pagingRecord[2].ue_Identity.type=1;
	paging.pagingRecordList.pagingRecord[2].ue_Identity.choice.s_TMSI.mmec=12;
	paging.pagingRecordList.pagingRecord[2].ue_Identity.choice.s_TMSI.m_TMSI=123457;
	paging.pagingRecordList.pagingRecord[2].cn_Domain=0;
	struct PCCH_Message pcch_msg;
	pcch_msg.paging=paging;
    69d2:	8d bd 44 fc ff ff    	lea    -0x3bc(%ebp),%edi
	paging.systemInfoModification=true;
	paging.havePagingRecord=true;
	paging.pagingRecordList.num=3;
	paging.pagingRecordList.pagingRecord[0].ue_Identity.type=1;
	paging.pagingRecordList.pagingRecord[0].ue_Identity.choice.s_TMSI.mmec=11;
	paging.pagingRecordList.pagingRecord[0].ue_Identity.choice.s_TMSI.m_TMSI=123456;
    69d8:	c7 85 29 fe ff ff 40 	movl   $0x1e240,-0x1d7(%ebp)
    69df:	e2 01 00 
	paging.pagingRecordList.pagingRecord[2].ue_Identity.type=1;
	paging.pagingRecordList.pagingRecord[2].ue_Identity.choice.s_TMSI.mmec=12;
	paging.pagingRecordList.pagingRecord[2].ue_Identity.choice.s_TMSI.m_TMSI=123457;
	paging.pagingRecordList.pagingRecord[2].cn_Domain=0;
	struct PCCH_Message pcch_msg;
	pcch_msg.paging=paging;
    69e2:	8d b5 1c fe ff ff    	lea    -0x1e4(%ebp),%esi
	paging.pagingRecordList.pagingRecord[0].ue_Identity.type=1;
	paging.pagingRecordList.pagingRecord[0].ue_Identity.choice.s_TMSI.mmec=11;
	paging.pagingRecordList.pagingRecord[0].ue_Identity.choice.s_TMSI.m_TMSI=123456;
	paging.pagingRecordList.pagingRecord[0].cn_Domain=0;
	paging.pagingRecordList.pagingRecord[1].ue_Identity.type=1;
	paging.pagingRecordList.pagingRecord[1].ue_Identity.choice.s_TMSI.mmec=12;
    69e8:	c6 85 84 fe ff ff 0c 	movb   $0xc,-0x17c(%ebp)
	paging.pagingRecordList.pagingRecord[1].ue_Identity.choice.s_TMSI.m_TMSI=123456;
    69ef:	c7 85 85 fe ff ff 40 	movl   $0x1e240,-0x17b(%ebp)
    69f6:	e2 01 00 
	paging.pagingRecordList.pagingRecord[1].cn_Domain=0;
	paging.pagingRecordList.pagingRecord[2].ue_Identity.type=1;
	paging.pagingRecordList.pagingRecord[2].ue_Identity.choice.s_TMSI.mmec=12;
    69f9:	c6 85 e0 fe ff ff 0c 	movb   $0xc,-0x120(%ebp)
	paging.pagingRecordList.pagingRecord[2].ue_Identity.choice.s_TMSI.m_TMSI=123457;
    6a00:	c7 85 e1 fe ff ff 41 	movl   $0x1e241,-0x11f(%ebp)
    6a07:	e2 01 00 
	paging.pagingRecordList.pagingRecord[2].cn_Domain=0;
	struct PCCH_Message pcch_msg;
	pcch_msg.paging=paging;
    6a0a:	c6 85 1c fe ff ff 01 	movb   $0x1,-0x1e4(%ebp)
    6a11:	c6 45 f0 01          	movb   $0x1,-0x10(%ebp)
    6a15:	c7 85 20 fe ff ff 03 	movl   $0x3,-0x1e0(%ebp)
    6a1c:	00 00 00 
    6a1f:	c7 85 34 ff ff ff 00 	movl   $0x0,-0xcc(%ebp)
    6a26:	00 00 00 
    6a29:	c7 85 dc fe ff ff 01 	movl   $0x1,-0x124(%ebp)
    6a30:	00 00 00 
    6a33:	c7 85 d8 fe ff ff 00 	movl   $0x0,-0x128(%ebp)
    6a3a:	00 00 00 
    6a3d:	c7 85 80 fe ff ff 01 	movl   $0x1,-0x180(%ebp)
    6a44:	00 00 00 
    6a47:	c7 85 7c fe ff ff 00 	movl   $0x0,-0x184(%ebp)
    6a4e:	00 00 00 
    6a51:	c7 85 24 fe ff ff 01 	movl   $0x1,-0x1dc(%ebp)
    6a58:	00 00 00 
    6a5b:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
	int message_type = 0;
	
	//Generate packets
	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr = fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));  
    6a5d:	e8 fc ff ff ff       	call   6a5e <gen_paging+0xae>
	fsm_skb_put(pkptr, msg_len);
    6a62:	ba d8 01 00 00       	mov    $0x1d8,%edx
	int message_type = 0;
	
	//Generate packets
	FSM_PKT* pkptr;
	struct lte_rrc_head* sh_ptr;
	pkptr = fsm_pkt_create(msg_len + sizeof(struct lte_rrc_head));  
    6a67:	89 c3                	mov    %eax,%ebx
	fsm_skb_put(pkptr, msg_len);
    6a69:	e8 fc ff ff ff       	call   6a6a <gen_paging+0xba>
	fsm_mem_cpy(pkptr->data, msg, msg_len);
    6a6e:	8b 83 ac 00 00 00    	mov    0xac(%ebx),%eax
    6a74:	8d 95 44 fc ff ff    	lea    -0x3bc(%ebp),%edx
    6a7a:	b9 d8 01 00 00       	mov    $0x1d8,%ecx
    6a7f:	e8 fc ff ff ff       	call   6a80 <gen_paging+0xd0>

	//Filling head
	if(fsm_skb_headroom(pkptr) < sizeof(struct lte_rrc_head)){
    6a84:	89 d8                	mov    %ebx,%eax
    6a86:	e8 fc ff ff ff       	call   6a87 <gen_paging+0xd7>
    6a8b:	83 f8 03             	cmp    $0x3,%eax
    6a8e:	77 12                	ja     6aa2 <gen_paging+0xf2>
		pkptr = fsm_skb_realloc_headeroom(pkptr,sizeof(struct lte_rrc_head));
    6a90:	89 d8                	mov    %ebx,%eax
    6a92:	ba 04 00 00 00       	mov    $0x4,%edx
    6a97:	e8 fc ff ff ff       	call   6a98 <gen_paging+0xe8>
		if(pkptr == NULL)
    6a9c:	85 c0                	test   %eax,%eax
	fsm_skb_put(pkptr, msg_len);
	fsm_mem_cpy(pkptr->data, msg, msg_len);

	//Filling head
	if(fsm_skb_headroom(pkptr) < sizeof(struct lte_rrc_head)){
		pkptr = fsm_skb_realloc_headeroom(pkptr,sizeof(struct lte_rrc_head));
    6a9e:	89 c3                	mov    %eax,%ebx
		if(pkptr == NULL)
    6aa0:	74 26                	je     6ac8 <gen_paging+0x118>
			return;
	}
	fsm_skb_push(pkptr, sizeof(struct lte_rrc_head));
    6aa2:	89 d8                	mov    %ebx,%eax
    6aa4:	ba 04 00 00 00       	mov    $0x4,%edx
    6aa9:	e8 fc ff ff ff       	call   6aaa <gen_paging+0xfa>
	sh_ptr = (struct lte_rrc_head*)pkptr->data;
	sh_ptr->message_type = message_type;
    6aae:	8b 83 ac 00 00 00    	mov    0xac(%ebx),%eax
    6ab4:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
	return pkptr;
	//rrc_messege_handler_rlc(pkptr);
}
    6aba:	89 d8                	mov    %ebx,%eax
    6abc:	81 c4 b0 03 00 00    	add    $0x3b0,%esp
    6ac2:	5b                   	pop    %ebx
    6ac3:	5e                   	pop    %esi
    6ac4:	5f                   	pop    %edi
    6ac5:	5d                   	pop    %ebp
    6ac6:	c3                   	ret    
    6ac7:	90                   	nop
    6ac8:	81 c4 b0 03 00 00    	add    $0x3b0,%esp
    6ace:	5b                   	pop    %ebx
    6acf:	5e                   	pop    %esi
    6ad0:	5f                   	pop    %edi
    6ad1:	5d                   	pop    %ebp
    6ad2:	c3                   	ret    
    6ad3:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    6ad9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00006ae0 <ApplyRachConfigCommon>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void ApplyRachConfigCommon(struct RachConfigCommon rcc)
{
    6ae0:	55                   	push   %ebp
    6ae1:	89 e5                	mov    %esp,%ebp
    6ae3:	83 ec 20             	sub    $0x20,%esp
    6ae6:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    6ae9:	89 75 f8             	mov    %esi,-0x8(%ebp)
    6aec:	89 7d fc             	mov    %edi,-0x4(%ebp)
    6aef:	e8 fc ff ff ff       	call   6af0 <ApplyRachConfigCommon+0x10>
    6af4:	8b 45 20             	mov    0x20(%ebp),%eax
    6af7:	8b 55 08             	mov    0x8(%ebp),%edx
    6afa:	8b 4d 1c             	mov    0x1c(%ebp),%ecx
    6afd:	8b 7d 10             	mov    0x10(%ebp),%edi
    6b00:	89 45 e8             	mov    %eax,-0x18(%ebp)
    6b03:	8b 45 24             	mov    0x24(%ebp),%eax
    6b06:	8b 75 14             	mov    0x14(%ebp),%esi
    6b09:	8b 5d 18             	mov    0x18(%ebp),%ebx
	FIN(ApplyRachConfigCommon());
	struct RachConfigCommon *rachConfigCommon=NULL;
	rachConfigCommon=fsm_mem_alloc(sizeof(struct RachConfigCommon));
    6b0c:	89 55 e0             	mov    %edx,-0x20(%ebp)
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void ApplyRachConfigCommon(struct RachConfigCommon rcc)
{
    6b0f:	89 45 ec             	mov    %eax,-0x14(%ebp)
    6b12:	8b 45 30             	mov    0x30(%ebp),%eax
	FIN(ApplyRachConfigCommon());
	struct RachConfigCommon *rachConfigCommon=NULL;
	rachConfigCommon=fsm_mem_alloc(sizeof(struct RachConfigCommon));
    6b15:	89 4d e4             	mov    %ecx,-0x1c(%ebp)
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void ApplyRachConfigCommon(struct RachConfigCommon rcc)
{
    6b18:	89 45 f0             	mov    %eax,-0x10(%ebp)
	FIN(ApplyRachConfigCommon());
	struct RachConfigCommon *rachConfigCommon=NULL;
	rachConfigCommon=fsm_mem_alloc(sizeof(struct RachConfigCommon));
    6b1b:	b8 2c 00 00 00       	mov    $0x2c,%eax
    6b20:	e8 fc ff ff ff       	call   6b21 <ApplyRachConfigCommon+0x41>
	rachConfigCommon->preambleInfo.numberOfRA_Preambles=rcc.preambleInfo.numberOfRA_Preambles;
    6b25:	8b 55 e0             	mov    -0x20(%ebp),%edx
	if(rcc.preambleInfo.havePreamblesGroupAConfig=true)//rachConfigCommon中含有PreamblesGroupAConfig信息
	{
	rachConfigCommon->preambleInfo.preamblesGroupAConfig.sizeOfRA_PreamblesGroupA=rcc.preambleInfo.preamblesGroupAConfig.sizeOfRA_PreamblesGroupA;
    6b28:	89 78 08             	mov    %edi,0x8(%eax)
	rachConfigCommon->preambleInfo.preamblesGroupAConfig.messageSizeGroupA=rcc.preambleInfo.preamblesGroupAConfig.messageSizeGroupA;
    6b2b:	89 70 0c             	mov    %esi,0xc(%eax)
	rachConfigCommon->preambleInfo.preamblesGroupAConfig.messagePowerOffsetGroupB=rcc.preambleInfo.preamblesGroupAConfig.messagePowerOffsetGroupB;
    6b2e:	89 58 10             	mov    %ebx,0x10(%eax)
void ApplyRachConfigCommon(struct RachConfigCommon rcc)
{
	FIN(ApplyRachConfigCommon());
	struct RachConfigCommon *rachConfigCommon=NULL;
	rachConfigCommon=fsm_mem_alloc(sizeof(struct RachConfigCommon));
	rachConfigCommon->preambleInfo.numberOfRA_Preambles=rcc.preambleInfo.numberOfRA_Preambles;
    6b31:	89 10                	mov    %edx,(%eax)
	{
	rachConfigCommon->preambleInfo.preamblesGroupAConfig.sizeOfRA_PreamblesGroupA=rcc.preambleInfo.preamblesGroupAConfig.sizeOfRA_PreamblesGroupA;
	rachConfigCommon->preambleInfo.preamblesGroupAConfig.messageSizeGroupA=rcc.preambleInfo.preamblesGroupAConfig.messageSizeGroupA;
	rachConfigCommon->preambleInfo.preamblesGroupAConfig.messagePowerOffsetGroupB=rcc.preambleInfo.preamblesGroupAConfig.messagePowerOffsetGroupB;
	}
	rachConfigCommon->powerRampingParameters.powerRampingStep=rcc.powerRampingParameters.powerRampingStep;
    6b33:	8b 4d e4             	mov    -0x1c(%ebp),%ecx
    6b36:	89 48 14             	mov    %ecx,0x14(%eax)
	rachConfigCommon->powerRampingParameters.preambleInitialReceivedTargetPower=rcc.powerRampingParameters.preambleInitialReceivedTargetPower;
    6b39:	8b 55 e8             	mov    -0x18(%ebp),%edx
    6b3c:	89 50 18             	mov    %edx,0x18(%eax)
	rachConfigCommon->raSupervisionInfo.preambleTransMax=rcc.raSupervisionInfo.preambleTransMax;
    6b3f:	8b 55 ec             	mov    -0x14(%ebp),%edx
    6b42:	89 50 1c             	mov    %edx,0x1c(%eax)
	rachConfigCommon->maxHARQ_Msg3Tx=rcc.maxHARQ_Msg3Tx;
    6b45:	8b 55 f0             	mov    -0x10(%ebp),%edx
    6b48:	89 50 28             	mov    %edx,0x28(%eax)
	//fsm_do_ioctrl(STRM_TO_MAC, IOCCMD_RRCTOMAC_CONFIG_RACH, (void*)rachConfigCommon, sizeof(struct RachConfigCommon));
	fsm_mem_free(rachConfigCommon);
    6b4b:	e8 fc ff ff ff       	call   6b4c <ApplyRachConfigCommon+0x6c>
	FOUT;
}
    6b50:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    6b53:	8b 75 f8             	mov    -0x8(%ebp),%esi
    6b56:	8b 7d fc             	mov    -0x4(%ebp),%edi
    6b59:	89 ec                	mov    %ebp,%esp
    6b5b:	5d                   	pop    %ebp
    6b5c:	c3                   	ret    
    6b5d:	8d 76 00             	lea    0x0(%esi),%esi

00006b60 <ApplyRadioResourceConfigCommon>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void ApplyRadioResourceConfigCommon(struct RadioResourceConfigCommonSib rrcc)
{
    6b60:	55                   	push   %ebp
    6b61:	89 e5                	mov    %esp,%ebp
    6b63:	83 ec 2c             	sub    $0x2c,%esp
    6b66:	e8 fc ff ff ff       	call   6b67 <ApplyRadioResourceConfigCommon+0x7>
	FIN(ApplyRadioResourceConfigCommon());
	ApplyRachConfigCommon(rrcc.rachConfigCommon);
    6b6b:	8b 45 08             	mov    0x8(%ebp),%eax
    6b6e:	89 04 24             	mov    %eax,(%esp)
    6b71:	8b 45 0c             	mov    0xc(%ebp),%eax
    6b74:	89 44 24 04          	mov    %eax,0x4(%esp)
    6b78:	8b 45 10             	mov    0x10(%ebp),%eax
    6b7b:	89 44 24 08          	mov    %eax,0x8(%esp)
    6b7f:	8b 45 14             	mov    0x14(%ebp),%eax
    6b82:	89 44 24 0c          	mov    %eax,0xc(%esp)
    6b86:	8b 45 18             	mov    0x18(%ebp),%eax
    6b89:	89 44 24 10          	mov    %eax,0x10(%esp)
    6b8d:	8b 45 1c             	mov    0x1c(%ebp),%eax
    6b90:	89 44 24 14          	mov    %eax,0x14(%esp)
    6b94:	8b 45 20             	mov    0x20(%ebp),%eax
    6b97:	89 44 24 18          	mov    %eax,0x18(%esp)
    6b9b:	8b 45 24             	mov    0x24(%ebp),%eax
    6b9e:	89 44 24 1c          	mov    %eax,0x1c(%esp)
    6ba2:	8b 45 28             	mov    0x28(%ebp),%eax
    6ba5:	89 44 24 20          	mov    %eax,0x20(%esp)
    6ba9:	8b 45 2c             	mov    0x2c(%ebp),%eax
    6bac:	89 44 24 24          	mov    %eax,0x24(%esp)
    6bb0:	8b 45 30             	mov    0x30(%ebp),%eax
    6bb3:	89 44 24 28          	mov    %eax,0x28(%esp)
    6bb7:	e8 fc ff ff ff       	call   6bb8 <ApplyRadioResourceConfigCommon+0x58>
	ApplyBCCH_Config(rrcc.bcch_Config);
	ApplyPCCH_Config(rrcc.pcch_Config);
	FOUT;
}
    6bbc:	c9                   	leave  
    6bbd:	c3                   	ret    
    6bbe:	66 90                	xchg   %ax,%ax

00006bc0 <DoReceiveSIB2>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void DoReceiveSIB2(struct SystemInformationBlockType2 sib2)
{
    6bc0:	55                   	push   %ebp
    6bc1:	89 e5                	mov    %esp,%ebp
    6bc3:	81 ec c4 00 00 00    	sub    $0xc4,%esp
    6bc9:	89 75 f8             	mov    %esi,-0x8(%ebp)
    6bcc:	89 7d fc             	mov    %edi,-0x4(%ebp)
    6bcf:	e8 fc ff ff ff       	call   6bd0 <DoReceiveSIB2+0x10>
	fsm_printf("[rrc] [fsm] start to handle SIB2 .\n");
    6bd4:	c7 04 24 14 19 00 00 	movl   $0x1914,(%esp)
	if(sib2.haveMBSFN_SubframeConfigList==true)
	{
		//fix me:认为在IE mbsfn_SubframeConfigList中表示的MBSFN子帧中没有发生其它下行分配
	}
	
	ApplyRadioResourceConfigCommon(sib2.radioResourceConfigCommon);
    6bdb:	8d 75 28             	lea    0x28(%ebp),%esi
** Modified by:
** Modified date:
******************************************************************/
void DoReceiveSIB2(struct SystemInformationBlockType2 sib2)
{
	fsm_printf("[rrc] [fsm] start to handle SIB2 .\n");
    6bde:	e8 fc ff ff ff       	call   6bdf <DoReceiveSIB2+0x1f>
	if(sib2.haveMBSFN_SubframeConfigList==true)
	{
		//fix me:认为在IE mbsfn_SubframeConfigList中表示的MBSFN子帧中没有发生其它下行分配
	}
	
	ApplyRadioResourceConfigCommon(sib2.radioResourceConfigCommon);
    6be3:	b9 2f 00 00 00       	mov    $0x2f,%ecx
    6be8:	89 e7                	mov    %esp,%edi
    6bea:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    6bec:	e8 fc ff ff ff       	call   6bed <DoReceiveSIB2+0x2d>
	fsm_printf("[rrc] [fsm] handle SIB2 successfully.\n");
    6bf1:	c7 04 24 38 19 00 00 	movl   $0x1938,(%esp)
    6bf8:	e8 fc ff ff ff       	call   6bf9 <DoReceiveSIB2+0x39>
}
    6bfd:	8b 75 f8             	mov    -0x8(%ebp),%esi
    6c00:	8b 7d fc             	mov    -0x4(%ebp),%edi
    6c03:	89 ec                	mov    %ebp,%esp
    6c05:	5d                   	pop    %ebp
    6c06:	c3                   	ret    
    6c07:	89 f6                	mov    %esi,%esi
    6c09:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00006c10 <SendCellAccessRelatedInfotoUS>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void SendCellAccessRelatedInfotoUS(struct CellAccessRelatedInfo cari)
{
    6c10:	55                   	push   %ebp
    6c11:	89 e5                	mov    %esp,%ebp
    6c13:	83 ec 04             	sub    $0x4,%esp
    6c16:	e8 fc ff ff ff       	call   6c17 <SendCellAccessRelatedInfotoUS+0x7>
	FIN(SendCellAccessRelatedInfotoUS());
	fsm_printf("[rrc] [sib1] start to send CellAccessRelatedInfo to US.\n");
    6c1b:	c7 04 24 60 19 00 00 	movl   $0x1960,(%esp)
    6c22:	e8 fc ff ff ff       	call   6c23 <SendCellAccessRelatedInfotoUS+0x13>
//	fsm_mem_cpy(data, data1, strlen(data1));
//	fsm_mem_cpy(data+strlen(data1), data2, strlen(data2));
//	fsm_mem_cpy(data+strlen(data1)+strlen(data2), data3, strlen(data3));
//	fsm_mem_cpy(data+strlen(data1)+strlen(data2)+strlen(data3), data4, strlen(data4)+1);
//	send_to_user(data, data_size);
	fsm_printf("[rrc] [sib1] send CellAccessRelatedInfo to US successfully.\n");
    6c27:	c7 04 24 9c 19 00 00 	movl   $0x199c,(%esp)
    6c2e:	e8 fc ff ff ff       	call   6c2f <SendCellAccessRelatedInfotoUS+0x1f>
	FOUT;
}
    6c33:	c9                   	leave  
    6c34:	c3                   	ret    
    6c35:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    6c39:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00006c40 <DoReceiveSIB1>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void DoReceiveSIB1(struct SystemInformationBlockType1 *sib1)
{
    6c40:	55                   	push   %ebp
    6c41:	89 e5                	mov    %esp,%ebp
    6c43:	81 ec c8 00 00 00    	sub    $0xc8,%esp
    6c49:	89 75 f8             	mov    %esi,-0x8(%ebp)
    6c4c:	89 7d fc             	mov    %edi,-0x4(%ebp)
    6c4f:	e8 fc ff ff ff       	call   6c50 <DoReceiveSIB1+0x10>
    6c54:	89 c6                	mov    %eax,%esi
	FIN(DoReceiveSIB1());
	fsm_printf("[rrc] [fsm] start to handle SIB1 .\n");
    6c56:	c7 04 24 dc 19 00 00 	movl   $0x19dc,(%esp)
    6c5d:	e8 fc ff ff ff       	call   6c5e <DoReceiveSIB1+0x1e>
	SendCellAccessRelatedInfotoUS(sib1->cellAccessRelatedInfo);
    6c62:	b9 30 00 00 00       	mov    $0x30,%ecx
    6c67:	89 e7                	mov    %esp,%edi
    6c69:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    6c6b:	e8 fc ff ff ff       	call   6c6c <DoReceiveSIB1+0x2c>
	fsm_printf("[rrc] [fsm] handle SIB1 successfully.\n");
    6c70:	c7 04 24 00 1a 00 00 	movl   $0x1a00,(%esp)
    6c77:	e8 fc ff ff ff       	call   6c78 <DoReceiveSIB1+0x38>
	FOUT;
}
    6c7c:	8b 75 f8             	mov    -0x8(%ebp),%esi
    6c7f:	8b 7d fc             	mov    -0x4(%ebp),%edi
    6c82:	89 ec                	mov    %ebp,%esp
    6c84:	5d                   	pop    %ebp
    6c85:	c3                   	ret    
    6c86:	8d 76 00             	lea    0x0(%esi),%esi
    6c89:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00006c90 <Begin_recv_sysinfo>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void Begin_recv_sysinfo(void)
{
    6c90:	55                   	push   %ebp
    6c91:	89 e5                	mov    %esp,%ebp
    6c93:	83 ec 04             	sub    $0x4,%esp
    6c96:	e8 fc ff ff ff       	call   6c97 <Begin_recv_sysinfo+0x7>
	FIN(Begin_recv_sysinfo());
	fsm_printf("[rrc] [paging] tell MAC to receive systeminfomation.\n");
    6c9b:	c7 04 24 28 1a 00 00 	movl   $0x1a28,(%esp)
    6ca2:	e8 fc ff ff ff       	call   6ca3 <Begin_recv_sysinfo+0x13>
	//fsm_do_ioctrl(STRM_TO_MAC, IOCCMD_RRCTOMAC_BEGIN_RECV_SYSINFO, NULL, 0);
	fsm_printf("[rrc] [paging] tell MAC to receive systeminfomation successfully.\n");
    6ca7:	c7 04 24 60 1a 00 00 	movl   $0x1a60,(%esp)
    6cae:	e8 fc ff ff ff       	call   6caf <Begin_recv_sysinfo+0x1f>
	FOUT;
}
    6cb3:	c9                   	leave  
    6cb4:	c3                   	ret    
    6cb5:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    6cb9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00006cc0 <CheckPagingRecord>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void CheckPagingRecord(struct PagingRecordList prl,struct UE_Identity ueIdentity)
{
    6cc0:	55                   	push   %ebp
    6cc1:	89 e5                	mov    %esp,%ebp
    6cc3:	57                   	push   %edi
    6cc4:	56                   	push   %esi
    6cc5:	53                   	push   %ebx
    6cc6:	83 ec 04             	sub    $0x4,%esp
    6cc9:	e8 fc ff ff ff       	call   6cca <CheckPagingRecord+0xa>
    6cce:	8b 5d 08             	mov    0x8(%ebp),%ebx
	FIN(CheckPagingRecord());
	fsm_printf("[rrc] [paging] start to send pagingRecord to US.\n");
    6cd1:	c7 04 24 a4 1a 00 00 	movl   $0x1aa4,(%esp)
    6cd8:	e8 fc ff ff ff       	call   6cd9 <CheckPagingRecord+0x19>
	int i;
	int *state=fsm_current_state_ptr_get();
    6cdd:	e8 fc ff ff ff       	call   6cde <CheckPagingRecord+0x1e>
	for(i=0;i<prl.num;i++)//Check every pagingRecord.
    6ce2:	85 db                	test   %ebx,%ebx
void CheckPagingRecord(struct PagingRecordList prl,struct UE_Identity ueIdentity)
{
	FIN(CheckPagingRecord());
	fsm_printf("[rrc] [paging] start to send pagingRecord to US.\n");
	int i;
	int *state=fsm_current_state_ptr_get();
    6ce4:	89 c7                	mov    %eax,%edi
	for(i=0;i<prl.num;i++)//Check every pagingRecord.
    6ce6:	74 36                	je     6d1e <CheckPagingRecord+0x5e>
** Created Date: 2014/10/07
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void CheckPagingRecord(struct PagingRecordList prl,struct UE_Identity ueIdentity)
    6ce8:	6b db 5c             	imul   $0x5c,%ebx,%ebx
{
	FIN(CheckPagingRecord());
	fsm_printf("[rrc] [paging] start to send pagingRecord to US.\n");
	int i;
	int *state=fsm_current_state_ptr_get();
	for(i=0;i<prl.num;i++)//Check every pagingRecord.
    6ceb:	0f b6 85 dc 01 00 00 	movzbl 0x1dc(%ebp),%eax
	{	
		if(*state =state_IDLE_WAIT_SYSINFO &&prl.pagingRecord[i].ue_Identity.choice.s_TMSI.mmec==ueIdentity.choice.s_TMSI.mmec 
			&& prl.pagingRecord[i].ue_Identity.choice.s_TMSI.m_TMSI==ueIdentity.choice.s_TMSI.m_TMSI)//pagingRecord中的ue_Identity与任一个上层分配的UE identitiy相匹配	
    6cf2:	8d 55 10             	lea    0x10(%ebp),%edx
    6cf5:	8b b5 dd 01 00 00    	mov    0x1dd(%ebp),%esi
** Created Date: 2014/10/07
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void CheckPagingRecord(struct PagingRecordList prl,struct UE_Identity ueIdentity)
    6cfb:	8d 1c 1a             	lea    (%edx,%ebx,1),%ebx
    6cfe:	eb 07                	jmp    6d07 <CheckPagingRecord+0x47>
	fsm_printf("[rrc] [paging] start to send pagingRecord to US.\n");
	int i;
	int *state=fsm_current_state_ptr_get();
	for(i=0;i<prl.num;i++)//Check every pagingRecord.
	{	
		if(*state =state_IDLE_WAIT_SYSINFO &&prl.pagingRecord[i].ue_Identity.choice.s_TMSI.mmec==ueIdentity.choice.s_TMSI.mmec 
    6d00:	83 c2 5c             	add    $0x5c,%edx
{
	FIN(CheckPagingRecord());
	fsm_printf("[rrc] [paging] start to send pagingRecord to US.\n");
	int i;
	int *state=fsm_current_state_ptr_get();
	for(i=0;i<prl.num;i++)//Check every pagingRecord.
    6d03:	39 da                	cmp    %ebx,%edx
    6d05:	74 15                	je     6d1c <CheckPagingRecord+0x5c>
	{	
		if(*state =state_IDLE_WAIT_SYSINFO &&prl.pagingRecord[i].ue_Identity.choice.s_TMSI.mmec==ueIdentity.choice.s_TMSI.mmec 
    6d07:	31 c9                	xor    %ecx,%ecx
    6d09:	38 02                	cmp    %al,(%edx)
    6d0b:	75 f3                	jne    6d00 <CheckPagingRecord+0x40>
    6d0d:	31 c9                	xor    %ecx,%ecx
    6d0f:	39 72 01             	cmp    %esi,0x1(%edx)
    6d12:	0f 94 c1             	sete   %cl
    6d15:	83 c2 5c             	add    $0x5c,%edx
{
	FIN(CheckPagingRecord());
	fsm_printf("[rrc] [paging] start to send pagingRecord to US.\n");
	int i;
	int *state=fsm_current_state_ptr_get();
	for(i=0;i<prl.num;i++)//Check every pagingRecord.
    6d18:	39 da                	cmp    %ebx,%edx
    6d1a:	75 eb                	jne    6d07 <CheckPagingRecord+0x47>
    6d1c:	89 0f                	mov    %ecx,(%edi)
		//	send_to_user(data, data_size); 
		}
				
	}

	fsm_printf("[rrc] [paging] send pagingRecord to US successfully.\n");
    6d1e:	c7 04 24 d8 1a 00 00 	movl   $0x1ad8,(%esp)
    6d25:	e8 fc ff ff ff       	call   6d26 <CheckPagingRecord+0x66>
	FOUT;	
}
    6d2a:	83 c4 04             	add    $0x4,%esp
    6d2d:	5b                   	pop    %ebx
    6d2e:	5e                   	pop    %esi
    6d2f:	5f                   	pop    %edi
    6d30:	5d                   	pop    %ebp
    6d31:	c3                   	ret    
    6d32:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    6d39:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00006d40 <DoReceivePaging>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void DoReceivePaging(struct Paging *paging,struct UE_Identity ueIdentity)
{
    6d40:	55                   	push   %ebp
    6d41:	89 e5                	mov    %esp,%ebp
    6d43:	81 ec 34 02 00 00    	sub    $0x234,%esp
    6d49:	89 5d f4             	mov    %ebx,-0xc(%ebp)
    6d4c:	89 75 f8             	mov    %esi,-0x8(%ebp)
    6d4f:	89 7d fc             	mov    %edi,-0x4(%ebp)
    6d52:	e8 fc ff ff ff       	call   6d53 <DoReceivePaging+0x13>
    6d57:	89 c3                	mov    %eax,%ebx
	FIN(DoReceivePaging());
	fsm_printf("[rrc] [fsm] start to handle paging.\n");
    6d59:	c7 04 24 10 1b 00 00 	movl   $0x1b10,(%esp)
    6d60:	e8 fc ff ff ff       	call   6d61 <DoReceivePaging+0x21>
	int *state = fsm_current_state_ptr_get();
    6d65:	e8 fc ff ff ff       	call   6d66 <DoReceivePaging+0x26>
	if(*state ==state_IDLE_NORMALLY && paging->havePagingRecord==true)
    6d6a:	83 38 07             	cmpl   $0x7,(%eax)
    6d6d:	74 39                	je     6da8 <DoReceivePaging+0x68>
	{
		CheckPagingRecord(paging->pagingRecordList,ueIdentity);
	}
	
	if (paging->systemInfoModification==true)
    6d6f:	80 bb d4 01 00 00 00 	cmpb   $0x0,0x1d4(%ebx)
    6d76:	74 11                	je     6d89 <DoReceivePaging+0x49>
	{
		fsm_printf("[rrc] [fsm] paging.systemInfoModification==true, renew the system information from enb.\n");
    6d78:	c7 04 24 38 1b 00 00 	movl   $0x1b38,(%esp)
    6d7f:	e8 fc ff ff ff       	call   6d80 <DoReceivePaging+0x40>
		Begin_recv_sysinfo();
    6d84:	e8 fc ff ff ff       	call   6d85 <DoReceivePaging+0x45>
	}

	fsm_printf("[rrc] [fsm] handle paging successfully.\n");
    6d89:	c7 04 24 94 1b 00 00 	movl   $0x1b94,(%esp)
    6d90:	e8 fc ff ff ff       	call   6d91 <DoReceivePaging+0x51>
	FOUT;
}
    6d95:	8b 5d f4             	mov    -0xc(%ebp),%ebx
    6d98:	8b 75 f8             	mov    -0x8(%ebp),%esi
    6d9b:	8b 7d fc             	mov    -0x4(%ebp),%edi
    6d9e:	89 ec                	mov    %ebp,%esp
    6da0:	5d                   	pop    %ebp
    6da1:	c3                   	ret    
    6da2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
void DoReceivePaging(struct Paging *paging,struct UE_Identity ueIdentity)
{
	FIN(DoReceivePaging());
	fsm_printf("[rrc] [fsm] start to handle paging.\n");
	int *state = fsm_current_state_ptr_get();
	if(*state ==state_IDLE_NORMALLY && paging->havePagingRecord==true)
    6da8:	80 3b 00             	cmpb   $0x0,(%ebx)
    6dab:	74 c2                	je     6d6f <DoReceivePaging+0x2f>
	{
		CheckPagingRecord(paging->pagingRecordList,ueIdentity);
    6dad:	8d 75 08             	lea    0x8(%ebp),%esi
    6db0:	b9 16 00 00 00       	mov    $0x16,%ecx
    6db5:	8d bc 24 d0 01 00 00 	lea    0x1d0(%esp),%edi
    6dbc:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    6dbe:	8d 73 04             	lea    0x4(%ebx),%esi
    6dc1:	89 e7                	mov    %esp,%edi
    6dc3:	b1 74                	mov    $0x74,%cl
    6dc5:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
    6dc7:	e8 fc ff ff ff       	call   6dc8 <DoReceivePaging+0x88>
    6dcc:	eb a1                	jmp    6d6f <DoReceivePaging+0x2f>
    6dce:	66 90                	xchg   %ax,%ax

00006dd0 <DoReceiveMIB>:
** -----------------------------------------------
** Modified by:
** Modified date:
******************************************************************/
void DoReceiveMIB(struct MasterInformationBlock * mib)
{
    6dd0:	55                   	push   %ebp
    6dd1:	89 e5                	mov    %esp,%ebp
    6dd3:	83 ec 04             	sub    $0x4,%esp
    6dd6:	e8 fc ff ff ff       	call   6dd7 <DoReceiveMIB+0x7>
	FIN(DoReceiveMIB());
	fsm_printf("[rrc] [fsm] start to handle MIB .\n");
    6ddb:	c7 04 24 c0 1b 00 00 	movl   $0x1bc0,(%esp)
    6de2:	e8 fc ff ff ff       	call   6de3 <DoReceiveMIB+0x13>
	ApplyPhich_Config(mib->phich_Config);
	int *state=fsm_current_state_ptr_get();
    6de7:	e8 fc ff ff ff       	call   6de8 <DoReceiveMIB+0x18>
	if (checkTimer(TIMER_T311)&&(*state==state_IDLE_NORMALLY||*state==state_CONNECTED_NORMALLY))//如果当 T311正在运行时，UE处在RRC_IDLE状态，或者处于RRC_CONNECTED状态
    6dec:	b8 37 01 00 00       	mov    $0x137,%eax
    6df1:	e8 fc ff ff ff       	call   6df2 <DoReceiveMIB+0x22>
		//fix me: Judge the validity of the system information(NULL)

		//fix me: dl_Bandwidth will be sent to ??
		//fsm_do_ioctrl(STRM_TO_MAC,IOCCMD_RRCTOMAC_DL_BANDWIDTH,sizeof(mib->dl_Bandwidth));
	}
	fsm_printf("[rrc] [fsm] handle MIB successfully.\n");
    6df6:	c7 04 24 e4 1b 00 00 	movl   $0x1be4,(%esp)
    6dfd:	e8 fc ff ff ff       	call   6dfe <DoReceiveMIB+0x2e>
	FOUT;
}
    6e02:	c9                   	leave  
    6e03:	c3                   	ret    
