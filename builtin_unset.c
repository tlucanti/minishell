/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:02:16 by kostya            #+#    #+#             */
/*   Updated: 2021/10/26 22:45:15 by kostya           ###   ########.fr       */
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
	uint				_;

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
		{
			_ = xfree(key) + xfree(value);
			return (ft_perror("unset", ENAVI, *argv) + 1);
		}
		list_remove(env, key);
		_ = xfree(key) + xfree(value);
		++argv;
	}
	(void)_;
	return (EXIT_SUCCESS);
}
