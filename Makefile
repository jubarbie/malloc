# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 08:58:23 by jubarbie          #+#    #+#              #
#    Updated: 2018/04/26 18:18:26 by jubarbie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -Ilibft -Wall -Wextra -Werror
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

$(NAME): $(OBJ)
	make -C libft
	$(CC) -Llibft/ -lft -o $@ $^

all: $(NAME)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	make clean -C libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all
