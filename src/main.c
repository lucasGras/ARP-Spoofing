/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include "arp.h"

int main(int ac, char **av)
{
    params_t *params = parse(ac, av);

    delete_params(params);
    return 0;
}