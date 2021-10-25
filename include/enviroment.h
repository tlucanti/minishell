/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 22:30:40 by kostya            #+#    #+#             */
/*   Updated: 2021/10/25 13:43:00 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# define ENVIROMENT_H

# include <stddef.h>
# include <string.h>
# include <unistd.h>

typedef struct s__internal_env_list
{
	char			*restrict	key;
	char			*restrict	value;
	size_t						key_size;
	size_t						value_size;
	struct s__internal_env_list	*next;
}	t__internal_env_list;

typedef struct s_env
{
	t__internal_env_list	*root;
	t__internal_env_list	*back;
	size_t					size;
}	t_env;

char	*ft_getenv_s(const char *name, size_t *size)
			__attribute__((warn_unused_result));
char	*ft_getenv(const char *name, size_t *size)
			__attribute__((warn_unused_result));
t_env		*env_init(void) __attribute__((warn_unused_result));
void		list_insert(t_env *env, const char *key, const char *value);
void		list_clear(t_env *env);
void		list_remove(t_env *env, char *key);
void		print_env(void);
t_env		*internal_env_storage(void);
char		**mas_gen(void) __attribute__((warn_unused_result));

#endif // ENVIROMENT_H
