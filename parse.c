#include "ft_malcom.h"

int valid_ip(char *ip)
{
    struct sockaddr_in sa;

    if (inet_pton(AF_INET, ip, &(sa.sin_addr)) == 1)
        return 1;
    return 0;
}

int valid_hostname(char *hostname)
{
    struct hostent *_host = gethostbyname(hostname);

    if (_host != NULL)
        return 0;
    return 1;
}

int parse(char **argv, t_malcom *data)
{
    if (valid_ip(argv[1]) != 1 && valid_hostname(argv[1]) != 0)
    {
        fprintf(stderr, "%s: unknown host or invalid source IP address: %s\n", argv[0], argv[1]);
        exit(-1);
    }
    if (valid_ip(argv[3]) != 1 && valid_hostname(argv[3]) != 0)
    {
        fprintf(stderr, "%s: unknown host or invalid target IP address: %s\n", argv[0], argv[3]);
        exit(-1);
    }
    (void)data;
    return (0);
}