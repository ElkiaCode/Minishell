/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:31:25 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/30 20:31:32 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_error(t_global *data, char *cmd)
{
	if (errno == EACCES && data->status == 0 && !is_file(cmd))
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		data->status = 126;
		return ;
	}
	else if ((!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
		&& data->status == 0)
		perror(cmd);
	else
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	data->status = 127;
}

void	child_process(t_global *data, t_cmd *cmd_ptr, int fd[2])
{
	close(fd[0]);
	if (cmd_ptr->infile_fd > 0)
		dup2(cmd_ptr->infile_fd, STDIN_FILENO);
	if (cmd_ptr->outfile_fd > 0)
		dup2(cmd_ptr->outfile_fd, STDOUT_FILENO);
	else if (cmd_ptr->next)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (data->env_tab)
	{
		free_tab(data->env_tab);
		data->env_tab = NULL;
	}
	make_env_tab(data);
	signals_child();
	if (cmd_is_builtin(cmd_ptr->args[0]))
		exec_builtin(data, cmd_ptr, STDOUT_FILENO);
	else if (execve(cmd_ptr->cmd_path, cmd_ptr->args, data->env_tab) == -1)
		exec_error(data, cmd_ptr->args[0]);
	exit(data->status);
}

void	parent_process(t_cmd *cmd_ptr, int fd[2])
{
	close(fd[1]);
	if (cmd_ptr->infile_fd > 0)
		close(cmd_ptr->infile_fd);
	if (cmd_ptr->next && cmd_ptr->next->infile_fd < 0)
		cmd_ptr->next->infile_fd = dup(fd[0]);
	close(fd[0]);
}

void	pipe_and_fork(t_global *data, t_cmd *cmd_ptr, int fd[2])
{
	if (pipe(fd) == -1)
	{
		data->status = 1;
		perror(NULL);
		return ;
	}
	g_signal_pid = fork();
	if (g_signal_pid < 0)
	{
		data->status = 1;
		perror(NULL);
		return ;
	}
	else if (g_signal_pid == 0)
		child_process(data, cmd_ptr, fd);
	else
		parent_process(cmd_ptr, fd);
}

void	do_cmds(t_global *data)
{
	int		fd[2];
	t_cmd	*cmd_ptr;

	cmd_ptr = data->cmds;
	while (cmd_ptr)
	{
		if (!cmd_ptr->cmd_path || !cmd_ptr->cmd_path[0] || cmd_ptr->skip_cmd)
		{
			cmd_ptr = cmd_ptr->next;
			if (cmd_ptr && cmd_ptr->infile_fd < 0)
				cmd_ptr->infile_fd = open("/dev/null", O_RDONLY);
			continue ;
		}
		else if (cmd_ptr == data->cmds && !cmd_ptr->next
			&& cmd_is_builtin(cmd_ptr->args[0]))
			exec_builtin(data, cmd_ptr, cmd_ptr->outfile_fd);
		else
			pipe_and_fork(data, cmd_ptr, fd);
		cmd_ptr = cmd_ptr->next;
	}
	wait_all_pids(data);
	data->cmds = free_cmd_list(data->cmds);
}
