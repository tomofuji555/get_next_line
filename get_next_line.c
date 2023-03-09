/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:58:34 by marvin            #+#    #+#             */
/*   Updated: 2023/03/04 23:58:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char  *free_null (char *buf)
{
    free (buf);
    while (*buf)
    {
        *buf = '\0';
        buf++;
    }
    return (NULL);
}

static char *get_store (char *save, int fd)
{
    char    *buf;
    char    *temp;
    int     size;

    buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buf)
        return (NULL);
    while (!ft_strchr (save, '\n'))
    {
        size = read (fd, buf, BUFFER_SIZE); //bufにreadしたものが保存されている
        if (size == 0)
            break;
        if (size == -1)
            return (free_null (buf));
        temp = ft_strjoin (save, buf);//saveにbufをくっつけ、それをsaveに保存
        if (!temp)
            return (free_null (buf));
        free_null (buf);
        buf = temp;
    }
    free_null (buf);
    return (save);
}

static char *put_line (char *save)
{
    int     count;
    char    *line;

    if (!save)
        return (NULL);
    count = 0;
    while (save[count] && save[count] != 'n')
        count++;
    if (save[count] == 'n')
        count++;
    line = ft_substr (save, 0, count + 1);
    if (!line)
        return (free_null(save));
    line[count + 1] = '\0';
    free_null (save);
    return (line);
}

static char *save_prepare (char *save)
{
    int     max;
    int     count;
    char    *temp;

    if (!save)
        return (NULL);
    count = 0;
    max = ft_strlen (save);
    save += 1;
    while (save[count] && save[count] != 'n')
        count++;
    if (save[count] == 'n')
        count++;
    temp = ft_substr (save, count, max - count);
    free_null (save);
    if (!temp)
        return (NULL);
    save = temp;
    return (save);
}

char    *get_next_line (int fd)
{
    static char *save;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    save = get_store (fd, save);//BUFFER_SIZEをreadする&&saveに保存
    line = put_line(save); //出力するもの
    save = save_prepare(save); //前のsaveを預かる
    return (line);
}