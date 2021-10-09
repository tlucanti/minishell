/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:18:44 by kostya            #+#    #+#             */
/*   Updated: 2021/10/08 14:03:56 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/error.h"

int	builtin_exit(char *const *argv)
/*
** function termitates work of current shell and clearing memory
*/
{
	int	status;
	int	error;

	++argv;
	if (!*argv)
		xexit(1);
	if (argv[1])
	{
		ft_perror("exit", ETMA, NULL);
		return (EXIT_FAILURE);
	}
	error = 0;
	status = ft_atoi_s(*argv, &error);
	if (error)
	{
		ft_perror("exit", ENUMR, *argv);
		xexit(2);
	}
	xexit(status);
}
