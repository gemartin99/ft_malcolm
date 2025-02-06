#ifndef FT_MALCOM_H
# define FT_MALCOM_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

typedef struct s_malcom
{
    char *s_ip;
    char *s_mac;
    char *t_ip;
    char *t_mac;
} t_malcom;

void	ft_bzero(void *s, size_t n);
int     parse(char **argv, t_malcom *data);
int     is_hex(char c);
size_t	ft_strlen(const char *s);

#endif