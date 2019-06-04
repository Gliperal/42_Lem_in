/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:31:31 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/03 15:41:21 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "graph.h"
#include "libft/libft.h"

t_graph	*graph_new(void)
{
	t_graph *graph;

	graph = malloc(sizeof(t_graph));
	if (!graph)
		return (NULL);
	graph->nodes = NULL;
	graph->size = 0;
	graph->free_space = 0;
	return (graph);
}

void	graph_free(t_graph *graph)
{
	int i;

	if (graph->nodes)
	{
		i = 0;
		while (i < graph->size - graph->free_space)
		{
			node_free(graph->nodes[i]);
			i++;
		}
	}
	free(graph->nodes);
	free(graph);
}

int	graph_add_node(t_graph *graph, const char *name)
{
	t_node *node;
	t_node **tmp;

	if (!graph || !name)
		return (-1);
	if (graph->nodes == NULL || graph->free_space == 0)
	{
		tmp = graph->nodes;
		graph->nodes = (t_node **)malloc((graph->size + 32) * sizeof(t_node *));
		if (graph->nodes == NULL)
		{
			graph->nodes = tmp;
			return (-1);
		}
		ft_memcpy(graph->nodes, tmp, graph->size * sizeof(t_node *));
		free(tmp);
		graph->size += 32;
		graph->free_space += 32;
	}
	node = node_new(graph->size - graph->free_space, name);
	if (!node)
		return (-1);
	graph->nodes[graph->size - graph->free_space] = node;
	graph->free_space--;
	return (0);
}

int	graph_node_index(t_graph *graph, const char *node_name)
{
	int i;

	if (!graph)
		return (-1);
	i = 0;
	while (i < graph->size - graph->free_space)
	{
		if (ft_strequ(graph->nodes[i]->name, node_name))
			return (i);
		i++;
	}
	return (-1);
}

int	graph_add_edge(t_graph *graph, const char *node1, const char *node2)
{
	int n1;
	int n2;

	if (!graph)
		return (-1);
	n1 = graph_node_index(graph, node1);
	n2 = graph_node_index(graph, node2);
	if (n1 == -1 || n2 == -1)
		return (-1);
	node_add_neighbor(graph->nodes[n1], n2);
	node_add_neighbor(graph->nodes[n2], n1);
	return (0);
}
