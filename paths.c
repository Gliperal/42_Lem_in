/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 14:01:33 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 15:11:38 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paths.h"

int		path_len(t_arrlst *paths, int index)
{
	t_arrlst *path;

	path = *(t_arrlst **)ft_arrlst_get(paths, index);
	return (path->size - 1);
}

void	print_path(t_arrlst *path, t_graph *graph)
{
	int i;
	int node;

	ft_printf("Path ");
	i = 0;
	while (i < path->size)
	{
		node = *(int *)ft_arrlst_get(path, i);
		if (i != 0)
			ft_putstr("--");
		ft_putstr(graph->nodes[node]->name);
		i++;
	}
	ft_printf("\n");
}

void	print_paths(t_arrlst *paths, t_graph *graph)
{
	int i;

	i = 0;
	while (i < paths->size)
	{
		print_path(*(t_arrlst **)ft_arrlst_get(paths, i), graph);
		i++;
	}
}

void	paths_del(t_arrlst **paths)
{
	int			i;
	t_arrlst	**path;

	i = 0;
	while (i < (*paths)->size)
	{
		path = ft_arrlst_get(*paths, i);
		ft_arrlst_del(path);
		i++;
	}
	ft_arrlst_del(paths);
}
