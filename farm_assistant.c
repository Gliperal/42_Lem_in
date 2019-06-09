/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm_assistant.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:43:53 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/09 13:54:40 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include "node.h"
#include "paths.h"
#include "libft/libft.h"

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

int	complete_path(t_graph *graph, t_arrlst *path, t_arrlst *blocked_nodes)
{
	int		i;
	t_node	*node;

	if (!graph || !path || !blocked_nodes)
		return (0);
	i = *(int *)ft_arrlst_get(path, path->size - 1);
	if (i == graph->end)
		return (1);
	node = graph->nodes[i];
	i = 0;
	while (i < node->degree)
	{
		if (!ft_arrlst_contains(blocked_nodes, node->neighbors + i) &&
				!ft_arrlst_contains(path, node->neighbors + i))
		{
			ft_arrlst_add(path, node->neighbors + i);
			if (node->neighbors[i] == graph->end)
				return (1);
			if (complete_path(graph, path, blocked_nodes))
				return (1);
			ft_arrlst_remove_last(path, 1);
		}
		i++;
	}
	return (0);
}

int	neighbor_index(t_node *node, int neighbor)
{
	int i;

	i = 0;
	while (i < node->degree)
	{
		if (node->neighbors[i] == neighbor)
			return (i);
		i++;
	}
	return (-1);
}

int	zaphod(t_graph *graph, t_arrlst *path, t_arrlst *blocked, int index)
{
	t_node	*node;
	int		i;

	node = graph->nodes[*(int *)ft_arrlst_get(path, index)];
	i = neighbor_index(node, *(int *)ft_arrlst_get(path, index + 1)) + 1;
	while (i < node->degree)
	{
		if (!ft_arrlst_contains(blocked, node->neighbors + i) &&
				!ft_arrlst_contains(path, node->neighbors + i))
		{
			ft_arrlst_set(path, path->size - 1, node->neighbors + i);
			if (complete_path(graph, path, blocked))
				return (1);
		}
		i++;
	}
	ft_arrlst_remove_last(path, 1);
	return (0);
}

int	next_path(t_graph *graph, t_arrlst *path, t_arrlst *blocked, int *timeout)
{
	int index;

	if (*timeout <= 0)
		return (0);
	*timeout -= 1;
	if (*(int *)ft_arrlst_get(path, path->size - 1) != graph->end)
		return (complete_path(graph, path, blocked));
	index = path->size - 2;
	while (index >= 0)
	{
		if (zaphod(graph, path, blocked, index))
			return (1);
		index--;
	}
	return (0);
}
