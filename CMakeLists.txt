cmake_minimum_required(VERSION 3.10)
project(minishell)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -g")

include_directories(include)
include_directories(include/include)

file(GLOB LIBFT_SOURCES
        "libft/src/*.c"
        "libft/src/*/*.c"
)

file(GLOB SOURCES
        "src/*.c"
        "src/*/*.c"
        ${LIBFT_SOURCES}
        )
add_executable(minishell ${SOURCES})