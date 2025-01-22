#ifndef FT_MALCOM_H
# define FT_MALCOM_H

typedef struct s_malcom
{
    char *s_ip;
    char *s_mac;
    char *t_ip;
    char *t_mac;
} t_malcom;

void	ft_bzero(void *s, size_t n);

#endif