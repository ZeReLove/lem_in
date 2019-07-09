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
    tmp = ft_strdup(line);
    neighb = (t_list*)malloc(sizeof(t_list));
	temp = rooms->neighb;
	while (temp)
		temp = temp->next;
	temp->next = neighb;
	neighb->neighbour = find_room(tmp, rooms);
	neighb->next = NULL;
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

void ants_going_through_graph(t_plist *pointers, t_array *pathes, t_data *read) // нигде не плюсуются муравьи в конечной комнате
{
	int value_of_ants;
	int *array_num_ant;
	t_plist *tmp;
	t_path *tmp2;
	int		i;
	int		l;

	ft_bzero(); // is_ant_inside
	tmp = pointers;
	l = read->amount_of_ants;
	read->ants_in_the_end_room = 0;
	while (read->ants_in_the_end_room != l)
	{
		if (read->amount_of_ants > 0)
			moving_ants(pathes, array_num_ant, read, &value_of_ants, pointers);
		ants_printing(pointers, &value_of_ants);
		i = pathes->num_of_pathes;
		while (i--)
		{
			tmp2 = tmp->path;
			while (tmp2->room->is_ant_inside == 1 && tmp2->next)
				tmp2 = tmp2->next;
			tmp->path->room->is_ant_inside = 0;
			if (tmp2->next)
				tmp2->room->is_ant_inside == 1;
			tmp = tmp->next;
		}
	}

}

void		moving_ants(t_array *pathes, int *array_num_ant, t_data *read, int *value_of_ants, t_plist *plist) //не помечаются в массиве муравьи пришедшие к финишу
{
	int 	j;
	t_plist	*tmp;

	tmp = plist;
	j = pathes->num_of_pathes;
	while (j && read->amount_of_ants)
	{
		plist->path->room->is_ant_inside = 1;
		array_num_ant[index++] = ++n_ant;
		(read->amount_of_ants)--;
		value_of_ants++;
		j--;
		tmp = tmp->next;
	}
}

void		ants_printing(t_plist *plist, int *value_of_ants) // Проблемы с распечаткой. каждому муравью печатается не та комната
{
	int 	k;
	t_plist	*tmp;
	t_path	*tmp2;

	k = 0;
	tmp = plist;
	while (*value_of_ants > 0)
	{
		tmp2 = tmp->path;
		write(1, "L", 1);
		printf("%i", array_num_ant[k++]);
		write(1, "-", 1);
		while (tmp2->next->room->is_ant_inside != 0)
			tmp2 = tmp2->next;
		printf("%s", tmp2->room->name);
		tmp = tmp->next;
		if (*value_of_ants == 1)
			write(1, "\n", 1);
		else
			write(1, " ", 1);
		(*value_of_ants)--;
	}
}

void	creating_of_array(t_array *pathes)
{
	pathes = (t_array*)malloc(sizeof(t_array) * 2);
	pathes->num_of_steps = 0;
	pathes->num_of_pathes = 0;
}

int number_of_pathes(int *num_of_pathes, t_data *read, t_plist *pointers, t_array *pathes)
{
	int number_of_steps;
	int sum_p; // длина всех путей
	int num_p; // количество всех путей
	t_plist *tmp;
	t_array *tmp2;
	
	tmp = pointers; // указатель для того, чтобы выяснить, сколько путей
	while (tmp)
	{
		tmp2 = tmp->path;
		while (tmp2)
		{
			tmp2 = tmp2->next;
			sum_p += 1;
		}
		number_of_steps = (read->amount_of_ants + sum_p - 1) / num_p;
		tmp = tmp->next;
		num_p += 1;
		comparing_of_values(pathes, number_of_steps, num_p);
	}
	if (pathes[0]->num_of_pathes != 0)
		return (pathes[0]->num_of_pathes);
	else
		return (pathes[1]->num_of_pathes);
}

void	comparing_of_values(t_array *pathes, int number_of_steps, int num_p)
{

	if (pathes[0]->num_of_pathes == 0 && pathes[1]->num_of_pathes == 0)
	{
		pathes[0]->num_of_pathes = num_p;
		pathes[0]->num_of_steps = number_of_steps;
		return ;
	}
	else if (pathes[0]->num_of_pathes != 0 && pathes[1]->num_of_pathes == 0)
	{
		pathes[1]->num_of_pathes = num_p;
		pathes[1]->num_of_steps = number_of_steps;
	}
	else if (pathes[0]->num_of_pathes == 0 && pathes[1]->num_of_pathes != 0)
	{
		pathes[0]->num_of_pathes[0] = num_p;
		pathes[0]->num_of_steps = number_of_steps;
	}
	if (pathes[0]->num_of_pathes > pathes[1]->num_of_pathes)
	{
		pathes[0]->num_of_pathes = 0;
		pathes[0]->num_of_steps = 0;
	}
	else
	{
		pathes[1]->num_of_pathes = 0;
		pathes[1]->num_of_steps = 0;
	}
}