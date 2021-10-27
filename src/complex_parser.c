/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:32:39 by kostya            #+#    #+#             */
/*   Updated: 2021/10/27 14:55:45 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/enviroment.h"
#include "../inc/memory.h"
#include "../inc/error.h"
#include "../inc/libft.h"
#include "../inc/minishell.h"

static int	complex_parser(char *__restrict *__restrict array,
				int _do_pipe) __attribute__((warn_unused_result));

int	complex_parser_decorator(char *__restrict *__restrict array, int _do_pipe)
{
	int		_backup_in_out[2];
	int		_status;
	int		ret;
	void	*_;

	backup_fd_in_out(_backup_in_out, 1);
	if (_backup_in_out[0] == -1 || _backup_in_out[1] == -1)
	{
		ft_perror("dup", errno, NULL);
		return (errno);
	}
	_ = builtin_heredoc_prompt(1);
	ret = complex_parser(array, _do_pipe);
	_status = 0;
	_status |= dup2(_backup_in_out[1], STDOUT);
	_status |= dup2(_backup_in_out[0], STDIN);
	if (_status == -1)
	{
		ft_perror("dup2", errno, NULL);
		return (errno);
	}
	(void)_;
	return (ret);
}

static int	complex_parser(char *__restrict *__restrict array, int _do_pipe)
{
	char *__restrict	*end;
	uint				argv_size;
	int					_in_out[2];
	int					_frk;
	int					was_redirect;

	was_redirect = 0;
	_in_out[1] = STDOUT;
	if (_do_pipe != -1)
		_in_out[0] = _do_pipe;
	else
		_in_out[0] = STDIN;
	argv_size = 0;
	end = redirect_shard(array, &argv_size, _in_out, &was_redirect);
	if (end == (char **)1)
		return (1);
	_frk = pipe_shard(end, _in_out, &_do_pipe, was_redirect);
	if (_frk == -1)
		return (1);
	if (!_frk)
		return (fork_shard(array, _in_out, end, argv_size));
	else
		return (complex_parser_decorator(end + 1, _do_pipe));
}

int	backup_fd_in_out(int _in_out[2], int init)
/*
** function initialises backup values for descriptors to return them after
** runnung execve or builtins (if `init` parameter is `true`) and returns
** saved value of backup stdin file descriptor)
*/
{
	static int	_in_out_backup_storage[2];

	if (init)
	{
		_in_out[0] = dup(STDIN);
		_in_out[1] = dup(STDOUT);
		_in_out_backup_storage[0] = _in_out[0];
		_in_out_backup_storage[1] = _in_out[1];
	}
	return (_in_out_backup_storage[0]);
}
