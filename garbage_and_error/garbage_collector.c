/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:45:57 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:45:59 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	**garbage_collector(void)
{
	static t_list	*gc = NULL;

	return (&gc);
}

void	garbage_collector_free(int flag)
{
	t_list	*node;
	t_list	*tmp;
	int		i;
	char	*fname;

	i = -1;
	while (++i < *n_doc() && flag)
	{
		fname = ft_strjoin("./tmp/heredoc", ft_itoa(i));
		unlink(fname);
	}
	node = *garbage_collector();
	while (node)
	{
		tmp = node->next;
		if (node)
		{
			if (node->content)
				free(node->content);
			free(node);
		}
		node = tmp;
	}
	*garbage_collector() = NULL;
	rl_clear_history();
}

void	free_heredoc(void)
{
	t_list	*node;
	t_list	*tmp;

	node = *garbage_collector();
	while (node)
	{
		tmp = node->next;
		if (node)
		{
			if (node->content)
				free(node->content);
			free(node);
		}
		node = tmp;
	}
	*garbage_collector() = NULL;
	rl_clear_history();
}
