/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include "arp.h"

void dump_broadcast_arp_packet(char *packet, int i)
{
    while (i < 42) {
        if ((packet[i] & 0xff) >= 0 && (packet[i] & 0xff) <= 8)
            printf("0");
        printf("%x", packet[i] & 0xff);
        if (i < 41)
            printf(" ");
        i++;
    }
    printf("\n");
}

void dump_broadcast_spoof_packet(char *packet, char *mac_addr)
{
    int j = 0;
    int count = 0;

    while (mac_addr[j]) {
        if (count == 2) {
            count = 0;
            j++;
            printf(" ");
        }
        printf("%c", mac_addr[j]);
        count ++;
        j++;
    }
    printf(" ");
    dump_broadcast_arp_packet(packet, 6);
}