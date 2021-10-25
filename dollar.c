/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:13:02 by kostya            #+#    #+#             */
/*   Updated: 2021/10/25 15:38:45 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parser.h"
#include "include/memory.h"
#include "include/libft.h"
#include "include/enviroment.h"

static char	*_dollar_commutate_extension(char *string, char *dollar_start, char **dollar_next);

void	enforce_env(char **array)
{
	while (*array)
	{
		if ((size_t)(*array) < ANY_TOKEN && (size_t)(*array) & DOUBLE_SKIP_DOLLAR)
			array += 2;
		else if ((size_t)(*array) < ANY_TOKEN && (size_t)(*array) & SINGLE_SKIP_DOLLAR)
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
		string = _dollar_commutate_extension(string, dollar, &dollar_next);
		printf("next: %s\n", dollar_next);
		dollar = dollar_next;
	}
}

static char	*_dollar_commutate_extension(char *string, char *dollar_start, char **dollar_next)
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
	dollar.new_string = xmalloc(dollar_start - string + dollar.env_size
			+ dollar.residue_size + 1);
	ft_memcpy(dollar.new_string, string, dollar_start - string);
	ft_memcpy(dollar.new_string + (dollar_start - string),
		dollar.new_env, dollar.env_size);
	ft_memcpy(dollar.new_string + (dollar_start - string)
		+ dollar.env_size, dollar.dollar_end, dollar.residue_size);
	*dollar_next = dollar.new_string + (dollar_start - string)
		+ dollar.env_size;
	free(string);
	return (dollar.new_string);

}
