#include "../includes/minishell.h"

void	init_tokens(t_tokens *token, int tokens_size)
{
	int	i;

	i = 0;
	while (i < (tokens_size + 1))
	{
		token[i].tokens = NULL;
		token[i].type = NULL;
		token[i].token_size = 0;
		i++;
	}
}

t_env	*new_env(char *env)
{
	t_env	*new;
	char	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	tmp = ft_strchr(env, '=');
	if (!tmp)
		return (free(new), NULL);
	new->name = ft_substr(env, 0, tmp - env);
	new->value = ft_strdup(tmp + 1);
	new->next = NULL;
	return (new);
}

void	env_add(t_global *global, t_env *new)
{
	t_env	*tmp;
	t_env	*prev;

	if (!global->env || ft_strcmp(new->name, global->env->name) < 0)
	{
		new->next = global->env;
		global->env = new;
		return ;
	}
	tmp = global->env;
	prev = NULL;
	while (tmp && ft_strcmp(new->name, tmp->name) > 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	new->next = tmp;
	if (prev)
		prev->next = new;
}

void	copy_env(t_global *global, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		env_add(global, new_env(env[i++]));
}

void	make_struct_null(t_global *global)
{
	global->env = NULL;
	global->status = 0;
	global->env_tab = NULL;
	global->isolate_cmd = NULL;
	global->isolate_infile = -2;
	global->isolate_outfile = -2;
	global->delimiter = NULL;
	global->cmds = NULL;
	global->token = NULL;
	global->pipe_nb = 0;
	global->cmd = NULL;
}

void	init_value(t_global **global)
{
	(*global)->cmd = readline("minishell> ");
	if (!(*global)->cmd)
		exit_shell(*global, EXIT_SUCCESS);
	(*global)->cmd = ft_strtrim((*global)->cmd, " ");
	(*global)->cmd = ft_strjoin((*global)->cmd, " ");
	(*global)->pipe_nb = pipe_nb((*global)->cmd);
	(*global)->token = malloc(sizeof(t_tokens) * ((*global)->pipe_nb + 1));
	init_tokens((*global)->token, (*global)->pipe_nb);
	add_history((*global)->cmd);
}
