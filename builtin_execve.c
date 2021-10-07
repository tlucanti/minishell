/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 22:22:39 by kostya            #+#    #+#             */
/*   Updated: 2021/09/15 22:54:50 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "minishell.h"
#include "memory.h"
#include "signal.h"
#include "error.h"

static char	*ft_execve_strsum(const char *str1, const char *str2) __attribute__((warn_unused_result));
static int	ft_iscolon(int c);
static void	builtin_execve__no_ret(char *const *argv) __attribute__((noreturn));

int	builtin_execve(char *const *argv)
// type commands in gdb to enable child debugging
// set follow-fork-mode child
// set detach-on-fork off
{
	pid_t	p_id;
	int		status;

	p_id = fork();
	if (p_id < 0)
		return (EXIT_FAILURE);
	else if (p_id == (pid_t)0)
	{
		signal(SIGINT, handler_signint_fork);
		builtin_execve__no_ret(argv);
	}
	else
	{
		waitpid(p_id, &status, 0);
		return (status);
	}
}

static void	builtin_execve__no_ret(char *const *argv)
{
	char	**path_argv;
	char	**env;
	char	*next_path;
	char	**path_argv_init;

	path_argv = ft_split(ft_getenv_s("PATH", NULL), ft_iscolon);
	path_argv_init = path_argv;
	env = mas_gen();
	if (**argv == '.' || **argv == '/')
	{
		execve(*argv, argv, env);
		ft_perror("minishell", errno, *argv);
		clear_split(path_argv_init);
		exit(1);
	}
	while (*path_argv)
	{
		next_path = ft_execve_strsum(*path_argv, *argv);
		execve(next_path, argv, env);
		// printf("%s: %d (%s)\n", next_path, ret, strerror(errno));
		++path_argv;
		if (errno != ENOENT)
		{
			ft_perror("minishell", errno, next_path);
			free(next_path);
			clear_split(path_argv_init);
			exit(1);
		}
		free(next_path);
	}
	ft_perror("minishell", ECNF, *argv);
	clear_split(path_argv_init);
	exit(1);
}

static char	*ft_execve_strsum(const char *str1, const char *str2)
{
	size_t	size1;
	size_t	size2;
	char	*sum;

	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
	sum = xmalloc(sizeof(char) * (size1 + size2 + 2));
	ft_memcpy(sum, str1, size1);
	sum[size1] = '/';
	ft_memcpy(sum + size1 + 1, str2, size2);
	sum[size1 + size2 + 2] = '\0';
	return (sum);
}

static int	ft_iscolon(int c)
{
	return (c == ':');
}
