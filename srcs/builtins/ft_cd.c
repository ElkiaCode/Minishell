/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:31:33 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/23 22:31:34 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_oldpwd(t_global *data)
{
	t_env	*curr;
	char	*oldpwd;

	curr = data->env;
	while (curr)
	{
		if (!ft_strncmp(curr->name, "PWD", INT_MAX))
		{
			oldpwd = ft_strdup(curr->value);
			update_env(data, "OLDPWD", oldpwd);
			free(oldpwd);
			return ;
		}
		curr = curr->next;
	}
}

void	update_pwd(t_global *data, char *path)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	update_oldpwd(data);
	if (!getcwd(cwd, PATH_MAX))
	{
		perror(path);
		return ;
	}
	pwd = ft_strdup(cwd);
	if (!pwd)
		return ;
	update_env(data, "PWD", pwd);
	free(pwd);
}

int	ft_cd(t_global *data, char **args)
{
	int	status;

	if (count_args(args) == 2)
	{
		status = chdir(args[1]);
		if (!status)
			update_pwd(data, args[1]);
		else if (status == -1)
		{
			perror(args[1]);
			status = 1;
		}
		return (status);
	}
	return (1);
}
