/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 12:06:41 by mrolfe            #+#    #+#             */
/*   Updated: 2019/08/06 14:14:36 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_plist		*algorithm(t_room *start, t_room *finish, t_room *arr)
{
	t_path	*path;
	t_plist	*plist;
	int		index;
	t_plist	*first;

	plist = NULL;
	index = 0;
	path = NULL;
	first = NULL;
	while (cutting_path(start, finish, first, &index))
	{
		while (width_search(start, finish, &path))
		{
			clean_values(arr);
			plist = make_path_list(plist, path);
			if (index == 0)
			{
				first = plist;
				index = 1;
			}
		}
	}
	return (first);
}

int			cutting_path(t_room *start, t_room *finish, t_plist *plist,
							int *index)
{
	t_plist	*tmp;
	t_path	*new;

	new = NULL;
	tmp = plist;
	if (plist)
	{
		unblock_rooms(tmp);
		block_direction(tmp, start);
		while (tmp->next)
			tmp = tmp->next;
		if (!width_search(start, finish, &new))
			return (0);
		make_path_list(tmp, new);
		if (!both_directions(tmp->next, start))
		{
			free_path(plist);
			return (0);
		}
		unblock_direction(plist, start);
		free_pathlist((plist)->path, plist);
		*index = 0;
		plist = NULL;
	}
	return (1);
}

int			both_directions(t_plist *plist, t_room *start)
{
	t_path	*tmp;
	t_room	*tmp2;
	int		count;

	count = 0;
	tmp = plist->path;
	tmp2 = start;
	while (tmp)
	{
		if (find_room3(tmp, tmp2))
			count++;
		tmp2 = tmp->room;
		tmp = tmp->next;
	}
	if (count != 0)
		return (1);
	return (0);
}

int			width_search(t_room *start, t_room *finish, t_path **path)
{
	int		val;
	t_nlist	*current;

	current = finish->neighb;
	start->value = 0;
	if (!give_values(&start, finish, 1))
		return (0);
	*path = make_path(NULL, finish, 0);
	val = finish->value;
	while (val != 1)
	{
		while (current->room->value != val - 1)
			current = current->next;
		*path = make_path(*path, current->room, 1);
		current = current->room->neighb;
		val--;
	}
	return (1);
}
