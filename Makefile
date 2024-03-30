NAME = minishell
LIBFT = libft/libft.a
CC = gcc

# Explicitly specify the paths to Readline library and include directory
READLINE_L = /Users/aghounam/.brew/opt/readline/lib
READLINE_I = /Users/aghounam/.brew/opt/readline/include

# Flags 
CFLAGS = -Wall -Wextra -Werror -g -I$(READLINE_I) #-fsanitize=address -g
LDFLAGS = -L$(READLINE_L) -lreadline -lhistory

# Sourc parser
src = main.c ft_lexer.c linked_list.c state.c syntax_error.c stack_command.c ft_lexer_utils.c ft_free.c

# sourece exec
src += execution/exec.c execution/ft_cd.c execution/exec_utils.c \
	execution/ft_pwd.c execution/ft_exit.c execution/ft_env.c 

# Objects
obj = $(src:.c=.o)

# Colors
GREEN := \033[0;32m
RED := \033[0;31m
BLUE := \033[0;34m
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
	@echo "$(BLUE)✔︎$< Compiling $(NC)"

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
