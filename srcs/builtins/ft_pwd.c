#include "../../includes/minishell.h"

int	ft_pwd(int out_fd)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
	{
		perror("pwd");
		return (1);
	}
	else
	{
		ft_putendl_fd(pwd, out_fd);
		return (0);
	}
}
