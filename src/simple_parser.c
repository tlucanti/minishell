/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:11:37 by kostya            #+#    #+#             */
/*   Updated: 2021/11/01 19:55:23 by kostya           ###   ########.fr       */
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

int	simple_parcer(char *__restrict input)
{
	char *__restrict	*arr;
	int					ret;

	arr = smart_split(input, ft_isspace);
	if (!arr)
		return (ft_perror("minishell", ESYNT, "unclosed quote"));
	if (!*arr)
		return ((size_t)clear_split_smart(arr));
	del_quotes_arr(arr);
	if ((size_t)(*arr) > ANY_TOKEN && !**arr)
	{
		clear_split_smart(arr);
		ft_perror("minishell", ECNF, "\'\'");
		return (127);
	}
	ret = syntax_check(arr);
	if (!ret)
	{
		clear_split_smart(arr);
		return (2);
	}
	ret = complex_parser_decorator(arr);
	clear_split_smart(arr);
	return (ret);
}

static int	syntax_check(char *__restrict *__restrict array)
{
	int	not_empty_pipe;

	not_empty_pipe = 0;
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
