/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 13:27:14 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/28 13:27:21 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
#define LEMIN_H

typedef struct          s_room
{
    char                *room_name;
    int                 id;
    int                 is_start;
    int                 is_end;
    int                 rx;
    int                 ry;
    struct s_room       *next_room;
}                       t_room;

typedef struct          s_lem
{
    int                 lem_num;
    int                 rooms_num;
    int                 start_id;
    int                 end_id;
    int                 is_start;
    int                 is_end;
    int                 **ms;
    t_room              *rooms;
    int                 tmp_rx;
    int                 tmp_ry;
    char                *tmp_rname;
    char                *prev_str;
    int                 is_link_begin;

}                       t_lem;

#endif
