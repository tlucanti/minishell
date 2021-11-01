/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_bind_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 20:16:36 by kostya            #+#    #+#             */
/*   Updated: 2021/10/31 21:08:19 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef RLBINDKEY

void	ft_rl_bind_key(void)
{
	rl_bind_key('\t', rl_complete);
}

#else

void	ft_rl_bind_key(void)
{
}

#endif
