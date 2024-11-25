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

int pipe_nb(char *line)
{
	int i;
	int nb;

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

int main()
{
	t_global *global;
	int tokens_size;

	tokens_size = 0;
	while (1)
	{
		tokens_size = init_struct(&global, tokens_size);
		parsing(global->token, global->cmd, tokens_size);
		free(global->cmd);
	}
	return (0);
}
