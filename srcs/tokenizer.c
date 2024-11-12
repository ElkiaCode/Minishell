/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:23:41 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/12 16:57:15 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void tokenizer(t_tokens *token, char *line, int tokens_size)
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
	while (j < tokens_size)
	{
		printf("Allocating tokens for token[%d] with size %d\n", j, size[j]);
		token[j].tokens = (char **)malloc(sizeof(char *) * (size[j] + 1));
		if (token[j].tokens == NULL)
		{
			fprintf(stderr, "Memory allocation failed\n");
			return;
		}
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
