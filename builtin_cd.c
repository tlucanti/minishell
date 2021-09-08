/**
 *	Author:		kostya
 *	Created:	2021-09-05 19:35:50
 *	Modified:	2021-09-07 10:56:58
 **/

#include "minishell.h"
#include "enviroment.h"

int	builtin_cd(__attribute__((unused)) const char *path, const char **argv)
{
	int			ret;
	const char	*togo;

	togo = *argv;
	// if no args - go to ~
	if (togo == NULL)
		togo = "~";
	if (!ft_memcmp("~", togo, 2))
		togo = ft_getenv("HOME", NULL);
	// if we want to go $HOME, but it deleted - we qre not going anywhere
	if (togo == NULL)
		togo = "";
	// if empty string ("") got as argument - we qre not going anywhere
	if (!*togo)
		return (EXIT_SUCCESS);
	ret = chdir(togo);
	if (ret == 0)
		return (EXIT_SUCCESS);
	xperror("cd", errno, argv[0]);
	return (EXIT_FAILURE);
}
