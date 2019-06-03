# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/28 14:41:02 by nwhitlow          #+#    #+#              #
#    Updated: 2019/06/03 15:36:15 by nwhitlow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror
OBJS=ft_file_processor.o graph.o main.o node.o read_graph.o
RM=rm -f
NAME=lem-in

$(NAME): $(OBJS) -lft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -Llibft -lft

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	$(RM) $(OBJS)
	make -C libft clean

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

vpath libft.a libft

libft/libft.a:
	make -C libft
