/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:10:20 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/12 16:29:09 by cparodi          ###   ########.fr       */
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
	char *line;
	int tokens_size;
	
	while (1)
	{
		line = readline("minishell> ");
		tokens_size = pipe_nb(line);
		init_struct(&global, tokens_size);
		tokenizer(global->token, line, tokens_size);
	}
	return (0);
}
