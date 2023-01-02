#ifndef __ISIS_CONST__
#define __ISIS_CONST__

#define ISIS_ETH_PKT_TYPE 131 //random choosen
#define ISIS_PTP_HELLO_PKT_TYPE 17
#define ISIS_LSP_PKT_TYPE 18

#define ISIS_DEFAULT_HELLO_INTERVAL 3
#define ISIS_DEFAULT_INTF_COST  10
#define ISIS_HOLD_TIME_FACTOR   2

/*ISIS TLV*/
#define ISIS_TLV_HOSTNAME 137
#define ISIS_TLV_RTR_ID 134
#define ISIS_TLV_IF_IP 132
#define ISIS_TLV_HOLD_TIME 5
#define ISIS_TLV_METRIC_VAL 6
#define ISIS_TLV_IF_INDEX 4

#define ISIS_IS_REACH_TLV  22 // as per standard 
#define ISIS_TLV_IF_INDEX   4 // as per standard
#define ISIS_TLV_LOCAL_IP   6 // as per standard
#define ISIS_TLV_REMOTE_IP  8 // as per standard
#define ISIS_TLV_ON_DEMAND  111 // imaginary
#define ISIS_TLV_IF_MAC     131 // Imaginary
#define ISIS_TLV_IP_REACH   130

/* Feature Name for logging */
#define ISIS_ADJ_MGMT   " ISIS(ADJ MGMT)"
#define ISIS_LSPDB_MGMT " ISIS(LSPDB MGMT)"
#define ISIS_SPF        " ISIS(SPF)"
#define ISIS_ERROR      " ISIS(ERROR)"
#define ISIS_PKT        " ISIS(PKT)"

#endif
