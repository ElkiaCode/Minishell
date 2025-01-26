/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:38:34 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:39:35 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	error_input(char *line)
{
	int		i;
	bool	s_quote;
	bool	d_quote;

	i = -1;
	s_quote = false;
	d_quote = false;

	while (line && line[++i])
	{
		if (line[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (line[i] == '"' && !s_quote)
			d_quote = !d_quote;
		if (!s_quote && !d_quote && (line[i] == ';' || line[i] == '&'))
			return (1);
		if (!s_quote && !d_quote && line[i] == '|')
		{
			if (i == 0 || line[i + 1] == '|' || line[i + 1] == '\0')
				return (1);
		}
	}
	if (s_quote || d_quote)
		return (1);
	return (0);
}


int	check_error(char *line)
{
	if (!line || *line == '\0' || *line == ' ')
		return (1);
	if (error_input(line) || line[ft_strlen(line) - 1] == '\\')
	{
		printf("error\n");
		return (1);
	}
	return (0);
}
