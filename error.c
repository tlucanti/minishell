/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:59:44 by kostya            #+#    #+#             */
/*   Updated: 2021/09/18 18:57:57 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "colors.h"
#include "enviroment.h"
#include "minishell.h"

static void			putsfd(int fd, const char *str);
static const char	*xstrerror(int errorcode);
static const char	*xstrsignal(int signum);

#include <string.h>
#define ft_strlen strlen

void	ft_perror(const char *parent, int errorcode, const char *arg)
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

void	ft_psignal(int pid, int signum, const char *parent)
{
	const char	*message;

	message = xstrsignal(signum);
	if (!message)
		return ;
	putsfd(2, TERM_BLUE "[2]\t" ERROR);
	putsfd(2, ft_itoa(pid));
	putsfd(2,TERM_WHITE ": ");
	putsfd(2, xstrsignal(signum));
	putsfd(2, "\t" WARNING);
	putsfd(2, parent);
	putsfd(2, RESET "\n");
}

void	xexit(int status)
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
	return (strerror(errorcode));
}

static const char	*xstrsignal(int signum)
{
	if (signum == SIGINT)
		return ("interrupted");
	else if (signum == SIGILL)
		return ("illegal hardware instruction (core dumped)");
	else if (signum == SIGABRT)
		return ("abort (core dumped)");
	else if (signum == SIGFPE)
		return ("floating point exception (core dumped)");
	else if (signum == SIGSEGV)
		return ("segmentation fault (core dumped)");
	else if (signum == SIGTERM)
		return ("terminated");
	else if (signum == SIGHUP)
		return ("hangup");
	else if (signum == SIGQUIT)
		return ("quit (core dumped)");
	else if (signum == SIGTRAP)
		return ("trace trap (core dumped)");
	else if (signum == SIGKILL)
		return ("killed");
	else if (signum == SIGBUS)
		return ("bus error (core dumped)");
	else if (signum == SIGSYS)
		return ("invalid system call (core dumped)");
	else if (signum == SIGPIPE)
		return ("broken pipe");
	else if (signum == SIGALRM)
		return ("alarm");
	else if (signum == SIGTSTP)
		return ("suspended");
	else
		return (NULL);
}
