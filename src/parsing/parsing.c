/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:20:29 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/14 11:48:57 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	cleanup_datas(t_env *env)
{
	if (env->tex[0].file)
		free(env->tex[0].file);
	if (env->tex[1].file)
		free(env->tex[1].file);
	if (env->tex[2].file)
		free(env->tex[2].file);
	if (env->tex[3].file)
		free(env->tex[3].file);
	if (env->tex[4].file)
		free(env->tex[4].file);
	return (1);
}

void	register_settings(int *progress, t_env *env, char *line)
{
	char	**elem;

	elem = ft_split(line, ' ');
	if (!elem[0] || !elem[1])
		return ;
	if (!ft_strncmp(elem[0], "NO", 3))
		env->tex[0].file = ft_strtrim(elem[1], "\n");
	else if (!ft_strncmp(elem[0], "SO", 3))
		env->tex[1].file = ft_strtrim(elem[1], "\n");
	else if (!ft_strncmp(elem[0], "WE", 3))
		env->tex[2].file = ft_strtrim(elem[1], "\n");
	else if (!ft_strncmp(elem[0], "EA", 3))
		env->tex[3].file = ft_strtrim(elem[1], "\n");
	else if (!ft_strncmp(elem[0], "DO", 3))
		env->tex[4].file = ft_strtrim(elem[1], "\n");
	else if (!ft_strncmp(elem[0], "F", 2))
		env->floorColor = rgb_to_int(elem + 1);
	else if (!ft_strncmp(elem[0], "C", 2))
		env->ceilColor = rgb_to_int(elem + 1);
	else
		(*progress)--;
	(*progress)++;
	ft_free_split(elem);
	if (env->floorColor == -1 || env->ceilColor == -1)
		(*progress)--;
}

t_slist	*read_map_line(t_env *env, char *line)
{
	t_slist	*ret;
	char	*map_y;
	int		i;

	ret = malloc(sizeof(t_slist));
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
	if (i > env->wide)
		env->wide = i;
	env->deep++;
	ret->next = NULL;
	ret->content = map_y;
	return (ret);
}

int	is_valid_map(t_env *env)
{
	if (!find_player(env))
		printf("Error: There is no player on the map.\n");
	else if (is_in_open_room(env, env->playerPos.x, env->playerPos.y))
		printf("Error: You are using an open map.\n");
	else
		return (1);
	return (0);
}

t_env	*load_map(char *filename)
{
	int				fd;
	char			*line;
	static int		progress;
	static t_slist	*e_map;
	t_env			*env;

	env = ft_calloc(1, sizeof(t_env));
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (*line && *line != '\n' && progress > 6 && progress++)
			ft_slst_add_back(&e_map, read_map_line(env, line));
		else if (*line != '#')
			register_settings(&progress, env, line);
		free(line);
		line = get_next_line(fd);
	}
	if (progress < 7 && cleanup_datas(env))
		return (NULL);
	env->map = create_map_array(e_map, env->wide, env->deep);
	if (!is_valid_map(env) && cleanup_datas(env))
		return (NULL);
	return (env);
}
