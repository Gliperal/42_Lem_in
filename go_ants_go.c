/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_ants_go.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 12:53:41 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/09 14:48:35 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "graph.h"
#include "node.h"
#include "paths.h"
#include "libft/libft.h"
#include "foo.h"

static int	*init_ants_per_path(t_arrlst *paths, int ants)
{
	int *ants_per_path;
	int i;
	int x;
	int q;
	int r;

	i = 0;
	x = ants;
	while (i < paths->size)
		x += path_len(paths, i++);
	q = x / paths->size;
	r = x % paths->size;
	ants_per_path = (int *)malloc(paths->size * sizeof(int));
	if (!ants_per_path)
		return (NULL);
	i = 0;
	while (i < paths->size)
	{
		ants_per_path[i] = q - path_len(paths, i);
		if (i < r)
			ants_per_path[i]++;
		i++;
	}
	return (ants_per_path);
}

static int	**init_ant_tracker(t_arrlst *paths, int *ants_per_path)
{
	int			**ant_tracker;
	int			i;
	t_arrlst	*path;

	ant_tracker = (int **)malloc(paths->size * sizeof(int *));
	if (!ant_tracker)
		return (NULL);
	i = 0;
	while (i < paths->size)
	{
		path = *(t_arrlst **)ft_arrlst_get(paths, i);
		ant_tracker[i] = (int *)malloc(path->size * sizeof(int));
		if (!ant_tracker[i])
			return (NULL);
		ft_bzero(ant_tracker[i], path->size * sizeof(int));
		ant_tracker[i][0] = ants_per_path[i];
		i++;
	}
	return (ant_tracker);
}

static void	move_ant(t_graph *graph, t_arrlst *path, int **ants, t_foo *bar)
{
	int		node_id;
	char	*room_name;

	node_id = *(int *)ft_arrlst_get(path, bar->i + 1);
	room_name = graph->nodes[node_id]->name;
	if (ants[bar->path_index][bar->i] == 0)
		return ;
	if (bar->ants_moved)
		write(1, " ", 1);
	else
		bar->ants_moved = 1;
	if (bar->i == 0)
	{
		ft_printf("L%d-%s", bar->current_ant, room_name);
		ants[bar->path_index][1] = bar->current_ant;
		ants[bar->path_index][0]--;
		bar->current_ant += 1;
	}
	else
	{
		ft_printf("L%d-%s", ants[bar->path_index][bar->i], room_name);
		ants[bar->path_index][bar->i + 1] = ants[bar->path_index][bar->i];
		ants[bar->path_index][bar->i] = 0;
	}
}

static void	go_ants_go2(t_graph *graph, t_arrlst *paths, int **ant_tracker)
{
	t_foo		bar;
	t_arrlst	*path;

	bar.current_ant = 1;
	while (1)
	{
		bar.ants_moved = 0;
		bar.path_index = 0;
		while (bar.path_index < paths->size)
		{
			path = *(t_arrlst **)ft_arrlst_get(paths, bar.path_index);
			bar.i = path->size - 2;
			while (bar.i >= 0)
			{
				move_ant(graph, path, ant_tracker, &bar);
				bar.i--;
			}
			bar.path_index++;
		}
		if (!bar.ants_moved)
			break ;
		write(1, "\n", 1);
	}
}

void		go_ants_go(t_graph *graph, t_arrlst *paths, int ants)
{
	int *ants_per_path;
	int **ant_tracker;
	int i;

	ants_per_path = init_ants_per_path(paths, ants);
	if (!ants_per_path)
		return ;
	ant_tracker = init_ant_tracker(paths, ants_per_path);
	if (ant_tracker)
	{
		go_ants_go2(graph, paths, ant_tracker);
		i = 0;
		while (i < paths->size)
		{
			free(ant_tracker[i]);
			i++;
		}
		free(ant_tracker);
	}
	free(ants_per_path);
}
