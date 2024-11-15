/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarlett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:17:33 by lbarlett          #+#    #+#             */
/*   Updated: 2023/10/12 12:17:33 by lbarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char set)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen((char *)s1);
	if (s1[i] != '\0' && set != '\0')
	{
		while (s1[i] && s1[i] == set)
			i++;
		while (s1[j - 1] && s1[j - 1] == set && j > i)
			j--;
	}
	str = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)&s1[i], j - i + 1);
	str[j - i] = '\0';
	return (str);
}
