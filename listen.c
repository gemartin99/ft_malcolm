#include "ft_malcom.h"

int listen_arp(t_malcom *data)
{
    int sockfd;
    //unsigned char buffer[BUFFER_SIZE];
    //struct sockaddr_ll addr;
    //socklen_t addr_len = sizeof(addr);

    if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0)
    {
        fprintf(stderr, "Failed to create RAW socket\n");
        exit(1);
    }

    int interface_index = if_nametoindex("eth0");
    if (interface_index == 0)
    {
        fprintf(stderr, "Failed to obtain the index of the interface eth0\n");
        close(sockfd);
        exit(1);
    }
    else
        printf("Found available interface: eth0\n");
    data->s_ip = "nada";
    return (0);
}




