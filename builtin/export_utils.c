/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:45:02 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:45:05 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_idchar(char *args, char c)
{
	t_index	id;

	id.i = 0;
	while (args[id.i])
	{
		if (args[id.i] == c)
			return (id.i);
		id.i++;
	}
	return (-1);
}

char	*ft_var_update(char *args, int *j)
{
	t_index	id;
	char	*envp;

	id.i = 0;
	id.k = 0;
	envp = ft_calloc(ft_strlen(args) + 1);
	while (args[id.i])
	{
		if (args[id.k] == '\'' || args[id.k] == '\"')
			id.k++;
		envp[id.i] = args[id.k];
		id.i++;
		id.k++;
	}
	*j = 0;
	envp[id.i] = '\0';
	return (envp);
}

void	add_env(char *str, char **envp, int i, int *j)
{
	int	k;

	k = 0;
	while (str[++*j])
	{
		if (str[k] == '\'' || str[k] == '\"')
			k++;
		envp[i][*j] = str[k++];
	}
}

static char	*ft_check_var_2(char *str, int i, t_shell *shell, t_index id)
{
	char	*res;

	res = NULL;
	while (str[++id.j])
	{
		if (str[id.j] == '$' && (ft_isalpha(str[id.j + 1]) == 1
				|| str[id.j + 1] == 34 || str[id.j + 1] == 39))
		{
			while (shell->env[i])
			{
				if (ft_strncmp(shell->env[i], id.var, id.k) == 0
					&& shell->env[i][id.k] == '=')
				{
					res = ft_strdup(shell->env[i] + id.k + 1, 0);
					break ;
				}
				i++;
			}
		}
		else if (str[id.j] == '$' && ft_isalpha(str[id.j + 1]) == 0)
			break ;
	}
	return (res);
}

char	*ft_check_var(char *str, int i, t_shell *shell)
{
	t_index	id;

	id.k = get_len(str, i);
	id.var = ft_calloc(id.k + 1);
	id.j = -1;
	if (!id.var)
		return (NULL);
	ft_strncpy(id.var, str + i, id.k);
	id.var[id.k] = '\0';
	i = 0;
	return (ft_check_var_2(str, i, shell, id));
}
