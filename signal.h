/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:34:56 by kostya            #+#    #+#             */
/*   Updated: 2021/09/18 18:04:13 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <signal.h>

void	handler_signint_fork(int signum) __attribute__((noreturn));
void	handler_signint_minishell(int signum);
void	handler_sigquit_minishell(int signum);
void	handler_signint_readline(int signum);
void	handler_sigstp_fork(int signum);

#endif
