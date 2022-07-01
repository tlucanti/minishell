/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:35:59 by tlucanti          #+#    #+#             */
/*   Updated: 2022/07/01 13:04:51 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/enviroment.h"
#include "../inc/color.h"
#include "../inc/libft.h"

void	update_promt_init(t_promt *promt_ptr, char *__restrict buff)
{
	promt_ptr->user = ft_getenv_s("USER", (size_t *)&(promt_ptr->user_size));
	promt_ptr->cwd = ft_getenv_s("PWD", (size_t *)&(promt_ptr->cwd_size));
	promt_ptr->shift_0 = sizeof(READLINE_GREEN) - 1;
	promt_ptr->memcpy_0 = ft_memcpy(buff, READLINE_GREEN, promt_ptr->shift_0);
	promt_ptr->memcpy_1 = ft_memcpy(buff + promt_ptr->shift_0, promt_ptr->user,
			promt_ptr->user_size);
	promt_ptr->shift_1 = promt_ptr->shift_0 + promt_ptr->user_size;
	promt_ptr->memcpy_2 = ft_memcpy(buff + promt_ptr->shift_1, READLINE_WHITE":"
			READLINE_BLUE, sizeof(READLINE_WHITE) + sizeof(READLINE_BLUE) - 1);
	promt_ptr->shift = promt_ptr->shift_1 + sizeof(READLINE_WHITE)
		+ sizeof(READLINE_BLUE) - 1;
	promt_ptr->getcwd_0 = getcwd(buff + promt_ptr->shift, PATH_MAX);
	promt_ptr->memcpy_3 = ft_memcpy(buff + promt_ptr->shift, promt_ptr->cwd,
			promt_ptr->cwd_size);
	promt_ptr->home = ft_getenv("HOME", (size_t *)&(promt_ptr->home_size));
	promt_ptr->r_size = 0;
	promt_ptr->self = promt_ptr;
}
