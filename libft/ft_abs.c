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
