/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:29 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:44:29 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*export_var(char *str)
{
	char	*dup;
	int		i;
	int		j;

	j = 0;
	i = -1;
	dup = (char *)ft_calloc(ft_strlen((char *)str) + 1);
	if (!dup)
		return (NULL);
	while (str[++i] != '\0')
	{
		if (str[i] == '+')
			i++;
		dup[j] = str[i];
		j++;
	}
	return (dup);
}

void	*upgrade_var(char *str, char **tmp, char **envp)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (envp[++i])
	{
		tmp[i] = ft_strdup(envp[i], 2);
		if (ft_strncmp(tmp[i], str, ft_name(str)) == 0)
		{
			if (ft_strchr(tmp[i], '='))
				tmp[i] = ft_strjoin(tmp[i], "=");
			tmp[i] = ft_strjoin(tmp[i], str + (ft_name(str) + 2));
			j = 1;
		}
	}
	if (j != 1)
	{
		tmp[i] = export_var(str);
		tmp[i + 1] = NULL;
	}
	return (tmp);
}

void	*update_var(char *str, char **tmp, char **envp)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], str, ft_name(str)) == 0)
			tmp[i] = ft_var_update(str, &j);
		else
			tmp[i] = ft_strdup(envp[i], 2);
	}
	if (j != 0)
	{
		tmp[i] = ft_strdup(str, 2);
		tmp[i + 1] = NULL;
	}
	return (tmp);
}

int	check_builtin2(t_shell *shell, int i, int j)
{
	if (ft_strcmp(shell->cmd[i].scmd->args[j], "export") == 0)
	{
		if (shell->cmd[i].scmd->args[j + 1] == NULL)
		{
			shell->env = export(shell, NULL, shell->env);
			return (0);
		}
		while (shell->cmd[i].scmd->args[++j])
			shell->env = export(shell, shell->cmd[i].scmd->args[j], shell->env);
		return (0);
	}
	if (ft_strcmp(shell->cmd[i].scmd->args[j], "unset") == 0)
	{
		while (shell->cmd[i].scmd->args[++j])
			unset(shell, shell->cmd[i].scmd->args[j], shell->env);
		return (0);
	}
	if (ft_strcmp(shell->cmd[i].scmd->args[j], "cd") == 0)
		return (0);
	if (ft_strcmp(shell->cmd[i].scmd->args[j], "exit") == 0)
		return (0);
	return (1);
}

int	check_builtin1(t_shell *shell, int i, int j, int fd)
{
	if (ft_strcmp(shell->cmd[i].scmd->args[j], "echo") == 0)
	{
		if (shell->cmd[i].scmd->args[j + 1]
			&& minusn_finder(shell->cmd[i].scmd->args[j + 1]) == 0)
		{
			j++;
			ft_echo(shell->cmd[i].scmd->args, shell, 1, fd);
		}
		else
		{
			ft_echo(shell->cmd[i].scmd->args, shell, 0, fd);
			ft_putchar_fd('\n', fd);
		}
		return (0);
	}
	if (ft_strcmp(shell->cmd[i].scmd->args[j], "env") == 0)
		return (print_env(shell->env, fd));
	if (ft_strcmp(shell->cmd[i].scmd->args[j], "pwd") == 0)
		return (pwd());
	return (check_builtin2(shell, i, j));
}
