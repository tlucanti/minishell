/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 13:23:17 by kostya            #+#    #+#             */
/*   Updated: 2021/11/05 16:42:28 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/error.h"
#include "../inc/color.h"

static const char	*xstrsignal(int signum) __attribute__((
							warn_unused_result)) __attribute__((__nothrow__));
static const char	*__xstrsignal_extension(int signum)	__attribute__((
							warn_unused_result)) __attribute__((__nothrow__));

void	ft_psignal(int pid, int signum, const char *__restrict parent)
/*
** function prints signal handling message for signal handled in child process
** in format:
** {BLUE_COLOR}[INTERNAL_PID] {WHITE_COLOR}[GLOBAL_PID]: [SIGNAL_MESSAGE] \
** {YELLOW_COLOR}[`parent`]
** [SIGNAL_MESSAGE] is standard glibc error message (like `psignal` do)
*/
{
	const char	*message;
	char		*pid_str;

	message = xstrsignal(signum);
	if (!message)
		return ;
	pid_str = ft_itoa(pid);
	ft_putstr_fd(TERM_BLUE "[2]\t" ERROR, 2);
	ft_putstr_fd(pid_str, 2);
	ft_putstr_fd(TERM_WHITE ": ", 2);
	ft_putstr_fd(xstrsignal(signum), 2);
	ft_putstr_fd("\t" WARNING, 2);
	ft_putstr_fd(parent, 2);
	ft_putstr_fd(RESET "\n", 2);
	free(pid_str);
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
	else
		return (__xstrsignal_extension(signum));
}

static const char	*__xstrsignal_extension(int signum)
{
	if (signum == SIGSYS)
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
