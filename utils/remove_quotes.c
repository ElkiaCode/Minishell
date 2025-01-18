#include "../includes/minishell.h"

bool is_quote(char c)
{
    return (c == '"' || c == '\'');
}

char    *remove_quotes(char *token, int j)
{
    char *result;
    int len;
    int i;
    bool in_quote = false;
    char current_quote;

    len = ft_strlen(token);
    current_quote = 0;
    i = 0;
    result = malloc(len + 1);
    while (token[i])
    {
        if (is_quote(token[i]))
        {
            if (in_quote && token[i] == current_quote)
            {
                in_quote = false;
                current_quote = 0;
            }
            else if (!in_quote)
            {
                in_quote = true;
                current_quote = token[i];
            }
            else
                result[j++] = token[i];
        }
        else
            result[j++] = token[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}
