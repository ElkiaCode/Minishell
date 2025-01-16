#include "../../includes/minishell.h"

static int	print_export(t_global *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
	return (0);
}

static int	is_valid_export(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (0);
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '=')
			return (0);
	}
	return (1);
}

char	**get_name_value(char *arg)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		return (NULL);
	while (arg[i] && arg[i] != '=')
		i++;
	tmp[0] = ft_substr(arg, 0, i - 1);
	tmp[1] = ft_strdup(arg + i + 1);
	tmp[2] = NULL;
	return (tmp);
}

int	ft_export(t_global *data, char **args)
{
	int		i;
	int		exit_status;
	char	**tmp;

	i = 0;
	if (count_args(args) == 1)
		return (print_export(data));
	else
	{
		while (args[++i])
		{
			tmp = get_name_value(args[i]);
			if (!is_valid_export(tmp[0]))
			{
				ft_putendl_fd("export: invalid identifier\n", 2);
				exit_status = 1;
			}
			else
				update_env(data, tmp[0], tmp[1]);
			free_tab(tmp);
		}
	}
	return (1);
}
