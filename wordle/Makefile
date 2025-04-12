# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 16:46:46 by dpaes-so          #+#    #+#              #
#    Updated: 2025/03/25 16:46:30 by dpaes-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wordle

LIBFT = ./libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SOURCES = wordle.c
OBJS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -g $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -g -c $< -o $@

$(LIBFT):
	make -C ./libft -s

clean:
	make clean -C ./libft -s
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft -s
	rm -f $(NAME)

re: fclean all