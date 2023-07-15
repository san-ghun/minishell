# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 22:48:59 by sanghupa          #+#    #+#              #
#    Updated: 2023/07/15 16:35:38 by sanghupa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc

CFLAGS		= -Wall -Werror -Wextra

RM			= rm

AR			= ar -rc
# -r : replace or add the specified files to the archive.
# -c : create archive without message. `ar: creating archive libft.a`
# -v : provide verbose output. `a` if the file is added and \
		`r` if the file replace a file already in the archive.

NAME		= libft.a

INCLUDE		= ./include

SRC			= ./isto/ft_isalnum.c ./isto/ft_isalpha.c \
				./isto/ft_isdigit.c ./isto/ft_isascii.c \
				./isto/ft_isprint.c ./isto/ft_toupper.c \
				./isto/ft_tolower.c \
				./str_lib/ft_strlen.c ./str_lib/ft_strlcpy.c \
				./str_lib/ft_strlcat.c ./str_lib/ft_strchr.c \
				./str_lib/ft_strrchr.c ./str_lib/ft_strncmp.c \
				./str_lib/ft_strnstr.c ./str_lib/ft_atoi.c \
				./str_lib/ft_strdup.c \
				./str_nonlib/ft_substr.c ./str_nonlib/ft_strjoin.c \
				./str_nonlib/ft_strtrim.c ./str_nonlib/ft_split.c \
				./str_nonlib/ft_itoa.c ./str_nonlib/ft_strmapi.c \
				./str_nonlib/ft_striteri.c \
				./mem/ft_memset.c ./mem/ft_bzero.c \
				./mem/ft_memcpy.c ./mem/ft_memmove.c \
				./mem/ft_memchr.c ./mem/ft_memcmp.c \
				./mem/ft_calloc.c \
				./put_fd/ft_putchar_fd.c ./put_fd/ft_putstr_fd.c \
				./put_fd/ft_putendl_fd.c ./put_fd/ft_putnbr_fd.c \
				./llst/ft_lstnew.c ./llst/ft_lstadd_front.c \
				./llst/ft_lstsize.c ./llst/ft_lstlast.c \
				./llst/ft_lstadd_back.c ./llst/ft_lstdelone.c \
				./llst/ft_lstclear.c ./llst/ft_lstiter.c \
				./llst/ft_lstmap.c \
				./gnl/get_next_line.c ./gnl/get_next_line_utils.c \
				./ft_printf/ft_printf_cs.c ./ft_printf/ft_printf_diu.c \
				./ft_printf/ft_printf_p.c ./ft_printf/ft_printf_hex.c \
				./ft_printf/ft_printf.c

OBJ 		= $(SRC:.c=.o)


all: $(NAME)

%.o: %.c
		@$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

$(NAME): $(OBJ)
		@$(AR) $@ $^

clean:
		@$(RM) -f $(OBJ)

fclean: clean
		@$(RM) -f $(NAME)

re: fclean all

# Library Test Code

TEST = test.c

test: $(NAME) $(TEST)
		$(CC) $(TEST) -o $(TEST:.c=.out) $(NAME) -I $(INCLUDE) -g
		./$(TEST:.c=.out)
		rm -f $(TEST:.c=.out)
		rm -rf $(TEST:.c=.out.dSYM)

.PHONY: all clean fclean re test