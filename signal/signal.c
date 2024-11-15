/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:47:40 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:47:43 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_sigflag = SIGINT;
		*exit_status() = 130;
		garbage_collector_free(1);
		exit (130);
	}
}

void	ctrl_executor(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_sigflag = SIGINT;
	}
}
