#include "../includes/minishell.h"

t_tokens	*union_arg_res(t_tokens *token, int key)
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
		if (token->type[i] == T_ARG)
		{
			merged = ft_strdup(token->tokens[i]);
			while (i + 1 < token->token_size && token->type[i + 1] == T_ARG)
			{
				temp = malloc(ft_strlen(merged) + ft_strlen(token->tokens[i
							+ 1]) + 2);
				ft_strncpy(temp, merged, ft_strlen(merged));
				if (!ft_strncmp(token->tokens[i + 1], "'", 1)
					&& !ft_strncmp(token->tokens[i], "'", 1))
					{
						if (key == 0)
							ft_strcat(temp, " ");
					}
				ft_strcat(temp, token->tokens[i + 1]);
				free(merged);
				merged = temp;
				i++;
			}
			result->tokens[new_size] = merged;
			result->type[new_size] = T_ARG;
			new_size++;
		}
		else
		{
			result->tokens[new_size] = ft_strdup(token->tokens[i]);
			result->type[new_size] = token->type[i];
			new_size++;
		}
	}
	result->tokens[new_size] = NULL;
	result->token_size = new_size;
	return (result);
}

void	union_arg(t_tokens **token, int token_size, int key)
{
	t_tokens	*new_token;
	int			i;
	int			j;

	i = -1;
	while (++i < token_size)
	{
		j = -1;
		new_token = union_arg_res(&(*token)[i], key);
		while (++j < (*token)[i].token_size)
			free((*token)[i].tokens[j]);
		free((*token)[i].tokens);
		free((*token)[i].type);
		(*token)[i] = *new_token;
		free(new_token);
	}
}
