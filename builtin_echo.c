/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:05:54 by kostya            #+#    #+#             */
/*   Updated: 2021/10/07 22:05:23 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/error.h"
#include "include/minishell.h"

static char *const	*__builtin_echo_arg_check(char *const *argv,
						int *restrict n_opt)
					__attribute__((warn_unused_result));

int	builtin_echo(char *const *argv)
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
		printf("%s", *argv);
		++argv;
	}
	while (*argv)
	{
		printf(" %s", *argv);
		++argv;
	}
	if (!n_opt)
		printf("\n");
	return (EXIT_SUCCESS);
}

static char *const	*__builtin_echo_arg_check(char *const *argv,
						int *restrict n_opt)
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
