/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:47:30 by narnaud           #+#    #+#             */
/*   Updated: 2022/06/01 17:10:10 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press_hook(int keycode, t_env *env)
{
	if (keycode == KEY_M)
		env->minimap = !env->minimap;
	else
		env->controls[keycode] = 1;
	return (1);
}

int	key_release_hook(int keycode, t_env *env)
{
	env->controls[keycode] = 0;
	return (1);
}

int update_hook(t_env *env)
{	
	double dX;
	double dY;

	dX =  (env->controls[KEY_W] - env->controls[KEY_S]) * env->playerDir.x 
		/ (10 - env->controls[KEY_SHFT] * 5);
	dY =  (env->controls[KEY_W] - env->controls[KEY_S]) * env->playerDir.y 
		/ (10 - env->controls[KEY_SHFT] * 5);
	
	if (env->map[(int)env->playerPos.y][(int)(env->playerPos.x + dX)] == '0')
			set_vec(&env->playerPos, env->playerPos.x + dX, env->playerPos.y);
	if (env->map[(int)(env->playerPos.y + dY)][(int)env->playerPos.x] == '0')
			set_vec(&env->playerPos, env->playerPos.x, env->playerPos.y + dY);
	rot_vec(&env->playerDir, 
		(double)(env->controls[KEY_D] - env->controls[KEY_A]) * M_PI / 36);
	rot_vec(&env->camPlan, 
		(double)(env->controls[KEY_D] - env->controls[KEY_A]) * M_PI / 36);
	if (DEBUG)
	{
	printf("playerPos: %f, %f. playerDir: %f, %f\n", env->playerPos.x, env->playerPos.y, env->playerDir.x, env->playerDir.y);
	printf("camPlan: %f, %f\n", env->camPlan.x, env->camPlan.y);
	}
	render(env);
	return (1);
}
