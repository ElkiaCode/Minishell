/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:31:46 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:31:47 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_var(t_global *data, char *var)
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
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_global *data, char **args)
{
	int	i;

	i = 0;
	while (args && args[++i])
		unset_var(data, args[i]);
	return (0);
}
