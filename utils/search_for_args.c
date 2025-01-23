#include "../includes/minishell.h"

static void handle_redirections(t_tokens *token, int i, int j)
{
    if (token[i].type[j] == T_DLESS && token[i].type[j + 1] == T_ERR)
        token[i].type[j + 1] = T_HEREDOC;
    else if (token[i].type[j] == T_RLESS && token[i].type[j + 1] == T_ERR)
        token[i].type[j + 1] = T_I_FILE;
    else if (token[i].type[j] == T_RGREAT && token[i].type[j + 1] == T_ERR)
        token[i].type[j + 1] = T_OR_FILE;
    else if (token[i].type[j] == T_DGREAT && token[i].type[j + 1] == T_ERR)
        token[i].type[j + 1] = T_OD_FILE;
}

static int handle_double_quotes(t_tokens *token, int i, int j)
{
    if (token[i].type[j] == T_D_QUOTE)
    {
        j++;
        while (token[i].type[j] != T_D_QUOTE && token[i].tokens[j])
        {
            token[i].type[j] = T_ARG;
            j++;
        }
    }
    return (j);
}

static int handle_single_quotes(t_tokens *token, int i, int j)
{
    if (token[i].type[j] == T_S_QUOTE)
    {
        j++;
        while (token[i].type[j] != T_S_QUOTE && token[i].tokens[j])
        {
            token[i].type[j] = T_ARG;
            j++;
        }
    }
    return (j);
}

static void handle_argument_types(t_tokens *token, int i, int j)
{
    if (token[i].type[j] == T_ERR && 
        (token[i].type[j + 1] == T_D_QUOTE || token[i].type[j + 1] == T_S_QUOTE))
        token[i].type[j] = T_ARG;
    else if (token[i].type[j] == T_CMD && 
             token[i].type[j + 1] == T_ERR)
        token[i].type[j + 1] = T_ARG;
    else if (token[i].type[j] == T_ARG && 
             token[i].type[j + 1] == T_ERR)
        token[i].type[j + 1] = T_ARG;
}

t_tokens *search_for_args(t_tokens *token, int token_size)
{
    int i;
    int j;

    i = -1;
    while (++i < token_size)
    {
        j = -1;
        while (token[i].tokens[++j])
        {
            if (j + 1 < token[i].token_size)
                handle_redirections(token, i, j);
            j = handle_double_quotes(token, i, j);
            j = handle_single_quotes(token, i, j);
            if (j + 1 < token[i].token_size)
                handle_argument_types(token, i, j);
        }
    }
    return (token);
}
