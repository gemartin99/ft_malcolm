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

int valid_mac(char *s)
{
    if (ft_strlen(s) != 17)
        return (-1);
    int i = 0;
    while (s[i])
    {
        if (i % 3 == 2 && s[i] != ':')
            return (-1);
        else if (i % 3 != 2 && is_hex(s[i]) == -1)
            return (-1);
        i++;
    }
    return (0);
}

int parse(char **argv)
{
    if (valid_ip(argv[1]) != 1 && valid_hostname(argv[1]) != 0)
    {
        fprintf(stderr, "%s: unknown host or invalid source IP address: %s\n", argv[0], argv[1]);
        return(-1);
    }
    if (valid_ip(argv[3]) != 1 && valid_hostname(argv[3]) != 0)
    {
        fprintf(stderr, "%s: unknown host or invalid target IP address: %s\n", argv[0], argv[3]);
        return(-1);
    }
    if (valid_mac(argv[2]) != 0)
    {
        fprintf(stderr, "%s:  invalid mac address: (%s)\n", argv[0], argv[2]);
        return(-1);
    }
    if (valid_mac(argv[4]) != 0)
    {
        fprintf(stderr, "%s:  invalid mac address: (%s)\n", argv[0], argv[4]);
        return(-1);
    }
    return (0);
}