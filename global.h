/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 23:59:15 by kostya            #+#    #+#             */
/*   Updated: 2021/09/09 14:45:08 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
#define GLOBAL_H

#ifndef PATH_MAX
# define PATH_MAX 4096
#endif
typedef struct g_main_st_s
{
	char			promt[PATH_MAX];
	void			(*at_exit) (const char *);
	void			*env;
} g_main_st_t;

#endif
