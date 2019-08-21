/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:44:00 by mrolfe            #+#    #+#             */
/*   Updated: 2019/08/21 16:02:01 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int     checking_data(t_data *str) //нет проверки на на дубликаты. Надо ли?
{
    if (str->end_room->name && str->start_room->name)
    {
        if (ft_strequ(str->end_room->name, str->start_room->name))
            map_error();
    }
    if (str->amount_of_ants > 0 && str->start_room && str->end_room && room_nb > 2 && index_for_rc == 1)
        return (1);
    else
        map_error();
    return (0);
}

void     check(char *line, int fd, t_data *str, t_room *room, int *index) //норма
{
    int i;

    i = 2;
    if (line[0] == '#' && line[1] == '#')
    {
        if (ft_strequ(line, "##start") && idx_for_start == 0)
            read_start(line, fd, str, room);
        else if (ft_strequ(line, "##end") && idx_for_end == 0)
            read_end(line, fd, str, room);
        else
            return ;
    }
    else if (line[0] == '#' && line[1] != '#')
    {
        printf("%s\n", line);
        free(line);
        return ;
    }
    else if (checking_dash(line))
    {
        printf("%s\n", line);
        if (*index == 0)
            sorting_rooms(room, 0, room_nb - 1, str);
        *index = 1;
        room_connections(room, line);
        free(line);
    }
    else
    {
        check_room(&line);
        printf("%s\n", line);
        other_rooms(line, room);
    }
}

int     check_room(char **line)
{
    int i;
    int j;
    int count;

    i = 1;
    j = 0;
    count = 0;
    if (line[0][0] == 'L' || line[0][0] == '#')
        map_error();
    while (line[0][i] && line[0][i] != ' ')
        i++;
    while (line[0][i])
    {
        if (!((line[0][i] >= '0' && line[0][i] <= '9') || line[0][i] == ' '))
            map_error();
        if (line[0][i] == ' ')
            count++;
        i++;
    }
    if (count != 2)
        map_error();
    return (1);
}

int     check_ants(const int fd, char **line)
{
    int i;

    i = 0;
    if (!get_next_line(fd, line))
        map_error();
    if ((line[0][0] == '#' && line[0][1] == '#') || (line[0][0] == '#' && line[0][1] != '#'))
    {
        if (ft_strequ(*line, "##start") || ft_strequ(*line, "##end"))
            map_error();
        else
        //free(*line);
            get_next_line(fd, line);
    }
        
    while (line[0][i])
    {
        if (!(line[0][i] >= '0' && line[0][i] <= '9'))
            map_error();
        i++;
    }
    return (1);
}
