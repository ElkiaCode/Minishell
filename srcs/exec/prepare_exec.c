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

void	make_env_tab(t_global *data)
{
	t_env	*env_ptr;
	int		i;
	char	*tmp;

	i = 0;
	env_ptr = data->env;
	while (env_ptr)
	{
		i++;
		env_ptr = env_ptr->next;
	}
	data->env_tab = malloc(sizeof(char *) * (i + 1));
	if (!data->env_tab)
		return ;
	i = 0;
	env_ptr = data->env;
	while (env_ptr)
	{
		data->env_tab[i] = ft_strjoin(env_ptr->name, "=");
		tmp = ft_strjoin(data->env_tab[i], env_ptr->value);
		free(data->env_tab[i]);
		data->env_tab[i++] = tmp;
		env_ptr = env_ptr->next;
	}
	data->env_tab[i] = NULL;
}

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

void	exec_error(t_global *data, char *cmd)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		data->status = 127;
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		data->status = 126;
	}
}

void	child_process(t_global *data, t_cmd *cmd_ptr, int fd[2])
{
	close(fd[0]);
	if (cmd_ptr->infile_fd > 0)
		dup2(cmd_ptr->infile_fd, STDIN_FILENO);
	if (cmd_ptr->next)
		dup2(fd[1], STDOUT_FILENO);
	else if (cmd_ptr->outfile_fd > 0)
		dup2(cmd_ptr->outfile_fd, STDOUT_FILENO);
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
	if (cmd_ptr->next)
		cmd_ptr->next->infile_fd = dup(fd[0]);
	close(fd[0]);
}

void	pipe_and_fork(t_global *data, t_cmd *cmd_ptr, int fd[2])
{
	if (pipe(fd) == -1)
	{
		data->status = 1;
		return ;
	}
	g_signal_pid = fork();
	if (g_signal_pid < 0)
	{
		data->status = 1;
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
		if (cmd_ptr == data->cmds && !cmd_ptr->next
			&& cmd_is_builtin(cmd_ptr->args[0]))
			exec_builtin(data, cmd_ptr, cmd_ptr->outfile_fd);
		else
			pipe_and_fork(data, cmd_ptr, fd);
		cmd_ptr = cmd_ptr->next;
	}
	wait_all_pids(data);
}

void	write_in_heredoc(t_global *data, char *line, int heredoc_fd)
{
	line = final_expander(data, line);
	write(heredoc_fd, line, ft_strlen(line));
	write(heredoc_fd, "\n", 1);
	free(line);
}

int	do_heredoc(t_global data)
{
	int		heredoc_fd;
	char	*line;

	heredoc_fd = open("/tmp/.heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (heredoc_fd == -1)
		return (-1);
	while (1)
	{
		line = readline("heredoc>");
		if (!line)
		{
			printf("minishell: warning: here-document delimited ");
			printf("by end-of-file (wanted `%s')\n", data.delimiter);
			break ;
		}
		if (!ft_strncmp(line, data.delimiter, INT_MAX))
			break ;
		write_in_heredoc(&data, line, heredoc_fd);
	}
	close(heredoc_fd);
	free(line);
	heredoc_fd = open("/tmp/.heredoc", O_RDONLY);
	unlink("/tmp/.heredoc");
	return (heredoc_fd);
}

int	prepare_infile(t_global *data, char *file, int type)
{
	int	fd;
	int	old_fd;

	old_fd = data->isolate_infile;
	if (type == T_I_FILE)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			perror(file);
			fd = open("/dev/null", O_RDONLY);
		}
	}
	if (type == T_HEREDOC)
		fd = do_heredoc(*data);
	if (old_fd != -2)
		close(old_fd);
	return (fd);
}

int	prepare_outfile(t_global *data, char *file, int type)
{
	int	fd;
	int	old_fd;

	old_fd = data->isolate_outfile;
	fd = 0;
	if (type == T_OD_FILE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == T_OR_FILE)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		fd = open("/dev/null", O_WRONLY);
		perror(file);
		data->status = 1;
	}
	if (old_fd != -2)
		close(old_fd);
	return (fd);
}

void	treat_token(t_global *data, char *token, int type, t_index *index)
{
	if (type == T_CMD || type == T_ARG || type == T_ERR)
		data->isolate_cmd[index->k++] = ft_strdup(token);
	else if (type == T_HEREDOC)
	{
		if (data->delimiter)
			free(data->delimiter);
		data->delimiter = ft_strdup(data->token[index->i].tokens[index->j]);
		data->isolate_infile = prepare_infile(data, token, type);
	}
	else if (type == T_I_FILE)
		data->isolate_infile = prepare_infile(data, token, type);
	else if (type == T_OD_FILE || type == T_OR_FILE)
		data->isolate_outfile = prepare_outfile(data, token, type);
}

int	is_directory(t_global *data, char *cmd)
{
	int	tmp_fd;

	tmp_fd = open(cmd, O_WRONLY);
	if (tmp_fd < 0 && errno == EISDIR)
	{
		perror(cmd);
		data->status = 1;
		return (1);
	}
	close(tmp_fd);
	return (0);
}

char	*find_exec(char *cmd, char **paths)
{
	int		i;
	char	*exec_path;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		exec_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(exec_path, X_OK))
		{
			free_tab(paths);
			return (exec_path);
		}
		free(exec_path);
		exec_path = NULL;
		i++;
	}
	free_tab(paths);
	return (NULL);
}

char	*cmd_path(t_global *data, char *cmd)
{
	char	*exec_path;
	char	*tmp;

	if (!cmd)
		return (NULL);
	if (is_directory(data, cmd))
		return (NULL);
	else if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	if (!data->env)
		return (ft_strdup(cmd));
	exec_path = NULL;
	tmp = ft_getenv(data, "PATH");
	if (tmp)
	{
		exec_path = find_exec(cmd, ft_split(tmp, ":"));
		free(tmp);
	}
	return (exec_path);
}

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
		if (token.type[i] == T_CMD || token.type[i] == T_ARG
			|| token.type[i] == T_ERR)
			size++;
	return (size);
}

void	prepare_exec(t_global *data)
{
	t_index	index;

	index.i = -1;
	while (data->token && ++index.i < data->pipe_nb)
	{
		if (data->isolate_cmd)
			free_tab(data->isolate_cmd);
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
		data->isolate_infile = -2;
		data->isolate_outfile = -2;
	}
	free_tokens(data->token, data->pipe_nb);
	do_cmds(data);
	data->cmds = free_cmd_list(data->cmds);
}
