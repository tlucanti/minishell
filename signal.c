/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:34:34 by kostya            #+#    #+#             */
/*   Updated: 2021/09/18 18:12:52 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "error.h"
#include "minishell.h"

void	handler_signint_fork(int signum)
{
	(void)signum;
	printf("\n\nhandle inside fork\n\n\n");
	exit(SIGINT);
}

void	handler_signint_readline(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}