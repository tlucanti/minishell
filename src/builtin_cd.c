/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:22:41 by kostya            #+#    #+#             */
/*   Updated: 2021/11/01 17:49:09 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/enviroment.h"
#include "../inc/error.h"
#include "../inc/libft.h"
#include "../inc/minishell.h"

int	__builtin_cd_extension_1(const char **__restrict togo_ptr, int *ret,
		int *oldpwd);

int	builtin_cd(char *__restrict const *__restrict argv)
/*
** function changes current working dir (CWD) of shell to path in first argument
** if no arguments provided - changing to ~ (HOME)
** if path is empty string - CWD will not chamge
** errno errors printed to STDERR
*/
{
	int			ret;
	int			oldpwd;
	const char	*togo;
	const char	*cwd;

	oldpwd = 0;
	if (argv[2])
		return (ft_perror("cd", ETMA, NULL) + 1);
	togo = *(++argv);
	if (__builtin_cd_extension_1(&togo, &ret, &oldpwd))
		return (ret);
	if (!*togo)
		return (EXIT_SUCCESS);
	ret = chdir(togo);
	cwd = getcwd(NULL, 0);
	list_insert(internal_env_storage(), ft_strdup("OLDPWD"),
		ft_strdup(ft_getenv_s("PWD", NULL)));
	if (cwd == NULL)
		list_insert(internal_env_storage(), ft_strdup("PWD"), ft_strdup("."));
	else
		list_insert(internal_env_storage(), ft_strdup("PWD"), getcwd(NULL, 0));
	if (oldpwd && !ret)
		oldpwd = builtin_pwd(NULL);
	return (ret && (ft_perror("cd", errno, *argv) + 1));
}

int	__builtin_cd_extension_1(const char **__restrict togo_ptr, int *ret,
		int *oldpwd)
{
	const char	*home;

	if ((*togo_ptr) && !ft_memcmp((*togo_ptr), "-", 2))
	{
		(*togo_ptr) = ft_getenv("OLDPWD", NULL);
		if ((*togo_ptr) == NULL)
		{
			*ret = 1;
			return (ft_perror("minishell", EOLDPWD, NULL) + 1);
		}
		*oldpwd = 1;
	}
	if ((*togo_ptr) == NULL)
		(*togo_ptr) = "~";
	if ((*togo_ptr)[0] == '~')
	{
		home = ft_getenv("HOME", NULL);
		if (!home)
			*togo_ptr = NULL;
		else
			(*togo_ptr) = ft_strjoin(home, (*togo_ptr) + 1);
	}
	if ((*togo_ptr) == NULL)
		(*togo_ptr) = "";
	return (0);
}
