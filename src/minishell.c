/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:56:55 by kostya            #+#    #+#             */
/*   Updated: 2021/10/30 16:42:16 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/enviroment.h"
#include "../inc/error.h"
#include "../inc/handler.h"
#include "../inc/color.h"
#include "../inc/libft.h"
#include "../inc/parser.h"
#include "../inc/memory.h"

static void	update_promt(char *__restrict promt) __attribute__((__nothrow__));
static char	*ft_readline(void) __attribute__((warn_unused_result)) __attribute__((__nothrow__));

int	main(void)
{
	char	*input;
	void	*_;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	// set_autoattr(0, 0, ECHOCTL);
	_ = internal_env_storage();
	while (1)
	{
		signal(SIGINT, handler_signint_readline);
		input = ft_readline();
		signal(SIGINT, SIG_IGN);
		if (!input)
		{
			if (isatty(0))
			printf("exit\n");
			xexit(xfree(input));
		}
		/* rl_bind_key('\t', rl_complete); */
		exit_status_storage(simple_parcer(input), 1);
		free(input);
	}
	(void)_;
}

static void	update_promt(char *__restrict promt)
/*
** tlucanti:/home/tlucanti $ 
*/
{
	const char		*env;
	size_t			user_size;
	size_t			cwd_size;
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
	if (!getcwd(promt + shift, PATH_MAX))
		return ;
	env = ft_getenv_s("PWD", &cwd_size);
	ft_memcpy(promt + shift, env, cwd_size);
	env = ft_getenv_s("HOME", &home_size);
	if (!ft_memcmp(promt + shift, env, home_size + 1))
		promt[shift] = '~';
	else
		shift += cwd_size - 1;
	ft_memcpy(promt + shift + 1, " " READLINE_YELLOW "\001➜\002" READLINE_RESET
		" ", sizeof(READLINE_YELLOW) + sizeof(READLINE_RESET) + 6);
}

static char	*ft_readline(void)
{
	char	promt[PATH_MAX];
	char	*input;

	fprintf(stderr, "isatty %d\n", isatty(0));
	if (isatty(0))
	{
		update_promt(promt);
		input = readline(promt);
		if (input && input[0])
			add_history(input);
	}
	else
	{
		int ret = get_next_line(0, &input);
		if (ret == 0)
			return (NULL);
	}
	return (input);
}

void	clear_split(char *__restrict *__restrict array)
{
	char *__restrict	*ptr;

	ptr = array;
	while (*array)
	{
		free(*array);
		++array;
	}
	free((void *)ptr);
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

int	exit_status_storage(int status, int set)
{
	static int	_internal_status = 0;

	if (set)
		_internal_status = status;
	return (_internal_status);
}
