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
