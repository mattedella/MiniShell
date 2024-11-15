/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:47:26 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:47:28 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	close_out(t_shell *shell, int pos, int i)
{
	if (shell->cmd[i].out[pos] != NULL)
		shell->cmd[i].out[pos] = NULL;
	close(shell->cmd[i].fd[i]);
	return (0);
}

int	copy_infile(t_shell *shell, int i, int *j)
{
	t_echo	a;

	a.apex = 0;
	a.j = *j;
	shell->cmdtab[i][a.j] = ' ';
	check_space(shell, &a.j, i);
	if (shell->cmdtab[i][a.j] == 34 || shell->cmdtab[i][a.j] == 39)
		a.apex = 1;
	shell->cmd[i].in[0] = copy_redirect(shell, i, a.j);
	shell->cmd[i].fd[0] = open(shell->cmd[i].in[0], O_RDONLY);
	*j = a.j;
	if (shell->cmd[i].fd[0] < 0)
		return (ft_print(shell, "Permission denied or non-existent file", 1));
	if (shell->cmd[i].in[1] != NULL)
		shell->cmd[i].in[1] = NULL;
	close(shell->cmd[i].fd[0]);
	return (0);
}

int	copy_heredoc(t_shell *shell, int i, int *j)
{
	t_echo	a;
	char	*limiter;

	a.j = *j;
	a.apex = 0;
	while (a.j < *j + 2)
		shell->cmdtab[i][a.j++] = ' ';
	check_space(shell, &a.j, i);
	if (shell->cmdtab[i][a.j] == '>' || shell->cmdtab[i][a.j] == '<')
		return (ft_print(shell, "parse error near '<'", 1));
	check_here_flag(shell, i);
	if (shell->cmdtab[i][a.j] == 34 || shell->cmdtab[i][a.j] == 39)
	{
		a.apex = 1;
		shell->cmdtab[i][a.j++] = ' ';
	}
	limiter = copy_redirect(shell, i, a.j);
	limiter = apex_trim(limiter);
	if (limiter[0] == '\0')
		return (ft_print(shell, "syntax error near unexpected token `<<'", 2));
	*j = a.j;
	create_heredoc(limiter, n_doc(), shell, i);
	if (shell->cmd[i].in[0] != NULL)
		shell->cmd[i].in[0] = NULL;
	return (0);
}

int	copy_outfile(t_shell *shell, int i, int *j)
{
	t_echo	a;

	a.apex = 0;
	a.j = *j;
	shell->cmdtab[i][a.j] = ' ';
	check_space(shell, &a.j, i);
	if (shell->cmdtab[i][a.j] == '>' || shell->cmdtab[i][a.j] == '<')
		return (ft_print(shell, "parse error near '>'", 2));
	if (shell->cmdtab[i][a.j] == 34 || shell->cmdtab[i][a.j] == 39)
		a.apex = 1;
	shell->cmd[i].out[0] = copy_redirect(shell, i, a.j);
	shell->cmd[i].fd[i] = open(shell->cmd[i].out[0],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	*j = a.j;
	if (open(shell->cmd[i].out[0], O_DIRECTORY, 0644) != -1
		|| shell->cmd[i].fd[i] < 0)
		return (check_fd(shell, i, 0));
	if (shell->cmd[i].fd[i] < 0)
		return (ft_print(shell, "Permission denied", 1));
	return (close_out(shell, 1, i));
}

int	copy_append(t_shell *shell, int i, int *j)
{
	t_echo	a;

	a.apex = 0;
	a.j = *j;
	while (a.j < *j + 2)
		shell->cmdtab[i][a.j++] = ' ';
	check_space(shell, &a.j, i);
	if (shell->cmdtab[i][a.j] == '>' || shell->cmdtab[i][a.j] == '<')
		return (ft_print(shell, "parse error near '>'", 2));
	if (shell->cmdtab[i][a.j] == 34 || shell->cmdtab[i][a.j] == 39)
		a.apex = 1;
	shell->cmd[i].out[1] = copy_redirect(shell, i, a.j);
	shell->cmd[i].fd[i] = open(shell->cmd[i].out[1],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (open(shell->cmd[i].out[1], O_DIRECTORY, 0644) != -1
		|| shell->cmd[i].fd[i] < 0)
		return (check_fd(shell, i, 1));
	*j = a.j;
	if (shell->cmd[i].fd[i] < 0)
		return (ft_print(shell, "Permission denied", 1));
	return (close_out(shell, 0, i));
}
