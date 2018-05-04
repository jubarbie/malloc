# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 08:58:23 by jubarbie          #+#    #+#              #
#    Updated: 2018/05/04 20:00:08 by jubarbie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -ILibs/libft -IIncludes -Wall -Wextra -Werror 
SRC=	Sources/malloc.c \
		Sources/block_getter.c \
		Sources/block_setter.c \
		Sources/block_setter2.c \
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
	@echo "Creating libft \c"
	@make -C Libs/libft
	@echo " \033[32m[OK]\033[0m"
	@echo "Creating libft_malloc \c"
	@$(CC) -LLibs/libft -lft -lpthread -shared -o $@ $^
	@ln -sf $(NAME) $(LINK)
	@echo " \033[32m[OK]\033[0m"
	
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
