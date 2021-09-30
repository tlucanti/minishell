/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:56:55 by kostya            #+#    #+#             */
/*   Updated: 2021/09/18 18:28:36 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "enviroment.h"
#include "error.h"
#include "signal.h"
#include "colors.h"

static int	update_promt(char *promt);

int	main(void)
{
	char	*input;
	char	promt[PATH_MAX];

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	set_autoattr(0, 0, ECHOCTL);
	internal_env_storage();
	while (1)
	{
		update_promt(promt);
		signal(SIGINT, handler_signint_readline);
		input = readline(promt);
		signal(SIGINT, SIG_IGN);
		if (!input)
		{
			printf("exit\n");
			free(input);
			xexit(0);
		}
		rl_bind_key('\t', rl_complete);
		add_history(input);
		not_so_simple_parser(input);
		free(input);
	}
}

int	__update_promt(char *promt)
// "kostya:/media/kostya/Data/CLion/Minishell/cmake-build-debug $ "
{
	snprintf(promt, PATH_MAX, "%s%s%s:%s%s%s %s\001➜\002%s ",
		READLINE_GREEN, ft_getenv_s("USER", NULL), READLINE_RESET,
		READLINE_BLUE, getcwd(NULL, 1024), READLINE_RESET,
		READLINE_YELLOW, READLINE_RESET);
	return (0);
}

int	update_promt(char *promt)
// tlucanti:/home/tlucanti $
{
	const char		*env;
	size_t			user_size;
	unsigned int	cwd_size;
	size_t			home_size;
	size_t			shift;

	shift = sizeof(READLINE_GREEN) - 1;
	ft_memcpy(promt, READLINE_GREEN, shift);
	env = ft_getenv_s("USER", &user_size);
	ft_memcpy(promt + shift, env, user_size);
	shift += user_size;
	ft_memcpy(promt + shift, READLINE_WHITE ":" READLINE_BLUE,
		sizeof(READLINE_WHITE) + sizeof(READLINE_BLUE) - 1);
	shift += sizeof(READLINE_WHITE) + sizeof(READLINE_BLUE) - 1;
	env = getcwd(promt + shift, PATH_MAX);
	(void)env;
	cwd_size = ft_strlen(promt + shift);
	env = ft_getenv_s("HOME", &home_size);
	if (!ft_memcmp(promt + shift, env, home_size + 1))
		promt[shift] = '~';
	else
		shift += cwd_size - 1;
	ft_memcpy(promt + shift + 1, " " READLINE_YELLOW "\001➜\002" READLINE_RESET " ",
		sizeof(READLINE_YELLOW) + sizeof(READLINE_RESET) + 6);
	return (0);
}


void print_my_cool_split(char **p);

#define HEREDOC		(char *)3

int builtin (char **arr)
{
	static int ret;

	 if (!ft_strcmp(arr[0], "echo"))
		ret = builtin_echo(arr);
	else if (!ft_strcmp(arr[0], "cd"))
		ret = builtin_cd(arr);
	else if (!ft_strcmp(arr[0], "pwd"))
		ret = builtin_pwd(arr);
	else if (!ft_strcmp(arr[0], "export"))
		ret = builtin_export(arr);
	else if (!ft_strcmp(arr[0], "unset"))
		ret = builtin_unset(arr);
	else if (!ft_strcmp(arr[0], "env"))
		ret = builtin_env(arr);
	else if (!ft_strcmp(arr[0], "exit"))
		ret = builtin_exit(arr);
	else if (arr[1] == HEREDOC)
	{
		ret = 0;
		printf("heredoc > %s\n", builtin_heredoc(arr[2]));
	}
	else
		ret = builtin_execve(arr);
	return (ret);
}

/*
int check_arr_length(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	if (i > 3)
		return (0);
	return (1);
}
*/
/*
edit this all
*/

static char		*ft_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (ptr);
}

char			*ft_strdup(const char *src)
{
	char *dup;

	if ((dup = malloc(ft_strlen(src) + 1)))
		return (ft_strcpy(dup, src));
	else
		return (0);
}

static int is_token(char *arr)
{
	if (arr != OUT_APPEND && arr != OUT_WRITE && arr != HEREDOC
		 && arr != INPUT && arr != PIPE && arr != UNO_QUOTE && arr != DBL_QUOTE)
		return (0);
	return (1);
}

int is_env_token(int c)
{
	return (c == '$');
}

int		ft_strhaschr(const char *str, int ch)
{
	unsigned char	cc;
	int				ret;

	ret = 0;
	cc = (unsigned char)ch;
	while (*str)
	{
		if (*str == cc)
		{
			ret = 1;
			return (ret);
		}
		str++;
	}
	if (*str == 0 && ch == 0)
		ret = 1;
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_s;
	char	*to_free;

	to_free = s1;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_s = (char *)malloc(s1_len + s2_len + 1);
	if (new_s == 0)
		return (NULL);
	ft_memcpy(new_s, s1, s1_len);
	ft_memcpy(new_s + s1_len, s2, s2_len + 1);
	if (to_free)
		free(to_free);
	return (new_s);
}
/*
	derrick comment: optimize (0) for debugging purpose, remove on release
*/
static char *get_all_env(char *arr) __attribute__((optimize(0)));

static char *make_dollar_great_again(char *src)
{
	char *temp;
	int i;
	int env_name_len;
	char *res;
	size_t env_res_len;

	env_name_len = 0;
	i = 0;
	env_res_len= 0;

	while (src[env_name_len] != '=')
		env_name_len++;
	src[env_name_len] = 0;
	res = ft_getenv_s(src, &env_res_len);
	src[env_name_len] = '=';
	i = ft_strlen(src) + env_res_len - env_name_len + (!env_name_len) + 1;
	temp = malloc(i);
	if (!env_name_len)
		ft_memcpy(temp, "$", 1);
	else if(env_res_len)
		ft_memcpy(temp, res, env_res_len);
	ft_memcpy(temp + env_res_len + (!env_name_len), src + env_name_len, i);
	temp[i] = 0;
	return (temp);
}

static char *get_all_env(char *arr)
{
	char *res;
	char **temp;
	char *temp2;
	int i;
	size_t why;

	i = -1;
	res = malloc(1);
	*res = '\0';
	temp2 = 0;

	temp = ft_split_special(arr, is_env_token);
	print_my_cool_split(temp);
	while (temp[++i])
	{
		if (temp[i][0] == '?')
			temp2 = '?'; //derrick comment: later add get_q_mark();
		else if (ft_strchr(temp[i], '='))
			temp2 = make_dollar_great_again(temp[i]);
		else
			temp2 = ft_getenv_s(temp[i], &why);
		res = ft_strjoin(res, temp2);
	}
	clear_split(temp);
	return (res);
}

static void expand_env(char **arr)
{
	int		i;
	char	*temp;
	temp = 0;

	i = -1;
	while (arr[++i])
	{
		if (is_token(arr[i]))
		{
			printf("istoken");
			continue ;
		}
		if (ft_strhaschr(arr[i], '$') && (i == 0 || arr[i - 1] != UNO_QUOTE))
		{
			temp = get_all_env(arr[i]);
			free(arr[i]);
			if (temp)
				arr[i] = ft_strdup(temp);
			else
				arr[i] = NULL;
		}
	}
}


int	not_so_simple_parser(const char *input)
{
	char	**arr;
	static int		ret;

	 arr = smart_split(input, ft_isspace);
	//arr = ft_split(input, ft_isspace);
	 print_my_cool_split(arr);
	 expand_env(arr);
	 print_my_cool_split(arr);
	//exit(0);
	// return (0);
	if (!*arr)
		return (0);
	else if (1)
		ret = builtin(arr);
	clear_split(arr);
	return (ret);
}

void	clear_split(char **array)
{
	char	**ptr;

	ptr = array;
	while (*array)
	{
		free(*array);
		++array;
	}
	free(ptr);
}

int	set_autoattr(int desc, int value, int what)
{
	struct termios	settings;
	int				result;

	result = tcgetattr(desc, &settings);
	if (result < 0)
	{
		perror ("error in tcgetattr");
		return (1);
	}
	settings.c_lflag &= ~what;
	if (value)
		settings.c_lflag |= what;
	result = tcsetattr(desc, TCSANOW, &settings);
	if (result < 0)
	{
		perror ("error in tcgetattr");
		return (1);
	}
	return (0);
}
