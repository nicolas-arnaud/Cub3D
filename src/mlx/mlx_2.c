/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:47:30 by narnaud           #+#    #+#             */
/*   Updated: 2022/11/21 18:57:55 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	exit_game(t_env *env)
{
	int	i;

	i = 0;
	while (i < 5)
		mlx_destroy_image(env->mlx, env->tex[i++].img);
	mlx_destroy_image(env->mlx, env->img);
	exit(EXIT_SUCCESS);
}

int	key_press_hook(int keycode, t_env *env)
{
	if (keycode == KEY_M)
		env->minimap = !env->minimap;
	else if (keycode == KEY_ECHAP)
		exit_game(env);
	else
		env->controls[keycode] = 1;
	return (1);
}

int	key_release_hook(int keycode, t_env *env)
{
	env->controls[keycode] = 0;
	return (1);
}

int	update_hook(t_env *env)
{	
	t_dvec	d;

	d.x = ((env->controls[KEY_W] - env->controls[KEY_S]) * env->player_dir.x \
		+ (env->controls[KEY_D] - env->controls[KEY_A]) * env->cam_plan.x) \
		/ (20 - env->controls[KEY_SHFT] * 10);
	d.y = ((env->controls[KEY_W] - env->controls[KEY_S]) * env->player_dir.y \
		+ (env->controls[KEY_D] - env->controls[KEY_A]) * env->cam_plan.y) \
		/ (20 - env->controls[KEY_SHFT] * 10);
	if (env->map[(int)env->player_pos.y][(int)(env->player_pos.x + d.x)] != '1')
		dvec_set(&env->player_pos, env->player_pos.x + d.x, env->player_pos.y);
	if (env->map[(int)(env->player_pos.y + d.y)][(int)env->player_pos.x] != '1')
		dvec_set(&env->player_pos, env->player_pos.x, env->player_pos.y + d.y);
	env->player_dir = dvec_rot(env->player_dir,
			(double)(env->controls[KEY_RIGHT] - env->controls[KEY_LEFT])
			* M_PI / 180, 1);
	env->cam_plan = dvec_rot(env->player_dir, M_PI / 2, 0.66);
	render(env);
	return (1);
}
