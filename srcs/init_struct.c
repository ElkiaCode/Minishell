#include "../includes/minishell.h"

void	init_tokens(t_tokens *token, int tokens_size)
{
	int	i;

	i = 0;
	while (i < tokens_size)
	{
		token[i].tokens = NULL;
		token[i].type = NULL;
		token[i].token_size = 0;
		i++;
	}
}

void	init_struct(t_global **global)
{
	*global = malloc(sizeof(t_global));
	(*global)->cmd = readline("minishell> ");
	if (ft_strncmp((*global)->cmd, "exit", 4) == 0)
	{
		rl_clear_history();
		exit(EXIT_SUCCESS);
	}
	(*global)->pipe_nb = pipe_nb((*global)->cmd);
	(*global)->space_nb = 0;
	(*global)->token = malloc(sizeof(t_tokens) * ((*global)->pipe_nb));
	init_tokens((*global)->token, (*global)->pipe_nb);
	add_history((*global)->cmd);
}
