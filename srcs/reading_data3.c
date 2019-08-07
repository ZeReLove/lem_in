/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_data3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:16:37 by mrolfe            #+#    #+#             */
/*   Updated: 2019/08/06 14:18:32 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		make_start(t_data *str, t_room *room, char *line)
{
	int		i;

	i = 0;
	while (line[i] != ' ')
		i++;
	line[i] = '\0';
	room[room_nb].name = ft_strdup(line);
	str->start = ft_strdup(line);
	room[room_nb].value = NOT_GIVEN;
	room[room_nb].neighb = NULL;
	room[room_nb].status = OPENED;
	room[room_nb].is_ant_inside = 0;
	str->start_room = &room[room_nb];
	room_nb++;
}

void		make_end(t_data *str, t_room *room, char *line)
{
	int		i;

	i = 0;
	while (line[i] != ' ')
		i++;
	line[i] = '\0';
	if (!(room[room_nb].name = ft_strdup(line)))
		malloc_error();
	str->end = ft_strdup(line);
	room[room_nb].value = NOT_GIVEN;
	room[room_nb].status = OPENED;
	room[room_nb].neighb = NULL;
	room[room_nb].is_ant_inside = 3;
	str->end_room = &room[room_nb];
	room_nb++;
}

t_room		*make_struct_arr(void)
{
	t_room	*room;

	if (!(room = (t_room*)ft_memalloc(sizeof(t_room) * MAXV)))
		malloc_error();
	set_neighb(room);
	return (room);
}

void		make_neighb_list(t_room *rooms, char *line, t_room *room)
{
	t_nlist	*new;
	t_nlist	*temp;

	if (!(new = (t_nlist*)ft_memalloc(sizeof(t_nlist))))
		malloc_error();
	temp = room->neighb;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->room = find_room(line, rooms);
		new->status = OPENED;
		new->next = NULL;
	}
	else
	{
		room->neighb = new;
		new->room = find_room(line, rooms);
		new->status = OPENED;
		new->next = NULL;
	}
}

void		other_rooms(char *line, t_room *room)
{
	int	i;

	i = 0;
	while (line[i] != ' ')
		i++;
	line[i] = '\0';
	room[room_nb].name = ft_strdup(line);
	room[room_nb].value = NOT_GIVEN;
	room[room_nb].status = OPENED;
	room[room_nb].is_ant_inside = 0;
	room_nb++;
}
