/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:23:41 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/25 09:10:01 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

const char	*tokens_strings[] = {
	[T_CMD] = "T_CMD",
	[T_ARG] = "T_ARG",
	[T_RLESS] = "T_RLESS",
	[T_RGREAT] = "T_RGREAT",
	[T_DLESS] = "T_DLESS",
	[T_DGREAT] = "T_DGREAT",
	[T_OD_FILE] = "T_OD_FILE",
	[T_I_FILE] = "T_I_FILE",
	[T_AND] = "T_AND",
	[T_OR_FILE] = "T_OR_FILE",
	[T_NL] = "T_NL",
	[T_ERR] = "T_ERR",
	[T_HEREDOC] = "T_HEREDOC",
	[T_VAR] = "T_VAR",
	[T_S_QUOTE] = "T_S_QUOTE",
	[T_D_QUOTE] = "T_D_QUOTE",
};

void	tokenizer(t_tokens *token, char **line_tab, int tokens_size, int *size)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	token = malloc_token(token, size, tokens_size);
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
	token = get_token_type(token, tokens_size);
	token = search_for_args(token, tokens_size);
	token = main_expand(token, tokens_size);
	j = 0;
	i = 0;
	while (j < tokens_size)
	{
		printf("Group %d:\n", j);
		i = 0;
		if (token[j].tokens == NULL)
		{
			printf("  token[%d].tokens is NULL, skipping\n", j);
			j++;
			continue ;
		}
		while (token[j].tokens[i] != NULL)
		{
			if (token[j].tokens[i] != NULL)
			{
				printf("  %s\n", tokens_strings[token[j].type[i]]);
				printf("  %s\n", token[j].tokens[i]);
			}
			else
				printf("  token[%d].tokens[%d] is NULL\n", j, i);
			i++;
		}
		printf("-----------------\n");
		j++;
	}
}
