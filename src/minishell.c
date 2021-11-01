/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:56:55 by kostya            #+#    #+#             */
/*   Updated: 2021/11/01 14:31:13 by kostya           ###   ########.fr       */
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
			free(input);
			xexit(0);
		}
		ft_rl_bind_key();
		exit_status_storage(simple_parcer(input), 1);
		free(input);
	}
	(void)_;
}

static void	update_promt(char *__restrict buff)
/*
** tlucanti:/home/tlucanti $ 
*/
{
	const t_promt	promt = (t_promt){ft_getenv_s("USER", (size_t *)&promt.
user_size), promt.user_size, ft_getenv_s("PWD", (size_t *)&promt.cwd_size),
promt.cwd_size, sizeof(READLINE_GREEN) - 1, ft_memcpy(buff, READLINE_GREEN,
promt.shift_0), ft_memcpy(buff + promt.shift_0, promt.user, promt.user_size),
promt.shift_0 + promt.user_size, ft_memcpy(buff + promt.shift_1, READLINE_WHITE
":" READLINE_BLUE, sizeof(READLINE_WHITE) + sizeof(READLINE_BLUE) - 1), promt.
shift_1 + sizeof(READLINE_WHITE) + sizeof(READLINE_BLUE) - 1, getcwd(buff +
promt.shift, PATH_MAX), ft_memcpy(buff + promt.shift, promt.cwd, promt.cwd_size)
, ft_getenv_s("HOME", (size_t *)&promt.home_size), promt.home_size, 0, (t_promt
*)&promt};

	if (!ft_memcmp(buff + promt.shift, promt.home, promt.home_size))
	{
		buff[promt.shift] = '~';
		promt.self->r_size = ft_strlen(buff + promt.shift + promt.home_size);
		ft_memmove(buff + promt.shift + 1, buff + promt.shift + promt.home_size,
			promt.r_size);
		promt.self->shift += promt.r_size;
	}
	else
		promt.self->shift += promt.cwd_size - 1;
	ft_memcpy(buff + promt.shift + 1, " " READLINE_YELLOW "\001➜\002"
		READLINE_RESET " ", sizeof(READLINE_YELLOW) + sizeof(READLINE_RESET)
		+ 6);
}

static char	*ft_readline(void)
{
	char	promt[PATH_MAX];
	char	*input;

	if (isatty(0))
	{
		update_promt(promt);
		input = readline(promt);
		if (input && input[0])
			add_history(input);
	}
	else
	{
		if (!get_next_line(0, &input))
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
