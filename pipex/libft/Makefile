#Name of the project
NAME	=	libft.a

#Compiler + Flags 
# -I (include) Specifies a directory dir to search for included makefiles.
CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM	=	rm -f

HEADER = ./

#.c files
SRC	= ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c\
ft_isprint.c ft_memchr.c ft_memcmp.c ft_striter.c ft_striteri.c\
ft_memcpy.c ft_memmove.c ft_memset.c ft_putendl_fd.c\
ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c\
ft_strchr.c ft_strlcpy.c ft_strmapi.c\
ft_strdup.c ft_split.c ft_calloc.c ft_itoa.c\
ft_strlen.c ft_strncmp.c ft_substr.c ft_strtrim.c\
ft_strnstr.c ft_strrchr.c ft_strjoin.c\
ft_tolower.c ft_toupper.c ft_strlcat.c ft_strncat.c\
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\
ft_printf.c ft_printf_c.c ft_printf_d.c ft_printf_p.c\
ft_printf_s.c ft_printf_u.c ft_printf_x.c ft_printf_xx.c\
ft_putnbr_base.c ft_n_base_counter.c ft_n_pointer.c ft_func_select.c\
get_next_line.c

#Object files
OBJ	=	$(SRC:.c=.o)

#Compile with the flags
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(HEADER)

# Colors #
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
RESET       =   \033[0m

all:	$(NAME)

$(NAME):    $(OBJ)
	@echo "$(YELLOW)[       Compiling libft ...      ]$(RESET)"
	@ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)[    Libft.a has been created!   ]$(RESET)"

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)[    libft.a has been removed!   ]$(RESET)"

re: fclean $(NAME)

# Is just a name for a recipe to be executed when you make an explicit request. 
# Avoid a conflict with a file of the same name, and to improve performance.
.PHONY: all clean fclean re

