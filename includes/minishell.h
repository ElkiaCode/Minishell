/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:11:16 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/21 15:05:17 by cparodi          ###   ########.fr       */
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
#include <readline/history.h>

// structs

// typedef enum e_token_type
// {
// 	command,
// 	arg,
// 	op,
// 	redir,
// } t_token_type;

typedef struct s_tokens
{
	char				**tokens;
	// t_enum type;
}	t_tokens;

typedef struct s_global
{
	char				*cmd;
	t_tokens			*token;
}	t_global;

//init

int		init_struct(t_global **global, int tokens_size);

// srcs

void	tokenizer(t_tokens *token, char **line_tab, int tokens_size, int *size);
void	parsing(t_tokens *token, char *line, int tokens_size);

// utils

void		*ft_memcpy(void *dest, const void *src, size_t n);
char		**split_command(char *str);
char		*ft_strdup(char *src);
char		*ft_strncpy(char *s1, char *s2, int n);
int			*tab_size(char **tab_line);
char		**ft_split(char **input, char *charset);
int			pipe_nb(char *line);
int			ft_strncmp(const char *s1, const char *s2, size_t n);



#endif
