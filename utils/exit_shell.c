/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:38:48 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:39:37 by lpolizzi         ###   ########.fr       */
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
