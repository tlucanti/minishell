/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:29:33 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/13 14:29:33 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	void	*ret;

	ret = ft_memchr(s, 0, maxlen);
	if (ret == NULLPTR)
		return (maxlen);
	return ((size_t)ret - (size_t)s);
}
