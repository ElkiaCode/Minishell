/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:23:41 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/19 17:42:13 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokenizer(t_tokens *token, char **line_tab, int tokens_size, int *size)
{
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = 0;
	while (j < tokens_size)
	{
		token[j].tokens = (char **)malloc(sizeof(char *) * (size[j] + 1));
		token[j].tokens[size[j]] = NULL;
		j++;
	}
	j = 0;
	while (line_tab[n] && j < tokens_size)
	{
		if (*line_tab[n] == '|')
		{
			j++;
			i = 0;
			n++;
		}
		token[j].tokens[i] = ft_strdup(line_tab[n]);
		i++;
		n++;
	}
	j = 0;
	i = 0;
	while (j < tokens_size)
	{
		printf("Group %d:\n", j);
		i = 0;
		if (token[j].tokens == NULL) {
			printf("  token[%d].tokens is NULL, skipping\n", j);
			j++;
			continue;
		}
		while (token[j].tokens[i] != NULL)
		{
			if (token[j].tokens[i] != NULL)
				printf("  %s\n", token[j].tokens[i]);
			else
				printf("  token[%d].tokens[%d] is NULL\n", j, i);
			i++;
		}
		printf("-----------------\n");
		j++;
	}
}
