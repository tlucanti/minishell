/**
 *    author:  kostya
 *    created: 2021-08-30 20:15:18
 *    modified 2021-08-30 20:16:09
 **/

#ifndef MINISHELL_H
#define MINISHELL_H

#include <linux/limits.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <errno.h>

#define ECNF -2 // ERROR COMMAND NOT FOUND
#define ETMA -3 // ERROR TOO MANY ARGUMENTS

int	init_g_main();
int	update_promt();
char	**ft_split(char const *s, int (*is_space)(int));
void clear_split(char **array);
size_t	putsfd(int fd, const char *str);
void xperror(const char *parent, int errorcode, const char *arg);
const char *xstrerror(int errorcode);
int	simple_parcer(const char *input);
const char *xgetenv(const char *env);

int	builtin_echo(__attribute__((unused)) __attribute__((unused)) const char *name, const char **args);
static const char **builtin_echo_arg_check(const char **argv, int * restrict n_opt);
int	builtin_cd(__attribute__((unused)) const char *path, const char **argv);
int	builtin_pwd(__attribute__((unused)) char *path, const char **argv);
int	builtin_export(__attribute__((unused)) const char *path, const char **argv);
int builtin_export_split(const char *string, char **restrict key, char **restrict value);
int	builtin_unset(const char *arg);
int	builtin_env(void);
void	builtin_exit(const char *status);

char	**ft_error_test_ft_split(char **ret);
char	**ft_str_append_sized(char **arr, char *str, size_t size, size_t arrlen);
char	**ft_push_back_char_ss(char **arr, char *new_s, size_t arrlen);
void	*ft_arr_clear(char **arr);


#define ft_strlen strlen
#define ft_memcpy memcpy
#define ft_memcmp memcmp
#define ft_calloc calloc
#define ft_atoi atoi

#endif
