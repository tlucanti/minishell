/**
 *	Author:		kostya
 *	Created:	2021-09-05 19:33:59
 *	Modified:	2021-09-06 00:31:50
 **/

#include "minishell.h"
#include "enviroment.h"
#include "global.h"
#include "memory.h"

#define ft_isalnum isalnum
#define ft_isdigit isdigit

extern g_main_st_t g_main;

int	builtin_export(__attribute__((unused)) const char *path, const char **argv)
{
	char	*key;
	char	*value;

	while (*argv)
	{
		if (builtin_export_split(*argv, &key, &value))
			return (1);
		list_remove(g_main.env, key);
		list_push_back(g_main.env, key, value);
		++argv;
	}
	return (0);
}

int builtin_export_split(const char *string, char **restrict key, char **restrict value)
{
	size_t	it;

	it = 0;
	if (ft_isdigit(string[0]))
		return(EXIT_FAILURE);
	while (string[it])
	{
		if (!ft_isalnum(string[it]) || string[it] != '_')
			return (EXIT_FAILURE);
		if (string[it] == '=')
			break ;
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
