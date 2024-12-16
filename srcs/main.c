#include "../includes/minishell.h"

int	pipe_nb(char *line)
{
	int	i;
	int	nb;

	i = 0;
	nb = 1;
	while (line[i])
	{
		if (line[i] == '|')
			nb++;
		i++;
	}
	return (nb);
}

int	main(void)
{
	t_global	*global;

	while (1)
	{
		init_struct(&global);
		parsing(global->token, global->cmd, global->pipe_nb);
		prepare_exec(global);
		free(global->cmd);
	}
	return (0);
}
