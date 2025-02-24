/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:36:23 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:36:24 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_pipes(char **tab_line)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (tab_line[i])
	{
		if (*tab_line[i] == '|')
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

static int	*initialize_size_array(int pipe_count)
{
	int	*size;
	int	k;

	k = 0;
	size = malloc(sizeof(int) * (pipe_count + 1));
	if (!size)
		return (NULL);
	while (k <= pipe_count)
	{
		size[k] = 0;
		k++;
	}
	return (size);
}

static void	fill_size_array(char **tab_line, int *size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab_line[i])
	{
		if (*tab_line[i] == '|')
			j++;
		else
			size[j]++;
		i++;
	}
}

int	*tab_size(char **tab_line)
{
	int	pipe_count;
	int	*size;

	pipe_count = count_pipes(tab_line);
	size = initialize_size_array(pipe_count);
	if (!size)
		return (NULL);
	fill_size_array(tab_line, size);
	return (size);
}
