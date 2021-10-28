/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 22:30:40 by kostya            #+#    #+#             */
/*   Updated: 2021/10/28 16:50:42 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# define ENVIROMENT_H

# include <stddef.h>
# include <string.h>
# include <unistd.h>

typedef struct s__internal_env_list
{
	char *__restrict			key;
	char *__restrict			value;
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

char	*ft_getenv_s(const char *__restrict name, size_t *__restrict size)
		__attribute__((warn_unused_result)) __attribute__((__nothrow__));
char	*ft_getenv(const char *__restrict name, size_t *__restrict size)
		__attribute__((warn_unused_result)) __attribute__((__nothrow__));
t_env	*env_init(void)
		__attribute__((warn_unused_result)) __attribute__((__nothrow__));
void	list_insert(t_env *env, const char *key, const char *value)
		__attribute__((__nothrow__));
void	list_clear(t_env *__restrict env)
		__attribute__((__nothrow__));
void	list_remove(t_env *__restrict env, char *__restrict key)
		__attribute__((__nothrow__));
void	print_env(void)
		__attribute__((__nothrow__));
t_env	*internal_env_storage(void)
		__attribute__((warn_unused_result)) __attribute__((__nothrow__));
char	**mas_gen(void)
		__attribute__((warn_unused_result)) __attribute__((__nothrow__));

#endif // ENVIROMENT_H
