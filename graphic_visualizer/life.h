/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:27:11 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 20:29:53 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

typedef struct	s_board
{
	char		*data;
	int			width;
	int			height;
}				t_board;

typedef	void	(*t_cells_func)(t_board *board1, t_board *board2, int x, int y);

void			board_set(t_board *board, int x, int y, char c);
void			board_mark(t_board *board, int x, int y);
void			boards_iter(t_board *board1, t_board *board2, t_cells_func f);

void			set_char(int x, int y, char c);
int				init(t_board *board1, t_board *board2, int width, int height);
void			update(t_board *board1, t_board *board2);

#endif
