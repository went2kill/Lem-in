/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 20:51:43 by yrobotko          #+#    #+#             */
/*   Updated: 2017/09/17 21:03:11 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void f_strjoin(char **str, char *st)
{
    char *s;
    
    s = *str;
    *str = ft_strjoin(*str, st);
    free(s);
    s = *str;
    *str = ft_strjoin(*str, "\n");
    free(s);
}

void    get_lem_num(t_lem *lem, char **s)
{
    char *str;
    
    while (lem->lem_num == -1)
    {
        get_next_line(0, &str);
        f_strjoin(s, str);
        if (is_digit_str(str)) {
            if (ft_atoi(str) <= 0)
                error();
            lem->lem_num = ft_atoi(str);
        } else
            read_input(lem, str);
    }
}

int in_queue(t_queue *queue, int id)
{
    while (queue)
    {
        if (queue->id_room == id)
            return (1);
        queue = queue->next;
    }
    return (0);
}

int get_next(t_queue *q, int fl, t_lem *lem)
{
    int id;
    
    while (q->is_visited == 1 && q->next)
        q = q->next;
    id = q->id_room;
    if (fl == 1)
        ft_printf("Get next from queue: %s\n", get_name(lem, id));
    return (id);
}

void bfs(t_lem *lem)
{
    t_queue *queue;
    int id;
    int i;
    
    queue = new_queue(NULL, lem->start_id);
    while (queue)
    {
        id = get_next(queue, lem->show_info, lem);
        queue->is_visited = 1;
        lem->visited[id] = 1;
        if (id == lem->end_id)
            break;
        i = -1;
        while (++i < lem->rooms_num)
            if (lem->ms[id][i] == 1 && lem->visited[i] != 1 && !in_queue(queue, i))
            {
                add_in_queue(queue, i, lem->show_info, lem);
                lem->path[i] = id;
            }
        if (!queue->next)
            error();
        queue = queue->next;
    }
}
