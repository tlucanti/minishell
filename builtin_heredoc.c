/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:58:07 by kostya            #+#    #+#             */
/*   Updated: 2021/10/27 11:27:08 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/memory.h"
#include "include/minishell.h"
#include "include/libft.h"
#include "include/handler.h"

static void	ft_putunbr(char *__restrict string, int num)
			__attribute__((__nothrow__));
char		*builtin_heredoc_prompt(int reset)
			__attribute__((warn_unused_result)) __attribute__((__nothrow__));
static void	builtin_heredoc_extension(char *__restrict *__restrict out,
				size_t *__restrict size, char *__restrict str_tmp,
				size_t new_size) __attribute__((__nothrow__));

char	*builtin_heredoc(const char *__restrict end)
/*
** function reads from STDIN data for function run with `heredoc` syntax
** heredoc syntax: [end_symbol]\n[data]\n[end_symbol]
*/
{
	char	*input;
	char	*out;
	char	*str_tmp;
	size_t	size;
	size_t	new_size;

	size = 0;
	out = (char *)xmalloc(sizeof(char));
	out[0] = 0;
	while (1)
	{
		signal(SIGINT, handler_signint_heredoc);
		input = readline(builtin_heredoc_prompt(0));
		signal(SIGINT, SIG_IGN);
		if (!input)
			return (NULL);
		new_size = ft_strlen(input);
		if (!ft_memcmp(input, end, new_size + 1))
			return (out);
		str_tmp = (char *)xmalloc(sizeof(char) * (size + new_size + 2));
		ft_memcpy(str_tmp, out, size);
		ft_memcpy(str_tmp + size, input, new_size + 1);
		free(out);
		builtin_heredoc_extension(&out, &size, str_tmp, new_size);
	}
}

static void	builtin_heredoc_extension(char *__restrict *__restrict out,
				size_t *__restrict size, char *__restrict str_tmp,
	size_t new_size)
{
	*out = str_tmp;
	*size += new_size + 1;
	(*out)[*size - 1] = '\n';
	(*out)[*size] = 0;
}

char	*builtin_heredoc_prompt(int reset)
{
	static int	count = 0;
	static char	pattern[] = "heredoc (            ";

	if (reset)
	{
		count = 0;
		return (NULL);
	}
	ft_putunbr(pattern + 9, ++count);
	return (pattern);
}

static void	ft_putunbr(char *string, int num)
{
	while (num)
	{
		*string++ = num % 10 + '0';
		num /= 10;
	}
	string[0] = ')';
	string[1] = ' ';
	string[2] = '>';
	string[3] = ' ';
	string[4] = '\0';
}
