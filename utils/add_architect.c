/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_architect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:26:32 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/09 19:50:37 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_architect *lst_new_architect(char *str)
{
	t_architect *new_node;
	new_node = (t_architect *)malloc(sizeof(t_architect));
    if (!new_node)
        return NULL;
    new_node->str = strdup(str);
    new_node->next = NULL;
    return (new_node);
}

void	add_architect(t_architect **list, char *str)
{
	t_architect *new_node;
	t_architect *current;

	new_node = lst_new_architect(str);
	if (*list == NULL)
		*list = new_node;
	else
	{
		current = *list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}
