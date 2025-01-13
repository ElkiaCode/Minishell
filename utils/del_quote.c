#include "../includes/minishell.h"

static t_tokens *remove_quotes(t_tokens *token)
{
    t_tokens *result;
    int       i;
    int       new_size;

    result = malloc(sizeof(t_tokens));
    result->tokens = malloc(sizeof(char *) * (token->token_size + 1));
    result->type = malloc(sizeof(int) * token->token_size);
    if (!result->tokens || !result->type)
    {
        free(result->tokens);
        free(result->type);
        free(result);
        return NULL;
    }

    i = 0;
    new_size = 0;
    while (i < token->token_size)
    {
        if (token->type[i] != T_S_QUOTE && token->type[i] != T_D_QUOTE)
        {
            result->tokens[new_size] = ft_strdup(token->tokens[i]);
            result->type[new_size] = token->type[i];
            new_size++;
        }
        i++;
    }

    result->tokens[new_size] = NULL;
    result->token_size = new_size;

    return result;
}

void    del_quote(t_tokens **token, int token_size)
{
    t_tokens	*new_token;
	int			i;
	int			j;

	i = -1;
	while (++i < token_size)
	{
	    j = -1;
		new_token = remove_quotes(&(*token)[i]);
		while (++j < (*token)[i].token_size)
			free((*token)[i].tokens[j]);
		free((*token)[i].tokens);
		free((*token)[i].type);
		(*token)[i] = *new_token;
		free(new_token);
	}
}