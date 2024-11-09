/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:46:35 by lpolizzi          #+#    #+#             */
/*   Updated: 2024/09/26 14:15:52 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	char_is_separator(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

int	ft_countwords(char *str, char *sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (char_is_separator(str[i + 1], sep) == 1
			&& char_is_separator(str[i], sep) == 0)
			count++;
		i++;
	}
	return (count);
}

void	write_word(char *dest, char *from, char *charset)
{
	int	i;

	i = 0;
	while (char_is_separator(from[i], charset) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

void	write_split(char **strs, char *str, char *charset)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (char_is_separator(str[i], charset) == 1)
			i++;
		else
		{
			j = 0;
			while (char_is_separator(str[i + j], charset) == 0)
				j++;
			strs[word] = (char *) malloc(sizeof(char) * (j + 1));
			if (!strs[word])
				return ;
			write_word(strs[word], str + i, charset);
			i += j;
			word++;
		}
	}
}

char	**ft_split(char *str, char *charset)
{
	char	**strs;
	int		i;

	i = 0;
	strs = malloc(sizeof(char *) * ft_countwords(str, charset) + 1);
	if (!strs)
		return (NULL);
	strs[ft_countwords(str, charset)] = 0;
	write_split(strs, str, charset);
	return (strs);
}
