/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:02:16 by kostya            #+#    #+#             */
/*   Updated: 2021/10/08 14:50:28 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/enviroment.h"
#include "include/minishell.h"
#include "include/memory.h"
#include "include/error.h"

int	builtin_unset(char *const *argv)
/*
** function remove envroment variable provided in argv from internal shell
** storage
** variable may not be in enviroment
*/
{
	char	*restrict	key;
	char	*restrict	value;
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
			_ += xfree(key) + xfree(value);
			ft_perror("unset", ENAVI, *argv);
			return (EXIT_FAILURE);
		}
		list_remove(env, key);
		_ += xfree(key) + xfree(value);
		++argv;
	}
	return (EXIT_SUCCESS);
}
