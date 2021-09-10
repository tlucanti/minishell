/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:18:44 by kostya            #+#    #+#             */
/*   Updated: 2021/09/10 21:14:31 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

int	builtin_exit(char *const *argv)
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
