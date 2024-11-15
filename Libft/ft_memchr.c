/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarlett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:59:26 by lbarlett          #+#    #+#             */
/*   Updated: 2023/10/11 14:16:45 by lbarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*temp_s;
	size_t				i;

	temp_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (temp_s[i] == (unsigned char)c)
			return (temp_s + i);
		i++;
	}
	return (NULL);
}
