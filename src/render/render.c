/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:33:02 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/22 07:13:31 by narnaud          ###   ########.fr       */
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

/* Draw the wall/door using texture for it.
 *
 * First calculate the horizontal coordinate of the wall texture which 
 * 	was hit and his height.
 * Reverse coordinate if the raycas was moving with negative direciton.
 * Init step and screen Y initial coordinate.
 * For each vertical pixel which must be drawn on screen, 
 * 	draw the corresponding texture pixel.
 */
void	draw_wall(t_env *env, t_rc *rc, int wallHeight, int *wall_lim)
{
	int		tex_height;
	t_vec	tex;
	double	step;
	double	y_out;

	tex_height = env->tex[rc->tex].height;
	tex.x = (int)(rc->wall_x * (double)env->tex[rc->tex].width);
	if ((!rc->side && rc->vec.x > 0) || (rc->side && rc->vec.y < 0))
		tex.x = env->tex[rc->tex].width - tex.x - 1;
	step = 1.0 * tex_height / wallHeight;
	y_out = (wall_lim[0] - WIN_Y_SZ / 2.0 + wallHeight / 2.0) * step;
	while (wall_lim[0] < wall_lim[1])
	{
		tex.y = (int)y_out & (tex_height - 1);
		y_out += step;
		env->buffer[env->line_bytes * wall_lim[0] + rc->x]
			= env->tex[rc->tex].buffer[tex_height * tex.y + tex.x];
		wall_lim[0]++;
	}
}

/* Draw the vertical thanks to raycast datas.
 * The wall/door size is the portionaly inverse to the distance to
 * 	the player he is.
 * Cap wall drawing to the borders of the window.
 * Draw the ceil part, the wall and the floor.
 */
void	draw_vert(t_env *env, t_rc *rc, int side)
{
	int		wall_height;
	int		wall_lim[2];

	wall_height = (int)(WIN_Y_SZ / rc->s_dist[side]);
	if (wall_height < 0)
		wall_height = 0;
	get_wall(wall_lim, wall_lim + 1, wall_height);
	draw_rectangle(env, (t_rect){(t_vec){rc->x, 0},
		(t_vec){1, wall_lim[0]}, env->ceil_color}, 0);
	draw_wall(env, rc, wall_height, wall_lim);
	draw_rectangle(env, (t_rect){(t_vec){rc->x, wall_lim[1]},
		(t_vec){1, WIN_Y_SZ - wall_lim[1]}, env->floor_color}, 0);
}

/* Calculate player point of view:
 *
 * - For each vertical along the window:
 *   - Calculate X coordinate with center of screen as origin.
 *   - Initialize raycasting datas:
 *  	- calculate unit vector for the ray corresponding to this vertical,
 *  	- set the step vector to 0  an save the x to not reverse calculate it,
 *  	- finish initialization with initials  deltas and sides distances.
 *   - Shot the ray until he hit a wall or a door.
 *   - Check which orentation the hit point have.
 *   - Draw the vertical
 */
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
		dvec_set(&rc.vec, env->player_dir.x + env->cam_plan.x * cam_x,
			env->player_dir.y + env->cam_plan.y * cam_x);
		rc.cell = (int [2]){env->player_pos.x, env->player_pos.y};
		rc.step = (int [2]){0, 0};
		rc.x = x;
		init_ray(env, &rc);
		while (!ray_hit(env, &rc))
			rc.s_dist[rc.side] += rc.d_dist[rc.side];
		check_side(&rc);
		draw_vert(env, &rc, rc.side);
		x++;
	}
}

/* Generate the render for the actual tick.
 *
 * - Erase the previous render.
 * - Calculate player point of view.
 * - If minimap enabled, generate it. (minimap.c)
 * - Put render in window.
 */
void	render(t_env *env)
{
	ft_bzero(env->buffer, WIN_Y_SZ * WIN_X_SZ * sizeof(int));
	render_view(env);
	if (env->minimap)
		render_minimap(env, measure(env));
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
