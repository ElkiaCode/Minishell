/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:31:53 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:31:57 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_exit_code(char *arg)
{
	unsigned long long	exit_code;
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	exit_code = 0;
	while ((arg[i] <= 13 && arg[i] >= 9) || arg[i] == 32)
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		if (arg[i++] == '-')
			sign = -1;
	while (arg[i] >= '0' && arg[i] <= '9')
		exit_code = exit_code * 10 + arg[i++] - '0';
	return ((int)(exit_code * sign) % 256);
}

bool check_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
		if (!ft_isdigit(arg[i++]))
			return (0);
	return (1);
}

void	ft_exit(t_global *data, char **args)
{
	int		exit_code;

	exit_code = 0;
	if (count_args(args) == 1)
		exit_shell(data, data->status);
	if (args[1])
	{
		exit_code = get_exit_code(args[1]);
		if (!check_numeric(args[1]))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit_shell(data, 2);
		}
	}
	if (count_args(args) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		data->status = 1;
		return ;
	}
	exit_shell(data, exit_code);
}
