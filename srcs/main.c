/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:10:20 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/07 19:06:26 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main()
{
	t_global global;
	char *line;
	
	init_struct(global);
	while (1)
	{
		line = readline("minishell> ");
		tokenization(global.token, line);
	}
	return (0);
}
