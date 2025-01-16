#include "../includes/minishell.h"

int	unset_var(t_global *data, char *var)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = data->env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				data->env = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

int	is_valid_arg(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 0;
	while (arg[++i])
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
	return (1);
}

int	ft_unset(t_global *data, char **args)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (args && args[++i])
	{
		if (!is_valid_arg(args[i]))
		{
			status = 1;
			ft_putstr_fd("unset: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else if (unset_var(data, args[i]))
			status = 1;
	}
	return (status);
}
