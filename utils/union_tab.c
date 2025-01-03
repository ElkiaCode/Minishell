#include "../includes/minishell.h"

char	**union_tab(char **tab, int size)
{
	char	**result;
	int		i;
	int		new_size;
	char	*merged;
	char	*temp;

	i = 0;
	new_size = 0;
	while (tab[size])
		size++;
	result = malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		if (ft_strncmp(tab[i], ">", 1) == 0 || ft_strncmp(tab[i], "<", 1) == 0)
		{
			merged = strdup(tab[i]);
			while (i + 1 < size && ft_strncmp(tab[i + 1], tab[i], 1) == 0)
			{
				temp = malloc(ft_strlen(merged) + 2);
				ft_strncpy(temp, merged, ft_strlen(merged));
				ft_strcat(temp, tab[i + 1]);
				free(merged);
				merged = temp;
				i++;
			}
			result[new_size++] = merged;
		}
		else
			result[new_size++] = ft_strdup(tab[i]);
		i++;
	}
	result[new_size] = NULL;
	return (result);
}
