/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:30:25 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/30 20:30:37 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", INT_MAX))
		return (true);
	else if (!ft_strncmp(cmd, "cd", INT_MAX))
		return (true);
	else if (!ft_strncmp(cmd, "pwd", INT_MAX))
		return (true);
	else if (!ft_strncmp(cmd, "export", INT_MAX))
		return (true);
	else if (!ft_strncmp(cmd, "unset", INT_MAX))
		return (true);
	else if (!ft_strncmp(cmd, "env", INT_MAX))
		return (true);
	else if (!ft_strncmp(cmd, "exit", INT_MAX))
		return (true);
	else if (!ft_strncmp(cmd, "bob", INT_MAX))
		return (true);
	else if (!ft_strncmp(cmd, "rand", INT_MAX))
		return (true);
	return (false);
}

void	exec_builtin(t_global *data, t_cmd *cmd_ptr, int fd_out)
{
	if (fd_out < 0)
		fd_out = STDOUT_FILENO;
	if (!ft_strncmp(cmd_ptr->args[0], "echo", INT_MAX))
		data->status = ft_echo(cmd_ptr->args, fd_out);
	else if (!ft_strncmp(cmd_ptr->args[0], "cd", INT_MAX))
		data->status = ft_cd(data, cmd_ptr->args);
	else if (!ft_strncmp(cmd_ptr->args[0], "pwd", INT_MAX))
		data->status = ft_pwd(fd_out);
	else if (!ft_strncmp(cmd_ptr->args[0], "export", INT_MAX))
		data->status = ft_export(data, cmd_ptr->args, fd_out);
	else if (!ft_strncmp(cmd_ptr->args[0], "unset", INT_MAX))
		data->status = ft_unset(data, cmd_ptr->args);
	else if (!ft_strncmp(cmd_ptr->args[0], "env", INT_MAX))
		data->status = ft_env(data, fd_out);
	else if (!ft_strncmp(cmd_ptr->args[0], "exit", INT_MAX))
		ft_exit(data, cmd_ptr->args);
	else if (!ft_strncmp(cmd_ptr->args[0], "bob", INT_MAX))
		printf("Le Bricoleur\n");
	else if (!ft_strncmp(cmd_ptr->args[0], "rand", INT_MAX))
		data->status = ft_rand(cmd_ptr->args);
}
