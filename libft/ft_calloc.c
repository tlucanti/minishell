/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:42:15 by tlucanti          #+#    #+#             */
/*   Updated: 2021/10/29 18:24:47 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	ret = xmalloc(nmemb * size);
	if (ret != NULLPTR)
		return (ft_memset(ret, 0, nmemb * size));
	return (ret);
}
