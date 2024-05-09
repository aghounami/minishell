# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aghounam <aghounam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 04:09:48 by hkchikec          #+#    #+#              #
#    Updated: 2024/05/08 10:39:04 by aghounam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MANDA_SRCS =    ft_atoi.c  ft_bzero.c ft_calloc.c \
                ft_isalnum.c ft_isalpha.c ft_isascii.c \
                ft_isdigit.c ft_isprint.c ft_itoa.c \
                ft_memchr.c ft_memcmp.c ft_memcpy.c \
                ft_memmove.c ft_memset.c ft_putchar_fd.c \
                ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
                ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
                ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
                ft_strmapi.c ft_strncmp.c ft_strnstr.c \
                ft_strrchr.c ft_strtrim.c ft_substr.c \
                ft_tolower.c ft_toupper.c
BONUS_SRCS =   ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
                ft_lstsize_bonus.c ft_lstlast_bonus.c \
                ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
                ft_lstclear_bonus.c ft_lstiter_bonus.c \
                ft_lstmap_bonus.c
NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBC = ar rcs
RM = rm -f
OBJ = $(MANDA_SRCS:.c=.o)
BONUS_OBJ = $(BONUS_SRCS:.c=.o)

GREEN := \033[0;32m
RED := \033[0;31m
NC := \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(LIBC) $(NAME) $(OBJ)
	@echo "$(GREEN)libft Compiled ✔︎$(NC)"

bonus: all $(BONUS_OBJ)
	@$(LIBC) $(NAME) $(BONUS_OBJ)

%.o: %.c libft.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(BONUS_OBJ) $(OBJ)
	@echo "libft Cleaning 🧹"

fclean: clean
	@$(RM) $(NAME)
	@echo "libft Full Cleaning 🧹"

re: fclean all

.PHONY: all clean bonus fclean re
