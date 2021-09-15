/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:34:56 by kostya            #+#    #+#             */
/*   Updated: 2021/09/15 23:18:14 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <signal.h>

void	handler_signint_fork(int signum) __attribute__((noreturn));
void	handler_signint_minishell(int signum);
void	handler_sigquit_minishell(int signum);

#endif
