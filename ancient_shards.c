/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ancient_shards.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:37:45 by kostya            #+#    #+#             */
/*   Updated: 2021/10/26 23:38:22 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parser.h"

char	**redirect_shard(char **__restrict ptr, uint *__restrict argv_size,
				int _in_out[2], int *__restrict was_redirect)
{
	while (*ptr && *ptr != PIPE_PTR)
	{
		if ((size_t)(*ptr) < ANY_TOKEN && (size_t)(*ptr) & REDIRECT)
		{
			*was_redirect = 1;
			ptr = implement_redirect(ptr, _in_out);
			if (!ptr)
				return ((char **)1);
		}
		else if ((size_t)(*ptr) < ANY_TOKEN && (size_t)(*ptr) & SKIP_PARSER)
			++ptr;
		else
		{
			++ptr;
			++(*argv_size);
		}
	}
	return (ptr);
}

int	pipe_shard(char *__restrict *__restrict ptr, int _in_out[2],
				int *__restrict _do_pipe, int was_redirect)
{
	int		_pipes_in_out[2];
	int		_frk;

	if (*ptr == PIPE_PTR)
	{
		if (pipe(_pipes_in_out))
			return (ft_perror("pipe", errno, NULL) - 1);
		*_do_pipe = _pipes_in_out[0];
		if (!was_redirect)
		{
			close(_in_out[1]);
			_in_out[1] = _pipes_in_out[1];
		}
		_frk = fork();
		if (_frk == -1)
			return (ft_perror("fork", errno, NULL) - 1);
		if (_frk)
			close(_pipes_in_out[1]);
		else
			close(_pipes_in_out[0]);
		return (_frk);
	}
	return (0);
}

int	fork_shard(char *__restrict *__restrict array, int _in_out[2],
				char *__restrict *__restrict end, uint argv_size)
{
	int	_status;
	int	ret;

	_status = 0;
	_status |= dup2(_in_out[0], STDIN);
	_status |= dup2(_in_out[1], STDOUT);
	if (_status == -1)
	{
		ft_perror("dup2", errno, NULL);
		return (errno);
	}
	ret = builtin(materialize_argv(array, argv_size));
	if (*end == PIPE_PTR)
		exit(0);
	return (ret);
}
