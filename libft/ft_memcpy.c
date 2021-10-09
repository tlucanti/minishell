/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:35:15 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/10 20:01:49 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*src_ptr;
	unsigned char	*dst_ptr;

	if (dst == src)
		return (dst);
	if (dst == NULLPTR)
		return (NULLPTR);
	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	if (len >= 8)
	{
		while ((size_t)dst_ptr % 8)
		{
			*dst_ptr++ = *src_ptr++;
			len--;
		}
		ft_memcpy_fast_fwd(&dst_ptr, &src_ptr, len / 8);
		len %= 8;
	}
	while (len--)
		*dst_ptr++ = *src_ptr++;
	return (dst);
}

void	ft_memcpy_fast_fwd(unsigned char **dst, unsigned char **src,
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
		dst_ptr[0] = src_ptr[0];
		dst_ptr[1] = src_ptr[1];
		dst_ptr[2] = src_ptr[2];
		dst_ptr[3] = src_ptr[3];
		dst_ptr[4] = src_ptr[4];
		dst_ptr[5] = src_ptr[5];
		dst_ptr[6] = src_ptr[6];
		dst_ptr[7] = src_ptr[7];
		dst_ptr += 8;
		src_ptr += 8;
	}
	xlen %= 8;
	while (xlen--)
		*dst_ptr++ = *src_ptr++;
	*dst = (unsigned char *)dst_ptr;
	*src = (unsigned char *)src_ptr;
}
