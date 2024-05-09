NAME = minishell
LIBF = libf/libft.a
CC = gcc

# Explicitly specify the paths to Readline library and include directory
READLINE_L = /Users/aghounam/.brew/opt/readline/lib
READLINE_I = /Users/aghounam/.brew/opt/readline/include

# Flags 
CFLAGS = -Wall -Wextra -g -I$(READLINE_I)  -fsanitize=address -g
LDFLAGS = -L$(READLINE_L) -lreadline -lhistory

# Sourc parser
src = parsing/main.c parsing/ft_lexer.c parsing/linked_list.c parsing/state.c parsing/syntax_error.c \
	parsing/stack_command.c parsing/ft_lexer_utils.c parsing/ft_free.c parsing/new_list.c \
	parsing/env_value.c parsing/command_utils.c parsing/new_list_utils.c\

# sourece exec
src += execution/exec.c execution/ft_cd.c execution/exec_utils.c execution/ft_export.c \
	execution/ft_pwd.c execution/ft_exit.c execution/ft_env.c execution/echo.c  execution/linked_list_exec.c \
	execution/unset.c execution/redirection.c\

# Objects
obj = $(src:.c=.o)

# Colors
RED := \033[0;31m
BLUE := \033[0;34m
NC := \033[0m


all: LIBFT $(NAME)

LIBFT:
	@echo "$(RED)libf Compiling$(NC)"
	@echo "$(RED)-----------------$(NC)"
	@cd libf && make
	@echo "$(RED)minishell Compiling$(NC)"

$(NAME): $(obj) $(LIBF)
	@$(CC) $(CFLAGS) $(obj) $(LIBF) -o $(NAME)  $(LDFLAGS)

%.o: %.c minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)✔︎$< Compiling $(NC)"

clean:
	@rm -f $(obj)
	@cd libf && make clean
	@echo "minishell Cleaning 🧹"

fclean: clean
	@rm -f $(NAME)
	@cd libf && make fclean
	@echo "minishell Full Cleaning 🧹"

re: fclean all

push :
	@git add .
	@git commit -m "update"
	@git push

.PHONY: all clean fclean re
