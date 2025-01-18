#include "../includes/minishell.h"

t_tokens	*malloc_token(t_tokens *token, int *size, int tokens_size)
{
	int	j;
	int	i;

	j = 0;
	while (j < tokens_size)
	{
		i = 0;
		token[j].tokens = (char **)malloc(sizeof(char *) * (size[j] + 1));
		token[j].type = malloc(sizeof(int) * (size[j] + 1));
		token[j].token_size = size[j];
		while (i <= size[j])
		{
			token[j].type[i] = 0;
			i++;
		}
		token[j].tokens[size[j]] = NULL;
		j++;
	}
	return (token);
}
