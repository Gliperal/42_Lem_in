/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 14:03:24 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 14:11:37 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHS_H
# define PATHS_H

#include "graph.h"
#include "node.h"
#include "libft/libft.h"

int		path_len(t_arrlst *paths, int index);
void	print_path(t_arrlst *path, t_graph *graph);
void	print_paths(t_arrlst *paths, t_graph *graph);
void	paths_del(t_arrlst **paths);

#endif
