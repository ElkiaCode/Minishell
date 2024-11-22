void redirect_io(t_data *data)
{
	if (data->input_file)
	{
		data->fd_in = open(data->input_file, O_RDONLY);
		if (data->fd_in < 0)
			exit_error(data, "open", data->input_file);
		dup2(data->fd_in, STDIN_FILENO);
	}
	if (data->output_file)
	{
		if (data->output_type == 1)
			data->fd_out = open(data->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (data->output_type == 2)
			data->fd_out = open(data->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->fd_out < 0)
			exit_error(data, "open", data->output_file);
		dup2(data->fd_out, STDOUT_FILENO);
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**path;
	char	*path_cmd;
	char	*temp;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	path = ft_split(env[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		path_cmd = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path_cmd, F_OK) == 0)
		{
			free_split(path);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	free_split(path);
	return (NULL);
}
void	exec(t_data *data)
{
	char	*path;

	if (access(data->cmd[0], F_OK) == 0)
		path = ft_strdup(data->cmd[0]);
	else
		path = get_path(data->cmd[0], data->env);
	if (!path)
	{
		perror("Minishell : command not found : ");
		ft_putendl_fd(data->cmd[0], 2);
		exit(EXIT_FAILURE);
	}
	if (execve(path, data->cmd, data->env) == -1)
	{
		perror("Minishell : command not found: ");
		ft_putendl_fd(data->cmd[0], 2);
		free(path);
		exit(EXIT_FAILURE);
	}
	free(path);
}

void parent_process(t_data *data)
{
    int status;

    waitpid(data->pid, &status, 0);
    if (WIFEXITED(status))
        data->exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        data->exit_status = 128 + WTERMSIG(status);

    if (data->is_pipe)
    {
        if (data->pipe_in > 0)
            close(data->pipe_in);
        if (data->pipe_out > 0)
            close(data->pipe_out);
    }

    if (data->fd_in > 0)
        close(data->fd_in);
    if (data->fd_out > 0)
        close(data->fd_out);
}

void child_process(t_data *data)
{
	if (data->is_pipe)
	{
		if (data->pipe_in != STDIN_FILENO)
		{
			if (dup2(data->pipe_in, STDIN_FILENO) < 0)
				exit(EXIT_FAILURE);
			close(data->pipe_in);
		}
		if (data->pipe_out != STDOUT_FILENO)
		{
			if (dup2(data->pipe_out, STDOUT_FILENO) < 0)
				exit(EXIT_FAILURE);
			close(data->pipe_out);
		}
	}
	redirect_io(data);
	exec(data);
}

int do_pipe(int *pipe_fds)
{
    if (pipe(pipe_fds) == -1)
    {
        perror("pipe");
        return -1;
    }
    return 0;
}

void fork_process(t_data *data)
{
    int pipe_fds[2];

    if (data->is_pipe && do_pipe(pipe_fds) == -1)
        exit(EXIT_FAILURE);

    data->pipe_in = pipe_fds[0];
    data->pipe_out = pipe_fds[1];

    data->pid = fork();
    if (data->pid < 0)
        exit(EXIT_FAILURE);

    if (data->pid == 0)
        child_process(data);
    else
        parent_process(data);
}
