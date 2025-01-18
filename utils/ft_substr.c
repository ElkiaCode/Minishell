#include "../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	char	*str;

	j = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (len < (ft_strlen(s) - start))
		str = malloc(sizeof(char) * (len + 1));
	else
		str = malloc(sizeof(char) * ((ft_strlen(s) - start) + 1));
	if (!str)
		return (NULL);
	while (s[start] && len)
	{
		str[j] = s[start];
		start++;
		j++;
		len--;
	}
	str[j] = 0;
	return (str);
}
