/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 21:23:40 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/22 05:00:06 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*save_buffer(char *buffer, int *i)
{
	int		j;
	char	*part1;
	char	*part2;
	char	*ret;

	part1 = malloc(4097 * sizeof(char));
	j = 0;
	while (j < 4096)
	{
		part1[j++] = buffer[*i];
		if (buffer[*i] == '\0' || buffer[(*i)++] == '\n')
		{
			part1[j] = 0;
			return (part1);
		}
	}
	part1[4097] = 0;
	part2 = save_buffer(buffer, i);
	ret = ft_strjoin(part1, part2);
	free(part1);
	free(part2);
	return (ret);
}

char	*get_next_line(const int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	i;
	char		*line;
	char		*ret;
	char		*next;

	if (fd == -1)
		return (NULL);
	if (!*buffer)
		buffer[read(fd, buffer, BUFFER_SIZE)] = 0;
	ret = ft_calloc(1, sizeof(char));
	while (buffer[i])
	{
		next = save_buffer(buffer, &i);
		line = ft_strjoin(ret, next);
		ret = (free(ret), line);
		free(next);
		if (buffer[i - 1] == '\n')
			break ;
		buffer[read(fd, buffer, BUFFER_SIZE)] = 0;
		i = 0;
	}
	if (*ret)
		return (ret);
	return (free(ret), NULL);
}
