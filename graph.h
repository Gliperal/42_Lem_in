/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:32:09 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/03 13:36:32 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_H
# define GRAPH_H

# include "node.h"

typedef struct	s_graph
{
	t_node		**nodes;
	int			size;
	int			free_space;
}				t_graph;

t_graph	*graph_new(void);
int	graph_add_node(t_graph *graph, const char *name);
int	graph_node_index(t_graph *graph, const char *node_name);
int	graph_add_edge(t_graph *graph, const char *node1, const char *node2);

#endif
