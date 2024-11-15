/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:47:13 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:47:15 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*readline_heredoc(char *str, t_shell *shell, int fd)
{
	char	*line;

	line = readline(str);
	if (is_valid_line(line, 1))
		shell->flag = 0;
	if (!line)
	{
		printf("exit\n");
		close(fd);
		ft_quit(shell, shell->exit_status, 0);
	}
	ft_lstadd_front(garbage_collector(), ft_lstnew(line));
	return (line);
}
