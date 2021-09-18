cmake_minimum_required(VERSION 3.20)
project(Minishell C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
link_libraries(readline)
add_executable(Minishell
        builtin_echo.c
        builtin_cd.c
        builtin_pwd.c
        builtin_export.c
        builtin_heredoc.c
        builtin_unset.c
        builtin_env.c
        builtin_exit.c
        builtin_execve.c

        enviroment.c
        enviroment.h

        memory.c
        memory.h

        error.c
        error.h

        signal.c
        signal.h

        minishell.c
        minishell.h

        ft_split.c
        ft_atoi_s.c
        split_smart.c
)

