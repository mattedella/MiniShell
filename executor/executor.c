/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:45:21 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:45:24 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_one_command(t_shell *shell)
{
	t_filefd	filefd;

	filefd.in = 0;
	filefd.out = 1;
	redirect_fd(shell, &filefd.in, &filefd.out, 0);
	if (filefd.in != 0)
		dup2(filefd.in, 0);
	if (filefd.out != 1)
		dup2(filefd.out, 1);
	if (check_builtin1(shell, 0, 0, filefd.out) == 0)
		ft_quit(shell, 0, 0);
	execve(shell->cmd[0].scmd->path, shell->cmd[0].scmd->args, shell->env);
	close(filefd.in);
	close(filefd.out);
	ft_quit(shell, 2, 0);
}

static void	execute_command(t_shell *shell, int i, int **fd)
{
	t_filefd	filefd;

	filefd.in = 0;
	filefd.out = 1;
	(void)(dup2(fd[i][1], 1) + close(fd[i][0]));
	redirect_fd(shell, &filefd.in, &filefd.out, i);
	if (filefd.in != 0)
		dup2(filefd.in, 0);
	else if (i != 0)
		(void)(dup2(fd[i - 1][0], 0) + close(fd[i - 1][1]));
	if (filefd.out != 1)
		dup2(filefd.out, 1);
	else if (i != 0)
		(void)(dup2(fd[i][1], 1) + close(fd[i][0]));
	get_builtin(shell, i, filefd.out, fd);
	if (!(valid_command(shell->cmd[i].scmd->args, shell->path)))
		ft_quit(shell, 127, 0);
	execve(shell->cmd[i].scmd->path, shell->cmd[i].scmd->args, shell->env);
	close(filefd.in);
	close(filefd.out);
	wait_and_free(0, 0);
	close_fd(fd, i);
	ft_quit(shell, 2, 0);
}

static void	execute_last_command(t_shell *shell, int i, int **fd)
{
	t_filefd	filefd;

	filefd.in = 0;
	filefd.out = 1;
	redirect_fd(shell, &filefd.in, &filefd.out, i);
	if (filefd.out != 1)
		dup2(filefd.out, 1);
	if (filefd.in != 0)
		dup2(filefd.in, 0);
	else
		(void)(dup2(fd[i - 1][0], 0) + close(fd[i - 1][1]));
	if (!check_builtin1(shell, i, 0, filefd.out))
	{
		close(fd[i -1][0]);
		ft_quit(shell, 0, 0);
	}
	if (!(valid_command(shell->cmd[i].scmd->args, shell->path)))
		ft_quit(shell, 127, 0);
	execve(shell->cmd[i].scmd->path, shell->cmd[i].scmd->args, shell->env);
	close(filefd.in);
	close(filefd.out);
	wait_and_free(0, 0);
	close_fd(fd, i);
	ft_quit(shell, 2, 0);
}

static void	pipex(t_shell *shell, int i, t_index p)
{
	p.i = -1;
	while (++p.i < i - 1)
	{
		if (pipe(p.fd[p.i]) == -1)
		{
			close_fd(p.fd, i);
			ft_error(shell, 6, 0);
		}
		p.pid[p.i] = fork();
		if (p.pid[p.i] == -1)
			ft_error(shell, 7, 0);
		if (p.pid[p.i] == 0)
			execute_command(shell, p.i, p.fd);
		if (p.i < i - 1)
			close(p.fd[p.i][1]);
	}
	p.pid[p.i] = fork();
	if (p.pid[p.i] == -1)
		ft_error(shell, 8, 0);
	if (p.pid[p.i] == 0)
		execute_last_command(shell, p.i, p.fd);
	shell->exit_status = wait_and_free(p.pid, i);
	close_fd(p.fd, i);
	if (update_flag_pipex(shell))
		return ;
}

void	executor(t_shell *shell, int i)
{
	t_index	p;

	p.j = -1;
	p.pid = (pid_t *)ft_calloc(sizeof(pid_t) * i);
	if (i != 1)
	{
		p.fd = ft_calloc(sizeof(int *) * i);
		while (++p.j < i - 1)
			p.fd[p.j] = ft_calloc(sizeof(int) * 2);
		p.fd[p.j] = NULL;
	}
	if (i == 1)
	{
		p.pid[0] = fork();
		if (p.pid[0] == 0)
			execute_one_command(shell);
		else
		{
			shell->exit_status = wait_and_free(p.pid, i);
			if (shell->exit_status != 0)
				shell->flag = 2;
		}
	}
	else
		pipex(shell, i, p);
}
