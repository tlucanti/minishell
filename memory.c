/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:58:13 by kostya            #+#    #+#             */
/*   Updated: 2021/10/08 14:05:03 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/memory.h"
#include "include/error.h"

void	*xmalloc(size_t size)
/*
** function allocates memory or terminates program if allocation faled
*/
{
	register void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		xexit(1);
	return (ptr);
}

inline uint	xfree(void *ptr)
/*
** function clears `ptr` memory and return `1`
*/
{
	free(ptr);
	return (1);
}
