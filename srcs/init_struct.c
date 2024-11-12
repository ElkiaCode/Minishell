/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:37:13 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/12 13:45:09 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_tokens(t_tokens *token, int tokens_size)
{
	int i;

	i = 0;
	while (i < tokens_size)
	{
		token[i].tokens = NULL;
		token[i].size = 0;
		i++;
	}
}

void	init_struct(t_global **global, int tokens_size)
{
	*global = malloc(sizeof(t_global));
	if (*global == NULL)
		return;
	(* global)->token = malloc(sizeof(t_tokens) * (tokens_size));
	if ((*global)->token == NULL)
	{
		free(*global);
		return;
	}	
	init_tokens((* global)->token, tokens_size);
}
