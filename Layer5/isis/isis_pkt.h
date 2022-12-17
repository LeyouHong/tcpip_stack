#ifndef __ISIS_PKT__
#define __ISIS_PKT__

#define ISIS_INTF_COST(intf_ptr) \
    (((isis_intf_info_t *)((intf_ptr)->intf_nw_props.isis_intf_info))->cost)

#define ISIS_INTF_HELLO_INTERVAL(intf_ptr) \
    (((isis_intf_info_t *)((intf_ptr)->intf_nw_props.isis_intf_info))->hello_interval)

bool isis_pkt_trap_rule(char *pkt, size_t pkt_size);
void isis_pkt_receive(void *arg, size_t arg_size);

#endif
