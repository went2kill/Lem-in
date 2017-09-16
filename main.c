#include <stdio.h>
#include "libft.h"
#include "lemin.h"

static size_t		words_len(const char *s, char c)
{
    size_t			i;

    i = 0;
    while (s[i] != '\0' && s[i] != c)
        i++;
    return (i);
}

static size_t		count_w(const char *s, char c)
{
    size_t			i;
    size_t			count;

    i = 0;
    count = 0;
    while (s[i] != '\0')
    {
        while ((s[i] == c) && s[i] != '\0')
            i++;
        if (s[i])
            count++;
        while (s[i] != c && s[i] != '\0')
            i++;
    }
    return (count);
}

static char			*paswd(const char *s, size_t len)
{
    char			*words;
    size_t			i;

    i = 0;
    if ((words = (char *)malloc(sizeof(char *) * (len + 1))) == NULL)
        return (NULL);
    while (i < len)
    {
        words[i] = s[i];
        i++;
    }
    words[i] = '\0';
    return (words);
}

char				**fft_strsplit(char const *s, char c)
{
    char			**str;
    size_t			i;
    size_t			j;

    i = 0;
    j = 0;
    if (s == NULL)
        return (NULL);
    if (!(str = (char **)malloc(sizeof(char *) * (count_w(s, c) + 1))))
        return (NULL);
    while (i < count_w(s, c))
    {
        while ((s[j] == c))
            j++;
        if ((str[i] = paswd(s + j, words_len(s + j, c))) == NULL)
            return (NULL);
        while (s[j] != c && s[j])
            j++;
        i++;
    }
    str[i] = 0;
    return (str);
}


void error(void)
{
    ft_printf("ERROR");
    exit(0);
}

t_room *new_room(void)
{
    t_room *ret_room;

    ret_room = (t_room*)malloc(sizeof(t_room));
    ft_bzero(ret_room, sizeof(t_room));
    return (ret_room);
}

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

void add_in_queue(t_queue *q, int id)
{
    while (q->next != 0)
        q = q->next;
    q->next = new_queue(q, id);
}

int is_coment(char *str)
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
    if (!spl || spl[0] == 0 || spl[1] == 0 || lem->start_id == -1 || lem->end_id == -1)
        return (0);
    if (lem->is_link_begin == 0)
        mall_matrix(lem);
    ft_printf("%s - %s\n", spl[0], spl[1]);
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

void read_input(t_lem *lem, char *str)
{
    if (is_coment(str))
    {
        free(str);
        return;
    }
    if (start_end(lem, str) == 1)
    {
        lem->is_start = 1;
        return;
    }
    if (start_end(lem, str) == 2)
    {
        lem->is_end = 1;
        return;
    }
    if (room_ok(lem, str))
    {
        is_room(lem);
        return;
    }
    if (is_link(lem, str))
        return;
    error();
}

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

int get_next(t_queue *q)
{
    int id;

    while (q->is_visited == 1 && q->next)
        q = q->next;
    id = q->id_room;
    return (id);
}

void bfs(t_lem *lem)                              /////
{
    t_queue *queue;
    int id;
    int i;

    queue = new_queue(NULL, lem->start_id);
    while (queue)
    {
        id = get_next(queue);
        queue->is_visited = 1;
        lem->visited[id] = 1;
        if (id == lem->end_id)
            break;
        i = -1;
        while (++i < lem->rooms_num)
            if (lem->ms[id][i] == 1 && lem->visited[i] != 1 && !in_queue(queue, i))
            {
                add_in_queue(queue, i);
                lem->path[i] = id;
            }
        if (!queue->next)
            error();
        queue = queue->next;
    }
}

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

int *make_way(t_lem *lem, int *path, int *way)
{
    int i, j, *w;

    w = (int*)malloc(sizeof(int) * lem->rooms_num);
    i = -1;
    while (++i < lem->rooms_num)
        w[i] = -1;
    i = lem->end_id;
    j = 0;
    while (path[i] != i)
    {
        ft_printf("%d %d\n",w[j], i);
        if (i != lem->start_id)
        {
            w[j] = i;
            j++;
        }
        if (!path[i])
        {
            w[j] = lem->start_id;
            ft_printf("%d %d\n",w[j], i);
            j++;
            break;
        }
        i = path[i];
    }
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
    ft_printf("Way length: %d\n", len);
}

void part2(t_lem *lem)
{
    mall(lem, lem->rooms_num);
    bfs(lem);
    lem->way = make_way(lem, lem->path, 0);
    show_path(lem, lem->way, lem->way_len);
    lem->lets_go = get_way(lem->way, lem);
    show_way_len(lem->way_len);
    if (lem->way_len == 2)
        print_all_end(lem, lem->end_id, lem->lem_num);
    else
        go_go_lem(lem->lets_go, lem->lem_num);
}

int main()
{
    t_lem   *lem;
    char    *str;
    char    *s;

    lem = new_lem();
    s = ft_strnew(1);
    get_lem_num(lem, &s);
    while (get_next_line(0, &str) && str[0] != '\0')   ///!DONT FORGET!!!!
    {
        if (ft_strequ(lem->prev_str, "##start") || ft_strequ(lem->prev_str, "##end"))
                if (!room_ok(lem, str))
                    error();
        if (lem->prev_str != 0)
            free(lem->prev_str);
        f_strjoin(&s, str);
        lem->prev_str = ft_strdup(str);
        if (str[0] == '#' && str[1] == '#' && !ft_strequ(str, "##start") && !ft_strequ(str, "##end"))
            continue;
        read_input(lem, str);
    }
    part2(lem);
    return 0;
}