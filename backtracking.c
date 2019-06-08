/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 21:12:40 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 14:42:07 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include "node.h"
#include "paths.h"
#include "libft/libft.h"

int	next_path(t_graph *graph, t_arrlst *path, t_arrlst *blocked_nodes);

static int	bt(t_graph *graph, t_arrlst *paths, t_arrlst *used, int num_paths)
{
	t_arrlst	*new_path;
	int			status;

	if (num_paths == 0)
		return (1);
	new_path = ft_arrlst_new(sizeof(int));
	if (!new_path)
		return (0);
	ft_arrlst_add(new_path, &(graph->start));
	ft_arrlst_add(paths, &new_path);
	while (1)
	{
		status = next_path(graph, new_path, used);
		if (status == 0)
		{
			ft_arrlst_remove_last(paths, 1);
			return (0);
		}
		ft_arrlst_add_arrlst(used, new_path, 1, new_path->size - 2);
		if (bt(graph, paths, used, num_paths - 1))
			return (1);
		ft_arrlst_remove_last(used, new_path->size - 2);
	}
}

t_arrlst	*create_paths(t_graph *graph, int num_paths)
{
	t_arrlst *paths;
	t_arrlst *blocked_nodes;

	if (num_paths < 0)
		return (NULL);
	paths = ft_arrlst_new(sizeof(t_arrlst *));
	if (!paths)
		return (NULL);
	blocked_nodes = ft_arrlst_new(sizeof(int));
	if (!blocked_nodes)
	{
		ft_arrlst_del(&paths);
		return (0);
	}
	if (!bt(graph, paths, blocked_nodes, num_paths))
		paths_del(&paths);
	ft_arrlst_del(&blocked_nodes);
	return (paths);
}
