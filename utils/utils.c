/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:48:13 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:48:15 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	matlen(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
		i++;
	return (i);
}

char	**env_copy(char **envp)
{
	int		i;
	int		j;
	char	**env_copy;

	i = 0;
	j = 0;
	env_copy = (char **)ft_calloc(sizeof(char *) * (matlen(envp) + 1));
	while (envp[i])
	{
		j = 0;
		env_copy[i] = (char *)ft_calloc(sizeof(char)
				* (ft_strlen(envp[i]) + 1));
		while (envp[i][j])
		{
			env_copy[i][j] = envp[i][j];
			j++;
		}
		env_copy[i][j] = '\0';
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

size_t	ft_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	return (i);
}

unsigned char	wait_and_free(pid_t *pid, int n_cmd)
{
	unsigned char	ret;
	int				status;
	int				i;

	i = 0;
	signal(SIGINT, ctrl_executor);
	signal(SIGTERM, SIG_IGN);
	while (i < n_cmd)
	{
		if (wait4(pid[i], &status, WUNTRACED, NULL) > 0)
		{
			if (WIFEXITED(status))
				ret = (WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				ret = (WTERMSIG(status) + 128);
		}
		else
			ret = 0;
		i++;
	}
	return (ret);
}

int	print_exit_error(int f)
{
	if (f == 1)
	{
		printf("minishell: exit: too many arguments\n");
		return (3);
	}
	else
		printf("minishell: exit: numeric argument required\n");
	return (2);
}
