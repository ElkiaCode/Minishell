#include "../../includes/minishell.h"

static int	get_exit_code(char *arg, bool *error)
{
	unsigned long long	exit_code;
	int					i;
	int					sign;
	int					len_remove;

	i = 0;
	sign = 1;
	exit_code = 0;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] != 32)
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		if (arg[i++] == '-')
			sign = -1;
	len_remove = i;
	while (arg[i] >= '0' && arg[i] <= '9')
		exit_code = exit_code * 10 + (arg[i++] - '0');
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] != 32)
	{
		i++;
		len_remove++;
	}
	if (arg[i] || i - len_remove > 20 || ((sign == 1 && exit_code > LONG_MAX
				|| (sign == -1 && (exit_code - 1) > LONG_MAX + 1))))
		*error = true;
	return ((int)(exit_code * sign) % 256);
}

void	ft_exit(t_global *data, char **args)
{
	int		exit_code;
	bool	error;

	exit_code = 0;
	error = false;
	if (count_args(args) == 1)
		exit_shell(data, data->status); // TODO : implement exit_shell
	if (args[1])
	{
		exit_code = get_exit_code(args[1], &error);
		if (error)
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
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
