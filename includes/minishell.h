/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:41:53 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/18 14:41:54 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern pid_t		g_signal_pid;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

// structs

typedef struct s_index
{
	int				i;
	int				j;
	int				k;
}					t_index;

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

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			*cmd_path;
	char			**args;
	int				infile_fd;
	int				outfile_fd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_global
{
	t_env			*env;
	char			**env_tab;
	char			*cmd;
	char			**isolate_cmd;
	int				pipe_nb;
	int				isolate_infile;
	int				isolate_outfile;
	char			*delimiter;
	int				status;
	t_tokens		*token;
	t_cmd			*cmds;
}					t_global;

// init

void				init_value(t_global **global);

// srcs

void				tokenizer(t_tokens *token, char **line_tab, int tokens_size,
						int *size);
void	parsing(t_global *data, t_tokens *token, char *line, int tokens_size);

// Exec
int					ft_pwd(void);
int					ft_export(t_global *data, char **args);
int					ft_unset(t_global *data, char **args);
int					ft_echo(char **args);
int					ft_env(t_global *data);
void				signals_child(void);
void				signals(void);
void				wait_all_pids(t_global *data);
void				make_env_tab(t_global *data);
bool				cmd_is_builtin(char *cmd);
void				exec_builtin(t_global *data, t_cmd *cmd_ptr);
void				child_process(t_global *data, t_cmd *cmd_ptr, int fd[2]);
void				parent_process(t_cmd *cmd_ptr, int fd[2]);
void				do_cmds(t_global *data);
int					do_heredoc(t_global data);
int					prepare_infile(t_global *data, char *file, int type);
int					prepare_outfile(t_global *data, char *file, int type);
void				treat_token(t_global *data, char *token, int type,
						t_index *index);
int					is_directory(t_global *data, char *cmd);
char				*find_exec(char *cmd, char **paths);
char				*cmd_path(t_global *data, char *cmd);
void				cmd_cpy(t_global *data, t_cmd *cmd);
t_cmd				*cmd_new(t_global *data);
void				cmd_add_back(t_cmd **cmd, t_cmd *new);
void				prepare_exec(t_global *data);
void				update_oldpwd(t_global *data);
void				update_pwd(t_global *data, char *path);
int					ft_cd(t_global *data, char **args);
int					ft_echo(char **args);
int					ft_env(t_global *data);
void				ft_exit(t_global *data, char **args);
int					get_exit_code(char *arg, bool *error);
int					print_export(t_global *data);
char				*ft_getenv(t_global *data, char *name);
void				update_env(t_global *data, char *name, char *value);
void				free_tab(char **tab);

// utils

void				make_struct_null(t_global *global);
void				copy_env(t_global *global, char **env);
void				env_add(t_global *global, t_env *new);
t_env				*new_env(char *env);
char				*get_next_line(int fd);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				**split_command(char *str);
char				*ft_strdup(const char *src);
char				*ft_strncpy(char *s1, char *s2, int n);
int					*tab_size(char **tab_line);
char				**ft_split_tab(char **input, char *charset);
int					pipe_nb(char *line);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_tokens			*get_token_type(t_tokens *token, int token_size);
t_tokens			*search_for_args(t_tokens *token, int token_size);
t_tokens			*malloc_token(t_tokens *token, int *size, int tokens_size);
char				*ft_strcat(char *dst, const char *src);
char				**union_tab(char **tab, int size);
size_t				ft_strlen(const char *s);
int					check_error(char *line);
int					final_parser(t_tokens *token, int token_size);
void				print_test(t_tokens *token, int tokens_size);
char				*ft_strjoin(char const *s1, char const *s2);
void	get_args(t_global *data, t_tokens **token, int token_size);
void				update_env(t_global *data, char *name, char *value);
char				*remove_quotes(char *token, int j);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strchr(const char *s, int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
void				ft_putendl_fd(char *s, int fd);
void				ft_putstr_fd(char *s, int fd);
int					ft_strcmp(const char *s1, const char *s2);
int					count_args(char **args);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char *str, char *charset);
void				exit_shell(t_global *data, int exit_code);
char    *final_expander(t_global *data, char *token);
char	*ft_strndup(const char *src, int n);
#endif
