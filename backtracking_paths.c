/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:43:53 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/05 20:44:22 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include "node.h"
#include "libft/libft.h"

int	ft_arrlst_contains(t_arrlst *list, int elem)
{
	return (ft_arrlst_indexof(list, &elem) != -1);
}

void ft_arrlst_remove_index(t_arrlst *list, int index)
{
	if (index == list->size - 1)
		list->size = list->size - 1;
}

int complete_path(t_graph *graph, t_arrlst *path, t_arrlst *blocked_nodes)
{
	if (!graph || !path || !blocked_nodes)
		return (0);
	int i = *(int *)ft_arrlst_get(path, path->size - 1);
	if (i == graph->end)
		return (1);
	t_node *node = graph->nodes[i];
	i = 0;
	while (i < node->degree)
	{
		if (ft_arrlst_contains(blocked_nodes, node->neighbors[i]) ||
				ft_arrlst_contains(path, node->neighbors[i])
		)
		{
			i++;
			continue ;
		}
		ft_arrlst_add(path, node->neighbors + i);
		if (node->neighbors[i] == graph->end)
			return (1);
		if (complete_path(graph, path, blocked_nodes))
			return (1);
		ft_arrlst_remove_index(path, path->size - 1);
		i++;
	}
	return (0);
}

int neighbor_index(t_node *node, int neighbor)
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

void	ft_arrlst_set(t_arrlst *lst, int index, void *data)
{
	ft_memcpy(lst->data + index * lst->elem_size, data, lst->elem_size);
}

int	next_path(t_graph *graph, t_arrlst *path, t_arrlst *blocked_nodes)
{
	int index;
	t_node *node;
	int *neighbors;
	int i;

	if (*(int *)ft_arrlst_get(path, path->size - 1) != graph->end)
		return (complete_path(graph, path, blocked_nodes));
	index = path->size - 2;
	while (index >= 0)
	{
		node = graph->nodes[*(int *)ft_arrlst_get(path, index)];
		neighbors = node->neighbors;
		i = neighbor_index(node, *(int *)ft_arrlst_get(path, index + 1)) + 1;
		while (i < node->degree)
		{
			if (ft_arrlst_contains(blocked_nodes, node->neighbors[i]) ||
					ft_arrlst_contains(path, node->neighbors[i]))
			{
				i++;
				continue ;
			}
			ft_arrlst_set(path, path->size - 1, neighbors + i);
			if (complete_path(graph, path, blocked_nodes))
				return (1);
			i++;
		}
		ft_arrlst_remove_index(path, path->size - 1);
		index--;
	}
	return (0);
}
