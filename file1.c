/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 20:51:33 by yrobotko          #+#    #+#             */
/*   Updated: 2017/09/17 20:51:36 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void mall(t_lem *lem, int count)
{
    int  i;
    
    i = 0;
    if (lem->is_link_begin != 1)
        error();
    lem->visited = (int*)malloc(sizeof(int) * count);
    lem->path = (int*)malloc(sizeof(int) * count);
    while (i < count)
    {
        lem->visited[i] = 0;
        lem->path[i] = 0;
        i++;
    }
}

int do_some(t_lem *lem, int *path, int i, int **w)
{
    int j;
    
    j = 0;
    while (path[i] != i)
    {
        if (i != lem->start_id)
        {
            (*w)[j] = i;
            j++;
        }
        if (!path[i])
        {
            (*w)[j] = lem->start_id;
            j++;
            break;
        }
        i = path[i];
    }
    return (j);
}

int *make_way(t_lem *lem, int *path, int *way)
{
    int i;
    int j;
    int *w;
    
    w = (int*)malloc(sizeof(int) * lem->rooms_num);
    i = -1;
    while (++i < lem->rooms_num)
        w[i] = -1;
    i = lem->end_id;
    j = do_some(lem, path, i, &w);
    lem->way_len = j;
    way = (int*)malloc(sizeof(int) * j);
    i = -1;
    while (i < lem->way_len && j > 0)
        way[++i] = w[--j];
    return (way);
}

t_way *new_way(int id, char *name)
{
    t_way *ret;
    
    ret = (t_way*)malloc(sizeof(t_way));
    ret->id = id;
    ret->name = ft_strdup(name);
    ret->lem_num = 0;
    ret->finish = 0;
    ret->next = 0;
    return (ret);
}

t_way *get_way(int *way, t_lem *lem)
{
    
    int i;
    t_way *ret;
    t_way *r;
    
    r = new_way(way[1], get_name(lem, way[1]));
    ret = r;
    i = 2;
    while (i < lem->way_len)
    {
        r->next = new_way(way[i], get_name(lem, way[i]));
        r = r->next;
        i++;
    }
    return (ret);
}
