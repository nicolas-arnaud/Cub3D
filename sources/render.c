/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:33:02 by narnaud           #+#    #+#             */
/*   Updated: 2022/06/01 17:00:21 by narnaud          ###   ########.fr       */
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

double	get_wall_dist(t_env *env, int x)
{
	double	camX;
	t_vec_d ray;
	double	dDist[2];
	double	sDist[2];
	int		cell[2];
	int		*step;
	int		hit;
	int		side;

	camX = 2 * x / (double)WIN_X_SZ - 1;
	set_vec(&ray, env->playerDir.x + env->camPlan.x * camX, env->playerDir.y + env->camPlan.y * camX);
	cell[0] = (int)(env->playerPos.x);
	cell[1] = (int)(env->playerPos.y);
	if (ray.x == 0)
		dDist[0] = 1e30;
	else
		dDist[0] = fabs(1 / ray.x);
	if (ray.y == 0)
		dDist[1] = 1e30;
	else
		dDist[1] = fabs(1 / ray.y);
	hit = 0;
	step = (int[2]){0, 0};
	if (ray.x < 0 && --step[0])
		sDist[0] = (env->playerPos.x - cell[0]) * dDist[0];
	else if (++step[0])
		sDist[0] = (cell[0] + 1.0 - env->playerPos.x) * dDist[0];
	if (ray.y < 0 && --step[1])
		sDist[1] = (env->playerPos.y - cell[1]) * dDist[1];
	else if (++step[1])
		sDist[1] = (cell[1] + 1.0 - env->playerPos.y) * dDist[1];
	while (hit == 0)
	{
		side = 0;
		if (sDist[0] > sDist[1])
			side++;
		sDist[side] += dDist[side];
		cell[side] += step[side];
		if (env->map[cell[1]][cell[0]] > '0')
			hit = 1;
	}
	return (sDist[side] - dDist[side]);
}

void render_view(t_env *env)
{
	int	x;
	double	perpWallDist;
	int		startEnd[2];
	int		lineHeight;
	
	x = 0;
	while (x < WIN_X_SZ)
	{
		perpWallDist = get_wall_dist(env, x);
		lineHeight = (int)(WIN_Y_SZ / perpWallDist);
		if (lineHeight < 0)
			lineHeight = 0; // = WIN_Y_SZ 
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
