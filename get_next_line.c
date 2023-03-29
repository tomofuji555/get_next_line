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
#include <limits.h>

static char	*free_null(char *buf, char *save)
{
	if (buf)
	{
		free (buf);
		buf = NULL;
	}
	if (save)
	{
		free (save);
		buf = NULL;
	}
	return (NULL);
}

static char	*get_read(char *save, int fd)
{
	char		*buf;
	ssize_t		size;
	char		*tmp;

	buf = (char *)malloc(sizeof(char) * ((BUFFER_SIZE + (size_t) 1)));
	if (!buf)
		return (NULL);
	size = 1;
	while (!ft_strchr (save, '\n') && size != 0)
	{
		size = read (fd, buf, BUFFER_SIZE);
		if (size == -1)
			return (free_null(buf, save));
		buf [size] = '\0';
		tmp = ft_strjoin (save, buf);
		save = tmp;
		if (size == 0 && save[0] == '\0')
			return (free_null(buf, save));
	}
	free_null(buf, NULL);
	return (save);
}

static char	*put_line(char *save)
{
	size_t	count;
	char	*line;

	if (!save)
		return (NULL);
	count = 0;
	while (save[count] && save[count] != '\n')
		count++;
	if (save[count] == '\n')
		count++;
	if (!ft_strchr(save, '\n'))
		return (ft_strdup(save));
	line = ft_substr (save, 0, count);
	if (!line)
		return (free_null(line, save));
	if (line[0] == '\0')
		return (free_null(line, NULL));
	return (line);
}

static char	*save_prepare(char *save)
{
	size_t	max;
	size_t	count;
	char	*temp;

	if (!save)
		return (NULL);
	count = 0;
	max = ft_strlen (save);
	while (save[count] && save[count] != '\n')
		count++;
	if (save[count] == '\n')
		count++;
	temp = ft_substr (save, count, max - count);
	free_null (NULL, save);
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
	save = get_read (save, fd);
	if (!save)
		return (NULL);
	line = put_line(save);
	save = save_prepare(save);
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
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	 }
// 		printf("%zu", (size_t)(-1));

// 	// printf("return %s\n", get_next_line(fd));
// 	// printf("return %s\n", get_next_line(fd));
// 	close (fd);
// 	// system("leaks -q a.out");
// 	return (0);
// }
