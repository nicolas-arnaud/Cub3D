/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:27:55 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/21 19:00:59 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_side(t_rc *rc)
{
	if (rc->s_dist[0] > rc->s_dist[1])
		rc->side = 1;
	else
		rc->side = 0;
}

void	init_ray(t_env *env, t_rc *rc)
{
	if (rc->vec.x == 0)
		rc->d_dist[0] = 1e30;
	else
		rc->d_dist[0] = fabs(1 / rc->vec.x);
	if (rc->vec.y == 0)
		rc->d_dist[1] = 1e30;
	else
		rc->d_dist[1] = fabs(1 / rc->vec.y);
	if (rc->vec.x < 0 && --rc->step[0])
		rc->s_dist[0] = (env->player_pos.x - rc->cell[0]) * rc->d_dist[0];
	else if (++rc->step[0])
		rc->s_dist[0] = (rc->cell[0] + 1.0 - env->player_pos.x) * rc->d_dist[0];
	if (rc->vec.y < 0 && --rc->step[1])
		rc->s_dist[1] = (env->player_pos.y - rc->cell[1]) * rc->d_dist[1];
	else if (++rc->step[1])
		rc->s_dist[1] = (rc->cell[1] + 1.0 - env->player_pos.y) * rc->d_dist[1];
}

int	ray_hit(t_env *env, t_rc *rc)
{
	check_side(rc);
	rc->cell[rc->side] += rc->step[rc->side];
	if (env->map[rc->cell[1]][rc->cell[0]] > '0')
	{
		if (env->map[rc->cell[1]][rc->cell[0]] == '1')
			rc->tex = 3 - rc->side * 2 - (rc->step[rc->side] + 1) / 2;
		else if (env->map[rc->cell[1]][rc->cell[0]] == '2' && rc->tex != 4)
			rc->tex = 4;
		else
			return (0);
		if (!rc->side)
			rc->wall_x = env->player_pos.y + rc->s_dist[rc->side] * rc->vec.y;
		else
			rc->wall_x = env->player_pos.x + rc->s_dist[rc->side] * rc->vec.x;
		rc->wall_x -= floor(rc->wall_x);
		if (rc->tex != 4 || 2 * rc->wall_x - dvec_len((t_dvec){\
					rc->cell[0] - env->player_pos.x, \
					rc->cell[1] - env->player_pos.y}) < -2)
			return (1);
	}
	else
		rc->tex = 0;
	return (0);
}
