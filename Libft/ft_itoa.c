/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarlett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:10:17 by lbarlett          #+#    #+#             */
/*   Updated: 2023/10/17 17:10:17 by lbarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_count_num(int n)
{
	int			i;
	long long	num;

	num = (long long)n;
	i = 0;
	if (num < 0)
	{
		num *= -1;
		i++;
	}
	if (n == 0)
		return (1);
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long long	num;

	i = ft_count_num(n);
	str = (char *)ft_calloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	num = (long long)n;
	str[i] = '\0';
	i--;
	if (n < 0)
	{
		num *= -1;
		str[0] = '-';
	}
	if (n == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[i] = num % 10 + 48;
		num /= 10;
		i--;
	}
	return (str);
}
