/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:25:04 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/01/24 11:25:06 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_numlen(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ret;
	long	ln;
	int		size;

	ln = n;
	size = ft_numlen(ln);
	ret = malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	ret[size] = '\0';
	if (ln == 0)
		ret[size - 1] = '0';
	if (ln < 0)
	{
		ret[0] = '-';
		ln *= -1;
	}
	while (ln)
	{
		ret[size - 1] = ln % 10 + '0';
		ln /= 10;
		size--;
	}
	return (ret);
}
