/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 20:52:04 by yrobotko          #+#    #+#             */
/*   Updated: 2017/09/17 20:52:06 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int room_ok(t_lem *lem, char *str)
{
    int count_space;
    char **spl;
    
    count_space = 0;
    if (*str == 'L' || ft_strchr(str, '-'))
        return (0);
    spl = fft_strsplit(str, ' ');
    if (!spl[1] || !is_digit_str(spl[1]) || !spl[2] || !is_digit_str(spl[2]))
        return (0);
    lem->tmp_rname = spl[0];
    if (spl[1])
        lem->tmp_rx = ft_atoi(spl[1]);
    if (spl[2])
        lem->tmp_ry = ft_atoi(spl[2]);
    while (spl[count_space])
        count_space++;
    if (count_space != 3 || lem->lem_num == -1)
        return (0);
    return (1);
}

void is_room_part2(t_lem *lem, t_room *room, t_room *pr_room)
{
    room->room_name = lem->tmp_rname;
    room->rx = lem->tmp_rx;
    room->ry = lem->tmp_ry;
    room->id = pr_room->id + 1;
    if (lem->is_start == 1)
    {
        
        room->is_start = 1;
        lem->start_id = room->id;
        lem->is_start = -1;
    }
    if (lem->is_end == 1)
    {
        room->is_end = 1;
        lem->end_id = room->id;
        lem->is_end = -1;
    }
    lem->rooms_num++;
}

void is_room(t_lem *lem)
{
    t_room *room;
    t_room *pr_room;
    
    room = lem->rooms;
    while (room != 0) {
        if (ft_strequ(room->room_name, lem->tmp_rname) ||
            (room->rx == lem->tmp_rx && room->ry == lem->tmp_ry))
            error();
        if (room->next_room == NULL)
            break;
        room = room->next_room;
    }
    if (lem->is_link_begin == 1)
        error();
    pr_room = room;
    if (room->id != -1)
    {
        room->next_room = new_room();
        room = room->next_room;
    }
    is_room_part2(lem, room, pr_room);
}

void mall_matrix(t_lem *lem)
{
    int i, j;
    
    i = 0;
    j = 0;
    lem->is_link_begin = 1;
    lem->ms = (int**)malloc(sizeof(int*) * lem->rooms_num);
    while (i < lem->rooms_num)
    {
        lem->ms[i] = (int*)malloc(sizeof(int) * lem->rooms_num);
        j = 0;
        while (j < lem->rooms_num)
        {
            lem->ms[i][j] = 0;
            j++;
        }
        i++;
    }
}

int get_id(t_lem *lem, char *str)
{
    t_room *room;
    
    room = lem->rooms;
    while (room)
    {
        if (ft_strequ(str, room->room_name))
            return (room->id);
        room = room->next_room;
    }
    free(room);
    return (-1);
}
