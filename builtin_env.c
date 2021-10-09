/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:12:43 by kostya            #+#    #+#             */
/*   Updated: 2021/10/08 14:03:44 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/enviroment.h"
#include "include/error.h"

int	builtin_env(char *const *argv)
/*
** function prints to STDIN all enviroment variables sorted by lexical order
** if arguments provided - prints error to STDERR
*/
{
	if (argv[1])
	{
		ft_perror("env", ETMA, NULL);
		return (EXIT_FAILURE);
	}
	print_env();
	return (EXIT_SUCCESS);
}
