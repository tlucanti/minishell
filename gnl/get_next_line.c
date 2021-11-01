/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:55:29 by tlucanti          #+#    #+#             */
/*   Updated: 2021/11/01 14:30:10 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static t_buffer		*buff[1024] = {0};
	int					end_ind;
	t_deque				*l_l;
	size_t				ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == 0)
		return (-1);
	l_l = NULL;
	if (buff[fd] == NULL)
		buff[fd] = (t_buffer *)xmalloc(sizeof(t_buffer));
	if (buff[fd] == NULL)
		return (-1);
	ft_memset(buff[fd], 0, sizeof(t_buffer));
	ret = gnl_loop(fd, line, buff, &l_l);
	if ((ret & 0xffffffff) != 2)
		return (ret);
	end_ind = ret >> 32u;
	if (ft_lpf(&l_l, buff[fd]->buffer + buff[fd]->start, end_ind))
		return (ft_c(l_l, buff, fd));
	buff[fd]->start += end_ind;
	if (ft_lm(l_l, line, fd, buff) == -1)
		return (-1);
	return (ft_c(l_l, buff, -1) + 2);
}

size_t	gnl_loop(int fd, char **line, t_buffer **buff, t_deque **l_l)
{
	size_t	ret;
	int		end_ind;

	end_ind = ft_find_end(buff[fd]->buffer + buff[fd]->start,
			buff[fd]->read_bytes - buff[fd]->start);
	while (end_ind == -1)
	{
		if (ft_lpf(l_l, buff[fd]->buffer + buff[fd]->start, buff[fd]->read_bytes
				- buff[fd]->start) || ft_assign64(&buff[fd]->read_bytes,
				read(fd, buff[fd]->buffer, BUFFER_SIZE)) == (size_t)(-1))
			return (ft_c(*l_l, buff, fd));
		else if (buff[fd]->read_bytes == 0)
		{
			if (ft_lm(*l_l, line, fd, buff) == -1)
				return (-1);
			return (ft_c(*l_l, buff, fd) + 1);
		}
		buff[fd]->start = 0;
		end_ind = ft_find_end(buff[fd]->buffer + buff[fd]->start,
				buff[fd]->read_bytes - buff[fd]->start);
	}
	ret = 0;
	ret |= ((size_t)end_ind << 32u) | 2;
	return (ret);
}

int	ft_lpf(t_deque **list, const char *str, size_t size)
{
	char	*new_str;
	t_deque	*new_lst;

	if (size-- == 0)
		return (0);
	if (str[size] != 0xa)
		size++;
	new_str = (char *)xmalloc(size);
	if (new_str == NULL)
		return (1);
	new_lst = (t_deque *)xmalloc(sizeof(t_deque));
	if (new_lst == NULL)
		return (1);
	new_lst->str = new_str;
	new_lst->size = size;
	new_lst->prev = NULL;
	ft_memcpy_gnl(new_str, (void *)str, size);
	new_lst->next = *list;
	if (*list != NULL)
		(*list)->prev = new_lst;
	*list = new_lst;
	return (0);
}

int	ft_c(t_deque *lst, t_buffer **tbuff, int fd)
{
	t_deque	*next;
	size_t	size;

	while (lst)
	{
		next = lst->next;
		free(lst->str);
		free(lst);
		lst = next;
	}
	if (fd != -1)
	{
		size = 0;
		while (size < (size_t)BUFFER_SIZE)
			tbuff[fd]->buffer[size++] = 0;
		free(tbuff[fd]);
		tbuff[fd] = 0;
	}
	return (-1);
}

int	ft_lm(t_deque *list, char **line, int fd, t_buffer **tbuff)
{
	size_t	total_size;
	t_deque	*lst_ptr;
	char	*line_ptr;

	total_size = 0;
	lst_ptr = list;
	while (lst_ptr != NULL)
	{
		total_size += lst_ptr->size;
		if (lst_ptr->next == NULL)
			break ;
		lst_ptr = lst_ptr->next;
	}
	*line = (char *)xmalloc(total_size + 1);
	if (*line == NULL)
		return (ft_c(list, tbuff, fd));
	line_ptr = *line;
	while (lst_ptr)
	{
		line_ptr = ft_memcpy_gnl(line_ptr, lst_ptr->str, lst_ptr->size);
		lst_ptr = lst_ptr->prev;
	}
	*line_ptr = 0;
	return (0);
}
