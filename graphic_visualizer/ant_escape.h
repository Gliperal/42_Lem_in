/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_escape.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:35:53 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 19:57:10 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANT_ESCAPE_H
# define ANT_ESCAPE_H

# include <time.h>

typedef struct				s_message_chunk
{
	int						target;
	const char				*chunk;
}							t_message_chunk;

static const t_message_chunk g_message[10] =
{
	(t_message_chunk)	{0, "ERROR"},
	(t_message_chunk)	{5, " Ant farm is invalid."},
	(t_message_chunk)	{20, " The ants are escaping."},
	(t_message_chunk)	{35, " What have you done?!"},
	(t_message_chunk)	{50, " My beautiful terminal window!"},
	(t_message_chunk)	{75, " OH GOD THEY'RE EVERYWHERE!"},
	(t_message_chunk)	{90, " I don't think I'll be able to make it..."},
	(t_message_chunk)	{105, " You must... go on... without me..."},
	(t_message_chunk)	{120, " AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"},
	(t_message_chunk)	{-1, 0}
};

static const unsigned long	g_update_interval = CLOCKS_PER_SEC * 3 / 10;

# define CLOCKS_TO_NANO 1000000000L / CLOCKS_PER_SEC

int							ant_escape();

#endif
