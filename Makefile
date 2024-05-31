# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/26 14:32:42 by srachidi          #+#    #+#              #
#    Updated: 2024/05/31 11:02:43 by aaghla           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
FLAGS = -g -fsanitize=address -Wall -Werror -Wextra
FLAGS = #-Wall -Werror -Wextra
RM = rm -rf
LIB = -lreadline
# ---------------------
READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include
# ---------------------
O_DR = objs/

SRC := 	main/main.c \
		main/grbg_cllctor.c \
		env_tools/env_tools1.c \
		env_tools/env_tools2.c \
		env_tools/env_tools3.c \
		env_tools/env_tools4.c \
		env_tools/env_tools5.c \
		env_tools/fcts_tools1.c \
		env_tools/fcts_tools2.c \
		env_tools/fcts_tools3.c \
		env_tools/rdr_tools/rdr_tools1.c \
		env_tools/sh_tools/sh_tools1.c \
		parsing/ft_parser.c					\
		parsing/my_split.c					\
		parsing/tools.c						\
		parsing/ft_strtrim.c				\
		parsing/ft_expand.c					\
		parsing/parse_input.c				\
		parsing/ft_token_tools.c			\
		parsing/here_doc.c					\
		parsing/tokenization.c				\
		parsing/ft_rdr_tools.c				\
		parsing/ft_expand_tools.c			\
		parsing/ft_expand_tools2.c			\
		parsing/expand_tools3.c			\
		parsing/ft_itoa.c					\
		parsing/ft_expand_heredoc.c			\
		parsing/t_var_tools.c				\
		execution/executor.c \
		execution/executor1.c \
		execution/executor2.c \
		execution/built_ins/blt_in_env.c \
		execution/built_ins/blt_in_pwd.c \
		execution/built_ins/blt_in_echo.c \
		execution/built_ins/blt_in_echo1.c \
		execution/built_ins/blt_in_echo2.c \
		execution/built_ins/blt_in_cd.c \
		execution/built_ins/blt_in_exit.c \
		execution/built_ins/blt_in_exit1.c \
		execution/legacy_tools/leg_tools1.c \
		execution/legacy_tools/leg_tools2.c \
		execution/built_ins/blt_in_export.c \
		execution/built_ins/blt_in_export1.c \
		execution/built_ins/blt_in_unset.c \
		execution/pipelining/other_cmd.c \
		execution/pipelining/other_cmd1.c \
		execution/pipelining/pipe_tools1.c \
		execution/pipelining/pipe_tools2.c \
		execution/pipelining/pipe_tools3.c \
		execution/pipelining/pipeliner.c \
		execution/pipelining/pipeliner1.c \
		execution/pipelining/pipeliner2.c \
		execution/pipelining/pipeliner3.c \
		execution/pipelining/pipe_tools4.c \
		execution/pipelining/pipe_tools5.c \
		execution/pipelining/pipe_tools6.c \
		signals/signals.c \

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
	@$(CC) $(FLAGS) $(OBJ)  -o $@ -L $(READLINE_L) $(LIB)
	@echo "$(GREEN)$(NAME) created Successfully${CLR_RMV} ✔️"

$(O_DR)%.o: %.c main/minishell.h execution/execution.h parsing/parsing.h
	@mkdir -p $(@D)
	@$(CC) $(FLAGS)  -I $(READLINE_I) -c $< -o $@

all: $(NAME)

clean:
	@$(RM) $(O_DR)
	@echo "$(RED)Deleting $(BLUE)$(NAME) $(CLR_RMV)object files ✔️"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Deleting $(BLUE)$(NAME) $(CLR_RMV)binary ✔️"

re: fclean all

.PHONY: all clean fclean re