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

typedef struct          s_queue
{
    int                 id_room;
    int                 is_visited;
    struct s_queue      *prev;
    struct s_queue      *next;
}                       t_queue;

typedef struct          s_way
{
    int                 id;
    char                *name;
    int                 lem_num;
    int                 finish;
    struct s_way        *next;
}                       t_way;

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
    t_way               *lets_go;
    t_room              *rooms;
    t_queue             *queue;
    int                 tmp_rx;
    int                 tmp_ry;
    char                *tmp_rname;
    char                *prev_str;
    int                 is_link_begin;

}                       t_lem;

static size_t		words_len(const char *s, char c);
static size_t		count_w(const char *s, char c);
static char			*paswd(const char *s, size_t len);
char				**fft_strsplit(char const *s, char c);
void error(void);
t_room *new_room(void);
t_lem *new_lem(void);
t_queue *new_queue(t_queue *prev, int id);
void add_in_queue(t_queue *q, int id);
int is_coment(char *str);
int is_digit_str(char *s);
int room_ok(t_lem *lem, char *str);
void is_room(t_lem *lem);
void mall_matrix(t_lem *lem);
int get_id(t_lem *lem, char *str);
char *get_name(t_lem *lem, int id);
int is_link(t_lem *lem, char *str);
int start_end(t_lem *lem, char *str);
void read_input(t_lem *lem, char *str);
void f_strjoin(char **str, char *st);
void    get_lem_num(t_lem *lem, char **s);
int in_queue(t_queue *queue, int id);
int get_next(t_queue *q);
void bfs(t_lem *lem);
void mall(t_lem *lem, int count);
int *make_way(t_lem *lem, int *path, int *way);
t_way *new_way(int id, char *name);
t_way *get_way(int *way, t_lem *lem);
int is_lem_here(t_way *way);
void shift_way(t_way *way, int lem_num, int curr);
void print_lem(t_way *way);
void go_go_lem(t_way *way, int lem_num);
void print_all_end(t_lem *lem, int id, int lem_num);
void show_path(t_lem *lem, int *way, int len);
void show_way_len(int len);
void part2(t_lem *lem);

#endif
