/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarlett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:55:52 by lbarlett          #+#    #+#             */
/*   Updated: 2023/10/17 16:55:52 by lbarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_char_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static int	ft_len_n(int nb, int l)
{
	if (nb / 10 == 0)
	{
		return (l);
	}
	return (ft_len_n(nb / 10, l * 10));
}

void	ft_putnbr_fd(int nb, int fd)
{
	char	c;
	int		len;

	if (nb < 0)
	{
		ft_char_fd('-', fd);
		if (nb == -2147483648)
		{
			write(fd, "2147483648", 10);
			return ;
		}
		else
			nb *= -1;
	}
	len = ft_len_n(nb, 1);
	while (len > 0)
	{
		c = (nb / len) % 10 + '0';
		ft_char_fd(c, fd);
		len /= 10;
	}
}
