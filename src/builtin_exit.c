/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:18:44 by kostya            #+#    #+#             */
/*   Updated: 2021/10/31 16:03:21 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/error.h"

int	builtin_exit(char *__restrict const *__restrict argv)
/*
** function termitates work of current shell and clearing memory
*/
{
	int	status;
	int	error;

	++argv;
	if (!*argv)
		xexit(0);
	if (argv[1])
	{
		ft_perror("exit", ETMA, NULL);
		xexit(2);
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
