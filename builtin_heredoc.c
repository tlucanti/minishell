/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:58:07 by kostya            #+#    #+#             */
/*   Updated: 2021/09/17 14:18:01 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "minishell.h"

char	*builtin_heredoc(const char *end)
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