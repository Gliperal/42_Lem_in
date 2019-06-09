# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/28 14:41:02 by nwhitlow          #+#    #+#              #
#    Updated: 2019/06/09 14:49:51 by nwhitlow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror
OBJS=graph.o main.o node.o pathfind.o read_graph.o farm_assistant.o farm_manager.o graph_sort_neighbors.o paths.o go_ants_go.o
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

farm_assistant.o: graph.h node.h paths.h -lft
graph.o: graph.h -lft
node.o: node.h -lft
pathfind.o: graph.h node.h -lft
read_graph.o: read_graph.h graph.h node.h -lft
farm_manager.o: farm_management.h graph.h node.h -lft
graph_sort_neighbors.o: graph.h node.h -lft
paths.o: paths.h graph.h node.h -lft
main.o: main.h graph.h node.h paths.h -lft
go_ants_go.o: graph.h node.h paths.h foo.h -lft
