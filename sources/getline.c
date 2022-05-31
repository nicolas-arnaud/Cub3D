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

#include "../includes/cub3d.h"

char	*save_buffer(char *buffer, int *i)
{
	int 	j;
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
	free(part1);
	free(part2);
	return (ret);
}

char *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	i;
	ssize_t		read_size;
	char		*line;
	char		*ret;


	if (!*buffer)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		buffer[read_size] = 0;
	}
	ret = ft_calloc(1, sizeof(char));
	while (buffer[i])
	{
		line = ft_strjoin(ret, save_buffer(buffer, &i));
		free(ret);
		ret = line;
		if (buffer[i - 1] == '\n')
			break ;
		read_size = read(fd, buffer, BUFFER_SIZE);
		buffer[read_size] = 0;
		i = 0;
	}
	if (*ret)
		return (ret);
	free(ret);
	return (NULL);
}