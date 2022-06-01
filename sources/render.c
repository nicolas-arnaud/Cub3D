/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:33:02 by narnaud           #+#    #+#             */
/*   Updated: 2022/06/01 19:57:30 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_rectangle(t_env *env, t_rectangle rect, int borders)
{
	int	stepX;
	int	stepY;
	
	stepY = 0;
	while (stepY < rect.sizeY)
	{
		stepX = 0;
		while (stepX < rect.sizeX)
		{
			if (borders && (stepX == rect.sizeX - 1 || stepY == rect.sizeY - 1))
				env->buffer[(env->line_bytes * (int)(rect.startY + stepY))
				+ (int)(rect.startX + stepX)] = 0;
			else
				env->buffer[(env->line_bytes * (int)(rect.startY + stepY))
				+ (int)(rect.startX + stepX)] = rect.color;
			stepX++;
		}
		stepY++;
	}
}

void	draw_vert(t_env *env, int x, int *startEnd, int color)
{
	draw_rectangle(env, (t_rectangle){x, 0, 1, startEnd[0] - 1, env->ceilColor}, 0);
	draw_rectangle(env, (t_rectangle){x, startEnd[0], 1, startEnd[1] - startEnd[0] - 1, color}, 0);
	draw_rectangle(env, (t_rectangle){x, startEnd[1], 1, WIN_Y_SZ - startEnd[1], env->floorColor}, 0);
}

void	render_minimap(t_env *env, t_vec size)
{
	char	**map;
	t_vec	vec;
	int		dX;
	int		dY;

	dX = size.x / env->wide;
	dY = size.y / env->deep;
	vec.y = 0;
	map = env->map;
	while (map[vec.y])
	{
		vec.x = 0;
		while (map[vec.y][vec.x])
		{
			if (map[vec.y][vec.x] == '0')		
				draw_rectangle(env, (t_rectangle){vec.x * dX, vec.y * dY, dX, dY, 39424}, 1);
			else if (map[vec.y][vec.x] == '1')
				draw_rectangle(env, (t_rectangle){vec.x * dX, vec.y * dY, dX, dY, 11885067}, 1);
			vec.x++;
		}
		vec.y++;
	}
	draw_rectangle(env, (t_rectangle){
		env->playerPos.x * dX - dX / 4, env->playerPos.y * dY - dY / 4,
		dX / 2, dY / 2, 255}, 0);
}


double	calculate_dist(t_env *env, t_raycast rc)
{
	int	side;

	while (1)
	{
		side = 0;
		if (rc.sDist[0] > rc.sDist[1])
			side++;
		rc.sDist[side] += rc.dDist[side];
		rc.cell[side] += rc.step[side];
		if (env->map[rc.cell[1]][rc.cell[0]] > '0')
			return (rc.sDist[side] - rc.dDist[side]);
	}
}

double	get_wall_dist(t_env *env, int x)
{
	double		camX;
	t_raycast	rc;

	camX = 2 * x / (double)WIN_X_SZ - 1;
	set_vec(&rc.vec, env->playerDir.x + env->camPlan.x * camX,
		env->playerDir.y + env->camPlan.y * camX);
	rc.cell[0] = (int)(env->playerPos.x);
	rc.cell[1] = (int)(env->playerPos.y);
	if (rc.vec.x == 0)
		rc.dDist[0] = 1e30;
	else
		rc.dDist[0] = fabs(1 / rc.vec.x);
	if (rc.vec.y == 0)
		rc.dDist[1] = 1e30;
	else
		rc.dDist[1] = fabs(1 / rc.vec.y);
	rc.step = (int[2]){0, 0};
	if (rc.vec.x < 0 && --rc.step[0])
		rc.sDist[0] = (env->playerPos.x - rc.cell[0]) * rc.dDist[0];
	else if (++rc.step[0])
		rc.sDist[0] = (rc.cell[0] + 1.0 - env->playerPos.x) * rc.dDist[0];
	if (rc.vec.y < 0 && --rc.step[1])
		rc.sDist[1] = (env->playerPos.y - rc.cell[1]) * rc.dDist[1];
	else if (++rc.step[1])
		rc.sDist[1] = (rc.cell[1] + 1.0 - env->playerPos.y) * rc.dDist[1];
	return (calculate_dist(env, rc));
}

void render_view(t_env *env)
{
	int	x;
	double	wallDist;
	int		startEnd[2];
	int		lineHeight;
	
	x = 0;
	while (x < WIN_X_SZ)
	{
		wallDist = get_wall_dist(env, x);
		lineHeight = (int)(WIN_Y_SZ / wallDist);
		if (lineHeight < 0)
			lineHeight = 0;
		startEnd[0] = -lineHeight / 2 + WIN_Y_SZ / 2;
		if (startEnd[0] < 0)
			startEnd[0] = 0;
		startEnd[1] = lineHeight / 2 + WIN_Y_SZ / 2;
		if(startEnd[1] >= WIN_Y_SZ)
			startEnd[1] = WIN_Y_SZ - 1;
		draw_vert(env, x, startEnd, 11885067);
		x++;
	}
}

void	render(t_env *env)
{
	env->img = mlx_new_image(env->mlx, WIN_X_SZ, WIN_Y_SZ);
	env->buffer = (int *)mlx_get_data_addr(env->img, \
		&env->pixel_bits, &env->line_bytes, &env->endian);
	env->line_bytes /= 4;
	render_view(env);
	if (env->minimap)
		render_minimap(env, (t_vec){env->wide * 8, env->deep * 8});
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_destroy_image(env->mlx, env->img);
}
