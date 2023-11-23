cmake_minimum_required(VERSION 3.10)
project(minishell)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -g")

# Include and compile libft
file(GLOB_RECURSE LIBFT_SOURCES "libft/*/*.c")
add_library(libft STATIC ${LIBFT_SOURCES})
target_include_directories(libft PUBLIC libft/include)

# Include minishell header
include_directories(include)

# Manually specify Readline paths
include_directories(/usr/include/readline) # Update this path
link_directories(/usr/lib) # Update this path


# Compile minishell
file(GLOB_RECURSE MINISHELL_SOURCES
        "src/*.c"
        "src/*/*.c"
)
add_executable(minishell ${MINISHELL_SOURCES})

# Link libft to minishell
target_link_libraries(minishell libft readline)