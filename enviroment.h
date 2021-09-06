/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 22:30:40 by kostya            #+#    #+#             */
/*   Updated: 2021/09/06 00:28:52 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include <stddef.h>
#include <string.h>
#define ft_strcmp strcmp

typedef struct s__internal_env_list
{
	char				*key;
	char				*value;
	size_t			key_size;
	size_t			value_size;
	struct s__internal_env_list	*next;
}	t__internal_env_list;

typedef struct s_env
{
	t__internal_env_list	*root;
	t__internal_env_list	*back;
}	t_env;

__attribute__((warn_unused_result)) const char	*ft_getenv(const char *name, size_t *size);
t_env		*env_init(void);
void		list_push_back(t_env *env, const char *key, const char *value);
void		list_remove(t_env *env, char *key);

#endif
