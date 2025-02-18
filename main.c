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
    data->o = 0;
    data->v = 0;
    data->s = 0;
    data->output = NULL;
    return (data);
}

int main(int argc, char **argv)
{
    if (geteuid() != 0)
    {
        fprintf(stderr, "Failed: This program must be run as root.\n");
        return (-1);
    }
    if (argc == 2 && (ft_strcmp(argv[1], "-h") == 0 || ft_strcmp(argv[1], "--help") == 0))
        print_help();
    signal(SIGINT, handle_sigint);
    if (argc < 5)
    {
        fprintf(stderr, "Usage: %s <source ip> <source mac address> <target ip> <target mac address>\n", argv[0]);
        return (-1);
    }
    if (parse(argv) == -1)
        return (-1);
    t_malcom *data = init_struct(argv);
    if (argc > 5)
        parse_bonus(argc, argv, data);
    listen_arp(data);
    if (check_sigint == 0)
        send_arp(data);
    return (0);
}