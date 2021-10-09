/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:01:08 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/11 17:01:41 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	ch;
	void			*ret;

	ptr = (unsigned char *)s;
	ch = (unsigned char)c;
	if (n >= 8)
	{
		while ((size_t)ptr % 8)
			if (*ptr++ == ch)
				return (ptr - 1);
		else
			n--;
		ret = ft_memchr_fast(&ptr, ch, n / 8);
		if (ret != NULLPTR)
			return (ret);
		n %= 8;
	}
	while (n--)
		if (*ptr++ == ch)
			return (ptr - 1);
	return (NULLPTR);
}

void	*ft_memchr_fast(unsigned char **ptr, unsigned char ch, size_t xlen)
{
	unsigned long long	ones_ll;
	unsigned long long	cccc;
	unsigned long long	xor_ll;
	unsigned long long	*ptrll;

	ones_ll = 0x0101010101010101;
	cccc = ch;
	cccc |= cccc << 8u;
	cccc |= cccc << 16u;
	cccc |= cccc << 32u;
	ptrll = *(unsigned long long **)ptr;
	while (xlen--)
	{
		xor_ll = *ptrll ^ cccc;
		if ((((xor_ll - ones_ll) & ~xor_ll) & (ones_ll << 7u)) != 0)
		{
			xlen = 8;
			*ptr = (unsigned char *)ptrll;
			while (xlen--)
				if (*((*ptr)++) == ch)
					return ((*ptr) - 1);
		}
		ptrll++;
	}
	return ((void *)((size_t)(*ptr = (unsigned char *)ptrll) * 0));
}
