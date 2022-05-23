/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/23 14:50:48 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_map_datas(t_env *env, char *line)
{
	t_slist	*lst_e;
	char	*map_y;
	int		i;
	
	i = 0;
	lst_e = malloc(sizeof(*lst_e));
	lst_e->next = NULL;
	map_y = malloc(ft_strlen(line) * sizeof(char));
	while (*line)
	{
		if (!ft_isspace(*line))
		{
			map_y[i] = *line;
			i++;
		}
		line++;
	}
	map_y[i] = '\0';
	env->deep++;
	if (!env->raw_map)
		env->raw_map = ft_slst_new(map_y);
	else
	{
		lst_e->content = map_y;
		ft_slst_add_back(&(env->raw_map), lst_e);
	}
}

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
	else if (env->step > 5)
		get_map_datas(env, line);
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
	int		y;
	t_slist	*raw_map;

	ret = malloc(sizeof(t_env));
	ret->deep = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		register_data(ret, line);
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	if (ret->step < 7)
		return (NULL);
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("%s\n", ret->wallTexture[0]);
	printf("%s\n", ret->wallTexture[1]);
	printf("%s\n", ret->wallTexture[2]);
	printf("%s\n", ret->wallTexture[3]);
	printf("%d\n", ret->floorColor);
	printf("%d\n", ret->ceilColor);
	y = 0;
	raw_map = ret->raw_map;
	while (y < ret->deep)
	{
		printf("%s\n", (char *)raw_map->content);
		y++;
		raw_map = raw_map->next;
	}
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
