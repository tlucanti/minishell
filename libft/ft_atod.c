#include "libft.h"

float	ft_atof(const char *str)
{
	return ((float)(ft_atod(str)));
}

double 	ft_atod(const char *str)
{
	double	ans;
	double	sgn;

	if (str == NULL)
		return (0);
	while (ft_isspace(*str))
		str++;
	ans = ft_atod_noexp(&str, &sgn);
	if (*str == '.')
		ans += ft_atod_frac(&str);
	if (*str == 'e' || *str == 'E')
		return (sgn * ans * ft_powd_fast(10, ft_atoi(++str)));
	return (sgn * ans);
}

double	ft_atod_noexp(const char **str, double *sgn)
{
	double	ans;

	ans = 0;
	*sgn = 1;
	if (**str == '-')
		*sgn = -1;
	if (**str == '-' || **str == '+')
		(*str)++;
	while (ft_isdigit(**str))
		ans = ans * 10 + (*(*str)++ - 48);
	return (ans);
}

double	ft_powd_fast(double n, int exp)
{
	double	nn;

	if (exp == 0)
		return (1);
	else if (exp < 0)
		return (1 / ft_powd_fast(n, -exp));
	else if (exp % 2)
		return (n * ft_powd_fast(n, exp - 1));
	else
	{
		nn = ft_powd_fast(n, exp / 2);
		return (nn * nn);
	}
}

double	ft_atod_frac(const char **str__)
{
	char	*ptr;
	char	*str;
	double	ans;

	ans = 0;
	ptr = *((char **)str__);
	str = ptr;
	while (*ptr && *ptr != 'e' && *ptr != 'E')
		ptr++;
	*str__ = ptr;
	ptr--;
	while (str != ptr)
	{
		ans = ans / 10 + (*ptr-- - 48);
	}
	return (ans / 10);
}
