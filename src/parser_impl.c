/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_impl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:39:52 by kostya            #+#    #+#             */
/*   Updated: 2021/10/31 21:07:56 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/minishell.h"
#include "../inc/error.h"

static void	_implement_heredoc_extension(int _pipes_in_out[2],
				char *heredoc_str) __attribute__((noreturn)) __attribute__((
					__nothrow__));

char	*__restrict	*implement_redirect(char *__restrict *__restrict ptr)
{
	const mode_t	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int				error;
	char			*fname;

	error = 0;
	fname = ptr[1];
	if (*ptr == OUT_WRITE_PTR || *ptr == OUT_APPEND_PTR)
	{
		close(STDOUT);
		if (*ptr == OUT_WRITE_PTR)
			error = open(fname, O_CREAT | O_RDWR | O_TRUNC, mode);
		else
			error = open(fname, O_CREAT | O_RDWR | O_APPEND, mode);
	}
	else if (*ptr == INPUT_PTR || *ptr == HEREDOC_PTR)
	{
		close(STDIN);
		if (*ptr == INPUT_PTR)
			error = open(fname, O_RDONLY);
		else
			error = implement_heredoc(fname);
	}
	if (error == -1)
		return ((char **)(size_t)ft_perror("open", errno, ptr[1]));
	return (ptr + 2);
}

int	implement_heredoc(const char *__restrict end)
{
	char	*heredoc_str;
	int		_pipes_in_out[2];
	int		_frk;
	int		_backup_x2_in;

	_backup_x2_in = dup(backup_fd_in_out(NULL, 0));
	if (dup2(_backup_x2_in, STDIN) == -1)
		return (ft_perror("dup2", errno, NULL) - 1);
	heredoc_str = builtin_heredoc(end);
	close(STDIN);
	if (pipe(_pipes_in_out))
		return (ft_perror("pipe", errno, NULL) - 1);
	_frk = fork();
	if (_frk == -1)
		return (ft_perror("fork", errno, NULL) - 1);
	if (!_frk)
		_implement_heredoc_extension(_pipes_in_out, heredoc_str);
	else
	{
		close(_pipes_in_out[1]);
		return (_pipes_in_out[0]);
	}
	return (0);
}

static void	_implement_heredoc_extension(int _pipes_in_out[2],
				char *heredoc_str)
{
	close(_pipes_in_out[0]);
	putsfd(_pipes_in_out[1], heredoc_str);
	free(heredoc_str);
	close(_pipes_in_out[1]);
	exit(0);
}
