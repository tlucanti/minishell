/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:02:16 by kostya            #+#    #+#             */
/*   Updated: 2021/10/27 12:38:11 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/enviroment.h"
#include "include/minishell.h"
#include "include/memory.h"
#include "include/error.h"

int	builtin_unset(char *__restrict const *__restrict argv)
/*
** function remove envroment variable provided in argv from internal shell
** storage
** variable may not be in enviroment
*/
{
	char *__restrict	key;
	char *__restrict	value;
	t_env				*env;

	++argv;
	if (!*argv)
	{
		ft_perror("unset", ENEA, NULL);
		return (EXIT_FAILURE);
	}
	env = internal_env_storage();
	while (*argv)
	{
		if (builtin_export_split(*argv, &key, &value))
			return (ft_perror("unset", ENAVI, *argv) + 1);
		list_remove(env, key);
		free(key);
		free(value);
		++argv;
	}
	return (EXIT_SUCCESS);
}
