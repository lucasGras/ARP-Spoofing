/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include "arp.h"

void delete_arp_packet(arp_hdr_t *arp_hdr)
{
    free(arp_hdr);
}