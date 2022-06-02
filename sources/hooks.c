/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:47:30 by narnaud           #+#    #+#             */
/*   Updated: 2022/06/02 17:50:36 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press_hook(int keycode, t_env *env)
{
	if (keycode == KEY_M)
		env->minimap = !env->minimap;
	if (keycode == KEY_F1)
		env->debug = !env->debug;
	else
		env->controls[keycode] = 1;
	if (env->debug)
		printf("Key pressed: %d\n", keycode);
	return (1);
}

int	key_release_hook(int keycode, t_env *env)
{
	env->controls[keycode] = 0;
	return (1);
}

int	mouse_move_hook(int x, int y, t_env *env)
{
	(void)y;
	if (env->mouseX)
	{
		if (env->mouseX - x > 0)
			env->playerDir = rot_vec(env->playerDir, (double)( -M_PI / 90), 1);
		else if (env->mouseX - x < 0)
			env->playerDir = rot_vec(env->playerDir, (double)( M_PI / 90), 1);
		env->mouseX = x;
	}
	return (1);
}

int	mouse_down_hook(int buton, int x, int y, t_env *env)
{
	(void)buton;
	(void)y;
	if (!env->mouseX)
		env->mouseX = x;
	return (1);
}

int	mouse_up_hook(int buton, int x, int y, t_env *env)
{
	(void)buton;
	(void)x;
	(void)y;
	env->mouseX = 0;	
	return (1);
}

int update_hook(t_env *env)
{	
	double dX;
	double dY;

	env->tick++;
	dX =  ((env->controls[KEY_W] - env->controls[KEY_S]) * env->playerDir.x 
		+ (env->controls[KEY_D] - env->controls[KEY_A]) * env->camPlan.x )
		/ (20 - env->controls[KEY_SHFT] * 10);
	dY =  ((env->controls[KEY_W] - env->controls[KEY_S]) * env->playerDir.y 
		+ (env->controls[KEY_D] - env->controls[KEY_A]) * env->camPlan.y)
		/ (20 - env->controls[KEY_SHFT] * 10);
	if (env->map[(int)env->playerPos.y][(int)(env->playerPos.x + dX)] == '0')
			set_vec(&env->playerPos, env->playerPos.x + dX, env->playerPos.y);
	if (env->map[(int)(env->playerPos.y + dY)][(int)env->playerPos.x] == '0')
			set_vec(&env->playerPos, env->playerPos.x, env->playerPos.y + dY);
	env->playerDir = rot_vec(env->playerDir, 
		(double)(env->controls[KEY_E] - env->controls[KEY_Q]) * M_PI / 72, 1);
	env->camPlan = rot_vec(env->playerDir, M_PI / 2, 0.66);
	if (env->debug && !(env->tick % 50))
	{
		printf("playerPos: %f, %f. playerDir: %f, %f\n",
			env->playerPos.x, env->playerPos.y, env->playerDir.x, env->playerDir.y);
		printf("camPlan: %f, %f\n", env->camPlan.x, env->camPlan.y);
	}
	render(env);
	return (1);
}
