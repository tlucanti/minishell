/**
 *	Author:		kostya
 *	Created:	2021-09-05 19:36:31
 *	Modified:	2021-09-06 00:17:09
 **/

#include "minishell.h"
#include "global.h"
#include "enviroment.h"

g_main_st_t g_main;
int main()
{
	char	*input;

	init_g_main();
	env_init();
	while (1)
	{
		update_promt();
		input = readline(g_main.promt);
		if (!input)
		{
			printf("eof found");
			break ;
		}
		rl_bind_key('\t', rl_complete);
		add_history(input);
		simple_parcer(input);
		free(input);
	}
}

int	init_g_main()
{
	return (0);
}

int	update_promt()
// tlucanti:/home/tlucanti $ 
{
	const char		*env;
	size_t			user_size;
	unsigned int	cwd_size;
	size_t	home_size;

	env = ft_getenv("USER", &user_size);
	user_size = ft_strlen(env);
	ft_memcpy(g_main.promt, env, user_size);
	g_main.promt[user_size] = ':';
	getcwd(g_main.promt + user_size + 1, PATH_MAX);
	cwd_size = ft_strlen(g_main.promt);
	env = ft_getenv("HOME", &home_size);
	if (!ft_memcmp(g_main.promt + user_size + 1, env, home_size))
	{
		g_main.promt[user_size + 1] = '~';
		cwd_size = 1;
	}
	g_main.promt[user_size + cwd_size + 1] = ' ';
	g_main.promt[user_size + cwd_size + 2] = '$';
	g_main.promt[user_size + cwd_size + 3] = ' ';
	g_main.promt[user_size + cwd_size + 4] = '\0';
	return (0);
}


// char	*xgetcwd()
// {
// 	int		size;
// 	char	*buffer;
// 	char	*ret;

// 	size = 100;
// 	buffer = (char *)xmalloc(size);
// 	while (1)
// 	{
// 		ret = getcwd(buffer, size);
// 		if (ret)
// 			return (buffer);
// 		size *= 2;
// 		free(buffer);
// 		buffer = xmalloc(size);
// 	}
// }




// char	*xstrsum(const char *str1, const char *str2)
// {
// 	char	*ret;
// 	size_t	str1len;
// 	size_t	str2len;


// 	str1len = ft_strlen(str1);
// 	str2len = ft_strlen(str2);
// 	ret = xmalloc(str1len + str2len + 1);
// 	ft_memcpy(ret, str1, str1len);
// 	ft_memcpy(ret + str1len, str2len);
// 	ret[str1len + strlen] = '\0';
// 	return (ret);
// }

int	is_space(int c)
{
	return (c == ' ');
}

int	simple_parcer(const char *input)
{
	char **arr = ft_split(input, is_space);

	if (!strcmp(arr[0], "echo"))
		return (builtin_echo(NULL, (const char **)(arr + 1)));
	else if (!strcmp(arr[0], "cd"))
		return (builtin_cd(NULL, (const char **)(arr + 1)));
	else if (!strcmp(arr[0], "pwd"))
		return (builtin_pwd(NULL, (const char **)(arr + 1)));
	else if (!strcmp(arr[0], "export"))
		return (builtin_export(NULL, (const char **)(arr + 1)));
	else if (!strcmp(arr[0], "unset"))
		return (builtin_unset(arr[1]));
	else if (!strcmp(arr[0], "env"))
		return (builtin_env());
	else if (!strcmp(arr[0], "exit"))
		builtin_exit(arr[1]);
	else
	{
		xperror("minishell", ECNF, arr[0]);
		return (127);
	}
	clear_split(arr);
	return (0);
}

int	builtin_unset(const char *arg)
{
	printf("called unset builtin function with arg: |%s|\n", arg);
	return (0);
}

int	builtin_env(void)
{
	printf("called env builtin function\n");
	return (0);
}

void	builtin_exit(const char *status)
{
	int	ret;

	if (!status)
		ret = 0;
	else
		ret = ft_atoi(status);
	g_main.at_exit(NULL);
	exit(ret);
}

size_t	putsfd(int fd, const char *str)
{
	size_t	size;

	size = ft_strlen(str);
	write(fd, str, size);
	return (size);
}

void clear_split(char **array)
{
	while (*array)
	{
		free(*array);
		++array;
	}
	free(array);
}

void xperror(const char *parent, int errorcode, const char *arg)
{
	putsfd(2, parent);
	putsfd(2, ": ");
	putsfd(2, xstrerror(errorcode));
	if (arg)
	{
		putsfd(2, ": ");
		putsfd(2, arg);
	}
	putsfd(2, "\n");
}

const char *xstrerror(int errorcode)
{
	if (errorcode == ECNF)
		return ("command not found");
	else if (errorcode == ETMA)
		return ("too many arguments");
	return strerror(errorcode);
}

const char *xgetenv(const char *env)
{
	if (!env)
		return ("");
	return (getenv(env));
}
