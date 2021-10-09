/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:11:35 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/12 14:47:02 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	if (dst == NULLPTR && src == NULLPTR)
		return (0);
	if (src > dst)
		return (ft_memcpy(dst, src, len));
	dst_ptr = (unsigned char *)dst + len;
	src_ptr = (unsigned char *)src + len;
	if (len > 8)
	{
		while ((size_t)dst_ptr % 8)
		{
			*--dst_ptr = *--src_ptr;
			len--;
		}
		ft_memcpy_fast_bkw(&dst_ptr, &src_ptr, len / 8);
		len %= 8;
	}
	while (len--)
		*--dst_ptr = *--src_ptr;
	return (dst);
}

void	ft_memcpy_fast_bkw(unsigned char **dst, unsigned char **src,
	size_t xlen)
{
	unsigned long long	*dst_ptr;
	unsigned long long	*src_ptr;
	size_t				xxlen;

	dst_ptr = *(unsigned long long **)dst;
	src_ptr = *(unsigned long long **)src;
	xxlen = xlen / 8;
	while (xxlen--)
	{
		dst_ptr -= 8;
		src_ptr -= 8;
		dst_ptr[7] = src_ptr[7];
		dst_ptr[6] = src_ptr[6];
		dst_ptr[5] = src_ptr[5];
		dst_ptr[4] = src_ptr[4];
		dst_ptr[3] = src_ptr[3];
		dst_ptr[2] = src_ptr[2];
		dst_ptr[1] = src_ptr[1];
		dst_ptr[0] = src_ptr[0];
	}
	xlen %= 8;
	while (xlen--)
		*--dst_ptr = *--src_ptr;
	*dst = (unsigned char *)dst_ptr;
	*src = (unsigned char *)src_ptr;
}
