# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 08:58:23 by jubarbie          #+#    #+#              #
#    Updated: 2018/05/02 17:50:21 by jubarbie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
SRC=    align_test.c \
		../Sources/align.c
OBJ=$(SRC:.c=.o)
NAME= test
.PHONY: clean fclean all re

$(NAME): $(OBJ)
	$(CC) -o $@ $^

all: $(NAME)

%.o: %.c
	$(CC) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(LINK)

re: fclean all
