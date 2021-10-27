/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:34:38 by kostya            #+#    #+#             */
/*   Updated: 2021/10/27 13:30:45 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_minl(long long __a1, long long __a2)
{
	long long	diff;

	diff = __a1 - __a2;
	return (__a2 + (diff & (diff >> 31u)));
}

int	ft_min(int __a1, int __a2)
{
	int	diff;

	diff = __a1 - __a2;
	return (__a2 + (diff & (diff >> 31u)));
}
