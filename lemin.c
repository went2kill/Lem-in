/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 15:58:15 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/25 15:58:25 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void show_path(t_lem *lem, int *way, int len)
{
    int i = 0;
    
    ft_printf("Path: ");
    while (i < len - 1)
    {
        ft_printf("%s->", get_name(lem, way[i]));
        i++;
    }
    ft_printf("%s\n", get_name(lem, way[i]));
}

void show_way_len(int len)
{
    ft_printf("Path length: %d\n", len);
}

void show_steps(int len, int num)
{
    ft_printf("Count steps: %d", (len - 1) * num);
    
}

void part2(t_lem *lem)
{
    mall(lem, lem->rooms_num);
    bfs(lem);
    lem->way = make_way(lem, lem->path, 0);
    if (lem->show_path)
        show_path(lem, lem->way, lem->way_len);
    lem->lets_go = get_way(lem->way, lem);
    if (lem->show_len)
        show_way_len(lem->way_len);
    if (lem->way_len == 2)
        print_all_end(lem, lem->end_id, lem->lem_num);
    else
        go_go_lem(lem->lets_go, lem->lem_num);
    if (lem->show_steps)
        show_steps(lem->way_len, lem->lem_num);
}

int main()
{
    t_lem   *lem;
    char    *str;
    char    *s;
    
    lem = new_lem();
    s = ft_strnew(1);
    get_lem_num(lem, &s);
    while (get_next_line(0, &str) > 0)   ///!DONT FORGET!!!!
    {
        if (ft_strequ(lem->prev_str, "##start") || ft_strequ(lem->prev_str, "##end"))
            if (!room_ok(lem, str))
                error();
        if (lem->prev_str != 0)
            free(lem->prev_str);
        f_strjoin(&s, str);
        lem->prev_str = ft_strdup(str);
        read_input(lem, str);
        if (str[0] == '#' && str[1] == '#' && !ft_strequ(str, "##start") && !ft_strequ(str, "##end"))
            continue;
    }
    part2(lem);
    return 0;
}
