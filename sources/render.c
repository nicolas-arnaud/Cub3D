/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:33:02 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/31 18:11:15 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_vert(t_env *env, int x, int *startEnd, int color)
{
	int y;

	y= 0;
	while (y < startEnd[0])
	{
		env->buffer[env->line_bytes * y + x] = env->ceilColor;
		y++;
	}
	while (startEnd[0] < startEnd[1])
	{
		env->buffer[env->line_bytes * startEnd[0] + x] = color;
		startEnd[0]++;
	}
	y = startEnd[0];
	while (y < WIN_Y_SZ)
	{
		env->buffer[env->line_bytes * y + x] = env->floorColor;
		y++;
	}
}

void	draw_square(t_env *env, t_vec_d vec, int size, int color)
{
	int	step_x;
	int	step_y;

	step_y = 0;
	while (step_y < size)
	{
		step_x = 0;
		while (step_x < size)
		{
			if (step_x == size - 1 || step_y == size - 1)
				env->buffer[(env->line_bytes * (int)(vec.y * size + step_y)) + (int)(vec.x * size + step_x)] = 0;
			else
				env->buffer[(env->line_bytes * (int)(vec.y * size + step_y)) + (int)(vec.x * size + step_x)] = color;
			step_x++;
		}
		step_y++;
	}
}

void	render_minimap(t_env *env)
{
	char	**map;
	t_vec	vec;
	t_vec_d	vecd;

	vec.y = 0;
	map = env->map;
	while (map[vec.y])
	{
		vec.x = 0;
		while (map[vec.y][vec.x])
		{
			vecd = (t_vec_d){vec.x, vec.y};
			if (map[vec.y][vec.x] == '0')		
				draw_square(env, vecd, 6, 39424);
			else if (map[vec.y][vec.x] == '1')
				draw_square(env, vecd, 6, 11885067);
			vec.x++;
		}
		vec.y++;
	}
	vecd = (t_vec_d){env->playerPos.x, env->playerPos.y};
	draw_square(env, vecd, 6, 255);
}

double	get_wall_dist(t_env *env, int x)
{
	double	camX;
	t_vec_d ray;
	t_vec_d	dDist;
	t_vec_d sDist;
	t_vec	cell;
	t_vec	step;
	int		hit;
	int		side;
	
	camX = 2 * x / (double)WIN_X_SZ - 1;
	set_vec(&ray, env->playerDir.x + env->camPlan.x * camX, env->playerDir.y + env->camPlan.y * camX);
	cell.x = round(env->playerPos.x);
	cell.y = round(env->playerPos.y);
	if (ray.x == 0)
		dDist.x = 1e30;
	else
		dDist.x = fabs(1 / ray.x);
	if (ray.y == 0)
		dDist.y = 1e30;
	else
		dDist.y = fabs(1 / ray.y);
	hit = 0;
	if (ray.x < 0)
	{
		step.x = -1;
		sDist.x = (env->playerPos.x - cell.x) * dDist.x;
	}
	else
	{
		step.x = 1;
		sDist.x = (cell.x + 1.0 - env->playerPos.x) * dDist.x;
	}
	if (ray.y < 0)
	{
		step.y = -1;
		sDist.y = (env->playerPos.y - cell.y) * dDist.y;
	}
	else
	{
		step.y = 1;
		sDist.y = (cell.y + 1.0 - env->playerPos.y) * dDist.y;
	}
	while (hit == 0)
	{
		if (sDist.x < sDist.y)
		{
			sDist.x += dDist.x;
			cell.x += step.x;
			side = 0;
		}
		else
		{
			sDist.y += dDist.y;
			cell.y += step.y;
			side = 1;
		}
		if (env->map[cell.y][cell.x] > '0')
			hit = 1;
	}
	if (side == 0)
		return (sDist.x - dDist.x);
	else
		return (sDist.y - dDist.y);
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
	render_minimap(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_destroy_image(env->mlx, env->img);
}