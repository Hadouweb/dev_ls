CC = gcc -Werror -Wextra -Wall -g

SRCPATH = ./srcs
OPTION_L = $(SRCPATH)/option_l

INCPATH = ./includes

LIBFT = ./libft

HEADER = -I $(LIBFT)/includes -I $(INCPATH)

LIB = -L$(LIBFT) -lft

SRC = 	$(SRCPATH)/main.c\
		$(SRCPATH)/ls_util_dir.c\
		$(SRCPATH)/ls_error.c\
		$(SRCPATH)/ls_get_data.c\
		$(SRCPATH)/ls_debug.c\
		$(SRCPATH)/ls_option.c\
		$(SRCPATH)/ls_sort.c\
		$(SRCPATH)/ls_print_result.c\
		$(SRCPATH)/ls_print_folder.c\
		$(SRCPATH)/ls_set_data.c\
		$(OPTION_L)/ls_option_l.c\
		$(OPTION_L)/ls_mode.c\
		$(OPTION_L)/ls_print_l.c\
		$(OPTION_L)/ls_print2_l.c\
		$(OPTION_L)/ls_util_l.c\

OBJ = $(SRC:.c=.o)

NAME = ft_ls

all : dep $(NAME)
	
dep : 
	make -C $(LIBFT)

$(NAME) : $(OBJ)
	@$(CC) $(HEADER) $(LIB) $(OBJ) -o $(NAME)
	@echo "\n\033[39mCompilation done.\033[0m"

%.o: %.c
	@$(CC) $(HEADER) -o $@ -c $<
	@echo "\033[34m█\033[0m\c"

clean : 
	@make -C $(LIBFT) clean
	rm -rf $(OBJ)

fclean : clean
	@make -C $(LIBFT) fclean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re