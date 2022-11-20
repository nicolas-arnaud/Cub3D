/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 21:23:40 by narnaud           #+#    #+#             */
/*   Updated: 2022/08/23 16:34:20 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*save_buffer(char *buffer, int *i)
{
	int		j;
	char	*part1;
	char	*part2;
	char	*ret;

	part1 = ft_calloc(512, sizeof(char));
	j = 0;
	while (j < 512)
	{
		part1[j++] = buffer[*i];
		if (buffer[*i] == '\0' || buffer[(*i)++] == '\n')
			return (part1);
	}
	part2 = save_buffer(buffer, i);
	ret = ft_strjoin(part1, part2);
	return (free(part1), free(part2), ret);
}

char	*get_next_line(const int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	i;
	char		*line;
	char		*ret;
	char		*next;

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
