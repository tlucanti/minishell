/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:56:55 by kostya            #+#    #+#             */
/*   Updated: 2021/10/25 21:35:07 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/enviroment.h"
#include "include/error.h"
#include "include/handler.h"
#include "include/color.h"
#include "include/libft.h"
#include "include/parser.h"

static int	update_promt(char *promt);
static int	syntax_check(char **array);
static char	*token_to_string(const char *token);

int	main(void)
{
	char	*input;
	char	promt[PATH_MAX];

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	set_autoattr(0, 0, ECHOCTL);
	internal_env_storage();
	while (1)
	{
		update_promt(promt);
		signal(SIGINT, handler_signint_readline);
		input = readline(promt);
		signal(SIGINT, SIG_IGN);
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

int	__update_promt(char *promt)
/*
** "kostya:/media/kostya/Data/CLion/Minishell/cmake-build-debug $ "
*/
{
	snprintf(promt, PATH_MAX, "%s%s%s:%s%s%s %s\001➜\002%s ",
		READLINE_GREEN, ft_getenv_s("USER", NULL), READLINE_RESET,
		READLINE_BLUE, getcwd(NULL, 1024), READLINE_RESET,
		READLINE_YELLOW, READLINE_RESET);
	return (0);
}

int	update_promt(char *promt)
/*
** tlucanti:/home/tlucanti $ 
*/
{
	const char		*env;
	size_t			user_size;
	unsigned int	cwd_size;
	size_t			home_size;
	size_t			shift;

	shift = sizeof(READLINE_GREEN) - 1;
	ft_memcpy(promt, READLINE_GREEN, shift);
	env = ft_getenv_s("USER", &user_size);
	ft_memcpy(promt + shift, env, user_size);
	shift += user_size;
	ft_memcpy(promt + shift, READLINE_WHITE ":" READLINE_BLUE,
		sizeof(READLINE_WHITE) + sizeof(READLINE_BLUE) - 1);
	shift += sizeof(READLINE_WHITE) + sizeof(READLINE_BLUE) - 1;
	env = getcwd(promt + shift, PATH_MAX);
	(void)env;
	cwd_size = ft_strlen(promt + shift);
	env = ft_getenv_s("HOME", &home_size);
	if (!ft_memcmp(promt + shift, env, home_size + 1))
		promt[shift] = '~';
	else
		shift += cwd_size - 1;
	ft_memcpy(promt + shift + 1, " " READLINE_YELLOW "\001➜\002" READLINE_RESET
		" ", sizeof(READLINE_YELLOW) + sizeof(READLINE_RESET) + 6);
	return (0);
}

int	simple_parcer(const char *input)
{
	char	**arr;
	int		ret;

	arr = smart_split(input, ft_isspace);
	ret = syntax_check(arr);
	if (!ret)
		return (ret);
	enforce_env(arr);
	ret = complex_parser_decorator(arr, -1);
	clear_split_smart(arr);
	list_insert(internal_env_storage(), ft_strdup("?"), ft_itoa(ret));
	return (ret);
}

static int	syntax_check(char **array)
{
	int	not_empty_pipe;

	not_empty_pipe = 0;
	if (!array)
		return (ft_perror("minishell", ESYNT, "unclosed quote"));
	if (*array == PIPE_PTR)
		return (ft_perror("minishell", ESYNT, "empty pipe"));
	if ((size_t)(*array) < ANY_TOKEN)
		return (ft_perror("minishell", ESYNT, "token without command"));
	while (*array)
	{
		if ((size_t)(*array) > ANY_TOKEN && ++array && ++not_empty_pipe)
			continue ;
		if (*array == PIPE_PTR && !array[1])
			return (ft_perror("minishell", ESYNT, "unclosed pipe"));
		if (*array == PIPE_PTR && !not_empty_pipe++)
			return (ft_perror("minishell", ESYNT, "empty pipe"));
		if (array[-1] == PIPE_PTR)
			return (ft_perror("minishell", ESYNT, "token without command"));
		else if ((size_t)array[1] < ANY_TOKEN)
			return (ft_perror("minishell", ETOKEN, token_to_string(array[1])));
		++array;
	}
	return (1);
}

static char	*token_to_string(const char *token)
{
	if (token == OUT_APPEND_PTR)
		return (">>");
	else if (token == OUT_WRITE_PTR)
		return (">");
	else if (token == INPUT_PTR)
		return ("<");
	else if (token == HEREDOC_PTR)
		return ("<<");
	else if (token == PIPE_PTR)
		return ("pipe");
	return ("end of line");
}

int	builtin(char **arr)
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

void	clear_split(char **array)
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

int	set_autoattr(int desc, int value, int what)
{
	struct termios	settings;
	int				result;

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
