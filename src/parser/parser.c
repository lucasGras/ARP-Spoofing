/*
** EPITECH PROJECT, 2022
** NWP_myarpspoof_2018
** File description:
** Created by lucasg,
*/

#include "arp.h"

bool check_typo(char *str, char *regex)
{
    regex_t regex_ip;
    int state_ip = regcomp(&regex_ip, regex, REG_EXTENDED | REG_NOSUB);

    if (state_ip)
        return false;
    state_ip = regexec(&regex_ip, str, 0, NULL, 0);
    regfree(&regex_ip);
    return (state_ip == 0);
}

params_t *parse_arguments(int ac, char **av)
{
    params_t *params = malloc(sizeof(*params));

    params->print_broadcast = false;
    params->print_spoof_mac_addr = NULL;
    if (ac >= 5) {
        if (strcmp(av[4], "--printBroadcast") == 0 && ac == 5)
            params->print_broadcast = true;
        else if (strcmp(av[4], "--printSpoof") == 0 && ac == 6
        && check_typo(av[5], MACADDR_REGEX))
            params->print_spoof_mac_addr = strdup(av[5]);
        else
            return NULL;
    }
    params->source_ip = strdup(av[1]);
    params->dest_ip = strdup(av[2]);
    params->interface = strdup(av[3]);
    return params;
}

params_t *parse(int ac, char **av)
{
    params_t *params = NULL;

    if (ac < 4 || ac > 6) {
        printf("Not enough arguments\n");
        exit(84);
    }
    if (!check_typo(av[1], IP_REGEX) || !check_typo(av[2], IP_REGEX)) {
        printf("Invalid IP addresses\n");
        exit(84);
    }
    params = parse_arguments(ac, av);
    if (!params) {
        printf("Arguments error\n");
        exit(84);
    }
    return params;
}