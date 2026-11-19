/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavryk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 22:12:47 by alavryk           #+#    #+#             */
/*   Updated: 2026/11/19 02:40:24 by alavryk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_clean(char *stash)
{
	size_t		i;
	size_t		j;
	char		*new_stash;

	if (!stash)
		return (NULL);
	if (ft_strchr(stash, '\n') == NULL)
		return (free(stash), NULL);
	i = 0;
	while (stash[i] != '\n')
		i++;
	i++;
	if (ft_strlen(stash) == i)
		return (free(stash), NULL);
	new_stash = malloc((ft_strlen(stash) - i + 1) * sizeof(char));
	if (!new_stash)
		return (free(stash), NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	return (free(stash), new_stash);
}

static char	*ft_strim(char *stash)
{
	size_t		len;
	char		*res;
	size_t		i;

	if (!stash)
		return (NULL);
	len = 0;
	while (stash[len] != '\0' && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = stash[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char	*read_stash(char *stash, int fd, char *buffer)
{
	ssize_t	read_bytes;

	read_bytes = 1;
	while (ft_strchr(stash, '\n') == NULL && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(stash), free(buffer), NULL);
		buffer[read_bytes] = '\0';
		stash = ft_join_and_free(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
	}
	return (free(buffer), stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[MX_FD];
	char		*buffer;
	char		*line;

	if (BUFFER_SIZE < 1 || fd < 0 || fd >= MX_FD)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	stash[fd] = read_stash(stash[fd], fd, buffer);
	if (!stash[fd] || !(*stash[fd]))
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	line = ft_strim(stash[fd]);
	if (!line)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	stash[fd] = ft_clean(stash[fd]);
	return (line);
}
