/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:14:02 by mrolfe            #+#    #+#             */
/*   Updated: 2019/08/07 20:00:09 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			give_values(t_room **start, t_room *finish, int cur_val)
{
	t_room	**queue;
	t_norm	norm;
	t_nlist	*tmp;

	tmp = (*start)->neighb;
	queue = give_values3(&norm, start);
	while (queue[norm.j] != NULL)
	{
		queue[(norm.j)++] = NULL;
		while (tmp)
		{
			if (tmp->room->value == NOT_GIVEN && tmp->room->status == OPENED &&
				tmp->status == OPENED)
			{
				queue[norm.i] = tmp->room;
				queue[(norm.i)++]->value = cur_val;
				if (check_finish(finish, queue[norm.i - 1]))
					return (give_values4(queue));
			}
			tmp = tmp->next;
		}
		give_values2(&norm, queue, &tmp, &cur_val);
	}
	free(queue);
	return (0);
}

t_room		**give_values3(t_norm *norm, t_room **start)
{
	t_room	**queue;

	norm->i = 0;
	norm->j = 0;
	norm->block = 1;
	queue = make_queue();
	queue[(norm->i)++] = *start;
	return (queue);
}

int			give_values4(t_room **queue)
{
	free(queue);
	return (1);
}

void		give_values2(t_norm *norm, t_room **queue, t_nlist **tmp,
				int *cur_val)
{
	if (norm->j == norm->block || norm->block == 1)
		(*cur_val)++;
	if (norm->j == norm->block)
		norm->block = norm->i;
	if (queue[norm->j])
		*tmp = queue[norm->j]->neighb;
}
