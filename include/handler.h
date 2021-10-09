/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:34:56 by kostya            #+#    #+#             */
/*   Updated: 2021/10/08 17:01:23 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
# define HANDLER_H

# include <signal.h>

void	handler_signint_fork(int signum) __attribute__((noreturn));
void	handler_signint_readline(int signum);

#endif // HANDLER_H
