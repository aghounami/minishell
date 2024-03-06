NAME = minishell
LIBFT = libft/libft.a
CC = gcc

# Explicitly specify the paths to Readline library and include directory
READLINE_L = /Users/aghounam/.brew/opt/readline/lib
READLINE_I = /Users/aghounam/.brew/opt/readline/include

# Flags 
CFLAGS = -Wall -Wextra -Werror -I$(READLINE_I) -fsanitize=address -g
LDFLAGS = -L$(READLINE_L) -lreadline -lhistory

# Sources
src = main.c split.c ft_lexer.c linked_list.c

# Objects
obj = $(src:.c=.o)

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@cd libft && make

$(NAME): $(obj)
	$(CC) $(CFLAGS) -o $(NAME) $(obj) $(LDFLAGS)

clean:
	rm -f $(obj)
	@cd libft && make clean

fclean: clean
	rm -f $(NAME)
	@cd libft && make fclean

re: fclean all

.PHONY: all clean fclean re
