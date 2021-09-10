/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:22:41 by kostya            #+#    #+#             */
/*   Updated: 2021/09/10 21:14:33 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "error.h"

#define ft_memcmp memcmp

int	builtin_cd(char *const *argv)
{
	int			ret;
	const char	*togo;

	togo = *(++argv);
	// if no args - go to ~
	if (togo == NULL)
		togo = "~";
	if (!ft_memcmp("~", togo, 2))
		togo = ft_getenv("HOME", NULL);
	// if we want to go $HOME, but it deleted - we qre not going anywhere
	if (togo == NULL)
		togo = "";
	// if empty string ("") got as argument - we qre not going anywhere
	if (!*togo)
		return (EXIT_SUCCESS);
	ret = chdir(togo);
	if (ret == 0)
		return (EXIT_SUCCESS);
	ft_perror("cd", errno, *argv);
	return (EXIT_FAILURE);
}
