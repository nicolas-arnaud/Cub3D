/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:22:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/23 16:54:20 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_map_datas(t_env *env, char *line)
{
	t_slist	*lst_e;
	char	*map_y;
	int		i;
	
	i = 0;
	map_y = malloc((ft_strlen(line)) * sizeof(char));
	while (*line)
	{
		if (*line == '\n')
			break ;
		else if (!ft_isspace(*line))
			map_y[i] = *line;
		else
			map_y[i] = '0';
		line++;
		i++;
	}
	map_y[i] = '\0';
	env->deep++;
	lst_e = malloc(sizeof(*lst_e));
	lst_e->next = NULL;
	lst_e->content = map_y;
	ft_slst_add_back(&(env->raw_map), lst_e);
}

int	rgb_to_int(char	**rgb)
{
	int		ret;
	int		i;
	int		c;
	char	**colors;

	ret = 0;
	rgb++;
	colors = ft_split(*rgb, ',');
	c = 0;
	i = 0;
	while (c < 3)
	{
		if (colors[i])
		{
			ret |= ft_atoi(colors[i]) << (8 * (2 - c));
			c++;
			i++;
		}
		else
		{
			ft_free_split(colors);
			rgb++;
			i = 0;
			colors = ft_split(*rgb, ',');
		}
	}
	ft_free_split(colors);
	return (ret);
}

void	register_data(t_env	*env, char *line)
{
	char	**elem;

	if (*line && *line != '\n' && env->step > 5)
	{
		get_map_datas(env, line);
		return ;
	}
	elem = ft_split(line, ' ');
	if (!elem[0] || !elem[1])
		return ;
	if (!ft_strncmp(elem[0],"NO", 3))
		env->wallTexture[0] = ft_strtrim(elem[1], "\n");
	else if (!ft_strncmp(elem[0],"SO", 3))
		env->wallTexture[1] = ft_strtrim(elem[1], "\n");
	else if (!ft_strncmp(elem[0],"WE", 3))
		env->wallTexture[2] = ft_strtrim(elem[1], "\n");
	else if (!ft_strncmp(elem[0],"EA", 3))
		env->wallTexture[3] = ft_strtrim(elem[1], "\n");
	else if (!ft_strncmp(elem[0],"F", 2))
		env->floorColor = rgb_to_int(elem);
	else if (!ft_strncmp(elem[0],"C", 2))
		env->ceilColor = rgb_to_int(elem);
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
		printf("%s", line);
		register_data(ret, line);
		free(line);
		line = get_next_line(fd);
	}
	if (ret->step < 6)
		return (NULL);
	printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
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
