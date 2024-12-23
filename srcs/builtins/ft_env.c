#include "minishell.h"

int ft_env(t_global *data)
{
	t_env *tmp;

	tmp = data->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
