#include "minishell.h"

static void	print_echo(int count, int i, bool nl, char **args)
{
	if (!ft_strncmp(args[i], "-n", INT_MAX))
	{
		nl = false;
		i++;
	}
	while (i < count)
	{
		printf("%s", args[i]);
		if (i + 1 < count)
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
}

int	ft_echo(char **args)
{
	int		i;
	int		count;
	bool	nl;

	count = 0;
	while (args[count])
		count++;
	i = 1;
	nl = true;
	print_echo(count, i, nl, args);
	return (0);
}
