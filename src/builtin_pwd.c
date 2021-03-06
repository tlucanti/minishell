/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:05:54 by kostya            #+#    #+#             */
/*   Updated: 2021/11/01 16:36:38 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/error.h"

int	builtin_pwd(char *__restrict const *__restrict argv)
/*
** function prints to STDOUT current working directory (CWD)
** if arguments provided - prints error to STDERR
*/
{
	char	buff[PATH_MAX];
	char	*_;

	if (argv && argv[1])
	{
		ft_perror("pwd", ETMA, NULL);
		return (EXIT_FAILURE);
	}
	_ = getcwd(buff, PATH_MAX);
	(void)_;
	printf("%s\n", buff);
	return (EXIT_SUCCESS);
}
