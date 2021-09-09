/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:56:55 by kostya            #+#    #+#             */
/*   Updated: 2021/09/09 14:45:19 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"
#include "enviroment.h"

g_main_st_t g_main;

static int	update_promt();
static const char *xstrerror(int errorcode);

int main()
{
	char	*input;

	 g_main.env = env_init();
	while (1)
	{
		update_promt();
		input = readline(g_main.promt);
		if (!input)
		{
			printf("eof found");
			break ;
		}
		rl_bind_key('\t', rl_complete);
		add_history(input);
		simple_parcer(input);
		free(input);
	}
}

static int	update_promt()
// tlucanti:/home/tlucanti $ 
{
	const char		*env;
	size_t			user_size;
	unsigned int	cwd_size;
	size_t			home_size;

	env = ft_getenv_s("USER", &user_size);
	user_size = ft_strlen(env);
	ft_memcpy(g_main.promt, env, user_size);
	g_main.promt[user_size] = ':';
	getcwd(g_main.promt + user_size + 1, PATH_MAX);
	cwd_size = ft_strlen(g_main.promt + user_size + 1);
	env = ft_getenv_s("HOME", &home_size);
	if (!ft_memcmp(g_main.promt + user_size + 1, env, home_size + 1))
	{
		g_main.promt[user_size + 1] = '~';
		cwd_size = 1;
	}
	g_main.promt[user_size + cwd_size + 1] = ' ';
	g_main.promt[user_size + cwd_size + 2] = '$';
	g_main.promt[user_size + cwd_size + 3] = ' ';
	g_main.promt[user_size + cwd_size + 4] = '\0';
	return (0);
}

int	simple_parcer(const char *input)
{
	char **arr = ft_split(input, ft_isspace);

	if (!strcmp(arr[0], "echo"))
		return (builtin_echo(arr));
	else if (!strcmp(arr[0], "cd"))
		return (builtin_cd(arr));
	else if (!strcmp(arr[0], "pwd"))
		return (builtin_pwd(arr));
	else if (!strcmp(arr[0], "export"))
		return (builtin_export(arr));
	else if (!strcmp(arr[0], "unset"))
		return (builtin_unset(arr));
	else if (!strcmp(arr[0], "env"))
		return (builtin_env(arr));
	else if (!strcmp(arr[0], "exit"))
		return (builtin_exit(arr));
	else
		builtin_execve(arr);
	xperror("minishell", ECNF, arr[0]);
	return (1);
//	clear_split(arr);
//	return (0);
}

size_t	putsfd(int fd, const char *str)
{
	size_t	size;

	size = ft_strlen(str);
	write(fd, str, size);
	return (size);
}

void clear_split(char **array)
{
	char	**ptr;

	ptr = array;
	while (*array)
	{
		free(*array);
		++array;
	}
	free(ptr);
}

void xperror(const char *parent, int errorcode, const char *arg)
{
	putsfd(2, parent);
	putsfd(2, ": ");
	putsfd(2, xstrerror(errorcode));
	if (arg)
	{
		putsfd(2, ": ");
		putsfd(2, arg);
	}
	putsfd(2, "\n");
}

const char *xstrerror(int errorcode)
{
	if (errorcode == ECNF)
		return ("command not found");
	else if (errorcode == ETMA)
		return ("too many arguments");
	else if (errorcode == ENAVI)
		return ("not a valid identifier");
	else if (errorcode == ENEA)
		return ("not enough arguments");
	else if (errorcode == ENUMR)
		return ("numeric argument required");
	return strerror(errorcode);
}

void xexit(int status)
{
	exit(status);
}
