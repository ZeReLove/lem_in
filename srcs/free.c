/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 13:43:53 by mrolfe            #+#    #+#             */
/*   Updated: 2019/08/07 19:47:42 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_pathlist(t_path *path, t_plist *plist)
{
	t_path	*tmp;
	t_plist	*tmp2;

	while (plist)
	{
		tmp2 = plist;
		while (path)
		{
			tmp = path;
			path = path->next;
			free(tmp);
		}
		plist = plist->next;
		free(tmp2);
	}
}

void		free_path(t_plist *plist)
{
	t_plist	*tmp;
	t_path	*tmp2;
	t_path	*path;

	tmp = plist;
	while (tmp->next->next)
		tmp = tmp->next;
	path = tmp->next->path;
	while (path)
	{
		tmp2 = path;
		path = path->next;
		free(tmp2);
	}
	free(tmp->next);
	tmp->next = NULL;
}

static void	free_data(t_data *str)
{
	free(str->end_room->name);
	free(str->start_room->name);
	free(str->start);
	free(str->end);
	free(str->delta);
}

void		free_neighb_list(t_room *room, t_data *str)
{
	int		i;
	t_nlist	*tmp;
	t_nlist	*tmp2;

	i = 0;
	while (i < room_nb)
	{
		tmp = room[i].neighb;
		free(room[i++].name);
		while (tmp)
		{
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2);
		}
	}
	free(room);
	free_data(str);
}