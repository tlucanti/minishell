/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:00:14 by kostya            #+#    #+#             */
/*   Updated: 2021/09/15 22:19:07 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <errno.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_perror(const char *parent, int errorcode, const char *arg);
void	xexit(int status) __attribute__((noreturn));

# define ECNF -2		// ERROR COMMAND NOT FOUND
# define ETMA -3		// ERROR TOO MANY ARGUMENTS
# define ENAVI -4		// ERROR NOT A VALID IDENTIFIER
# define ENEA -5		// ERROR NOT ENOUGH ARGUMENTS
# define ENUMR -6		// ERROR NUMERIC ARGUMENT REQUIRED

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif
# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif

#endif
