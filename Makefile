# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 08:58:23 by jubarbie          #+#    #+#              #
#    Updated: 2018/04/20 12:16:23 by jubarbie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -Wall -Wextra -Werror
SRC=    main.c \
		malloc.c
OBJ=$(SRC:.c=.o)
NAME=malloc

$(NAME): $(OBJ)
	$(CC) -o $@ $^

all: $(NAME)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
