/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 20:57:50 by yrobotko          #+#    #+#             */
/*   Updated: 2017/09/17 20:57:53 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

size_t        count_w(const char *s, char c)
{
    size_t            i;
    size_t            count;
    
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

char            *paswd(const char *s, size_t len)
{
    char            *words;
    size_t            i;
    
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

char                **fft_strsplit(char const *s, char c)
{
    char            **str;
    size_t            i;
    size_t            j;
    
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
