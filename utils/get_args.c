#include "../includes/minishell.h"

static char *process_double_quote(t_global *data, char *token)
{
    char *expanded;
    char *result;

    expanded = final_expander(data, token);
    result = remove_quotes(expanded, 0);
    free(expanded);
    return (result);
}

static void fill_result(t_tokens *result, char *new_token, int new_size, int type)
{
    result->tokens[new_size] = ft_strdup(new_token);
    result->type[new_size] = type;
}

static void process_token(t_global *data, t_tokens *token, t_tokens *result, int i)
{
    char *new_token;

    if (token->type[i] == T_D_QUOTE)
    {
        new_token = process_double_quote(data, token->tokens[i]);
        fill_result(result, new_token, result->token_size++, T_ARG);
        free(new_token);
    }
    else if (token->type[i] == T_S_QUOTE)
    {
        new_token = remove_quotes(token->tokens[i], 0);
        fill_result(result, new_token, result->token_size++, T_ARG);
    }
    else
    {
        new_token = process_double_quote(data, token->tokens[i]);
        fill_result(result, new_token, result->token_size++, token->type[i]);
        free(new_token);
    }
}

t_tokens *get_args_app(t_global *data, t_tokens *token)
{
    t_tokens *result;
    int i;

    result = malloc(sizeof(t_tokens));
    result->token_size = 0;
    result->tokens = malloc(sizeof(char *) * (token->token_size + 1));
    result->type = malloc(sizeof(int) * token->token_size);
    i = -1;
    while (++i < token->token_size)
        process_token(data, token, result, i);
    result->tokens[result->token_size] = NULL;
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

