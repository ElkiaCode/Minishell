/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:39:10 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:39:32 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	return (0);
}

int	determine_token_type(char *token)
{
	if (ft_strncmp(token, "<<", 2) == 0)
		return (T_DLESS);
	else if (ft_strncmp(token, ">>", 2) == 0)
		return (T_DGREAT);
	else if (ft_strncmp(token, "<", 1) == 0)
		return (T_RLESS);
	else if (ft_strncmp(token, ">", 1) == 0)
		return (T_RGREAT);
	else if (token[0] == '\'')
		return (T_S_QUOTE);
	else if (token[0] == '"')
		return (T_D_QUOTE);
	else if (ft_is_cmd(token) == 1)
		return (T_CMD);
	return (T_ERR);
}

t_tokens	*get_token_type(t_tokens *token, int token_size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < token_size)
	{
		j = -1;
		while (token[i].tokens[++j])
		{
			token[i].type[j] = determine_token_type(token[i].tokens[j]);
			if (j == 0 && token[i].type[0] == T_ERR)
				token[i].type[0] = T_CMD;
		}
	}
	return (token);
}
