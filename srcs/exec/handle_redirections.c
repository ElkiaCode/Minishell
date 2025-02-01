/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:32:31 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/30 20:32:38 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_in_heredoc(t_global *data, char *line, int heredoc_fd)
{
	char	*tmp;

	tmp = final_expander(data, line);
	write(heredoc_fd, tmp, ft_strlen(tmp));
	write(heredoc_fd, "\n", 1);
	free(line);
	free(tmp);
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
		line = readline("\x1b[36;1mheredoc>\x1b[39;49m\x1b[22m ");
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
	fd = 0;
	if (type == T_I_FILE)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			perror(file);
			data->status = 1;
			data->isolate_skip = true;
		}
	}
	if (type == T_HEREDOC)
		fd = do_heredoc(*data);
	if (old_fd > 0)
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
		perror(file);
		data->status = 1;
		data->isolate_skip = true;
	}
	if (old_fd > 0)
		close(old_fd);
	return (fd);
}
