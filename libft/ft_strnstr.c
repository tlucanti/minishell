/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:46:51 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/16 12:46:51 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	haystack_len;
	size_t	it;

	it = 0;
	if (haystack == NULLPTR && needle == NULLPTR)
		return (NULLPTR);
	needle_len = ft_strnlen(needle, len + 1);
	haystack_len = ft_strnlen(haystack, len);
	if (needle_len == 0)
		return ((char *)haystack);
	if (needle_len > len || len == 0 || haystack_len == 0)
		return (0);
	while (it <= len - needle_len && it <= haystack_len - needle_len)
	{
		if (!ft_memcmp(needle, haystack + it, needle_len))
			return ((char *)haystack + it);
		it++;
	}
	return (NULLPTR);
}
