/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:17:43 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/12 12:31:35 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int *tab_size(char **tab_line)
{
	int *size;
	int i;
	int j;
	int	k;

	i = 0;
	k = 0;
	j = 0;
	while (tab_line[i])
	{
		if (*tab_line[i] == '|')
			j++;
		i++;
	}
	size = malloc(sizeof(int) * (j + 1));
	while (k <= j)
	{
		size[k] = 0;
		k++;
	}
	i = 0;
	j = 0;
	while (tab_line[i])
	{
		if (*tab_line[i] == '|')
			j++;
		else
			size[j] += 1;
		i++;
	}
	return (size);
}
