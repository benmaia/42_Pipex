
# Colors #
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RED		=	\033[0;31m
RESET		=   \033[0m

NAME = pipex

LIBFT_DIR	=	libft
SRC		=	srcs/mandatory/main.c \
			srcs/mandatory/command.c \
			srcs/mandatory/parsing.c \
			srcs/mandatory/free.c

B_SRC		=	srcs/bonus/main_bonus.c \
			srcs/bonus/command_bonus.c \
			srcs/bonus/free_bonus.c \
			srcs/bonus/parsing_bonus.c

OBJ		=	$(SRC:srcs/mandatory/%.c=$(OBJ_DIR)/%.o)
B_OBJ		=	$(B_SRC:srcs/bonus/%.c=$(B_OBJ_DIR)/%.o)
INC_DIR		=	inc
BUILD_DIR	=	./build
BIN_DIR		=	$(BUILD_DIR)/bin
OBJ_DIR		=	$(BUILD_DIR)/objects
B_OBJ_DIR	=	$(BUILD_DIR)/b_objects
BIN		=	$(BIN_DIR)/$(NAME)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -I$(INC_DIR) -I$(LIBFT_DIR)

(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OBJ_DIR) $(B_OBJ_DIR) $(BIN_DIR)

all: $(NAME)

$(NAME): $(BIN)

$(BIN):	$(OBJ) | $(BIN_DIR)
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -o $(@) $(^) -L$(LIBFT_DIR) -lft
	@echo "$(GREEN)[ Pipex is ready to use ! ] $(RESET)"

$(OBJ_DIR)/%.o:	srcs/mandatory/%.c | $(BUILD_DIR)
	@#echo "$(YELLOW)[       Compiling pipex ...      ]$(RESET)"	
	@echo "$(GREEN)[ Creating ${@F} ]$(RESET)"
	@$(CC) $(CFLAGS) -c $(^) -o $(@)

.SILENT = $(OBJ)
.SILENT = $(B_OBJ)

#$(BUILD_DIR):
#		@mkdir -p $(BUILD_DIR)
#		@mkdir -p $(OBJ_DIR) $(B_OBJ_DIR) $(BIN_DIR)

bonus: $(B_OBJ) | $(BIN_DIR)
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -o $(NAME) $(^) -L$(LIBFT_DIR) -lft
	@mv pipex build/bin
	@echo "$(GREEN)[ Pipex Bonus is ready to use ! ] $(RESET)"

$(B_OBJ_DIR)/%.o:	srcs/bonus/%.c | $(BUILD_DIR)
	@#echo "$(YELLOW)[       Compiling pipex ...      ]$(RESET)"	
	@echo "$(GREEN)[ Creating ${@F} ]$(RESET)"
	@$(CC) $(CFLAGS) -c $(^) -o $(@)

clean:
	@make clean -s -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(B_OBJ_DIR)
	@#echo "$(YELLOW)[    Objects have been removed!  ]$(RESET)"

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@rm -rf build
	@echo "$(RED)[ Pipex has been removed ! ]$(RESET)"

re: fclean all

mandatory: all
	@./build/bin/pipex main.txt "/bin/ls" "wc" test.txt

bonus1: bonus
	@./build/bin/pipex main.txt "ls -l" "grep .txt" "grep test" test.txt

bonus2: bonus
	@./build/bin/pipex main.txt "ls -l" "grep .txt" "grep test" "wc -l" test.txt

bonus3: bonus
	@./build/bin/pipex here_doc 42 "cat" "cat" test.txt

bonus4: bonus
	@./build/bin/pipex here_doc 42 "ls -l" "grep .txt" "grep main" test.txt

bonus5: bonus
	@./build/bin/pipex here_doc Oi "ls -l" "cat" "grep .txt" test2.txt

.PHONY: all clean fclean re bonus
