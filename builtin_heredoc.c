/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:58:07 by kostya            #+#    #+#             */
/*   Updated: 2021/10/25 21:21:46 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/memory.h"
#include "include/minishell.h"
#include "include/libft.h"

char	*builtin_heredoc(const char *end)
/*
** function reads from STDIN data for function run with `heredoc` syntax
** heredoc syntax: [end_symbol]\n[data]\n[end_symbol]
*/
{
	char	*input;
	char	*out;
	char	*str_tmp;
	size_t	size;
	size_t	new_size;

	size = 0;
	out = xmalloc(sizeof(char));
	out[0] = 0;
	while (1)
	{
		input = readline("> ");
		new_size = ft_strlen(input);
		if (!ft_memcmp(input, end, new_size + 1))
			return (out);
		str_tmp = xmalloc(sizeof(char) * (size + new_size + 1));
		ft_memcpy(str_tmp, out, size);
		ft_memcpy(str_tmp + size, input, new_size + 1);
		out = str_tmp;
		free(out);
	}
}
