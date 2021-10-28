/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ancient_shards.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:37:45 by kostya            #+#    #+#             */
/*   Updated: 2021/10/28 17:48:57 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/minishell.h"
#include "../inc/error.h"
#include "../inc/libft.h"
#include "../inc/memory.h"

static int	builtin(char **__restrict arr) __attribute__((
					warn_unused_result)) __attribute__((__nothrow__));
static char	**materialize_argv(char *__restrict *__restrict start,
				uint argv_size) __attribute__((
					warn_unused_result)) __attribute__((__nothrow__));

char	*__restrict	*redirect_shard(char *__restrict *__restrict ptr,
				uint *__restrict argv_size)
{
	while (*ptr && *ptr != PIPE_PTR)
	{
		if ((size_t)(*ptr) < ANY_TOKEN && (size_t)(*ptr) & REDIRECT)
		{
			ptr = implement_redirect(ptr);
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

int	pipe_shard(char *__restrict *__restrict ptr)
{
	int		_pipes_in_out[2];
	int		_frk;

	if (*ptr == PIPE_PTR)
	{
		if (pipe(_pipes_in_out))
			return (ft_perror("pipe", errno, NULL) - 1);
		_frk = fork();
		if (_frk == -1)
			return (ft_perror("fork", errno, NULL) - 1);
		if (_frk)
		{
			close(_pipes_in_out[1]);
			close(STDIN);
			dup(_pipes_in_out[0]);
		}
		else
		{
			close(_pipes_in_out[0]);
			close(STDOUT);
			dup(_pipes_in_out[1]);
		}
		return (_frk);
	}
	return (0);
}

int	fork_shard(char *__restrict *__restrict array,
		char *__restrict *__restrict end, uint argv_size)
{
	int		ret;
	char	**argv;
	uint	i;

	argv = materialize_argv(array, argv_size);
	ret = builtin(argv);
	i = 0;
	while (i < argv_size)
		free(argv[i++]);
	free(argv);
	if (*end == PIPE_PTR)
		exit(0);
	return (ret);
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
