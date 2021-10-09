/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:44:41 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/17 12:03:04 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_s;
	size_t	strlen;

	if (s == NULLPTR)
		return (NULLPTR);
	strlen = ft_strlen(s);
	new_s = ft_strdup(s);
	if (new_s == NULLPTR)
		return (NULLPTR);
	while (strlen--)
		new_s[strlen] = f(strlen, s[strlen]);
	return (new_s);
}
