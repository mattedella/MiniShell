/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:48:20 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:48:21 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*valid_command(char **command, char **env)
{
	int		i;
	char	*tmp;
	char	*command2;

	i = -1;
	if (ft_strnstr(command[0], "./", 2))
		return (command[0]);
	if (ft_strnstr(command[0], "/bin", 4))
		return (command[0]);
	if (!env)
		return (NULL);
	command2 = ft_strjoin("/", command[0]);
	while (env[++i])
	{
		if (ft_strnstr(command2, "//bin", 5))
			tmp = ft_strjoin(env[i], command2 + 5);
		else
			tmp = ft_strjoin(env[i], command2);
		if (access(tmp, F_OK) == 0)
			return (tmp);
	}
	return (NULL);
}

void	check_exit(t_shell *shell)
{
	if (g_sigflag == SIGINT)
	{
		shell->exit_status = 130;
		shell->flag = 2;
	}
	if (g_sigflag == SIGTERM)
	{
		shell->exit_status = 131;
		shell->flag = 2;
	}
	if (shell->flag == 1)
		shell->exit_status = 127;
	else if (shell->flag == 2)
		return ;
	else if (shell->flag == 3)
		shell->exit_status = 1;
	else
		shell->exit_status = 0;
}

char	*ft_readline(char *str, t_shell *shell)
{
	char	*line;

	line = NULL;
	signal(SIGINT, ctrl_c);
	signal(SIGTERM, ctrl_d);
	signal(SIGQUIT, SIG_IGN);
	line = readline(str);
	check_exit(shell);
	if (is_valid_line(line, 0))
		shell->flag = 0;
	if (!line)
	{
		printf("exit\n");
		ft_quit(shell, shell->exit_status, 0);
	}
	ft_lstadd_front(garbage_collector(), ft_lstnew(line));
	return (line);
}

int	is_valid_line(char *line, int flag)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if (line[0] == '|')
	{
		if (flag)
			printf("minishell$: syntax error near unexpected token `|' \n");
		return (0);
	}
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	is_a_really_valid_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}
