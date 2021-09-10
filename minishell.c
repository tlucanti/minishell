/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:56:55 by kostya            #+#    #+#             */
/*   Updated: 2021/09/10 22:42:40 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "enviroment.h"
#include "error.h"
#include "signal.h"
#include "colors.h"

static int	update_promt(char *promt);
static int set_autoattr(int desc, int value, int what);

int main()
{
	char	*input;
	char	*promt = calloc(1,PATH_MAX + 1);

	signal(SIGINT, handler_signint_minishell);
	signal(SIGQUIT, handler_sigquit_minishell);
	set_autoattr(0, 0, ECHOCTL);
	ft_env_storage();
	while (1)
	{
		update_promt(promt);
		input = readline(promt);
		if (!input)
		{
			printf("exit\n");
			free(input);
			xexit(0);
		}
		rl_bind_key('\t', rl_complete);
		add_history(input);
		simple_parcer(input);
		free(input);
	}
}

static int	update_promt(char *promt)
// "\033[1;92mkostya\033[0m:/media/kostya/Data/CLion/Minishell/cmake-build-debug $ "
{
	// sprintf(promt, "\001\033[1;92m\002kostya:/media/kostya/Data/CLion/Minishell/cmake-build-debug $ ");
//	 snprintf(promt, PATH_MAX, READLINE_GREEN"%s"READLINE_WHITE":"READLINE_BLUE"%s"READLINE_YELLOW" \001➜\002 "READLINE_RESET, getenv("USER"), getcwd(NULL, 1024));
	snprintf(promt, PATH_MAX, "%s%s%s:%s%s%s %s\001➜\002%s ",
		READLINE_GREEN, ft_getenv_s("USER", NULL), READLINE_RESET,
		READLINE_BLUE, getcwd(NULL, 1024), READLINE_RESET,
		READLINE_YELLOW, READLINE_RESET);
//	 printf("\n|%s|\n", promt);
	return (0);
}

inline int	__update_promt(char *promt)
// tlucanti:/home/tlucanti $ 
{
	const char		*env;
	size_t			user_size;
	unsigned int	cwd_size;
	size_t			home_size;

	ft_memcpy(promt, TERM_GREEN, ft_strlen(TERM_GREEN));
	env = ft_getenv_s("USER", &user_size);
	user_size = ft_strlen(env);
	ft_memcpy(promt + ft_strlen(TERM_GREEN), env, user_size);
	promt[user_size] = ':';
	env = getcwd(promt + user_size + 1, PATH_MAX);
	(void)env;
	cwd_size = ft_strlen(promt + user_size + 1);
	env = ft_getenv_s("HOME", &home_size);
	if (!ft_memcmp(promt + user_size + 1, env, home_size + 1))
	{
		promt[user_size + 1] = '~';
		cwd_size = 1;
	}
	promt[user_size + cwd_size + 1] = ' ';
	promt[user_size + cwd_size + 2] = '$';
	promt[user_size + cwd_size + 3] = ' ';
	promt[user_size + cwd_size + 4] = '\0';
	return (0);
}

int	simple_parcer(const char *input)
{
	char **arr = ft_split(input, ft_isspace);

	if (!*arr)
		return (0);
	else if (!strcmp(arr[0], "echo"))
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
	return (builtin_execve(arr));
//	clear_split(arr);
//	return (0);
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

static int set_autoattr(int desc, int value, int what)
{
	struct termios settings;
	int result;
	result = tcgetattr(desc, &settings);
	if (result < 0)
	{
		perror ("error in tcgetattr");
		return (1);
	}
	settings.c_lflag &= ~what;
	if (value)
		settings.c_lflag |= what;
	result = tcsetattr(desc, TCSANOW, &settings);
	if (result < 0)
	{
		perror ("error in tcgetattr");
		return (1);
	}
	return (0);
}
