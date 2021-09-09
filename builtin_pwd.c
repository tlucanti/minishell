/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:05:54 by kostya            #+#    #+#             */
/*   Updated: 2021/09/09 14:44:59 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char * const *argv)
{
	char	buff[PATH_MAX];

	if (argv[1])
	{
		xperror("cd", ETMA, NULL);
		return (EXIT_FAILURE);
	}
	getcwd(buff, PATH_MAX);
	printf("%s\n", buff);
	return (EXIT_SUCCESS);
}
