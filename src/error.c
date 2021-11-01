/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:59:44 by kostya            #+#    #+#             */
/*   Updated: 2021/11/01 17:56:01 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/error.h"
#include "../inc/color.h"
#include "../inc/enviroment.h"
#include "../inc/minishell.h"
#include "../inc/libft.h"

static const char	*xstrerror(int errorcode) __attribute__((
							warn_unused_result)) __attribute__((
							__nothrow__));

int	ft_perror(const char *__restrict parent, int errorcode,
		const char *__restrict arg)
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
	exit(status);
}

void	putsfd(int fd, const char *__restrict str)
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
	else if (errorcode == EOLDPWD)
		return ("OLDPWD not set");
	return (strerror(errorcode));
}

int	exit_status_storage(int status, int set)
{
	static int	_internal_status = 0;

	if (set)
		_internal_status = status;
	return (_internal_status);
}
