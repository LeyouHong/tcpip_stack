#ifndef __ISIS_RTR__
#define __ISIS_RTR__

#define ISIS_NODE_INFO(node_ptr) \
  ((isis_node_info_t *)(node_ptr->node_nw_prop.isis_node_info))

typedef struct isis_node_info_ {
//
} isis_node_info_t;

bool isis_is_protocol_enable_on_node(node_t *node);

#endif