/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 21:09:58 by kostya            #+#    #+#             */
/*   Updated: 2021/10/31 21:45:36 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/libft.h"

static char	*del_quotes(char *__restrict input)
			__attribute__((warn_unused_result)) __attribute__((__nothrow__));
static int	__del_quotes_extension_1(t_quote *__restrict quote,
				char *__restrict *__restrict input_ptr)
			__attribute__((warn_unused_result)) __attribute__((
					__nothrow__));
static void	__del_quotes_extension_2(t_quote *__restrict quote,
				char *__restrict *__restrict input_ptr)
			__attribute__((__nothrow__));
static int	__del_quotes_extension_3(t_quote *__restrict quote,
				char *__restrict *__restrict input)
			__attribute__((warn_unused_result)) __attribute__((
					__nothrow__));

void	del_quotes_arr(char *__restrict *__restrict array)
{
	while (*array)
	{
		if ((size_t)(*array) > ANY_TOKEN)
			*array = del_quotes(*array);
		++array;
	}
}

static char	*del_quotes(char *__restrict input)
{
	t_quote	quote;

	quote.s_size = 0;
	while (input[quote.s_size])
	{
		if (input[quote.s_size] == '\'' || input[quote.s_size] == '\"')
		{
			if (__del_quotes_extension_1(&quote, &input))
				return (NULL);
		}
		else
		{
			if (input[quote.s_size] == '$')
			{
				if (__del_quotes_extension_3(&quote, &input))
					continue ;
			}
			else
				++quote.s_size;
		}
	}
	return (input);
}

static int	__del_quotes_extension_1(t_quote *__restrict quote,
			char *__restrict *__restrict input_ptr)
{
	quote->quote_index = ft_strchr((*input_ptr) + quote->s_size + 1,
			(*input_ptr)[quote->s_size]);
	if (quote->quote_index == NULL)
		return (1);
	quote->r_size = ft_strlen(quote->quote_index + 1);
	quote->q_size = quote->quote_index - (*input_ptr) - quote->s_size - 1;
	if ((*input_ptr)[quote->s_size] == '\'' || ft_memchr((*input_ptr)
		+ quote->s_size + 1, '$', quote->q_size) == NULL)
	{
		ft_memmove((*input_ptr) + quote->s_size, (*input_ptr) + quote->s_size
			+ 1, quote->q_size);
		ft_memmove(quote->quote_index - 1, quote->quote_index + 1,
			quote->r_size);
		quote->quote_index[quote->r_size - 1] = 0;
		quote->s_size = quote->s_size + quote->q_size;
	}
	else
		__del_quotes_extension_2(quote, input_ptr);
	return (0);
}

static void	__del_quotes_extension_2(t_quote *__restrict quote,
			char *__restrict *__restrict input_ptr)
{
	*(quote->quote_index) = 0;
	quote->string = dollar_commutate(ft_strdup((*input_ptr) + quote->s_size
				+ 1));
	quote->e_size = ft_strlen(quote->string);
	quote->input = (char *)xmalloc(quote->s_size + quote->e_size + quote->r_size
			+ 1);
	ft_memcpy(quote->input, (*input_ptr), quote->s_size);
	ft_memcpy(quote->input + quote->s_size, quote->string, quote->e_size);
	ft_memcpy(quote->input + quote->s_size + quote->e_size, quote->quote_index
		+ 1, quote->r_size);
	free((*input_ptr));
	(*input_ptr) = quote->input;
	quote->s_size = quote->s_size + quote->e_size;
}

static int	__del_quotes_extension_3(t_quote *__restrict quote,
			char *__restrict *__restrict input_ptr)
{
	quote->string = (*input_ptr) + quote->s_size + 1;
	if ((*input_ptr)[quote->s_size + 1] == '?')
		(*input_ptr) = dollar_commutate_extension_2((*input_ptr), (*input_ptr)
				+ quote->s_size, &quote->string);
	else if (ft_isalnum((*input_ptr)[quote->s_size + 1]))
		(*input_ptr) = dollar_commutate_extension_1((*input_ptr), (*input_ptr)
				+ quote->s_size, &quote->string);
	else if (!ft_isspace((*input_ptr)[quote->s_size + 1]) && (*input_ptr)[quote
		->s_size + 1])
	{
		ft_memmove((*input_ptr) + quote->s_size, (*input_ptr) + quote->s_size
			+ 1, ft_strlen((*input_ptr) + quote->s_size));
		return (1);
	}
	quote->s_size = quote->string - (*input_ptr);
	return (0);
}
