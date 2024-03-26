NAME = minishell
LIBFT = libft/libft.a
CC = gcc

# Explicitly specify the paths to Readline library and include directory
READLINE_L = /Users/aghounam/.brew/opt/readline/lib
READLINE_I = /Users/aghounam/.brew/opt/readline/include

# Flags 
CFLAGS = -Wall -Wextra -Werror -g -I$(READLINE_I) #-fsanitize=address -g
LDFLAGS = -L$(READLINE_L) -lreadline -lhistory

# Sourc
src = main.c ft_lexer.c linked_list.c state.c syntax_error.c stack_command.c exec.c
  
# Objects
obj = $(src:.c=.o)

# Colors
GREEN := \033[0;32m
RED := \033[0;31m
NC := \033[0m


all: $(LIBFT) $(NAME) 

$(LIBFT):
	@echo "$(RED)libft Compiling$(NC)"
	@echo "$(RED)-----------------$(NC)"
	@cd libft && make
	@echo "$(RED)minishell Compiling$(NC)"

$(NAME): $(obj)
	@$(CC) $(CFLAGS) $(obj) $(LIBFT) -o $(NAME)  $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✔︎$< Compiling $(NC)"

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
	@git commit -m "update"
	@git push

.PHONY: all clean fclean re
