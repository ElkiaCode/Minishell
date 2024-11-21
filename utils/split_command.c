/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:53:38 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/15 16:29:25 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	word_count(char *str)
{
	int i;
	int wc;

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
	int i;
	int j;
	int n;
	int wc;
	char **result;

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
