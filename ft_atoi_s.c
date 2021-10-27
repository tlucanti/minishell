/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:41:54 by tlucanti          #+#    #+#             */
/*   Updated: 2021/10/26 22:46:12 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/libft.h"

int	ft_atoi_s(const char *__restrict str, int *__restrict error)
{
	return ((int)ft_atol_s(str, error));
}

long long	ft_atol_s(const char *__restrict str, int *__restrict error)
{
	long long	ans;
	long long	sign;

	if (str == NULL)
		return (0);
	ans = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (1)
	{
		if (!*str)
			return (ans * sign);
		if (!ft_isdigit(*str))
		{
			*error = 1;
			return (0);
		}
		ans = ans * 10 + (*str++ - 48);
	}
}
