
# Colors #
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
RESET       =   \033[0m

E		= @echo
S		= @sleep 
PF		= @printf
CP		= $(E) "$(YELLOW)⚜️ -------->> Compiling Pipex  <<--------- ⚜️ \n"
CL		= $(E) "$(YELLOW)⚜️ -------->> Compiling Libft  <<--------- ⚜️ \n"
BB		= $(E) "$(YELLOW)⚜️ --------------------------------------- ⚜️ \n"

NAME = pipex

LIBFT_DIR	=	libft
SRC			=	srcs/main.c
OBJ			=	$(SRC:srcs/%.c=$(OBJ_DIR)/%.o)
INC_DIR		=	inc
BUILD_DIR	=	./build
BIN_DIR		=	$(BUILD_DIR)/bin
OBJ_DIR		=	$(BUILD_DIR)/objects
BIN			:=	$(BIN_DIR)/$(NAME)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(BIN)

$(BIN):	$(OBJ) | $(BIN_DIR)
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -o $(@) $(^) -L$(LIBFT_DIR) -lft
#1- frame
	$(PF) "\033c\n"
	$(CP)
	@say -r 325 "compiling pipex"
	$(E) "\033[0;35m              ► Loading \n"
	$(BB)
	$(S) 0.5
	$(PF) "\033r"
#2- frame	
	$(PF) "\033c\n"
	$(CP)
	$(E) "\033[0;35m              ► Loading .\n"
	$(BB)
	$(S) 0.5
	$(PF) "\033r"
#3- frame 
	$(PF) "\033c\n"
	$(CP)
	$(E) "\033[0;35m              ► Loading ..\n"
	$(BB)
	$(S) 0.5
	$(PF) "\033r"
#4- frame
	$(PF) "\033c\n"
	$(CP)
	$(E) "\033[0;35m              ► Loading ...\n"
	$(BB)
	$(S) 0.7
	$(PF) "\033r"
#5- frame green
	$(PF) "\033c\n"
	$(E) "\033[2;32m⚜️ -------->> Compiling Pipex  <<--------- ⚜️ \n"
	$(E) "\033[1;;32m            ✅ Pipex Compiled!                \n"
	$(E) "\033[2;32m⚜️ <-----------------<>------------------> ⚜️ \n"
	@say -r 350 "compiling is done, have fun piping your mother"

$(OBJ_DIR)/%.o:	srcs/%.c | $(BUILD_DIR)
	@#echo "$(YELLOW)[       Compiling pipex ...      ]$(RESET)"	
	@#echo "$(GREEN)[         Creating ${@F}        ]$(RESET)"
	@$(CC) $(CFLAGS) -c $(^) -o $(@)

.SILENT = $(OBJ)

$(BUILD_DIR):
		@mkdir -p $(BUILD_DIR)
		@mkdir -p $(OBJ_DIR) $(BIN_DIR)

clean:
	@make clean -s -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@#echo "$(YELLOW)[    Objects have been removed!  ]$(RESET)"

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@rm -rf build
	@#echo "$(RED)[     Pipex has been removed!    ]$(RESET)"

re: fclean all

exe: all
	@./build/bin/pipex test.txt "ls" "wc" test2.txt

.PHONY: all clean fclean re