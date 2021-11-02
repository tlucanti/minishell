/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:58:07 by kostya            #+#    #+#             */
/*   Updated: 2021/11/02 13:33:32 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/memory.h"
#include "../inc/minishell.h"
#include "../inc/libft.h"
#include "../inc/handler.h"
#include "../inc/parser.h"

static void	ft_putunbr(char *__restrict string, int num)
			__attribute__((__nothrow__));
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
	out = (char *)ft_calloc(1, sizeof(char));
	while (1)
	{
		signal(SIGINT, handler_signint_heredoc);
		input = readline(builtin_heredoc_prompt(0));
		signal(SIGINT, SIG_IGN);
		if (!input)
			return ((char *)(size_t)(xfree(out) - 1));
		new_size = ft_strlen(input);
		if (!ft_memcmp(input, end, new_size + 1))
			return (out + xfree(input) - 1);
		str_tmp = (char *)xmalloc(sizeof(char) * (size + new_size + 2));
		ft_memcpy(str_tmp, out, size);
		ft_memcpy(str_tmp + size, input, new_size + 1);
		free_s(&input);
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

	if (reset == 1)
	{
		count = 0;
		return (NULL);
	}
	else if (reset == 2)
	{
		++count;
		return (NULL);
	}
	ft_putunbr(pattern + 9, count);
	return (pattern);
}

static void	ft_putunbr(char *string, int num)
{
	int	dn;
	int	dn2;
	int	n;

	n = num;
	dn = 0;
	while (n)
	{
		++dn;
		n /= 10;
	}
	dn2 = dn;
	while (num)
	{
		string[--dn] = num % 10 + '0';
		num /= 10;
	}
	string[dn2 + 0] = ')';
	string[dn2 + 1] = ' ';
	string[dn2 + 2] = '>';
	string[dn2 + 3] = ' ';
	string[dn2 + 4] = '\0';
}
