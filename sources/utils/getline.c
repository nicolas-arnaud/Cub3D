/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 21:23:40 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/21 22:51:16 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*save_buffer(char *buffer, int *i)
{
	int j;

	line = ft_calloc(512);
	j = 0;
	while (j < 512)
	{
		line[j++] = buffer[(*i)++];
		if (buffer[*i] == '\n')
			return (line)
	}
	return (ft_strjoin(line, save_buffer(buffer, i)));
}

char *get_next_line(int fd)
{
	static char	*buffer[BUFFER_SIZE];
	static int	i;
	ssize_t		read_size;
	char		*line;

	if (!*buffer)
		read_size = read(fd, buffer, BUFFER_SIZE);
	line = ft_calloc(1);
	while (read_size)
	{
		line = ft_strjoin(line, save_buffer(buffer, i));
		if (line[i] == '\n')
			return (line);
		read_size = read(fd, buffer, BUFFER_SIZE);
		i = 0;
	}
	if (*line)
		return (line);
	free(line);
	return (NULL);
}
