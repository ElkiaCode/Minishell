/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:44:01 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/07 17:00:34 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	void *new_ptr;
	size_t old_size;

	new_ptr = malloc(new_size);


	free(ptr);
	return (new_ptr);
}
