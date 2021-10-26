# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kostya <kostya@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/08 23:21:10 by kostya            #+#    #+#              #
#    Updated: 2021/10/26 23:17:24 by kostya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	clang
NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror -Wno-error=deprecated -Wno-error=missing-exception-spec
COPTIONS	=	-O0
RM			=	rm -f
LIB_DIR		=	-L.
LIBRARY		=	-lreadline -lft
LIBFT_DIR	=	libft
INCLUDE_DIR	=	include
OBJS_DIR	=	objects
# ------------------------------------------------------------------------------
SRCS		=	\
				builtin_cd		\
				builtin_echo	\
				builtin_env		\
				builtin_execve	\
				builtin_exit	\
				builtin_export	\
				builtin_heredoc	\
				builtin_pwd		\
				builtin_unset	\
				enviroment		\
				error			\
				ft_atoi_s		\
				handler			\
				memory			\
				minishell		\
				signal			\
				split_smart		\
				stack1			\
				stack			\
				complex_parser	\
				dollar
# ------------------------------------------------------------------------------
HDRS		=	\
				enviroment		\
				global 			\
				memory			\
				minishell		\
				error			\
				colors			\
				parser
# ------------------------------------------------------------------------------
OBJS		=	$(addprefix ${OBJS_DIR}/,${SRCS:=.o})
DEPS		=	$(addprefix ${INCLUDE_DIR}/,${HDRS:=.h})
# LIBFT		=	${LIBFT_DIR}/libft.a
LIBFT		=
# ------------------------------------------------------------------------------
all:
	$(MAKE)		${NAME} -j

# ------------------------------------------------------------------------------
${OBJS_DIR}/%.o: %.c Makefile
	${CC}		${CFLAGS}  ${COPTIONS} -c -o $@ $<

# ------------------------------------------------------------------------------
$(NAME):		${OBJS_DIR} libft ${OBJS}
	${CC}		-o ${NAME} ${CFLAGS} ${COPTIONS} ${OBJS} ${LIB_DIR} ${LIBRARY} ${LIBFT}

# ------------------------------------------------------------------------------
clean:
	${MAKE}		-C ${LIBFT_DIR} clean
	${RM}		${OBJS}

# ------------------------------------------------------------------------------
fclean:			clean
	${MAKE}		-C ${LIBFT_DIR} fclean
	${RM}		${NAME}
	${RM}		libft.a

# ------------------------------------------------------------------------------
libft:
	${MAKE}		-C ${LIBFT_DIR}
	ln			-sf ../${LIBFT_DIR}/libft.h ${INCLUDE_DIR}/libft.h
	cp			${LIBFT_DIR}/libft.a .

# ------------------------------------------------------------------------------
${OBJS_DIR}:
	mkdir -p	${OBJS_DIR}

# ------------------------------------------------------------------------------
re:			fclean all

# ------------------------------------------------------------------------------
pvs:
	pvs-studio-analyzer trace -- make
	pvs-studio-analyzer analyze --disableLicenseExpirationCheck --compiler gcc -l/home/kostya/.config/PVS-Studio/PVS-Studio.lic -o /media/kostya/Data/CLion/Minishell/project.log -j2
	plog-converter -a GA:1,2 -t tasklist -o /media/kostya/Data/CLion/Minishell/project.tasks /media/kostya/Data/CLion/Minishell/project.log

# ------------------------------------------------------------------------------
.PHONY:			all clean fclean re pvs libft ${OBJS_DIR}
