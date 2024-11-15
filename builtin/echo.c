/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:55 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:44:57 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	apex_reset(char *apex, int *i)
{
	*apex = 0;
	(*i)++;
}

int	check_apex(char args)
{
	if (args == 34 || args == 39)
		return (1);
	return (0);
}

void	ft_echo(char **args, t_shell *shell, int flag, int fd)
{
	t_echo	e;

	(void)shell;
	e.j = 0;
	e.apex = 0;
	if (flag == 1)
		minusn_check(args, &e.j);
	while (args[++e.j])
	{
		e.i = 0;
		while (args[e.j][e.i])
			ft_putchar_fd(args[e.j][e.i++], fd);
		if (args[e.j + 1])
			ft_putchar_fd(' ', fd);
	}
}
