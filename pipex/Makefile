# Colors #
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
RESET       =   \033[0m

NAME = pipex

LIBFT_DIR = libft
SRC = srcs/main.c
OBJ = $(SRC:%.c=%.o)
INC_DIR = inc

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(NAME)

.SILENT = $(OBJ)

%.o: %.c 
	@echo "$(YELLOW)[       Compiling pipex ...      ]$(RESET)"	
	@echo "$(YELLOW)[         Creating ${@F}        ]$(RESET)"
	@$(CC) $(CFLAGS) -c $(^) -o $(@)

runlibft:
	@make -s -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -o $(@) $(^) -L $(LIBFT_DIR) -lft
	@# mkdir -p ./build/objs
	@# mv $(OBJ) build/objs
	@#mkdir -p build/bin
	@#mv $(NAME) build/bin
	@echo "$(GREEN)[     Pipex is ready to use!     ]$(RESET)"

clean:
	@make clean -s -C $(LIBFT_DIR)
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
