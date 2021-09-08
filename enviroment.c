/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 20:05:35 by kostya            #+#    #+#             */
/*   Updated: 2021/09/08 12:06:35 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment.h"
#include "global.h"
#include "memory.h"

extern g_main_st_t	g_main;
#define ft_memcmp memcmp
#define ft_strlen strlen

static t__internal_env_list *f__internal_new_node() __attribute__((warn_unused_result));
static void					f__internal_rm_node(t__internal_env_list *_node);

const char	*ft_getenv(const char *name, size_t *size)
{
	t__internal_env_list	*ptr;

	ptr = ((t_env *)g_main.env)->root;
	while (ptr->next)
	{
		if (!ft_memcmp(name, ptr->key, ptr->key_size))
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

const char	*ft_getenv_s(const char *name, size_t *size)
{
	const char	*ret;

	ret = ft_getenv(name, size);
	if (!ret)
		return ("");
	return (ret);
}

t_env * env_init(void) {
	t_env	*new_env;
	// char	*restrict key;
	// char	*restrict value;
	// size_t	it;

	new_env = xmalloc(sizeof(t_env));
	new_env->root = f__internal_new_node();
	new_env->back = new_env->root;
	// it = 0;
	// while (__environ[it])
	// {
	// 	builtin_export_split(__environ[it], &key, &value);
	// 	list_insert(new_env, key, value);
	// 	++it;
	// }
	return (new_env);
}

void	list_insert(t_env *env, const char *key, const char *value)
{
	t__internal_env_list	*prev;
	t__internal_env_list	*ptr;
	t__internal_env_list	*new_node;
	int						cmp;

	new_node = f__internal_new_node();
	new_node->key = (char *)key;
	new_node->value = (char *)value;
	new_node->key_size = ft_strlen(key);
	new_node->value_size = ft_strlen(value);
	if (env->root->next == NULL || ft_memcmp(env->root->key, new_node->key, env->root->key_size + 1) > 0)
		// we need to insert node to the beginning of list
	{
		new_node->next = env->root;
		env->root = new_node;
		return ;
	}
	prev = env->root;
	ptr = prev->next;
	while (ptr->next)
	{
		cmp = ft_memcmp(ptr->key, new_node->key, ptr->key_size + 1);
		if (cmp == 0)
			// we need to replace node if key exist
		{
			prev->next = new_node;
			new_node->next = ptr->next;
			f__internal_rm_node(ptr);
			return ;
		}
		if (cmp > 0)
			// we need to insert key if we we found compare border
		{
			prev->next = new_node;
			new_node->next = ptr;
			return ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	prev->next = new_node;
	new_node->next = ptr;
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
		f__internal_rm_node(env->root);
		env->root = ptr;
		return ;
	}
	prev = env->root;
	ptr = prev->next;
	while (!ptr->next)
	{
		if (!ft_memcmp(env->root->key, key, env->root->key_size + 1))
		{
			prev->next = ptr->next;
			f__internal_rm_node(ptr);
			return ;
		}
		ptr = ptr->next;
		prev = prev->next;
	}
}

void	print_list(t_env *env)
{
	t__internal_env_list	*ptr;

	ptr = env->root;
	while (ptr->next)
	{
		printf("%s=%s\n", ptr->key, ptr->value);
		ptr = ptr->next;
	}
}

static t__internal_env_list *f__internal_new_node()
{
	t__internal_env_list	*new_node;

	new_node = xmalloc(sizeof(t__internal_env_list));
	new_node->key = NULL;
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

static void	f__internal_rm_node(t__internal_env_list *_node)
{
	free(_node->key);
	free(_node->value);
	free(_node);
}
