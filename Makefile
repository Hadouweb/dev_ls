CC = gcc -Werror -Wextra -Wall -g

SRCPATH = ./src
OPTION_L = $(SRCPATH)/option_l

INCPATH = ./includes

LIBFTPATH = ./libft

HEADER = -I $(LIBFTPATH)/includes -I $(INCPATH)

LIB = -L$(LIBFTPATH) -lft
LIBNAME = libft/libft.a

SRC = 	$(SRCPATH)/main.c\
		$(SRCPATH)/ls_util_dir.c\
		$(SRCPATH)/ls_error.c\
		$(SRCPATH)/ls_get_data.c\
		$(SRCPATH)/ls_debug.c\
		$(SRCPATH)/ls_option.c\
		$(SRCPATH)/ls_sort.c\
		$(SRCPATH)/ls_foreach_param.c\
		$(SRCPATH)/ls_print_folder.c\
		$(SRCPATH)/ls_set_data.c\
		$(SRCPATH)/ls_cmp.c\
		$(OPTION_L)/ls_option_l.c\
		$(OPTION_L)/ls_mode.c\
		$(OPTION_L)/ls_set_option_l.c\
		$(OPTION_L)/ls_set_option_l_2.c\
		$(OPTION_L)/ls_util_l.c\

OBJ = $(SRC:.c=.o)

NAME = ft_ls

all: $(NAME)

$(NAME): $(LIBNAME) $(OBJ)
	@$(CC) -o $@ $(LIB) $^
	@echo "\n\033[39mCompilation done.\033[0m"

$(LIBNAME):
	make -C $(LIBFTPATH)

%.o: %.c
	@$(CC) -o $@ -c $< $(HEADER)
	@echo "\033[34m█\033[0m\c"

clean: 
	@make -C $(LIBFTPATH) clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C $(LIBFTPATH) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re