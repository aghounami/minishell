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
	@$(CC) $(CFLAGS) $(obj) $(LIBFT) -o $(NAME)  $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "✅$< Compiling "

clean:
	@rm -f $(obj)
	@cd libft && make clean
	@echo "minishell Cleaning 🧹"

fclean: clean
	@rm -f $(NAME)
	@cd libft && make fclean
	@echo "minishell Full Cleaning 🧹"

re: fclean all

push :
	@git add .
	@git commit -m "push"
	@git push

.PHONY: all clean fclean re
