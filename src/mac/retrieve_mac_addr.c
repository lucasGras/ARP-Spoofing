/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include <net/if.h>
#include "arp.h"

uint8_t *retrieve_mac_addr(char *interface, int socket_fd)
{
    struct ifreq ifr;
    uint8_t *mac_addr = malloc(sizeof(uint8_t) * MACADDR_LEN);

    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_ifrn.ifrn_name, interface);
    if (ioctl(socket_fd, SIOCGIFHWADDR, &ifr) < 0)
        return NULL;
    memcpy(mac_addr, ifr.ifr_hwaddr.sa_data, sizeof(uint8_t) * MACADDR_LEN);
    return mac_addr;
}