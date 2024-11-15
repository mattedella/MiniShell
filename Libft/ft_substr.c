/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarlett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:55:20 by lbarlett          #+#    #+#             */
/*   Updated: 2023/10/17 16:55:20 by lbarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;

	if (start > ft_strlen((char *)s))
	{
		sub_s = (char *)malloc(sizeof(char) * 1);
		if (!sub_s)
			return (NULL);
		sub_s[0] = '\0';
		return (sub_s);
	}
	i = -1;
	s += start;
	if (ft_strlen((char *)s) <= len)
		sub_s = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	else
		sub_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_s)
		return (NULL);
	while (s[++i] != '\0' && i < len)
		sub_s[i] = s[i];
	sub_s[i] = '\0';
	return (sub_s);
}
