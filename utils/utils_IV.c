/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_IV.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:48:05 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:48:07 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = -1;
	dup = (char *)ft_calloc(ft_strlen((char *)s) + 2);
	if (!dup)
		return (NULL);
	while (s[++i] != '\0')
		dup[i] = s[i];
	return (dup);
}

void	check_here_flag(t_shell *shell, int i)
{
	char	apex;
	int		j;

	apex = 0;
	j = 0;
	while (shell->cmdtab[i][j])
	{
		if ((shell->cmdtab[i][j] == 34 || shell->cmdtab[i][j] == 39)
			&& apex == 0)
		{
			apex = shell->cmdtab[i][j];
			j++;
		}
		if (shell->cmdtab[i][j] == apex
			&& (shell->cmdtab[i][j] == 34 || shell->cmdtab[i][j] == 39))
		{
			shell->here_flag = 1;
			return ;
		}
		else
			j++;
	}
	shell->here_flag = 0;
}

void	close_fd(int **fd, int n_cmd)
{
	int	i;

	i = 0;
	while (i < n_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

int	is_digit_3(char *str, int flag)
{
	int	i;

	i = 0;
	if (flag)
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*copy_redirect(t_shell *shell, int i, int j)
{
	t_echo	d;

	d.i = 0;
	d.apex = 0;
	d.res = (char *)ft_calloc(ft_strlen((char *)shell->cmdtab[i]) + 1);
	while (shell->cmdtab[i][j] != '\0')
	{
		if (check_apex(shell->cmdtab[i][j])
			&& d.apex == shell->cmdtab[i][j])
		{
			d.apex = 0;
			shell->cmdtab[i][j++] = ' ';
		}
		if (d.apex == 0 && check_apex(shell->cmdtab[i][j]))
		{
			d.apex = shell->cmdtab[i][j];
			shell->cmdtab[i][j++] = ' ';
		}
		if (d.apex == 0 && shell->cmdtab[i][j] == ' ')
			return (d.res);
		d.res[d.i++] = shell->cmdtab[i][j];
		shell->cmdtab[i][j] = ' ';
		j++;
	}
	return (d.res);
}
