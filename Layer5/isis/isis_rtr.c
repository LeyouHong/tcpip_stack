#include "../../tcp_public.h"
#include "isis_rtr.h"
#include "isis_pkt.h"

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
  printf("ISIS Protocol: %s\n", isis_is_protocol_enable_on_node(node) ? "Enable" : "Disable");
}