/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:37:13 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/09 19:54:18 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_struct(t_global *global)
{
	global->token = NULL;
	global->architect = NULL;
}
