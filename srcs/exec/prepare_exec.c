/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:36:57 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/30 20:37:04 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	treat_token(t_global *data, char *token, int type, t_index *index)
{
	if ((type == T_CMD || type == T_ARG || type == T_ERR) && token[0])
		data->isolate_cmd[index->k++] = ft_strdup(token);
	else if (type == T_HEREDOC && data->isolate_skip == false)
	{
		if (data->delimiter)
			free(data->delimiter);
		data->delimiter = ft_strdup(data->token[index->i].tokens[index->j]);
		data->isolate_infile = prepare_infile(data, token, type);
	}
	else if (type == T_I_FILE && data->isolate_skip == false)
		data->isolate_infile = prepare_infile(data, token, type);
	else if ((type == T_OD_FILE || type == T_OR_FILE)
		&& data->isolate_skip == false)
		data->isolate_outfile = prepare_outfile(data, token, type);
}

void	reset_isolate(t_global *data)
{
	if (data->isolate_cmd)
	{
		free_tab(data->isolate_cmd);
		data->isolate_cmd = NULL;
	}
	data->isolate_infile = -2;
	data->isolate_outfile = -2;
	data->isolate_skip = 0;
}

void	prepare_exec(t_global *data)
{
	t_index	index;

	index.i = -1;
	data->isolate_cmd = NULL;
	while (data->token && ++index.i < data->pipe_nb)
	{
		data->status = 0;
		reset_isolate(data);
		data->isolate_cmd = malloc(sizeof(char *)
				* (count_cmd_size(data->token[index.i]) + 1));
		if (!data->isolate_cmd)
			return ;
		data->isolate_cmd[count_cmd_size(data->token[index.i])] = NULL;
		index.j = -1;
		index.k = 0;
		while (data->token[index.i].tokens
			&& data->token[index.i].tokens[++index.j])
			treat_token(data, data->token[index.i].tokens[index.j],
				data->token[index.i].type[index.j], &index);
		cmd_add_back(&data->cmds, cmd_new(data));
	}
	free_tokens(data->token, data->pipe_nb);
	do_cmds(data);
	reset_isolate(data);
}
