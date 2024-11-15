/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:45:39 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:45:44 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_apexlen(char *str)
{
	t_echo	id;

	id.i = 0;
	id.j = 0;
	id.apex = 0;
	while (str[id.i] && str[id.i] != ' ')
	{
		if ((str[id.i] == '\"' || str[id.i] == '\'') && id.apex == 0)
		{
			id.apex = str[id.i];
			id.i++;
		}
		else if (str[id.i] == id.apex)
		{
			id.apex = 0;
			id.i++;
		}
		else
		{
			id.i++;
			id.j++;
		}
	}
	id.j += ft_strlen(str + id.i);
	return (id.j);
}

int	init_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (get_len(str, i + 1));
		i++;
	}
	return (0);
}

static void	expand_var_2(char *str, t_shell *shell, int i, int j)
{
	char	*tmp;

	tmp = ft_strdup(shell->cmdtab[i], 2);
	if (str[j + 1] == '?')
	{
		shell->cmdtab[i] = ft_substitute_error(tmp,
				ft_itoa(shell->exit_status));
	}
	else
	{
		shell->cmdtab[i] = ft_substitute(tmp,
				ft_check_var(str, ++j, shell));
	}
}

void	expand_var(char **tmp, t_shell *shell)
{
	t_echo	d;

	d.i = 0;
	d.apex = 0;
	while (tmp[d.i])
	{
		d.j = -1;
		while (tmp[d.i][++d.j])
		{
			if (d.apex == 0 && check_apex(tmp[d.i][d.j]))
				d.apex = tmp[d.i][d.j];
			else if (check_apex(tmp[d.i][d.j]) && d.apex == tmp[d.i][d.j])
				d.apex = 0;
			else if (tmp[d.i][d.j] == '$' && (ft_isalpha(tmp[d.i][d.j + 1])
					|| tmp[d.i][d.j + 1] == '?')
					&& (d.apex == '"' || d.apex == 0))
				expand_var_2(tmp[d.i], shell, d.i, d.j);
		}
		d.i++;
	}
}
