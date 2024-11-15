/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarlett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:51:20 by lbarlett          #+#    #+#             */
/*   Updated: 2023/10/11 15:51:20 by lbarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s, int apex)
{
	char	*dup;
	int		i;

	i = -1;
	dup = (char *)ft_calloc(ft_strlen((char *)s) + 2);
	if (!dup)
		return (NULL);
	if (apex == 1)
	{
		while (s[++i] != '\0')
		{
			while (s[i] == 34 && s[i] == 39)
				i++;
			dup[i] = s[i];
		}
	}
	if (apex == 2)
		while (s[++i] != '\0')
			dup[i] = s[i];
	else
		while (s[++i] != ' ' && s[i] != '\0')
			dup[i] = s[i];
	return (dup);
}
