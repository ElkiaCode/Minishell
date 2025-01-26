#include "../includes/minishell.h"
const char	*tokens_strings[] = {
	[T_CMD] = "T_CMD",
	[T_ARG] = "T_ARG",
	[T_RLESS] = "T_RLESS",
	[T_RGREAT] = "T_RGREAT",
	[T_DLESS] = "T_DLESS",
	[T_DGREAT] = "T_DGREAT",
	[T_OD_FILE] = "T_OD_FILE",
	[T_I_FILE] = "T_I_FILE",
	[T_AND] = "T_AND",
	[T_OR_FILE] = "T_OR_FILE",
	[T_NL] = "T_NL",
	[T_ERR] = "T_ERR",
	[T_HEREDOC] = "T_HEREDOC",
	[T_VAR] = "T_VAR",
	[T_S_QUOTE] = "T_S_QUOTE",
	[T_D_QUOTE] = "T_D_QUOTE",
};
void	print_test(t_tokens *token, int tokens_size)
{
	int	i;
	int	j;
	i = 0;
	j = 0;
	while (j < tokens_size)
	{
		printf("Group %d:\n", j);
		i = 0;
		if (token[j].tokens == NULL)
		{
			printf("  token[%d].tokens is NULL, skipping\n", j);
			j++;
			continue ;
		}
		while (token[j].tokens[i] != NULL)
		{
			if (token[j].tokens[i] != NULL)
			{
				printf("  %s\n", tokens_strings[token[j].type[i]]);
				printf("  %s\n", token[j].tokens[i]);
			}
			else
				printf("  token[%d].tokens[%d] is NULL\n", j, i);
			i++;
		}
		printf("-----------------\n");
		j++;
	}
}