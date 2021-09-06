
CC		=	gcc
RM		=	rm -rf
NAME	=	minishell
CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	builtin_cd.c \
			builtin_echo.c \
			builtin_export.c \
			enviroment.c \
			ft_split.c \
			memory.c \
			minishell.c \
			pwd.c

HDRS	=	enviroment.h \
			global.h \
			memory.h \
			minishell.h
		
OBJS	=	${SRCS:=.o}
LIBRARY	=	-lreadline

.c.o:
	${CC}	${CFLAGS} ${COPTIONS} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS}
	${CC}	-o ${NAME} ${CFLAGS} ${COPTIONS} ${OBJS} ${LIBRARY}

clean:
	${RM}	OBJS

fclean:		${CLEAN}
	${RM} 	${NAME}

pvs:
	pvs-studio-analyzer trace -- make
	pvs-studio-analyzer analyze --disableLicenseExpirationCheck --compiler gcc -l/home/kostya/.config/PVS-Studio/PVS-Studio.lic -o /media/kostya/Data/CLion/Minishell/project.log -j2
	plog-converter -a GA:1,2 -t tasklist -o /media/kostya/Data/CLion/Minishell/project.tasks /media/kostya/Data/CLion/Minishell/project.log
