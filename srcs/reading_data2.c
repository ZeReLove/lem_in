/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_data2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:17:53 by mrolfe            #+#    #+#             */
/*   Updated: 2019/08/06 14:18:26 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	check_start_finish(t_room *room1, t_room *room2, t_data *str)
{
	if (ft_strequ(room1->name, str->start))
		str->start_room = room1;
	else if (ft_strequ(room2->name, str->start))
		str->start_room = room2;
	if (ft_strequ(room1->name, str->end))
		str->end_room = room1;
	else if (ft_strequ(room2->name, str->end))
		str->end_room = room2;
}

static int	partition(t_room *room, int low, int high, t_data *str)
{
	t_room	pivot;
	int		i;
	int		j;

	i = (low - 1);
	pivot = room[high];
	j = low;
	while (j <= high - 1)
	{
		if (ft_strcmp(room[j].name, pivot.name) <= 0)
		{
			i++;
			ft_uniswap(&room[i], &room[j], sizeof(t_room));
			check_start_finish(&room[i], &room[j], str);
		}
		j++;
	}
	ft_uniswap(&room[i + 1], &room[high], sizeof(t_room));
	check_start_finish(&room[i + 1], &room[high], str);
	return (i + 1);
}

void		sorting_rooms(t_room *room, int low, int high, t_data *str)
{
	int pi;

	if (low < high)
	{
		pi = partition(room, low, high, str);
		sorting_rooms(room, low, pi - 1, str);
		sorting_rooms(room, pi + 1, high, str);
	}
}

t_room		*find_room(char *buff, t_room *room)
{
	int start;
	int end;
	int middle;
	int	res;

	start = 0;
	end = room_nb;
	while (start <= end)
	{
		middle = (start + end) / 2;
		res = ft_strcmp(room[middle].name, buff);
		if (res > 0)
			end = middle - 1;
		else if (res < 0)
			start = middle + 1;
		else
			return (&room[middle]);
	}
	map_error();
	return (NULL);
}

int			checking_dash(char *line)
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
