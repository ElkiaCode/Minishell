#include "../includes/minishell.h"

static int	ft_is_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	return (0);
}

t_tokens	*get_token_type(t_tokens *token, int token_size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < token_size)
	{
		j = -1;
		while (token[i].tokens[++j])
		{
			if (ft_strncmp(token[i].tokens[j], "<<", 2) == 0)
				token[i].type[j] = T_DLESS;
			else if (ft_strncmp(token[i].tokens[j], ">>", 2) == 0)
				token[i].type[j] = T_DGREAT;
			else if (ft_strncmp(token[i].tokens[j], "<", 1) == 0)
				token[i].type[j] = T_RLESS;
			else if (ft_strncmp(token[i].tokens[j], ">", 1) == 0)
				token[i].type[j] = T_RGREAT;
			else if (ft_strncmp(token[i].tokens[j], "'", 1) == 0)
				token[i].type[j] = T_S_QUOTE;
			else if (token[i].tokens[j][0] == '"')
				token[i].type[j] = T_D_QUOTE;
			else if (ft_is_cmd(token[i].tokens[j]) == 1)
				token[i].type[j] = T_CMD;
			else
				token[i].type[j] = T_ERR;
			if (token[i].type[0] == T_ERR)
				token[i].type[0] = T_CMD;
		}
	}
	return (token);
}
