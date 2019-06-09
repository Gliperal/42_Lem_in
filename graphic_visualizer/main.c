/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 19:30:21 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 20:09:08 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ant_escape.h"
#include "../libft/libft.h"

int	visualize(void)
{
	ft_putstr("                    .:_:.\n");
	ft_putstr("                 ,-'     '-,\n");
	ft_putstr("             .-*\"           \"*-.\n");
	ft_putstr("________.,-*'                   '*-,.________\n\n");
	ft_putstr("Here is your ant farm.\n");
	sleep(3);
	ft_putstr("You can't see the ants, because they're underground.\n");
	sleep(5);
	ft_putstr("But trust me, ");
	ft_putstr("they found a very fast route through the tunnels.\n");
	sleep(5);
	ft_putstr("You should be very proud of your ants :)\n");
	return (0);
}

int	main(void)
{
	char	*line;
	char	*last_line;
	int		status;
	int		error;

	line = NULL;
	last_line = NULL;
	while ((status = get_next_line(0, &line)) != 0)
	{
		if (status == -1)
		{
			free(line);
			free(last_line);
			return (1);
		}
		free(last_line);
		last_line = line;
	}
	error = ft_strequ(last_line, "ERROR");
	free(last_line);
	if (error)
		return (ant_escape());
	else
		return (visualize());
}
