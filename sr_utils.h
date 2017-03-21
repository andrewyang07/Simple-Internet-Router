/*
 *  Copyright (c) 2009 Roger Liao <rogliao@cs.stanford.edu>
 *  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef SR_UTILS_H
#define SR_UTILS_H

#include "sr_rt.h"
#include "sr_if.h"

uint16_t cksum(const void *_data, int len);

uint16_t ethertype(uint8_t *buf);
uint8_t ip_protocol(uint8_t *buf);

void print_addr_eth(uint8_t *addr);
void print_addr_ip(struct in_addr address);
void print_addr_ip_int(uint32_t ip);

void print_hdr_eth(uint8_t *buf);
void print_hdr_ip(uint8_t *buf);
void print_hdr_icmp(uint8_t *buf);
void print_hdr_arp(uint8_t *buf);

/* prints all headers, starting from eth */
void print_hdrs(uint8_t *buf, uint32_t length);

/* Helper functions */

struct sr_if *find_dst_if(struct sr_instance *sr, uint32_t dst);

int sr_send_reply(struct sr_instance *sr, sr_ethernet_hdr_t *e_hdr,
 sr_arp_hdr_t *a_hdr, struct sr_if* iface);
/* Getting headers */
sr_arp_hdr_t *get_arp_hdr(uint8_t *packet);
sr_ethernet_hdr_t *get_eth_hdr(uint8_t *packet);
sr_ip_hdr_t *get_ip_hdr(uint8_t *packet);
sr_icmp_hdr_t *get_icmp_hdr(uint8_t *packet);


/* Sanity check */
int sanity_check_arp(unsigned int len);
int sanity_check_ip(unsigned int len);
int sanity_check_icmp(unsigned int len);

/* Checksum check */
int check_ip_chksum(sr_ip_hdr_t *ip_hdr);
int check_icmp_chksum(uint16_t ip_len, sr_icmp_hdr_t *icmp_hdr);



#endif /* -- SR_UTILS_H -- */
