/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:38:55 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/24 10:06:51 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	valid_redirection(int type, int next_type)
{
	if (type == T_DLESS && next_type != T_HEREDOC)
		return (1);
	else if (type == T_RLESS && next_type != T_I_FILE)
		return (1);
	else if (type == T_RGREAT && next_type != T_OR_FILE)
		return (1);
	else if (type == T_DGREAT && next_type != T_OD_FILE)
		return (1);
	return (0);
}

static int	parser_redirection(t_tokens *token, int token_size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < token_size)
	{
		j = -1;
		while (token[i].tokens[++j])
		{
			if (j + 1 < token[i].token_size)
			{
				if (valid_redirection(token[i].type[j], token[i].type[j + 1]))
					return (1);
			}
		}
	}
	return (0);
}

int	final_parser(t_tokens *token, int token_size)
{
	if (parser_redirection(token, token_size) == 1)
	{
		printf("error\n");
		return (1);
	}
	return (0);
}
