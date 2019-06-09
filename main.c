/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 12:53:41 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/09 14:38:24 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "graph.h"
#include "node.h"
#include "paths.h"
#include "libft/libft.h"
#include "main.h"

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

static void	free_ant_tracker(int **ant_tracker, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(ant_tracker[i]);
		i++;
	}
	free(ant_tracker);
}

static void	go_ants_go(t_graph *graph, t_arrlst *paths, int ants)
{
	int *ants_per_path;
	int **ant_tracker;

	ants_per_path = init_ants_per_path(paths, ants);
	if (!ants_per_path)
		return ;
	ant_tracker = init_ant_tracker(paths, ants_per_path);
	if (ant_tracker)
	{
		go_ants_go2(graph, paths, ant_tracker);
		free_ant_tracker(ant_tracker, paths->size);
	}
	free(ants_per_path);
}

static int	get_num_ants(int fd)
{
	char	*line;
	int		status;
	int		i;

	status = get_next_line(fd, &line);
	if (status != 1)
		return (-1);
	i = 0;
	while (line[i])
	{
		if (line[i] < '0' || line[i] > '9')
		{
			free(line);
			return (-1);
		}
		i++;
	}
	i = ft_atoi(line);
	free(line);
	return (i);
}

static int	lem_in(t_graph *graph, int num_ants)
{
	int			start_degree;
	int			end_degree;
	int			max_paths;
	t_arrlst	*paths;

	pathfind(graph);
	graph_sort_neighbors(graph);
	start_degree = graph->nodes[graph->start]->degree;
	end_degree = graph->nodes[graph->end]->degree;
	max_paths = ft_min(num_ants, ft_min(start_degree, end_degree));
	paths = find_best_paths(graph, num_ants, max_paths);
	if (!paths)
		return (1);
	go_ants_go(graph, paths, num_ants);
	paths_del(&paths);
	return (0);
}

int			main(void)
{
	t_graph	*graph;
	int		num_ants;
	int		exit_status;

	num_ants = get_num_ants(0);
	exit_status = 0;
	if (num_ants == -1)
		exit_status = 1;
	else
	{
		graph = read_graph(0);
		if (!graph)
			exit_status = 1;
		else if (num_ants != 0)
		{
			write(1, "\n", 1);
			exit_status = lem_in(graph, num_ants);
			graph_free(graph);
		}
	}
	if (exit_status)
		write(1, "ERROR\n", 6);
	return (exit_status);
}
