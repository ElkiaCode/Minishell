#include "../includes/minishell.h"

int	char_is_sep(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (c == charset[i])
			return (1);
	if (!c)
		return (1);
	return (0);
}

int	ft_countwords(char *str, char *sep)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (char_is_sep(str[i + 1], sep) && !char_is_sep(str[i], sep))
			count++;
	return (count);
}

void	write_word(char *dest, char *from, char *charset)
{
	int	i;

	i = -1;
	while (!char_is_sep(from[++i], charset))
		dest[i] = from[i];
	dest[i] = '\0';
}

void	write_split(char **strs, char *str, char *charset)
{
	int	i;
	int	j;
	int	word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (char_is_sep(str[i], charset))
			i++;
		else
		{
			j = 0;
			while (!char_is_sep(str[i + j], charset))
				j++;
			strs[word] = (char *)malloc(sizeof(char) * (j + 1));
			if (!strs[word])
				return ;
			write_word(strs[word++], str + i, charset);
			i += j;
		}
	}
}

char	**ft_split(char *str, char *charset)
{
	char **strs;

	strs = malloc(sizeof(char *) * ft_countwords(str, charset) + 1);
	if (!strs)
		return (NULL);
	strs[ft_countwords(str, charset)] = 0;
	write_split(strs, str, charset);
	return (strs);
}
