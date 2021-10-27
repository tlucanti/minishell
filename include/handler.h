/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:34:56 by kostya            #+#    #+#             */
/*   Updated: 2021/10/26 23:55:04 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
# define HANDLER_H

# include <signal.h>

void	handler_signint_fork(__attribute__((unused)) int signum) __attribute__((
				noreturn)) __attribute__((__nothrow__));
void	handler_signint_readline(__attribute__((unused)) int signum
			) __attribute__((__nothrow__));
void	handler_signint_heredoc(__attribute__((unused)) int signum
			) __attribute__((__nothrow__));

#endif // HANDLER_H
