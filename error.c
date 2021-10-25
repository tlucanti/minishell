/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:59:44 by kostya            #+#    #+#             */
/*   Updated: 2021/10/25 20:57:26 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/error.h"
#include "include/color.h"
#include "include/enviroment.h"
#include "include/minishell.h"
#include "include/libft.h"

static void			putsfd(int fd, const char *str);
static const char	*xstrerror(int errorcode);

int	ft_perror(const char *parent, int errorcode, const char *arg)
/*
** function prints error message to STDOUT by `errorcode` in format:
** {RED_COLOR}[`parent`]: {WHITE_COLOR}[ERROR_MESSAGE]: {YELLOW_COLOR}[`arg`]\n
** [ERROR_MESSAGE] is internal shell error message or standard glibc error
** message (like `perror` do)
*/
{
	putsfd(2, ERROR);
	putsfd(2, parent);
	putsfd(2, TERM_WHITE);
	putsfd(2, ": ");
	putsfd(2, xstrerror(errorcode));
	if (arg)
	{
		putsfd(2, ": ");
		putsfd(2, WARNING);
		putsfd(2, arg);
	}
	putsfd(2, RESET "\n");
	return (0);
}

void	xexit(int status)
/*
** function free all allocated memory and terminates program
*/
{
	list_clear(internal_env_storage());
	set_autoattr(0, 1, ECHOCTL);
	exit(status);
}

static void	putsfd(int fd, const char *str)
{
	size_t	size;

	size = ft_strlen(str);
	size = write(fd, str, size);
}

static const char	*xstrerror(int errorcode)
{
	if (errorcode == ECNF)
		return ("command not found");
	else if (errorcode == ETMA)
		return ("too many arguments");
	else if (errorcode == ENAVI)
		return ("not a valid identifier");
	else if (errorcode == ENEA)
		return ("not enough arguments");
	else if (errorcode == ENUMR)
		return ("numeric argument required");
	else if (errorcode == ETOKEN)
		return ("syntax error, unexpected token");
	else if (errorcode == ESYNT)
		return ("syntax error");
	return (strerror(errorcode));
}
