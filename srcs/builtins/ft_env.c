/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:32:09 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:32:10 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_global *data, int out_fd)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		write(out_fd, tmp->name, ft_strlen(tmp->name));
		write(out_fd, "=", 1);
		if (tmp->value)
			write(out_fd, tmp->value, ft_strlen(tmp->value));
		write(out_fd, "\n", 1);
		tmp = tmp->next;
	}
	return (0);
}
