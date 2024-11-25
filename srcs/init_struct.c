/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:37:13 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/25 08:05:19 by cparodi          ###   ########.fr       */
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
		token[i].type = NULL;
		i++;
	}
}

int	init_struct(t_global **global, int tokens_size)
{
	*global = malloc(sizeof(t_global));
	if (*global == NULL)
		return (0);
	(*global)->cmd = readline("minishell> ");
	if (ft_strncmp((*global)->cmd, "exit", 4) == 0)
	{
		rl_clear_history();
		exit(EXIT_SUCCESS);
	}
	tokens_size = pipe_nb((*global)->cmd);
	(* global)->token = malloc(sizeof(t_tokens) * (tokens_size));
	if ((*global)->token == NULL)
	{
		free(*global);
		return (0);
	}	
	init_tokens((* global)->token, tokens_size);
	add_history((*global)->cmd);
	return (tokens_size);
}
