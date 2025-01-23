#include "../includes/minishell.h"

static int	error_input(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
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

	i = -1;
	while (line && line[++i])
	{
		if (line[0] == '|')
			return (1);
		if (line[i] == '|' && line[i + 1] == '|')
			return (1);
		if (line[i] == '|' && line[i + 1] == '\0')
			return (1);
	}
	return (0);
}

static int	double_quote(char *line)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (line && line[++i])
		if (line[i] == '"')
			count++;
	return (count % 2);
}

static int	single_quote(char *line)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (line && line[++i])
		if (line[i] == '\'')
			count++;
	return (count % 2);
}

int	check_error(char *line)
{
	if (!line || *line == '\0' || *line == ' ')
		return (1);
	if (single_quote(line) || error_input(line) || pipe_error(line)
		|| double_quote(line) || line[ft_strlen(line) - 1] == '\\')
	{
		printf("error\n");
		return (1);
	}
	return (0);
}
