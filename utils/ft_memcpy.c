/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:58:56 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/07 16:59:47 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	tmp1 = (char *)dest;
	tmp2 = (char *)src;
	while (i < n)
	{
		tmp1[i] = tmp2[i];
		i++;
	}
	while (i < n)
	{
		tmp1[i] = '\0';
		i++;
	}
	return (tmp1);
}
