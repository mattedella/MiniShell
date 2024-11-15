/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_III.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:48:00 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:48:02 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_digit_2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

long long	ft_atol(char *str)
{
	int			x;
	int			s;
	long long	num;

	num = 0;
	x = 0;
	s = 1;
	while (str[x] == ' ' || (str[x] >= 9 && str[x] <= 13))
		x++;
	if (str[x] == '-' || str[x] == '+')
	{
		if (str[x] == '-')
			s *= -1;
		x++;
	}
	while (str[x] >= '0' && str[x] <= '9')
	{
		num *= 10;
		num += str[x] -48;
		x++;
	}
	return (num * s);
}

int	exit_handler(char *str, int f)
{
	long long	i;
	t_echo		id;

	id.j = 0;
	id.flag = 0;
	if (str == NULL)
		return (0);
	while (str[id.j])
	{
		if (str[id.j] == '-' || str[id.j] == '+')
			id.flag = 1;
		id.j++;
	}
	if (is_digit_3(str, id.flag) && f == 1)
		return (print_exit_error(0));
	i = ft_atol(str);
	if (i > 255 || i < 0)
	{
		i %= 256;
		if (i < 0)
			i += 256;
		if (i == 0)
			i += 1;
	}
	return (i);
}

int	my_isalnum(char *c)
{
	if (ft_isalpha(c[0]) || c[0] == '_')
		return (0);
	else
		return (1);
}

int	check_char(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && !(ft_isalpha(str[0])))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (2);
		if (str[i] != '_' && !(ft_isalnum(str[i])))
			return (1);
		i++;
	}
	return (0);
}
