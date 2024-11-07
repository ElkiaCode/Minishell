/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:11:16 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/07 19:07:19 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <termios.h>
#include <curses.h>
#include <readline/readline.h>

// structs

typedef struct s_tokens
{
	char		**tokens;
	size_t		size;
	int			t_count;
}	t_tokens;

typedef struct s_global
{
	t_tokens	token;
}	t_global;

//init

t_global	init_struct(t_global global, char **argv);
void		init_tokens(t_tokens tokens);


// srcs

void		tokenization(t_tokens tokens, char *command);
void		split_token(t_tokens tokens, char *command);



// utils

void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_realloc(void *ptr, size_t new_size);


#endif
