/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:55:48 by tlucanti          #+#    #+#             */
/*   Updated: 2021/10/30 16:38:56 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy_gnl(void *dst, const void *src, size_t len)
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
		ft_memcpy_fast_gnl(&dst_ptr, &src_ptr, len / 8);
		len %= 8;
	}
	while (len--)
		*dst_ptr++ = *src_ptr++;
	return (dst_ptr);
}

void	ft_memcpy_fast_gnl(unsigned char **dst, unsigned char **src,
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

void	*ft_calloc1(size_t nmeb)
{
	char	*arr;

	arr = (char *)malloc(nmeb);
	if (arr == NULL)
		return (NULL);
	while (nmeb--)
		arr[nmeb] = 0;
	return (arr);
}

size_t	ft_find_end(char *str, size_t size)
{
	size_t	i;

	i = 0;
	while (i++ < size)
	{
		if (*str == 0 || *str == 0xa)
			return (i);
		str++;
	}
	return (-1);
}
