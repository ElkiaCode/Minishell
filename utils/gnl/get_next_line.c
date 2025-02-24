/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:34:34 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:34:41 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*gnl_remove_line(char *data)
{
	char	*new_data;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data[i] && data[i] != '\n')
		i++;
	if (!data[i] || !data[i + 1])
	{
		free(data);
		return (NULL);
	}
	new_data = malloc(sizeof(char) * (gnl_strlen(data) - i + 1));
	if (!new_data)
	{
		free(data);
		return (NULL);
	}
	i++;
	while (data[i])
		new_data[j++] = data[i++];
	new_data[j] = '\0';
	free(data);
	return (new_data);
}

char	*gnl_cut_line(const char *data)
{
	size_t	i;
	char	*ret;

	if (!data)
		return (NULL);
	i = 0;
	while (data[i] && data[i] != '\n')
		i++;
	ret = malloc(sizeof(char) * (i + 2));
	if (!ret)
		return (NULL);
	i = 0;
	while (data[i] && data[i] != '\n')
	{
		ret[i] = data[i];
		i++;
	}
	if (data[i] == '\n')
		ret[i++] = '\n';
	ret[i] = '\0';
	return (ret);
}

static char	*gnl_read_from_file(int fd, char *data)
{
	char	*s;
	int		bytes_read;

	s = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!s)
		return (NULL);
	bytes_read = 1;
	while (!gnl_strchr(data, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, s, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(s);
			return (NULL);
		}
		s[bytes_read] = 0;
		data = gnl_strjoin(data, s);
	}
	free(s);
	return (data);
}

char	*get_next_line(int fd)
{
	static char	*data[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (data[fd])
		{
			free(data[fd]);
			data[fd] = NULL;
		}
		return (NULL);
	}
	data[fd] = gnl_read_from_file(fd, data[fd]);
	if (!data[fd])
		return (NULL);
	line = gnl_cut_line(data[fd]);
	data[fd] = gnl_remove_line(data[fd]);
	if (!data[fd] && !gnl_strlen(line))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
