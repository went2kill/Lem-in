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
    return (ret_lem);
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
    if (count_space != 3)
        return (0);
    return (1);
}

void is_room(t_lem *lem, char *str) {
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
    if (room->id != -1) {
        room->next_room = new_room();
        room = room->next_room;
    }
    room->room_name = lem->tmp_rname;
    room->rx = lem->tmp_rx;
    room->ry = lem->tmp_ry;
    room->id = pr_room->id + 1;
    if (lem->is_start == 1) {

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
    int i;

    i = 0;
    lem->is_link_begin = 1;
    lem->ms = (int**)malloc(sizeof(int*) * lem->rooms_num);
    while (i <= lem->rooms_num)
    {
        lem->ms[i] = (int*)malloc(sizeof(int) * lem->rooms_num);
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

int is_link(t_lem *lem, char *str)
{
    char **spl;
    int x,y;

    spl = fft_strsplit(str, '-');
    if (!spl || spl[0] == 0 || spl[1] == 0)
        return (0);
    if (lem->is_link_begin == 0)
        mall_matrix(lem);
    ft_printf("%s - %s\n", spl[0], spl[1]);
    if (get_id(lem, spl[0]) == -1 || get_id(lem, spl[1]) == -1)
        error();
    x = get_id(lem, spl[0]);
    y = get_id(lem, spl[1]);
    lem->ms[x][y] = 1;
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
        is_room(lem, str);
        ft_printf("VALID ROOM\n");
        return;
    }
    if (is_link(lem, str))
    {
        ft_printf("LINK OK\n");
        return;
    }
    ft_printf("hz cho eto\n");
}

void get_lem_num(t_lem *lem)
{
    char *str;

    get_next_line(0, &str);
    if (is_digit_str(str))
        lem->lem_num = ft_atoi(str);
    else
        error();
}

void strjoin(char **str, char *st)
{
    char *s;

    s = *str;
    *str = ft_strjoin(*str, st);
    free(s);
    s = *str;
    *str = ft_strjoin(*str, "\n");
    free(s);
}

void print_link(int **ms)
{
    int i, j;

    i = 0;
    j = 0;
    while (i < 5)
    {
        j = 0;
        while (j < 5)
        {
            ft_printf("%d", ms[i][j]);
            j++;
        }
        ft_printf("\n");
        i++;
    }
}

void list_print(t_room *room)
{
    while (room)
    {
        ft_printf("\nroom_id = %d  %s   x= %d y= %d is start ->%d<- is end ->%d<- ", room->id, room->room_name, room->rx, room->ry, room->is_start, room->is_end);
        room = room->next_room;
    }
}

int have_some_links(char **ms, int size, int x, int y)
{
    while (y < size)
    {
        x = 0;
        while (x < size)
        {
            if (ms[y][x] == 1)
                return (1);
            x++;
        }
        y++;
    }
    return (0);
}

void next_step(t_lem *lem)
{

}

int main()
{
    t_lem   *lem;
    char    *str;
    char    *s;

    lem = new_lem();
    get_lem_num(lem);
    s = ft_strnew(1);
    while (get_next_line(0, &str) && str[0] != '\0')    //////!!!!!!!!
    {
        if (ft_strequ(lem->prev_str, "##start") || ft_strequ(lem->prev_str, "##end"))
                if (!room_ok(lem, str))
                    error();
        if (lem->prev_str != 0)
            free(lem->prev_str);
        strjoin(s, str);
        lem->prev_str = ft_strdup(str);
        if (str[0] == '#' && str[1] == '#' && !ft_strequ(str, "##start") && !ft_strequ(str, "##end"))
            continue;
        read_input(lem, str);
    }
    list_print(lem->rooms);
    ft_printf("\n\n");
    print_link(lem->ms);
    ft_printf("%s", s);
    next_step(lem);
    return 0;
}