/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:47:35 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:47:37 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sighandle_command(int signal)
{
	if (signal == SIGINT)
	{
		g_sigflag = SIGINT;
		write(1, "\n", 1);
	}
	else if (signal == SIGQUIT)
	{
		g_sigflag = SIGQUIT;
		write(1, "Quit (core dumped)\n", 20);
	}
}

void	ctrl_c(int sig)
{
	*exit_status() = 130;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sigflag = SIGINT;
	}
}

void	ctrl_d(int sig)
{
	(void)sig;
	g_sigflag = SIGTERM;
	*exit_status() = 131;
	write(1, "exit\n", 5);
	exit(0);
}

void	ctrl_bslash(int sig)
{
	if (sig == SIGQUIT)
	{
		g_sigflag = SIGQUIT;
		*exit_status() = 131;
		write(2, "Quit (core dumped)\n", 19);
	}
}
