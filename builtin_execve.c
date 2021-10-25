/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 22:22:39 by kostya            #+#    #+#             */
/*   Updated: 2021/10/25 19:31:36 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/enviroment.h"
#include "include/minishell.h"
#include "include/memory.h"
#include "include/handler.h"
#include "include/error.h"
#include "include/libft.h"

int			ft_iscolon(int c);
static char	*__builtin_execve_strsum(const char *str1, const char *str2)
			__attribute__((warn_unused_result));
static void	__builtin_execve_no_ret(char *const *argv)
			__attribute__((noreturn));
static void	__builtin_execve_current_dir(char *const *argv,
				char **path_argv_init, char *const *env)
			__attribute__((noreturn));

int	builtin_execve(char *const *argv)
/*
** function statrts program provided in argv[0] with arguments provided in
** argv[1:] with enviroment variables array argenv
** function searches binaries in $PATH enviroment variable or in current
** working directory (CWD)
** errno errors printed to STDERR
**
** type commands in gdb to enable child debugging
** set follow-fork-mode child
** set detach-on-fork off
** type commands in gdb to enable parent debugging
** set follow-fork-mode parent
*/
{
	pid_t	p_id;
	int		status;

	p_id = fork();
	if (p_id < 0)
		return (EXIT_FAILURE);
	else if (p_id == (pid_t)0)
	{
		signal(SIGINT, handler_signint_fork);
		__builtin_execve_no_ret(argv);
	}
	else
	{
		waitpid(p_id, &status, 0);
		ft_psignal(p_id, status & 0x7f, argv[0]);
		return (status);
	}
}

static void	__builtin_execve_no_ret(char *const *argv)
{
	char	**path_argv;
	char	**env;
	char	*next_path;
	char	**path_argv_init;

	path_argv = ft_split(ft_getenv_s("PATH", NULL), ft_iscolon);
	path_argv_init = path_argv;
	env = mas_gen();
	if (**argv == '.' || **argv == '/')
		__builtin_execve_current_dir(argv, path_argv_init, env);
	while (*path_argv)
	{
		next_path = __builtin_execve_strsum(*path_argv++, *argv);
		if (access(next_path, F_OK) != 0 && xfree(next_path))
			continue ;
		execve(next_path, argv, env);
		ft_perror("minishell", errno, next_path);
		free(next_path);
		clear_split(path_argv_init);
		exit(1);
	}
	ft_perror("minishell", ECNF, *argv);
	clear_split(path_argv_init);
	exit(1);
}

static void	__builtin_execve_current_dir(char *const *argv,
				char **path_argv_init, char *const *env)
{
	execve(*argv, argv, env);
	ft_perror("minishell", errno, *argv);
	clear_split(path_argv_init);
	exit(1);
}

static char	*__builtin_execve_strsum(const char *str1, const char *str2)
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

inline int	ft_iscolon(int c)
{
	return (c == ':');
}
