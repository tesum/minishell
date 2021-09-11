NAME		= libft.a

SRC =		ft_atoi.c		ft_isalpha.c		ft_itoa.c\
			ft_memcpy.c		ft_putendl_fd.c		ft_strdup.c\
			ft_strmapi.c	ft_tolower.c		ft_bzero.c\
			ft_isascii.c	ft_memccpy.c		ft_memmove.c\
			ft_putnbr_fd.c	ft_strlcat.c		ft_strncmp.c\
			ft_toupper.c	ft_calloc.c			ft_isdigit.c\
			ft_memchr.c		ft_memset.c			ft_putstr_fd.c\
			ft_strlcpy.c	ft_strnstr.c		ft_isalnum.c\
			ft_isprint.c	ft_memcmp.c			ft_putchar_fd.c\
			ft_strchr.c		ft_strlen.c			ft_strrchr.c\
			ft_substr.c		ft_strjoin.c		ft_split.c\
			ft_strtrim.c	ft_atof.c			ft_isspace.c\
			ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c\
			ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c\
			ft_lstclear.c	ft_lstiter.c		ft_lstmap.c\
			ft_printf/ft_printf.c		ft_printf/parsing.c			ft_printf/proc_char.c\
			ft_printf/proc_hex.c		ft_printf/proc_int.c		ft_printf/proc_percent.c\
			ft_printf/proc_pointer.c	ft_printf/proc_string.c		ft_printf/proc_uint.c\
			ft_printf/ft_utils.c		ft_printf/print.c			gnl/get_next_line.c

OBJ_DIR		= object/
OBJ			= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
D_FILES		= $(wildcard $(OBJ_DIR)*.d)

CC			= gcc
CFLAGS		= -g -Wall -Wextra -Werror -I .

# COLORS

BLACK					=	\033[0;30m
RED						=	\033[0;31m
GREEN					=	\033[0;32m
YELLOW					=	\033[0;33m
BLUE					=	\033[0;34m
MAGENTA					=	\033[0;35m
CYAN					=	\033[0;36m
RESET					=	\033[0m

# 

.PHONY : 	all sub_directory clean fclean re bonus

all : sub_directory $(NAME)

sub_directory :
	@mkdir -p $(OBJ_DIR)/ft_printf
	@mkdir -p $(OBJ_DIR)/gnl

$(OBJ_DIR)%.o : %.c
	@$(CC) -c -MMD $(CFLAGS) $< -o $@
	@echo "$(GREEN)+$(RESET)\c"

$(NAME) : $(OBJ)
	@ar rcs $(NAME) $?
	@echo "$(GREEN)+$(RESET)\c"

bonus : all

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -rf $(NAME)

re : fclean all
