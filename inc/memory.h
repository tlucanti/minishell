/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 22:35:26 by kostya            #+#    #+#             */
/*   Updated: 2022/07/01 12:13:43 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# ifdef __linux__
#  include <malloc.h>
# else
#  include <stdlib.h>
# endif

void			*xmalloc(size_t size) __attribute__((malloc)) __attribute__((
						warn_unused_result)) __attribute__((__nothrow__));
unsigned int	xfree(void *__restrict ptr)
				__attribute__((__nothrow__));
void			free_s(void *__restrict ptr)
				__attribute__((__nothrow__));

#endif // MEMORY_H
