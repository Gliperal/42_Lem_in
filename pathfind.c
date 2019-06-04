/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 16:01:25 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/03 21:53:20 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"
#include "graph.h"
#include "node.h"

// TODO REMOVE
#include <stdio.h>

int	pathfind(t_graph *graph, int end)
{
	t_arrlst *active;
	t_arrlst *pending;
	int i;
	int j;
	int depth;

	graph->size = graph->size - graph->free_space;
	graph->free_space = 0;
	active = ft_arrlst_new(sizeof(int));
	if (!active)
		return (-1);
	pending = ft_arrlst_new(sizeof(int));
	if (!pending)
		return (-1);
	ft_arrlst_add(active, &end);
	depth = 1;
	graph->nodes[end]->dist_to_end = 0;
	// set dist_to_end to -1 for all nodes
	while (!ft_arrlst_isempty(active))
	{
		ft_arrlst_clear(pending);
		i = 0;
		while (i < active->size)
		{
			int node = *(int *)ft_arrlst_get(active, i);
			j = 0;
			while (j < graph->nodes[node]->degree)
			{
				int neighbor_id = graph->nodes[node]->neighbors[j];
				t_node *neighbor = graph->nodes[neighbor_id];
				if (neighbor->dist_to_end == -1)
				{
					neighbor->dist_to_end = depth;
					printf("Adding %d\n", neighbor_id);
					ft_arrlst_add(pending, &neighbor_id);
				}
				j++;
			}
			i++;
		}
		t_arrlst *tmp = active;
		active = pending;
		pending = tmp;
		depth++;
	}
	return (0);
}
