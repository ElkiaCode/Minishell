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

void split_token(t_tokens tokens, char *command)
{
	
}

void tokenization(t_global *global, char *command)
{
	char **result;
	int i;
	
	i = 0;
	result = split_command(command);
	while (result[i])
	{
		add_architect(&global->architect, result[i]);
		i++;
	}
}
