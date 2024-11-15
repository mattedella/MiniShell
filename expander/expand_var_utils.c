/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:45:32 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/08 11:45:32 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strvar(char *str1, char *str2)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (str1[++i])
	{
		j = -1;
		if (str1[i] == '$')
		{
			while (str2[++j])
				k++;
			break ;
		}
	}
	return (k);
}

static int	ft_lenvar(char *str, int flag)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$' && !check_apex(str[i + 1]))
		{
			i++;
			len++;
			while ((ft_isalpha(str[i]) && str[i] != 34 && str[i] != 39
					&& str[i] != '$') || str[i] == '_' || str[i] == '?')
			{
				i++;
				len++;
			}
			if (flag)
				return (len);
		}
		i++;
	}
	return (len);
}

static char	*ft_sub_null(char *str)
{
	t_index	d;
	int		apex;
	char	*str2;

	d.i = 0;
	d.j = init_len(str);
	d.k = 0;
	apex = 0;
	str2 = ft_calloc(ft_strlen(str) - d.j);
	while (str[d.i])
	{
		if (str[d.i] == '$' && apex == 0)
		{
			apex = 1;
			d.i += d.j;
		}
		else
		{
			str2[d.k] = str[d.i];
			d.k++;
		}
		d.i++;
	}
	return (str2);
}

char	*ft_substitute(char *str1, char *str2)
{
	t_echo	d;

	d.i = 0;
	d.j = 0;
	d.k = 0;
	d.apex = '0';
	if (str2 == NULL)
		return (ft_sub_null(str1));
	d.res = ft_calloc(ft_strlen(str1) - ft_lenvar(str1, 1)
			+ ft_strvar(str1, str2) + 1);
	if (!d.res)
		return (NULL);
	while (str1[d.i])
	{
		if (str1[d.i] == '$' && d.apex == '0' && !check_apex(str1[d.i + 1]))
		{
			while (str2[d.j])
				d.res[d.k++] = str2[d.j++];
			d.apex = '1';
			d.i += ft_lenvar(str1, 1);
		}
		else
			d.res[d.k++] = str1[d.i++];
	}
	return (d.res);
}

char	*ft_substitute_error(char *str1, char *str2)
{
	t_echo	exp;

	exp.i = 0;
	exp.j = 0;
	exp.k = 0;
	exp.apex = '0';
	if (str2 == NULL)
		return (ft_sub_null(str1));
	exp.res = ft_calloc(ft_strlen(str1) - ft_lenvar(str1, 1)
			+ ft_strvar(str1, str2) + 1);
	if (!exp.res)
		return (NULL);
	while (str1[exp.i])
	{
		if (str1[exp.i] == '$' && exp.apex == '0')
		{
			while (str2[exp.j])
				exp.res[exp.k++] = str2[exp.j++];
			exp.apex = '1';
			exp.i += 2;
		}
		else
			exp.res[exp.k++] = str1[exp.i++];
	}
	return (exp.res);
}
