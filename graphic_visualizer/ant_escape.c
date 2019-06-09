/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_escape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:22:52 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 20:09:44 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>

#include "ant_escape.h"
#include "life.h"
#include "../libft/libft.h"

static void	print_chunks(int num_chunks, int strlen, int width)
{
	int cursor_x;
	int i;

	cursor_x = 0;
	i = 0;
	while (i < num_chunks)
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
			write(1, g_message[i].chunk + width - cursor_x, \
					strlen - width + cursor_x);
			cursor_x += strlen - width;
		}
		i++;
	}
}

static void	print_message(int round, int width)
{
	int chunks;
	int strlen;
	int i;

	chunks = 0;
	while (g_message[chunks].chunk && g_message[chunks].target <= round)
		chunks++;
	strlen = 0;
	i = 0;
	while (i < chunks)
	{
		strlen += ft_strlen(g_message[i].chunk);
		i++;
	}
	ft_putstr("\e[s");
	if (strlen > width)
		ft_printf("\e[%dA", (strlen - 1) / width);
	ft_putstr("\e[0A");
	print_chunks(chunks, strlen, width);
	ft_putstr("\e[K");
	ft_putstr("\e[u");
}

static int	loop(t_board *board1, t_board *board2)
{
	unsigned long	wait_until;
	struct timespec	sleep_time;
	int				round;
	t_board			*tmp;

	sleep_time.tv_sec = 0;
	round = 0;
	while (1)
	{
		wait_until = clock() + g_update_interval;
		if (round >= 15)
			update(board1, board2);
		tmp = board2;
		board2 = board1;
		board1 = tmp;
		print_message(round, board1->width);
		sleep_time.tv_nsec = (wait_until - clock()) * CLOCKS_TO_NANO;
		nanosleep(&sleep_time, NULL);
		round++;
	}
}

int			ant_escape(void)
{
	struct winsize	w;
	t_board			board1;
	t_board			board2;

	ioctl(1, TIOCGWINSZ, &w);
	if (init(&board1, &board2, w.ws_col, w.ws_row))
		return (1);
	write(1, "\n", 1);
	loop(&board1, &board2);
	return (0);
}
