/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_smart1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:19:08 by kostya            #+#    #+#             */
/*   Updated: 2021/10/30 14:27:05 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/memory.h"

char *__restrict	*push_back_null(char *__restrict *__restrict array,
						size_t size) __attribute__((warn_unused_result))
						 __attribute__((__nothrow__));
char *__restrict	*push_back_string(char *__restrict *__restrict array,
						const char *__restrict input, size_t str_size,
						size_t *array_size) __attribute__((
							warn_unused_result)) __attribute__((
							__nothrow__));
static void		_push_back_token_extension(
						char *__restrict *__restrict array,
						const char *__restrict *__restrict input,
						size_t *__restrict size) __attribute__((__nothrow__));

char *__restrict	*push_back_token(char *__restrict *__restrict array,
				const char *__restrict *__restrict input,
				size_t *__restrict size)
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
	else if (input[0][0] == '\"')
	{
		array[*size] = DBL_QUOTE_PTR;
		*input += 1;
	}
	else
		_push_back_token_extension(array, input, size);
	*size += 1;
	if (input[0][-1] == **input && (input[0][-1] == '"' || **input == '\''))
		array = push_back_string(array, &"\000\000"[1], 1, size);
	return (array);
}

static void	_push_back_token_extension(char *__restrict *__restrict array,
				const char *__restrict *__restrict input,
				size_t *__restrict size)
{
	if (input[0][0] == '<')
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
}

char *__restrict	*clear_split_smart(char *__restrict *__restrict array)
{
	char *__restrict	*ptr;

	if (!array)
		return (NULL);
	ptr = array;
	while (*array)
	{
		if ((size_t)(*array) > ANY_TOKEN)
			free(*array);
		++array;
	}
	free((void *)ptr);
	return (NULL);
}
