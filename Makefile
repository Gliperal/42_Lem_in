# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/28 14:41:02 by nwhitlow          #+#    #+#              #
#    Updated: 2019/06/05 20:05:23 by nwhitlow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror
OBJS=ft_file_processor.o graph.o main.o node.o pathfind.o read_graph.o backtracking_paths.o
RM=rm -f
NAME=lem-in

vpath libft.a libft

$(NAME): $(OBJS) -lft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -Llibft -lft

.PHONY: all clean fclean re
all: $(NAME)

clean:
	$(RM) $(OBJS)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

libft/libft.a:
	make -C libft

backtracking_paths.o: graph.h node.h -lft
graph.o: graph.h -lft
node.o: node.h -lft
pathfind.o: graph.h node.h -lft
read_graph.o: graph.h node.h -lft
