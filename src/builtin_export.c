/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:38:52 by kostya            #+#    #+#             */
/*   Updated: 2021/11/05 17:56:21 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/enviroment.h"
#include "../inc/memory.h"
#include "../inc/error.h"
#include "../inc/libft.h"

int	builtin_export_split(const char *__restrict string, char *__restrict *key,
		char *__restrict *value)
	__attribute__((warn_unused_result)) __attribute__((__nothrow__));

int	builtin_export(char *const *__restrict argv)
/*
** function adds new enviroment variables provided in argv to internal shell
** storage with syntax [VAR_NAME]=[VALUE]
*/
{
	char *__restrict	key;
	char *__restrict	value;
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
			ft_perror("export", ENAVI, *argv);
			return (1);
		}
		if (ft_strchr(*argv, '=') == NULL)
			value = ft_strdup(ft_getenv_s(key, NULL));
		list_insert(env, key, value);
		++argv;
	}
	return (0);
}

int	builtin_export_split(const char *__restrict string, char *__restrict *key,
		char *__restrict *value)
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
	*key = (char *)xmalloc(it + 1);
	ft_memcpy(*key, string, it);
	(*key)[it] = 0;
	*value = NULL;
	if (!string[it])
		return (EXIT_SUCCESS);
	string += it + (string[it] == '=');
	it = ft_strlen(string);
	*value = (char *)xmalloc(it + 1);
	ft_memcpy(*value, string, it + 1);
	return (EXIT_SUCCESS);
}
