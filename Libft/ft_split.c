/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarlett <lbarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:56:59 by lbarlett          #+#    #+#             */
/*   Updated: 2024/04/24 13:22:59 by lbarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char *s, char c)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static char	*ft_matrix(char *s, char c, int *index)
{
	int		j;
	char	*word;
	int		i;

	i = *index;
	j = 0;
	while (s[i + j] != c && s[i + j] != '\0')
		j++;
	word = ft_calloc(sizeof(char) * j + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + i, j + 1);
	*index = i + j;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**strsp;
	int		nwords;
	int		i;
	int		word;

	if (!s)
		return (NULL);
	nwords = ft_count_words((char *)s, (char)c);
	strsp = ft_calloc(sizeof(char *) * (nwords + 1));
	if (!strsp)
		return (NULL);
	word = -1;
	i = 0;
	while (++word < nwords)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			strsp[word] = ft_matrix((char *)s, c, &i);
		}
	}
	strsp[word] = NULL;
	return (strsp);
}
