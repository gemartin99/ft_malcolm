int valid_ip(char *ip)
{

}

int valid_hostname(char *hostname)
{

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
}