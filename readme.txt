

     Group Members: names and usernames of each member,
     Work Division: who implemented/tested which part (we reserve the right to check your claim),
     Known Bugs/Issues: all bugs or issues that you know of in your code, and
     Code Design: Briefly describe the design of your code and the data structures implemented.


Group Members:
Member1: Yang Yang, yya123@sfu.ca
Member2: Site Li, sitel@sfu.ca

Work Division:

Yang Yang:

Finished helper functions, handle_IP function, handle_arp_request function, and debug.

Mainly write codes.

Site Li:

Finished handle_arp_reply function, the structure of handle_packet, handle_ICMP function, and debug.

Mainly test and debug.



Known Bugs/Issues:





Code Design:
1.When the router gets packets, firstly we check the ethernet header to determine it is a ip header or arp header(step 2-3).

/*------------receive a arp packet----------------*/
2.If the packet is a arp header, firstly check this packet whether it is correct or not, if it is correct, then using handle_function to deal this packet.

3.The handle_function firstly determines it is a arp_request packet or arp_reply packet, if it is a request packet, the router should reply a arp packet,
if it is a reply packet, the function inserts the MAC address into arp cache, and send the packets which did not forward before, and destroy these packets.

/*------------receive a ip packet-----------------*/
4.If the packet is a ip packet, we determine it is a ICMP packet or others packet.

5.If it is a ICMP packet, the router should forward this ICMP packet. The function looks up the arp cache to search the correct MAC address,
  if it can be found, the forward this ICMP packet, if it cannot be found, insert this ICMP packet into arp request queue, wait for a MAC address.

6.
