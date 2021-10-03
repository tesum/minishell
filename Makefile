# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: demilan <demilan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/10 22:20:54 by caugusta          #+#    #+#              #
#    Updated: 2021/10/03 20:29:08 by demilan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= minishell
LIBFT_NAME			= libft.a

CC					= gcc
CFLAGS				= -Wall -Wextra -Werror -MMD -g
INCFLAGS			= -I ./includes/ -I/Users/$(USER)/.brew/Cellar/readline/8.1/include

READLINEFLAGS		= -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -lreadline -ltermcap

SOURCE_DIR			= source/
SOURCE				=	main.c exec.c cmd_arr.c \
						parser/preparser.c parser/parser.c parser/parser_dollar.c parser/parser_pipe_redirect.c parser/post_modern_parser.c\
						cmd/pwd.c cmd/echo.c cmd/cd.c  cmd/exit.c cmd/export.c cmd/env.c cmd/unset.c \
						utils/array_utils.c utils/struct_command_utils.c utils/utils.c \
						utils/array_utils.c utils/struct_command_utils.c \
						env/init_env.c env/export_utils.c \
						pipex/pipes.c \
						
OBJ_DIR				= object/
OBJ_DIRS			= $(sort $(dir $(OBJ)))

LIBFT				= libft/$(LIBFT_NAME)
LIBFT_DIR			= libft/

OBJ					= $(addprefix $(OBJ_DIR), $(SOURCE:.c=.o))
D_FILES				= $(wildcard $(OBJ_DIR)%.d)

# COLORS

BLACK				=	\033[0;30m
RED					=	\033[0;31m
GREEN				=	\033[0;32m
YELLOW				=	\033[0;33m
BLUE				=	\033[0;34m
MAGENTA				=	\033[0;35m
CYAN				=	\033[0;36m
RESET				=	\033[0m

# 

.PHONY : all dir_bonus clean fclean re bonus run

all : $(OBJ_DIRS) $(LIBFT) $(NAME)
	@echo "\n$(GREEN)COMPLETE$(RESET)"
	@${MAKE} run

$(OBJ_DIRS):
	@mkdir -p $@

$(OBJ_DIR)%.o : $(SOURCE_DIR)%.c
	@$(CC) $(CFLAGS) -c -o $@ $^ $(INCFLAGS)
	@echo "$(GREEN)+$(RESET)\c"

$(NAME) : $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(READLINEFLAGS) -o $@ $^ $(INCFLAGS)
	@echo "$(GREEN)+$(RESET)\c"

$(LIBFT) :
	@$(MAKE) -C $(LIBFT_DIR)
	@cp $(LIBFT_DIR)/libft.h ./includes
	@echo "\n$(GREEN)LIBFT OK$(RESET)"

include $(D_FILES)

clean :
	@$(MAKE) clean -C $(LIBFT_DIR) --silent
	@rm -rf $(OBJ_DIR)
	@echo CLEAN COMPLETE

fclean : clean
	@$(MAKE) fclean -C $(LIBFT_DIR) --silent
	@rm -rf $(NAME)
	@rm -rf includes/libft.h
	@echo FCLEAN COMPLETE

re : fclean all

run :
	./${NAME}
