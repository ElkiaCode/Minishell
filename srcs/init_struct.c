/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:37:13 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/07 18:52:04 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_tokens(t_tokens tokens)
{

}

t_global init_struct(t_global global, char **argv)
{
	init_tokens(global.token);
	return (global);
}
