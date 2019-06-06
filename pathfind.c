/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 16:01:25 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/06 12:45:38 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"
#include "graph.h"
#include "node.h"

static void	search(t_graph *graph, t_arrlst *active, t_arrlst *pend, int depth)
{
	int		i;
	int		j;
	int		node;
	int		neighbor_id;
	t_node	*neighbor;

	i = 0;
	while (i < active->size)
	{
		node = *(int *)ft_arrlst_get(active, i);
		j = 0;
		while (j < graph->nodes[node]->degree)
		{
			neighbor_id = graph->nodes[node]->neighbors[j];
			neighbor = graph->nodes[neighbor_id];
			if (neighbor->dist_to_end == -1)
			{
				neighbor->dist_to_end = depth;
				ft_arrlst_add(pend, &neighbor_id);
			}
			j++;
		}
		i++;
	}
}

static void	init_graph(t_graph *graph)
{
	int i;

	graph->size = graph->size - graph->free_space;
	graph->free_space = 0;
	i = 0;
	while (i < graph->size)
	{
		graph->nodes[i]->dist_to_end = -1;
		i++;
	}
	graph->nodes[graph->end]->dist_to_end = 0;
}

int			pathfind(t_graph *graph)
{
	t_arrlst	*active;
	t_arrlst	*pending;
	t_arrlst	*tmp;
	int			depth;

	active = ft_arrlst_new(sizeof(int));
	if (!active)
		return (-1);
	pending = ft_arrlst_new(sizeof(int));
	if (!pending)
		return (-1);
	ft_arrlst_add(active, &(graph->end));
	depth = 1;
	init_graph(graph);
	while (!ft_arrlst_isempty(active))
	{
		ft_arrlst_clear(pending);
		search(graph, active, pending, depth);
		tmp = active;
		active = pending;
		pending = tmp;
		depth++;
	}
	return (0);
}
