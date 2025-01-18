#include "../includes/minishell.h"

void	exit_shell(t_global *data, int exit_code)
{
	(void)data;
	exit(exit_code);
}
