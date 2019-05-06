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

// myARPSpoof Parser
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

#endif //NWP_MYARPSPOOF_2018_ARP_H
