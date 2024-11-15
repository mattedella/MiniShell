/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarlett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:53:14 by lbarlett          #+#    #+#             */
/*   Updated: 2023/10/25 11:53:14 by lbarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	t_list	*tmp;
	void	*result;

	if (!lst || !f || !del)
		return (NULL);
	tmp = lst;
	new_lst = NULL;
	new_node = NULL;
	while (tmp != NULL)
	{
		result = f(tmp->content);
		new_node = ft_lstnew(result);
		if (!new_node)
		{
			del(result);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		tmp = tmp->next;
	}
	return (new_lst);
}
