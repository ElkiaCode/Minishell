#include "minishell.h"

void update_env(t_global *data, char *name, char *value)
{
	t_env *curr;
	char *full;
	char *tmp;

	curr = data->env;
	while (curr)
	{
		if (!ft_strncmp(curr->name, name, INT_MAX))
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	full = ft_strjoin(name, "=");
	tmp = ft_strdup(full);
	free(full);
	full = ft_strjoin(tmp, value);
	free(tmp);
	env_add(data, new_env(full));
}

char *ft_getenv(t_global *data, char *name)
{
	t_env *tmp;
	char *res;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, INT_MAX))
		{
			res = ft_strdup(tmp->value);
			return (res);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
