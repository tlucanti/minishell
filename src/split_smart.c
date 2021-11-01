/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_smart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 18:15:13 by kostya            #+#    #+#             */
/*   Updated: 2021/11/01 13:02:36 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/memory.h"
#include "../inc/libft.h"
#include "../inc/parser.h"

char *__restrict	*push_back_token(char *__restrict *__restrict array,
						const char *__restrict *__restrict input,
						size_t *__restrict size)
					__attribute__((warn_unused_result)) __attribute__((
							__nothrow__));
char *__restrict	*push_back_null(char *__restrict *__restrict array,
						size_t size)
					__attribute__((warn_unused_result)) __attribute__((
							__nothrow__));
char *__restrict	*push_back_string(char *__restrict *__restrict array,
						const char *__restrict input, size_t str_size,
						size_t *array_size)
					__attribute__((warn_unused_result)) __attribute__((
							__nothrow__));
static int		smart_split_skip_quote(
						const char *__restrict *__restrict input_ptr,
						size_t *__restrict size_ptr)
					__attribute__((warn_unused_result)) __attribute__((
							__nothrow__));
static int		__smart_split_extension(
						const char *__restrict *__restrict input_ptr,
						size_t *__restrict size,
						char *__restrict *__restrict ret, int (*skip)(int))
					__attribute__((warn_unused_result)) __attribute__((
							__nothrow__));

// echo hello > lol << kek | lololol|lol<f>e
// lol c++ comment
char *__restrict	*smart_split(const char *__restrict input, int (*skip)(int))
{
	size_t				size;
	size_t				array_size;
	char *__restrict	*ret;

	array_size = 0;
	ret = (char **)xmalloc(sizeof(char *) * 2);
	ret[0] = NULL;
	ret[1] = NULL;
	while (*input)
	{
		while (skip(*input) && *input)
			++input;
		if (*input == '>' || *input == '<' || *input == '|')
		{
			ret = push_back_token(ret, &input, &array_size);
			continue ;
		}
		size = 0;
		if (!__smart_split_extension(&input, &size, ret, skip))
			return (NULL);
		ret = push_back_string(ret, input, size, &array_size);
	}
	return (ret);
}

static int	smart_split_skip_quote(const char *__restrict *__restrict input_ptr,
				size_t *__restrict size_ptr)
{
	const char	quote = **input_ptr;

	if (**input_ptr != '\'' && **input_ptr != '\"')
		return (0);
	++(*input_ptr);
	++(*size_ptr);
	while (**input_ptr != quote && **input_ptr)
	{
		++(*input_ptr);
		++(*size_ptr);
	}
	if (!**input_ptr)
		return (1);
	return (0);
}

char *__restrict	*push_back_string(char *__restrict *__restrict array,
						const char *__restrict input, size_t str_size,
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

char *__restrict	*push_back_null(char *__restrict *__restrict array,
						size_t size)
{
	char	**_new;

	_new = (char **)xmalloc(sizeof(char *) * (size + 3));
	ft_memcpy(_new, (void *)array, sizeof(char *) * (size + 2));
	_new[size + 2] = NULL;
	free((void *)array);
	return (_new);
}

static int	__smart_split_extension(
				const char *__restrict *__restrict input_ptr,
				size_t *__restrict size, char *__restrict *__restrict ret,
				int (*skip)(int))
{
	while (**input_ptr && **input_ptr != '>' && **input_ptr != '<'
		&& **input_ptr != '|')
	{
		if (smart_split_skip_quote(input_ptr, size))
			return ((size_t)clear_split_smart(ret));
		if (skip(**input_ptr))
			return (1);
		++(*size);
		++(*input_ptr);
	}
	return (1);
}
