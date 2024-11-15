/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:48:24 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:48:26 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigflag;

void	init_all(t_shell *shell)
{
	shell->path = NULL;
	shell->env = NULL;
	shell->cmdtab = NULL;
	shell->line = NULL;
	shell->exit_status = 0;
	shell->flag = 0;
	shell->here_flag = 0;
}

t_shell	*init_shell(void)
{
	t_shell	*shell;

	shell = ft_calloc(sizeof(t_shell));
	if (!shell)
		ft_exit(1);
	init_all(shell);
	return (shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;

	argc += 0;
	argv += 0;
	if (argc > 1)
		ft_exit(0);
	shell = init_shell();
	shell->env = env_copy(envp);
	shell->line = ft_readline(ORANGE "minishell$ " DEFAULT, shell);
	while (shell->line)
	{
		g_sigflag = 0;
		*exit_status() = 0;
		signal(SIGQUIT, ctrl_bslash);
		if (shell->line[0] != '\0')
			add_history(shell->line);
		if (is_valid_line(shell->line, 1))
			lexer(shell);
		shell->line = ft_readline(ORANGE "minishell$ " DEFAULT, shell);
	}
	ft_quit(shell, 1, 0);
	return (0);
}
