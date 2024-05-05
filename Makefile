# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 09:21:55 by srachidi          #+#    #+#              #
#    Updated: 2024/05/05 19:12:26 by aaghla           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
# FLAGS = -g -fsanitize=address -Wall -Werror -Wextra
FLAGS =  #-Wall -Werror -Wextra
RM = rm -rf
LIB = -lreadline
# ---------------------
READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include
# ---------------------
O_DR = objs/

SRC := 	main/main.c \
		main/grbg_cllctor.c \
		env/env_tools1.c \
		env/env_tools2.c \
		env/env_tools3.c \
		env/fcts_tools1.c \
		env/fcts_tools2.c \
		env/fcts_tools3.c \
		main/sh_tools/sh_tools1.c \
		execution/built_ins/blt_in_env.c \
		execution/built_ins/blt_in_pwd.c \
		parsing/ft_parser.c					\
		parsing/my_split.c					\
		parsing/my_split_tools.c			\
		parsing/tools.c						\
		parsing/ft_strtrim.c				\
		parsing/ft_expand.c					\
		parsing/handle_quotes.c				\
		parsing/histr_tools.c				\
		parsing/parse_input.c				\
		parsing/ft_token_tools.c			\
		parsing/here_doc.c			\
		parsing/get_next_line/get_next_line.c		\
		parsing/get_next_line/get_next_line_utils.c	\


CLR_RMV		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[0;32m
PURPLE		:= \033[35m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m

OBJ = $(addprefix $(O_DR),$(SRC:.c=.o))

$(NAME): $(OBJ)
	@echo "$(BLUE)░▒▓██████████████▓▒░░▒▓█▓▒░▒▓███████▓▒░░▒▓█▓▒░░▒▓███████▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓█▓▒░      ░▒▓█▓▒░        "
	@echo "░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        "
	@echo "░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        "
	@echo "░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓████████▓▒░▒▓██████▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░        "
	@echo "░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        "
	@echo "░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        "
	@echo "░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓████████▓▒░▒▓████████▓▒░ "
	@echo "                                                                                                                ${CLR_RMV}"
	@echo "$(PURPLE)Compilation ${CLR_RMV} of $(BLUE)$(NAME) ${CLR_RMV}..."
	@$(CC) $(FLAGS) $(OBJ) -o $@ -L $(READLINE_L) $(LIB)
	@echo "$(GREEN)$(NAME) created Successfully${CLR_RMV} ✔️"

$(O_DR)%.o: %.c main/minishell.h execution/execution.h parsing/parsing.h
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -I $(READLINE_I) -c $< -o $@

all: $(NAME)

clean:
	@$(RM) $(O_DR)
	@echo "$(RED)Deleting $(BLUE)$(NAME) $(CLR_RMV)object files ✔️"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Deleting $(BLUE)$(NAME) $(CLR_RMV)binary ✔️"

re: fclean all

.PHONY: all clean fclean re