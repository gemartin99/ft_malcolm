#include "ft_malcom.h"

t_malcom *init_struct(void)
{
    t_malcom *data = (t_malcom *)malloc(sizeof(t_malcom));
    if (!data)
        exit (-1);
    ft_bzero(data, sizeof(*data));
    return (data);
}

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: ./%s <source ip> <source mac address> <target ip> <target mac address>\n", argv[0]);
        exit (-1);
    }
    t_malcom *data = init_struct();
}