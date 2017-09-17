/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 20:51:55 by yrobotko          #+#    #+#             */
/*   Updated: 2017/09/17 20:51:57 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char *get_name(t_lem *lem, int id)
{
    t_room *room;
    
    room = lem->rooms;
    while (room)
    {
        if (room->id == id)
            return (room->room_name);
        room = room->next_room;
    }
    free(room);
    return (0);
}

int is_link(t_lem *lem, char *str)
{
    char **spl;
    int x, y;
    
    spl = fft_strsplit(str, '-');
    if (!spl || spl[0] == 0 || spl[1] == 0 ||
        lem->start_id == -1 || lem->end_id == -1)
        return (0);
    if (lem->is_link_begin == 0)
        mall_matrix(lem);
    if (get_id(lem, spl[0]) == -1 || get_id(lem, spl[1]) == -1)
        error();
    x = get_id(lem, spl[0]);
    y = get_id(lem, spl[1]);
    lem->ms[x][y] = 1;
    lem->ms[y][x] = 1;
    return (1);
}

int start_end(t_lem *lem, char *str)
{
    if (ft_strequ(str, "##start") && lem->is_start == -1)
        error();
    if (ft_strequ(str, "##end") && lem->is_end == -1)
        error();
    if (ft_strequ(str, "##start"))
        return (1);
    if (ft_strequ(str, "##end"))
        return (2);
    return (0);
}

void read_part2(t_lem *lem, char *str)
{
    if (is_comment(str))
    {
        free(str);
        return ;
    }
    if (start_end(lem, str) == 1)
    {
        lem->is_start = 1;
        return ;
    }
    if (start_end(lem, str) == 2)
    {
        lem->is_end = 1;
        return ;
    }
    if (room_ok(lem, str))
    {
        is_room(lem);
        return ;
    }
    if (is_link(lem, str))
        return ;
    error();
}

void read_input(t_lem *lem, char *str)
{
    if (ft_strequ(str, "##show_info"))
    {
        lem->show_info = 1;
        return ;
    }
    if (ft_strequ(str, "##show_len"))
    {
        lem->show_len = 1;
        return ;
    }
    if (ft_strequ(str, "##show_path"))
    {
        lem->show_path = 1;
        return ;
    }
    if (ft_strequ(str, "##show_steps"))
    {
        lem->show_steps = 1;
        return ;
    }
    read_part2(lem, str);
}
