/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:51:16 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/25 23:13:29 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

unsigned int	ft_random_env(void)
{
	int				fd;
	unsigned int	random;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error while trying to open /dev/random.", STDERR_FILENO);
		return (-1);
	}
	read(fd, &random, sizeof(random));
	close(fd);
	return (random % 32767);
}

int	check_rand_args(char **args)
{
	int	i;

	i = -1;
	if (!args[1])
	{
		ft_putendl_fd("rand: missing argument", STDERR_FILENO);
		return (-1);
	}
	if (args[2])
	{
		ft_putendl_fd("rand: too many arguments", STDERR_FILENO);
		return (-1);
	}
	while (args[1][++i])
	{
		if (!ft_isdigit(args[1][i]) && args[1][i] != '-')
		{
			ft_putendl_fd("rand: numerical argument required", STDERR_FILENO);
			return (-1);
		}
	}
	return (0);
}

int	ft_rand(char **args)
{
	int		nb;
	int		fd;
	char	buf[1];
	char	*tmp;

	if (check_rand_args(args) == -1)
		return (1);
	nb = ft_atoi(args[1]);
	if (nb < 0)
	{
		ft_putendl_fd("rand: value out of range", STDERR_FILENO);
		return (1);
	}
	fd = open("/dev/random", O_RDONLY);
	read(fd, buf, 1);
	close(fd);
	tmp = ft_itoa(buf[0] % nb);
	ft_putendl_fd(tmp, STDOUT_FILENO);
	free(tmp);
	return (0);
}
