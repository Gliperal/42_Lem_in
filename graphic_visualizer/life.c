/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:21:20 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 20:28:01 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "life.h"
#include "../libft/libft.h"

static void	count_neighbors(t_board *board1, t_board *board2, int x, int y)
{
	int loc;

	loc = y * board1->width + x;
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

static void	update_cells(t_board *board1, t_board *board2, int x, int y)
{
	int loc;
	int neighbors;

	loc = y * board2->width + x;
	neighbors = board2->data[loc];
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

void		update(t_board *board1, t_board *board2)
{
	int x;

	x = 20;
	while (x < 25)
	{
		if (rand() % 2)
			board_set(board1, x, 1, '.');
		x++;
	}
	ft_bzero(board2->data, board2->width * board2->height * sizeof(char));
	boards_iter(board1, board2, &count_neighbors);
	boards_iter(board1, board2, &update_cells);
}

int			init(t_board *board1, t_board *board2, int width, int height)
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
