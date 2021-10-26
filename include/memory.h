/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 22:35:26 by kostya            #+#    #+#             */
/*   Updated: 2021/10/26 23:55:16 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <malloc.h>
# include <stdlib.h>

void	*xmalloc(size_t size) __attribute__((malloc)) __attribute__((
				warn_unused_result)) __attribute__((__nothrow__));
uint	xfree(void *__restrict ptr) __attribute__((__nothrow__));

#endif // MEMORY_H
