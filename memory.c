/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:58:13 by kostya            #+#    #+#             */
/*   Updated: 2021/09/08 12:06:40 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*xmalloc(size_t size)
{
	register void *ptr = malloc(size);
	if (!ptr)
		exit(1);
//		g_main.at_exit("malloc");
	return (ptr);
}
