#include "ft_malcom.h"

int send_arp(t_malcom *data)
{
    int sockfd;
    int if_index;
    struct arp_packet packet;
    struct sockaddr_ll sock_addr;

    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sockfd < 0)
    {
        fprintf(stderr, "Failed to create RAW socket\n");
        exit(1);
    }
    if_index = if_nametoindex(data->iface);
    if (if_index == 0)
    {
        fprintf(stderr, "Failed to obtain index of the network interface: %s\n", data->iface);
        exit(1);
    }
    (void)packet;
    (void)sock_addr;
    return (0);
}