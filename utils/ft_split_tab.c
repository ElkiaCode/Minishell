/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:39:55 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:39:57 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_countwords(char *str, char *sep)
{
	size_t	i;
	size_t	count;
	char quote;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!is_sep(str[i], sep))
		{
			count++;
			while (str[i] && !is_sep(str[i], sep))
			{
				if (str[i] == '"' || str[i] == '\'')
				{
					quote = str[i];
					i++;
					while (str[i] && str[i] != quote)
						i++;
					if (str[i] == quote)
						i++;
				}
				if (str[i])
				i++;
			}
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static void	handle_word(char **strs, char *str, size_t *word_idx, int *i)
{
	int	len;
	char temp;
	
	len = 0;
	while (str[*i + len] && !is_sep(str[*i + len], " "))
	{
		if (str[*i + len] == '"' || str[*i + len] == '\'')
		{
			temp = str[*i + len];
			len++;
			while (str[*i + len] && str[*i + len] != temp)
				len++;
		}
		if (str[*i + len])
			len++;
	}
	strs[*word_idx] = malloc(sizeof(char) * (len + 1));
	if (!strs[*word_idx])
	{
		free_tab(strs);
		return ;
	}
	ft_strncpy(strs[*word_idx], &str[*i], len);
	strs[*word_idx][len] = '\0';
	*i += len;
	(*word_idx)++;
}

static void	make_split(char **strs, char *str, char *charset, size_t *word_idx)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!is_sep(str[i], charset))
			handle_word(strs, str, word_idx, &i);
		else
		{
			strs[*word_idx] = malloc(sizeof(char) * 2);
			if (!strs[*word_idx])
			{
				free_tab(strs);
				return ;
			}
			strs[*word_idx][0] = str[i];
			strs[*word_idx][1] = '\0';
			i++;
			(*word_idx)++;
		}
	}
}

char	**ft_split_tab(char **input, char *charset)
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
	free_tab(input);
	return (strs);
}
