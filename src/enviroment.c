/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 20:05:35 by kostya            #+#    #+#             */
/*   Updated: 2021/10/27 14:55:44 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/enviroment.h"
#include "../inc/memory.h"
#include "../inc/minishell.h"
#include "../inc/libft.h"

char	*ft_getenv(const char *__restrict name, size_t *__restrict size)
/*
** function search and return variable in internal enviroment variable storage
** by `name`, size of found veriable saved in `size`
** if variable not found - return is null pointer (NULL)
** if `size` is NULL - size of variable will not set
*/
{
	t__internal_env_list	*ptr;

	ptr = internal_env_storage()->root;
	while (ptr->next)
	{
		if (!ft_memcmp(name, ptr->key, ft_strlen(name) + 1))
		{
			if (size)
				*size = ptr->value_size;
			return (ptr->value);
		}
		ptr = ptr->next;
	}
	if (size)
		*size = 0;
	return (NULL);
}

char	*ft_getenv_s(const char *__restrict name, size_t *__restrict size)
/*
** function is safe analog of ft_getenv
** difference: if variable not found in internal enviroment variable storage -
** empty string ("") retunrned, not null pointer (NULL) unlike in ft_getenv
*/
{
	char	*ret;

	ret = ft_getenv(name, size);
	if (!ret)
		return ((char *)"");
	return (ret);
}

void	print_env(void)
{
	t__internal_env_list	*ptr;

	ptr = internal_env_storage()->root;
	while (ptr->next)
	{
		printf("%s=%s\n", ptr->key, ptr->value);
		ptr = ptr->next;
	}
}

t_env	*internal_env_storage(void)
{
	static t_env	*env = NULL;

	if (!env)
		env = env_init();
	return (env);
}
