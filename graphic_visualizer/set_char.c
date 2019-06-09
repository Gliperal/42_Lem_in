/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:29:58 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 19:50:56 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

void	set_char(int x, int y, char c)
{
	ft_putstr("\e[s");
	ft_printf("\e[%dA", y);
	ft_printf("\e[%dC", x);
	ft_putchar(c);
	ft_putstr("\e[u");
}
