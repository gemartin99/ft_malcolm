#include "ft_malcom.h"

int listen_arp(t_malcom *data)
{
    int sockfd;
    unsigned char buffer[BUFFER_SIZE];
    struct sockaddr_ll addr;
    socklen_t addr_len = sizeof(addr);
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

    ifa = ifaddr;

    while (ifa != NULL)
    {
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_PACKET) //solo interfaces fisicas. No 'lo' y variantes.
        {
            unsigned int flags = ifa->ifa_flags;

            if ((flags & IFF_UP) && (flags & IFF_RUNNING) &&
                (flags & IFF_BROADCAST || flags & IFF_MULTICAST)) //interfaz activada, funcionando y permitiendo la comunicacion con otras maquinas
            {
                strncpy(data->iface, ifa->ifa_name, IFNAMSIZ);
                break;
            }
        }
        ifa = ifa->ifa_next;
    }

    freeifaddrs(ifaddr);
    if (data->iface[0] != '\0')
        printf("Found available interface: %s\n", data->iface);
    else
    {
        fprintf(stderr, "Failed to obtain available network interface\n");
        exit(1);
    }
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
    printf("Waiting for ARP request for %s on network interface %s\n", data->s_ip, data->iface);
    while (check_sigint == 0)
    {
        fd_set fds;
        struct timeval timeout;

        FD_ZERO(&fds);
        FD_SET(sockfd, &fds);

        timeout.tv_sec = 0;
        timeout.tv_usec = 500000; //500ms

        int ret = select(sockfd + 1, &fds, NULL, NULL, &timeout);
        if (ret < 0)
        {
            if (check_sigint == 0)
                fprintf(stderr, "Failed to monitor socket\n");
            close(sockfd);
            exit(1);
        }
        else if (ret == 0)
            continue; //timeout

        int nbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0,(struct sockaddr *)&addr, &addr_len);
        if (nbytes < 0)
        {
            fprintf(stderr, "Failed to receive the packet\n");
            continue;
        }

        //extraemos la cabecera ethernet del paquete
        struct ethhdr *eth_hdr = (struct ethhdr *)buffer;

        if (ntohs(eth_hdr->h_proto) != ETH_P_ARP)
            continue; //si no es un paquete ARP se ignora

        //extraemos cabecera arp del paquete    
        struct ether_arp *arp_hdr = (struct ether_arp *)(buffer + sizeof(struct ethhdr));

        
        if (ntohs(arp_hdr->ea_hdr.ar_op) != ARPOP_REQUEST)
            continue; //si no es solicitud arp se ignora

        //extraemos la direccion ip destino
        char arp_tpa[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, arp_hdr->arp_tpa, arp_tpa, sizeof(arp_tpa));//convertir ip binario to str


        if (strcmp(arp_tpa, data->s_ip) == 0)
        {
            printf("Received ARP request from %s\n", data->s_ip);
            break;
        }

    }
    close(sockfd);
    return (0);
}





