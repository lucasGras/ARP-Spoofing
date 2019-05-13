/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include "arp.h"

void dump_broadcast_arp_packet(char *packet)
{
    int i = 0;

    while (i < PACKET_LEN - 1) {
        printf("%02x ", packet[i]);
        i++;
    }
    i++;
    printf("%2x\n", packet[i]);
}