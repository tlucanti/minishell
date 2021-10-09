/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:10:28 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/13 15:10:28 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*found;
	const char	*p;

	c = (unsigned char)c;
	if (c == 0)
		return (ft_strchr(s, 0));
	found = 0;
	p = ft_strchr(s, c);
	while (p != 0)
	{
		found = p;
		s = p + 1;
		p = ft_strchr(s, c);
	}
	return ((char *)found);
}
