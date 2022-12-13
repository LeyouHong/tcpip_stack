#include "../../tcp_public.h"
#include "isis_rtr.h"

bool isis_is_protocol_enable_on_node(node_t *node) {
    isis_node_info_t *isis_node_info = ISIS_NODE_INFO(node);

    if (!isis_node_info ) {
        return false;
    }   

    return true;
}