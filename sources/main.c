/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/23 09:54:53 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map	parse_map(char *map_filename)
{
	static t_map	ret;
	int		fd;
	char	*file_line;

	fd = open(map_filename, O_RDONLY);
	file_line = get_next_line(fd);
	while (file_line)
	{
		ret.deep++;
		printf("%s", file_line);
		free(file_line);
		file_line = get_next_line(fd);
	}
	return (ret);
}

int	main(int argc, char **argv)
{
	t_map	map;

	(void)argc;
	map = parse_map(argv[1]);
	
	return (EXIT_SUCCESS);
}
