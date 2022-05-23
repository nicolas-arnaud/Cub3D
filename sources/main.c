/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/22 22:34:44 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*parse_map(char *map_filename)
{
	int		fd;
	char	*file_line;
	t_map	*ret;

	fd = open(map_filenamem, O_RDONLY);
	file_line = get_next_line(fd);
	ret = ft_calloc(sizeof(t_map));

	return (ret);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	map = parse_map(argv[1]);
	
	return (EXIT_SUCCESS);
}
