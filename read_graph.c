/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:56:53 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/08 12:15:26 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include "node.h"
#include "libft/libft.h"

// TODO Move to libft
#include "ft_file_processor.h"

static int	is_room(const char *line)
{
	if (line[0] == ' ' || line[0] == 'L' || line[0] == '#')
		return (0);
	while (*line && *line != ' ')
		line++;
	if (!(*line))
		return (0);
	while (*line == ' ')
		line++;
	if (*line == '+' || *line == '-')
		line++;
	if (*line < '0' || *line > '9')
		return (0);
	while (*line >= '0' && *line <= '9')
		line++;
	if (*line != ' ')
		return (0);
	while (*line == ' ')
		line++;
	if (*line == '+' || *line == '-')
		line++;
	if (*line < '0' || *line > '9')
		return (0);
	while (*line >= '0' && *line <= '9')
		line++;
	return (!(*line));
}

typedef struct	s_read_helper
{
	t_graph		*graph;
	int			awaiting_special;
	char		*special[2];
}				t_read_helper;

static int	process_line_special(const char *line, t_read_helper *rh)
{
	if (ft_strequ(line, "#start"))
	{
		if (rh->awaiting_special != -1 || rh->special[0])
			return (-1);
		rh->awaiting_special = 0;
		ft_putstr("##start\n");
		return (0);
	}
	else if (ft_strequ(line, "#end"))
	{
		if (rh->awaiting_special != -1 || rh->special[1])
			return (-1);
		rh->awaiting_special = 1;
		ft_putstr("##end\n");
		return (0);
	}
	return (0);
}

static int	process_line_node(const char *line, void *data)
{
	t_read_helper	*rh;
	char			*name;

	rh = (t_read_helper *)data;
	if (line[0] == '#')
		return (process_line_special(line + 1, rh));
	else if (is_room(line))
	{
		name = ft_strsub(line, 0, ft_strchr(line, ' ') - line);
		if (graph_add_node(rh->graph, name) == -1)
		{
			free(name);
			return (-1);
		}
		if (rh->awaiting_special != -1)
			rh->special[rh->awaiting_special] = ft_strdup(name);
		free(name);
		rh->awaiting_special = -1;
		ft_putendl(line);
		return (0);
	}
	return (-1);
}

static int	ft_indexof(const char *str, const char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	process_line_edge(const char *line, void *data)
{
	t_read_helper	*rh;
	int				status;
	char			*node1;
	int				split;

	rh = (t_read_helper *)data;
	if (line[0] == '#')
	{
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			return (-1);
		else
			return (0);
	}
	split = ft_indexof(line, '-');
	if (split == -1)
		return (-1);
	node1 = ft_strsub(line, 0, split);
	status = graph_add_edge(rh->graph, node1, line + split + 1);
	free(node1);
	if (status == -1)
		return (-1);
	ft_putendl(line);
	return (0);
}

static t_lh g_process_line[3] = {&process_line_node, &process_line_edge, NULL};

/*
** @deprecated
*/

void	free_read_helper(void *data)
{
	t_read_helper *rh;

	rh = (t_read_helper *)data;
	free(rh->graph);
	if (rh->special[0])
		free(rh->special[0]);
	if (rh->special[1])
		free(rh->special[1]);
}

t_graph	*read_graph(int fd)
{
	t_read_helper		rh;
	t_file_processor	*fp;
	int					status;

	rh.graph = graph_new();
	if (!rh.graph)
		return (NULL);
	rh.awaiting_special = -1;
	rh.special[0] = NULL;
	rh.special[1] = NULL;
	fp = ft_fp_init(g_process_line, &rh, NULL);
	status = ft_fp_process_fd(fp, fd);
	free(fp);
	rh.graph->start = graph_node_index(rh.graph, rh.special[0]);
	rh.graph->end = graph_node_index(rh.graph, rh.special[1]);
	ft_printf("start %d %s\n", rh.graph->start, rh.special[0]);
	ft_printf("end %d %s\n", rh.graph->end, rh.special[1]);
	free(rh.special[0]);
	free(rh.special[1]);
	if (status || rh.graph->start == -1 || rh.graph->end == -1)
	{
		free(rh.graph);
		return (NULL);
	}
	return (rh.graph);
}
