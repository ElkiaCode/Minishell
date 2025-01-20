#include "../includes/minishell.h"

t_tokens	*get_args_app(t_global *data, t_tokens *token)
{
	t_tokens	*result;
	int			i;
	int			new_size;
	char		*new_token;
	int			j;

	i = -1;
	j = 0;
	new_size = 0;
	result = malloc(sizeof(t_tokens));
	result->token_size = 0;
	result->tokens = malloc(sizeof(char *) * (token->token_size + 1));
	result->type = malloc(sizeof(int) * token->token_size);
	while (++i < token->token_size)
	{
		if (token->type[i] == T_D_QUOTE)
		{
			new_token = final_expander(data, token->tokens[i]);
			new_token = remove_quotes(new_token, j);
			result->tokens[new_size] = ft_strdup(new_token);
			result->type[new_size] = T_ARG;
		}
		else if (token->type[i] == T_S_QUOTE)
		{
			new_token = remove_quotes(token->tokens[i], j);
			result->tokens[new_size] = ft_strdup(new_token);
			result->type[new_size] = T_ARG;
		}
		else
		{
			new_token = final_expander(data, token->tokens[i]);
			new_token = remove_quotes(new_token, j);
			result->tokens[new_size] = ft_strdup(new_token);
			result->type[new_size] = token->type[i];
		}
		new_size++;
	}
	result->tokens[new_size] = NULL;
	result->token_size = new_size;
	return (result);
}

void	get_args(t_global *data, t_tokens **token, int token_size)
{
	t_tokens	*new_token;
	int			i;
	int			j;

	i = -1;
	while (++i < token_size)
	{
		j = -1;
		new_token = get_args_app(data, &(*token)[i]);
		while (++j < (*token)[i].token_size)
			free((*token)[i].tokens[j]);
		free((*token)[i].tokens);
		free((*token)[i].type);
		(*token)[i] = *new_token;
		free(new_token);
	}
}
