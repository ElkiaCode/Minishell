/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:11:16 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/09 19:53:01 by cparodi          ###   ########.fr       */
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

typedef struct s_architect
{
	char				*str;
	struct s_architect	*next;
}	t_architect;

typedef struct s_tokens
{
	char				**tokens;
	int					size;
	struct s_tokens		*next;
}	t_tokens;

typedef struct s_global
{
	t_tokens			*token;
	t_architect			*architect;
}	t_global;

//init

void		init_struct(t_global *global);


// srcs

void		tokenization(t_global *global, char *command);
void		split_token(t_global *global);



// utils

void		*ft_memcpy(void *dest, const void *src, size_t n);
char		**split_command(char *str);
char		*ft_strdup(char *src);
char		*ft_strncpy(char *s1, char *s2, int n);
void		add_architect(t_architect **list, char *str);
t_architect	*lst_new_architect(char *str);
void		add_token(t_tokens **list, char *str, int size);
t_tokens	*lst_new_tokens(char *str);

#endif
