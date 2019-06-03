/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:45:37 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/03 14:29:32 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/libft.h"
#include "node.h"

t_node	*node_new(int id, const char *name)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->id = id;
	node->name = ft_strdup(name);
	node->dist_to_end = -1;
	node->degree = 0;
	node->neighbors = NULL;
	return (node);
}

int		node_add_neighbor(t_node *node, int neighbor)
{
	int *tmp;

	tmp = node->neighbors;
	node->neighbors = (int *)malloc((node->degree + 1) * sizeof(int));
	if (!node->neighbors)
	{
		node->neighbors = tmp;
		return (-1);
	}
	ft_memcpy(node->neighbors, tmp, node->degree * sizeof(int));
	free(tmp);
	node->neighbors[node->degree] = neighbor;
	node->degree++;
	return (0);
}

void	node_free(t_node *node)
{
	free(node->name);
	free(node->neighbors);
	free(node);
}
