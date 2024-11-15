/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:46:05 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:46:07 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_path5(t_shell *shell, int i, int j)
{
	if (ft_strcmp(shell->cmd[i].scmd->args[j], "unset") == 0)
	{
		if (shell->cmdtab[i + 1] == NULL)
		{
			while (shell->cmd[i].scmd->args[++j])
				unset(shell, shell->cmd[i].scmd->args[j], shell->env);
		}
		return (50);
	}
	return (1);
}

static int	check_path4(t_shell *shell, int i, int j)
{
	if (ft_strcmp(shell->cmd[i].scmd->args[j], "export") == 0)
	{
		if (shell->cmdtab[i + 1] == NULL)
		{
			if (shell->cmd[i].scmd->args[j + 1] == NULL)
			{
				shell->env = export(shell, NULL, shell->env);
				return (0);
			}
			while (shell->cmd[i].scmd->args[++j])
				shell->env
					= export(shell, shell->cmd[i].scmd->args[j], shell->env);
			return (50);
		}
		return (0);
	}
	return (check_path5(shell, i, j));
}

static int	check_path3(t_shell *shell, int i, int j)
{
	if (ft_strcmp(shell->cmd[i].scmd->args[j], "exit") == 0
		&& exit_handler(shell->cmd[i].scmd->args[++j], 0) != -1)
	{
		if (shell->cmdtab[1] == NULL)
		{
			check_num(shell, i, j);
			if (shell->cmd[i].scmd->args[j] == NULL)
				ft_quit(shell, 0, 0);
			else if (shell->cmd[i].scmd->args[j + 1] == NULL
				|| (is_digit_2(shell->cmd[i].scmd->args[j])))
				ft_quit(shell, exit_handler(shell->cmd[i].scmd->args[j], 1), 0);
			else
				shell->flag = print_exit_error(1);
			return (0);
		}
		return (0);
	}
	return (check_path4(shell, i, j));
}

static int	check_path2(t_shell *shell, int i, int j)
{
	if (ft_strcmp(shell->cmd[i].scmd->args[j], "cd") == 0)
	{
		if (shell->cmdtab[1] == NULL)
		{
			if (matlen(shell->cmd[i].scmd->args) > 2)
			{
				printf("minishell: cd: too many arguments\n");
				shell->flag = 3;
				return (50);
			}
			ft_cd(shell, shell->cmd[i].scmd->args[++j]);
			shell->env = copy_pwd(shell->env);
		}
		return (0);
	}
	return (check_path3(shell, i, j));
}

int	check_path(t_shell *shell, int i, int j)
{
	if (ft_strcmp(shell->cmd[i].scmd->args[j], "echo") == 0)
		return (0);
	else if (ft_strcmp(shell->cmd[i].scmd->args[j], "pwd") == 0)
		return (0);
	else if (ft_strcmp(shell->cmd[i].scmd->args[j], "env") == 0)
		return (0);
	if (shell->cmd[i].scmd->path)
		return (0);
	return (check_path2(shell, i, j));
}
