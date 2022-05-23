/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/23 13:35:12 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
/*
void	get_map_datas(t_env *env, char **elem);
{
	return ;
}
*/
int	rgb_to_int(char	*rgb)
{
	int		ret;
	int		c;
	char	**colors;

	ret = 0;
	colors = ft_split(rgb, ',');
	c = 0;
	while (c < 3)
	{
		ret |= ft_atoi(colors[c]) << (8 * (2 - c));
		c++;
	}
	ft_free_split(colors);
	return (ret);
}

void	register_data(t_env	*env, char *line)
{
	char	**elem;

	elem = ft_split(line, ' ');
	if (!elem[0] || !elem[1])
		return ;
	if (!ft_strncmp(elem[0],"NO", 3))
		env->wallTexture[0] = ft_strdup(elem[1]);
	else if (!ft_strncmp(elem[0],"SO", 3))
		env->wallTexture[1] = ft_strdup(elem[1]);
	else if (!ft_strncmp(elem[0],"WE", 3))
		env->wallTexture[2] = ft_strdup(elem[1]);
	else if (!ft_strncmp(elem[0],"EA", 3))
		env->wallTexture[3] = ft_strdup(elem[1]);
	else if (!ft_strncmp(elem[0],"F", 2))
		env->floorColor = rgb_to_int(elem[1]);
	else if (!ft_strncmp(elem[0],"C", 2))
		env->ceilColor = rgb_to_int(elem[1]);
	//else if (env->step > 6)
	//	get_map_datas(env, elem);
	else
		env->step--;
	env->step++;
	ft_free_split(elem);
}

t_env	*parse_envFile(char *filename)
{
	int		fd;
	char	*line;
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		register_data(ret, line);
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	if (ret->step < 6)
		return (NULL);
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("%s\n", ret->wallTexture[0]);
	printf("%s\n", ret->wallTexture[1]);
	printf("%s\n", ret->wallTexture[2]);
	printf("%s\n", ret->wallTexture[3]);
	printf("%d\n", ret->floorColor);
	printf("%d\n", ret->ceilColor);
	return (ret);
}

int	main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
		return (EXIT_FAILURE);
	env = parse_envFile(argv[1]);	
	return (EXIT_SUCCESS);
}
