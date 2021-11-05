/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:16:21 by kostya            #+#    #+#             */
/*   Updated: 2021/11/05 16:07:32 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

int				complex_parser_decorator(char *__restrict *__restrict array)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
char *__restrict	*clear_split_smart(char *__restrict *__restrict array)
				__attribute__((__nothrow__));
char *__restrict	*smart_split(const char *__restrict input, int (*skip)(int))
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
void			enforce_env(char *__restrict *__restrict array)
				__attribute__((__nothrow__));
char			*dollar_commutate(char *__restrict string)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
char			*builtin_heredoc_prompt(int reset)
				__attribute__((__nothrow__));
char *__restrict	*implement_redirect(char *__restrict *__restrict ptr)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				implement_heredoc(const char *__restrict end)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
char *__restrict	*redirect_shard(char *__restrict *__restrict ptr,
					uint *__restrict argv_size)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				pipe_shard(char *__restrict *__restrict ptr)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				fork_shard(char *__restrict *__restrict array,
					char *__restrict *__restrict end, uint argv_size)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
int				backup_fd_in_out(int _in_out[2], int init)
				__attribute__((__nothrow__));
char			*dollar_commutate_extension_1(char *string, char *dollar_start,
					char **dollar_next)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
char			*dollar_commutate_extension_2(char *string, char *dollar_start,
					char **dollar_next)
				__attribute__((warn_unused_result)) __attribute__((
						__nothrow__));
void			del_quotes_arr(char *__restrict *__restrict array)
				__attribute__((__nothrow__));

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
# define ANY_QUOTE		0b01100000
// # define NOT_QUOTE		0b00011111

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

typedef struct s_quote
{
	size_t	s_size;
	size_t	r_size;
	size_t	q_size;
	size_t	e_size;

	char	*string;
	char	*input;
	char	*quote_index;
}	t_quote;

inline void	print_my_cool_split(char *__restrict *__restrict p)
{
	if (!p)
	{
		printf("syntax error\n");
		return ;
	}
	if (!*p)
	{
		printf("[%p, %p]\n", p[0], p[1]);
		return ;
	}
	if ((size_t) * p > 100)
		printf("['%s'", *p);
	else
		printf("[%p", *p);
	++p;
	while (*p)
	{
		if ((size_t) * p > 100)
			printf(", '%s'", *p);
		else
			printf(", %p", *p);
		++p;
	}
	printf(", %p, %p", p[0], p[1]);
	printf("]\n");
}

#endif // PARSER_H
