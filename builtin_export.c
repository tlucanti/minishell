/**
 *	Author:		kostya
 *	Created:	2021-09-05 19:33:59
 *	Modified:	2021-09-08 11:07:57
 **/

#include "minishell.h"
#include "enviroment.h"
#include "global.h"
#include "memory.h"

extern g_main_st_t g_main;

int	builtin_export(__attribute__((unused)) const char *path, const char **argv)
{
	char	*restrict key;
	char	*restrict value;

	if (!*argv)
	{
		print_list(g_main.env);
		return (0);
	}
	while (*argv)
	{
		if (builtin_export_split(*argv, &key, &value))
		{
			xperror("export", ENAVI, *argv);
			return (1);
		}
		list_insert(g_main.env, key, value);
		++argv;
	}
	return (0);
}

int builtin_export_split(const char *string, char *restrict  *key, char *restrict *value)
{
	size_t	it;

	it = 0;
	if (!ft_isalpha(string[0]) && string[0] != '_')
		return(EXIT_FAILURE);
	while (string[it])
	{
		if (!ft_isalnum(string[it]) && string[it] != '_' && string[it] != '=')
			return (EXIT_FAILURE);
		if (string[it] == '=')
			break ;
		++it;
	}
	*key = xmalloc(it + 1);
	ft_memcpy(*key, string, it);
	(*key)[it] = 0;
	string += it + 1;
	it = ft_strlen(string);
	*value = xmalloc(it + 1);
	ft_memcpy(*value, string, it + 1);
	return (EXIT_SUCCESS);
}
