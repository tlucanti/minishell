/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 22:35:26 by kostya            #+#    #+#             */
/*   Updated: 2022/06/29 11:51:07 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# ifdef __linux__
#  include <malloc.h>
# else
#  include <stdlib.h>
# endif

typedef unsigned int uint;

void	*xmalloc(size_t size) __attribute__((malloc)) __attribute__((
				warn_unused_result)) __attribute__((__nothrow__));
uint	xfree(void *__restrict ptr)
		__attribute__((__nothrow__));
void	free_s(void *__restrict ptr)
		__attribute__((__nothrow__));

#endif // MEMORY_H
