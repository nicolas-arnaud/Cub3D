/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:33:02 by narnaud           #+#    #+#             */
/*   Updated: 2022/06/07 11:46:39 by narnaud          ###   ########.fr       */
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
				draw_rectangle(env, (t_rectangle){vec.x * dX, vec.y * dY, dX, dY, 9539977}, 1);
			else if (map[vec.y][vec.x] == '2')
				draw_rectangle(env, (t_rectangle){vec.x * dX, vec.y * dY, dX, dY, 100 << 16 | 20 << 8| 100}, 1);
			vec.x++;
		}
		vec.y++;
	}
	draw_rectangle(env, (t_rectangle){
		env->playerPos.x * dX - dX / 4, env->playerPos.y * dY - dY / 4,
		dX / 2, dY / 2, 255}, 0);
}

void draw_vert(t_env *env, t_raycast *rc, int side, int x)
{
	int		startEnd[2];
	int 	texHeight;
	int 	texX;
	int 	texY;
	double	step;
	double	texPos;
	int		lineHeight;

	lineHeight = (int)(WIN_Y_SZ / rc->sDist[side]);
	if (lineHeight < 0)
		lineHeight = 0;
	startEnd[0] = -lineHeight / 2 + WIN_Y_SZ / 2;
	if (startEnd[0] < 0)
		startEnd[0] = 0;
	startEnd[1] = lineHeight / 2 + WIN_Y_SZ / 2;
	if(startEnd[1] >= WIN_Y_SZ)
		startEnd[1] = WIN_Y_SZ - 1;
	texHeight = env->tex[rc->tex].height;
	draw_rectangle(env, (t_rectangle){x, 0, 1, startEnd[0], env->ceilColor}, 0);
	//draw_rectangle(env, (t_rectangle){x, startEnd[0], 1, startEnd[1] - startEnd[0] - 1, color}, 0);
	texX = (int)(rc->wallX * (double)env->tex[rc->tex].width);
	if(!side && rc->vec.x > 0) 
		texX = env->tex[rc->tex].width - texX - 1;
	if(side && rc->vec.y < 0) 
		texX = env->tex[rc->tex].width - texX - 1;
	step = 1.0 * texHeight / lineHeight;
	texPos = (startEnd[0] - WIN_Y_SZ / 2 + lineHeight / 2) * step;
	while (startEnd[0] < startEnd[1])
	{
		texY = (int)texPos & (texHeight - 1);
		texPos += step;
		env->buffer[env->line_bytes * startEnd[0] + x] \
			= env->tex[rc->tex].buffer[texHeight * texY + texX];
		startEnd[0]++;
	}
	draw_rectangle(env, (t_rectangle){x, startEnd[1], 1, WIN_Y_SZ - startEnd[1], env->floorColor}, 0);
}

int	to_draw(t_env *env, t_raycast *rc, int *side)
{
			*side = 0;
			if (rc->sDist[0] > rc->sDist[1])
				(*side)++;
			rc->cell[*side] += rc->step[*side]; 
			if (env->map[rc->cell[1]][rc->cell[0]] > '0')
			{
				if (env->map[rc->cell[1]][rc->cell[0]] == '1')
					rc->tex = 3 - *side * 2 - (rc->step[*side] + 1) / 2;
				else if (env->map[rc->cell[1]][rc->cell[0]] == '2' && rc->tex != 4)
					rc->tex = 4;
				else 
					return (0);
				if (!*side)
					rc->wallX= env->playerPos.y + rc->sDist[*side] * rc->vec.y;
				else
					rc->wallX = env->playerPos.x + rc->sDist[*side] * rc->vec.x;
				rc->wallX -= floor(rc->wallX);
				if (rc->tex != 4 || 2 * rc->wallX - vec_len((t_vec_d){rc->cell[0] - env->playerPos.x, rc->cell[1] - env->playerPos.y}) < -2)
					return (1);
			}
			else
				rc->tex = 0;
			return (0);
}

void	init_vert_rc(t_env *env, t_raycast *rc)
{
	if (rc->vec.x == 0)
		rc->dDist[0] = 1e30;
	else
		rc->dDist[0] = fabs(1 / rc->vec.x);
	if (rc->vec.y == 0)
		rc->dDist[1] = 1e30;
	else
		rc->dDist[1] = fabs(1 / rc->vec.y);
	rc->step = (int[2]){0, 0};
	if (rc->vec.x < 0 && --rc->step[0])
		rc->sDist[0] = (env->playerPos.x - rc->cell[0]) * rc->dDist[0];
	else if (++rc->step[0])
		rc->sDist[0] = (rc->cell[0] + 1.0 - env->playerPos.x) * rc->dDist[0];
	if (rc->vec.y < 0 && --rc->step[1])
		rc->sDist[1] = (env->playerPos.y - rc->cell[1]) * rc->dDist[1];
	else if (++rc->step[1])
		rc->sDist[1] = (rc->cell[1] + 1.0 - env->playerPos.y) * rc->dDist[1];
}

void	render_view(t_env* env)
{
	int			side;
	t_raycast	rc;
	int			x;
	double		camX;

	x = 0;
	while (x < WIN_X_SZ)
	{
		ft_bzero(&rc, sizeof(rc));
		camX = 2 * x / (double)WIN_X_SZ - 1;
		set_vec(&rc.vec, env->playerDir.x + env->camPlan.x * camX,
			env->playerDir.y + env->camPlan.y * camX);
		rc.cell = (int[2]){env->playerPos.x, env->playerPos.y};
		init_vert_rc(env, &rc);
		while (!to_draw(env, &rc, &side))
			rc.sDist[side] += rc.dDist[side];
		draw_vert(env, &rc, side, x);
		x++;
	}
}

void	render(t_env *env)
{
	bzero(env->buffer, WIN_Y_SZ * WIN_X_SZ * sizeof(int));

	render_view(env);
	if (env->minimap)
		render_minimap(env, (t_vec){env->wide * 8, env->deep * 8});
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
