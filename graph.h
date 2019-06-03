/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:32:09 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/03 14:31:31 by nwhitlow         ###   ########.fr       */
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

t_graph			*graph_new(void);
int				graph_add_node(t_graph *graph, const char *name);
int				graph_node_index(t_graph *graph, const char *node_name);
int				graph_add_edge(t_graph *graph, const char *n1, const char *n2);
void			graph_free(t_graph *graph);

#endif
