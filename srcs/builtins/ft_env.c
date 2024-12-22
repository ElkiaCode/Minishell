#include "minishell.h"

int ft_env(t_global *data)
{
	int i;

	i = -1;
	while (data->env && data->env[++i])
		if (ft_strchr(data->env[i], '='))
			ft_putendl_fd(data->env[i], 1);
	return (0);
}
