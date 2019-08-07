/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:15:43 by mrolfe            #+#    #+#             */
/*   Updated: 2019/08/06 14:15:56 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		find_room2(t_path *path, t_room *room)
{
	t_nlist	*tmp;

	tmp = room->neighb;
	while (tmp)
	{
		if (ft_strequ(tmp->room->name, path->room->name))
		{
			tmp->status = BLOCKED;
			return ;
		}
		tmp = tmp->next;
	}
}

int			find_room3(t_path *path, t_room *room)
{
	t_nlist	*tmp;
	int		count;

	count = 0;
	tmp = path->room->neighb;
	while (tmp)
	{
		if (ft_strcmp(tmp->room->name, room->name))
		{
			if (tmp->status == BLOCKED)
				find_room4(tmp, path, room, &count);
			break ;
		}
		tmp = tmp->next;
	}
	if (count != 0)
		return (1);
	return (0);
}

void		find_room4(t_nlist *tmp, t_path *path, t_room *room, int *count)
{
	tmp->status = DELETED;
	(*count)++;
	tmp = room->neighb;
	while (tmp)
	{
		if (ft_strcmp(path->room->name, tmp->room->name))
		{
			tmp->status = DELETED;
			break ;
		}
		tmp = tmp->next;
	}
}
