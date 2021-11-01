/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:00:14 by kostya            #+#    #+#             */
/*   Updated: 2021/11/01 16:13:00 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

int		ft_perror(const char *__restrict parent, int errorcode,
			const char *__restrict arg)
		__attribute__((__nothrow__));
void	ft_psignal(int pid, int signum, const char *__restrict parent)
		__attribute__((__nothrow__));
void	xexit(int status)
		__attribute__((noreturn)) __attribute__((__nothrow__));

# define ECNF		-2		// ERROR COMMAND NOT FOUND
# define ETMA		-3		// ERROR TOO MANY ARGUMENTS
# define ENAVI		-4		// ERROR NOT A VALID IDENTIFIER
# define ENEA		-5		// ERROR NOT ENOUGH ARGUMENTS
# define ENUMR		-6		// ERROR NUMERIC ARGUMENT REQUIRED
# define ETOKEN		-7		// ERROR UNEXPECTED TOKEN IN PARSE
# define ESYNT		-8		// ERROR INVALID SYNTAX
# define EOLDPWD	-9		// ERROR $OLDPWD NOT SET

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif
# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif

#endif // ERROR_H
