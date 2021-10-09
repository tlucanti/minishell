/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:27:16 by tlucanti          #+#    #+#             */
/*   Updated: 2020/11/17 12:38:18 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	ans[12];
	int		dn;

	dn = ft_digit_num(n);
	if (n == 0)
		ans[0] = '0';
	ans[dn + (n < 0)] = 0;
	if (n < 0)
	{
		ans[0] = '-';
		ans[dn] = (char)((char)(n % 10) *(-1) + 48);
		n = -(n / 10);
	}
	while (n)
	{
		ans[--dn] = (char)((char)(n % 10) + 48);
		n /= 10;
	}
	ft_putstr_fd(ans, fd);
}
