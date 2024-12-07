/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:11:16 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/25 09:03:57 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>

// structs

typedef enum e_token_type
{
	T_CMD,
	T_ARG,
	T_RLESS,
	T_RGREAT,
	T_DLESS,
	T_DGREAT,
	T_OD_FILE,
	T_I_FILE,
	T_AND,
	T_OR_FILE,
	T_NL,
	T_ERR,
	T_HEREDOC,
	T_VAR,
	T_S_QUOTE,
	T_D_QUOTE,
}					t_token_type;

typedef struct s_tokens
{
	char			**tokens;
	t_token_type	*type;
	int				token_size;
}					t_tokens;

typedef struct s_global
{
	char			*cmd;
	char			**isolate_cmd;
	int				pipe_nb;
	t_tokens		*token;
}					t_global;

// init

void				init_struct(t_global **global);

// srcs

void				tokenizer(t_tokens *token, char **line_tab, int tokens_size,
						int *size);
void				parsing(t_tokens *token, char *line, int tokens_size);

// utils

void				*ft_memcpy(void *dest, const void *src, size_t n);
char				**split_command(char *str);
char				*ft_strdup(char *src);
char				*ft_strncpy(char *s1, char *s2, int n);
int					*tab_size(char **tab_line);
char				**ft_split(char **input, char *charset);
int					pipe_nb(char *line);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_tokens			*get_token_type(t_tokens *token, int token_size);
t_tokens			*search_for_args(t_tokens *token, int token_size);
t_tokens			*malloc_token(t_tokens *token, int *size, int tokens_size);
char				*ft_strcat(char *dst, const char *src);
char				**union_tab(char **tab, int size);
size_t				ft_strlen(const char *s);
int					check_error(char *line);
t_tokens			*main_expand(t_tokens *token, int token_size);

#endif
