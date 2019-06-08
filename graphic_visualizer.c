/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_visualizer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 19:30:21 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/07 22:28:33 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "libft/libft.h"

typedef struct	s_board
{
	char		*data;
	int			width;
	int			height;
}				t_board;

static void	set_char(int x, int y, char c)
{
	ft_putstr("\e[s");
	ft_printf("\e[%dA", y);
	ft_printf("\e[%dC", x);
	ft_putchar(c);
	ft_putstr("\e[u");
}

static void	board_set(t_board *board, int x, int y, char c)
{
	if (x < 0 || x > board->width)
		return ;
	if (y < 0 || y > board->height)
		return ;
	board->data[y * board->width + x] = c;
}

static void	board_mark(t_board *board, int x, int y)
{
	if (x < 0 || x > board->width)
		return ;
	if (y < 0 || y > board->height)
		return ;
	board->data[y * board->width + x]++;
}

static void	update(t_board *board1, t_board *board2)
{
	for (int x = 20; x < 25; x++)
		if (rand() % 2)
			board_set(board1, x, 1, '.');
	ft_bzero(board2->data, board2->width * board2->height * sizeof(char));
	for (int x = 0; x < board1->width; x++)
		for (int y = 0; y < board1->height; y++)
		{
			int loc = y * board1->width + x;
			if (board1->data[loc] == '.')
			{
				board_mark(board2, x - 1, y - 1);
				board_mark(board2, x - 1, y);
				board_mark(board2, x - 1, y + 1);
				board_mark(board2, x, y - 1);
				board_mark(board2, x, y + 1);
				board_mark(board2, x + 1, y - 1);
				board_mark(board2, x + 1, y);
				board_mark(board2, x + 1, y + 1);
			}
		}
	for (int x = 0; x < board2->width; x++)
		for (int y = 0; y < board2->height; y++)
		{
			int loc = y * board2->width + x;
			int neighbors = board2->data[loc];
			if (board1->data[loc] == '.')
			{
				if (neighbors < 1 || neighbors > 3)
					board2->data[loc] = ' ';
				else
					board2->data[loc] = '.';
				set_char(x, y, board2->data[loc]);
			}
			else if (neighbors == 3)
			{
				board2->data[loc] = '.';
				set_char(x, y, board2->data[loc]);
			}
		}
}

static int	init(t_board *board1, t_board *board2, int width, int height)
{
	int area;

	area = width * height;
	board1->data = (char *)malloc(area * sizeof(char));
	if (!board1->data)
		return (1);
	board2->data = (char *)malloc(area * sizeof(char));
	if (!board2->data)
	{
		free(board1->data);
		return (1);
	}
	ft_bzero(board1->data, area * sizeof(char));
	ft_bzero(board2->data, area * sizeof(char));
	board1->width = width;
	board1->height = height;
	board2->width = width;
	board2->height = height;
	return (0);
}

typedef struct		s_message_chunk
{
	int				target;
	const char		*chunk;
}					t_message_chunk;

static const t_message_chunk g_message[10] =
{
	(t_message_chunk)	{0, "ERROR"},
	(t_message_chunk)	{5, " Ant farm is invalid."},
	(t_message_chunk)	{20, " The ants are escaping."},
	(t_message_chunk)	{35, " What have you done?!"},
	(t_message_chunk)	{50, " My beautiful terminal window!"},
	(t_message_chunk)	{75, " OH GOD THEY'RE EVERYWHERE!"},
	(t_message_chunk)	{90, " I don't think I'll be able to make it..."},
	(t_message_chunk)	{105, " You must... go on... without me..."},
	(t_message_chunk)	{120, " AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"},
	(t_message_chunk)	{-1, NULL}
};

static void	print_message(int round, int width)
{
	int chunks;
	int strlen;
	int cursor_x;

	chunks = 0;
	while (g_message[chunks].chunk && g_message[chunks].target <= round)
		chunks++;
	strlen = 0;
	for (int i = 0; i < chunks; i++)
		strlen += ft_strlen(g_message[i].chunk);
	ft_putstr("\e[s");
	if (strlen > width)
		ft_printf("\e[%dA", (strlen - 1) / width);
	ft_putstr("\e[0A");
	cursor_x = 0;
	int i = 0;
	while (i < chunks)
	{
		strlen = ft_strlen(g_message[i].chunk);
		if (strlen <= width - cursor_x)
		{
			write(1, g_message[i].chunk, strlen);
			cursor_x += strlen;
		}
		else
		{
			write(1, g_message[i].chunk, width - cursor_x);
			ft_printf("\e[%dD", width);
			ft_putstr("\e[1B");
			write(1, g_message[i].chunk + width - cursor_x, strlen - width + cursor_x);
			cursor_x += strlen - width;
		}
		i++;
	}
	ft_putstr("\e[K");
	ft_putstr("\e[u");
}

static const unsigned long g_update_interval = CLOCKS_PER_SEC * 3 / 10;

static int loop(t_board *board1, t_board *board2)
{
	unsigned long	wait_until;
	struct timespec	sleep_time = {0, 0};
	int				round;

	round = 0;
	while (1)
	{
		wait_until = clock() + g_update_interval;
		if (round >= 15)
			update(board1, board2);
		t_board *tmp = board2;
		board2 = board1;
		board1 = tmp;
		print_message(round, board1->width);
		sleep_time.tv_nsec = (wait_until - clock()) * 1000000000L / CLOCKS_PER_SEC;
		nanosleep(&sleep_time, NULL);
		round++;
	}
}

int	main()
{
	struct winsize	w;
	t_board			board1;
	t_board			board2;

	ioctl(1, TIOCGWINSZ, &w);
	if (init(&board1, &board2, w.ws_col, w.ws_row))
		return (1);
	loop(&board1, &board2);
}
