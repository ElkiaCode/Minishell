#include "minishell.h"

void	free_tab(char ***tab)
{
	int	i;

	i = 0;
	while (*tab[i])
	{
		free(*tab[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}


int	do_heredoc(t_global data)
{
	int		heredoc_fd;
	char	*line;
	char	*tmp;

	heredoc_fd = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		tmp = ft_strjoin(data.delimiter, "\n");
		if (!ft_strcmp(line, tmp))
			break ;
		write(heredoc_fd, line, ft_strlen(line));
		free(line);
		free(tmp);
	}
	close(heredoc_fd);
	if (line)
		free(line);
	if (tmp)
		free(tmp);
	return (open(".heredoc", O_RDONLY));
}

void	init_heredoc(t_global *data)
{
	data->is_heredoc = 1;
	return (do_heredoc(*data));
}

int	prepare_infile(t_global *data, char *file, int type)
{
	int	fd;

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
	{
		fd = init_heredoc(data);
	}
	return (fd);
}

int	prepare_outfile(t_global *data, char *file, int type)
{
	int	fd;

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
	return (fd);
}

void	treat_token(t_global *data, char *token, int type, int *k)
{
	if (type == T_CMD || type == T_ARG)
	{
		data->isolate_cmd[*k] = ft_strdup(token);
		(*k)++;
	}
	else if (type == T_I_FILE || type == T_HEREDOC)
		data->isolate_infile = prepare_infile(data, token, type);
	else if (type == T_OD_FILE || type == T_OR_FILE)
		data->isolateoutfile = prepare_outfile(data, token, type);
	else if (type == T_DELIMITER)
	{
		if (data->delimiter)
			free(data->delimiter);
		data->delimiter = ft_strdup(token);
	}
}

int	is_directory(t_pipex *data, char *cmd)
{
	int	tmp_fd;

	tmp_fd = open(cmd, O_WRONLY);
	if (tmp_fd < 0 && errno == EISDIR)
		data->status = 1;
	close(tmp_fd);
	return (0);
}

char	**get_paths(t_pipex *data)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
		{
			paths = ft_split(data->env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!paths)
		data->status = 127;
	return (paths);
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
	if (!data->*env)
	{
		perror(cmd);
		return (NULL);
	}
	paths = get_paths(data);
	exec_path = find_exec(cmd, paths);
	free_tab(&paths);
	return (exec_path);
}

void cmd_cpy(t_global *data, t_cmd *cmd)
{
	int i;

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
	cmd->infile = data->isolate_infile;
	cmd->outfile = data->isolate_outfile;
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
		if (*tmp)
			cmd->cmd_path = ft_strdup(data->isolate_cmd[0]);
	cmd_cpy(data, cmd);
	cmd->next = NULL;
	cmd->pid = -1;
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
	int	i;
	int	j;
	int	k;

	i = -1;
	while (data->token[++i])
	{
		if (data->isolate_cmd)
			free_tab(&data->isolate_cmd);
		j = 0;
		while (data->token[i].tokens[j])
			j++;
		data->isolate_cmd = malloc(sizeof(char *) * (j + 1));
		if (!data->isolate_cmd)
			return ;
		data->isolate_cmd[j] = NULL;
		j = -1;
		k = 0;
		while (data->token[i].tokens[++j])
			treat_token(data, data->token[i].tokens[j], data->token[i].type[j], &k);
		cmd_add_back(&data->cmd, new_cmd(data));
		data->isolate_infile = -2;
		data->isolate_outfile = -2;
	}
}
