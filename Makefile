# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kostya <kostya@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/08 23:21:10 by kostya            #+#    #+#              #
#    Updated: 2021/09/18 00:03:33 by kostya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
NAME		=	minishell
CFLAGS		=	-Wall -Wextra -g3
COPTIONS	=	-O1
DEPS		=	fract-ol.h
RM			=	rm -f
LIBRARY		=	-lreadline
# ------------------------------------------------------------------------------
SRCS		=	\
				builtin_cd \
				builtin_echo \
				builtin_env \
				builtin_export \
				builtin_heredoc \
				builtin_pwd \
				builtin_unset \
				enviroment \
				ft_split \
				memory \
				minishell \
				ft_atoi_s \
				builtin_exit \
				builtin_execve \
				error \
				signal \
				split_smart
# ------------------------------------------------------------------------------
HDRS		=	\
				enviroment.h \
				global.h \
				memory.h \
				minishell.h \
				error.h \
				colors.h
# ------------------------------------------------------------------------------
OBJS_DIR	=	.objects
OBJS		=	${SRCS:=.o}
LIBRARY		=	-lreadline

%.o: %.c
	${CC}		${CFLAGS}  ${COPTIONS} -c -o $@ $<

$(NAME):		${OBJS}
# 	${MAKE}		-C libft
	${CC}		-o ${NAME} ${CFLAGS} ${COPTIONS} ${OBJS} ${LIBRARY}

# ------------------------------------------------------------------------------
all:			${NAME}

# ------------------------------------------------------------------------------
clean:
# 	${MAKE}		-C libft clean
	${RM}		${OBJS}

# ------------------------------------------------------------------------------
fclean:			clean
# 	${MAKE}		fclean -C libft
	${RM}		${NAME}

# ------------------------------------------------------------------------------
re:			fclean all

# ------------------------------------------------------------------------------
pvs:
	pvs-studio-analyzer trace -- make
	pvs-studio-analyzer analyze --disableLicenseExpirationCheck --compiler gcc -l/home/kostya/.config/PVS-Studio/PVS-Studio.lic -o /media/kostya/Data/CLion/Minishell/project.log -j2
	plog-converter -a GA:1,2 -t tasklist -o /media/kostya/Data/CLion/Minishell/project.tasks /media/kostya/Data/CLion/Minishell/project.log

# ------------------------------------------------------------------------------
.PHONY:			all clean fclean re pvs
