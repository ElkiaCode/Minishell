#include "../includes/minishell.h"

static char *get_env_name(t_global *data, char *name)
{
    char *result;

    result = ft_getenv(data, name);
    if (result)
        return (ft_strdup(result));
    return (ft_strdup(""));
}

static char    *add_result(char *result, char *new)
{
    int old_len;
    int new_len;
    char *new_result;

    if (result)
        old_len = ft_strlen(result);
    else
        old_len = 0;
    if (new)
        new_len = ft_strlen(new);
    else
        new_len = 0;
    new_result = malloc(old_len + new_len + 1);
    if (result)
    {
        ft_strncpy(new_result, result, old_len);
        free(result);
    }
    else
        new_result[0] = '\0';
    if (new)
        ft_strcat(new_result, new);
    return (new_result);

}

static char *expand_variable(t_global *data, char *token, int *i)
{
    int j;
    char *temp;
    char *name;

    j = *i + 1;
    while (token[j] && (ft_isalnum(token[j]) || token[j] == '_'))
        j++;
    temp = ft_strndup(&token[*i + 1], j - (*i + 1));
    name = get_env_name(data, temp);
    free(temp);
    *i = j;
    return (name);
}

static char *append_to_result(char *result, char *new_part)
{
    char *temp;

    temp = result;
    result = add_result(temp, new_part);
    free(new_part);
    return (result);
}

char *final_expander(t_global *data, char *token)
{
    int i;
    int j;
    char *result;
    char *temp;

    i = 0;
    result = NULL;
    while (token[i])
    {
        if (token[i] == '$')
        {
            temp = expand_variable(data, token, &i);
            result = append_to_result(result, temp);
        }
        else
        {
            j = i;
            while (token[i] && token[i] != '$')
                i++;
            temp = ft_strndup(&token[j], i - j);
            result = append_to_result(result, temp);
        }
    }
    return (result);
}
