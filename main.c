/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 12:53:41 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/09 18:24:50 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "graph.h"
#include "node.h"
#include "paths.h"
#include "libft/libft.h"
#include "main.h"

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
		ft_printf("%d\n", num_ants);
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
