/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include <net/if.h>
#include "arp.h"

void process_arping(params_t *params)
{
    int local_socket = create_socket();
    struct sockaddr_ll *arp_sockaddr = create_broadcast_arp_socketaddr(params);
    arp_hdr_t *arp = create_arp_packet(params, local_socket);
    char *packet = create_sendable_packet(arp, arp_sockaddr, params);
    unsigned char *victim_mac_addr = NULL;

    close(local_socket);
    victim_mac_addr = process_arp_spoofing(packet, arp_sockaddr);
    if (victim_mac_addr) {
        print_victim_mac_addr(victim_mac_addr);
        spoofing_loop(params, (char *) victim_mac_addr, arp);
        free(victim_mac_addr);
    }
    delete_arp_packet(arp);
    free(arp_sockaddr);
    free(packet);
    close(local_socket);
}

void process_broadcast_dump(params_t *params)
{
    int local_socket = create_socket();
    struct sockaddr_ll *arp_sockaddr = create_broadcast_arp_socketaddr(params);
    arp_hdr_t *arp = create_arp_packet(params, local_socket);
    char *packet = create_sendable_packet(arp, arp_sockaddr, params);

    dump_broadcast_arp_packet(packet);
    delete_arp_packet(arp);
    free(arp_sockaddr);
    free(packet);
    close(local_socket);
}

int main(int ac, char **av)
{
    params_t *params = parse(ac, av);

    if (params->print_broadcast) {
        process_broadcast_dump(params);
    } else if (params->print_spoof_mac_addr) {

    } else {
        process_arping(params);
    }
    delete_params(params);
    return 0;
}