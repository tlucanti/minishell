/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:02:16 by kostya            #+#    #+#             */
/*   Updated: 2021/09/10 16:04:46 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "minishell.h"
#include "error.h"

int	builtin_unset(char *const *argv)
{
	char *restrict key;
	char *restrict value;

	++argv;
	if (!*argv)
	{
		ft_perror("unset", ENEA, NULL);
		return (EXIT_FAILURE);
	}
	while (*argv)
	{
		if (builtin_export_split(*argv, &key, &value))
		{
			ft_perror("unset", ENAVI, *argv);
			return (EXIT_FAILURE);
		}
		list_remove(ft_env_storage(), key);
		free(value);
		free(key);
		++argv;
	}
	return (EXIT_SUCCESS);
}
