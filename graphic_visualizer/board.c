/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 20:27:47 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 20:29:43 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	board_set(t_board *board, int x, int y, char c)
{
	if (x < 0 || x > board->width)
		return ;
	if (y < 0 || y > board->height)
		return ;
	board->data[y * board->width + x] = c;
}

void	board_mark(t_board *board, int x, int y)
{
	if (x < 0 || x > board->width)
		return ;
	if (y < 0 || y > board->height)
		return ;
	board->data[y * board->width + x]++;
}

void	boards_iter(t_board *board1, t_board *board2, t_cells_func f)
{
	int x;
	int y;

	x = 0;
	while (x < board1->width)
	{
		y = 0;
		while (y < board1->height)
		{
			(*f)(board1, board2, x, y);
			y++;
		}
		x++;
	}
}
