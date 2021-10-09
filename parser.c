#include "include/minishell.h"
#include "include/enviroment.h"
#include "include/error.h"
#include "include/parser.h"
#include "include/minishell.h"
#include "include/libft.h"

static int is_token(char *arr)
{
	if (arr != OUT_APPEND && arr != OUT_WRITE && arr != HEREDOC
		 && arr != INPUT && arr != PIPE && arr != UNO_QUOTE && arr != DBL_QUOTE)
		return (0);
	return ((int)*arr);
}

static int is_env_token(int c)
{
	return (c == '$');
}

static int		check_double_env(char const *s)
{
	if (*s && *(s + 1) && *s == '$' && *(s + 1) == '$')
		return (1);
	return (0);
}

char	**ft_split_special(char const *s, int (*f)(int))
{
	char	**ret;
	size_t	arrlen;
	size_t	size;

	ret = (char **)ft_calloc(1, sizeof(char **));
	if (s == NULL || ret == NULL)
		return (NULL);
	arrlen = 0;
	while (*s)
	{
		if (check_double_env(s))
		{
			ret = ft_str_append_sized(ret, (char *)(s), 1, arrlen++);
			s += 2;
			continue ;
		}
		while (f(*s) && *s)
			s++;
		if (!*s)
			break ;
		size = 0;
		while (!f(*s) && *s)
		{
			size++;
			s++;
		}
		ret = ft_str_append_sized(ret, (char *)(s - size), size, arrlen++);
		if (ret == NULL)
			return (NULL);
	}
	return (ft_error_test_ft_split(ret));
}

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

char	*ft_strjoin_s1free(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_s;
	char	*to_free;

	to_free = (char *)s1;
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

char *make_dollar_great_again(char *src)
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
	res = (char *)ft_getenv_s(src, &env_res_len);
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

char *get_all_env(char *arr)
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
			temp2 = "?"; //derrick comment: later add get_q_mark();
		else if (ft_strchr(temp[i], '='))
			temp2 = (char *)make_dollar_great_again(temp[i]);
		else
			temp2 = (char *)ft_getenv_s(temp[i], &why);
		res = ft_strjoin_s1free(res, temp2);
	}
	clear_split(temp);
	return (res);
}

void expand_env(char **arr)
{
	int		i;
	char	*temp;
	temp = 0;

	i = -1;
	while (arr[++i])
	{
		if (is_token(arr[i]))
			continue ;
		if (ft_strhaschr(arr[i], '$') && (i == 0 || arr[i - 1] != UNO_QUOTE))
		{
			temp = get_all_env(arr[i]);
			free(arr[i]);
			arr[i] = ft_strdup(temp);
		}
	}
}

char		*ft_strcpy(char *dest, const char *src)
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



int	complex_parser(const char *input)
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
