/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:13:02 by kostya            #+#    #+#             */
/*   Updated: 2021/10/26 23:09:23 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parser.h"
#include "include/memory.h"
#include "include/libft.h"
#include "include/enviroment.h"
#include "include/minishell.h"

static char	*dollar_commutate_extension_1(char *string, char *dollar_start,
				char **dollar_next)
			__attribute__((warn_unused_result)) __attribute__((__nothrow__));
static char	*dollar_commutate_extension_2(char *string, char *dollar_start,
				char **dollar_next)
			__attribute__((warn_unused_result)) __attribute__((__nothrow__));

void	enforce_env(char **__restrict array)
{
	while (*array)
	{
		if ((size_t)(*array) < ANY_TOKEN && (size_t)(*array)
			& DOUBLE_SKIP_DOLLAR)
			array += 2;
		else if ((size_t)(*array) < ANY_TOKEN && (size_t)(*array)
			& SINGLE_SKIP_DOLLAR)
			++array;
		else
		{
			*array = dollar_commutate(*array);
			++array;
		}
	}
}

char	*dollar_commutate(char *string)
{
	char	*dollar;
	char	*dollar_next;

	dollar = string;
	dollar_next = NULL;
	while (1)
	{
		dollar = ft_strchr(dollar, '$');
		if (dollar == NULL)
			return (string);
		if (dollar[1] == '?')
			string = dollar_commutate_extension_2(string, dollar, &dollar_next);
		else
			string = dollar_commutate_extension_1(string, dollar, &dollar_next);
		dollar = dollar_next;
	}
}

static char	*dollar_commutate_extension_1(char *string, char *dollar_start,
				char **dollar_next)
{
	t_dollar	dollar;

	dollar.dollar_end = dollar_start + 1;
	*dollar_next = dollar.dollar_end;
	if (!ft_isalnum(*dollar.dollar_end))
		return (string);
	while (ft_isalnum(*dollar.dollar_end))
		++dollar.dollar_end;
	dollar._saved_char = *dollar.dollar_end;
	*dollar.dollar_end = 0;
	dollar.new_env = ft_getenv_s(dollar_start + 1, &dollar.env_size);
	*dollar.dollar_end = dollar._saved_char;
	dollar.residue_size = ft_strlen(dollar.dollar_end);
	dollar.new_string = (char *)xmalloc(dollar_start - string + dollar.env_size
			+ dollar.residue_size + 1);
	ft_memcpy(dollar.new_string, string, dollar_start - string);
	ft_memcpy(dollar.new_string + (dollar_start - string),
		dollar.new_env, dollar.env_size);
	ft_memcpy(dollar.new_string + (dollar_start - string)
		+ dollar.env_size, dollar.dollar_end, dollar.residue_size + 1);
	*dollar_next = dollar.new_string + (dollar_start - string)
		+ dollar.env_size;
	free(string);
	return (dollar.new_string);
}

static char	*dollar_commutate_extension_2(char *string, char *dollar_start,
				char **dollar_next)
{
	t_dollar	dollar;

	dollar.exit_status = ft_itoa(exit_status_storage(0, 0));
	dollar.exit_status_size = ft_strlen(dollar.exit_status);
	dollar.residue_size = ft_strlen(dollar_start + 1);
	dollar.new_string = (char *)xmalloc(dollar_start - string
			+ dollar.exit_status_size + dollar.residue_size + 1);
	ft_memcpy(dollar.new_string, string, dollar_start - string);
	ft_memcpy(dollar.new_string + (dollar_start - string), dollar.exit_status,
		dollar.exit_status_size);
	ft_memcpy(dollar.new_string + (dollar_start - string)
		+ dollar.exit_status_size, dollar_start + 2, dollar.residue_size + 1);
	free(dollar.exit_status);
	free(string);
	*dollar_next = dollar.new_string + (dollar_start - string) + 1;
	return (dollar.new_string);
}
