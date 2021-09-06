/**
 *	Author:		kostya
 *	Created:	2021-09-05 19:37:15
 *	Modified:	2021-09-06 00:24:39
 **/

#include "minishell.h"

int	builtin_pwd(__attribute__((unused)) char *path, const char **argv)
{
	char	buff[PATH_MAX];

	if (*argv)
	{
		xperror("cd", ETMA, NULL);
		return (EXIT_FAILURE);
	}
	getcwd(buff, PATH_MAX);
	printf("%s\n", buff);
	return (EXIT_SUCCESS);
}
