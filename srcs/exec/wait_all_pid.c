/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_pid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:28:02 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/30 20:28:34 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_signal_status(t_global *data, int status)
{
	static const t_signal_message	signal_messages[] = {
	{SIGXFSZ, "File size limit exceeded (core dumped)\n"},
	{SIGSYS, "Bad system call (core dumped)\n"},
	{SIGPIPE, "Broken pipe\n"},
	{SIGXCPU, "CPU time limit exceeded (core dumped)\n"},
	{SIGBUS, "Bus error (core dumped)\n"},
	{SIGFPE, "Floating point exception (core dumped)\n"},
	{SIGSEGV, "Segmentation fault (core dumped)\n"},
	{SIGQUIT, "Quit (core dumped)\n"},
	{SIGILL, "Illegal instruction (core dumped)\n"},
	{SIGABRT, "Aborted (core dumped)\n"},
	{0, NULL}};
	int								i;

	i = -1;
	data->status = 128 + status;
	while (signal_messages[++i].signal)
	{
		if (signal_messages[i].signal == status)
		{
			printf("%s", signal_messages[i].message);
			break ;
		}
	}
}

void	wait_all_pids(t_global *data)
{
	t_cmd	*cmd_ptr;
	int		status;
	pid_t	pid;

	cmd_ptr = data->cmds;
	while (cmd_ptr)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == g_signal_pid)
		{
			if (WIFSIGNALED(status))
				get_signal_status(data, WTERMSIG(status));
			else if (WIFEXITED(status))
				if (WEXITSTATUS(status) > data->status)
					data->status = WEXITSTATUS(status);
		}
		cmd_ptr = cmd_ptr->next;
	}
}
