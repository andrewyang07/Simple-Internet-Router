/**********************************************************************
 * file:  sr_router.c
 * date:  Mon Feb 18 12:50:42 PST 2002
 * Contact: casado@stanford.edu
 *
 * Description:
 *
 * This file contains all the functions that interact directly
 * with the routing table, as well as the main entry method
 * for routing.
 *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "sr_if.h"
#include "sr_rt.h"
#include "sr_router.h"
#include "sr_protocol.h"
#include "sr_arpcache.h"
#include "sr_utils.h"

/* TODO: Add constant definitions here... */

/* TODO: Add helper functions here... */

/* See pseudo-code in sr_arpcache.h */
void handle_arpreq(struct sr_instance* sr, struct sr_arpreq *req){
  /* TODO: Fill this in */

}

/*---------------------------------------------------------------------
 * Method: sr_init(void)
 * Scope:  Global
 *
 * Initialize the routing subsystem
 *
 *---------------------------------------------------------------------*/

void sr_init(struct sr_instance* sr)
{
    /* REQUIRES */
    assert(sr);

    /* Initialize cache and cache cleanup thread */
    sr_arpcache_init(&(sr->cache));

    pthread_attr_init(&(sr->attr));
    pthread_attr_setdetachstate(&(sr->attr), PTHREAD_CREATE_JOINABLE);
    pthread_attr_setscope(&(sr->attr), PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&(sr->attr), PTHREAD_SCOPE_SYSTEM);
    pthread_t thread;

    pthread_create(&thread, &(sr->attr), sr_arpcache_timeout, sr);

    /* TODO: (opt) Add initialization code here */

} /* -- sr_init -- */

/*---------------------------------------------------------------------
 * Method: sr_handlepacket(uint8_t* p,char* interface)
 * Scope:  Global
 *
 * This method is called each time the router receives a packet on the
 * interface.  The packet buffer, the packet length and the receiving
 * interface are passed in as parameters. The packet is complete with
 * ethernet headers.
 *
 * Note: Both the packet buffer and the character's memory are handled
 * by sr_vns_comm.c that means do NOT free either (signified by "lent" comment).
 * Make a copy of the
 * packet instead if you intend to keep it around beyond the scope of
 * the method call.
 *
 *---------------------------------------------------------------------*/

 /*
 struct sr_instance
 {
     int  sockfd;    socket to server
     char user[32];  user name
     char host[32];  host name
     char template[30];  template name if any
     unsigned short topo_id;
     struct sockaddr_in sr_addr;  address to server
     struct sr_if* if_list;  list of interfaces
     struct sr_rt* routing_table;  routing table
     struct sr_arpcache cache;    ARP cache
     pthread_attr_t attr;
     FILE* logfile;
 };
 */


void sr_handlepacket(struct sr_instance* sr,
        uint8_t * packet/* lent */,
        unsigned int len,
        char* interface/* lent */){


  /*len = data length
    uint8_t is 8bits integer
    interface store which interface comes from
  */

  /* REQUIRES */
  assert(sr);
  assert(packet);
  /*assert(len); */
  assert(interface);

  printf("*** -> Received packet of length %d\n",len);

  /* TODO: Add forwarding logic here */
  /* uint32_t sum = cksum (const void *_data, int len); */
  /* struct if_tt*           arp_table = 0; */
  struct sr_if *iface = sr_get_interface(sr, interface);
  assert(iface);

  sr_ethernet_hdr_t *e_hdr = get_eth_hdr(packet);
  sr_arp_hdr_t *a_hdr = get_arp_hdr(packet);
  /* a_hdr = get_arp_hdr(packet); */
  /* printf("\nEthernet header is: %d, ARP header is: %d", e_hdr->ether_type,
   a_hdr); */
  uint16_t type_ = ntohs(e_hdr->ether_type);
  switch(type_){
    case ethertype_arp:
      printf("\nARP, Packet type: %d, Arp type: %d",type_,ethertype_arp);
      if(!sanity_check_arp(len)){
        printf("\nSanity check failed, ARP packet dropped.");
        break;
      }
      handle_arp(sr, e_hdr, a_hdr, iface);
      /*sr_handlearp(sr, packet, len, iface); */
      break;

    case ethertype_ip:
      printf("\nIP, Packet type: %d, IP type: %d",type_,ethertype_ip);
      break;

    default:
      printf("\nUnknown Packet type. Packet dropped.");
      printf("\nPacket type: %d,IP type: %d, ARP type: %d",type_,ethertype_ip,ethertype_arp);
      break;
  }

}/* -- sr_handlepacket -- */


void handle_arp(struct sr_instance* sr, uint8_t *packet, unsigned int len,
  struct sr_if *iface){
      sr_ethernet_hdr_t *e_hdr = get_eth_hdr(packet);
      sr_arp_hdr_t *a_hdr = get_arp_hdr(packet);
      printf("\nAn ARP packet received! Processing...");
      switch(ntohs(a_hdr->ar_op)) {
        case arp_op_request:
          printf("\nAn ARP request received!");
          /*firstly should check the arp cache using sr_arpcache_lookup
          */

          struct sr_rt* temp=sr->routing_table;

          /*printf("Sender MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
          a_hdr->ar_sha[0] & 0xff, a_hdr->ar_sha[1] & 0xff, a_hdr->ar_sha[2] & 0xff,
          a_hdr->ar_sha[3] & 0xff, a_hdr->ar_sha[4] & 0xff, a_hdr->ar_sha[5] & 0xff);*/


          break;
        case arp_op_reply:
          printf("\nAn ARP reply received!");

          /*struct sr_arp_req *req = sr_arpcache_insert(cache, a_hdr->ar_sha, a_hdr->ar_sip);
          if (req!=NULL)
          {
            pkg=req->sr_packet;
            while (pkg!=NULL)
            {
              bool success=send(pkg->iface, pkg->buf, pkg->len, 0);
              if (success==-1) continue;
              pkg=pkg->sr_packet;
            }
            sr_arpreq_destroy(cache, req);
          }


          */




          /*printf("Sender MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
          a_hdr->ar_sha[0] & 0xff, a_hdr->ar_sha[1] & 0xff, a_hdr->ar_sha[2] & 0xff,
          a_hdr->ar_sha[3] & 0xff, a_hdr->ar_sha[4] & 0xff, a_hdr->ar_sha[5] & 0xff);*/



          /*should save into request queue*/

          /*The ARP reply processing code should move entries from the ARP request
          queue to the ARP cache:

          # When servicing an arp reply that gives us an IP->MAC mapping
          req = arpcache_insert(ip, mac)

          if req:
              send all packets on the req->packets linked list
              arpreq_destroy(req)*/

          break;
        default:
          printf("\nCannot recognize this ARP frame");
          return;
      }
  }
