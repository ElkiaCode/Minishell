/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:41:21 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:41:25 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*merge_tokens(char **tab, int *i, int size)
{
	char	*merged;
	char	*temp;

	merged = strdup(tab[*i]);
	while (*i + 1 < size && ft_strncmp(tab[*i + 1], tab[*i], 1) == 0)
	{
		temp = malloc(ft_strlen(merged) + 2);
		ft_strncpy(temp, merged, ft_strlen(merged));
		ft_strcat(temp, tab[*i + 1]);
		free(merged);
		merged = temp;
		(*i)++;
	}
	return (merged);
}

char	**union_tab(char **tab, int size)
{
	char	**result;
	int		i;
	int		new_size;

	i = 0;
	new_size = 0;
	while (tab[size])
		size++;
	result = malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		if (ft_strncmp(tab[i], ">", 1) == 0 || ft_strncmp(tab[i], "<", 1) == 0)
			result[new_size++] = merge_tokens(tab, &i, size);
		else
			result[new_size++] = ft_strdup(tab[i]);
		i++;
	}
	result[new_size] = NULL;
	return (result);
}
