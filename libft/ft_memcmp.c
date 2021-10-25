/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:36:16 by tlucanti          #+#    #+#             */
/*   Updated: 2021/10/25 14:02:44 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	register const unsigned char *p1;
	register const unsigned char *p2;

	p1 = s1;
	p2 = s2;

	while (n)
	{
		if (*p1++ != *p2++)
			return (*--p1 - *--p2);
		--n;
	}
	return (0);
}
