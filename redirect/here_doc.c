/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:47:08 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:47:10 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*n_doc(void)
{
	static int	n_doc = 0;

	return (&n_doc);
}

int	create_heredoc_parent(int pid, int *status, int fd)
{
	int	ex_status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait4(pid, status, WUNTRACED, NULL);
	signal(SIGINT, sighandle_command);
	signal(SIGQUIT, sighandle_command);
	close(fd);
	if (WIFEXITED(*status))
	{
		ex_status = WEXITSTATUS(*status);
		if (ex_status == 130)
		{
			g_sigflag = SIGINT;
			return (0);
		}
		return (1);
	}
	*exit_status() = errno;
	return (0);
}

void	heredoc_signal_exit(int fd, int id)
{
	close(fd);
	garbage_collector_free(0);
	exit(id);
}

void	get_doc(char *limiter, int fd, t_shell *shell)
{
	char	*line;

	signal(SIGINT, ctrl_heredoc);
	signal(SIGQUIT, SIG_IGN);
	line = readline_heredoc(">", shell, fd);
	if (line == NULL)
		heredoc_signal_exit(fd, 1);
	while (ft_strcmp(line, limiter) != 0)
	{
		if (shell->here_flag != 1)
			line = expand_varline(line, shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		line = readline_heredoc(">", shell, fd);
		if (line == NULL)
			heredoc_signal_exit(fd, 1);
	}
	close(fd);
	free_heredoc();
	exit(1);
}

int	create_heredoc(char *limiter, int *n_doc, t_shell *shell, int i)
{
	int		fd;
	int		exit;
	int		pid;
	int		status;

	shell->cmd[i].in[1] = ft_strjoin("./tmp/heredoc", ft_itoa(*n_doc));
	fd = open(shell->cmd[i].in[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	(*n_doc)++;
	pid = fork();
	if (pid == 0)
		get_doc(limiter, fd, shell);
	else
	{
		exit = create_heredoc_parent(pid, &status, fd);
		return (exit);
	}
	return (0);
}
