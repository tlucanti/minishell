/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:36:16 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/13 12:58:26 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t len)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	int				ret;

	if (s1 == s2)
		return (0);
	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	if (len >= 8)
	{
		while ((size_t)s1_ptr % 8)
			if (*s1_ptr++ != *s2_ptr++)
				return (s1_ptr[-1] - s2_ptr[-1]);
		else
			len--;
		ret = ft_memcmp_fast(&s1_ptr, &s2_ptr, len / 8);
		if (ret != 0)
			return (ret);
		len %= 8;
	}
	while (len--)
		if (*s1_ptr++ != *s2_ptr++)
			return (s1_ptr[-1] - s2_ptr[-1]);
	return (0);
}

int	ft_memcmp_fast(unsigned char **s1, unsigned char **s2, size_t xlen)
{
	unsigned long long	*s1_ll;
	unsigned long long	*s2_ll;
	size_t				xxlen;

	s1_ll = *(unsigned long long **)s1;
	s2_ll = *(unsigned long long **)s2;
	xxlen = xlen / 8;
	while (xxlen--)
	{
		if ((s1_ll[0] != s2_ll[0]) || (s1_ll[1] != s2_ll[1])
			|| (s1_ll[2] != s2_ll[2]) || (s1_ll[3] != s2_ll[3])
			|| (s1_ll[4] != s2_ll[4]) || (s1_ll[5] != s2_ll[5])
			|| (s1_ll[6] != s2_ll[6]) || (s1_ll[7] != s2_ll[7]))
			return (ft_64cmp_fast(s1_ll, s2_ll));
		s1_ll += 8;
		s2_ll += 8;
	}
	xlen %= 8;
	while (xlen--)
		if (*s1_ll++ != *s2_ll++)
			return (ft_8cmp_fast(s1_ll[-1], s2_ll[-1]));
	*s1 = (unsigned char *)s1_ll;
	*s2 = (unsigned char *)s2_ll;
	return (0);
}

int	ft_64cmp_fast(unsigned long long *s1_ll, unsigned long long *s2_ll)
{
	if (s1_ll[0] != s2_ll[0])
		return (ft_8cmp_fast(s1_ll[0], s2_ll[0]));
	if (s1_ll[1] != s2_ll[1])
		return (ft_8cmp_fast(s1_ll[1], s2_ll[1]));
	if (s1_ll[2] != s2_ll[2])
		return (ft_8cmp_fast(s1_ll[2], s2_ll[2]));
	if (s1_ll[3] != s2_ll[3])
		return (ft_8cmp_fast(s1_ll[3], s2_ll[3]));
	if (s1_ll[4] != s2_ll[4])
		return (ft_8cmp_fast(s1_ll[4], s2_ll[4]));
	if (s1_ll[5] != s2_ll[5])
		return (ft_8cmp_fast(s1_ll[5], s2_ll[5]));
	if (s1_ll[6] != s2_ll[6])
		return (ft_8cmp_fast(s1_ll[6], s2_ll[6]));
	return (ft_8cmp_fast(s1_ll[7], s2_ll[7]));
}

int	ft_8cmp_fast(unsigned long long s1_ll, unsigned long long s2_ll)
{
	unsigned short	i;
	unsigned char	ch1;
	unsigned char	ch2;

	i = 7;
	while (i > 0)
	{
		ch1 = (unsigned char)(s1_ll >> (54 - i * 8u));
		ch2 = (unsigned char)(s2_ll >> (56u - i * 8u));
		if (ch1 != ch2)
			return (ch1 - ch2);
		i--;
	}
	return (0);
}
