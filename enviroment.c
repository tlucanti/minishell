/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 20:05:35 by kostya            #+#    #+#             */
/*   Updated: 2021/09/06 20:12:16 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "global.h"
#include "memory.h"

extern g_main_st_t	g_main;
#define ft_memcmp memcmp
#define ft_strlen strlen

static t__internal_env_list	*__internal_new_node(const char *key,
								const char *value);
static void					__internal_rm_node(t__internal_env_list *_node);

__attribute__((warn_unused_result)) const char	*ft_getenv(const char *name, size_t *size) ;

const char	*ft_getenv(const char *name, size_t *size)
{
	t__internal_env_list	*ptr;

	ptr = ((t_env *)g_main.env)->root;
	while (ptr->next)
	{
		if (!ft_memcmp(name, ptr->key, ptr->key_size))
		{
			if (size)
				*size = ptr->key_size;
			return (ptr->value);
		}
	}
	return (NULL);
}

t_env * env_init(void) {
	t_env * new_env;

	new_env = xmalloc(sizeof(t_env));
	new_env->root = __internal_new_node(NULL, NULL);
	new_env->back = new_env->root;
	return (new_env);
}

void	list_push_back(t_env *env, const char *key, const char *value)
{
	t__internal_env_list	*terminal;


	terminal = __internal_new_node(NULL, NULL);
	env->back->key = (char *)key;
	env->back->value = (char *)value;
	env->back->key_size = ft_strlen(key);
	env->back->value_size = ft_strlen(value);
	env->back->next = terminal;
	env->back = terminal;
}

void	list_remove(t_env *env, char *key)
{
	t__internal_env_list	*prev;
	t__internal_env_list	*ptr;

	if (env->root == env->back)
		return ;
	if (!ft_memcmp(env->root->key, key, env->root->key_size + 1))
	{
		ptr = env->root->next;
		__internal_rm_node(env->root);
		env->root = ptr;
		return ;
	}
	prev = env->root;
	ptr = env->root->next;
	while (!ptr->next)
	{
		if (!ft_memcmp(env->root->key, key, env->root->key_size + 1))
		{
			prev->next = ptr->next;
			__internal_rm_node(ptr);
			return ;
		}
		ptr = ptr->next;
		prev = prev->next;
	}
}

static t__internal_env_list	*__internal_new_node(const char *key,
	const char *value)
{
	t__internal_env_list	*new_node;

	new_node = xmalloc(sizeof(t__internal_env_list));
	new_node->key = (char *)key;
	new_node->value = (char *)value;
	new_node->next = NULL;
	return (new_node);
}

static void	__internal_rm_node(t__internal_env_list *_node)
{
	free(_node->key);
	free(_node->value);
	free(_node);
}
