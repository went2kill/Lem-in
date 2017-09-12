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
    int                 is_visited;
    struct s_room       *next_room;
}                       t_room;

typedef struct          s_queue
{
    int                 id_room;
    int                 is_visited;
    struct s_queue      *prev;
    struct s_queue      *next;
}                       t_queue;

typedef struct          s_lem
{
    int                 way_len;
    int                 *way;
    int                 lem_num;
    int                 rooms_num;
    int                 start_id;
    int                 end_id;
    int                 is_start;
    int                 is_end;
    int                 *visited;
    int                 *path;
    int                 **ms;
    t_room              *rooms;
    t_queue             *queue;
    int                 tmp_rx;
    int                 tmp_ry;
    char                *tmp_rname;
    char                *prev_str;
    int                 is_link_begin;

}                       t_lem;

#endif
