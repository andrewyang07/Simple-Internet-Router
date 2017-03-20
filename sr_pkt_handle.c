#include <stdlib.h>
#include <string.h>
#include "sr_router.h"
#include "sr_utils.h"
#include "sr_pkt_handle.h"

/* Hanle ARP frames */
void sr_handlearp(struct sr_instance* sr, uint8_t *packet,
  unsigned int len, struct sr_if *rec_iface) {
  sr_ethernet_hdr_t *eth_hdr = packet_get_eth_hdr(packet);
  sr_arp_hdr_t *arp_hdr = packet_get_arp_hdr(packet);
}
