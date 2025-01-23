/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:33:47 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:33:53 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	g_signal_pid;

int	pipe_nb(char *line)
{
	int	i;
	int	nb;

	i = 0;
	nb = 1;
	while (line[i])
	{
		if (line[i] == '|')
			nb++;
		i++;
	}
	return (nb);
}

int	main(int ac, char **av, char **env)
{
	t_global	*global;

	(void)ac;
	(void)av;
	global = malloc(sizeof(t_global));
	if (!global)
		return (EXIT_FAILURE);
	make_struct_null(global);
	copy_env(global, env);
	signals();
	while (1)
	{
		g_signal_pid = 0;
		init_value(&global);
		parsing(global, global->token, global->cmd, global->pipe_nb);
		if (!global->stop_exec)
			prepare_exec(global);
		free(global->cmd);
		global->stop_exec = false;
	}
	return (0);
}
