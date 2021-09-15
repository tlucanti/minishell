/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:02:16 by kostya            #+#    #+#             */
/*   Updated: 2021/09/15 22:11:11 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "minishell.h"
#include "error.h"

int	builtin_unset(char *const *argv)
{
	char	*restrict	key;
	char	*restrict	value;
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
		{
			free(key);
			free(value);
			ft_perror("unset", ENAVI, *argv);
			return (EXIT_FAILURE);
		}
		list_remove(env, key);
		free(value);
		free(key);
		++argv;
	}
	return (EXIT_SUCCESS);
}
