/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:14:30 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/09 17:43:43 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tokens	*lst_new_tokens(char *str, int size)
{
	t_tokens *new_node;
	new_node = (t_tokens *)malloc(sizeof(t_tokens));
    if (!new_node)
        return NULL;
    new_node->tokens[size] = strdup(str);
    new_node->next = NULL;
    return (new_node);
}

void	add_token(t_tokens **list, char *str, int size)
{
	t_tokens *new_node;
	t_tokens *current;

	current = *list;
	new_node = lst_new(str, size);
	if (*list == NULL)
		*list = new_node;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

