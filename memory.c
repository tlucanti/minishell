/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:58:13 by kostya            #+#    #+#             */
/*   Updated: 2021/09/15 22:20:09 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "error.h"

void	*xmalloc(size_t size)
{
	register void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit(1);
	return (ptr);
}
