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

static int	partition(t_room *room, int low, int high)
{
	t_list pivot;
	int i;
	int j;

	i = (low - 1);
	pivot = room[high];
	j = low;
	while (j <= high - 1)
	{
		if (ft_strcmp(room[j]->name, room[pivot]->name) <= 0) //???
		{
			i++;
			ft_uniswap(&room[i], &room[j], t_room *room);
		}
		j++;
	}
	ft_uniswap(&room[i + 1], &room[high], t_room *room);
	return (i + 1);
}

void sorting_rooms(t_room *room)
{
	int low;
	int high;
	int pi;

	low = 0;
	high = room_nb;
	if (low < high)
	{
		pi = partition(room, low, high);
		quick_sort(room, low, pi - 1);
		quick_sort(room, pi + 1, high);
	}
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
    t_list *neighb;
	t_list *temp;

    i = 0;
    while (line[i] != '-')
        i++;
    i++;
    tmp = ft_strdup(*line);
    neighb = (t_list*)malloc(sizeof(t_list));
	temp = neighb;
	while (temp)
		temp = temp->next;
	temp->next->neighbour = tmp;
	temp->next->next = NULL;
}

void	clear_neigbouhrs_list(t_list *neighb)
{
	t_list *tmp;

	while (neighb)
	{
		tmp = neighb->next;
		free((void *)neighb);
		neighb = tmp;
	}
}

void algorithm()
{
	int value_of_ants;
	char *num_ant;
}


void	ants_printing(t_room *room, int value_of_ants, char *num_ant)
{
	int i;
	int j;

	i = 0;
	while (value_of_ants > 0)
	{
		if (room[i]->is_ant_inside == 1)
		{
			write(1, "L", 1);
			j = 0;
			while(num_ant[j])
				write(1, &num_ant[j++], 1);
			write(1, "-", 1);
			j = 0;
			while(room[j]->name)
				write(1, &name, 1);
			if (value_of_ants == 1)
				write(1, "\n", 1);
			else
				write(1, " ", 1);
			value_of_ants--;
		}
		i++;
	}
}

int number_of_pathes(t_data *read, t_plist *pointers, t_path *pathes)
{
	int num;
	int sum_p; // длина всех путей
	int num_p; // количество всех путей
	t_list *tmp;
	t_list *tmp2;

	tmp = pointers; // указатель для того, чтобы выяснить, сколько путей
	tmp2 = pathes; // указатель для суммы всех шагов всех путей
	while (tmp)
	{
		while (tmp2)
		{
			tmp2 = tmp2->next;
			sum_p += 1;
		}
		tmp = tmp->next;
		num_p += 1;
	}
	num = (read->amount_of_ants + sum_p - 1) / num_p;
	return (num);
}