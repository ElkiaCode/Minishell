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

char    *final_expander(t_global *data, char *token)
{
    int i;
    int j;
    char *result;
    char *temp;
    char *name;
    
    i = 0;
    result = NULL;
    while(token[i])
    {
        if (token[i] == '$')
        {
            j = i + 1;
            while (token[j] && (ft_isalnum(token[j]) || token[j] == '_'))
                j++;
            temp = ft_strndup(&token[i + 1], j - (i + 1));
            name = get_env_name(data, temp);
            free(temp);
            temp = result;
            result = add_result(temp, name);
            free(name);
            i = j;
        }
        else
        {
            j = i;
            while (token[i] && token[i] != '$')
                i++;
            temp = ft_strndup(&token[j], i - j);
            name = result;
            result = add_result(name, temp);
            free(temp);
        }
    }
    return (result);
}