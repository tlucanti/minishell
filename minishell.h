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

#ifndef EXIT_FAILURE
# define EXIT_FAILURE 1
#endif
#ifndef EXIT_SUCCESS
# define EXIT_SUCCESS 0
#endif

#define ECNF -2		// ERROR COMMAND NOT FOUND
#define ETMA -3		// ERROR TOO MANY ARGUMENTS
#define ENAVI -4	// ERROR NOT A VALID IDENTIFIER
#define ENEA -5		// ERROR NOT ENOUGH ARGUMENTS
#define ENUMR -6	// ERROR NUMERIC ARGUMENT REQUIRED

char	**ft_split(char const *s, int (*is_space)(int));
long long	ft_atol_s(const char *str, int *error);
int		ft_atoi_s(const char *str, int *error);
void	clear_split(char **array);
size_t	putsfd(int fd, const char *str);
void	xperror(const char *parent, int errorcode, const char *arg);
int		simple_parcer(const char *input);

int		builtin_echo(__attribute__((unused)) __attribute__((unused)) const char *name, const char **args);
int		builtin_cd(__attribute__((unused)) const char *path, const char **argv);
int		builtin_pwd(__attribute__((unused)) char *path, const char **argv);
int		builtin_export(__attribute__((unused)) const char *path, const char **argv);
int		builtin_export_split(const char *string, char *restrict  *key, char *restrict *value);
int		builtin_unset(__attribute__((unused)) const char *path, const char **argv);
int		builtin_env(__attribute__((unused)) const char *path, const char **argv);
int		builtin_exit(__attribute__((unused)) const char *path, const char **argv);

char	**ft_error_test_ft_split(char **ret);
char	**ft_str_append_sized(char **arr, char *str, size_t size, size_t arrlen);
char	**ft_push_back_char_ss(char **arr, char *new_s, size_t arrlen);
void	*ft_arr_clear(char **arr);
void 	xexit(int status) __attribute__((noreturn));


#define ft_strlen strlen
#define ft_memcpy memcpy
#define ft_memcmp memcmp
#define ft_calloc calloc
#define ft_atoi(n) strtol((n), NULL, 10)
#define ft_isalnum isalnum
#define ft_isdigit isdigit
#define ft_isalpha isalpha
#define ft_isspace isspace

#endif
