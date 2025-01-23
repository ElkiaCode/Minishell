/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:38:55 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:39:39 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
				if (token[i].type[j] == T_DLESS && (!token[i].type[j + 1]
						|| token[i].type[j + 1] != T_HEREDOC))
					return (1);
				else if (token[i].type[j] == T_RLESS && (!token[i].type[j + 1]
						|| token[i].type[j + 1] != T_I_FILE))
					return (1);
				else if (token[i].type[j] == T_RGREAT && (!token[i].type[j + 1]
						|| token[i].type[j + 1] != T_OR_FILE))
					return (1);
				else if (token[i].type[j] == T_DGREAT && (!token[i].type[j + 1]
						|| token[i].type[j + 1] != T_OD_FILE))
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
