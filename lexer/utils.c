/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:46:50 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:46:52 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_tabdup(char **tab, char **new)
{
	int	i;

	i = -1;
	while (tab[++i])
		new[i] = my_strdup(tab[i]);
	return (new);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	command_not_found(t_shell *shell, char *str)
{
	printf("%s: command not found\n", str);
	shell->flag = 1;
	return (1);
}

char	*apex_trim(char *str)
{
	t_echo	d;

	d.i = 0;
	d.j = 0;
	d.apex = 0;
	d.res = ft_calloc(ft_apexlen(str) + 1);
	while (str[d.i])
	{
		if ((str[d.i] == 34 || str[d.i] == 39)
			&& (d.apex == str[d.i] || d.apex == 0))
		{
			if (d.apex == 0)
				d.apex = str[d.i++];
			else if (d.apex != 0 && str[d.i] == d.apex)
				apex_reset(&d.apex, &d.i);
			if ((str[d.i] == 34 || str[d.i] == 39) && d.apex == 0)
				d.apex = str[d.i++];
			else if ((str[d.i] == 34 || str[d.i] == 39)
				&& d.apex == str[d.i])
				apex_reset(&d.apex, &d.i);
		}
		else
			d.res[d.j++] = str[d.i++];
	}
	return (d.res);
}

char	**get_env(char **envp)
{
	int		i;
	char	**mat;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			mat = ft_split(envp[i] + 5, ':');
			return (mat);
		}
		i++;
	}
	return (NULL);
}
