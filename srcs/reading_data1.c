/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_data1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:09:51 by mrolfe            #+#    #+#             */
/*   Updated: 2019/08/07 19:02:54 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		set_neighb(t_room *room)
{
	int		i;

	i = -1;
	while (++i < MAXV)
		room[i].neighb = NULL;
}

void		read_start(char *line, int fd, t_data *str, t_room *room)
{
	ft_printf("%s\n", line);
	free(line);
	get_next_line(fd, &line);
	check_room(&line);
	ft_printf("%s\n", line);
	make_start(str, room, line);
}

void		read_end(char *line, int fd, t_data *str, t_room *room)
{
	ft_printf("%s\n", line);
	free(line);
	get_next_line(fd, &line);
	check_room(&line);
	ft_printf("%s\n", line);
	make_end(str, room, line);
}

t_room		*reading_data(t_data *str, char *line, int fd)
{
	int		i;
	t_room	*room;
	int		index;

	index = 0;
	room = make_struct_arr();
	if (!check_ants(fd, &line))
		map_error();
	str->amount_of_ants = ft_atoi(line);
	index1 = str->amount_of_ants;
	index3 = str->amount_of_ants - 1;
	while (get_next_line(fd, &line))
	{
		i = -1;
		check(line, fd, str, room, &index);
	}
	return (room);
}

void		room_connections(t_room *room, char *line)
{
	int		i;
	t_room	*r;
	t_room	*r2;

	i = 0;
	while (line[i] != '-')
		i++;
	line[i] = '\0';
	r = find_room(line, room);
	make_neighb_list(room, &line[i + 1], r);
	r2 = find_room(&line[i + 1], room);
	make_neighb_list(room, &line[0], r2);
}
