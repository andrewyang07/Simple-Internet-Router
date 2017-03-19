#include <stdlib.h>
#include <string.h>
#include "sr_router.h"
#include "sr_utils.h"
#include "sr_handle_arp.h"


void sr_handlearp(struct sr_instance* sr,
    uint8_t *packet, unsigned int len, struct sr_if *rec_iface) {
  sr_ethernet_hdr_t *eth_hdr = get_eth_hdr(packet);
  sr_arp_hdr_t *arp_hdr = get_arp_hdr(packet);

  printf("\nReceived an ARP frame, processing it");

  switch(ntohs(arp_hdr->ar_op)) {
    case arp_op_request:
    if(arp_hdr->ar_tip == rec_iface->ip) {
      printf("\n\tThis is an ARP reply at interfce %s.", rec_iface->name);

      pthread_mutex_lock(&sr->cache.lock);



      pthread_mutex_unlock(&sr->cache.lock);
    }
      break;
    case arp_op_reply:
      break;
    default:
      Printf("\n Wrong ARP frame received, dropping it");
      return;
  }
}
