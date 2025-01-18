#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	pwd[_PC_PATH_MAX];

	if (!getcwd(pwd, _PC_PATH_MAX))
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
