/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:37:31 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/17 14:43:57 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstpushback(t_list **lst, void *content)
{
	t_list	*list_new;

	if (lst == NULLPTR)
		return (1);
	if (*lst == NULLPTR)
	{
		*lst = ft_lstnew(content);
		if (*lst == NULLPTR)
			return (1);
		return (0);
	}
	list_new = ft_lstnew(content);
	if (list_new == NULLPTR)
		return (1);
	ft_lstend(*lst)->next = list_new;
	return (0);
}

void	ft_lstadd_back(t_list **lst, t_list *new_)
{
	if (lst == NULLPTR)
		return ;
	if (*lst == NULLPTR)
		*lst = new_;
	else
		ft_lstend(*lst)->next = new_;
}
