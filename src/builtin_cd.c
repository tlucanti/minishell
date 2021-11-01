/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:22:41 by kostya            #+#    #+#             */
/*   Updated: 2021/10/31 20:05:00 by kostya           ###   ########.fr       */
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
	const char	*cwd;

	if (argv[2])
		return (ft_perror("cd", ETMA, NULL) + 1);
	togo = *(++argv);
	if (togo == NULL)
		togo = "~";
	if (togo[0] == '~')
		togo = ft_strjoin(ft_getenv_s("HOME", NULL), togo + 1);
	if (togo == NULL)
		togo = "";
	if (!*togo)
		return (EXIT_SUCCESS);
	ret = chdir(togo);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		list_insert(internal_env_storage(), ft_strdup("PWD"), ft_strdup("."));
	else
		list_insert(internal_env_storage(), ft_strdup("PWD"), getcwd(NULL, 0));
	if (ret == 0)
		return (EXIT_SUCCESS);
	ft_perror("cd", errno, *argv);
	return (EXIT_FAILURE);
}
