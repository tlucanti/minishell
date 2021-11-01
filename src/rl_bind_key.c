/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_bind_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 20:16:36 by kostya            #+#    #+#             */
/*   Updated: 2021/11/01 19:57:35 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifndef RLBINDKEY

void	ft_rl_bind_key(void)
{
	rl_bind_key('\t', rl_complete);
}

#else

void	ft_rl_bind_key(void)
{
}

#endif
