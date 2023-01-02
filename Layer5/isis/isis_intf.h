#ifndef __ISIS_INIF__
#define __ISIS_INIF__

typedef struct isis_adjacency_ isis_adjacency_t; //forward declarations

typedef struct isis_intf_info_ {

  uint32_t cost;
  uint16_t hello_interval; 
  timer_event_handle *hello_xmit_timer;
  isis_adjacency_t *adjacency;

  /* Adj list on this interface */
  glthread_t adj_list_head;
} isis_intf_info_t;
GLTHREAD_TO_STRUCT(intf_adj_list_head_to_intf_info, 
                                            isis_intf_info_t,  adj_list_head);

#define ISIS_INTF_INFO(intf_ptr) \
  ((isis_intf_info_t *)(intf_ptr->intf_nw_props.isis_intf_info))

#define ISIS_INTF_COST(intf_ptr) \
  (((isis_intf_info_t *)(intf_ptr->intf_nw_props.isis_intf_info))->cost)

#define ISIS_INTF_HELLO_INTERVAL(intf_ptr) \
  (((isis_intf_info_t *)(intf_ptr->intf_nw_props.isis_intf_info))->hello_interval)

#define ISIS_INTF_HELLO_XMIT_TIMER(intf_ptr) \
  (((isis_intf_info_t *)(intf_ptr->intf_nw_props.isis_intf_info))->hello_xmit_timer)

#define ISIS_INTF_ADJ_LST_HEAD(intf_ptr) \
    (&(((isis_intf_info_t *)((intf_ptr)->intf_nw_props.isis_intf_info))->adj_list_head))

bool isis_node_intf_is_enable(interface_t *intf);

void isis_enable_protocol_on_interface(interface_t *intf);

void isis_disable_protocol_on_interface(interface_t *intf);

void isis_start_sending_hellos(interface_t *intf);

void isis_stop_sending_hellos(interface_t *intf);

bool isis_interface_qualify_to_send_hellos(interface_t *intf);

void isis_show_interface_protocol_state(interface_t *intf);

#endif