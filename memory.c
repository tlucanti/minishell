/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 22:35:01 by kostya            #+#    #+#             */
/*   Updated: 2021/09/06 00:17:22 by kostya           ###   ########.fr       */
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
