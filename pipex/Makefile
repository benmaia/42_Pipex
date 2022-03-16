NAME = pipex

LIBFT_DIR = ./libft

SRC = srcs/main.c
OBJ = $(SRC:%.c=%.o)
INC_DIR = inc

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(NAME)

.SILENT = $(OBJ)

%.o: %.c
	@printf "\033[33m[CREATING ${@F}]\033[0m\n"
	@$(CC) $(CFLAGS) -c $(^) -o $(@)
	
$(NAME): $(OBJ)
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -o $(@) $(^) -L $(LIBFT_DIR) -lft
	@# mkdir -p ./build/objs
	@# mv $(OBJ) build/objs
	@mkdir -p build/bin
	@mv $(NAME) build/bin

clean:
	@make clean -s -C $(LIBFT_DIR)
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@rm -rf build

re: fclean all

.PHONY: all clean fclean re
