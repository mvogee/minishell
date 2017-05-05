NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I./includes \
			-I./libft \
			-I./ft_printf

LINK = ./libft/libft.a \
 		./ft_printf/libftprintf.a \

SRCS = src/main.c \
		src/utils.c \

OBJS = $(SRCS:.c=.o)

all: make_libft make_printf $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(INCLUDES) $(LINK)

clean: clean_libft clean_printf
	rm -f $(OBJS)

fclean: fclean_libft fclean_printf
	rm -f $(NAME)

re: fclean all

re_mini: fclean_mini all

clean_libft:
	@make -C libft clean

clean_printf:
	@make -C ft_printf clean

fclean_mini: clean
	rm -f $(NAME);

fclean_libft:
	@make -C libft fclean

fclean_printf:
	@make -C ft_printf fclean

make_libft:
	@make -C libft all

make_printf:
	@make -C ft_printf all
