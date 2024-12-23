#include "../includes/minishell.h"

char *ft_getenv(t_global *data, char *name)
{
	t_env *tmp;
	char *res;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, INT_MAX))
		{
			res = ft_strdup(tmp->value);
			return (res);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static char *expand_tilde(char *token)
{
    char *temp;
    char *result;
    size_t size;

    if (token[0] == '~')
    {
        temp = getenv("HOME");
        if (temp)
        {
            size = ft_strlen(temp) + ft_strlen(token);
            result = malloc(size);
            ft_strncpy(result, temp, ft_strlen(temp));
            ft_strcat(result, token + 1);
            return (result);
        }
    }
    return (ft_strdup(token));
}

static char *expand_variable(char *token)
{
    char *var_name;
    char *result;

    if (token[0] == '$')
    {
        var_name = token + 1;
        result = getenv(var_name);
        if (result)
            return (ft_strdup(result));
        else
            return (ft_strdup(""));
    }
    return (ft_strdup(token));
}

t_tokens *main_expand(t_tokens *token, int token_size)
{
    int i;
    int j;

    i = -1;
    while (++i < token_size)
    {
        j = -1;
        while (token[i].tokens[++j])
        {
            token[i].tokens[j] = expand_variable(token[i].tokens[j]);
            token[i].tokens[j] = expand_tilde(token[i].tokens[j]);
        }
    }
    return (token);
}
