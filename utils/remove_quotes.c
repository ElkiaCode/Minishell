#include "../includes/minishell.h"

bool is_quote(char c)
{
    return (c == '"' || c == '\'');
}

static bool handle_quote(char c, bool *in_quote, char *current_quote)
{
    if (*in_quote && c == *current_quote)
    {
        *in_quote = false;
        *current_quote = 0;
        return (true);
    }
    else if (!*in_quote && is_quote(c))
    {
        *in_quote = true;
        *current_quote = c;
        return (true);
    }
    return (false);
}

static int process_char(char *result, char c, bool in_quote, int j)
{
    if (!is_quote(c) || in_quote)
        result[j++] = c;
    return (j);
}

char *remove_quotes(char *token, int j)
{
    char *result;
    int len;
    int i;
    bool in_quote;
    char current_quote;

    len = ft_strlen(token);
    result = malloc(len + 1);
    if (!result)
        return (NULL);
    i = 0;
    in_quote = false;
    current_quote = 0;
    while (token[i])
    {
        if (!handle_quote(token[i], &in_quote, &current_quote))
            j = process_char(result, token[i], in_quote, j);
        i++;
    }
    result[j] = '\0';
    return (result);
}
