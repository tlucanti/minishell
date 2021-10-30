cmake_minimum_required(VERSION 3.20)
project(Minishell C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(Minishell
        src/ancient_shards.c
        src/builtin_cd.c
        src/builtin_echo.c
        src/builtin_env.c
        src/builtin_execve.c
        src/builtin_exit.c
        src/builtin_export.c
        src/builtin_heredoc.c
        src/builtin_pwd.c
        src/builtin_unset.c
        src/complex_parser.c
        src/dollar.c
        src/enviroment.c
        src/error.c
        src/ft_atoi_s.c
        src/handler.c
        src/memory.c
        src/minishell.c
        src/parser_impl.c
        src/signal.c
        src/simple_parser.c
        src/split_smart.c
        src/split_smart1.c
        src/stack.c
        src/stack1.c

        inc/color.h
        inc/enviroment.h
        inc/error.h
        inc/handler.h
        inc/libft.h
        inc/memory.h
        inc/minishell.h
        inc/parser.h
)

target_link_libraries(Minishell
        readline
        /media/kostya/Data/CLion/Minishell/libft.a)