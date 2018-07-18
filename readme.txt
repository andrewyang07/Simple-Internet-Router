Group Members:
Member1: Yang Yang, yya123@sfu.ca
Member2: Site Li, sitel@sfu.ca

Work Division:

Yang Yang:

1. Implemented and tested helper functions in sr_utils.c
2. Finished and tested sr_handlepacket function in sr_router.c
3. Implemented and tested handle_IP function in sr_router.c
4. Added enum sr_icmp_type and enum sr_icmp_code and enum sr_ip_protocol in sr_protocol.h
5. Implemented and tested handle_IP function.

Site Li:

1. Tested and debugged helper functions in sr_utils.c
2. Implemented and tested handle_arp_reply function
3. Implemented and tested the structure of sr_handlepacket in sr_router.c
4. Implemented and tested handle_ICMP function in sr_router.c

Works we did together:

1. Requirement analysis
2. Using Wireshark to test and debug
3. Implementation of sr_handlepacket function and handle_arp function in sr_router.c
4. Improving code overall
5. Analysing and fixing bugs


Known Bugs/Issues:

1.If the router receives a non-existent destination packet, the router will reply a ICMP packet whose type is 3, and code 0, but the mininet does not show, the wireshark can capture the ICMP packet. I have checked my ICMP packets and sr_solution ICMP packets, they are the same except checksum bits, but my checksum is correct in wireshark.

2. When we call a comment “ client ping -c 3 192.168.2.2” in mininet, the router can forward 3 ICMP packets, after forwarding, it requests a hardware address again after 5 seconds. We have called arpreq_destroy function to destroy the cache. We do not know the reasons of issues.





Code Design:
1.When the router gets packets, we check the ethernet header to determine it is a ip header or arp header(step 2-3).

/*------------receive an arp packet----------------*/
2.If the packet is an arp header, check this packet whether it is correct or not, if it is correct, it will use handle_function to deal this packet.

3.The handle_function determines it is a arp_request packets or arp_reply packets, if it is a request packet, the router should reply a arp packet,
if it is a reply packet, the function inserts the MAC address into arp cache, and sends the packets which did not forward before, and destries these packets.

/*------------receive an ip packet-----------------*/
4.If the packet is a ip packet, we determine it is a ICMP packet or others packet.

5.If it is a ICMP packet, the router should forward this ICMP packet. The function looks up the arp cache to search the correct MAC address,
  if it can be found, the forward this ICMP packet, if it cannot be found, insert this ICMP packet into arp request queue, wait for a MAC address.

6.If it is others packet (TCP/UDP), if the destination of this packet is router, the router will reply ICMP packet. If the destination is not router, the router will forward this packet by handle_IP function.

Main function:

handle_ICMP: Handle a ICMP packet including check TTL and forwarding.

handle_IP:Handle a IP packet including check this packet and forwarding.

Handle_arp: Handle an arp packet, determines it is an arp request or arp reply. If it is a reply, then insert this MAC address into cache and forward the packet in cache. If it is an arp request, reply router’s MAC address.
