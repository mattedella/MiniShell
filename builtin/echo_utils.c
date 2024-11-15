/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:48 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:44:48 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minusn_check(char **args, int *j)
{
	int	a;

	a = *j;
	a++;
	while (minusn_finder(args[a]) == 0)
		a++;
	a--;
	*j = a;
}

int	minusn_finder(char *args)
{
	int	i;

	i = 0;
	if (!args)
		return (1);
	if (args[i] == '-')
	{
		i++;
		if (args[i] == 'n')
		{
			while (args[i])
			{
				if (args[i] != 'n')
					return (1);
				i++;
			}
			return (0);
		}
		return (1);
	}
	return (1);
}
