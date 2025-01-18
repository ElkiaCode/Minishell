#include "../includes/minishell.h"

int	*tab_size(char **tab_line)
{
	int	*size;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	j = 0;
	while (tab_line[i])
	{
		if (*tab_line[i] == '|')
			j++;
		i++;
	}
	size = malloc(sizeof(int) * (j + 1));
	while (k <= j)
	{
		size[k] = 0;
		k++;
	}
	i = 0;
	j = 0;
	while (tab_line[i])
	{
		if (*tab_line[i] == '|')
			j++;
		else
			size[j]++;
		i++;
	}
	return (size);
}
