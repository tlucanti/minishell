/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:50:35 by kostya            #+#    #+#             */
/*   Updated: 2021/10/28 17:52:06 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/enviroment.h"
#include "../inc/memory.h"
#include "../inc/libft.h"

static char	*__mas_gen_extension(const char *str1, const char *str2,
				size_t size1, size_t size2) __attribute__((
					warn_unused_result)) __attribute__((__nothrow__));
void		__internal_rm_node(
				t__internal_env_list *__restrict _node)	__attribute__((
					__nothrow__));

void	list_clear(t_env *__restrict env)
{
	t__internal_env_list	*ptr;
	t__internal_env_list	*next;

	ptr = env->root;
	while (ptr)
	{
		next = ptr->next;
		__internal_rm_node(ptr);
		ptr = next;
	}
	free(env);
}

void	__internal_rm_node(t__internal_env_list *__restrict _node)
{
	free(_node->key);
	free(_node->value);
	free(_node);
}

char	**mas_gen(void)
{
	t__internal_env_list	*ptr;
	size_t					size;
	char					**mas;

	mas = (char **)xmalloc(sizeof(char *) * (internal_env_storage()->size + 1));
	ptr = internal_env_storage()->root;
	size = 0;
	while (ptr->next)
	{
		mas[size] = __mas_gen_extension(ptr->key, ptr->value, ptr->key_size,
				ptr->value_size);
		++size;
		ptr = ptr->next;
	}
	mas[size] = NULL;
	return (mas);
}

static char	*__mas_gen_extension(const char *str1, const char *str2,
				size_t size1, size_t size2)
{
	char	*sum;

	sum = (char *)xmalloc(sizeof(char) * (size1 + size2 + 2));
	ft_memcpy(sum, str1, size1);
	sum[size1] = '=';
	ft_memcpy(sum + size1 + 1, str2, size2);
	sum[size1 + size2 + 1] = '\0';
	return (sum);
}
