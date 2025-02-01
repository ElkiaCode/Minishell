/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:34:09 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:34:23 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_tokens(t_tokens *token, int tokens_size)
{
	int	i;

	i = 0;
	while (i < (tokens_size + 1))
	{
		token[i].tokens = NULL;
		token[i].type = NULL;
		token[i].token_size = 0;
		i++;
	}
}

void	make_struct_null(t_global *global)
{
	global->env = NULL;
	global->status = 0;
	global->env_tab = NULL;
	global->isolate_cmd = NULL;
	global->isolate_infile = -2;
	global->isolate_outfile = -2;
	global->delimiter = NULL;
	global->cmds = NULL;
	global->token = NULL;
	global->pipe_nb = 0;
	global->cmd = NULL;
	global->stop_exec = false;
}

void	init_value(t_global **global)
{
	(*global)->cmd = readline("\x1b[34;1mbricoshell\x1b[36;1m>\x1b[39;49m\x1b[22m ");
	if (!(*global)->cmd)
		exit_shell(*global, EXIT_SUCCESS);
	(*global)->pipe_nb = pipe_nb((*global)->cmd);
	(*global)->token = malloc(sizeof(t_tokens) * ((*global)->pipe_nb + 1));
	init_tokens((*global)->token, (*global)->pipe_nb);
}
