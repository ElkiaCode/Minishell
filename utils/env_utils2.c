/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:29:24 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/30 20:29:37 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_env_tab(t_global *data)
{
	t_env	*env_ptr;
	int		i;
	char	*tmp;

	i = 0;
	env_ptr = data->env;
	while (env_ptr)
	{
		i++;
		env_ptr = env_ptr->next;
	}
	data->env_tab = malloc(sizeof(char *) * (i + 1));
	if (!data->env_tab)
		return ;
	i = 0;
	env_ptr = data->env;
	while (env_ptr)
	{
		data->env_tab[i] = ft_strjoin(env_ptr->name, "=");
		tmp = ft_strjoin(data->env_tab[i], env_ptr->value);
		free(data->env_tab[i]);
		data->env_tab[i++] = tmp;
		env_ptr = env_ptr->next;
	}
	data->env_tab[i] = NULL;
}
