# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/15 15:37:09 by sanghupa          #+#    #+#              #
#    Updated: 2023/11/25 15:40:34 by sanghupa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Alias

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g

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
			$(CC) -g -o $(NAME) $(SRC_NAME) $^ -I $(INC_DIR) -I $(LIBFT_I_DIR) $(RL_LINK)
#			$(CC) -fsanitize=address -g -o $(NAME) $(SRC_NAME) $^ -I $(INC_DIR) -I $(LIBFT_I_DIR) $(RL_LINK)
# 			For MacOS
#			$(CC) -fsanitize=address -g -o $(NAME) $(SRC_NAME) $^ -I $(INC_DIR) -I $(LIBFT_I_DIR) $(RL_LINK) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include
#			For dorker exe
#			gcc -g -o $(NAME) $(SRC_NAME) $^ -Llibft -I $(INC_DIR) -I $(LIBFT_I_DIR) $(RL_LINK) -lft


# Sub Command

%.o: %.c
			@$(CC) $(CFLAGS) -c -o $@ $< -I $(INC_DIR) -I $(LIBFT_I_DIR)

$(LIBFT):
			@make -C $(LIBFT_DIR)
			@mv $(LIBFT_PATH) ./

$(NAME):	$(OBJ_NAME) $(LIBFT)
			@$(CC) $(CFLAGS) -o $@ $^ -I $(INC_DIR) -I $(LIBFT_I_DIR) $(RL_LINK)
#			@$(CC) $(CFLAGS) -fsanitize=address -g -o $@ $^ -I $(INC_DIR) -I $(LIBFT_I_DIR) $(RL_LINK) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include

$(NAME_B):	$(OBJ_NAME_B) $(LIBFT)
			@$(CC) $(CFLAGS) -o $@ $^ -I $(INC_DIR) -I $(LIBFT_I_DIR)

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
