/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/
#ifndef NWP_MYARPSPOOF_2018_ARP_H
#define NWP_MYARPSPOOF_2018_ARP_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <zconf.h>
#include <stdbool.h>
#include <regex.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>

// -------------------  myARPSpoof Parser
#define IP_REGEX "\\b((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}\\b"
#define MACADDR_REGEX "^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$"

typedef struct params_s {
    char *source_ip;
    char *dest_ip;
    char *interface;
    bool print_broadcast;
    char *print_spoof_mac_addr;
} params_t;

params_t *parse(int ac, char **av);
void delete_params(params_t *params);

// ----------------------- ARP packets
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/ip.h>
#include <netpacket/packet.h>
#include <linux/if_ether.h>

#define ETHHDR_LEN 14
#define IP4HDR_LEN 20
#define ARPHDR_LEN 28
#define ETH_TYPE 1
#define IPV4_TYPE 2048
#define ARP_OPCODE 1

#define MACADDR_LEN 6
#define IPV4_LEN 4
#define PACKET_LEN 64

typedef struct arp_hdr_s {
    uint16_t    hardware_type;
    uint16_t    protocol_type;
    char        hardware_len;
    char        protocol_len;
    uint16_t    opcode;
    char        source_mac[6];
    char        source_ip[4];
    char        target_mac[6];
    char        target_ip[4];
} arp_hdr_t;

arp_hdr_t *create_arp_paquet(params_t *, int);
char *create_sendable_packets(arp_hdr_t *, struct sockaddr_ll *, params_t *);
struct sockaddr_ll *create_arp_socketaddr(params_t *);

// ----------------------- Socket
int create_socket(void);

// ------------------------ Mac
char *retrieve_mac_addr(char *, int);
unsigned char *retrieve_mac_addr_from_frame(char *);
void print_victim_mac_addr(unsigned char *);

#endif //NWP_MYARPSPOOF_2018_ARP_H
