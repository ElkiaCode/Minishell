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

char	**split_command(char *str)
{
	int		i;
	int		j;
	int		n;
	int		wc;
	char	**result;

	i = 0;
	j = 0;
	n = 0;
	wc = word_count(str);
	result = (char **)malloc(sizeof(char *) * (wc + 1));
	while (str[i])
	{
		while (str[i] && (str[i] == ' '))
			i++;
		j = i;
		if (str[i] == '"' || str[i] == '\'')
		{
			i++;
			while (str[i] && (str[i] != '"' && str[i] != '\''))
				i++;
		}
		while (str[i] && (str[i] != ' '))
			i++;
		if (i > j)
		{
			result[n] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			ft_strncpy(result[n++], &str[j], i - j);
		}
	}
	result[n] = NULL;
	return (result);
}
