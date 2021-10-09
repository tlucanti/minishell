/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:03:30 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/14 11:50:31 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	size;

	if (s == NULLPTR)
		return (NULLPTR);
	if (ft_strnlen(s, start) < start)
		size = 1;
	else
		size = ft_strnlen(s + start, len) + 1;
	new_s = (char *)malloc(size);
	if (new_s == NULLPTR)
		return (NULLPTR);
	ft_strlcpy(new_s, s + start, size);
	return (new_s);
}
