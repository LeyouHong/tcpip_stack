#ifndef __ISIS_PKT__
#define __ISIS_PKT__

typedef uint16_t isis_pkt_type_t;

#pragma pack (push,1)
/* Header of ISIS PKTS, common for Hellos and LSPs */
typedef uint8_t isis_pkt_hdr_flags_t;

typedef struct isis_pkt_hdr_{

    isis_pkt_type_t isis_pkt_type;
    uint32_t seq_no; /* meaningful only for LSPs */
    uint32_t rtr_id;
    isis_pkt_hdr_flags_t flags;
} isis_pkt_hdr_t;
#pragma pack(pop)

bool isis_pkt_trap_rule(char *pkt, size_t pkt_size);
void isis_pkt_receive(void *arg, size_t arg_size);
byte* isis_prepare_hello_pkt(interface_t *intf, size_t *hello_pkt_size);
void isis_print_pkt(void *arg, size_t arg_size);

#endif
