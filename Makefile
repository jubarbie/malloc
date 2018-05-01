# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 08:58:23 by jubarbie          #+#    #+#              #
#    Updated: 2018/05/01 21:11:35 by jubarbie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -ILibs/libft -IIncludes -Wall -Wextra -Werror 
SRC=    Sources/main.c \
		Sources/malloc.c \
		Sources/block_getter.c \
		Sources/block_setter.c \
		Sources/block.c \
		Sources/block2.c \
		Sources/free.c \
		Sources/realloc.c \
		Sources/show_alloc_mem.c
OBJ=$(SRC:.c=.o)
NAME=malloc
.PHONY: clean fclean all re

$(NAME): $(OBJ)
	@make -C Libs/libft
	@$(CC) -LLibs/libft/ -lft -o $@ $^
	@echo "\033[32mOK\033[0m"

all: $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@make clean -C Libs/libft
	@rm -f $(OBJ)
	@echo "Object files deleted"

fclean: clean
	@make fclean -C Libs/libft
	@rm -f $(NAME) $(LINK)
	@echo "Files deleted"

re: fclean all
