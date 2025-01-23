/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:32:48 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:32:54 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing(t_global *data, t_tokens *token, char *line, int tokens_size)
{
	int		*size;
	char	**line_tab;

	if (check_error(line) == 1)
	{
		data->stop_exec = true;
		return ;
	}
	line_tab = split_command(line);
	line_tab = ft_split_tab(line_tab, "<>|");
	line_tab = union_tab(line_tab, 0);
	size = tab_size(line_tab);
	tokenizer(token, line_tab, tokens_size, size);
	token = get_token_type(token, tokens_size);
	get_args(data, &token, tokens_size);
	token = search_for_args(token, tokens_size);
	if (final_parser(token, tokens_size) == 1)
		return ;
}
