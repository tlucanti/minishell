/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_smart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 18:15:13 by kostya            #+#    #+#             */
/*   Updated: 2021/10/08 16:50:17 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/memory.h"
#include "include/libft.h"

static char	**push_back_null(char **array, size_t size)
			__attribute__((warn_unused_result));
static char	**push_back_string(char **array, const char *input, size_t str_size,
				size_t *array_size) __attribute__((warn_unused_result));
static char	**push_back_token(char **array, const char **input, size_t *size)
			__attribute__((warn_unused_result));
static char	**clear_split_smart(char **array);
static int	is_token(int c);

#define OUT_APPEND	(char *)1
#define OUT_WRITE	(char *)2
#define HEREDOC		(char *)3
#define INPUT		(char *)4
#define PIPE		(char *)5
#define UNO_QUOTE	(char *)6
#define DBL_QUOTE	(char *)7

void	print_my_cool_split(char **p)
{
	if (!p || !*p)
	{
		printf("syntax error\n");
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
	printf("]\n");
}

// echo hello > lol << kek | lololol|lol<f>e
char	**smart_split(const char *input, int (*skip)(int))
{
	size_t	size;
	size_t	array_size;
	char	**ret;
	char	quote;

	array_size = 0;
	ret = (char **)xmalloc(sizeof(char *));
	*ret = NULL;
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

static char	**push_back_token(char **array, const char **input, size_t *size)
{
	array = push_back_null(array, *size);
	if (input[0][0] == '>')
	{
		if (input[0][1] == '>')
		{
			array[*size] = OUT_APPEND;
			*input += 2;
		}
		else
		{
			array[*size] = OUT_WRITE;
			*input += 1;
		}
	}
	else if (input[0][0] == '<')
	{
		if (input[0][1] == '<')
		{
			array[*size] = HEREDOC;
			*input += 2;
		}
		else
		{
			array[*size] = INPUT;
			*input += 1;
		}
	}
	else if (input[0][0] == '|')
	{
		array[*size] = PIPE;
		*input += 1;
	}
	else if (input[0][0] == '\'')
	{
		array[*size] = UNO_QUOTE;
		*input += 1;
	}
	else if (input[0][0] == '\"')
	{
		array[*size] = DBL_QUOTE;
		*input += 1;
	}
	*size += 1;
	if (input[0][-1] == **input && (input[0][-1] == '"' || **input == '\''))
		array = push_back_string(array, &"\000\000"[1], 1, size);
	return (array);
}

static char	**push_back_string(char **array, const char *input, size_t str_size,
				size_t *array_size)
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

static char	**push_back_null(char **array, size_t size)
{
	char	**_new;

	_new = (char **)xmalloc(sizeof(char *) * (size + 2));
	ft_memcpy(_new, array, sizeof(char *) * (size + 1));
	_new[size + 1] = NULL;
	free(array);
	return (_new);
}

static char	**clear_split_smart(char **array)
{
	char	**ptr;

	ptr = array;
	while (array)
	{
		if (*array != OUT_APPEND && *array != OUT_WRITE && *array != HEREDOC
			&& *array != INPUT && *array != PIPE && *array != UNO_QUOTE
			&& *array != DBL_QUOTE)
			free(*array++);
	}
	free(ptr);
	return (NULL);
}

static int	is_token(int c)
{
	return (c == '>' || c == '<' || c == '|' || c == '\'' || c == '\"');
}
