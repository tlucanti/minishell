/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:38:52 by kostya            #+#    #+#             */
/*   Updated: 2021/10/08 14:49:02 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/enviroment.h"
#include "include/memory.h"
#include "include/error.h"
#include "include/libft.h"

int	builtin_export_split(const char *string, char *restrict *key,
		char *restrict *value);

int	builtin_export(char *const *argv)
/*
** function adds new enviroment variables provided in argv to internal shell
** storage with syntax [VAR_NAME]=[VALUE]
*/
{
	char	*restrict	key;
	char	*restrict	value;
	t_env				*env;

	++argv;
	if (!*argv)
	{
		print_env();
		return (0);
	}
	env = internal_env_storage();
	while (*argv)
	{
		if (builtin_export_split(*argv, &key, &value))
		{
			free(key);
			free(value);
			ft_perror("export", ENAVI, *argv);
			return (1);
		}
		list_insert(env, key, value);
		++argv;
	}
	return (0);
}

int	builtin_export_split(const char *string, char *restrict *key,
		char *restrict *value)
{
	size_t	it;

	it = 0;
	if (!ft_isalpha(string[0]) && string[0] != '_')
		return (EXIT_FAILURE);
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
