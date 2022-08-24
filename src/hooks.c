/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:47:30 by narnaud           #+#    #+#             */
/*   Updated: 2022/08/23 16:27:20 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press_hook(int keycode, t_env *env)
{
	if (keycode == KEY_M)
		env->minimap = !env->minimap;
	else if (keycode == KEY_ECHAP)
		exit(EXIT_SUCCESS);
	else
		env->controls[keycode] = 1;
	return (1);
}

int	key_release_hook(int keycode, t_env *env)
{
	env->controls[keycode] = 0;
	return (1);
}

int	mouse_move_hook(int x, int y, t_env *env)
{
	int	dx;

	(void)y;
	dx = WIN_X_SZ / 2 - x;
	if (dx)
		env->playerDir = dvec_rot(env->playerDir,
				(double)(-M_PI * dx / 1800.0), 1);
	mlx_mouse_move(env->mlx, env->win, WIN_X_SZ / 2, WIN_Y_SZ / 2);
	return (1);
}

int	update_hook(t_env *env)
{	
	t_dvec	d;

	d.x = ((env->controls[KEY_W] - env->controls[KEY_S]) * env->playerDir.x \
		+ (env->controls[KEY_D] - env->controls[KEY_A]) * env->camPlan.x) \
		/ (20 - env->controls[KEY_SHFT] * 10);
	d.y = ((env->controls[KEY_W] - env->controls[KEY_S]) * env->playerDir.y \
		+ (env->controls[KEY_D] - env->controls[KEY_A]) * env->camPlan.y) \
		/ (20 - env->controls[KEY_SHFT] * 10);
	if (env->map[(int)env->playerPos.y][(int)(env->playerPos.x + d.x)] != '1')
		dvec_set(&env->playerPos, env->playerPos.x + d.x, env->playerPos.y);
	if (env->map[(int)(env->playerPos.y + d.y)][(int)env->playerPos.x] != '1')
		dvec_set(&env->playerPos, env->playerPos.x, env->playerPos.y + d.y);
	env->playerDir = dvec_rot(env->playerDir, (double)(env->controls[KEY_RIGHT]
				- env->controls[KEY_LEFT]) * M_PI / 180, 1);
	env->camPlan = dvec_rot(env->playerDir, M_PI / 2, 0.66);
	render(env);
	return (1);
}
