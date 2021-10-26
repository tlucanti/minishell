/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:34:34 by kostya            #+#    #+#             */
/*   Updated: 2021/10/26 22:46:16 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/error.h"
#include "include/minishell.h"

void	handler_signint_fork(__attribute__((unused)) int signum)
{
	exit(SIGINT);
}

void	handler_signint_readline(__attribute__((unused)) int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handler_signint_heredoc(__attribute__((unused)) int signum)
{
	printf("\n");
	close(0);
}
