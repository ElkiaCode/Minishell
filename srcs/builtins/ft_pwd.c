#include "minishell.h"

int ft_pwd(t_global *data)
{
	char pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
	{
		perror("pwd");
		return (1);
	}
	else
	{
		ft_putendl_fd(pwd, 1);
		return (0);
	}
}
