/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include "arp.h"

bool set_arp_source(params_t *params, arp_hdr_t *arp, int socket_fd)
{
    uint8_t *source_mac = NULL;
    char *source_ip = strdup(params->source_ip);
    int status = 0;

    if (!source_ip)
        return false;
    status = inet_pton(AF_INET, source_ip, &arp->source_ip);
    if (status < 0)
        return false;
    source_mac = retrieve_mac_addr(params->interface, socket_fd);
    if (!source_mac)
        return false;
    memcpy(arp->source_mac, source_mac, MACADDR_LEN * sizeof(uint8_t));
    return true;
}

bool set_arp_target(params_t *params, arp_hdr_t *arp)
{
    int status = 0;

    memset(arp->target_mac, 0xff, sizeof(uint8_t) * MACADDR_LEN);
    status = inet_pton(AF_INET, params->dest_ip, &arp->target_ip);
    return (status > 0);
}

arp_hdr_t *create_arp_paquet(params_t *params, int socket_fd)
{
    arp_hdr_t *arp_hdr = malloc(sizeof(*arp_hdr));

    if (!set_arp_source(params, arp_hdr, socket_fd))
        return NULL;
    if (!set_arp_target(params, arp_hdr))
        return NULL;
    arp_hdr->hardware_type = htons(ETH_TYPE);
    arp_hdr->hardware_len = MACADDR_LEN;
    arp_hdr->protocol_type = htons(IPV4_TYPE);
    arp_hdr->protocol_len = IPV4_LEN;
    arp_hdr->opcode = htons(ARP_OPCODE);
    close(socket_fd);
    return arp_hdr;
}

uint8_t *create_sendable_packets(arp_hdr_t *arp_hdr)
{
    uint8_t *packet = malloc(sizeof(uint8_t) * IP_MAXPACKET);

    memcpy(packet, &arp_hdr->target_mac, MACADDR_LEN * sizeof(uint8_t));
    memcpy(packet + MACADDR_LEN, &arp_hdr->source_mac, MACADDR_LEN * sizeof(uint8_t));
    memcpy(packet + ETHHDR_LEN, &arp_hdr, ARPHDR_LEN * sizeof(uint8_t));
    return packet;
}