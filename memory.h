/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 22:35:26 by kostya            #+#    #+#             */
/*   Updated: 2021/09/15 22:21:39 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <malloc.h>
# include <stdlib.h>

void	*xmalloc(size_t size) __attribute__((warn_unused_result));

#endif
