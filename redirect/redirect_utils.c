/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:47:19 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:47:21 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redirect_output(t_shell *shell, int i, int *j)
{
	t_index	id;

	id.j = *j + 1;
	id.flag = 0;
	while (--id.j >= 0)
	{
		if (id.flag == 0 && check_apex(shell->cmdtab[i][id.j]))
			id.flag = shell->cmdtab[i][id.j];
		else if (check_apex(shell->cmdtab[i][id.j])
			&& id.flag == shell->cmdtab[i][id.j])
			id.flag = 0;
	}
	if (shell->cmdtab[i][*j + 1] == '>')
	{
		if (copy_append(shell, i, j) == 1)
			return (1);
	}
	else
	{
		if (id.flag != 0)
			return (0);
		if (copy_outfile(shell, i, j) == 1)
			return (1);
	}
	return (0);
}

static int	redirect_input(t_shell *shell, int i, int *j)
{
	t_index	id;

	id.j = *j + 1;
	id.flag = 0;
	while (--id.j >= 0)
	{
		if (id.flag == 0 && check_apex(shell->cmdtab[i][id.j]))
			id.flag = shell->cmdtab[i][id.j];
		else if (check_apex(shell->cmdtab[i][id.j])
			&& id.flag == shell->cmdtab[i][id.j])
			id.flag = 0;
	}
	if (shell->cmdtab[i][*j + 1] == '<' && id.flag == 0)
	{
		if (copy_heredoc(shell, i, j) == 1)
			return (1);
	}
	else
	{
		if (id.flag != 0)
			return (0);
		if (copy_infile(shell, i, j) == 1)
			return (1);
	}
	return (0);
}

int	check_infile_outfile(t_shell *shell)
{
	t_index	id;

	id.i = -1;
	id.k = 0;
	id.x = 0;
	id.flag = 0;
	while (shell->cmdtab[++id.i])
	{
		id.j = -1;
		while (shell->cmdtab[id.i][++id.j])
		{
			if (id.flag == shell->cmdtab[id.i][id.j])
				id.flag = 0;
			else if (shell->cmdtab[id.i][id.j] == 34
				|| shell->cmdtab[id.i][id.j] == 39)
				id.flag = (int)shell->cmdtab[id.i][id.j];
			if (shell->cmdtab[id.i][id.j] == '<' && id.flag == 0)
				id.k = redirect_input(shell, id.i, &id.j);
			else if (shell->cmdtab[id.i][id.j] == '>' && id.flag == 0)
				id.x = redirect_output(shell, id.i, &id.j);
			if (id.k == 1 || id.x == 1)
				return (1);
		}
	}
	return (0);
}

int	ft_print(t_shell *shell, char *str, int quit)
{
	*exit_status() = quit;
	shell->exit_status = *exit_status();
	shell->flag = 2;
	printf("minishell: %s\n", str);
	return (1);
}

int	check_fd(t_shell *shell, int i, int fd)
{
	if (open(shell->cmd[i].out[fd], O_DIRECTORY) != -1)
	{
		printf("minishell: %s is a directory\n", shell->cmd[i].out[fd]);
		return (1);
	}
	if (shell->cmd[i].fd[i] < 0)
		return (ft_print(shell, "Permission denied", 1));
	return (0);
}
