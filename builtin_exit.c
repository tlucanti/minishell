/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:18:44 by kostya            #+#    #+#             */
/*   Updated: 2021/09/08 14:03:37 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(__attribute__((unused)) const char *path, const char **argv)
{
	int	status;
	int	error;

	if (!*argv)
		xexit(1);
	if (argv[1])
	{
		xperror("exit", ETMA, NULL);
		return (EXIT_FAILURE);
	}
	error = 0;
	status = ft_atoi_s(*argv, &error);
	if (error)
	{
		xperror("exit", ENUMR, *argv);
		xexit(2);
	}
	xexit(status);
}
