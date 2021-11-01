# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kostya <kostya@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/08 23:21:10 by kostya            #+#    #+#              #
#    Updated: 2021/11/01 20:10:15 by kostya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------ compiler options ------------------------------
NAME		=	minishell
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror
COPTIONS	=	-O3 -ffast-math
# ------------------------------- linker options -------------------------------
LIBRARY		=	-L. -lreadline -lft -lgnl
OBJS_DIR	=	obj
INCLUDE_DIR	=	inc
SCRS_DIR	=	src
GNL			=	gnl
LIBFT		=	libft
# ------------------------------- project sorces -------------------------------
SRCS		=	\
				ancient_shards	\
				builtin_cd		\
				builtin_echo	\
				builtin_env		\
				builtin_execve	\
				builtin_exit	\
				builtin_export	\
				builtin_heredoc	\
				builtin_pwd		\
				builtin_unset	\
				complex_parser	\
				dollar			\
				enviroment		\
				error			\
				ft_atoi_s		\
				handler			\
				memory			\
				minishell		\
				parser_impl		\
				rl_bind_key		\
				signal			\
				simple_parser	\
				split_smart1	\
				split_smart		\
				stack1			\
				stack			\
				del_quotes
# ------------------------------------------------------------------------------
HDRS		=	\
				color			\
				enviroment		\
				error			\
				handler			\
				libft			\
				memory			\
				minishell		\
				parser

# ======================= UNCHANGEABLE PART OF MAKEFILE ========================
# ------------------------------------------------------------------------------
RM			=	rm -f
OBJS		=	$(addprefix ${OBJS_DIR}/,${SRCS:=.o})
DEPS		=	$(addprefix ${INCLUDE_DIR}/,${HDRS:=.h})
INCLUDE		=	-I ${INCLUDE_DIR}

# ------------------------------------------------------------------------------
all: libft_ libgnl
	@$(MAKE)	$(NAME) -j

# ------------------------------------------------------------------------------
install: libft_ libgnl
	mkdir		-p ${OBJS_DIR}
	ln			-sf ../${GNL}/get_next_line.h ${INCLUDE_DIR}/get_next_line.h
	ln			-sf ${GNL}/libgnl.a libgnl.a
	ln			-sf ../${LIBFT}/libft.h ${INCLUDE_DIR}/libft.h
	ln			-sf ${LIBFT}/libft.a libft.a

# ------------------------------------------------------------------------------
${OBJS_DIR}/%.o: ${SCRS_DIR}/%.c ${DEPS} Makefile
	${CC}		${CFLAGS} ${COPTIONS} -c -o $@ $< ${INCLUDE}

# ------------------------------------------------------------------------------
$(NAME):		${OBJS} ${DEPS} libft.a libgnl.a
	${CC}		-o ${NAME} ${CFLAGS} ${COPTIONS} ${OBJS} ${LIBRARY}

# ------------------------------------------------------------------------------
libft_:
	@$(MAKE)	-C ${LIBFT}

# ------------------------------------------------------------------------------
libgnl:
	@$(MAKE)	-C ${GNL}

# ------------------------------------------------------------------------------
clean:
	${RM}		${OBJS}
	$(MAKE)		-C ${LIBFT} clean
	$(MAKE)		-C ${GNL}

# ------------------------------------------------------------------------------
fclean:			clean
	${RM}		${NAME}
	${RM}		libft.a
	${RM}		libgnl.a
	$(MAKE)		-C ${LIBFT} fclean
	$(MAKE)		-C ${GNL} fclean

# ------------------------------------------------------------------------------
re:				fclean install all

# ------------------------------------------------------------------------------
.PHONY:			all clean fclean re
