#include "ft_malcom.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

int is_hex(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) 
		return (1);
	return (-1);
}

void handle_sigint(int sig)
{
    (void)sig;
    printf("\nSIGINT signal received.\nExiting the program...\n");
    check_sigint = 1;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (dst);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

void mac_to_str(unsigned char *mac, char *mac_str)
{
    //bin to str
    snprintf(mac_str, 18, "%02x:%02x:%02x:%02x:%02x:%02x", 
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

size_t	ft_strncpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	while (src[c] != '\0')
		c++;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (c);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

void print_hex(const void *data, size_t size, FILE *output) 
{
    const unsigned char *byte = (const unsigned char *)data;
    for (size_t i = 0; i < size; i++) 
	{
        fprintf(output, "%02x ", byte[i]); // imprime cada byte en formato hexadecimal
        if ((i + 1) % 16 == 0) // salto de linea cada 16 bytes
            fprintf(output, "\n");
    }
    fprintf(output, "\n");
}

void print_help()
{
    printf("Normal usage: ./ft_malcolm <source ip> <source mac address> <target ip> <target mac address>\n");

    printf("Advanced usage: ./ft_malcolm <source ip> <source mac address> <target ip> <target mac address> [FLAGS]\n");

    printf("Flags:\n");
    printf("  -h, --help                Displays this help message.\n");
    printf("  -o, --output <file>       Specifies the output file (default is 'output.txt').\n");
    printf("  -v, --verbose             Shows detailed information for each packet.\n");
    printf("  -s, --silent              Does not show any output to the terminal (only logs if enabled).\n");
    printf("\n");
	exit(0);
}
