/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:38:48 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/26 11:21:28 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_tokens(t_tokens *token, int pipe_nb)
{
	int	i;
	int	j;

	i = -1;
	while (++i < pipe_nb)
	{
		j = -1;
		while (++j < token[i].token_size)
			free(token[i].tokens[j]);
		free(token[i].type);
		free(token[i].tokens);
	}
}

void	free_all(t_global *data)
{
	if (data->env)
		free_env_list(data->env);
	if (data->env_tab)
		free_tab(data->env_tab);
	if (data->cmds)
		data->cmds = free_cmd_list(data->cmds);
}

void	exit_shell(t_global *data, int exit_code)
{
	free_all(data);
	exit(exit_code);
}
