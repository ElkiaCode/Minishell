#include "../includes/minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void free_all(t_global *data)
{
	if (data->env)
		free_env_list(data->env);
	if (data->env_tab)
		free_tab(data->env_tab);
}

void	exit_shell(t_global *data, int exit_code)
{
	free_all(data);
	exit(exit_code);
}
