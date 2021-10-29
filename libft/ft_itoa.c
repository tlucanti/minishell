/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:12:21 by tlucanti          #+#    #+#             */
/*   Updated: 2021/10/29 18:24:52 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*ans;
	int		dn;

	dn = ft_digit_num(n);
	ans = (char *)xmalloc(dn + (n < 0) + 1);
	if (ans == NULLPTR)
		return (NULLPTR);
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
	return (ans);
}

int	ft_digit_num(int n)
{
	int	ans;

	if (n == 0)
		return (1);
	ans = 0;
	while (n)
	{
		ans++;
		n /= 10;
	}
	return (ans);
}
