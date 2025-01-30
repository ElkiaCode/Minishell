/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:35:37 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/30 20:36:00 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_file(char *cmd)
{
	int	tmp_fd;

	tmp_fd = open(cmd, O_RDONLY);
	if (tmp_fd >= 0)
	{
		close(tmp_fd);
		return (true);
	}
	return (false);
}

bool	is_directory(t_global *data, char *cmd, bool msg)
{
	int	tmp_fd;

	tmp_fd = open(cmd, O_WRONLY);
	if (tmp_fd < 0 && errno == EISDIR && data->status == 0)
	{
		if (msg)
			perror(cmd);
		data->status = 126;
		return (true);
	}
	close(tmp_fd);
	return (false);
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
	if ((!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
		&& is_directory(data, cmd, 1))
		return (ft_strdup(""));
	else if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	exec_path = NULL;
	tmp = ft_getenv(data, "PATH");
	if (!data->env || !tmp)
		return (ft_strdup(cmd));
	if (tmp)
	{
		exec_path = find_exec(cmd, ft_split(tmp, ":"));
		if (!exec_path && ft_strncmp(cmd, "./", 2) && ft_strncmp(cmd, "/", 1))
			exec_path = ft_strjoin(cmd, "./");
		free(tmp);
	}
	return (exec_path);
}
