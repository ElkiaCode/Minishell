#include "../includes/minishell.h"

static int	error_input(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && (line[i] == '&' || line[i] == ';'))
			return (1);
		if (line[i] && (line[i] == '"' || line[i] == '\''))
		{
			while (line[i] && (line[i] != '"' || line[i] != '\''))
				i++;
		}
		if (line[i])
			i++;
	}
	return (0);
}

static int	pipe_error(char *line)
{
	int	i;

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
	int		i;
	int		b;
	char	c;

	b = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] && (line[i] == '"' || line[i] == '\'') && b == 0)
		{
			b = 1;
			c = line[i];
			i++;
			while (line[i] && line[i] != c)
				i++;
			if (line[i] && line[i] == c)
				b = 0;
		}
		i++;
	}
	return (b);
}

int	check_error(char *line)
{
	if (!line || *line == '\0' || *line == ' ')
		return (1);
	if (single_quote(line) == 1 || error_input(line) == 1 || pipe_error(line) == 1)
	{
		printf("error\n");
		return (1);
	}
	return (0);
}
