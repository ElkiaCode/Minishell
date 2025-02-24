/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:33:32 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:33:33 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokenizer(t_tokens *token, char **line_tab, int tokens_size, int *size)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	token = malloc_token(token, size, tokens_size);
	free(size);
	while (line_tab[n] && j < tokens_size)
	{
		if (*line_tab[n] == '|')
		{
			token[j].tokens[i] = NULL;
			j++;
			i = 0;
			n++;
		}
		token[j].tokens[i] = ft_strdup(line_tab[n]);
		i++;
		n++;
	}
	free_tab(line_tab);
	token[j].tokens[i] = NULL;
}
