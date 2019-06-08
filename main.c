#include <stdio.h>
#include <unistd.h>
#include "graph.h"
#include "node.h"
#include "paths.h"
#include "libft/libft.h"

t_graph	*read_graph(int fd);
int	pathfind(t_graph *graph);
//t_arrlst	*create_paths(t_graph *graph, int num_paths);
t_arrlst	*find_best_paths(t_graph *graph, int ants, int max_paths);
void		graph_sort_neighbors(t_graph *graph);

/*
** void print_graph(t_graph *graph)
** {
** 	printf("Graph\n");
** 	for (int i = 0; i < graph->size - graph->free_space; i++)
** 	{
** 		t_node *node = graph->nodes[i];
** 		printf("\tNode [%d, %s] with neighbors [", node->id, node->name);
** 		for (int j = 0; j < node->degree; j++)
** 		{
** 			if (j == 0)
** 				printf("%d", node->neighbors[0]);
** 			else
** 				printf(", %d", node->neighbors[j]);
** 		}
** 		printf("] and dist %d\n", node->dist_to_end);
** 	}
** 	printf("\tstart = %d, end = %d\n", graph->start, graph->end);
** }
*/

void	go_ants_go2(t_graph *graph, t_arrlst *paths, int *ants_per_path)
{
	int **ant_tracker;
	int i;

	ant_tracker = (int **)malloc(paths->size * sizeof(int *));
	if (!ant_tracker)
		return ;
	i = 0;
	while (i < paths->size)
	{
		t_arrlst *path = *(t_arrlst **)ft_arrlst_get(paths, i);
		ant_tracker[i] = (int *)malloc(path->size * sizeof(int));
		if (!ant_tracker[i])
			return ;
		ft_bzero(ant_tracker[i], path->size * sizeof(int));
		ant_tracker[i][0] = ants_per_path[i];
		i++;
	}
	int current_ant = 1;
	while (1)
	{
		int ants_moved = 0;
		int path_index = 0;
		while (path_index < paths->size)
		{
			t_arrlst *path = *(t_arrlst **)ft_arrlst_get(paths, path_index);
			i = path->size - 2;
			while (i > 0)
			{
				if (ant_tracker[path_index][i])
				{
					if (ants_moved)
						write(1, " ", 1);
					else
						ants_moved = 1;
					int node_id = *(int *)ft_arrlst_get(path, i + 1);
					char *room_name = graph->nodes[node_id]->name;
					ft_printf("L%d-%s", ant_tracker[path_index][i], room_name);
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
				int node_id = *(int *)ft_arrlst_get(path, 1);
				char *room_name = graph->nodes[node_id]->name;
				ft_printf("L%d-%s", current_ant, room_name);
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

void	go_ants_go(t_graph *graph, t_arrlst *paths, int ants)
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
		return ;
	i = 0;
	while (i < paths->size)
	{
		ants_per_path[i] = q - path_len(paths, i);
		if (i < r)
			ants_per_path[i]++;
		i++;
	}
	go_ants_go2(graph, paths, ants_per_path);
	free(ants_per_path);
}

static int	get_num_ants(int fd)
{
	char *line;
	int status;
	int i;

	status = get_next_line(fd, &line);
	if (status != 1)
		return (-1);
	i = 0;
	while (line[i])
	{
		if (line[i] < '0' || line[i] > '9')
			return (-1);
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
	{
		graph_free(graph);
		return (1);
	}
	go_ants_go(graph, paths, num_ants);
	paths_del(&paths);
	graph_free(graph);
	return (0);
}

int	main(void)
{
	t_graph	*graph;
	int		num_ants;
	int	error;

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
		}
	}
	if (error)
	{
		write(1, "ERROR\n", 6);
		return (1);
	}
	return (0);
}
