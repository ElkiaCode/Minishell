/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:38:32 by cparodi           #+#    #+#             */
/*   Updated: 2024/11/12 11:34:26 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void free_all(t_global *global)
// {
//     t_architect *current_architect;
//     t_architect *next_architect;
//     t_tokens *current_token;
//     t_tokens *next_token;
//     int i;

//     // Libérer la liste des architectes
//     current_architect = global->architect;
//     while (current_architect != NULL)
//     {
//         next_architect = current_architect->next;
//         free(current_architect->str);  // Libérer la chaîne de caractères
//         free(current_architect);      // Libérer le nœud de l'architecte
//         current_architect = next_architect;
//     }

//     // Libérer la liste des tokens
//     current_token = global->token;
//     while (current_token != NULL)
//     {
//         next_token = current_token->next;
        
//         // Libérer chaque chaîne de caractères dans le tableau 'tokens'
//         i = 0;
//         while (current_token->tokens[i])
//         {
//             free(current_token->tokens[i]);
//             i++;
//         }
        
//         free(current_token->tokens);  // Libérer le tableau de chaînes de caractères
//         free(current_token);          // Libérer le nœud de token
//         current_token = next_token;
//     }
// }

// void split_token(t_global **global, int *size, int count)
// {
// 	int i;
// 	t_architect *current;

// 	current = (* global)->architect;
// 	i = 0;
// 	while (i < count)
// 	{
// 		add_token(&(*global)->token, current, size[i]);
// 		current = current->next;
// 		i++;
// 	}

// }

// static void print_list(t_architect *head) {
//     t_architect *current = head;
//     while (current != NULL) {
//         printf("%s\n", current->str);
//         current = current->next;
//     }
// }

// static void print_double_list(t_tokens *head)
// {
//     t_tokens *current = head;

//     while (current != NULL)
// 	{
// 		int i = 0;
// 		while (current->tokens[i])
// 		{
//         	printf("test : %s\n", current->tokens[i]);
// 			i++;
// 		}
//         current = current->next;
//     }
// }

// void tokenization(t_global *global, char *command)
// {
// 	char **result;
// 	int *size;
// 	int i;
// 	int j;
	
// 	i = 0;
// 	j = 0;
// 	result = split_command(command);
// 	i = size_of_tab(result);
// 	size = (int *)malloc(sizeof(int) * (i + 1));
// 	while (j < i)
// 	{
// 		size[j] = 1;
// 		j++;
// 	}
// 	j = 0;
// 	i = 0;
// 	while (result[i])
// 	{
// 		add_architect(&global->architect, result[i]);
// 		if (*result[i] == '|')
// 			j++;
// 		size[j] += 1;
// 		i++;
// 	}
// 	printf("test %d\n", j);
// 	print_list(global->architect);
// 	split_token(&global, size, j + 1);
// 	printf("----------------\n");
// 	print_double_list(global->token);
// 	free_all(global);
// }
