/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:25:07 by mrolfe            #+#    #+#             */
/*   Updated: 2019/07/10 14:46:17 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

# define 			MAXV 7000   /*максимальное количество вершин */
# define			OPENED 1
# define			CLOSED 0
# define			

int					room_nb;
int					n_ant;
int					index;
int					index2;
int					index3;


typedef struct		s_room //ячейка массива структур комнат
{
	char			*name;
	t_list			*neighb;
	int				status;
	int				is_ant_inside;
}					t_room;

typedef struct		s_list // ячейка списка соседей
{
	t_room			*neighbour;
	struct s_list	*next;		
}					t_list;

typedef struct	s_reading_data
{
    int				amount_of_ants;
    t_room			*start_room;
    t_room			*end_room;
	int				ants_in_the_end_room;
}					t_data;

typedef struct		s_path	
{
	t_room			*room;
	struct s_path	*next;
}					t_path;

typedef struct 		s_plist
{
	t_path			*path;
	struct s_plist	*next;
}					t_plist;

typedef struct		s_array
{
	int				num_of_steps;
	int				num_of_pathes;
}					t_array;




void			make_neigb_list(t_room *room, t_room *rooms, char *line);

#endif
