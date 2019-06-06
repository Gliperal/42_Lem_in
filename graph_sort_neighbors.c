/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_sort_neighbors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:46:14 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/06 15:07:52 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include "node.h"

static void	swap_ints(int *a, int *b)
{
	if (a == b)
		return ;
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

static int	partition(t_graph *graph, int *arr, int lo, int hi)
{
	int pivot;
	int i;
	int j;

	pivot = graph->nodes[arr[lo + (hi - lo) / 2]]->dist_to_end;
	i = lo - 1;
	j = hi + 1;
	while (1)
	{
		i++;
		while (graph->nodes[arr[i]]->dist_to_end < pivot)
			i++;
		j--;
		while (graph->nodes[arr[j]]->dist_to_end > pivot)
			j--;
		if (i >= j)
			return (j);
		swap_ints(arr + i, arr + j);
	}
}

static void	quicksort(t_graph *graph, int *arr, int lo, int hi)
{
	int part;

	if (lo < hi)
	{
		part = partition(graph, arr, lo, hi);
		quicksort(graph, arr, lo, part);
		quicksort(graph, arr, part + 1, hi);
	}
}

void		graph_sort_neighbors(t_graph *graph)
{
	int		i;
	t_node	*node;

	if (!graph)
		return ;
	i = 0;
	while (i < graph->size - graph->free_space)
	{
		node = graph->nodes[i];
		quicksort(graph, node->neighbors, 0, node->degree - 1);
		i++;
	}
}
