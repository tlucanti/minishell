/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:59:44 by kostya            #+#    #+#             */
/*   Updated: 2021/09/10 21:14:33 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "colors.h"

static void	putsfd(int fd, const char *str);
static const char *xstrerror(int errorcode);

#include <string.h>
#define ft_strlen strlen

void ft_perror(const char *parent, int errorcode, const char *arg)
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
}

void	xexit(int status)
{
	exit(status);
}

static void	putsfd(int fd, const char *str)
{
	size_t	size;

	size = ft_strlen(str);
	size = write(fd, str, size);
}

static const char *xstrerror(int errorcode)
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
	return strerror(errorcode);
}
