/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:02:16 by kostya            #+#    #+#             */
/*   Updated: 2021/09/08 11:32:27 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "enviroment.h"
#include "minishell.h"

extern g_main_st_t g_main;

int	builtin_unset(__attribute__((unused)) const char *path, const char **argv)
{
	char *restrict key;
	char *restrict value;

	if (!*argv)
	{
		xperror("unset", ENEA, NULL);
		return (EXIT_FAILURE);
	}
	while (*argv)
	{
		if (builtin_export_split(*argv, &key, &value))
		{
			xperror("unset", ENAVI, *argv);
			return (EXIT_FAILURE);
		}
		list_remove(g_main.env, key);
		free(value);
		free(key);
		++argv;
	}
	return (EXIT_SUCCESS);
}
