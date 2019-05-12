/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include <net/if.h>
#include "arp.h"

int main(int ac, char **av)
{
    params_t *params = parse(ac, av);
    int local_socket = create_socket();
    struct sockaddr_ll *arp_sockaddr = create_arp_socketaddr(params);
    arp_hdr_t *arp = create_arp_packet(params, local_socket);
    char *packet = create_sendable_packet(arp, arp_sockaddr, params);
    unsigned char *victim_mac_addr = NULL;

    close(local_socket);
    victim_mac_addr = process_arp_spoofing(packet, arp_sockaddr);
    if (victim_mac_addr) {
        print_victim_mac_addr(victim_mac_addr);
        free(victim_mac_addr);
    }
    delete_params(params);
    delete_arp_packet(arp);
    free(arp_sockaddr);
    free(packet);
    return 0;
}