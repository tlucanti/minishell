cmake_minimum_required(VERSION 3.20)
project(Minishell C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
link_libraries(readline)
add_executable(Minishell
        global.h

        builtin_cd.c
        builtin_echo.c
        builtin_export.c

        enviroment.c
        enviroment.h

        memory.c
        memory.h

        minishell.c
        minishell.h

        ft_split.c
        pwd.c
)

