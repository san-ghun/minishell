# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/15 15:37:09 by sanghupa          #+#    #+#              #
#    Updated: 2023/08/03 01:00:35 by sanghupa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Alias

CC			= cc
CFLAGS		= -Wall -Werror -Wextra

RL_LINK		= -lreadline

RM			= rm -f

INC_DIR		= ./include

LIBFT		= libft.a
LIBFT_DIR	= ./libft
LIBFT_I_DIR	= $(LIBFT_DIR)/include
LIBFT_PATH	= $(LIBFT_DIR)/$(LIBFT)

SRC_DIR		= ./src

NAME 		= minishell
SRC_NAME 	= $(shell find ./src -iname "*.c")

OBJ_NAME 	= $(SRC_NAME:.c=.o)

NAME_B 		= minishell_bonus
SRC_NAME_B 	= $(SRC_DIR)/$(NAME_B).c \
				$(SRC_DIR)/$(NAME_B)_util.c \

OBJ_NAME_B 	= $(SRC_NAME_B:.c=.o)


# Main Command

all: $(NAME)

bonus: $(NAME_B)

clean:
		@make clean -C $(LIBFT_DIR)
		@$(RM) $(OBJ_NAME)
		@$(RM) $(OBJ_NAME_B)

fclean:	clean
		@make fclean -C $(LIBFT_DIR)
		@$(RM) $(LIBFT)
		@$(RM) $(OBJ_NAME)
		@$(RM) $(OBJ_NAME_B)
		@$(RM) $(NAME)

re: fclean all

re_bonus: fclean bonus

dev: $(LIBFT)
# 			For 42
#			$(CC) -fsanitize=address -g -o $(NAME) $(SRC_NAME) $^ -I $(INC_DIR) -I $(LIBFT_I_DIR) $(RL_LINK)
# 			For MacOS
			$(CC) -fsanitize=address -g -o $(NAME) $(SRC_NAME) $^ -I $(INC_DIR) -I $(LIBFT_I_DIR) $(RL_LINK) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include


# Sub Command

%.o: %.c
			@$(CC) $(CFLAGS) -c -o $@ $< -I $(INC_DIR) -I $(LIBFT_I_DIR)

$(LIBFT):
			@make -C $(LIBFT_DIR)
			@mv $(LIBFT_PATH) ./

$(NAME):	$(OBJ_NAME) $(LIBFT)
#			@$(CC) $(CFLAGS) -o $@ $^ -I $(INC_DIR) -I $(LIBFT_I_DIR) $(RL_LINK)
			@$(CC) $(CFLAGS) -fsanitize=address -g -o $@ $^ -I $(INC_DIR) -I $(LIBFT_I_DIR) $(RL_LINK) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include

$(NAME_B):	$(OBJ_NAME_B) $(LIBFT)
			@$(CC) $(CFLAGS) -o $@ $^ -I $(INC_DIR) -I $(LIBFT_I_DIR)

# Test Code 

TEST 		=	test.c

TMP_LIB_A 	= $(shell find ./src/deque -iname "*.c")
TMP_LIB_B	= $(shell find ./src/t_sent -iname "*.c")
TMP_LIB_C	= $(shell find ./src/util -iname "*.c")
TMP_LIB_D	= $(shell find ./src/t_dlst -iname "*.c")
TMP_LIB_E	= $(shell find ./src/built-in -iname "*.c")

TMP 		= $(SRC_DIR)/pipex_util.c \
				$(SRC_DIR)/pipex.c \
				$(SRC_DIR)/minishell_util.c \
				$(TMP_LIB_A) \
				$(TMP_LIB_B) \
				$(TMP_LIB_C) \
				$(TMP_LIB_D) \
				$(TMP_LIB_E)
#				$(SRC_DIR)/minishell.c \

test: $(LIBFT)
			$(CC) $(TEST) -o $(TEST:.c=.out) $(TMP) $^ -I $(INC_DIR) -I $(LIBFT_I_DIR) $(RL_LINK)
			# -fsanitize=address -g
tclean: 
			make fclean -C $(LIBFT_DIR)
			$(RM) $(LIBFT)
			$(RM) -f test.o test.out

party:
			@printf "\033c"
			@echo "\n\033[35m♪┏(・o･)┛♪"
			@sleep 1
			@printf "\033c"
			@echo "\033[1;33m♪┗(・o･)┓♪"				@sleep 1
			@printf "\033c"
			@echo "\n\033[36m♪┏(・o･)┛♪"				@sleep 1
			@printf "\033c"
			@echo "\033[34m♪┗(・o･)┓♪\n"

# Phony target
.PHONY: all clean fclean re bonus re_bonus party