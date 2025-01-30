/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:34:15 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/30 20:34:26 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_cpy(t_global *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (data->isolate_cmd[i])
		i++;
	cmd->args = malloc(sizeof(char *) * (i + 1));
	if (!cmd->args)
		return ;
	i = -1;
	while (data->isolate_cmd[++i])
		cmd->args[i] = ft_strdup(data->isolate_cmd[i]);
	cmd->args[i] = NULL;
	cmd->infile_fd = data->isolate_infile;
	cmd->outfile_fd = data->isolate_outfile;
	cmd->skip_cmd = data->isolate_skip;
}

t_cmd	*cmd_new(t_global *data)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_path = cmd_path(data, data->isolate_cmd[0]);
	if (!cmd->cmd_path)
		cmd->cmd_path = ft_strdup(data->isolate_cmd[0]);
	cmd_cpy(data, cmd);
	cmd->next = NULL;
	return (cmd);
}

void	cmd_add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last;

	if (cmd && *cmd)
	{
		last = *cmd;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*cmd = new;
}

t_cmd	*free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->infile_fd > 0)
			close(cmd->infile_fd);
		if (cmd->outfile_fd > 0)
			close(cmd->outfile_fd);
		free_tab(cmd->args);
		free(cmd->cmd_path);
		free(cmd);
		cmd = tmp;
	}
	return (NULL);
}

int	count_cmd_size(t_tokens token)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (token.tokens && token.tokens[++i])
		if ((token.type[i] == T_CMD || token.type[i] == T_ARG
				|| token.type[i] == T_ERR) && token.tokens[i][0])
			size++;
	return (size);
}
