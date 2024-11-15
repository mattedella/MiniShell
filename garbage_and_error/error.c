/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:45:51 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:45:51 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(t_shell *shell, int id, int flag)
{
	(void)flag;
	shell->exit_status = id;
	garbage_collector_free(0);
	perror("Error");
	exit(id);
}

void	ft_exit(int id)
{
	write(2, "Error\n", 6);
	exit (id);
}

void	ft_quit(t_shell *shell, int quit, int flag)
{
	garbage_collector_free(flag);
	(void)shell;
	*exit_status() = quit;
	exit(quit);
}

int	*exit_status(void)
{
	static int	g_exit_status = 0;

	return (&g_exit_status);
}
