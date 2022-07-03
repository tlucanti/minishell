/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:53:32 by kostya            #+#    #+#             */
/*   Updated: 2022/07/01 12:56:55 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef __linux__
#  include <linux/limits.h>
#  include <readline/readline.h>
#  include <readline/history.h>
# else
#  include <limits.h>
#  include <readline.h>
#  include <history.h>
# endif

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termios.h>

long long int	ft_atol_s(const char *__restrict str, int *__restrict error)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				ft_atoi_s(const char *__restrict str, int *__restrict error)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
void			clear_split(char *__restrict *__restrict array)
				__attribute__((__nothrow__));
int				simple_parcer(char *__restrict input)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				set_autoattr(int desc, int value, int what)
				__attribute__((__nothrow__));
void			putsfd(int fd, const char *__restrict str)
				__attribute__((__nothrow__));
int				builtin_echo(char *const *__restrict argv)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				builtin_cd(char *__restrict const *__restrict argv)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				builtin_pwd(char *__restrict const *__restrict argv)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				builtin_export(char *const *__restrict argv)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				builtin_export_split(const char *__restrict string,
					char *__restrict *__restrict key,
					char *__restrict *__restrict value)
				__attribute__((__nothrow__));
int				builtin_unset(char *__restrict const *__restrict argv)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				builtin_env(char *__restrict const *__restrict argv)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				builtin_exit(char *__restrict const *__restrict argv)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				builtin_execve(char *const *__restrict argv)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
char			*builtin_heredoc(const char *__restrict end)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				exit_status_storage(int status, int set)
				__attribute__((__nothrow__));
int				get_next_line(int fd, char **line);
void			ft_rl_bind_key(void)
				__attribute__((__nothrow__));

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
	struct s_promt	*self;
}	t_promt;

void			update_promt_init(t_promt *promt_ptr, char *__restrict buff)
				__attribute__((__nothrow__));

#endif // MINISHELL_H
