/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:18:00 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/03/09 17:18:00 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static char	*free_null(char *buf)
{
    while (*buf)
    {
        *buf = '\0';
        buf++;
    }
    return (NULL);
}

static char	*get_read(char *save, int fd)
{
    char    *buf;
    int     size;

    buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)); //saveに保存するからmallocは一回で大丈夫
    if (!buf)
        return (NULL);
    while (!ft_strchr (save, '\n'))
    {
        size = read (fd, buf, BUFFER_SIZE); //bufにreadしたものが保存されている
        if (size == 0)
            break ;
        if (size == -1)
            return (free_null (buf));
        buf [size] = '\0';
        save = ft_strjoin (save, buf); //saveにbufをくっつけ、それをsaveに保存
    }
    free_null(buf);
    return (save);
}

static char	*put_line(char *save)
{
    int     count;
    char    *line;

    if (!save)
        return (NULL);
    count = 0;
    while (save[count] && save[count] != '\n')
        count++;
    if (save[count] == '\n')
        count++;
    line = ft_substr (save, 0, count);
    if (!line)
        return (free_null(save));
    if (*line == 0)
		return (free_null(line));
    return (line);
}

static char	*save_prepare(char *save)
{
    int  max;
    int  count;
    char    *temp;

    if (!save)
        return (NULL);
    count = 0;
    max = ft_strlen (save);
    while (save[count] && save[count] != '\n')
        count++;
    if (save[count] == '\n')
        count++;
    temp = ft_substr (save, count, max - count);
    free_null (save);
    if (!temp)
        return (NULL);
    return (temp);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    save = get_read (save, fd);//BUFFER_SIZEをreadする&&saveに保存
    if (!save)
        return (NULL);
    line = put_line(save); //出力するもの
    save = save_prepare(save); //前のsaveを預かる
    return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	line = "";
	fd = open("abc.txt", O_RDONLY);
	while (line)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
    close (fd);
	return (0);
}
