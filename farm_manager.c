/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 21:12:40 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/09 13:31:43 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include "node.h"
#include "paths.h"
#include "farm_management.h"
#include "libft/libft.h"

static int	backtrack(t_foo *args, int num_paths, int *timeout)
{
	t_arrlst	*new_path;
	int			status;

	if (num_paths == 0)
		return (1);
	new_path = ft_arrlst_new(sizeof(int));
	if (!new_path)
		return (0);
	ft_arrlst_add(new_path, &(args->graph->start));
	ft_arrlst_add(args->paths, &new_path);
	while (1)
	{
		status = next_path(args->graph, new_path, args->used_nodes, timeout);
		if (status == 0)
		{
			ft_arrlst_del(&new_path);
			ft_arrlst_remove_last(args->paths, 1);
			return (0);
		}
		ft_arrlst_add_arrlst(args->used_nodes, new_path, 1, new_path->size - 2);
		if (backtrack(args, num_paths - 1, timeout))
			return (1);
		ft_arrlst_remove_last(args->used_nodes, new_path->size - 2);
	}
}

t_arrlst	*create_paths(t_graph *graph, int num_paths)
{
	t_foo	args;
	int		timeout;

	args.graph = graph;
	if (num_paths < 0)
		return (NULL);
	args.paths = ft_arrlst_new(sizeof(t_arrlst *));
	if (!args.paths)
		return (NULL);
	args.used_nodes = ft_arrlst_new(sizeof(int));
	if (!args.used_nodes)
	{
		ft_arrlst_del(&args.paths);
		return (0);
	}
	timeout = 1042;
	if (!backtrack(&args, num_paths, &timeout))
		paths_del(&(args.paths));
	ft_arrlst_del(&(args.used_nodes));
	return (args.paths);
}

static int	too_many_paths(t_arrlst *paths, int ants)
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

t_arrlst	*find_best_paths(t_graph *graph, int ants, int max_paths)
{
	int num_paths;
	int best_time;
	int time;
	t_arrlst *best_paths;
	t_arrlst *paths;

	best_time = -1;
	best_paths = NULL;
	num_paths = 1;
	while (num_paths <= max_paths)
	{
		paths = create_paths(graph, num_paths);
		if (!paths)
			break ;
		if (too_many_paths(paths, ants))
		{
			paths_del(&paths);
			break ;
		}
		time = time_paths(paths, ants);
		if (best_time == -1 || time < best_time)
		{
			if (best_paths != NULL)
				paths_del(&best_paths);
			best_time = time;
			best_paths = paths;
		}
		else
			paths_del(&paths);
		num_paths++;
	}
	return (best_paths);
}
