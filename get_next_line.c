/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:02:46 by edawood           #+#    #+#             */
/*   Updated: 2022/10/13 17:44:55 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*ft_new_line(char *file)
{
	char	*buf;
	int		i;

	i = 0;
	if (!file)
		return (NULL);
	while (file[i] != '\n' && file[i] != '\0')
		i++;
	buf = (char *)ft_calloc(i + 2, sizeof(char));
	if (!buf)
		return (NULL);
	i = 0;
	while (file[i] != '\n' && file[i] != '\0')
	{
		buf[i] = file[i];
		i++;
	}
	if (file[i] == '\n')
		buf[i] = file[i];
	return (buf);
}

static	char	*ft_save(char *file)
{
	char	*remined_in_file;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (file[i] && file[i] != '\n')
		i++;
	if (!file[i])
	{
		free(file);
		return (NULL);
	}
	remined_in_file = ft_calloc(ft_strlen(file) - i + 1, sizeof(char));
	if (!remined_in_file)
		return (NULL);
	i++;
	while (file[i])
	{
		remined_in_file[j] = file[i];
		i++;
		j++;
	}
	free(file);
	return (remined_in_file);
}

static	char	*ft_read(char *file, int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	bytes_read = 1;
	while (!ft_strchr(file, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		file = ft_strjoin(file, buffer);
		if (file == NULL || file[0] == '\0')
		{
			free(file);
			return (NULL);
		}
	}
	return (file);
}

char	*get_next_line(int fd)
{
	char				*line;
	static char			*file;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	file = ft_read(file, fd);
	if (!file)
		return (NULL);
	line = ft_new_line(file);
	file = ft_save(file);
	return (line);
}
