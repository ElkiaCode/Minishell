#include "../includes/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*end;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	end = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!end)
		return (NULL);
	while (s1[i])
	{
		end[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		end[i + j] = s2[j];
		j++;
	}
	end[i + j] = '\0';
	return (end);
}