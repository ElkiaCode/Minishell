#include "../includes/minishell.h"

static int pipe_error(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[0] == '|')
			return (1);
		if (line[i] == '|' && line[i + 1] == '|')
			return (1);
		if (line[i] == '|' && line[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

static int	single_quote(char *line)
{
	int	i;
	int	b;

	b = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] && (line[i] == '"' || line[i] == '\'') && b == 0)
			b = 1;
		else if (line[i] && (line[i] == '"' || line[i] == '\'') && b == 1)
			b = 0;
		i++;
	}
	if (b == 1)
	{
		printf("error\n");
		return (1);
	}
	return (0);
}

int	check_error(char *line)
{
	if (single_quote(line) == 1)
	{
		printf("error\n");
		return (1);
	}
	if (pipe_error(line) == 1)
	{
		printf("error\n");
		return (1);
	}
	return (0);
}