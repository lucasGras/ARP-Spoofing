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

    source_mac = retrieve_mac_addr(params->interface, socket_fd);
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
    arp_hdr->opcode = htons(ARP_OPCODE);
    return arp_hdr;
}

struct sockaddr_ll *create_arp_socketaddr(params_t *params)
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

char *create_sendable_packet(arp_hdr_t *arp_hdr,
    struct sockaddr_ll *arp_sockaddr, params_t *params)
{
    char *packet = malloc(sizeof(char) * PACKET_LEN);
    struct ethhdr *eth_header = (struct ethhdr *)packet;
    arp_hdr_t *arp_header = (arp_hdr_t *)(packet + ETHHDR_LEN);
    uint32_t target_ip = inet_addr(params->dest_ip);
    uint32_t source_ip = inet_addr(params->source_ip);

    memset(eth_header->h_dest, 0xff, MACADDR_LEN);
    memset(arp_header->target_mac, 0x00, MACADDR_LEN);
    memcpy(eth_header->h_source, arp_hdr->source_mac, MACADDR_LEN);
    memcpy(arp_header->source_mac, arp_hdr->source_mac, MACADDR_LEN);
    memcpy(arp_sockaddr->sll_addr, arp_hdr->source_mac, MACADDR_LEN);
    eth_header->h_proto = htons(ETH_P_ARP);
    arp_header->hardware_type = arp_hdr->hardware_type;
    arp_header->hardware_len = arp_hdr->hardware_len;
    arp_header->protocol_type = arp_hdr->protocol_type;
    arp_header->protocol_len = arp_hdr->protocol_len;
    arp_header->opcode = arp_hdr->opcode;
    memcpy(arp_header->source_ip, &source_ip, sizeof(uint32_t));
    memcpy(arp_header->target_ip, &target_ip, sizeof(uint32_t));
    return packet;
}