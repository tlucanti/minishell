/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:00:38 by tlucanti          #+#    #+#             */
/*   Updated: 2021/01/20 12:00:43 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define NULLPTR 0
# define BUFFER_SIZE 255

typedef struct s_deque
{
	char			*str;
	size_t			size;
	struct s_deque	*next;
	struct s_deque	*prev;
}					t_deque;

typedef struct s_buffer
{
	char			buffer[BUFFER_SIZE];
	size_t			start;
	size_t			read_bytes;
}					t_buffer;

int					get_next_line(int fd, char **line);
size_t				gnl_loop(int fd, char **line, t_buffer **buff,
						t_deque **l_l);
size_t				ft_find_end(char *str, size_t size);
int					ft_lpf(t_deque **list, const char *str, size_t size);
int					ft_c(t_deque *lst, t_buffer **tbuff, int fd);
int					ft_lm(t_deque *list, char **line, int fd, t_buffer **tbuff);
void				*ft_memcpy_gnl(void *dst, const void *src, size_t size);
void				ft_memcpy_fast_gnl(unsigned char **dst, unsigned char **src,
						size_t xlen);
void				*ft_calloc1(size_t nmeb);

#endif
