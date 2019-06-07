#include <stdio.h>
#include <unistd.h>
#include "graph.h"
#include "node.h"
#include "libft/libft.h"

t_graph	*read_graph(int fd);
int	pathfind(t_graph *graph);
int complete_path(t_graph *graph, t_arrlst *path, t_arrlst *blocked_nodes);
int	next_path(t_graph *graph, t_arrlst *path, t_arrlst *blocked_nodes);
t_arrlst	*create_paths(t_graph *graph, int num_paths);
void		graph_sort_neighbors(t_graph *graph);
void		paths_del(t_arrlst **paths);

void print_graph(t_graph *graph)
{
	printf("Graph\n");
	for (int i = 0; i < graph->size - graph->free_space; i++)
	{
		t_node *node = graph->nodes[i];
		printf("\tNode [%d, %s] with neighbors [", node->id, node->name);
		for (int j = 0; j < node->degree; j++)
		{
			if (j == 0)
				printf("%d", node->neighbors[0]);
			else
				printf(", %d", node->neighbors[j]);
		}
		printf("] and dist %d\n", node->dist_to_end);
	}
	printf("\tstart = %d, end = %d\n", graph->start, graph->end);
}

void print_path(t_arrlst *path, t_graph *graph)
{
	printf("Path ");
	for (int i = 0; i < path->size; i++)
	{
		int node = *(int *)ft_arrlst_get(path, i);
		printf("%s--", graph->nodes[node]->name);
	}
	printf("\n");
}

void print_paths(t_arrlst *paths, t_graph *graph)
{
	for (int i = 0; i < paths->size; i++)
		print_path(*(t_arrlst **)ft_arrlst_get(paths, i), graph);
}

int	path_len(t_arrlst *paths, int index)
{
	t_arrlst *path;

	path = *(t_arrlst **)ft_arrlst_get(paths, index);
	return (path->size - 1);
}

int too_many_paths(t_arrlst *paths, int ants)
{
	int i;
	int x;

	i = 0;
	x = ants;
	while (i < paths->size - 1)
	{
		x += path_len(paths, i);
		i++;
	}
	return (x <= (paths->size - 1) * path_len(paths, paths->size - 1));
}

int	time_paths(t_arrlst *paths, int ants)
{
	int i;
	int x;

	i = 0;
	x = ants;
	while (i < paths->size)
	{
		x += path_len(paths, i) - 1;
		i++;
	}
	if (x % paths->size)
		return (x / paths->size + 1);
	else
		return (x / paths->size);
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
		printf("Sending %d ants down path %d\n", ants_per_path[i], i + 1);
		i++;
	}
	graph = 0;
}

void do_things(t_graph *graph, int ants)
{
/*
	t_arrlst *path = ft_arrlst_new(sizeof(int));
	t_arrlst *blocked = ft_arrlst_new(sizeof(int));
	if (!path || !blocked)
		return ;
	int i;
	i = 0; ft_arrlst_add(path, &i);
	i = 2; ft_arrlst_add(blocked, &i);
	i = 3; ft_arrlst_add(blocked, &i);
	print_path(path, graph);
	while (1)
	{
		int status = next_path(graph, path, blocked);
		printf("next_path %d\n", status);
		if (status)
			print_path(path, graph);
		else
			break;
	}
	*/
/*
	printf("Create_paths\n");
	t_arrlst *paths = ft_arrlst_new(sizeof(t_arrlst *));
	if (!paths)
		return ;
	t_arrlst *new_path = ft_arrlst_new(sizeof(int));
	if (!new_path)
		return ;
	i = 5; ft_arrlst_add(new_path, &i);
	i = 6; ft_arrlst_add(new_path, &i);
	ft_printf("Path:\n");
	print_path(new_path);
	ft_printf("return value: %p\n", ft_arrlst_add(paths, &new_path));
	ft_printf("new_path: %p\n", new_path);
	ft_printf("paths[0]: %p\n", ft_arrlst_get(paths, 0));
	ft_printf("*paths[0]: %p\n", *(void **)ft_arrlst_get(paths, 0));
	ft_printf("Path:\n");
	print_path(new_path);
	ft_printf("Paths:\n");
	print_paths(paths);
*/
	int start_degree = graph->nodes[graph->start]->degree;
	int end_degree = graph->nodes[graph->end]->degree;
	int max_paths = ft_min(ants, ft_min(start_degree, end_degree));
	printf("Absolute max paths = %d\n", max_paths);
	int num_paths = 1;
	int time;
	int best_time = -1;
	t_arrlst *best_paths = NULL;
	while (num_paths <= max_paths)
	{
		t_arrlst *paths = create_paths(graph, num_paths);
		if (!paths)
			break ;
		print_paths(paths, graph);
		if (too_many_paths(paths, ants))
		{
			printf("Too many paths.\n");
			paths_del(&paths);
			break ;
		}
		time = time_paths(paths, ants);
		printf("Time for %d ants to go through: %d\n", ants, time);
		if (best_time == -1 || time < best_time)
		{
			best_time = time;
			best_paths = paths;
		}
		else
			paths_del(&paths);
		num_paths++;
	}
	if (best_time == -1)
		printf("Complete failure.\n");
	else
	{
		printf("Best time: %d\n", best_time);
		go_ants_go(graph, best_paths, ants);
		paths_del(&best_paths);
	}
}

int	get_num_ants(int fd)
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

int main()
{
	t_graph	*graph;
	int		num_ants;

	num_ants = get_num_ants(0);
	if (num_ants == -1)
	{
		write(1, "ERROR\n", 6);
		return (1);
	}
	graph = read_graph(0);
	if (graph)
	{
		printf("%d ants\n", num_ants);
		print_graph(graph);

		pathfind(graph);
		printf("After pathfinding:\n");
		print_graph(graph);

		graph_sort_neighbors(graph);
		printf("After sorting:\n");
		print_graph(graph);

		do_things(graph, num_ants);
		graph_free(graph);
	}
	else
		write(1, "ERROR\n", 6);
	return (0);
}
