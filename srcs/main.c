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

int	main(int ac, char **av, char **env)
{
	t_global	*global;
	(void)ac;
	(void)av;

	while (1)
	{
		init_struct(&global, env);
		parsing(global->token, global->cmd, global->pipe_nb);
		prepare_exec(global);
		free(global->cmd);
	}
	return (0);
}
