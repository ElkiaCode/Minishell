#include "../includes/minishell.h"

t_tokens	*get_args_app(t_tokens *token)
{
	t_tokens	*result;
	int			i;
	int			new_size;
	char		*merged;
	char		*temp;

	i = -1;
	new_size = 0;
	result = malloc(sizeof(t_tokens));
	result->token_size = 0;
	result->tokens = malloc(sizeof(char *) * (token->token_size + 1));
	result->type = malloc(sizeof(int) * token->token_size);
	while (++i < token->token_size)
	{
		if (token->type[i] == T_D_QUOTE)
		{
			remove_quotes();
			result->type[new_size] = T_ARG;
		}
		else if (token->type[i] == T_S_QUOTE)
		{
			expander();
			remove_quotes();
			result->type[new_size] = T_ARG;
		}
		else
		{
			remove_quotes();
			result->tokens[new_size] = ft_strdup(token->tokens[i]);
			result->type[new_size] = token->type[i];
		}
		new_size++;
	}
	result->tokens[new_size] = NULL;
	result->token_size = new_size;
	return (result);
}

void	get_args(t_tokens **token, int token_size)
{
	t_tokens	*new_token;
	int			i;
	int			j;

	i = -1;
	while (++i < token_size)
	{
		j = -1;
		new_token = get_args_app(&(*token)[i]);
		while (++j < (*token)[i].token_size)
			free((*token)[i].tokens[j]);
		free((*token)[i].tokens);
		free((*token)[i].type);
		(*token)[i] = *new_token;
		free(new_token);
	}
}
