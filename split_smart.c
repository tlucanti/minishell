/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_smart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 18:15:13 by kostya            #+#    #+#             */
/*   Updated: 2021/10/26 22:47:59 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/memory.h"
#include "include/libft.h"
#include "include/parser.h"

static char	**push_back_null(char **__restrict array, size_t size)
			__attribute__((warn_unused_result)) __attribute__((__nothrow__));
static char	**push_back_string(char **__restrict array, const char *__restrict input, size_t str_size,
				size_t *array_size) __attribute__((warn_unused_result)) __attribute__((__nothrow__));
static char	**push_back_token(char **__restrict array, const char *__restrict *__restrict input, size_t *__restrict size)
			__attribute__((warn_unused_result)) __attribute__((__nothrow__));
static int	is_token(int c) __attribute__((warn_unused_result)) __attribute__((__nothrow__));

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

// echo hello > lol << kek | lololol|lol<f>e
char	**smart_split(const char *__restrict input, int (*skip)(int))
{
	size_t	size;
	size_t	array_size;
	char	**ret;
	char	quote;

	array_size = 0;
	ret = (char **)xmalloc(sizeof(char *) * 2);
	ret[0] = NULL;
	ret[1] = NULL;
	while (*input)
	{
		while (skip(*input) && *input)
			++input;
		if (*input == '>' || *input == '<' || *input == '|')
			ret = push_back_token(ret, &input, &array_size);
		size = 0;
		if (*input == '\'' || *input == '\"')
		{
			quote = *input;
			ret = push_back_token(ret, &input, &array_size);
			while (*input != quote && *input && ++size)
				++input;
			if (!*input++)
				return (clear_split_smart(ret));
			ret = push_back_string(ret, input - 1, size, &array_size);
		}
		size = 0;
		while (!is_token(*input) && *input && !skip(*input) && ++size)
			++input;
		ret = push_back_string(ret, input, size, &array_size);
	}
	return (ret);
}

static char	**push_back_token(char **array, const char *__restrict *__restrict input, size_t *__restrict size)
{
	array = push_back_null(array, *size);
	if (input[0][0] == '>')
	{
		if (input[0][1] == '>')
		{
			array[*size] = OUT_APPEND_PTR;
			*input += 2;
		}
		else
		{
			array[*size] = OUT_WRITE_PTR;
			*input += 1;
		}
	}
	else if (input[0][0] == '<')
	{
		if (input[0][1] == '<')
		{
			array[*size] = HEREDOC_PTR;
			*input += 2;
		}
		else
		{
			array[*size] = INPUT_PTR;
			*input += 1;
		}
	}
	else if (input[0][0] == '|')
	{
		array[*size] = PIPE_PTR;
		*input += 1;
	}
	else if (input[0][0] == '\'')
	{
		array[*size] = UNO_QUOTE_PTR;
		*input += 1;
	}
	else if (input[0][0] == '\"')
	{
		array[*size] = DBL_QUOTE_PTR;
		*input += 1;
	}
	*size += 1;
	if (input[0][-1] == **input && (input[0][-1] == '"' || **input == '\''))
		array = push_back_string(array, &"\000\000"[1], 1, size);
	return (array);
}

static char	**push_back_string(char **__restrict array, const char *__restrict input, size_t str_size,
				size_t *__restrict array_size)
{
	if (!str_size)
		return (array);
	array = push_back_null(array, *array_size);
	array[*array_size] = (char *)xmalloc(sizeof(char) * (str_size + 1));
	ft_memcpy(array[*array_size], input - str_size, str_size);
	array[*array_size][str_size] = 0;
	*array_size += 1;
	return (array);
}

static char	**push_back_null(char **__restrict array, size_t size)
{
	char	**_new;

	_new = (char **)xmalloc(sizeof(char *) * (size + 3));
	ft_memcpy(_new, array, sizeof(char *) * (size + 2));
	_new[size + 2] = NULL;
	free(array);
	return (_new);
}

char	**clear_split_smart(char **__restrict array)
{
	char	**ptr;

	ptr = array;
	while (*array)
	{
		if ((size_t)(*array) > ANY_TOKEN)
			free(*array);
		++array;
	}
	free(ptr);
	return (NULL);
}

static int	is_token(int c)
{
	return (c == '>' || c == '<' || c == '|' || c == '\'' || c == '\"');
}
