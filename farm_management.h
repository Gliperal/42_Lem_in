/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm_management.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 18:08:59 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 18:22:22 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FARM_MANAGEMENT_H
# define FARM_MANAGEMENT_H

int				next_path(t_graph *graph, t_arrlst *path, t_arrlst *block, int *time);
int				time_paths(t_arrlst *paths, int ants);

typedef struct	s_foo
{
	t_graph		*graph;
	t_arrlst	*paths;
	t_arrlst	*used_nodes;
}				t_foo;

#endif
