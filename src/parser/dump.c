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
    (void)mac_addr;
    dump_broadcast_arp_packet(packet, 0);
}

int hexadecimal_to_decimal(int x)
{
    int decimal_number = 0;
    int remainder = 0;
    int count = 0;

    while (x > 0) {
        remainder = x % 10;
        decimal_number = decimal_number + remainder * pow(16, count);
        x = x / 10;
        count++;
    }
    return decimal_number;
}