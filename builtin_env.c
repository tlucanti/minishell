/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:12:43 by kostya            #+#    #+#             */
/*   Updated: 2021/09/10 21:14:32 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "error.h"

int	builtin_env(char *const *argv)
{
	if (argv[1])
	{
		ft_perror("env", ETMA, NULL);
		return (EXIT_FAILURE);
	}
	print_env();
	return (EXIT_SUCCESS);
}
