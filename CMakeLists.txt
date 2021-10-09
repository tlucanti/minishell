cmake_minimum_required(VERSION 3.20)
project(Minishell C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(Minishell
    builtin_cd.c
    builtin_echo.c
    builtin_env.c
    builtin_execve.c
    builtin_exit.c
    builtin_export.c
    builtin_heredoc.c
    builtin_pwd.c
    builtin_unset.c
    enviroment.c
    error.c
    ft_atoi_s.c
    ft_split.c
    handler.c
    memory.c
    minishell.c
    signal.c
    split_smart.c
    stack1.c
    stack.c

    include/color.h
    include/enviroment.h
    include/error.h
    include/handler.h
    include/libft.h
    include/memory.h
    include/minishell.h
)

target_link_libraries(Minishell
        readline
        /media/kostya/Data/CLion/Minishell/libft/libft.a)