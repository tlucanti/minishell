/**
 *	Author:		kostya
 *	Created:	2021-09-05 16:48:48
 *	Modified:	2021-09-05 20:37:58
 **/

#include <zconf.h>

#ifdef DEBUG
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
int builtin_echo(const char *path, const char **argv);
const char **builtin_echo_arg_check(const char **argv,
int * restrict n_opt);
int main(int argc, const char **argv)
{
	(void)argc;
	builtin_echo(argv[0], argv + 1);
}
#endif
//#ifndef DEBUG
# include "minishell.h"
//#endif

int builtin_echo(__attribute__((unused)) const char *path, const char **argv)
{
	int n_opt;

	n_opt = 0;
	argv = builtin_echo_arg_check(argv, &n_opt);
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

static const char **builtin_echo_arg_check(const char **argv, int * restrict n_opt)
{
	size_t	it;
	int		got_n;

	while (*argv)
	{
		// check only minus - it will end options half of arguments
		if ((*argv)[0] == '-' && !(*argv)[1])
			return (argv + 1);
		// check is option
		if (**argv != '-')
			return (argv);
		// check n option
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
