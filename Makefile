# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 08:58:23 by jubarbie          #+#    #+#              #
#    Updated: 2018/04/28 14:51:15 by jubarbie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -Wall -Wextra -Werror 
SRC=    main.c \
		malloc.c \
		room.c \
		block.c \
		foot_block.c \
		head_block.c \
		free.c \
		show_alloc_mem.c
OBJ=$(SRC:.c=.o)
NAME=malloc
.PHONY: clean fclean all re

$(NAME): $(OBJ)
	@$(CC) -o $@ $^

all: $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(LINK)

re: fclean all
