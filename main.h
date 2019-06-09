/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:10:51 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/09 14:37:25 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

t_graph			*read_graph(int fd);
int				pathfind(t_graph *graph);
void			graph_sort_neighbors(t_graph *graph);
t_arrlst		*find_best_paths(t_graph *graph, int ants, int max_paths);

typedef struct	s_foo
{
	int			current_ant;
	int			path_index;
	int			i;
	int			ants_moved;
}				t_foo;

#endif
