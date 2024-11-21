/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:38:32 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/19 16:22:08 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing(t_tokens *token, char *line, int tokens_size)
{
	char	**line_tab;
	int		*size;

	line_tab = split_command(line);
	line_tab = ft_split(line_tab, "<>|;");
	size = tab_size(line_tab);
	tokenizer(token, line_tab, tokens_size, size);
	
}
