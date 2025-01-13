#include "../includes/minishell.h"

void	parsing(t_tokens *token, char *line, int tokens_size)
{
	int		*size;
	char	**line_tab;


/* pas vraiment le parsing mais le file conducteur de toute ma partie*/
	if (check_error(line) == 1) // premier check des erreur simple
		return ;
	line_tab = split_command(line); // la mise sous forme de tableau de la ligne de cmd
	line_tab = ft_split(line_tab, "'<>|\""); // les separateurs a prendre en compte individuellement
	line_tab = union_tab(line_tab, 0); // l'union des > et < qui se suivent
	size = tab_size(line_tab); // taille du tableau
	tokenizer(token, line_tab, tokens_size, size); // la mise en place des tokens
	token = get_token_type(token, tokens_size); // le typage des separateur et des cmd simple
	token = search_for_args(token, tokens_size); // typage des arguments et des expander
	token = main_expand(token, tokens_size); // les expanders
	union_arg(&token, tokens_size, 0);
	del_quote(&token, tokens_size);
	union_arg(&token, tokens_size, 1);
	if (final_parser(token, tokens_size) == 1) // parsing final et pas encore fini
		return ;
	print_test(token, tokens_size); //le print pour le test
}
