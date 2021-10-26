/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:32:39 by kostya            #+#    #+#             */
/*   Updated: 2021/10/26 23:43:40 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parser.h"
#include "include/enviroment.h"
#include "include/memory.h"
#include "include/error.h"
#include "include/libft.h"
#include "include/minishell.h"

static char	**implement_redirect(char **__restrict ptr,
				int _in_out[2]) __attribute__((warn_unused_result));
static int	implement_heredoc(
				const char *__restrict end) __attribute__((warn_unused_result));
static char	**materialize_argv(char *__restrict *__restrict start,
				uint argv_size) __attribute__((warn_unused_result));

static int	complex_parser(char **__restrict array,
				int _do_pipe) __attribute__((warn_unused_result));
static int	backup_fd_in_out(int _in_out[2], int init);
static int	builtin(char **__restrict arr) __attribute__((
					warn_unused_result)) __attribute__((__nothrow__));

int	complex_parser_decorator(char **__restrict array, int _do_pipe)
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

static int	complex_parser(char **__restrict array, int _do_pipe)
{
	uint	argv_size;
	char	**end;
	int		_in_out[2];
	int		_frk;
	int		was_redirect;

	was_redirect = 0;
	_in_out[1] = STDOUT;
	if (_do_pipe != -1)
		_in_out[0] = _do_pipe;
	else
		_in_out[0] = STDIN;
	argv_size = 0;
	end = redirect_sharp(array, &argv_size, _in_out, &was_redirect);
	if (end == (char **)1)
		return (1);
	_frk = pipe_sharp(end, _in_out, &_do_pipe, was_redirect);
	if (_frk == -1)
		return (1);
	if (!_frk)
		return (fork_sharp(array, _in_out, end, argv_size));
	else
		return (complex_parser_decorator(end + 1, _do_pipe));
}

static char	**materialize_argv(char *__restrict *__restrict start,
				uint argv_size)
{
	char	**argv;
	char	**ptr;

	argv = (char **)xmalloc(sizeof(char *) * (argv_size + 1));
	ptr = argv;
	argv[argv_size] = NULL;
	while (argv_size)
	{
		if ((size_t)(*start) < ANY_TOKEN && (size_t)(*start) & REDIRECT)
			start += 2;
		else if ((size_t)(*start) < ANY_TOKEN && (size_t)(*start) & SKIP_PARSER)
			++start;
		else
		{
			*ptr = ft_strdup(*start);
			argv_size--;
			++ptr;
			++start;
		}
	}
	return (argv);
}

static int	backup_fd_in_out(int _in_out[2], int init)
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

static int	builtin(char **__restrict arr)
{
	int	ret;

	if (!ft_strcmp(arr[0], "echo"))
		ret = builtin_echo(arr);
	else if (!ft_strcmp(arr[0], "cd"))
		ret = builtin_cd(arr);
	else if (!ft_strcmp(arr[0], "pwd"))
		ret = builtin_pwd(arr);
	else if (!ft_strcmp(arr[0], "export"))
		ret = builtin_export(arr);
	else if (!ft_strcmp(arr[0], "unset"))
		ret = builtin_unset(arr);
	else if (!ft_strcmp(arr[0], "env"))
		ret = builtin_env(arr);
	else if (!ft_strcmp(arr[0], "exit"))
		ret = builtin_exit(arr);
	else
		ret = builtin_execve(arr);
	return (ret);
}
