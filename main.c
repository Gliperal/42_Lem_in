/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 12:53:41 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/09 13:40:57 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "graph.h"
#include "node.h"
#include "paths.h"
#include "libft/libft.h"
#include "main.h"

int		*init_ants_per_path(t_arrlst *paths, int ants)
{
	int *ants_per_path;
	int i;
	int x;
	int q;
	int r;

	i = 0;
	x = ants;
	while (i < paths->size)
	{
		x += path_len(paths, i);
		i++;
	}
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

int		**init_ant_tracker(t_arrlst *paths, int *ants_per_path)
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

char	*room_name(t_graph *graph, t_arrlst *path, int steps_down_path)
{
	int node_id;

	node_id = *(int *)ft_arrlst_get(path, steps_down_path);
	return (graph->nodes[node_id]->name);
}

void	go_ants_go2(t_graph *graph, t_arrlst *paths, int **ant_tracker)
{
	int			i;
	int			current_ant;
	int			ants_moved;
	int			path_index;
	t_arrlst	*path;

	current_ant = 1;
	while (1)
	{
		ants_moved = 0;
		path_index = 0;
		while (path_index < paths->size)
		{
			path = *(t_arrlst **)ft_arrlst_get(paths, path_index);
			i = path->size - 2;
			while (i > 0)
			{
				if (ant_tracker[path_index][i])
				{
					if (ants_moved)
						write(1, " ", 1);
					else
						ants_moved = 1;
					ft_printf("L%d-%s", ant_tracker[path_index][i], room_name(graph, path, i + 1));
					ant_tracker[path_index][i + 1] = ant_tracker[path_index][i];
					ant_tracker[path_index][i] = 0;
				}
				i--;
			}
			if (ant_tracker[path_index][0])
			{
				if (ants_moved)
					write(1, " ", 1);
				else
					ants_moved = 1;
				ft_printf("L%d-%s", current_ant, room_name(graph, path, 1));
				ant_tracker[path_index][1] = current_ant;
				ant_tracker[path_index][0]--;
				current_ant++;
			}
			path_index++;
		}
		if (!ants_moved)
			break ;
		write(1, "\n", 1);
	}
}

void	free_ant_tracker(int **ant_tracker, int size)
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

void	go_ants_go(t_graph *graph, t_arrlst *paths, int ants)
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

int	main(void)
{
	t_graph	*graph;
	int		num_ants;
	int		error;

	num_ants = get_num_ants(0);
	error = 0;
	if (num_ants == -1)
		error = 1;
	else
	{
		graph = read_graph(0);
		if (!graph)
			error = 1;
		else if (num_ants != 0)
		{
			write(1, "\n", 1);
			error = lem_in(graph, num_ants);
			graph_free(graph);
		}
	}
	if (error)
	{
		write(1, "ERROR\n", 6);
		return (1);
	}
	return (0);
}
