CC=gcc
CFLAGS=-Wall -Wextra -Werror
OBJS=main.o ant_escape.o life.o set_char.o board.o
NAME=../visualizer
RM=rm -rf

vpath libft.a ../libft

$(NAME): $(OBJS) -lft
	$(CC) $(CFLAGS) $(OBJS) -L ../libft -l ft -o $(NAME)

main.o: ant_escape.h -lft
ant_escape.o: ant_escape.h life.h -lft
life.o: life.h -lft
board.o: life.h
set_char.o: -lft

fclean:
	$(RM) $(OBJS)
	$(RM) $(NAME)
