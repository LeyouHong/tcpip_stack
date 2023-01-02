#include "../../tcp_public.h"
#include "isis_adjacency.h"
#include "isis_intf.h"
#include "isis_const.h"

static void
isis_init_adjacency(isis_adjacency_t *adjacency) {

    memset(adjacency, 0, sizeof(isis_adjacency_t));
    adjacency->last_transition_time = time(NULL); /* Current system time */
    adjacency->adj_state = ISIS_ADJ_STATE_DOWN;
    init_glthread(&adjacency->glue);
}

void isis_update_interface_adjacency_from_hello(interface_t *iif, 
                                                byte *hello_tlv_buffer,
                                                size_t tlv_buff_size) {
  /*Algo: 
  1. if isis_adjacency doesn't exist, create a new one in down state.
  2. Iterate over hello_tlv_buffer and copy all 6 tlvs value from hello to adjacency members
  3. Track if there is a change in any attribute of existing adjacency in step2(bool nbr_attr_changed)
  4. Keep track if Adj is newly created(bool new_adj)
    */
  char ip_addr[16];  
  char * router_id_str;
  uint32_t *router_id_int;
  bool new_adj = false;
  bool nbr_attr_changed = false;
  uint32_t four_byte_data;
  uint8_t tlv_data_len;
  isis_adjacency_t *adjacency = NULL;

  router_id_int = (uint32_t *)tlv_buffer_get_particular_tlv(
                    hello_tlv_buffer, 
                    tlv_buff_size,
                    ISIS_TLV_RTR_ID, 
                    &tlv_data_len);

  adjacency = isis_find_adjacency_on_interface(iif, *router_id_int);

  if (!adjacency) {
    adjacency = calloc(1, sizeof(isis_adjacency_t));
    isis_init_adjacency(adjacency);
    adjacency->intf = iif;
    glthread_add_next(ISIS_INTF_ADJ_LST_HEAD(iif), &adjacency->glue);
    new_adj = true;
    router_id_str = tcp_ip_covert_ip_n_to_p(*router_id_int, ip_addr);
    sprintf(tlb, "%s : New Adjacency for nbr %s on intf %s Created\n",
        ISIS_ADJ_MGMT, router_id_str, iif->if_name);
    tcp_trace(iif->att_node, iif, tlb);
  }

  byte tlv_type, tlv_len, *tlv_value = NULL;

  ITERATE_TLV_BEGIN(hello_tlv_buffer, tlv_type, tlv_len, tlv_value, tlv_buff_size) {

    switch(tlv_type) {
      
      case ISIS_TLV_HOSTNAME:
        if (memcmp(adjacency->nbr_name, tlv_value, tlv_len)) {
          nbr_attr_changed = true;
          memcpy(adjacency->nbr_name, tlv_value, tlv_len);
        }
        break;
      case ISIS_TLV_RTR_ID:
        if (adjacency->nbr_rtr_id != *(uint32_t *)(tlv_value)) {
            adjacency->nbr_rtr_id = *(uint32_t *)(tlv_value);
        }
        break;
      case ISIS_TLV_IF_IP:
        memcpy((byte *)&four_byte_data, tlv_value, sizeof(four_byte_data));
        if (adjacency->nbr_intf_ip != four_byte_data ) {
            adjacency->nbr_intf_ip = four_byte_data;
        }
        break;
      case ISIS_TLV_HOLD_TIME:
        adjacency->hold_time = *((uint32_t *)tlv_value);
        break;
      case ISIS_TLV_METRIC_VAL:
        if (adjacency->cost != *((uint32_t *)tlv_value)) {
            adjacency->cost = *((uint32_t *)tlv_value);
        }
        break;
      case ISIS_TLV_IF_INDEX:
        if (adjacency->remote_if_index != *(uint32_t *)tlv_value) {
            memcpy((byte *)&adjacency->remote_if_index, tlv_value, tlv_len);
        }
        break;  
      default:;          
    }

  } ITERATE_TLV_END(hello_tlv_buffer, tlv_type, tlv_len, tlv_value, tlv_buff_size);
  
}

isis_adjacency_t *
isis_find_adjacency_on_interface(
        interface_t *intf,
        uint32_t nbr_rtr_id) {

    glthread_t *curr;
    isis_adjacency_t *adjacency;
    isis_intf_info_t *intf_info;

    intf_info = ISIS_INTF_INFO(intf);

    if(!intf_info) return NULL;

    ITERATE_GLTHREAD_BEGIN(ISIS_INTF_ADJ_LST_HEAD(intf), curr){

        adjacency = glthread_to_isis_adjacency(curr);
        if (!nbr_rtr_id) return adjacency;
        if (adjacency->nbr_rtr_id == nbr_rtr_id) {
            return adjacency;
        }
    } ITERATE_GLTHREAD_END(ISIS_INTF_ADJ_LST_HEAD(intf), curr);

    return NULL;
}

void isis_show_adjacency(isis_adjacency_t *adjacency, uint8_t tab_spaces) {
  char ip_addr_str[16];

  PRINT_TABS(tab_spaces);
  tcp_ip_covert_ip_n_to_p (adjacency->nbr_rtr_id, ip_addr_str);
  printf("Nbr : %s(%s)\n", adjacency->nbr_name, ip_addr_str);

  PRINT_TABS(tab_spaces);
  tcp_ip_covert_ip_n_to_p( adjacency->nbr_intf_ip, ip_addr_str);
  printf("Nbr intf ip : %s  ifindex : %u\n",
      ip_addr_str,
      adjacency->remote_if_index);

  PRINT_TABS(tab_spaces);
    printf("State : %s   HT : %u sec   Cost : %u\n",
        isis_adj_state_str(adjacency->adj_state),
        adjacency->hold_time,
        adjacency->cost);
}