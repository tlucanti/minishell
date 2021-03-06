/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:05:54 by kostya            #+#    #+#             */
/*   Updated: 2021/11/01 19:09:54 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/error.h"
#include "../inc/minishell.h"
#include "../inc/libft.h"

static char *const	*__builtin_echo_arg_check(
						char *const *__restrict argv,
						int *__restrict n_opt) __attribute__((
							warn_unused_result)) __attribute__((
							__nothrow__));

int	builtin_echo(char *const *__restrict argv)
/*
** funcion prints to STDIN arguments in argv split by space
** if option `-n` provided - no "\n" (ENDL) printed
*/
{
	int		n_opt;

	n_opt = 0;
	++argv;
	argv = __builtin_echo_arg_check(argv, &n_opt);
	if (*argv)
	{
		write(1, *argv, ft_strlen(*argv));
		++argv;
	}
	while (*argv)
	{
		write(1, " ", 1);
		write(1, *argv, ft_strlen(*argv));
		++argv;
	}
	if (!n_opt)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

static char *const	*__builtin_echo_arg_check(
						char *const *__restrict argv,
						int *__restrict n_opt)
{
	unsigned int	it;
	int				got_n;

	while (*argv)
	{
		if ((*argv)[0] == '-' && !(*argv)[1])
			return (argv + 1);
		if (**argv != '-')
			return (argv);
		it = 1;
		got_n = 0;
		while ((*argv)[it])
		{
			if ((*argv)[it] != 'n')
				return (argv);
			got_n |= (*argv)[it] == 'n';
			++it;
		}
		*n_opt |= got_n;
		++argv;
	}
	return (argv);
}
