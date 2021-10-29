/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:05:00 by tlucanti          #+#    #+#             */
/*   Updated: 2021/10/29 18:25:21 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_s;

	if (s1 == NULLPTR || s2 == NULLPTR)
		return (NULLPTR);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_s = (char *)xmalloc(s1_len + s2_len + 1);
	if (new_s == NULLPTR)
		return (NULLPTR);
	ft_memcpy(new_s, s1, s1_len);
	ft_memcpy(new_s + s1_len, s2, s2_len + 1);
	return (new_s);
}
