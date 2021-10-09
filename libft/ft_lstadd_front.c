/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:26:55 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/17 14:55:57 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstpushfront(t_list **lst, void *content)
{
	t_list	*root;

	if (lst == NULLPTR)
		return (1);
	root = ft_lstnew(content);
	if (root == NULLPTR)
		return (1);
	root->next = *lst;
	*lst = root;
	return (0);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULLPTR)
		return ;
	new->next = *lst;
	*lst = new;
}
