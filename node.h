/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:43:49 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/03 13:14:35 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

typedef struct	s_node
{
	int			id;
	const char	*name;
	int			dist_to_end;
	int			degree;
	int			*neighbors;
}				t_node;

t_node	*node_new(int id, const char *name);
int		node_add_neighbor(t_node *node, int neighbor);
void	node_free(t_node *node);

#endif
