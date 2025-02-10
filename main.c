#include "ft_malcom.h"

int check_sigint = 0;

t_malcom *init_struct(char **argv)
{
    t_malcom *data = (t_malcom *)malloc(sizeof(t_malcom));
    if (!data)
        exit(1);
    ft_bzero(data, sizeof(*data));
    data->s_ip = argv[1];
    data->s_mac = argv[2];
    data->t_ip = argv[3];
    data->t_mac = argv[4];
    return (data);
}

int main(int argc, char **argv)
{
    signal(SIGINT, handle_sigint);
    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s <source ip> <source mac address> <target ip> <target mac address>\n", argv[0]);
        return (-1);
    }
    if (parse(argv) == -1)
        return (-1);
    t_malcom *data = init_struct(argv);
    listen_arp(data);
    if (check_sigint == 0)
        send_arp(data);
    return (0);
}