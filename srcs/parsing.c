/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:38:32 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/25 10:20:04 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing(t_tokens *token, char *line, int tokens_size)
{
	int		*size;
	char	**line_tab;

	if (check_error(line) == 1)
		return ;
	line_tab = split_command(line);
	line_tab = ft_split(line_tab, "'<>|\"");
	line_tab = union_tab(line_tab, 0);
	size = tab_size(line_tab);
	tokenizer(token, line_tab, tokens_size, size);
}
