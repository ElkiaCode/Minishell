#include "minishell.h"

int ft_env(t_global *data)
{
	t_env *tmp;

	tmp = data->env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		else
			printf("%s=\n", tmp->name);
		tmp = tmp->next;
	}
	return (0);
}
