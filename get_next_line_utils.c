/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:18:12 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/03/09 17:18:12 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen (const char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (s + i);
		i++;
	}
	if (!(char)c)
		return (s + i);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		return (ft_strdup (s2));
	if (!s2)
		return (NULL);
	str = (char *) malloc ((sizeof (char))
			* (ft_strlen (s1)) + (ft_strlen (s2)) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		str[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_strdup(const char *src)
{
	size_t	i;
	char	*a;

	i = 0;
	a = ((char *)malloc(ft_strlen(src) * sizeof(char) + 1));
	if (!a)
		return (NULL);
	while (src[i] != '\0')
	{
		a[i] = src[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (len == 0 || start >= ft_strlen(s))
		return (ft_strdup (""));
	if (len > ft_strlen (s) - start)
		len = ft_strlen (s) - start;
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
