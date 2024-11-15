/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   altsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:47:49 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:47:49 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_count_words(char *s, char c)
{
	int		i;
	int		count;
	char	apex;

	i = 0;
	count = 0;
	apex = 0;
	while (s[i] != '\0')
	{
		if (check_apex(s[i]) == 1 && apex == 0)
			apex = s[i];
		else if (check_apex(s[i]) == 1 && apex == s[i])
			apex = 0;
		if (s[i] == c && apex == 0)
			count++;
		i++;
	}
	return (count + 1);
}

static char	*ft_matrix(char *s, char c, int *index)
{
	t_echo	id;

	id.i = *index;
	id.j = 0;
	id.apex = 0;
	while (s[id.i + id.j])
	{
		if (check_apex(s[id.i + id.j]) == 1 && id.apex == 0)
			id.apex = s[id.i + id.j];
		else if (check_apex(s[id.i + id.j]) == 1 && id.apex == s[id.i + id.j])
			id.apex = 0;
		if (s[id.i + id.j] == c && id.apex == 0)
			break ;
		else
			id.j++;
	}
	id.res = ft_calloc(sizeof(char) * id.j + 2);
	if (!id.res)
		return (NULL);
	ft_strlcpy(id.res, s + id.i, id.j + 1);
	*index = id.i + id.j;
	return (id.res);
}

char	**alt_split(char const *s, char c)
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
		if ((s[i] != c || check_apex(s[i - 1]) == 1) && s[i] != '\0')
			strsp[word] = ft_matrix((char *)s, c, &i);
	}
	strsp[word] = NULL;
	return (strsp);
}
