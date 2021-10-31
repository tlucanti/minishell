/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:56:55 by kostya            #+#    #+#             */
/*   Updated: 2021/10/31 20:02:51 by kostya           ###   ########.fr       */
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
static char	*ft_readline(void)
			__attribute__((warn_unused_result)) __attribute__((
					__nothrow__));

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

typedef struct s_promt
{
	const char		*user;
	size_t			user_size;
	const char		*cwd;
	size_t			cwd_size;
	size_t			shift_0;
	void			*memcpy_0;
	void			*memcpy_1;
	size_t			shift_1;
	void			*memcpy_2;
	size_t			shift;
	void			*getcwd_0;
	void			*memcpy_3;
	char			*home;
	size_t			home_size;
	size_t			r_size;
}	t_promt;

static void	update_promt(char *__restrict buff)
/*
** tlucanti:/home/tlucanti $ 
*/
{
	t_promt	promt = (t_promt) {
		ft_getenv_s("USER", &promt.user_size), // user
		promt.user_size, // user_size
		ft_getenv_s("PWD", &promt.cwd_size), // cwd
		promt.cwd_size, // cwd_size
		sizeof(READLINE_GREEN) - 1, // shift_0
		ft_memcpy(buff, READLINE_GREEN, promt.shift_0), // memcpy_0
		ft_memcpy(buff + promt.shift_0, promt.user, promt.user_size), // memcpy_1
		promt.shift_0 + promt.user_size, // shift_1
		ft_memcpy(buff + promt.shift_1, READLINE_WHITE ":" READLINE_BLUE,
				sizeof(READLINE_WHITE) + sizeof(READLINE_BLUE) - 1), // memcpy_2
		promt.shift_1 + sizeof(READLINE_WHITE) + sizeof(READLINE_BLUE) - 1, // shift
		getcwd(buff + promt.shift, PATH_MAX), // getcwd_0
		ft_memcpy(buff + promt.shift, promt.cwd, promt.cwd_size), // memcpy_3
		ft_getenv_s("HOME", &promt.home_size), // home
		promt.home_size, // home_size
		0 // r_size
	};


	if (!ft_memcmp(buff + promt.shift, promt.home, promt.home_size))
	{
		buff[promt.shift] = '~';
		promt.r_size = ft_strlen(buff + promt.shift + promt.home_size);
		ft_memmove(buff + promt.shift + 1, buff + promt.shift + promt.home_size,
			promt.r_size);
		promt.shift += promt.r_size;
	}
	else
		promt.shift += promt.cwd_size - 1;
	ft_memcpy(buff + promt.shift + 1, " " READLINE_YELLOW "\001➜\002"
		READLINE_RESET " ", sizeof(READLINE_YELLOW) + sizeof(READLINE_RESET)
		+ 6);
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
