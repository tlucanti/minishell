/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:05:54 by kostya            #+#    #+#             */
/*   Updated: 2021/09/10 21:14:28 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

int	builtin_pwd(char * const *argv)
{
	char	buff[PATH_MAX];
	char	*_;

	if (argv[1])
	{
		ft_perror("cd", ETMA, NULL);
		return (EXIT_FAILURE);
	}
	_ = getcwd(buff, PATH_MAX);
	(void)_;
	printf("%s\n", buff);
	return (EXIT_SUCCESS);
}
