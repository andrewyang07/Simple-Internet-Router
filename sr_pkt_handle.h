#ifndef SR_PKT_HANDLE_H
#define SR_PKY_HANDLE_H


void sr_handlearp(struct sr_instance* sr, uint8_t *packet,
  unsigned int len, struct sr_if *iface);

void sr_handlerep(struct sr_instance* sr, sr_arp_hdr_t *arp_hdr,
  struct sr_if* iface)


#endif
