/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:31:39 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:31:40 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_option(char *arg, int *i, bool *nl)
{
	int	j;

	j = 1;
	while (arg[j] == 'n')
		j++;
	if (arg[j] == '\0')
	{
		*nl = false;
		(*i)++;
	}
}

static void	print_echo(int count, bool nl, char **args, int out_fd)
{
	int	i;

	i = 1;
	if (args[i][0] == '-')
		check_option(args[i], &i, &nl);
	while (i < count)
	{
		write(out_fd, args[i], ft_strlen(args[i]));
		if (i + 1 < count)
			write(out_fd, " ", 1);
		i++;
	}
	if (nl)
		write(out_fd, "\n", 1);
}

int	ft_echo(char **args, int out_fd)
{
	int		count;
	bool	nl;

	count = 0;
	while (args[count])
		count++;
	nl = true;
	print_echo(count, nl, args, out_fd);
	return (0);
}
