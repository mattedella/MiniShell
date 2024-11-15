/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:46:11 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 16:49:20 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_ncmd(char *line)
{
	int		i;
	int		ncmd;

	i = 0;
	ncmd = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|')
			ncmd++;
		i++;
	}
	return (ncmd + 1);
}

static void	init_redirect(t_shell *shell)
{
	int	i;

	i = 0;
	shell->cmd = (t_cmd *)ft_calloc(sizeof(t_cmd) * get_ncmd(shell->line) + 1);
	while (i < get_ncmd(shell->line))
	{
		shell->cmd[i].scmd = (t_simplecmd *)ft_calloc(sizeof(t_simplecmd) * 2);
		shell->cmd[i].scmd->path = NULL;
		shell->cmd[i].scmd->args = NULL;
		shell->cmd[i].in = (char **)ft_calloc(sizeof(char *) * 2);
		shell->cmd[i].out = (char **)ft_calloc(sizeof(char *) * 2);
		shell->cmd[i].in[0] = NULL;
		shell->cmd[i].in[1] = NULL;
		shell->cmd[i].out[0] = NULL;
		shell->cmd[i].out[1] = NULL;
		i++;
	}
}

static void	parser(t_shell *shell, int flag)
{
	t_index	id;
	t_lexer	lex;

	id.i = -1;
	id.j = 0;
	id.k = 0;
	while (shell->cmdtab[++id.i] && flag == 0)
	{
		id.x = -1;
		lex.flag = 0;
		shell->cmd[id.i].scmd->args = alt_split(shell->cmdtab[id.i], ' ');
		if (shell->cmd[id.i].scmd->args[0] == NULL)
			break ;
		while (shell->cmd[id.i].scmd->args[++id.x])
			shell->cmd[id.i].scmd->args[id.x]
				= apex_trim(shell->cmd[id.i].scmd->args[id.x]);
		shell->cmd[id.i].scmd->path
			= valid_command(shell->cmd[id.i].scmd->args, shell->path);
		id.k = check_path(shell, id.i, id.j);
		if (!shell->cmd[id.i].scmd->path && id.k == 1)
			lex.flag = command_not_found(shell,
					shell->cmd[id.i].scmd->args[id.j]);
	}
	if (flag == 0 && lex.flag == 0 && id.k != 1 && id.k != 50)
		executor(shell, id.i);
}

void	lexer(t_shell *shell)
{
	t_index	id;
	char	**tmp;

	id.i = -1;
	init_redirect(shell);
	shell->cmdtab = alt_split(shell->line, '|');
	tmp = malloc(sizeof(char *) * (ft_tablen(shell->cmdtab) + 1));
	tmp[ft_tablen(shell->cmdtab)] = NULL;
	tmp = ft_tabdup(shell->cmdtab, tmp);
	expand_var(tmp, shell);
	free(tmp);
	id.x = check_infile_outfile(shell);
	shell->path = get_env(shell->env);
	if (shell->cmdtab[0][0] != '\0' && is_a_really_valid_line(shell->cmdtab[0]))
		parser(shell, id.x);
}
