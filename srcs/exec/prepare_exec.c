#include "../includes/minishell.h"

void	wait_all_pids(t_global *data)
{
	t_cmd	*cmd_ptr;
	int		tmp;
	pid_t	pid;

	cmd_ptr = data->cmds;
	while (cmd_ptr)
	{
		pid = waitpid(0, &tmp, 0);
		if (pid == g_signal_pid)
		{
			if (WIFEXITED(tmp))
				if (WEXITSTATUS(tmp) > data->status)
					data->status = WEXITSTATUS(tmp);
		}
		if (cmd_ptr->infile_fd > 0)
			close(cmd_ptr->infile_fd);
		if (cmd_ptr->outfile_fd > 0)
			close(cmd_ptr->outfile_fd);
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
		data->env_tab[i] = tmp;
		env_ptr = env_ptr->next;
		i++;
	}
	data->env_tab[i] = NULL;
}

bool	cmd_is_builtin(char *cmd)
{
	char	**builtins;
	int		i;

	builtins = ft_split("echo cd pwd export unset env exit", ' ');
	if (!builtins)
		return (false);
	i = -1;
	while (builtins[++i])
	{
		if (!ft_strncmp(builtins[i], cmd, INT_MAX))
		{
			free_tab(builtins);
			return (true);
		}
	}
	free_tab(builtins);
	return (false);
}

void	exec_builtin(t_global *data, t_cmd *cmd_ptr)
{
	if (!ft_strncmp(cmd_ptr->args[0], "echo", INT_MAX))
		data->status = ft_echo(cmd_ptr->args);
	else if (!ft_strncmp(cmd_ptr->args[0], "cd", INT_MAX))
		data->status = ft_cd(data, cmd_ptr->args);
	else if (!ft_strncmp(cmd_ptr->args[0], "pwd", INT_MAX))
		data->status = ft_pwd(data);
	else if (!ft_strncmp(cmd_ptr->args[0], "export", INT_MAX))
		data->status = ft_export(data, cmd_ptr->args);
	else if (!ft_strncmp(cmd_ptr->args[0], "unset", INT_MAX))
		data->status = ft_unset(data, cmd_ptr->args);
	else if (!ft_strncmp(cmd_ptr->args[0], "env", INT_MAX))
		data->status = ft_env(data);
	else if (!ft_strncmp(cmd_ptr->args[0], "exit", INT_MAX))
		ft_exit(data, cmd_ptr->args);
}

void	child_process(t_global *data, t_cmd *cmd_ptr, int fd[2])
{
	close(fd[0]);
	if (cmd_ptr->infile_fd != -2)
		dup2(cmd_ptr->infile_fd, STDIN_FILENO);
	if (cmd_ptr->outfile_fd != -2)
		dup2(cmd_ptr->outfile_fd, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (data->env_tab)
	{
		free_tab(data->env_tab);
		data->env_tab = NULL;
	}
	if (data->env_tab)
		free_tab(data->env_tab);
	make_env_tab(data);
	if (cmd_is_builtin(cmd_ptr->args[0]))
		exec_builtin(data, cmd_ptr);
	else
	{
		signals_child();
		if (execve(cmd_ptr->cmd_path, cmd_ptr->args, data->env_tab) == -1)
			exec_error(data, cmd_ptr->args[0]);
	}
}

void	parent_process(t_global *data, t_cmd *cmd_ptr, int fd[2])
{
	close(fd[1]);
	if (cmd_ptr->infile_fd != -2)
		close(cmd_ptr->infile_fd);
	cmd_ptr->infile_fd = dup(fd[0]);
	close(fd[0]);
}

void	do_cmds(t_global *data)
{
	int		fd[2];
	t_cmd	*cmd_ptr;

	cmd_ptr = data->cmds;
	while (cmd_ptr)
	{
		if (pipe(fd) < 0)
			data->status = 1;
		g_signal_pid = fork();
		if (g_signal_pid < 0)
			data->status = 1;
		else if (g_signal_pid == 0)
			child_process(data, cmd_ptr, fd);
		else
			parent_process(data, cmd_ptr, fd);
		cmd_ptr = cmd_ptr->next;
	}
	wait_all_pids(data);
}

int	do_heredoc(t_global data)
{
	int		heredoc_fd;
	char	*line;
	char	*tmp;

	heredoc_fd = open("/tmp/.heredocA9gF3kL7X2rW6pZ4",
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		tmp = ft_strjoin(data.delimiter, "\n");
		if (!ft_strcmp(line, tmp))
			break ;
		line = expand_heredoc(data, line);
		write(heredoc_fd, line, ft_strlen(line));
		free(line);
		free(tmp);
	}
	close(heredoc_fd);
	if (line)
		free(line);
	if (tmp)
		free(tmp);
	heredoc_fd = open("/tmp/.heredocA9gF3kL7X2rW6pZ4", O_RDONLY);
	unlink("/tmp/.heredocA9gF3kL7X2rW6pZ4");
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
	if (type == T_OD_FILE)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			perror(file);
	}
	if (type == T_OR_FILE)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			perror(file);
	}
	if (fd == -1)
		data->status = 1;
	if (old_fd != -2)
		close(old_fd);
	return (fd);
}

void	treat_token(t_global *data, char *token, int type, t_index *index)
{
	if (type == T_CMD || type == T_ARG)
		data->isolate_cmd[index->k++] = ft_strdup(token);
	if (type == T_HEREDOC)
	{
		if (data->delimiter)
			free(data->delimiter);
		data->delimiter = ft_strdup(data->token[index->i].tokens[index->j + 1]);
	}
	else if (type == T_I_FILE || type == T_HEREDOC)
		data->isolate_infile = prepare_infile(data, token, type);
	else if (type == T_OD_FILE || type == T_OR_FILE)
		data->isolate_outfile = prepare_outfile(data, token, type);
}

int	is_directory(t_global *data, char *cmd)
{
	int	tmp_fd;

	tmp_fd = open(cmd, O_WRONLY);
	if (tmp_fd < 0 && errno == EISDIR)
		data->status = 1;
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
			return (exec_path);
		free(exec_path);
		exec_path = NULL;
		i++;
	}
	perror(cmd);
	return (NULL);
}

char	*cmd_path(t_global *data, char *cmd)
{
	char	**paths;
	char	*exec_path;

	if (!cmd)
		return (NULL);
	if (!access(cmd, X_OK) && !is_directory(data, cmd))
		return (ft_strdup(cmd));
	if (!data->env)
	{
		perror(cmd);
		return (NULL);
	}
	paths = get_paths(data);
	exec_path = find_exec(cmd, ft_getenv(data, "PATH"));
	free_tab(paths);
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
		return (NULL);
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
	int		i;

	i = 0;
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

void	prepare_exec(t_global *data)
{
	t_index	index;

	index.i = -1;
	while (&data->token[++index.i])
	{
		if (!data->cmds)
			data->isolate_infile = open("/dev/null", O_RDONLY);
		if (data->isolate_cmd)
			free_tab(data->isolate_cmd);
		index.j = 0;
		while (data->token[index.i].tokens[index.j])
			index.j++;
		data->isolate_cmd = malloc(sizeof(char *) * (index.j + 1));
		if (!data->isolate_cmd)
			return ;
		data->isolate_cmd[index.j] = NULL;
		index.j = -1;
		index.k = 0;
		while (data->token[index.i].tokens[++index.j])
			treat_token(data, data->token[index.i].tokens[index.j],
				data->token[index.i].type[index.j], &index);
		cmd_add_back(&data->cmds, new_cmd(data));
		data->isolate_infile = -2;
		data->isolate_outfile = -2;
	}
	do_cmds(data);
}
