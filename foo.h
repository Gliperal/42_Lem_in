/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 14:48:40 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/09 14:49:08 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOO_H
# define FOO_H

typedef struct	s_foo
{
	int			current_ant;
	int			path_index;
	int			i;
	int			ants_moved;
}				t_foo;

#endif
