/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:40:41 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:40:42 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	word_count(char *str)
{
	int	i;
	int	wc;

	wc = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' '))
			i++;
		if (str[i])
			wc++;
		if (str[i] == '"' || str[i] == '\'')
		{
			i++;
			while (str[i] && (str[i] != '"' && str[i] != '\''))
				i++;
		}
		while (str[i] && (str[i] != ' '))
			i++;
	}
	return (wc);
}

static void	handle_word(char *str, char **result, int *i, int *n)
{
	int	j;

	while (str[*i] && str[*i] == ' ')
		(*i)++;
	j = *i;
	if (str[*i] == '"' || str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != str[j])
			(*i)++;
		(*i)++;
	}
	else
	{
		while (str[*i] && str[*i] != ' ')
			(*i)++;
	}
	if (*i > j)
	{
		result[*n] = (char *)malloc(sizeof(char) * ((*i - j) + 1));
		ft_strncpy(result[*n], &str[j], *i - j);
		result[*n][*i - j] = '\0';
		(*n)++;
	}
}

char	**split_command(char *str)
{
	int		i;
	int		n;
	int		wc;
	char	**result;

	i = 0;
	n = 0;
	wc = word_count(str);
	result = (char **)malloc(sizeof(char *) * (wc + 2));
	if (!result)
		return (NULL);
	while (str[i])
		handle_word(str, result, &i, &n);
	result[n] = NULL;
	return (result);
}
