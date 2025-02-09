#include "ft_malcom.h"

int listen_arp(t_malcom *data)
{
    int sockfd;
    //unsigned char buffer[BUFFER_SIZE];
    //struct sockaddr_ll addr;
    //socklen_t addr_len = sizeof(addr);
    struct ifaddrs *ifaddr, *ifa;

    if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0)
    {
        fprintf(stderr, "Failed to create RAW socket\n");
        exit(1);
    }

    if (getifaddrs(&ifaddr) == -1)
    {
        fprintf(stderr, "Failed to listing network interfaces\n");
        exit(1);
    }

    char selected_iface[IFNAMSIZ] = {0};
    ifa = ifaddr;

    while (ifa != NULL) {
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_PACKET) //solo interfaces fisicas. No 'lo' y variantes.
        {
            unsigned int flags = ifa->ifa_flags;

            if ((flags & IFF_UP) && (flags & IFF_RUNNING) &&
                (flags & IFF_BROADCAST || flags & IFF_MULTICAST)) //interfaz activada, funcionando y permitiendo la comunicacion con otras maquinas
            {
                strncpy(selected_iface, ifa->ifa_name, IFNAMSIZ);
                break;
            }
        }
        ifa = ifa->ifa_next;
    }

    freeifaddrs(ifaddr);
    printf("Found available interface: %s\n", selected_iface);
    /*
    MANERA DE UTILIZAR INTERFAZ HARDCODEADA
    int interface_index = if_nametoindex("eth0");
    if (interface_index == 0)
    {
        fprintf(stderr, "Failed to obtain the index of the interface eth0\n");
        close(sockfd);
        exit(1);
    }
    else
        printf("Found available interface: eth0\n");*/
    (void)data;
    return (0);
}





