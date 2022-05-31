/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:20:29 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/31 09:00:17 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	cleanup_datas(t_env *env)
{

	if (env->wallTexture[0])
		free(env->wallTexture[0]);
	if (env->wallTexture[1])
		free(env->wallTexture[1]);
	if (env->wallTexture[2])
		free(env->wallTexture[2]);
	if (env->wallTexture[3])
		free(env->wallTexture[3]);
	return (1);
}

void	register_settings(int *progress, t_env *env, char *line)
{
	char	**elem;

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
		(*progress)--;
	(*progress)++;
	ft_free_split(elem);
}

/* TODO : measure wide and deep progressively
 */
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

char	**create_map_array(t_slist	*e_lst, int wide, int deep)
{
	char	**ret;
	char	*endLine;
	t_slist	*tmp;
	int		i;

	if (!e_lst)
		return (ft_calloc(1, sizeof(char *)));
	ret = ft_calloc(deep + 1, sizeof(char *));
	i = 0;
	while (i < deep)
	{
		endLine = ft_calloc(wide - ft_strlen(e_lst->content) + 1, sizeof(char));
		endLine = memset(endLine, '0', wide - ft_strlen(e_lst->content) * sizeof(char));
		ret[i] = ft_strjoin(e_lst->content, endLine);
		free(endLine);
		free(e_lst->content);
		tmp = e_lst;
		e_lst = e_lst->next;
		free(tmp);
		i++;
	}
	return (ret);
}

int	init_player(t_env *env, int x, int y)
{
	char	orientation;

	orientation = env->map[y][x];
	env->map[y][x] = '0';
	set_vec(&env->playerPos, x, y);
	if (orientation == 'N')
		set_vec(&env->playerDir, 0, -1);
	else if (orientation == 'S')
		set_vec(&env->playerDir, 0, 1);
	else if (orientation == 'E')
		set_vec(&env->playerDir, 1, 0);
	else if (orientation == 'W')
		set_vec(&env->playerDir, -1, -1);
	return (1);

}

int	find_player(t_env *env) 
{
	char **map;
	int		x;
	int		y;
	char	cell;

	y = 0;

	map = env->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			cell = map[y][x];
			if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
				return (init_player(env, x, y));
			x++;
		}
		y++;
	}
	return (0);
}

int	is_in_open_room(t_env *env, int x, int y)
{
	static char	*checked;

	if (x < 0 || x >= env->wide || y < 0 || y >= env->deep)
		return (1);
	if (!checked)
		checked = ft_calloc(env->deep * env->wide + 1, sizeof(char));
	if (checked[y * env->wide + x])
		return (0);
	checked[y * env->wide + x] = 1;
	if (env->map[y][x] == '1')
		return (0);
	else if (is_in_open_room(env, x + 1, y)
			|| is_in_open_room(env, x - 1, y)
			|| is_in_open_room(env, x, y + 1)
			|| is_in_open_room(env, x, y - 1))
		return (1);
	else
		return (0);
}

t_env	*parse_envFile(char *filename)
{
	int		fd;
	char	*line;
	int		progress;
	t_slist	*e_map;
	t_env	*ret;

	progress = 0;
	e_map = NULL;
	ret = ft_calloc(1, sizeof(t_env));
	ret->deep = 0;
	ret->wide = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (*line && *line != '\n' && progress > 5 && progress++)
			ft_slst_add_back(&e_map, read_map_line(ret, line));
		else
			register_settings(&progress, ret, line);
		free(line);
		line = get_next_line(fd);
	}
	if (progress < 6 && cleanup_datas(ret))
		return (NULL);
	else
		ret->map = create_map_array(e_map, ret->wide, ret->deep);
	if ((!find_player(ret) || is_in_open_room(ret, ret->playerPos.x, ret->playerPos.y))
			&& cleanup_datas(ret))   //add map cleanup in cleanup_datas
	{
		printf("Error: You are using an open map.");
		return (NULL);
	}
	return (ret);
}
