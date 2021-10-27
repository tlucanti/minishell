/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:46:59 by kostya            #+#    #+#             */
/*   Updated: 2021/10/27 14:55:33 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/enviroment.h"
#include "../inc/memory.h"
#include "../inc/libft.h"
#include "../inc/minishell.h"

static t__internal_env_list	*__internal_new_node(void) __attribute__((
									warn_unused_result)) __attribute__((
									__nothrow__));
void						__internal_rm_node(
								t__internal_env_list *__restrict _node)
							__attribute__((__nothrow__));
static int					__list_insert_extension(
								t__internal_env_list *__restrict
								*__restrict p_ptr,
								t__internal_env_list *__restrict
								*__restrict p_new_node,
								t__internal_env_list *__restrict
								*__restrict p_prev,
								t_env *__restrict env) __attribute__((
									warn_unused_result)) __attribute__((
									__nothrow__));

void	list_insert(t_env *__restrict env, const char *__restrict key,
			const char *__restrict value)
{
	t__internal_env_list	*prev;
	t__internal_env_list	*ptr;
	t__internal_env_list	*new_node;

	++env->size;
	new_node = __internal_new_node();
	new_node->key = (char *)key;
	new_node->value = (char *)value;
	new_node->key_size = ft_strlen(key);
	new_node->value_size = ft_strlen(value);
	if (env->root->next == NULL || ft_memcmp(env->root->key, new_node->key,
			env->root->key_size + 1) > 0)
	{
		new_node->next = env->root;
		env->root = new_node;
		return ;
	}
	prev = env->root;
	ptr = prev->next;
	if (__list_insert_extension(&ptr, &new_node, &prev, env))
		return ;
	prev->next = new_node;
	new_node->next = ptr;
}

static int	__list_insert_extension(
				t__internal_env_list *__restrict *__restrict p_ptr,
				t__internal_env_list *__restrict *__restrict p_new_node,
				t__internal_env_list *__restrict *__restrict p_prev,
				t_env *__restrict env)
{
	int	cmp;

	while ((*p_ptr)->next)
	{
		cmp = ft_memcmp((*p_ptr)->key, (*p_new_node)->key,
				(*p_ptr)->key_size + 1);
		if (cmp == 0)
		{
			(*p_prev)->next = (*p_new_node);
			(*p_new_node)->next = (*p_ptr)->next;
			__internal_rm_node((*p_ptr));
			--env->size;
			return (1);
		}
		if (cmp > 0)
		{
			(*p_prev)->next = (*p_new_node);
			(*p_new_node)->next = (*p_ptr);
			return (1);
		}
		(*p_prev) = (*p_ptr);
		(*p_ptr) = (*p_ptr)->next;
	}
	return (0);
}

t_env	*env_init(void)
{
	char *__restrict	key;
	char *__restrict	value;
	t_env				*new_env;
	size_t				it;

	new_env = (t_env *)xmalloc(sizeof(t_env));
	new_env->root = __internal_new_node();
	new_env->back = new_env->root;
	it = 0;
	while (__environ[it])
	{
		builtin_export_split(__environ[it], &key, &value);
		list_insert(new_env, key, value);
		++it;
	}
	return (new_env);
}

void	list_remove(t_env *__restrict env, char *__restrict key)
{
	t__internal_env_list	*prev;
	t__internal_env_list	*ptr;

	if (env->root == env->back)
		return ;
	prev = env->root;
	ptr = prev->next;
	if (!ft_memcmp(prev->key, key, prev->key_size + 1))
	{
		__internal_rm_node(prev);
		env->root = ptr;
		return ;
	}
	while (!ptr->next)
	{
		if (!ft_memcmp(env->root->key, key, env->root->key_size + 1))
		{
			prev->next = ptr->next;
			__internal_rm_node(ptr);
			--env->size;
			return ;
		}
		ptr = ptr->next;
		prev = prev->next;
	}
}

static t__internal_env_list	*__internal_new_node(void)
{
	t__internal_env_list	*new_node;

	new_node = (t__internal_env_list *)xmalloc(sizeof(t__internal_env_list));
	new_node->key = NULL;
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}
