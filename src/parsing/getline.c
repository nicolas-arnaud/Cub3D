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

	part1 = ft_calloc(4097, sizeof(char));
	j = 0;
	while (j < 4096)
	{
		part1[j++] = buffer[*i];
		if (buffer[*i] == '\0' || buffer[(*i)++] == '\n')
		{
			return (part1);
		}
	}
	part2 = save_buffer(buffer, i);
	ret = ft_strjoin(part1, part2);
	free(part1);
	free(part2);
	return (ret);
}

typedef struct s_gnl
{
	char	*line;
	char	*next;
	char	*ret;
}	t_gnl;

char	*get_next_line(const int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	i;
	t_gnl		gnl;

	if (!buffer[i])
	{
		i = 0;
		buffer[read(fd, buffer, BUFFER_SIZE)] = 0;
	}
	gnl.ret = ft_calloc(1, sizeof(char));
	while (buffer[i])
	{
		gnl.next = save_buffer(buffer, &i);
		gnl.line = ft_strjoin(gnl.ret, gnl.next);
		gnl.ret = (free(gnl.ret), gnl.line);
		free(gnl.next);
		if (buffer[i - 1] == '\n')
			break ;
		buffer[read(fd, buffer, BUFFER_SIZE)] = 0;
		i = 0;
	}
	if (*(gnl.ret))
		return (gnl.ret);
	return (free(gnl.ret), NULL);
}
