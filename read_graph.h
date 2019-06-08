/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_graph.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:30:31 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 15:31:12 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_GRAPH_H
# define READ_GRAPH_H

typedef struct	s_read_helper
{
	t_graph		*graph;
	int			awaiting_special;
	char		*special[2];
}				t_read_helper;

#endif
