/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include <net/if.h>
#include "arp.h"

char *retrieve_mac_addr_as_sudo(char *interface, int socket_fd)
{
    struct ifreq ifr;
    char *mac_addr = malloc(sizeof(char) * MACADDR_LEN);

    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, interface);
    if (ioctl(socket_fd, SIOCGIFHWADDR, &ifr) < 0)
       return NULL;
    memcpy(mac_addr, ifr.ifr_hwaddr.sa_data, sizeof(uint8_t) * MACADDR_LEN);
    return mac_addr;
}

char *retrieve_mac_addr_as_user(char *interface)
{
    struct ifreq ifr;
    char *mac_addr = malloc(sizeof(char) * MACADDR_LEN);
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, interface);
    if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0)
        return NULL;
    memcpy(mac_addr, ifr.ifr_hwaddr.sa_data, sizeof(uint8_t) * MACADDR_LEN);
    return mac_addr;
}

unsigned char *retrieve_mac_addr_from_frame(char *frame)
{
    struct ethhdr *eth_hdr = (struct ethhdr *) frame;
    arp_hdr_t *arp_hdr = (arp_hdr_t *) (frame + ETHHDR_LEN);
    unsigned char *mac = malloc(sizeof(char) * MACADDR_LEN);

    if (ntohs(eth_hdr->h_proto) != 0x0806
    || ntohs(arp_hdr->opcode) != 0x02)
        return NULL;
    memcpy(mac, eth_hdr->h_source, MACADDR_LEN);
    return mac;
}

void print_victim_mac_addr(unsigned char *mac)
{
    int i = 0;

    printf("Found victim’s MAC address: \'");
    for (i = 0; i < MACADDR_LEN - 1; i++) {
        printf("%02X:", mac[i]);
    }
    printf("%02X\'\n", mac[i]);
}