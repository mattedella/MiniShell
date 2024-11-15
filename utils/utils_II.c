/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_II.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:47:54 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:47:56 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

char	**copy_pwd(char **env)
{
	t_index	id;
	char	**ret;
	char	tmp[200];

	id.i = -1;
	ret = (char **)ft_calloc(sizeof(char *) * (matlen(env) + 1));
	while (env[++id.i])
	{
		if (ft_strncmp(env[id.i], "PWD", 3) == 0)
		{
			if (getcwd(tmp, 200) != NULL)
				ret[id.i] = ft_strjoin("PWD=", getcwd(tmp, 200));
		}
		else
			ret[id.i] = ft_strdup(env[id.i], 0);
	}
	ret[id.i] = NULL;
	return (ret);
}

void	check_space(t_shell *shell, int *j, int i)
{
	int	x;

	x = *j;
	while ((shell->cmdtab[i][x] == ' ' || shell->cmdtab[i][x] == '\t')
		&& shell->cmdtab[i][x] != 34 && shell->cmdtab[i][x] != 39)
		x++;
	*j = x;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	my_getenv(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], "HOME=", 5))
			return (1);
		i++;
	}
	return (0);
}
