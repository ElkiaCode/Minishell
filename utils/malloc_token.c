/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:40:30 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:40:31 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tokens	*malloc_token(t_tokens *token, int *size, int tokens_size)
{
	int	j;
	int	i;

	j = 0;
	while (j < tokens_size)
	{
		i = 0;
		token[j].tokens = (char **)malloc(sizeof(char *) * (size[j] + 1));
		token[j].type = malloc(sizeof(int) * (size[j] + 1));
		token[j].token_size = size[j];
		while (i <= size[j])
		{
			token[j].type[i] = 0;
			i++;
		}
		token[j].tokens[size[j]] = NULL;
		j++;
	}
	return (token);
}
