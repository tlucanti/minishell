/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:00:34 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/16 10:59:50 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_maxl(long long __a1, long long __a2)
{
	long long	diff;

	diff = __a1 - __a2;
	return (__a1 - (diff & (diff >> 63u)));
}

int	ft_max(int __a1, int __a2)
{
	int	diff;

	diff = __a1 - __a2;
	return (__a1 - (diff & (diff >> 31u)));
}
