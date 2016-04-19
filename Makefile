CC = clang -Werror -Wextra -Wall -g

SRCPATH = ./srcs

INCPATH = ./includes

LIBFT = ./libft

HEADER = -I $(LIBFT)/includes -I $(INCPATH)

LIB = -L$(LIBFT) -lft

SRC = 	$(SRCPATH)/main.c\
		$(SRCPATH)/ls_dir.c\
		$(SRCPATH)/ls_error.c\
		$(SRCPATH)/ls_stat.c\
		$(SRCPATH)/ls_user.c\
		$(SRCPATH)/ls_group.c\

OBJ = $(SRC:.c=.o)

NAME = ft_ls

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C $(LIBFT)
	@$(CC) $(HEADER) $(LIB) $(OBJ) -o $(NAME)
	@echo "\n\033[39mCompilation done.\033[0m"

%.o: %.c
	@$(CC) $(HEADER) -o $@ -c $<
	@echo "\033[34m█\033[0m\c"

clean : 
	@make -C $(LIBFT) clean
	@rm -rf $(OBJ)

fclean : clean
	@make -C $(LIBFT) fclean
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re