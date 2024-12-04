/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:10:20 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/21 14:58:06 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_nb(char *line)
{
	int	i;
	int	nb;

	i = 0;
	nb = 1;
	while (line[i])
	{
		if (line[i] == '|')
			nb++;
		i++;
	}
	return (nb);
}

int	main(void)
{
	t_global	*global;

	while (1)
	{
		init_struct(&global);
		parsing(global->token, global->cmd, global->pipe_nb);
		free(global->cmd);
	}
	return (0);
}
