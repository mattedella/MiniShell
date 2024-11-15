/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:40 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:44:42 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**export(t_shell *shell, char *str, char **envp)
{
	t_index	id;
	char	**tmp;

	id.i = -1;
	tmp = ft_calloc(sizeof(char *) * (matlen(envp) + 2));
	if (str == NULL)
	{
		while (envp[++id.i])
			printf("declare -x %s\n", envp[id.i]);
		return (envp);
	}
	if (check_char(str) == 2)
	{
		upgrade_var(str, tmp, envp);
		return (tmp);
	}
	else if (check_char(str) == 0)
	{
		update_var(str, tmp, envp);
		return (tmp);
	}
	else
		printf ("export: `%s': not a valid identifier\n", str);
	shell->flag = 3;
	return (envp);
}

int	print_env(char **envp, int fd)
{
	t_index	id;

	id.i = -1;
	while (envp[++id.i])
	{
		if (ft_strchr(envp[id.i], '=') == 0
			&& envp[id.i][ft_strlen(envp[id.i]) - 1] != '=')
		{
			ft_putstr(envp[id.i]);
			ft_putchar_fd('\n', fd);
		}
	}
	return (0);
}

int	pwd(void)
{
	char	s[200];

	if (getcwd(s, 200) != NULL)
		printf("%s\n", getcwd(s, 200));
	else
		printf("%s\n", getenv("PWD"));
	return (0);
}

int	unset(t_shell *shell, char *args, char **envp)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (my_isalnum(args) == 1)
	{
		printf("unset: '%s': not a valid identifier\n", args);
		shell->flag = 3;
		return (0);
	}
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], args, ft_strlen(args)) == 0)
		{
			j = 1;
			break ;
		}
	}
	if (j == 1)
		env_null(i, envp);
	return (0);
}

void	ft_cd(t_shell *shell, char *args)
{
	if (args == NULL || ft_strcmp(args, "~") == 0)
	{
		if (my_getenv(shell) == 0)
		{
			printf("minishell: cd: HOME not set\n");
			shell->flag = 3;
			return ;
		}
		chdir(getenv("HOME"));
		return ;
	}
	else if (chdir(args) == -1)
	{
		printf(" cd: %s: No such file or directory\n", args);
		shell->flag = 3;
		return ;
	}
	return ;
}
