/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:37:55 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:37:56 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env(t_global *data, char *name, char *value)
{
	t_env	*curr;
	char	*full;
	char	*tmp;

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
	free(full);
}

char	*ft_getenv(t_global *data, char *name)
{
	t_env	*tmp;
	char	*res;

	if (!ft_strncmp(name, "?", INT_MAX))
		return (ft_itoa(data->status));
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

t_env	*new_env(char *env)
{
	t_env	*new;
	char	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	tmp = ft_strchr(env, '=');
	if (!tmp)
		return (free(new), NULL);
	new->name = ft_substr(env, 0, tmp - env);
	new->value = ft_strdup(tmp + 1);
	new->next = NULL;
	return (new);
}

void	env_add(t_global *global, t_env *new)
{
	t_env	*tmp;
	t_env	*prev;

	if (!global->env || ft_strcmp(new->name, global->env->name) < 0)
	{
		new->next = global->env;
		global->env = new;
		return ;
	}
	tmp = global->env;
	prev = NULL;
	while (tmp && ft_strcmp(new->name, tmp->name) > 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	new->next = tmp;
	if (prev)
		prev->next = new;
}

void	copy_env(t_global *global, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		env_add(global, new_env(env[i++]));
}
