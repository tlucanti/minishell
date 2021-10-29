/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:23:04 by tlucanti          #+#    #+#             */
/*   Updated: 2021/10/29 18:24:57 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = (t_list *)xmalloc(sizeof(t_list));
	if (lst == NULLPTR)
		return (NULLPTR);
	lst->content = content;
	lst->next = NULLPTR;
	return (lst);
}
