#include "lem_in.h"

void 	reading_data(t_data *str, char *line)
{
	int		i;
	t_room	*room;
	int index;

	index = 0;
	room = make_struct_arr();
	get_next_line(0, &line);
	if (line[0] == "#" && line[1] != '#')
		get_next_line(0, &line);
	str->amount_of_ants = ft_atoi(line);
	while (get_next_line(0, &line))
	{
		i = -1;
		if (line[0] == "#" && line[1] != '#')
			get_next_line(0, &line);
		else if (ft_strequ(line, "##start"))
		{
			get_next_line(0, &line);
			make_start(str, room, line)
		}
		else if (ft_strequ(line, "##end"))
		{
			get_next_line(0, &line);
			make_end(str, room, line);
		}
		else if (checking_dash(line))
			other_rooms(line, room);
		else
		{
			if (index == 0)
				sorting_rooms(room);
			rooms_connections(room, line);
			index = 1;
		}	
	}
}

void	room_connections(t_room *room, char *line)
{
	int		i;
	t_room	*r;

	i = 0;
	while (line[i] != ' ')
		i++;
	line[i] = '\0';
	r = find_room(ft_strdup(line), room);
	r.neigb = make_neighb_list(room, line);
}

void	sorting_rooms(t_room *room)
{
	int i;
	int j;
	int res;
	char *tmp;

	i = 0;
	j = 1;
	while (j != room_nb)
	{
		res = ft_strcmp(room->name[i], room->name[j])
		if (res > 0)
		{
			tmp = ft_strdup(room->name[j]);
			room->name[j] = ft_strdup(room->name[i]);
			room->name[i] = ft_strdup(tmp);
		}
		i++;
		j++;
	}
	if (!(is_sorted(room)))
		sorting_rooms(room);
	else
		return ;
}

int is_sorted(t_room *room)
{
	int i;

	i = 0;
	while (i < room_nb - 1)
	{
		if (ft_strcmp(room->name[i], room->name[i + 1]) < 0)
			i++;
		else
			return (0);
	}
	if (i == room_nb - 1)
		return (1);
	else
		return (0);
}

t_room	*find_room(char *buff, t_room *room)
{
	int start;
	int end;
	int middle;

	start = 0;
	end = room_nb;
	while (start <= end)
	{
		middle = (start + end) / 2;
		res = ft_strcmp(room->name[middle], buff);
		if (res > 0)
			end = middle - 1;
		if (res < 0)
			start = middle + 1;
		else
			return (room->name[middle]);
	}
}

void	make_start(t_data *str, t_room *room, char *line)
{
	room[room_nb].name = ft_strdup(line);
	str->start_room = &room[room_nb];
	room_nb++;
}

void	make_end(t_data *str, t_room *room, char *line)
{
	room[room_nb].name = ft_strdup(line);
	str->end_room = &room[room_nb];
	room_nb++;
}

t_room	*make_struct_arr()
{
	t_room	*room;

	if (!(room = (t_room*)malloc(sizeof(t_room) * 7001))
		return (NULL);
	return (room);
}

int		checking_dash(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

void	other_rooms(char *line, t_room *room)
{
	int	i;

	i = 0;
	while (line[i] != ' ')
		i++;
	line[i] = '\0';
	room[room_nb].name = ft_strdup(line);
	room_nb++;
}

t_list    *make_neighb_list(t_room *rooms, char *line)
{
    int i;
    char *tmp;
	char *save_pointer;
    t_list *neighb;

    i = 0;
    while (line[i] != '-')
        i++;
    i++;
    tmp = ft_strdup(*line);
    neighb = (t_list*)malloc(sizeof(t_list));
	if (flag == 1)
    	neighb->neighbour = find_room(save_pointer, rooms);
	else
		neighb->neighbour = find_room(tmp, rooms);
	save_pointer = ft_strdup(tmp);
	if (flag == 1)
		neighb->next = ft_strdup(tmp);
	else
		neighb->next = NULL;
	flag = 1;
}

void clear_neigbouhrs_list(t_list *neighb)
{
	t_list *tmp;

	while (neighb)
	{
		tmp = neighb->next;
		free((void *)neighb);
		neighb = tmp;
	}
}