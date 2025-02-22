#include "ft_malcolm.h"

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

//parse bonus

int is_writable(const char *filename, t_malcolm *data)
{
    if (!filename)
        return (-1);
    if (access(filename, F_OK) == -1)
    {
        if (!data->s)
            fprintf(stderr, "Failed to access to file %s\n", filename);
        exit(1);
    }
    if (access(filename, W_OK) == -1)
    {
        if (!data->s)
            fprintf(stderr, "Failed to write in file %s\n", filename);
        exit(1);
    }
    return 0;//el archivo existe y es escribible
}

int parse_bonus(int argc, char **argv, t_malcolm *data)
{
    int i = 5;
    while (i < argc && argv[i])
    {
        if ((ft_strcmp(argv[i], "-v") == 0 || ft_strcmp(argv[i], "--verbose") == 0) && data->s == 0)
            data->v = 1;
        else if (ft_strcmp(argv[i], "-o") == 0 || ft_strcmp(argv[i], "--output") == 0)
        {
            if (i + 1 <= argc && is_writable(argv[i + 1], data) != -1)
            {
                data->output = argv[i + 1];
                i++;
            }
            else 
                data->output = "output.txt";
            data->o = 1;
        }
        else if (ft_strcmp(argv[i], "-t") == 0 || ft_strcmp(argv[i], "--timeout") == 0)
        {
            if (i + 1 <= argc)
            {
                if (argv[i + 1])
                    data->timeout = atoi(argv[i + 1]);
                else
                    data->timeout = 15;
                if (data->timeout <= 0)
                {
                    if (!data->s)
                        printf("Invalid timeout. Use %s --help\n", argv[0]);
                    exit (1);
                }
                i++;
            }
            else 
                data->timeout = 15;
        }
        else if ((ft_strcmp(argv[i], "-s") == 0 || ft_strcmp(argv[i], "--silent") == 0) && data->v == 0)
            data->s = 1;
        else if (ft_strcmp(argv[i], "-h") == 0 || ft_strcmp(argv[i], "--help") == 0)
            print_help();
        else
        {
            printf("Invalid flag. Use %s --help\n", argv[0]);
            exit (1);
        }
        i++;
    }
    return (0);
}