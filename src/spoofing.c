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

void spoofing_loop(char *victim_addr)
{

}