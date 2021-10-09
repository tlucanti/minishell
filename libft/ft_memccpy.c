/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:10:24 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/16 12:42:39 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)ft_memchr(src, c, n);
	if (p != NULLPTR)
	{
		ft_memcpy(dst, src, p - (unsigned char *)src + 1);
		return (p - (size_t)src + (size_t)dst + 1);
	}
	ft_memcpy(dst, src, n);
	return (NULLPTR);
}
