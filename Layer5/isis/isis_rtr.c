#include "../../tcp_public.h"
#include "isis_const.h"
#include "isis_rtr.h"
#include "isis_pkt.h"
#include "isis_intf.h"

bool isis_is_protocol_enable_on_node(node_t *node) {
    isis_node_info_t *isis_node_info = ISIS_NODE_INFO(node);

    if (!isis_node_info ) {
        return false;
    }   

    return true;
}

void isis_init(node_t *node) {
  isis_node_info_t *isis_node_info = ISIS_NODE_INFO(node);
  if (isis_node_info) return;

  isis_node_info = calloc(1, sizeof(isis_node_info_t));
  /*ISIS_NODE_INFO(node) = isis_node_info*/
  node->node_nw_prop.isis_node_info = isis_node_info;

  /*when node init, register isis pkt rule, push packet to the protocol by using isis_pkt_receive*/
  tcp_stack_register_l2_pkt_trap_rule(node, isis_pkt_trap_rule, isis_pkt_receive);
}

void isis_de_init(node_t *node) {
  isis_node_info_t *isis_node_info = ISIS_NODE_INFO(node);
  if (!isis_node_info) return;

  free(isis_node_info);
  /*ISIS_NODE_INFO(node) = NULL*/
  node->node_nw_prop.isis_node_info = NULL;

  tcp_stack_de_register_l2_pkt_trap_rule(node, isis_pkt_trap_rule, isis_pkt_receive);
}

void isis_show_node_protocol_state(node_t *node) {
  interface_t *intf;
  bool is_enabled  = isis_is_protocol_enable_on_node(node);

  printf("ISIS Protocol : %sabled\n", is_enabled ? "En" : "Dis");

  if (!is_enabled) return;

  ITERATE_NODE_INTERFACES_BEGIN(node, intf) {
    if (!isis_node_intf_is_enable(intf)) {
      continue;
    }
    isis_show_interface_protocol_state(intf);
  } ITERATE_NODE_INTERFACES_END(node, intf);
}

void isis_one_time_registration() {
  nfc_register_for_pkt_tracing(ISIS_ETH_PKT_TYPE, isis_print_pkt);
}