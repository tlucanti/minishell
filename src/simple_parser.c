/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:11:37 by kostya            #+#    #+#             */
/*   Updated: 2021/10/29 18:15:25 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/libft.h"
#include "../inc/parser.h"
#include "../inc/enviroment.h"
#include "../inc/error.h"
#include "../inc/memory.h"

static int	syntax_check(char *__restrict *__restrict array)
			__attribute__((warn_unused_result)) __attribute__((__nothrow__));
static char	*token_to_string(const char *__restrict token)
			__attribute__((warn_unused_result)) __attribute__((__nothrow__));
static char *del_quotes(char *__restrict input)
			__attribute__((warn_unused_result)) __attribute__((__nothrow__));

void	print_my_cool_split(char **p)
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
	if ((size_t)*p > 100)
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

int	simple_parcer(char *__restrict *__restrict input_ptr)
{
	char *__restrict	*arr;
	int					ret;

	*input_ptr = del_quotes(*input_ptr);
	if (!*input_ptr)
		return (2);
	arr = smart_split(*input_ptr, ft_isspace);
	ret = syntax_check(arr);
	if (!ret)
	{
		clear_split_smart(arr);
		return (ret + 2);
	}
	if (!*arr)
	{
		clear_split_smart(arr);
		return (0);
	}
	enforce_env(arr);
	print_my_cool_split((void *)arr);
	// arr = del_quotes(arr);
	print_my_cool_split((void *)arr);
	ret = complex_parser_decorator(arr);
	clear_split_smart(arr);
	return (ret);
}

static int	syntax_check(char *__restrict *__restrict array)
{
	int	not_empty_pipe;

	not_empty_pipe = 0;
	if (!array)
		return (ft_perror("minishell", ESYNT, "unclosed quote"));
	if (*array == PIPE_PTR)
		return (ft_perror("minishell", ESYNT, "empty pipe"));
	if ((size_t)(*array) < ANY_TOKEN && (size_t)(*array) & NOT_QUOTE)
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
		else if ((size_t)array[1] < ANY_TOKEN && (size_t)(array[1]) & NOT_QUOTE)
			return (ft_perror("minishell", ETOKEN, token_to_string(array[1])));
		++array;
	}
	return (1);
}

static char	*token_to_string(const char *__restrict token)
{
	if (token == OUT_APPEND_PTR)
		return ((char *)">>");
	else if (token == OUT_WRITE_PTR)
		return ((char *)">");
	else if (token == INPUT_PTR)
		return ((char *)"<");
	else if (token == HEREDOC_PTR)
		return ((char *)"<<");
	else if (token == PIPE_PTR)
		return ((char *)"pipe");
	return ((char *)"end of line");
}

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

static char *del_quotes(char *__restrict input)
{
	t_quote	quote;

	quote.s_size = 0;
	while (input[quote.s_size])
	{
		if (input[quote.s_size] == '\'' || input[quote.s_size] == '\"')
		{
			quote.quote_index = ft_strchr(input + quote.s_size + 1, input[quote.s_size]);
			if (quote.quote_index == NULL)
				return (NULL);
			quote.r_size = ft_strlen(quote.quote_index + 1);
			quote.q_size = quote.quote_index - input - quote.s_size - 1;
			if (input[quote.s_size] == '\'' || ft_memchr(input + quote.s_size + 1, '$', quote.q_size) == NULL)
			{
				ft_memmove(input + quote.s_size, input + quote.s_size + 1, quote.q_size);
				ft_memmove(quote.quote_index - 1, quote.quote_index + 1, quote.r_size);
				quote.quote_index[quote.r_size - 1] = 0;
				quote.s_size = quote.s_size + quote.q_size;
			}
			else
			{
				*quote.quote_index = 0;
				quote.string = dollar_commutate(ft_strdup(input + quote.s_size + 1));
				quote.e_size = ft_strlen(quote.string);
				quote.input = (char *)xmalloc(quote.s_size + quote.e_size + quote.r_size + 1);
				ft_memcpy(quote.input, input, quote.s_size);
				ft_memcpy(quote.input + quote.s_size, quote.string, quote.e_size);
				ft_memcpy(quote.input + quote.s_size + quote.e_size, quote.quote_index + 1, quote.r_size);
				free(input);
				input = quote.input;
				quote.s_size = quote.s_size + quote.e_size;
			}
		}
		else
			++quote.s_size;
	}
	return (input);
}
