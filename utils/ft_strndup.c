#include "../includes/minishell.h"

char	*ft_strndup(const char *src, int n)
{
	char	*dest;
	int	i;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}