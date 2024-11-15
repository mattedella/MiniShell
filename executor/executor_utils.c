/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:45:14 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:45:16 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_fd(t_shell *shell, int *fd_in, int *fd_out, int i)
{
	if (shell->cmd[i].in[0] != NULL)
	{
		*fd_in = open(shell->cmd[i].in[0], O_RDONLY, 0644);
		if (*fd_in < 0)
			return ;
	}
	if (shell->cmd[i].in[1] != NULL)
	{
		*fd_in = open(shell->cmd[i].in[1], O_RDONLY, 0644);
		if (*fd_in < 0)
			return ;
	}
	if (shell->cmd[i].out[0] != NULL)
	{
		*fd_out = open(shell->cmd[i].out[0], O_WRONLY | O_TRUNC, 0644);
		if (*fd_out < 0)
			return ;
	}
	if (shell->cmd[i].out[1] != NULL)
	{
		*fd_out = open(shell->cmd[i].out[1], O_WRONLY | O_APPEND, 0644);
		if (*fd_out < 0)
			return ;
	}
}

void	get_builtin(t_shell *shell, int i, int fd_out, int **fd)
{
	if (fd_out != 1)
	{
		if (check_builtin1(shell, i, 0, fd_out) == 0)
		{
			close(fd[i][1]);
			close(fd[i][0]);
			ft_quit(shell, 0, 0);
		}
	}
	else
	{
		if (check_builtin1(shell, i, 0, fd[i][1]) == 0)
		{
			close(fd[i][1]);
			close(fd[i][0]);
			ft_quit(shell, 0, 0);
		}
	}
}

int	update_flag_pipex(t_shell *shell)
{
	if (shell->flag == 1)
	{
		shell->flag = 0;
		return (1);
	}
	if (shell->exit_status == 2)
		shell->flag = 2;
	return (0);
}
