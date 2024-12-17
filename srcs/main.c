#include "../includes/minishell.h"

int	pipe_nb(char *line)
{
	int	i;
	int	nb;

	i = 0;
	nb = 1;
	while (line[i])
	{
		if (line[i] == '|')
			nb++;
		i++;
	}
	return (nb);
}

int	main(void)
{
	t_global	*global;

	while (1)
	{
		init_struct(&global); // j'init un tableau de chaine de caractere pour chaque section de la cmd
		// separer d'un | se qui permet de faire comme une liste chainee mais plus simple d'uttilisation.
		parsing(global->token, global->cmd, global->pipe_nb);
		free(global->cmd);
	}
	return (0);
}


// intruductions dans ce super projet pas bien organiser :

// 1/

// je commence par recuperer la ligne de commande et je fait un premier check des differentes erreur.

// 2/

// ensuite je cree un tableau de chaine de carractere qui prend en compte chaque espace pour creer le tableau et 
// je fais ensuite la meme chose avec les separateur pour agrandir le tableau.

// 3/

//  je cree ensuite les tokens en separent en different tableau de chaine de carractere en fonction des pipes
// viens ensuite le typage de chaque chaine de carractere venant de chaque tokens.

// 4/

// le parsing final prenant en compte le typage de chaque tokens et verifiant bien qu'il n'y a pas d'erreur.
// cette parti n'est pas fini

// il reste a faire en sorte de supprimer les quotes des tokens + un petit nombre d'erreur.
//rien ne me viens en tete direct mais j'ai peu etre oublier autre chose.

