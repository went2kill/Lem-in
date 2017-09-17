/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 20:52:41 by yrobotko          #+#    #+#             */
/*   Updated: 2017/09/17 20:52:43 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int is_lem_here(t_way *way)
{
    while (way)
    {
        if (way->lem_num != 0)
            return (1);
        way = way->next;
    }
    return (0);
}

void shift_way(t_way *way, int lem_num, int curr)
{
    if (curr <= lem_num)
    {
        while (way && curr > 0) {
            way->lem_num = curr;
            curr--;
            way = way->next;
        }
        return ;
    }
    while (way && curr > lem_num)
    {
        if (way->lem_num == lem_num)
            way->lem_num = 0;
        else if (way->lem_num != 0)
            way->lem_num++;
        way = way->next;
    }
}

void print_lem(t_way *way)
{
    if (way->next)
        print_lem(way->next);
    if (way->lem_num)
        ft_printf("L%d-%s ", way->lem_num, way->name);
}

void go_go_lem(t_way *way, int lem_num)
{
    int i;
    
    i = 1;
    shift_way(way, lem_num, i);
    i++;
    while (is_lem_here(way))
    {
        print_lem(way);
        ft_printf("\n");
        shift_way(way, lem_num, i);
        i++;
    }
}

void print_all_end(t_lem *lem, int id, int lem_num)
{
    int i;
    
    i = 1;
    while (i <= lem_num)
    {
        ft_printf("L%d-%s ", i, get_name(lem, id));
        i++;
    }
}
