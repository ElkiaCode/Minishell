#include "../includes/minishell.h"

void	parsing(t_tokens *token, char *line, int tokens_size)
{
	int		*size;
	char	**line_tab;

	if (check_error(line) == 1)
		return ;
	line_tab = split_command(line);
	line_tab = ft_split(line_tab, "'<>|\"");
	line_tab = union_tab(line_tab, 0);
	size = tab_size(line_tab);
	tokenizer(token, line_tab, tokens_size, size);
	token = get_token_type(token, tokens_size);
	token = search_for_args(token, tokens_size);
	token = main_expand(token, tokens_size);
	union_arg(&token, tokens_size);
	if (final_parser(token, tokens_size) == 1)
		return ;
	print_test(token, tokens_size);
}
