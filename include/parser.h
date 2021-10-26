/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:16:21 by kostya            #+#    #+#             */
/*   Updated: 2021/10/27 00:10:54 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int		complex_parser_decorator(char **__restrict array, int _do_pipe
			) __attribute__((warn_unused_result)) __attribute__((__nothrow__));

void	print_my_cool_split(char **p) __attribute__((__nothrow__));
char	**clear_split_smart(char **__restrict array) __attribute__((
				__nothrow__));
void	enforce_env(char **__restrict array) __attribute__((__nothrow__));
char	*dollar_commutate(char *__restrict string) __attribute__((
				warn_unused_result)) __attribute__((__nothrow__));
char	*builtin_heredoc_prompt(int reset) __attribute__((
				warn_unused_result)) __attribute__((__nothrow__));

char	**redirect_sharp(char **__restrict ptr, uint *__restrict argv_size,
			int _in_out[2], int *__restrict was_redirect) __attribute__((
				warn_unused_result));
int		pipe_sharp(char *__restrict *__restrict ptr, int _in_out[2],
			int *__restrict _do_pipe, int was_redirect) __attribute__((
				warn_unused_result));
int		fork_sharp(char *__restrict *__restrict array, int _in_out[2],
			char *__restrict *__restrict end,
			uint argv_size) __attribute__((warn_unused_result));

# define OUT_APPEND_PTR	(char *)OUT_APPEND
# define OUT_WRITE_PTR	(char *)OUT_WRITE
# define HEREDOC_PTR	(char *)HEREDOC
# define INPUT_PTR		(char *)INPUT
# define PIPE_PTR		(char *)PIPE
# define UNO_QUOTE_PTR	(char *)UNO_QUOTE
# define DBL_QUOTE_PTR	(char *)DBL_QUOTE

# define OUT_APPEND		0b00000001
# define OUT_WRITE		0b00000010
# define HEREDOC		0b00000100
# define INPUT			0b00001000
# define PIPE			0b00010000
# define UNO_QUOTE		0b00100000
# define DBL_QUOTE		0b01000000
# define ANY_TOKEN		0b01111111

# define REDIRECT		0b00001111
# define SKIP_PARSER	0b01100000

# define DOUBLE_SKIP_DOLLAR	0b00101111
# define SINGLE_SKIP_DOLLAR	0b01010000

# define STDIN			STDIN_FILENO
# define STDOUT			STDOUT_FILENO

typedef struct s_dollar
{
	char	*new_string;

	char	*dollar_end;
	char	_saved_char;

	char	*new_env;
	size_t	env_size;

	size_t	residue_size;

	char	*exit_status;
	size_t	exit_status_size;
}	t_dollar;

#endif // PARSER_H
