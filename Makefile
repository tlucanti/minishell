# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kostya <kostya@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/08 23:21:10 by kostya            #+#    #+#              #
#    Updated: 2021/09/09 14:45:12 by kostya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
RM		=	rm -rf
NAME	=	minishell
CFLAGS	=	-Wall -Wextra -Werror -D__USE_GNU

SRCS	=	builtin_cd.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_export.c \
			builtin_pwd.c \
			builtin_unset.c \
			enviroment.c \
			ft_split.c \
			memory.c \
			minishell.c \
			ft_atoi_s.c \
			builtin_exit.c \
			builtin_execve.c


HDRS	=	enviroment.h \
			global.h \
			memory.h \
			minishell.h
		
OBJS	=	${SRCS:.c=.o}
LIBRARY	=	-lreadline

.c.o:
	${CC}	${CFLAGS} ${COPTIONS} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS}
	${CC}	-o ${NAME} ${CFLAGS} ${COPTIONS} ${OBJS} ${LIBRARY}

clean:
	${RM}	${OBJS}

fclean:		clean
	${RM} 	${NAME}

re:			fclean all

pvs:
	pvs-studio-analyzer trace -- make
	pvs-studio-analyzer analyze --disableLicenseExpirationCheck --compiler gcc -l/home/kostya/.config/PVS-Studio/PVS-Studio.lic -o /media/kostya/Data/CLion/Minishell/project.log -j2
	plog-converter -a GA:1,2 -t tasklist -o /media/kostya/Data/CLion/Minishell/project.tasks /media/kostya/Data/CLion/Minishell/project.log
