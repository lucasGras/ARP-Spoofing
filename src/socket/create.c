/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include "arp.h"

int create_socket(void)
{
    int socket_fd = 0;

    socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (socket_fd < 0) {
        printf("Error while creating socket\n");
        exit(84);
    }
    return socket_fd;
}