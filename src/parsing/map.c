/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:30:50 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/22 06:21:24 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Get the initial position and orientation of the player and
 * save it into env.
 */
int	init_player(t_env *env, int x, int y)
{
	char	orientation;

	orientation = env->map[y][x];
	env->map[y][x] = '0';
	dvec_set(&env->player_pos, x + 0.5, y + 0.5);
	if (orientation == 'N')
		dvec_set(&env->player_dir, 0, -1);
	else if (orientation == 'S')
		dvec_set(&env->player_dir, 0, 1);
	else if (orientation == 'E')
		dvec_set(&env->player_dir, 1, 0);
	else if (orientation == 'W')
		dvec_set(&env->player_dir, -1, 0);
	env->cam_plan = dvec_rot(env->player_dir, M_PI / 2, 0.66);
	return (1);
}

/* Find the player into the map */
int	find_player(t_env *env)
{
	char	**map;
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

/* Check all around the player if he can acces the void around the map.
 * Also check if the map is not to big to avoid so later stack overflow.
 */
int	is_in_open_room(t_env *env, int x, int y)
{
	static char		*checked;
	static int		recurs;

	recurs++;
	if (recurs > 1000000 - 2 * (env->wide * env->deep))
		return (1);
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
		|| is_in_open_room(env, x, y + 1)
		|| is_in_open_room(env, x - 1, y)
		|| is_in_open_room(env, x, y - 1))
		return (1);
	else
		return (0);
}

/* Convert map chained list into a string array for
 * render faster.
 */
char	**create_map_array(t_slist	*e_lst, int wide, int deep)
{
	char	**ret;
	char	*end_line;
	t_slist	*tmp;
	int		i;

	if (!e_lst)
		return (ft_calloc(1, sizeof(char *)));
	ret = ft_calloc(deep + 1, sizeof(char *));
	i = 0;
	while (i < deep)
	{
		end_line = ft_calloc(wide - ft_strlen(e_lst->content) + 1,
				sizeof(char));
		end_line = ft_memset(end_line,
				'0', wide - ft_strlen(e_lst->content) * sizeof(char));
		ret[i] = ft_strjoin(e_lst->content, end_line);
		free(end_line);
		free(e_lst->content);
		tmp = e_lst;
		e_lst = e_lst->next;
		free(tmp);
		i++;
	}
	return (ret);
}
