/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:34:38 by kostya            #+#    #+#             */
/*   Updated: 2021/10/27 00:12:47 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_absl(size_t __a)
{
	size_t	mask;

	mask = __a >> 63u;
	__a ^= mask;
	return (__a - mask);
}

int	ft_abs(int __a)
{
	unsigned int	mask;

	mask = __a >> 31u;
	__a ^= mask;
	return (__a - mask);
}
