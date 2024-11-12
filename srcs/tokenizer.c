/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:23:41 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/12 13:45:45 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void tokenizer(t_tokens **token, char *line, int tokens_size)
{
	int		i;
	int		j;
	char	**line_tab;
	int		*size;
	int		n;

	i = 0;
	j = 0;
	n = 0;
	line_tab = split_command(line);
	size = tab_size(line_tab);
	printf("%d\n", j);
	token[j]->tokens = malloc(sizeof(char *) * (size[j] + 1));
	while (line_tab[n] && j < tokens_size)
	{
		token[j]->tokens[i] = ft_strdup(line_tab[n]);
		if (*line_tab[n] == '|')
		{
			token[j]->tokens[i] = NULL;
			j++;
			i = 0;
			printf("%d\n", j);
			token[j]->tokens = malloc(sizeof(char *) * (size[j] + 1));
		}
		i++;
		n++;
	}
	token[j]->tokens[i] = NULL;
	j = 0;
	i = 0;
	while (j < tokens_size)
	{
		printf("%s\n", token[j]->tokens[i]);
		i++;
		if (token[j]->tokens[i] == NULL)
		{
			i = 0;
			j++;
			printf("-----------------\n");
		}
	}
}
