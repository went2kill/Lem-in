/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 20:52:26 by yrobotko          #+#    #+#             */
/*   Updated: 2017/09/17 20:52:33 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_lem *new_lem(void)
{
    t_lem   *ret_lem;
    
    ret_lem = (t_lem*)malloc(sizeof(t_lem));
    ft_bzero(ret_lem, sizeof(t_lem));
    ret_lem->rooms = new_room();
    ret_lem->rooms->id = -1;
    ret_lem->rooms->rx = -1;
    ret_lem->rooms->ry = -1;
    ret_lem->start_id = -1;
    ret_lem->end_id = -1;
    ret_lem->lem_num = -1;
    return (ret_lem);
}

t_queue *new_queue(t_queue *prev, int id)
{
    t_queue *ret_queue;
    
    ret_queue = (t_queue*)malloc(sizeof(t_queue));
    ret_queue->next = 0;
    ret_queue->is_visited = 0;
    ret_queue->id_room = id;
    ret_queue->prev = prev;
    return (ret_queue);
}

void add_in_queue(t_queue *q, int id, int fl, t_lem *lem)
{
    while (q->next != 0)
        q = q->next;
    q->next = new_queue(q, id);
    if (fl)
        ft_printf("Add in queue: %s\n", get_name(lem, id));
}

int is_comment(char *str)
{
    if (str[0] == '#' && str[1] != '#')
        return(1);
    return (0);
}

int is_digit_str(char *s)
{
    while (*s != '\0')
    {
        if (!ft_isdigit((int)*s))
            return (0);
        s++;
    }
    return (1);
}
