#include "../../includes/minishell.h"

static void	print_echo(int count, bool nl, char **args, int out_fd)
{
	int i;

	i = 1;
	if (!ft_strncmp(args[i], "-n", INT_MAX))
	{
		nl = false;
		i++;
	}
	while (i < count)
	{
		write(out_fd, args[i], ft_strlen(args[i]));
		if (i + 1 < count)
			write(out_fd, " ", 1);
		i++;
	}
	if (nl)
		write(out_fd, "\n", 1);
}

int	ft_echo(char **args, int out_fd)
{
	int		count;
	bool	nl;

	count = 0;
	printf("out fd is %d\n", out_fd);
	while (args[count])
		count++;
	nl = true;
	print_echo(count, nl, args, out_fd);
	return (0);
}
