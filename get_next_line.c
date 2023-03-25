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
	free(buf);
	buf = NULL;
	return (NULL);
}

static char	*get_read(char *save, int fd)
{
	char	*buf;
	int		size;
	char	*tmp;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)); //saveに保存するからmallocは一回で大丈夫
	if (!buf)
		return (NULL);
	size = 1;
	while (!ft_strchr (save, '\n') && size != 0)
	{
		size = read (fd, buf, BUFFER_SIZE);//bufにreadしたものが保存されている
		if (size == -1)
		{
			free_null(save);
			return (free_null (buf));
		}
		buf [size] = '\0';
		tmp = ft_strjoin (save, buf); //saveにbufをくっつけ、それをsaveに保存
		if (!save)
			free(save);
		save = tmp;
		if (size == 0 && save[0]=='\0')
		{
			free(buf);
			free(save);
			return (NULL);
		}
	}
	free_null(buf);
	return (save);
}

static char	*put_line(char *save)
{
	int		count;
	char	*line;

	if (!save)
		return (NULL);
	count = 0;
	while (save[count] && save[count] != '\n')
		count++;
	if (save[count] == '\n')
		count++;
	if (ft_strchr(save, '\n') == NULL)
		return (ft_strdup(save));
	line = ft_substr (save, 0, count);
	if (!line)
	{
		free_null(line);
		return (free_null(save));
	}
	if (line[0] == '\0')
	{
		return (free_null(line));
	}
	return (line);
}

static char	*save_prepare(char *save)
{
	int		max;
	int		count;
	char	*temp;

	if (save == NULL)
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
	if (save == NULL)
		return (NULL);
	line = put_line(save); //出力するもの
	save = save_prepare(save); //前のsaveを預かる
	return (line);
}

// __attribute__((destructor))
// static void destructor(void){
// 	system("leaks -q gnl");
// }

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	line = "";
// 	fd = open("abc.txt", O_RDONLY);
// 	// while ((line = get_next_line(fd)) != NULL)
// 	// {
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// }
// 	printf("return %s\n", get_next_line(fd));
// 	// printf("return %s\n", get_next_line(fd));
// 	close (fd);
// 	system("leaks -q a.out");
// 	return (0);
// }
