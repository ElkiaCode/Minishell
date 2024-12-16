#include "minishell.h"

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
		fd = do_heredoc(data);
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
		data->infile_fd = prepare_infile(data, token, type);
	else if (type == T_OD_FILE || type == T_OR_FILE)
		data->outfile_fd = prepare_outfile(data, token, type);
	else if (type == T_DELIMITER)
	{
		if (data->delimiter)
			free(data->delimiter);
		data->delimiter = ft_strdup(token);
	}
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
			free_tab(data->isolate_cmd);
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
		{
			treat_token(data, data->token[i].tokens[j], data->token[i].type[j], &k);
		}
		data->isolate_cmd[k] = NULL;
		do_exec(data);
		data->infile_fd = -2;
		data->outfile_fd = -2;
	}
}
