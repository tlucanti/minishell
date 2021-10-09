/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:07:05 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/11 17:00:51 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char		*ptrc;
	unsigned char		ch;

	ptrc = (unsigned char *)s;
	ch = c;
	if (len >= 8)
	{
		while ((size_t)ptrc % 8)
		{
			*ptrc++ = ch;
			len--;
		}
		ptrc = ft_memset_fast(ptrc, len / 8, (unsigned long long)ch);
		len %= 8;
	}
	while (len--)
		*ptrc++ = ch;
	return (s);
}

unsigned char	*ft_memset_fast(unsigned char *s, size_t xlen,
	unsigned long long cccc)
{
	unsigned long long	*ptrll;
	size_t				xxlen;

	cccc |= cccc << 8u;
	cccc |= cccc << 16u;
	cccc |= cccc << 32u;
	ptrll = (unsigned long long *)s;
	xxlen = xlen / 8;
	while (xxlen--)
	{
		ptrll[0] = cccc;
		ptrll[1] = cccc;
		ptrll[2] = cccc;
		ptrll[3] = cccc;
		ptrll[4] = cccc;
		ptrll[5] = cccc;
		ptrll[6] = cccc;
		ptrll[7] = cccc;
		ptrll += 8;
	}
	xlen %= 8;
	while (xlen--)
		*ptrll++ = cccc;
	return ((unsigned char *)ptrll);
}
