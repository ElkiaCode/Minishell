#include "../includes/minishell.h"

t_tokens	*search_for_args(t_tokens *token, int token_size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < token_size)
	{
		j = -1;
		while (token[i].tokens[++j])
		{
			if (token[i].type[j] == T_DLESS && token[i].type[j + 1] == T_ERR)
				token[i].type[j + 1] = T_HEREDOC;
			else if (token[i].type[j] == T_RLESS && token[i].type[j
				+ 1] == T_ERR)
				token[i].type[j + 1] = T_I_FILE;
			else if (token[i].type[j] == T_RGREAT && token[i].type[j
				+ 1] == T_ERR)
				token[i].type[j + 1] = T_OR_FILE;
			else if (token[i].type[j] == T_DGREAT && token[i].type[j
				+ 1] == T_ERR)
				token[i].type[j + 1] = T_OD_FILE;
			if (token[i].type[j] == T_D_QUOTE)
			{
				j++;
				while (token[i].type[j] != T_D_QUOTE && token[i].tokens[j])
				{
					token[i].type[j] = T_ARG;
					j++;
				}
			}
			if (token[i].type[j] == T_S_QUOTE)
			{
				j++;
				while (token[i].type[j] != T_S_QUOTE && token[i].tokens[j])
				{
					token[i].type[j] = T_ARG;
					j++;
				}
			}
			if (token[i].type[j] == T_ERR && (token[i].type[j + 1] == T_D_QUOTE
					|| token[i].type[j + 1] == T_S_QUOTE))
				token[i].type[j] = T_ARG;
			if (token[i].type[j] == T_CMD && (token[i].type[j + 1] != T_D_QUOTE
					|| token[i].type[j + 1] != T_S_QUOTE) && token[i].type[j
				+ 1] == T_ERR)
				token[i].type[j + 1] = T_ARG;
			if (token[i].type[j] == T_ARG && token[i].type[j + 1] == T_ERR)
				token[i].type[j + 1] = T_ARG;
		}
	}
	return (token);
}
