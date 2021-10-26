/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:32:39 by kostya            #+#    #+#             */
/*   Updated: 2021/10/26 22:47:10 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parser.h"
#include "include/enviroment.h"
#include "include/memory.h"
#include "include/error.h"
#include "include/libft.h"
#include "include/minishell.h"

static char	**implement_redirect(char **__restrict ptr, int _in_out[2]) __attribute__((warn_unused_result));
static int	implement_heredoc(const char *__restrict end) __attribute__((warn_unused_result));
static char	**materialize_argv(char *__restrict *__restrict start, uint argv_size) __attribute__((warn_unused_result));
static char	**redirect_sharp(char **__restrict ptr, uint *__restrict argv_size, int _in_out[2], int *__restrict was_redirect) __attribute__((warn_unused_result));
static int	pipe_sharp(char *__restrict *__restrict ptr, int _in_out[2], int *__restrict _do_pipe, int was_redirect) __attribute__((warn_unused_result));
static int	fork_sharp(char *__restrict *__restrict array, int _in_out[2], char *__restrict *__restrict end, uint argv_size) __attribute__((warn_unused_result));
static int complex_parser(char **__restrict array, int _do_pipe) __attribute__((warn_unused_result));
static int backup_fd_in_out(int _in_out[2], int init);

int complex_parser_decorator(char **__restrict array, int _do_pipe)
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

static char	**redirect_sharp(char **__restrict  ptr, uint *__restrict argv_size, int _in_out[2], int *__restrict was_redirect)
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

static int	pipe_sharp(char *__restrict *__restrict ptr, int _in_out[2], int *__restrict _do_pipe, int was_redirect)
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
		{
			/* CHILD process closing reading part of pipe, because it will
			** write to pipe
			*/
			close(_pipes_in_out[1]);
		}
		else
		{
			/* PARENT process closing writing part of pipe, because it will
			** read from pipe
			*/
			close(_pipes_in_out[0]);
		}
		return (_frk);
	}
	return (0);
}

static int	fork_sharp(char *__restrict *__restrict array, int _in_out[2], char *__restrict *__restrict end, uint argv_size)
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

static int complex_parser(char **__restrict array, int _do_pipe)
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
	if (!_frk) // CHILD or MAIN process
		return (fork_sharp(array, _in_out, end, argv_size));
	else // PARENT if got PIPE
		return (complex_parser_decorator(end + 1, _do_pipe));
}

static char	**implement_redirect(char **__restrict ptr, int _in_out[2])
{
	const mode_t	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	if (*ptr == OUT_WRITE_PTR || *ptr == OUT_APPEND_PTR)
	{
		close(_in_out[1]);
		if (*ptr == OUT_WRITE_PTR)
			_in_out[1] = open(ptr[1], O_CREAT | O_RDWR | O_TRUNC, mode);
		else
			_in_out[1] = open(ptr[1], O_CREAT | O_RDWR | O_APPEND, mode);
	}
	else if (*ptr == INPUT_PTR || *ptr == HEREDOC_PTR)
	{
		close(_in_out[0]);
		if (*ptr == INPUT_PTR)
			_in_out[0] = open(ptr[1], O_RDONLY);
		else
			_in_out[0] = implement_heredoc(ptr[1]);
	}
	if (_in_out[0] == -1 || _in_out[1] == -1)
		return ((char **)(size_t)ft_perror("open", errno, ptr[1]));
	return (ptr + 2);
}

static int	implement_heredoc(const char *__restrict end)
{
	char	*heredoc_str;
	int		_pipes_in_out[2];
	int		_frk;
	int		_backup_x2_in;

	_backup_x2_in = dup(backup_fd_in_out(NULL, 0));
	if (dup2(_backup_x2_in, STDIN) == -1)
		return (ft_perror("dup2", errno, NULL) - 1);
	heredoc_str = builtin_heredoc(end);
	close(STDIN);
	if (pipe(_pipes_in_out))
		return (ft_perror("pipe", errno, NULL) - 1);
	_frk = fork();
	if (_frk == -1)
		return (ft_perror("fork", errno, NULL) - 1);
	if (!_frk) // CHILD process
	{
		close(_pipes_in_out[0]);
		putsfd(_pipes_in_out[1], heredoc_str);
		free(heredoc_str);
		close(_pipes_in_out[1]);
		exit(0);
	}
	else
	{
		close(_pipes_in_out[1]);
		return (_pipes_in_out[0]);
	}
	return 0;
}

static char	**materialize_argv(char *__restrict *__restrict start, uint argv_size)
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

static int backup_fd_in_out(int _in_out[2], int init)
/*
** function initialises backup values for descriptors to return them after
** runnung execve or builtins (if `init` parameter is `true`) and returns
** saved value of backup stdin file descriptor)
*/
{
	static	int _in_out_backup_storage[2];

	if (init)
	{
		_in_out[0] = dup(STDIN);
		_in_out[1] = dup(STDOUT);
		_in_out_backup_storage[0] = _in_out[0];
		_in_out_backup_storage[1] = _in_out[1];
	}
	return (_in_out_backup_storage[0]);
}
