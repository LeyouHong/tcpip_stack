#ifndef __IGP_NBRSHIP__
#define __IGP_NBRSHIP__

typedef enum isis_adj_state_ {
    ISIS_ADJ_STATE_UNKNOWN,
    ISIS_ADJ_STATE_DOWN,
    ISIS_ADJ_STATE_INIT,
    ISIS_ADJ_STATE_UP
} isis_adj_state_t;

static inline char *
isis_adj_state_str(isis_adj_state_t adj_state) {

    switch(adj_state){
        case ISIS_ADJ_STATE_DOWN:
            return "Down";
        case ISIS_ADJ_STATE_INIT:
            return "Init";
        case ISIS_ADJ_STATE_UP:
            return "Up";
        default : ;
    }
    return NULL;
}

typedef struct isis_adjacency_ {
    /* back ptr to the the interface */
    interface_t *intf; 
    
    /*Nbr lo 0 address */
    uint32_t nbr_rtr_id;

    /* nbr Device Name */
    unsigned char nbr_name[NODE_NAME_SIZE];

    /* Nbr intf Ip */
    uint32_t nbr_intf_ip;

    /* Mac Address */
    mac_add_t nbr_mac;

    /* Nbr if index */
    uint32_t remote_if_index;

    /* Adj State */
    isis_adj_state_t adj_state;

    /* timestamp when Adj state changed */
    time_t last_transition_time;

    /* Hold time in sec reported by nbr*/
    uint32_t hold_time;

    /* Nbr link cost Value */
    uint32_t cost; 

     /* uptime */
    time_t uptime;

    /* Expiry timer */
    timer_event_handle *expiry_timer;

    /* Delete timer */
    timer_event_handle *delete_timer;
    
    glthread_t glue;
} isis_adjacency_t;
GLTHREAD_TO_STRUCT(glthread_to_isis_adjacency, isis_adjacency_t, glue);

void isis_update_interface_adjacency_from_hello(interface_t *iif, 
                                                byte *hello_tlv_buff,
                                                size_t tlv_buff_size);

isis_adjacency_t *
isis_find_adjacency_on_interface(
        interface_t *intf,
        uint32_t nbr_rtr_id);

void isis_show_adjacency(isis_adjacency_t *adjacency, uint8_t tab_spaces);

#endif