//
// Created by kostya on 3/20/21.
//

#include "libft.h"

int	ft_isspace(int __c)
{
	return (__c == ' ' || __c == '\t' || __c == '\n'
		|| __c == '\v' || __c == '\f' || __c == '\r');
}
