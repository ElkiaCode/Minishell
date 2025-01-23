/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:38:39 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:39:35 by lpolizzi         ###   ########.fr       */
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
