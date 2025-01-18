#include "../includes/minishell.h"

char	*ft_strcat(char *dst, const char *src)
{
	int	i;
	int	dst_len;

	i = 0;
	dst_len = 0;
	while (dst[dst_len] != '\0')
		dst_len++;
	while (src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst);
}
