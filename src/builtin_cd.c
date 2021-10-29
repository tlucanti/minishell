/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:22:41 by kostya            #+#    #+#             */
/*   Updated: 2021/10/28 23:06:38 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/enviroment.h"
#include "../inc/error.h"
#include "../inc/libft.h"

int	builtin_cd(char *__restrict const *__restrict argv)
/*
** function changes current working dir (CWD) of shell to path in first argument
** if no arguments provided - changing to ~ (HOME)
** if path is empty string - CWD will not chamge
** errno errors printed to STDERR
*/
{
	int			ret;
	const char	*togo;

	togo = *(++argv);
	if (togo == NULL)
		togo = "~";
	if (!ft_memcmp("~", togo, 2))
		togo = ft_getenv("HOME", NULL);
	if (togo == NULL)
		togo = "";
	if (!*togo)
		return (EXIT_SUCCESS);
	ret = chdir(togo);
	if (ret == 0)
		return (EXIT_SUCCESS);
	ft_perror("cd", errno, *argv);
	return (EXIT_FAILURE);
}
