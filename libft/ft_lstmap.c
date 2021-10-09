/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:03:55 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/17 15:16:06 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
		void (*del)(void *))
{
	t_list	*root;

	root = NULLPTR;
	while (lst)
	{
		if (ft_lstpushback(&root, f(lst->content)))
		{
			ft_lstclear(&root, del);
			return (NULLPTR);
		}
		lst = lst->next;
	}
	return (root);
}
