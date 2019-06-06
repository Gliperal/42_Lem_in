/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 21:12:40 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/05 21:58:14 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include "node.h"
#include "libft/libft.h"

int	next_path(t_graph *graph, t_arrlst *path, t_arrlst *blocked_nodes);

void ft_arrlst_remove_last(t_arrlst *list, int amount)
{
	list->size = list->size - amount;
}

static int	backtrack(t_graph *graph, t_arrlst *paths, t_arrlst *blocked_nodes, int num_paths)
{
	if (num_paths == 0)
		return (1);
	t_arrlst *new_path = ft_arrlst_new(sizeof(int));
	if (!new_path)
		return (0);
	ft_arrlst_add(new_path, &(graph->start));
	ft_arrlst_add(paths, &new_path);
	while (1)
	{
		int status = next_path(graph, new_path, blocked_nodes);
		if (status == 0)
		{
			ft_arrlst_remove_last(paths, 1);
			return (0);
		}
		// add new_path nodes to blocked_nodes (minus start and end)
		if (backtrack(graph, paths, blocked_nodes, num_paths - 1))
			return (1);
		// remove new_path nodes from blocked_nodes
	}
}

t_arrlst	*create_paths(t_graph *graph, int num_paths)
{
	// num_paths can be capped by degree of start and end as well (and number of ants)
	if (num_paths < 0)
		return (NULL);
	t_arrlst *paths = ft_arrlst_new(sizeof(t_arrlst *));
	if (!paths)
		return (NULL);
	t_arrlst *blocked_nodes = ft_arrlst_new(sizeof(int));
	if (!blocked_nodes)
	{
		ft_arrlst_del(&paths);
		return (0);
	}
	if (backtrack(graph, paths, blocked_nodes, num_paths))
		return (paths);
	return (NULL);
}
