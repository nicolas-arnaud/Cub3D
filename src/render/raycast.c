/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:27:55 by narnaud           #+#    #+#             */
/*   Updated: 2022/08/23 16:03:32 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_side(t_rc *rc)
{
	if (rc->sDist[0] > rc->sDist[1])
		rc->side = 1;
	else
		rc->side = 0;
}

void	init_ray(t_env *env, t_rc *rc)
{
	if (rc->vec.x == 0)
		rc->dDist[0] = 1e30;
	else
		rc->dDist[0] = fabs(1 / rc->vec.x);
	if (rc->vec.y == 0)
		rc->dDist[1] = 1e30;
	else
		rc->dDist[1] = fabs(1 / rc->vec.y);
	if (rc->vec.x < 0 && --rc->step[0])
		rc->sDist[0] = (env->playerPos.x - rc->cell[0]) * rc->dDist[0];
	else if (++rc->step[0])
		rc->sDist[0] = (rc->cell[0] + 1.0 - env->playerPos.x) * rc->dDist[0];
	if (rc->vec.y < 0 && --rc->step[1])
		rc->sDist[1] = (env->playerPos.y - rc->cell[1]) * rc->dDist[1];
	else if (++rc->step[1])
		rc->sDist[1] = (rc->cell[1] + 1.0 - env->playerPos.y) * rc->dDist[1];
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
			rc->wallX = env->playerPos.y + rc->sDist[rc->side] * rc->vec.y;
		else
			rc->wallX = env->playerPos.x + rc->sDist[rc->side] * rc->vec.x;
		rc->wallX -= floor(rc->wallX);
		if (rc->tex != 4 || 2 * rc->wallX - dvec_len((t_dvec){\
					rc->cell[0] - env->playerPos.x, \
					rc->cell[1] - env->playerPos.y}) < -2)
			return (1);
	}
	else
		rc->tex = 0;
	return (0);
}
