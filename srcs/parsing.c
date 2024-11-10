/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:38:32 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/09 19:54:30 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void split_token(t_global *global, int size)
{
	int i;

	i = 0;
	while (global->architect)
	{
		add_token(global->token, global->architect->str, global->token->size);
	}
}

void tokenization(t_global *global, char *command)
{
	char **result;
	int size;
	int i;
	
	i = 0;
	size = 0;
	result = split_command(command);
	while (result[i])
	{
		add_architect(&global->architect, result[i]);
		i++;
	}
	split_token(global, i);
}
