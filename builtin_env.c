/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:12:43 by kostya            #+#    #+#             */
/*   Updated: 2021/09/08 13:17:17 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "enviroment.h"
#include "global.h"

extern g_main_st_t g_main;

int	builtin_env(__attribute__((unused)) const char *path, const char **argv)
{
	if (*argv)
	{
		xperror("env", ETMA, NULL);
		return (EXIT_FAILURE);
	}
	print_list(g_main.env);
	return (EXIT_SUCCESS);
}
