/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_V.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:29:01 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/07 12:29:01 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len(char *str, int i)
{
	int	start;

	start = i;
	while (str[i] && str[i] != ' ' && str[i] != 39 && str[i] != 34
		&& str[i] != '$' && str[i] != '_' && str[i] != '='
		&& str[i] != '-' && str[i] != '+')
		i++;
	return (i - start);
}

void	check_num(t_shell *shell, int i, int j)
{
	int	k;

	k = 0;
	if (shell->cmd[i].scmd->args[j] != NULL)
	{
		while (shell->cmd[i].scmd->args[j][k])
			k++;
	}
	if (k >= 18)
	{
		if (ft_strncmp(shell->cmd[i].scmd->args[j], "9223372036854775807", 20)
			< 0)
		{
			ft_print(shell, "exit: numeric argument required", 1);
			ft_quit(shell, 2, 0);
		}
	}
}

void	env_null(int i, char **envp)
{
	while (envp[i + 1])
	{
		envp[i] = ft_strdup(envp[i + 1], 0);
		i++;
	}
	envp[i] = NULL;
}
