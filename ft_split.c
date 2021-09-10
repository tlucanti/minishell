/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:16:40 by tlucanti          #+#    #+#             */
/*   Updated: 2021/09/10 16:32:20 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_error_test_ft_split(char **ret) __attribute__((warn_unused_result));
static char	**ft_str_append_sized(char **arr, char *str, size_t size, size_t arrlen) __attribute__((warn_unused_result));
static char	**ft_push_back_char_ss(char **arr, char *new_s, size_t arrlen) __attribute__((warn_unused_result));
static void	*ft_arr_clear(char **arr);

char	**ft_split(char const *s, int (*f)(int))
{
	char	**ret;
	size_t	arrlen;
	size_t	size;

	ret = (char **)ft_calloc(1, sizeof(char **));
	if (s == NULL || ret == NULL)
		return (NULL);
	arrlen = 0;
	while (*s)
	{
		while (f(*s) && *s)
			s++;
		if (!*s)
			break ;
		size = 0;
		while (!f(*s) && *s)
		{
			size++;
			s++;
		}
		ret = ft_str_append_sized(ret, (char *)(s - size), size, arrlen++);
		if (ret == NULL)
			return (NULL);
	}
	return (ft_error_test_ft_split(ret));
}

static char	**ft_error_test_ft_split(char **ret)
{
	if (ret == NULL)
		return (NULL);
	if (*ret == NULL)
		return (ret);
	if (!*ret)
		return (ft_str_append_sized(ret, (char *)ft_calloc(1, 1), 1, 0));
	return (ret);
}

static char	**ft_str_append_sized(char **arr, char *str, size_t size, size_t arrlen)
{
	char	*new_s;

	new_s = (char *)malloc(size + 1);
	if (new_s == NULL)
		return ((char **)ft_arr_clear(arr));
	ft_memcpy(new_s, str, size + 1);
	new_s[size] = 0;
	return (ft_push_back_char_ss(arr, new_s, arrlen));
}

static char	**ft_push_back_char_ss(char **arr, char *new_s, size_t arrlen)
{
	char	**new_arr;
	char	**new_arr_ptr;
	char	**old_arr_ptr;

	if (arr == NULL)
	{
		new_arr = (char **)ft_calloc(sizeof(char *), 2);
		if (new_arr == NULL)
			return (NULL);
		new_arr[0] = new_s;
	}
	else
	{
		old_arr_ptr = arr;
		new_arr = (char **)malloc(sizeof(char *) * (arrlen + 2));
		if (new_arr == NULL)
			return ((char **)ft_arr_clear(arr));
		new_arr_ptr = new_arr;
		while (*arr)
			*new_arr_ptr++ = *arr++;
		*new_arr_ptr++ = new_s;
		*new_arr_ptr = NULL;
		free(old_arr_ptr);
	}
	return (new_arr);
}

static void	*ft_arr_clear(char **arr)
{
	char	**ptr_init;

	ptr_init = arr;
	while (*arr)
		free(*arr++);
	free(ptr_init);
	return (0);
}
