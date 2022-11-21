/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:33:02 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/14 16:45:42 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_wall(int *startY, int *endY, int height)
{
	*startY = -height / 2 + WIN_Y_SZ / 2;
	if (*startY < 0)
		*startY = 0;
	*endY = height / 2 + WIN_Y_SZ / 2;
	if (*endY >= WIN_Y_SZ)
		*endY = WIN_Y_SZ - 1;
}

void	draw_wall(t_env *env, t_rc *rc, int wallHeight, int *wall_lim)
{
	int		tex_height;
	t_vec	tex;
	double	step;
	double	y_out;

	tex_height = env->tex[rc->tex].height;
	tex.x = (int)(rc->wallX * (double)env->tex[rc->tex].width);
	if ((!rc->side && rc->vec.x > 0) || (rc->side && rc->vec.y < 0))
		tex.x = env->tex[rc->tex].width - tex.x - 1;
	step = 1.0 * tex_height / wallHeight;
	y_out = (wall_lim[0] - WIN_Y_SZ / 2.0 + wallHeight / 2.0) * step;
	while (wall_lim[0] < wall_lim[1])
	{
		tex.y = (int)y_out & (tex_height - 1);
		y_out += step;
		env->buffer[env->line_bytes * wall_lim[0] + rc->x] \
			= env->tex[rc->tex].buffer[tex_height * tex.y + tex.x];
		wall_lim[0]++;
	}
}

void	draw_vert(t_env *env, t_rc *rc, int side)
{
	int		wall_height;
	int		wall_lim[2];

	wall_height = (int)(WIN_Y_SZ / rc->sDist[side]);
	if (wall_height < 0)
		wall_height = 0;
	get_wall(wall_lim, wall_lim + 1, wall_height);
	draw_rectangle(env, (t_rect){(t_vec){rc->x, 0},
		(t_vec){1, wall_lim[0]}, env->ceilColor}, 0);
	draw_wall(env, rc, wall_height, wall_lim);
	draw_rectangle(env, (t_rect){(t_vec){rc->x, wall_lim[1]},
		(t_vec){1, WIN_Y_SZ - wall_lim[1]}, env->floorColor}, 0);
}

void	render_view(t_env *env)
{
	t_rc		rc;
	int			x;
	double		cam_x;

	x = 0;
	while (x < WIN_X_SZ)
	{
		ft_bzero(&rc, sizeof(rc));
		cam_x = 2 * x / (double)WIN_X_SZ - 1;
		dvec_set(&rc.vec, env->playerDir.x + env->camPlan.x * cam_x,
			env->playerDir.y + env->camPlan.y * cam_x);
		rc.cell = (int [2]){env->playerPos.x, env->playerPos.y};
		rc.step = (int [2]){0, 0};
		rc.x = x;
		init_ray(env, &rc);
		while (!ray_hit(env, &rc))
			rc.sDist[rc.side] += rc.dDist[rc.side];
		check_side(&rc);
		draw_vert(env, &rc, rc.side);
		x++;
	}
}

void	render(t_env *env)
{
	ft_bzero(env->buffer, WIN_Y_SZ * WIN_X_SZ * sizeof(int));
	render_view(env);
	if (env->minimap)
		render_minimap(env, (t_vec){WIN_X_SZ / 3, WIN_Y_SZ / 3});
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
