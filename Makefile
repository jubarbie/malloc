# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 08:58:23 by jubarbie          #+#    #+#              #
#    Updated: 2018/05/02 18:05:51 by jubarbie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -ILibs/libft -IIncludes -Wall -Wextra -Werror 
SRC=	Sources/malloc.c \
		Sources/block_getter.c \
		Sources/block_setter.c \
		Sources/block.c \
		Sources/block2.c \
		Sources/free.c \
		Sources/realloc.c \
		Sources/show_alloc_mem.c
OBJ=$(SRC:.c=.o)
ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME=libft_malloc_$(HOSTTYPE).so
LINK=libft_malloc.so
.PHONY: clean fclean all re

$(NAME): $(OBJ)
	@make -C Libs/libft
	@$(CC) -LLibs/libft -lft -shared -o $@ $^
	@ln -sf $(NAME) $(LINK)
	@echo 'libft_malloc created'
	
all: $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@make clean -C Libs/libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C Libs/libft
	@rm -f $(NAME) $(LINK)

re: fclean all
