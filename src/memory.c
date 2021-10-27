/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:58:13 by kostya            #+#    #+#             */
/*   Updated: 2021/10/27 14:55:43 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/memory.h"
#include "../inc/error.h"

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

uint	xfree(void *__restrict ptr)
/*
** function clears `ptr` memory and return `1`
*/
{
	free(ptr);
	return (1);
}
