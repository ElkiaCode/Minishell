/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:31:25 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:31:27 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_export(t_global *data, int out_fd)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		write(out_fd, "declare -x ", 11);
		write(out_fd, tmp->name, ft_strlen(tmp->name));
		if (tmp->value)
		{
			write(out_fd, "=\"", 2);
			write(out_fd, tmp->value, ft_strlen(tmp->value));
			write(out_fd, "\"\n", 2);
		}
		else
		{
			write(out_fd, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	is_valid_export(char *arg)
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
	if (arg[i] == '\0')
	{
		tmp[0] = ft_strdup(arg);
		tmp[1] = NULL;
		tmp[2] = NULL;
		return (tmp);
	}
	tmp[0] = ft_substr(arg, 0, i);
	tmp[1] = ft_strdup(arg + i + 1);
	tmp[2] = NULL;
	return (tmp);
}

int	ft_export(t_global *data, char **args, int out_fd)
{
	int		i;
	int		exit_status;
	char	**tmp;

	i = 0;
	if (count_args(args) == 1)
		return (print_export(data, out_fd));
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
