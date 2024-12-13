#include "../includes/minishell.h"

static int	is_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i] || c == '\0')
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_countwords(char *str, char *sep)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!is_sep(str[i], sep))
		{
			count++;
			while (str[i] && !is_sep(str[i], sep))
				i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

static void	make_split(char **strs, char *str, char *charset, size_t *word_idx)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		if (!is_sep(str[i], charset))
		{
			j = 0;
			while (str[i + j] && !is_sep(str[i + j], charset))
				j++;
			strs[*word_idx] = malloc(sizeof(char) * (j + 1));
			if (!strs[*word_idx])
			{
				free_tab(strs);
				return ;
			}
			ft_strncpy(strs[*word_idx], &str[i], j);
			strs[*word_idx][j] = '\0';
			i += j;
		}
		else
		{
			strs[*word_idx] = malloc(sizeof(char) * (2));
			if (!strs[*word_idx])
			{
				free_tab(strs);
				return ;
			}
			strs[*word_idx][0] = str[i];
			strs[*word_idx][1] = '\0';
			i++;
		}
		(*word_idx)++;
	}
}

char	**ft_split(char **input, char *charset)
{
	char	**strs;
	size_t	total_words;
	size_t	word_idx;
	size_t	i;

	i = 0;
	word_idx = 0;
	total_words = 0;
	while (input[i])
		total_words += ft_countwords(input[i++], charset);
	strs = malloc(sizeof(char *) * (total_words + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (input[i])
	{
		make_split(strs, input[i], charset, &word_idx);
		i++;
	}
	strs[total_words] = NULL;
	return (strs);
}
