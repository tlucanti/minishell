/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:53:32 by kostya            #+#    #+#             */
/*   Updated: 2021/09/15 23:16:32 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <linux/limits.h>

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termios.h>

char		**ft_split(char const *s, int (*is_space)(int)) __attribute__((warn_unused_result));
long long	ft_atol_s(const char *str, int *error);
int			ft_atoi_s(const char *str, int *error);
void		clear_split(char **array);
int			simple_parcer(const char *input);
int			set_autoattr(int desc, int value, int what);

int			builtin_echo(char *const *argv);
int			builtin_cd(char *const *argv);
int			builtin_pwd(char *const *argv);
int			builtin_export(char *const *argv);
int			builtin_export_split(const char *string, char *restrict *key, char *restrict *value);
int			builtin_unset(char *const *argv);
int			builtin_env(char *const *argv);
int			builtin_exit(char *const *argv);
int			builtin_execve(char *const *argv);

# define ft_strlen strlen
# define ft_memcpy memcpy
# define ft_memcmp memcmp
# define ft_calloc calloc
# define ft_atoi(n) strtol((n), NULL, 10)
# define ft_isalnum isalnum
# define ft_isdigit isdigit
# define ft_isalpha isalpha
# define ft_isspace isspace

#endif
